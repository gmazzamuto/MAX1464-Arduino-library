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

#ifndef MAX1464_H
#define MAX1464_H

#include "lib/AbstractMAX1464.h"
#include <SPI.h>

/**
 * @brief Interface to the Maxim %MAX1464 Multichannel Sensor Signal Processor,
 * Arduino SPI library version.
 *
 * This class makes use of the Arduino SPI library with 4-wire data transfer
 * mode.
 */

class MAX1464 : public AbstractMAX1464
{
public:
    MAX1464(const int chipSelect);
    virtual void begin();
    virtual void end();

    virtual void byteShiftOut(
            const uint8_t b, const char *debugMsg = NULL) const;
    virtual uint16_t wordShiftIn() const;

private:
    SPISettings settings;
};

#endif // MAX1464_H
