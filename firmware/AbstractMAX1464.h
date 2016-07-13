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
#include "max1464_enums.h"

//#define SERIALDEBUG

class AbstractMAX1464
{

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
