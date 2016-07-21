# Introduction

This library implements a complete interface to the [Maxim MAX1464
Multichannel Sensor Signal Processor](https://www.maximintegrated.com/en/products/analog/sensors-and-sensor-interface/MAX1464.html)
for Arduino.

There are two classes provided with this library. The MAX1464 class makes use of
Arduino's SPI library, whereas the MAX1464_SS class implements SPI in software
on the user-specified pins. See the [documentation](https://gmazzamuto.github.io/MAX1464-Arduino-library/index.html)
for a complete reference.

## Tutorial

To use the library, include the header file:
```cpp
#include <MAX1464.h>
```
or
```cpp
#include <MAX1464_SS.h>
```
if you prefer to use software SPI.

Define a macro for the slave select pin:
```cpp
#define SPI_SLAVESELECT 10
```

If you are using software SPI, you also need to define the pins for MOSI, MISO
and SCK:
```cpp
#define SPI_DATAOUT 11  // MOSI
#define SPI_DATAIN  12  // MISO
#define SPI_CLOCK   13  // SCK
```

In case you need to use register addresses, configuration bits, etc, add this
line to access the corresponding enums easily:
```cpp
using namespace MAX1464_enums;
```

Then, create an instance of the MAX1464 or MAX1464_SS class:
```cpp
MAX1464 max1464(SPI_SLAVESELECT);
```
```cpp
MAX1464_SS max1464(SPI_SLAVESELECT); // for software SPI
```

In your `setup()` function, call the `begin()` method:
```cpp
max1464.begin();
```
For software SPI:
```cpp
max1464.setSpiPins(SPI_DATAOUT, SPI_DATAIN, SPI_CLOCK); // for software SPI only
max1464.begin();
```

Now the library is initialized and you can use it in your `loop()` function.

## Common operations

To control the CPU state:
```cpp
max1464.haltCpu();
max1464.resetCpu();
max1464.releaseCpu();
```

To write to and read from CPU ports:
```cpp
max1464.writeCpuPort(0x1234, CPU_PORT_A);
uint16_t value = max1464.readCpuPort(CPU_PORT_A);
```

To write to and read from module registers:
```cpp
max1464.writeModuleRegister(
            CONFIGA_PGA_00 | CONFIGA_CLK6 | CONFIGA_RES_9BIT | CONFIGA_CO0,
            R_ADC_CONFIG_1A);
max1464.writeModuleRegister(GPIO_OUT_HIGH, GPIO1_CONTROL);
uint16_t value = max1464.readModuleRegister(GPIO1_CONTROL);
```
Please refer to the documentation for a complete list of
[available enums](https://gmazzamuto.github.io/MAX1464-Arduino-library/namespaceMAX1464__enums.html).

To write to flash memory:
```cpp
max1464.beginWritingToFlashPartition(PARTITION_0);
max1464.writeHexLineToFlashMemory(inputString); // HEX line 1
max1464.writeHexLineToFlashMemory(inputString); // HEX line 2
...
```
## Example

The library comes with an example Arduino sketch implementing a serial terminal.
This is a list of the serial commands available in the example:

- `IDEN` print an identification string
- `RFW [N]` read firmware (partition `N`)
- `HALTCPU`
- `RESETCPU`
- `RELEASECPU`
- `RP N` read CPU port number `N` (0-15)
- `STEP` single step the CPU, useful for debugging
- `!ERASEFLASHMEMORY!` (both partitions)
- `!WRITEFLASHMEMORY!` enter firmware flashing mode. From now on, only HEX lines
   are expected from the serial port. You can then send a whole HEX file using
   your terminal emulator. Normal command mode is resumed after the last HEX
   line has been sent, or alternatively by issuing the `!ABORTWRITEFLASHMEMORY!`
   command.
- `!ABORTWRITEFLASHMEMORY!` see above
