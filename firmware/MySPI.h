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

#ifndef MYSPI_H
#define MYSPI_H
//#define SERIALDEBUG

#define DATAOUT 11 //MOSI
#define DATAIN  12 //MISO
#define SPICLOCK 13 //sck
#define SS 10

#include <Arduino.h>

class MySPI {
public:
    MySPI() { chipSelect = SS; }

    void SPISetup();
    void bitOut(boolean b);
    void byteShiftOut(byte b, const char *debugMsg = NULL);
    boolean bitIn();
    uint16_t wordShiftIn();
    void setChipSelect(unsigned int cs) { chipSelect = cs; }

private:
    unsigned int chipSelect;
};



#endif // MYSPI_H
