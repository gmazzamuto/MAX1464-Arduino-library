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

#ifndef MAX1464_SS_H
#define MAX1464_SS_H

#include "AbstractMAX1464.h"

class MAX1464_SS : public AbstractMAX1464
{
public:
    MAX1464_SS(const int chipSelect);
    virtual void begin();

    virtual void byteShiftOut(
            const uint8_t b, const char *debugMsg = NULL) const;
    virtual uint16_t wordShiftIn() const;
    void setPins(const int dataout, const int datain, const int clock);

private:
    int _spi_dataout, _spi_datain, _spi_clock;
};

#endif // MAX1464_SS_H
