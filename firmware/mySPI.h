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

#ifndef SPI_H
#define SPI_H

#include "printhex.h"

#define DATAOUT 11 //MOSI
#define DATAIN  12 //MISO
#define SPICLOCK 13 //sck
#define SS 10

void SPISetup() {
    pinMode(DATAOUT, OUTPUT);
    pinMode(DATAIN, INPUT);
    pinMode(SPICLOCK,OUTPUT);
    pinMode(SS,OUTPUT);

    digitalWrite(DATAOUT,LOW);
    digitalWrite(SPICLOCK,LOW);
    digitalWrite(SS,HIGH); //disable device
    delayMicroseconds(1);
}

void bitOut(boolean b) {
#ifdef SERIALDEBUG
    if(b)
        Serial.print('1');
    else
        Serial.print('0');
#endif
    digitalWrite(DATAOUT,b);
    delayMicroseconds(1);
    digitalWrite(SPICLOCK,HIGH);
    delayMicroseconds(1);
    digitalWrite(SPICLOCK,LOW);
    delayMicroseconds(1);
}

void byteShiftOut(byte b, const char* debugMsg = NULL) {
    digitalWrite(SS, LOW);
    delayMicroseconds(1);
#ifdef SERIALDEBUG
    Serial.print("tx byte: ");
    PrintHex8(&b,1);
#endif
    for(int i=0;i<8;i++) {
#ifdef SERIALDEBUG
        if(i==4)
            Serial.print(" ");
#endif
        bitOut(b & (1<<i));
    }
#ifdef SERIALDEBUG
    if(debugMsg == NULL)
        debugMsg = "";
    Serial.println(String(" //") + debugMsg);
#endif
    digitalWrite(SS, HIGH);
    delayMicroseconds(1);
}

boolean bitIn() {
    digitalWrite(SPICLOCK,HIGH);
    delayMicroseconds(1);
    boolean in = digitalRead(DATAIN);
#ifdef SERIALDEBUG
    if(in)
        Serial.print('1');
    else
        Serial.print('0');
#endif
    digitalWrite(SPICLOCK,LOW);
    delayMicroseconds(1);
    return in;
}

uint16_t wordShiftIn() {
    digitalWrite(SS, LOW);
    delayMicroseconds(1);
    uint16_t w = 0;
#ifdef SERIALDEBUG
    Serial.print("rx word: ");
#endif
    for(int i=15;i>=0;i--) {
        w |= (bitIn() << i);
#ifdef SERIALDEBUG
    if(i%4 == 0)
        Serial.print(" ");
#endif
    }
#ifdef SERIALDEBUG
    Serial.print(" -> ");
    PrintHex16(&w,1);
    Serial.println();
#endif
    digitalWrite(SS, HIGH);
    delayMicroseconds(1);
    return w;
}

#endif // SPI_H
