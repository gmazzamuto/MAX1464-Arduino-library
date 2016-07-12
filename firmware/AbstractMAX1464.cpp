/*
  MAX1464 library for Arduino
  Copyright (C) 2016 Giacomo Mazzamuto <gmazzamuto@gmail.com>

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library. If not, see <http://www.gnu.org/licenses/>.
*/

#include "printhex.h"
#include "AbstractMAX1464.h"

#ifdef SERIALDEBUG
const char *cr_commands_debug_msgs[16] = {
    "CR_WRITE16_DHR_TO_CPU_PORT",
    "CR_WRITE8_DHR_TO_FLASH_MEMORY",
    "CR_READ16_CPU_PORT",
    "CR_READ8_FLASH",
    "CR_READ16_CPU_ACC",
    "CR_READ8_FLASH_SPEC_PC",
    "CR_READ16_PC",
    "CR_HALT_CPU",
    "CR_START_CPU",
    "CR_SINGLE_STEP_CPU",
    "CR_RESET_PC",
    "CR_RESET_MODULES",
    "CR_NOP",
    "CR_ERASE_FLASH_PAGE",
    "CR_ERASE_FLASH_PARTITION",
    "CR_SELECT_FLASH_PARTITION_1"
};
#endif

AbstractMAX1464::AbstractMAX1464(int chipSelect)
{
    _chipSelect = chipSelect;
    _3wireMode = true;
    pinMode(_chipSelect, OUTPUT);
    digitalWrite(_chipSelect, HIGH);
}



//CR functions

void AbstractMAX1464::haltCPU()
{
    writeCR(CR_HALT_CPU);
}

void AbstractMAX1464::resetCPU()
{
    haltCPU();
    writeCR(CR_RESET_PC);
    releaseCPU();
}

void AbstractMAX1464::releaseCPU()
{
    writeCR(CR_START_CPU);
}

void AbstractMAX1464::eraseFlashMemory()
{
    haltCPU();
    writeCR(CR_ERASE_FLASH_PARTITION);
}

void AbstractMAX1464::copyFlashToDHR()
{
    writeCR(CR_READ8_FLASH);
}



//IRSA functions

void AbstractMAX1464::enable4WireModeDataTransfer()
{
#ifdef SERIALDEBUG
    debugMsg = "enable 4 Wire Mode Data Transfer";
#endif
    writeNibble(IMR_4WIRE, IRSA_IMR);
    _3wireMode = false;
}

void AbstractMAX1464::enable3WireModeDataTransfer()
{
#ifdef SERIALDEBUG
    debugMsg = "enable 3 Wire Mode Data Transfer";
#endif
    writeNibble(IMR_3WIRE, IRSA_IMR);
    _3wireMode = true;
}

void AbstractMAX1464::setFlashAddress(uint16_t addr)
{
    writeNibble(0, IRSA_PFAR3);
    writeNibble((addr >> (4*2)) & 0xf, IRSA_PFAR2);
    writeNibble((addr >> (4*1)) & 0xf, IRSA_PFAR1);
    writeNibble((addr >> (4*0)) & 0xf, IRSA_PFAR0);
}

void AbstractMAX1464::writeDHR(uint16_t data)
{
    writeNibble((data >> (4*3)) & 0xf, IRSA_DHR3);
    writeNibble((data >> (4*2)) & 0xf, IRSA_DHR2);
    writeNibble((data >> (4*1)) & 0xf, IRSA_DHR1);
    writeNibble((data >> (4*0)) & 0xf, IRSA_DHR0);
}

void AbstractMAX1464::writeDHRLSB(uint8_t data)
{
    writeNibble((data >> (4*1)) & 0xf, IRSA_DHR1);
    writeNibble((data >> (4*0)) & 0xf, IRSA_DHR0);
}

void AbstractMAX1464::writeCR(CR_COMMAND cmd)
{
#ifdef SERIALDEBUG
    debugMsg = cr_commands_debug_msgs[cmd];
#endif
    writeNibble(cmd, IRSA_CR);
}



void AbstractMAX1464::startWritingToFlashMemory()
{
// see datasheet, page 21
    haltCPU();

    writeDHR(0x0000);
    byteShiftOut(0xd4);
    byteShiftOut(0x08);

    writeDHR(0x0031);
    byteShiftOut(0xe4);
    byteShiftOut(0x08);

    writeDHR(0x8000);
    byteShiftOut(0xf4);
    byteShiftOut(0x08);

    writeCR(CR_ERASE_FLASH_PARTITION);
    delay(5);
    EOFReached = false;
}


boolean AbstractMAX1464::writeHexLineToFlashMemory(const String hexline)
{
    if(hexline.charAt(0) != ':')
        return false;
    unsigned int i = 1;
    uint8_t byteCount = strtoul(hexline.substring(i,i+2).c_str(),NULL,16);
    i+=2;
    uint16_t address = strtoul(hexline.substring(i,i+4).c_str(),NULL,16);
    PrintHex::PrintHex16(&address,1);
    Serial.println();
    i+=4;
    uint8_t recordType = strtoul(hexline.substring(i,i+2).c_str(),NULL,16);
    i+=2;
    byte data[byteCount];
    uint16_t sum = byteCount+(address >> 8)+(address & 0xff)+recordType;
    for (uint8_t count = 0; count < byteCount; ++count) {
        byte b = strtoul(hexline.substring(i,i+2).c_str(),NULL,16);
        sum += b;
        data[count] = b;
        i+=2;
    }
    sum += strtoul(hexline.substring(i,i+2).c_str(),NULL,16); //checksum
    if((sum & 0xff) != 0) {
        Serial.print("Wrong checksum ");
        PrintHex::PrintHex16(&sum,1);
        return false;
    }
    if(recordType == 0x01) { //end of file
        resetCPU();
        EOFReached = true;
        return true;
    }
    if(recordType != 0x0) {
        Serial.println("Wrong recordType");
        return false;
    }
    uint16_t addr = address;
    for (uint8_t count = 0; count < byteCount; ++count)
        writeByteToFlash(addr++,data[count]);
    return true;
}

void AbstractMAX1464::readFirmware() {
    haltCPU();
    for(uint16_t addr=0; addr<16; addr++) {
        // set address
        setFlashAddress(addr);
        copyFlashToDHR();
        if(_3wireMode)
            enable3WireModeDataTransfer();

        uint16_t val = wordShiftIn();
        uint8_t val8 = val & 0xff;
        Serial.print("addr=");
        PrintHex::PrintHex16(&addr,1);
        Serial.print(" -> ");
        PrintHex::PrintHex8(&val8,1);
        Serial.println();
    }
}


void AbstractMAX1464::writeByteToFlash(const uint16_t addr, const uint8_t value)
{
    setFlashAddress(addr);
    writeDHRLSB(value);
    writeCR(CR_WRITE8_DHR_TO_FLASH_MEMORY);
    delayMicroseconds(100);
}

void AbstractMAX1464::writeNibble(uint8_t nibble, IRSA irsa)
{
    byteShiftOut((nibble << 4) | (irsa & 0xf));
}
