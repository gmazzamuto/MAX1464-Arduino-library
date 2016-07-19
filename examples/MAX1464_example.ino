/*
  Example sketch for the MAX1464 library.
  Copyright (C) 2016 Giacomo Mazzamuto <gmazzamuto@gmail.com>

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  as published by the Free Software Foundation; either version 2
  of the License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/**
 * \file
 */

#include "printhex.h"

#include "MAX1464.h"

// for software SPI
//#include "MAX1464_SS.h"
//#define SPI_DATAOUT 11    // MOSI
//#define SPI_DATAIN  12    // MISO
//#define SPI_CLOCK   13    // SCK

using namespace MAX1464_enums; // enums for register addresses, bits, etc

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete
boolean writingToFlash = false;  // whether we are currently writing to MAX1464
                                 // flash memory
unsigned long hexLinesWritten = 0; // count hex lines written during flash loop

#define SPI_SLAVESELECT 10

MAX1464 max1464(SPI_SLAVESELECT);
//MAX1464_SS max1464(SPI_SLAVESELECT); // for software SPI

void printIden() {
    Serial.println("Arduino MAX1464 Serial Terminal");
}

void setup() {
    Serial.begin(115200);
    printIden();
    inputString.reserve(200);

//    max1464.setSpiPins(
//                SPI_DATAOUT, SPI_DATAIN, SPI_CLOCK); // only for software SPI
    max1464.begin();
}

void serialEvent() {
    while (Serial.available()) {
        char inChar = (char)Serial.read();
        if (inChar == '\n') {
            stringComplete = true;
        }
        else {
            inputString += inChar;
        }
    }
}

void loop() {
    if (stringComplete) {
        inputString.toUpperCase();
        inputString = strtok((char *)inputString.c_str(), " ");
        if(writingToFlash) {
            if(String("!ABORTWRITEFLASHMEMORY!").equals(inputString)) {
                writingToFlash = false;
                Serial.println("\nAbort writing to flash memory...");
            }
            else if(!max1464.writeHexLineToFlashMemory(inputString)) {
                Serial.print("\nIllegal line ");
                Serial.println(inputString);
            }
            else {
                Serial.print(".");
                hexLinesWritten++;
                if(hexLinesWritten>80) {
                    hexLinesWritten = 0;
                    Serial.println();
                }
                if(max1464.hasEOFBeenReached()) {
                    writingToFlash = false;
                    Serial.println();
                }
            }
        }
        else if(String("IDEN").startsWith(inputString)) {
            printIden();
        }
        else if(String("RFW").startsWith(inputString)) {
            char *partition_cp = strtok(NULL, " ");
            uint8_t partition = 0;
            if(partition_cp != NULL) {
                partition = atoi(partition_cp);
            }
            max1464.readFlashPartition((FLASH_PARTITION)partition);
        }
        else if(String("HALTCPU").startsWith(inputString)) {
            Serial.println("Halting CPU");
            max1464.haltCpu();
        }
        else if(String("RESETCPU").startsWith(inputString)) {
            Serial.println("Resetting CPU");
            max1464.resetCpu();
        }
        else if(String("RP").startsWith(inputString)) {
            char *port_cp = strtok(NULL, " ");
            if(port_cp != NULL) {
                uint8_t port = atoi(port_cp);
                Serial.print("CPU port ");
                Serial.print(port_cp);
                Serial.print(" == ");
                uint16_t value = max1464.readCpuPort((CPU_PORT)port);
                printHex16(value);
                Serial.println();
            }
        }
        else if(String("STEP").startsWith(inputString)) {
            Serial.println("stepping");
            max1464.singleStepCpu();
        }
        else if(String("RELEASECPU").startsWith(inputString)) {
            Serial.println("Releasing CPU");
            max1464.releaseCpu();
        }
        else if(String("!ERASEFLASHMEMORY!").equals(inputString)) {
            Serial.println("Erasing FLASH memory");
            max1464.eraseFlashMemory();
        }
        else if(String("!WRITEFLASHMEMORY!").equals(inputString)) {
            char *partition_cp = strtok(NULL, " ");
            uint8_t partition = 0;
            if(partition_cp != NULL) {
                partition = atoi(partition_cp);
            }
            writingToFlash = true;
            hexLinesWritten = 0;
            max1464.beginWritingToFlashPartition((FLASH_PARTITION)partition);
            Serial.println("Writing to flash memory...");
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
