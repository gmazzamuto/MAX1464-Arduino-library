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

#ifndef ABSTRACTMAX1464_H
#define ABSTRACTMAX1464_H

#include <Arduino.h>

//#define SERIALDEBUG

class AbstractMAX1464
{

    enum CR_COMMAND {
        CR_WRITE16_DHR_TO_CPU_PORT = 0x0,
        CR_WRITE8_DHR_TO_FLASH_MEMORY = 0x1,
        CR_READ16_CPU_PORT = 0x2,
        CR_READ8_FLASH = 0x3,
        CR_READ16_CPU_ACC = 0x4,
        CR_READ8_FLASH_SPEC_PC = 0x5,
        CR_READ16_CPU_PC = 0x6,
        CR_HALT_CPU = 0x7,
        CR_START_CPU = 0x8,
        CR_SINGLE_STEP_CPU = 0x9,
        CR_RESET_PC = 0xa,
        CR_RESET_MODULES = 0xb,
        CR_NOP = 0xc,
        CR_ERASE_FLASH_PAGE = 0xd,
        CR_ERASE_FLASH_PARTITION = 0xe,
        CR_SELECT_FLASH_PARTITION_1 = 0xf
    };

    //Internal Register Set Address
    enum IRSA {
        IRSA_DHR0 = 0x0,
        IRSA_DHR1 = 0x1,
        IRSA_DHR2 = 0x2,
        IRSA_DHR3 = 0x3,
        IRSA_PFAR0 = 0x4,
        IRSA_PFAR1 = 0x5,
        IRSA_PFAR2 = 0x6,
        IRSA_PFAR3 = 0x7,
        IRSA_CR = 0x8,
        IRSA_IMR = 0x9
    };

    //Interface Mode Register
    enum IMR {
        IMR_4WIRE = 0x0,
        IMR_3WIRE = 0x1
    };

    enum CPU_PORT {
        PORT_0 = 0x0,
        PORT_1 = 0x1,
        PORT_2 = 0x2,
        PORT_3 = 0x3,
        PORT_4 = 0x4,
        PORT_5 = 0x5,
        PORT_6 = 0x6,
        PORT_7 = 0x7,
        PORT_8 = 0x8,
        PORT_9 = 0x9,
        PORT_A = 0xa,
        PORT_B = 0xb,
        PORT_C = 0xc,
        PORT_D, MODULE_DATA_PORT = 0xd,
        PORT_E, MODULE_ADDRESS_PORT = 0xe,
        PORT_F, MODULE_CONTROL_PORT = 0xf,
    };

public:
    AbstractMAX1464(int chipSelect = 10);
    virtual void begin() {}

    // simple CR functions
    void haltCpu();
    void resetCpu();
    void releaseCpu();
    void eraseFlashMemory();
    void copyFlashToDhr();
    void singleStepCpu();

    // IRSA functions
    void enable4WireModeDataTransfer();
    void enable3WireModeDataTransfer();
    void setFlashAddress(uint16_t addr);
    void writeDHR(uint16_t data);
    void writeDHRLSB(uint8_t data);
    void writeCR(CR_COMMAND cmd);
    void writeNibble(uint8_t nibble, IRSA irsa);

    // Flash memory
    void startWritingToFlashMemory(uint8_t partition = 0);
    boolean writeHexLineToFlashMemory(const String hexline);
    void readFirmware(uint8_t partition = 0);
    void writeByteToFlash(const uint16_t addr, const uint8_t value);

    // CPU ports
    uint16_t readCpuPort(uint8_t port);
    void writeCpuPort(uint16_t word, uint8_t port);
    void writeModuleRegister(const uint16_t data, const uint16_t addr);
    uint16_t readModuleRegister(const uint16_t addr);

    // CPU registers
    uint16_t readCpuAccumulatorRegister();
    uint16_t readCpuProgramCounter();

    virtual void byteShiftOut(uint8_t b) = 0;
    virtual uint16_t wordShiftIn() = 0;

    boolean hasEOFBeenReached() {return EOFReached;}

private:
    boolean EOFReached;
    boolean _3wireMode;

protected:
    int _chipSelect;
#ifdef SERIALDEBUG
    const char *debugMsg;
#endif
};


#endif // ABSTRACTMAX1464_H
