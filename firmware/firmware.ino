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

#include "printhex.h"
#include "MAX1464.h"

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete
boolean writingToFlash = false;  // whether we are currently writing to MAX1464 flash memory
unsigned long flashLinesWritten = 0; // count hex lines during flash loop
MAX1464 maxim(10);

void printIden() {
    Serial.println("Arduino MAX1464 Serial Terminal");
}

void setup() {
    // initialize serial:
    Serial.begin(115200);
    printIden();
    // reserve 200 bytes for the inputString:
    inputString.reserve(200);

//    maxim.setPins(11,12,13); // only for software SPI
    maxim.begin();
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

void writeToFlashMemory() {

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
            else if(!maxim.writeHexLineToFlashMemory(inputString)) {
                Serial.print("\nIllegal line ");
                Serial.println(inputString);
            }
            else {
                if(maxim.hasEOFBeenReached())
                    writingToFlash = false;
                Serial.print(".");
                flashLinesWritten++;
                if(flashLinesWritten>80) {
                    flashLinesWritten = 0;
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
            maxim.readFirmware(partition);
        }
        else if(String("HALTCPU").startsWith(inputString)) {
            Serial.println("Halting CPU");
            maxim.haltCpu();
        }
        else if(String("RESETCPU").startsWith(inputString)) {
            Serial.println("Resetting CPU");
            maxim.resetCpu();
        }
        else if(String("RP").startsWith(inputString)) {
            char *port_cp = strtok(NULL, " ");
            if(port_cp != NULL) {
                uint8_t port = atoi(port_cp);
                Serial.print("CPU port ");
                Serial.print(port_cp);
                Serial.print(" == ");
                uint16_t value = maxim.readCpuPort(port);
                printHex16(value);
                Serial.println();
            }
        }
        else if(String("STEP").startsWith(inputString)) {
            Serial.println("stepping");
            maxim.singleStepCpu();
        }
        else if(String("RELEASECPU").startsWith(inputString)) {
            Serial.println("Releasing CPU");
            maxim.releaseCpu();
        }
        else if(String("!ERASEFLASHMEMORY!").equals(inputString)) {
            Serial.println("Erasing FLASH memory");
            maxim.eraseFlashMemory();
        }
        else if(String("!WRITEFLASHMEMORY!").equals(inputString)) {
            char *partition_cp = strtok(NULL, " ");
            uint8_t partition = 0;
            if(partition_cp != NULL) {
                partition = atoi(partition_cp);
            }
            writingToFlash = true;
            flashLinesWritten = 0;
            maxim.startWritingToFlashMemory(partition);
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
