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

#define DATAOUT 11//MOSI
#define DATAIN  12//MISO
#define SPICLOCK  13//sck

#define SERIALDEBUG

void transfer_bit(boolean b) {
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

void transfer_byte(byte b, const char* debugMsg = NULL) {
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
        transfer_bit(b & (1<<i));
    }
    #ifdef SERIALDEBUG
    if(debugMsg == NULL)
    debugMsg = "";
    Serial.println(String(" //") + debugMsg);
    #endif
    digitalWrite(SS, HIGH);
    delayMicroseconds(1);
}

boolean read_bit() {
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

uint16_t read_word() {
    digitalWrite(SS, LOW);
    delayMicroseconds(1);
    uint16_t w = 0;
    #ifdef SERIALDEBUG
    Serial.print("rx word: ");
    #endif
    for(int i=15;i>=0;i--) {
        w |= (read_bit() << i);
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

#define SS 10

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

void PrintHex8(uint8_t *data, uint8_t length) // prints 8-bit data in hex with leading zeroes
{
    Serial.print("0x");
    for (int i=0; i<length; i++) {
        if (data[i]<0x10) {Serial.print("0");}
        Serial.print(data[i],HEX);
        Serial.print(" ");
    }
}

void PrintHex16(uint16_t *data, uint8_t length) // prints 16-bit data in hex with leading zeroes
{
    Serial.print("0x");
    for (int i=0; i<length; i++)
    {
        uint8_t MSB=byte(data[i]>>8);
        uint8_t LSB=byte(data[i]);

        if (MSB<0x10) {Serial.print("0");} Serial.print(MSB,HEX); Serial.print(" ");
        if (LSB<0x10) {Serial.print("0");} Serial.print(LSB,HEX); Serial.print(" ");
    }
}

void printIden() {
    Serial.println("Arduino MAX1464 Serial Terminal");
}

void myTransfer(uint8_t b, const char* debugMsg=NULL) {
    transfer_byte(b,debugMsg);
}

void setup() {
    // initialize SPI:
    //  SPI.begin();

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
    b = 0x78;
    myTransfer(b, "reset CPU"); //reset CPU
    Serial.println();
    for(uint16_t addr=0; addr<1; addr++) {
        // set address
        myTransfer(0x07);
        for(int i=2;i>=0;i--){
            byte msNibble;
            msNibble = (addr >> (8*i)) & 0xff;
            b = (msNibble << 4) | 6 + (i-2);
            myTransfer(b, String(String("write address to be read to PFAR:") + String("0x") + String(addr,HEX)).c_str());
        }
        Serial.println();
        myTransfer(0x38,"copying FLASH to DHR");
        Serial.println();
        uint16_t val = read_word(); //read
        Serial.print("addr=");
        PrintHex16(&addr,1);
        Serial.print(" -> ");
        PrintHex16(&val,1);
        Serial.println('--------------');
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
