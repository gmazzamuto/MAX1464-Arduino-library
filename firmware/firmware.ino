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

// #define SERIALDEBUG
#include "mySPI.h"

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

void printIden() {
    Serial.println("Arduino MAX1464 Serial Terminal");
}

void myTransfer(uint8_t b, const char* debugMsg=NULL) {
    transfer_byte(b,debugMsg);
}

void setup() {
    // initialize serial:
    Serial.begin(115200);
    printIden();
    // reserve 200 bytes for the inputString:
    inputString.reserve(200);

    pinMode(DATAOUT, OUTPUT);
    pinMode(DATAIN, INPUT);
    pinMode(SPICLOCK,OUTPUT);
    pinMode(SS,OUTPUT);

    digitalWrite(DATAOUT,LOW);
    digitalWrite(SPICLOCK,LOW);
    digitalWrite(SS,HIGH); //disable device
    delayMicroseconds(1);
    myTransfer(0x09, "Enable 4-wire mode data read");
}

void readFirmware() {
    uint8_t b;
    myTransfer(0x78, "reset CPU"); //reset CPU
#ifdef SERIALDEBUG
    Serial.println();
#endif
    for(uint16_t addr=0; addr<1; addr++) {
        // set address
        myTransfer(0x07);
        for(int i=2;i>=0;i--){
            byte msNibble;
            msNibble = (addr >> (8*i)) & 0xff;
            b = (msNibble << 4) | 6 + (i-2);
            myTransfer(b, String(String("write address to be read to PFAR:") + String("0x") + String(addr,HEX)).c_str());
        }
#ifdef SERIALDEBUG
        Serial.println();
#endif
        myTransfer(0x38,"copying FLASH to DHR");
#ifdef SERIALDEBUG
        Serial.println();
#endif
        uint16_t val = read_word();
#ifdef SERIALDEBUG
        Serial.print("addr=");
        PrintHex16(&addr,1);
        Serial.print(" -> ");
        PrintHex16(&val,1);
        Serial.println('--------------');
#endif
    }
}

void haltCPU() {
    Serial.println("Halting CPU");
    myTransfer(0x78);
}

void flashFirmware() {

}

void eraseFlashMemory() {
    Serial.println("Erasing FLASH memory");
    myTransfer(0x78);
    myTransfer(0xe8);
}

/*
SerialEvent occurs whenever a new data comes in the
hardware serial RX.  This routine is run between each
time loop() runs, so using delay inside loop can delay
response.  Multiple bytes of data may be available.
*/
void serialEvent() {
    while (Serial.available()) {
        // get the new byte:
        char inChar = (char)Serial.read();
        // if the incoming character is a newline, set a flag
        // so the main loop can do something about it:
        if (inChar == '\n') {
            stringComplete = true;
        }
        else {
            // add it to the inputString:
            inputString += inChar;
        }
    }
}

void loop() {
    if (stringComplete) {
        inputString.toUpperCase();
        if(String("IDEN").startsWith(inputString)) {
            printIden();
        }
        else if(String("RFW").startsWith(inputString)) {
            readFirmware();
        }
        else if(String("HALTCPU").startsWith(inputString)) {
            haltCPU();
        }
        else if(String("!ERASEFLASHMEMORY!").equals(inputString)) {
            eraseFlashMemory();
        }
        else {
            Serial.print("Unknown input string: ");
            Serial.println(inputString);
        }

        // clear the string:
        inputString = "";
        stringComplete = false;
    }
}
