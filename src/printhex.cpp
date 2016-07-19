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

/**
 * \file
 */

#include "printhex.h"

void printHex8(const uint8_t b)
{
    Serial.print("0x");
    if (b < 16)
        Serial.print("0");
    Serial.print(b, HEX);
    Serial.print(" ");
}

void printHex16(const uint16_t word)
{
    Serial.print("0x");
    union { uint16_t val; struct { uint8_t lsb; uint8_t msb; }; } w;
    w.val = word;
    if (w.msb < 16)
        Serial.print("0");
    Serial.print(w.msb, HEX);
    Serial.print(" ");
    if (w.lsb < 16)
        Serial.print("0");
    Serial.print(w.lsb, HEX);
    Serial.print(" ");
}
