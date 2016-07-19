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

#include "MAX1464_SS.h"
#include "printhex.h"

using namespace MAX1464_enums;

MAX1464_SS::MAX1464_SS(const int chipSelect) :
    AbstractMAX1464(chipSelect)
{
    _spi_dataout = 11;
    _spi_datain = 12;
    _spi_clock = 13;
}

/**
 * @brief Initialize the SPI bus.
 *
 * Initializes the specified SPI pins to outputs, pulling SCK and MOSI low, and
 * SS high.
 */

void MAX1464_SS::begin()
{
    pinMode(_spi_dataout, OUTPUT);
    if(!_3wireMode)
        pinMode(_spi_datain, INPUT);
    pinMode(_spi_clock, OUTPUT);
    pinMode(_chipSelect, OUTPUT);

    digitalWrite(_spi_dataout, LOW);
    digitalWrite(_spi_clock, LOW);
    digitalWrite(_chipSelect, HIGH); //disable device
}

void MAX1464_SS::byteShiftOut(const uint8_t b, const char *debugMsg) const
{
#ifdef MAX1464_SERIALDEBUG
    printHex8(b);
    if(debugMsg != NULL)
        Serial.println(debugMsg);
#endif
    digitalWrite(_spi_clock, LOW);
    digitalWrite(_chipSelect,LOW);
    shiftOut(_spi_dataout, _spi_clock, LSBFIRST, b);
    digitalWrite(_chipSelect, HIGH);
}

uint16_t MAX1464_SS::wordShiftIn() const
{
    if(_3wireMode) {
        writeNibble(IMR_3WIRE, IRSA_IMR);
        pinMode(_spi_datain, INPUT);
    }
    uint16_t w = 0;
    digitalWrite(_spi_clock, LOW);
    digitalWrite(_chipSelect, LOW);
    w |= (shiftIn(_spi_datain, _spi_clock, MSBFIRST) << 8);
    w |= (shiftIn(_spi_datain, _spi_clock, MSBFIRST));
    digitalWrite(_chipSelect, HIGH);
    if(_3wireMode) {
        pinMode(_spi_dataout, OUTPUT);
        digitalWrite(_spi_dataout, LOW);
    }
    return w;
}

/**
 * @brief Set the pins to be used for SPI communication.
 * @param dataout MOSI
 * @param datain MISO
 * @param clock SCK
 *
 * If dataout and datain are the same pin, the device is configured in 3-wire
 * SPI mode.
 */

void MAX1464_SS::setSpiPins(
        const int dataout, const int datain, const int clock)
{
    _spi_datain = datain;
    _spi_dataout = dataout;
    _spi_clock = clock;
    if(_spi_datain == _spi_dataout)
        _3wireMode = true;
    else
        _3wireMode = false;
}
