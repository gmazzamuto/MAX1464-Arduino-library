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
#include "MAX1464.h"

MAX1464::MAX1464() :
    MySPI()
{

}

void MAX1464::readFirmware() {
    haltCPU();
#ifdef SERIALDEBUG
    Serial.println();
#endif
    for(uint16_t addr=0; addr<1; addr++) {
        // set address
        setFlashAddress(addr);
        copyFlashToDHR();

        uint16_t val = wordShiftIn();
#ifdef SERIALDEBUG
        Serial.print("addr=");
        PrintHex::PrintHex16(&addr,1);
        Serial.print(" -> ");
        PrintHex::PrintHex16(&val,1);
        Serial.println('--------------');
#endif
    }
}

void MAX1464::haltCPU()
{
    const char *debugMsg = NULL;
#ifdef SERIALDEBUG
    debugMsg = "halt CPU";
#endif
    byteShiftOut(0x78, debugMsg);
}

void MAX1464::enable4WireModeDataTransfer()
{
    const char *debugMsg = NULL;
#ifdef SERIALDEBUG
    debugMsg = "enable 4 Wire Mode Data Transfer";
#endif
    byteShiftOut(0x09, debugMsg);
}

void MAX1464::eraseFlashMemory()
{
    const char *debugMsg = NULL;
#ifdef SERIALDEBUG
    debugMsg = "erase flash memory";
#endif
    haltCPU();
    byteShiftOut(0xe8, debugMsg);
}

void MAX1464::setFlashAddress(uint16_t addr)
{
    const char *debugMsg = NULL;
#ifdef SERIALDEBUG
    debugMsg = "write address to PFAR";
#endif
    uint8_t b;
    byteShiftOut(0x07, debugMsg);
    for(int i=2;i>=0;i--){
        byte msNibble;
        msNibble = (addr >> (8*i)) & 0xff;
        b = (msNibble << 4) | (6 + (i-2));
        byteShiftOut(b, debugMsg);
    }
#ifdef SERIALDEBUG
    Serial.println();
#endif
}

void MAX1464::copyFlashToDHR()
{
    const char *debugMsg = NULL;
#ifdef SERIALDEBUG
    debugMsg = "copy FLASH to DHR";
#endif
    byteShiftOut(0x38,debugMsg);
#ifdef SERIALDEBUG
    Serial.println();
#endif
}
