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

#ifndef ABSTRACTMAX1464_H
#define ABSTRACTMAX1464_H

#include <Arduino.h>
#include "MAX1464_enums.h"

//#define MAX1464_SERIALDEBUG

/**
 * @brief The AbstractMAX1464 class provides a complete interface to the Maxim
 * %MAX1464 Multichannel Sensor Signal Processor.
 *
 * The serial communication details are left unimplemented. The MAX1464 class
 * makes use of the Arduino SPI library, whereas the MAX1464_SS class
 * implements SPI in software.
 */

class AbstractMAX1464
{

public:
    AbstractMAX1464(const int chipSelect = 10);
    /**
     * @brief Initialize the SPI bus.
     *
     * The default implementation does nothing.
     */
    virtual void begin() {}
    virtual void end() {}

    // simple CR functions
    void haltCpu() const;
    void resetCpu() const;
    void releaseCpu() const;
    void eraseFlashMemory() const;
    void eraseFlashPartition(
            const MAX1464_enums::FLASH_PARTITION partition) const;
    void copyFlashToDhr() const;
    void singleStepCpu() const;

    // IRSA functions
    void setFlashAddress(const uint16_t addr) const;
    void writeDHR(const uint16_t data) const;
    void writeDHRLSB(const uint8_t data) const;
    void writeCR(const MAX1464_enums::CR_COMMAND cmd) const;
    void writeNibble(
            const uint8_t nibble, const MAX1464_enums::IRSA irsa) const;

    // Flash memory
    void beginWritingToFlashPartition(const MAX1464_enums::FLASH_PARTITION partition) const;
    boolean writeHexLineToFlashMemory(const String hexline);
    void readFlashPartition(
            const MAX1464_enums::FLASH_PARTITION partition
            = MAX1464_enums::PARTITION_0) const;
    void writeByteToFlash(const uint8_t value, const uint16_t addr) const;
    boolean hasEOFBeenReached() const;

    // CPU ports
    uint16_t readCpuPort(const MAX1464_enums::CPU_PORT port) const;
    void writeCpuPort(
            const uint16_t word, const MAX1464_enums::CPU_PORT port) const;

    // module registers
    void writeModuleRegister(const uint16_t data,
                             const MAX1464_enums::MODULE_REGISTER_ADDRESS addr
                             ) const;
    uint16_t readModuleRegister(
            const MAX1464_enums::MODULE_REGISTER_ADDRESS addr) const;

    // CPU registers
    uint16_t readCpuAccumulatorRegister() const;
    uint16_t readCpuProgramCounter() const;

    virtual void byteShiftOut(
            const uint8_t b, const char *debugMsg = NULL) const = 0;
    virtual uint16_t wordShiftIn() const = 0;

private:
    boolean EOFReached;

protected:
    int _chipSelect;
    boolean _3wireMode;
};


#endif // ABSTRACTMAX1464_H
