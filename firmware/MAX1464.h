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
public:
    MAX1464();
    void readFirmware();
    void haltCPU();
    void resetCPU();
    void releaseCPU();
    void writeCommand();
    void enable4WireModeDataTransfer();
    void eraseFlashMemory();
    void setFlashAddress(uint16_t addr);
    void writeDHR(uint16_t value);
    void writeDHRLSB(uint8_t value);
    void copyFlashToDHR();

    void startWritingToFlashMemory();
    boolean writeHexLineToFlashMemory(const String hexline);
    void writeByteToFlash(const uint16_t addr, const uint8_t value);

    boolean hasEOFBeenReached() {return EOFReached;}

private:
    boolean EOFReached;
};

#endif // MAX1464_H
