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
    AbstractMAX1464(const int chipSelect = 10);
    virtual void begin() {}

    // simple CR functions
    void haltCpu() const;
    void resetCpu() const;
    void releaseCpu() const;
    void eraseFlashMemory() const;
    void copyFlashToDhr() const;
    void singleStepCpu() const;

    // IRSA functions
    void enable4WireModeDataTransfer();
    void enable3WireModeDataTransfer();
    void setFlashAddress(const uint16_t addr) const;
    void writeDHR(const uint16_t data) const;
    void writeDHRLSB(const uint8_t data) const;
    void writeCR(const MAX1464_enums::CR_COMMAND cmd) const;
    void writeNibble(
            const uint8_t nibble, const MAX1464_enums::IRSA irsa) const;

    // Flash memory
    void startWritingToFlashMemory(const uint8_t partition = 0) const;
    boolean writeHexLineToFlashMemory(const String hexline);
    void readFirmware(const uint8_t partition = 0) const;
    void writeByteToFlash(const uint8_t value, const uint16_t addr) const;

    // CPU ports
    uint16_t readCpuPort(const uint8_t port) const;
    void writeCpuPort(const uint16_t word, const uint8_t port) const;
    void writeModuleRegister(const uint16_t data, const uint16_t addr) const;
    uint16_t readModuleRegister(const uint16_t addr) const;

    // CPU registers
    uint16_t readCpuAccumulatorRegister() const;
    uint16_t readCpuProgramCounter() const;

    virtual void byteShiftOut(
            const uint8_t b, const char *debugMsg = NULL) const = 0;
    virtual uint16_t wordShiftIn() const = 0;

    boolean hasEOFBeenReached() const {return EOFReached;}

private:
    boolean EOFReached;
    boolean _3wireMode;

protected:
    int _chipSelect;
};


#endif // ABSTRACTMAX1464_H
