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

#include "MAX1464.h"

MAX1464::MAX1464(int chipSelect) :
    AbstractMAX1464(chipSelect)
{
    settings = SPISettings(4000000, LSBFIRST, SPI_MODE0);
}

void MAX1464::begin()
{
    SPI.begin();
    enable4WireModeDataTransfer();
}

void MAX1464::byteShiftOut(uint8_t b)
{
#ifdef SERIALDEBUG
    if(debugMsg == NULL)
        debugMsg = "";
    Serial.println(debugMsg);
    debugMsg = NULL;
#endif
    SPI.beginTransaction(settings);
    digitalWrite(10, LOW);
    SPI.transfer(b);
    digitalWrite(10, HIGH);
    SPI.endTransaction();
}

uint16_t MAX1464::wordShiftIn()
{
    uint16_t w = 0;
    SPI.beginTransaction(settings);
    digitalWrite(_chipSelect, LOW);
    w = SPI.transfer16(0x0000);

    digitalWrite(_chipSelect, HIGH);
    SPI.endTransaction();

    // reverse bits
    uint8_t newVal = 0;
    if (w & 0x1) newVal |= 0x8000;
    if (w & 0x2) newVal |= 0x4000;
    if (w & 0x4) newVal |= 0x2000;
    if (w & 0x8) newVal |= 0x1000;
    if (w & 0x10) newVal |= 0x800;
    if (w & 0x20) newVal |= 0x400;
    if (w & 0x40) newVal |= 0x200;
    if (w & 0x80) newVal |= 0x100;
    if (w & 0x100) newVal |= 0x80;
    if (w & 0x200) newVal |= 0x40;
    if (w & 0x400) newVal |= 0x20;
    if (w & 0x800) newVal |= 0x10;
    if (w & 0x1000) newVal |= 0x8;
    if (w & 0x2000) newVal |= 0x4;
    if (w & 0x4000) newVal |= 0x2;
    if (w & 0x8000) newVal |= 0x1;

    return newVal;
}
