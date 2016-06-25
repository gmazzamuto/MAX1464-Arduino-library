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

#ifndef MAX1464_H
#define MAX1464_H

#include <Arduino.h>

#include "MySPI.h"

class MAX1464 : public MySPI
{

    enum CR_COMMAND {
        CR_WRITE16_DHR_TO_CPU_PORT = 0x0,
        CR_WRITE8_DHR_TO_FLASH_MEMORY = 0x1,
        CR_READ16_CPU_PORT = 0x2,
        CR_READ8_FLASH = 0x3,
        CR_READ16_CPU_ACC = 0x4,
        CR_READ8_FLASH_SPEC_PC = 0x5,
        CR_READ16_PC = 0x6,
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

public:
    MAX1464();
    void readFirmware();
    void haltCPU();
    void resetCPU();
    void releaseCPU();
    void eraseFlashMemory();
    void enable4WireModeDataTransfer();
    void setFlashAddress(uint16_t addr);
    void writeDHR(uint16_t value);
    void writeDHRLSB(uint8_t value);
    void copyFlashToDHR();
    void writeNibble(uint8_t nibble, IRSA irsa);
    void writeCR(CR_COMMAND cmd);

    void startWritingToFlashMemory();
    boolean writeHexLineToFlashMemory(const String hexline);
    void writeByteToFlash(const uint16_t addr, const uint8_t value);

    boolean hasEOFBeenReached() {return EOFReached;}

private:
    boolean EOFReached;
};


#endif // MAX1464_H
