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

#include "MAX1464_SS.h"

MAX1464_SS::MAX1464_SS(int chipSelect) :
    AbstractMAX1464(chipSelect)
{
    pinMode(SPI_DATAOUT, OUTPUT);
    pinMode(SPI_DATAIN, INPUT);
    pinMode(SPI_CLOCK,OUTPUT);
    pinMode(_chipSelect,OUTPUT);

    digitalWrite(SPI_DATAOUT,LOW);
    digitalWrite(SPI_CLOCK,LOW);
    digitalWrite(_chipSelect,HIGH); //disable device
}

void MAX1464_SS::byteShiftOut(uint8_t b)
{
    digitalWrite(SPI_CLOCK, LOW);
    digitalWrite(_chipSelect,LOW);
    shiftOut(SPI_DATAOUT, SPI_CLOCK, LSBFIRST, b);
    digitalWrite(_chipSelect,HIGH);
}

uint16_t MAX1464_SS::wordShiftIn()
{
    uint16_t w = 0;
    digitalWrite(SPI_CLOCK, LOW);
    digitalWrite(_chipSelect, LOW);
    w |= (shiftIn(SPI_DATAIN, SPI_CLOCK, MSBFIRST) << 8);
    w |= (shiftIn(SPI_DATAIN, SPI_CLOCK, MSBFIRST));
    digitalWrite(_chipSelect,HIGH);
    return w;
}
