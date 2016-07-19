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

#ifndef MAX1464_ENUMS_H
#define MAX1464_ENUMS_H

/**
 * \brief Enumerations for register addresses, configuration bits, etc.
 */

namespace MAX1464_enums {


// Command Register

/**
 * @brief Command Register (CR) decoding.
 */

enum CR_COMMAND {
    CR_WRITE16_DHR_TO_CPU_PORT      = 0x0,
    CR_WRITE8_DHR_TO_FLASH_MEMORY   = 0x1,
    CR_READ16_CPU_PORT              = 0x2,
    CR_READ8_FLASH                  = 0x3,
    CR_READ16_CPU_ACC               = 0x4,
    CR_READ8_FLASH_PC               = 0x5,
    CR_READ16_CPU_PC                = 0x6,
    CR_HALT_CPU                     = 0x7,
    CR_START_CPU                    = 0x8,
    CR_SINGLE_STEP_CPU              = 0x9,
    CR_RESET_PC                     = 0xa,
    CR_RESET_MODULES                = 0xb,
    CR_NOP                          = 0xc,
    CR_ERASE_FLASH_PAGE             = 0xd,
    CR_ERASE_FLASH_PARTITION        = 0xe,
    CR_SELECT_FLASH_PARTITION_1     = 0xf,
};


// Internal Register Set Address

/**
 * @brief Internal Register Set Address (IRSA) decoding.
 */

enum IRSA {
    IRSA_DHR0   = 0x0,
    IRSA_DHR1   = 0x1,
    IRSA_DHR2   = 0x2,
    IRSA_DHR3   = 0x3,
    IRSA_PFAR0  = 0x4,
    IRSA_PFAR1  = 0x5,
    IRSA_PFAR2  = 0x6,
    IRSA_PFAR3  = 0x7,
    IRSA_CR     = 0x8,
    IRSA_IMR    = 0x9,
};


// Interface Mode Register

/**
 * @brief Interface Mode Register (IMR) decoding.
 */

enum IMR {
    IMR_4WIRE = 0x0,
    IMR_3WIRE = 0x1,
};


// Flash partition

/**
 * @brief Flash partition.
 */

enum FLASH_PARTITION {
    PARTITION_0,
    PARTITION_1
};


/**
 * @brief CPU ports.
 */

enum CPU_PORT {
    CPU_PORT_0 = 0x0,
    CPU_PORT_1 = 0x1,
    CPU_PORT_2 = 0x2,
    CPU_PORT_3 = 0x3,
    CPU_PORT_4 = 0x4,
    CPU_PORT_5 = 0x5,
    CPU_PORT_6 = 0x6,
    CPU_PORT_7 = 0x7,
    CPU_PORT_8 = 0x8,
    CPU_PORT_9 = 0x9,
    CPU_PORT_A = 0xa,
    CPU_PORT_B = 0xb,
    CPU_PORT_C = 0xc,
    CPU_PORT_D, MODULE_DATA_PORT = 0xd,
    CPU_PORT_E, MODULE_ADDRESS_PORT = 0xe,
    CPU_PORT_F, MODULE_CONTROL_PORT = 0xf,
};

/**
 * @brief Module register addresses.
 */

enum MODULE_REGISTER_ADDRESS {
    R_ADC_CONTROL   = 0x00,
    R_ADC_DATA_1    = 0x01,
    R_ADC_CONFIG_1A = 0x02,
    R_ADC_CONFIG_1B = 0x03,
    R_ADC_DATA_2    = 0x04,
    R_ADC_CONFIG_2A = 0x05,
    R_ADC_CONFIG_2B = 0x06,
    R_ADC_DATA_T    = 0x07,
    R_ADC_CONFIG_TA = 0x08,
    R_ADC_CONFIG_TB = 0x09,
    R_DOP1_DATA     = 0x10,
    R_DOP1_CONTROL  = 0x11,
    R_DOP1_CONFIG   = 0x12,
    R_DOP2_DATA     = 0x13,
    R_DOP2_CONTROL  = 0x14,
    R_DOP2_CONFIG   = 0x15,
    R_TMR_CONTROL   = 0x20,
    R_TMR_CONFIG    = 0x21,
    R_OPAMP_CONFIG  = 0x30,
    R_PO_CONTROL    = 0x31,
    R_OSC_CONTROL   = 0x32,
    R_GPIO1_CONTROL = 0x40,
    R_GPIO2_CONTROL = 0x41,
};


/**
 * @brief ADC_CONTROL register bits.
 */

enum ADC_CONTROL {
    CNVT_ADC_1       = 0x0004,
    CNVT_ADC_2       = 0x0002,
    CNVT_ADC_T       = 0x0001,
    CNVT_SE_VBG     = 0x0100,
    CNVT_SE_SM      = 0x0200,
    CNVT_SE_LG      = 0x0300,
    CNVT_SE_VDD     = 0x0400,
    CNVT_SE_VSS     = 0x0500,
    CNVT_SE_DACSM   = 0x0600,
    CNVT_SE_DACLG   = 0x0700,
    CNVT_SE_INP     = 0x0800,
    CNVT_SE_INM     = 0x0900,
};

// Programmable-Gain Amplifier

/**
 * @brief Programmable-Gain Amplifier (PGA) bits in the ADC_CONFIG_nA register.
 */

enum PGA {
    CONFIGA_PGA_00, CONFIGA_PGA_GAIN_0_99   = 0x0000,
    CONFIGA_PGA_01, CONFIGA_PGA_GAIN_7_7    = 0x0800,
    CONFIGA_PGA_02, CONFIGA_PGA_GAIN_15_5   = 0x1000,
    CONFIGA_PGA_03, CONFIGA_PGA_GAIN_23     = 0x1800,
    CONFIGA_PGA_04, CONFIGA_PGA_GAIN_31     = 0x2000,
    CONFIGA_PGA_05, CONFIGA_PGA_GAIN_39     = 0x2800,
    CONFIGA_PGA_06, CONFIGA_PGA_GAIN_46     = 0x3000,
    CONFIGA_PGA_07, CONFIGA_PGA_GAIN_54     = 0x3800,
    CONFIGA_PGA_08, CONFIGA_PGA_GAIN_65     = 0x4000,
    CONFIGA_PGA_0A, CONFIGA_PGA_GAIN_77     = 0x5000,
    CONFIGA_PGA_0C, CONFIGA_PGA_GAIN_92     = 0x6000,
    CONFIGA_PGA_0E, CONFIGA_PGA_GAIN_107    = 0x7000,
    CONFIGA_PGA_10, CONFIGA_PGA_GAIN_123    = 0x8000,
    CONFIGA_PGA_14, CONFIGA_PGA_GAIN_153    = 0xa000,
    CONFIGA_PGA_18, CONFIGA_PGA_GAIN_183    = 0xc000,
    CONFIGA_PGA_1C, CONFIGA_PGA_GAIN_214    = 0xe000,
    CONFIGA_PGA_1E, CONFIGA_PGA_GAIN_244    = 0xf000,
};

/**
 * @brief ADC clock bits in the ADC_CONFIG_nA register.
 */

enum ADC_CLK {
    CONFIGA_CLK0, CONFIGA_CLK_1MHz      = 0x0000,
    CONFIGA_CLK1, CONFIGA_CLK_500kHz	= 0x0100,
    CONFIGA_CLK2, CONFIGA_CLK_250kHz	= 0x0200,
    CONFIGA_CLK3, CONFIGA_CLK_125kHz	= 0x0300,
    CONFIGA_CLK4, CONFIGA_CLK_62_5kHz	= 0x0400,
    CONFIGA_CLK5, CONFIGA_CLK_31_25kHz	= 0x0500,
    CONFIGA_CLK6, CONFIGA_CLK_15_625kHz	= 0x0600,
    CONFIGA_CLK7, CONFIGA_CLK_7_8125kHz = 0x0700,
};

/**
 * @brief ADC resolution bits in the ADC_CONFIG_nA register.
 */

enum ADC_RES {
    CONFIGA_RES0, CONFIGA_RES_9BIT  = 0x0000,
    CONFIGA_RES1, CONFIGA_RES_10BIT = 0x0010,
    CONFIGA_RES2, CONFIGA_RES_12BIT = 0x0020,
    CONFIGA_RES3, CONFIGA_RES_13BIT = 0x0030,
    CONFIGA_RES4, CONFIGA_RES_14BIT = 0x0040,
    CONFIGA_RES5, CONFIGA_RES_15BIT = 0x0050,
    CONFIGA_RES6, CONFIGA_RES_16BIT = 0x0060,
};

/**
 * @brief ADC coarse offest bits in the ADC_CONFIG_nA register.
 */

enum ADC_COARSE_OFFSET {
    CONFIGA_CO7 = 0x0007,
    CONFIGA_CO6 = 0x0006,
    CONFIGA_CO5 = 0x0005,
    CONFIGA_CO4 = 0x0004,
    CONFIGA_CO3 = 0x0003,
    CONFIGA_CO2 = 0x0002,
    CONFIGA_CO1 = 0x0001,
    CONFIGA_CO0 = 0x0000,
    CONFIGA_CO8 = 0x0008,
    CONFIGA_CO9 = 0x0009,
    CONFIGA_COA = 0x000a,
    CONFIGA_COB = 0x000b,
    CONFIGA_COC = 0x000c,
    CONFIGA_COD = 0x000d,
    CONFIGA_COE = 0x000e,
    CONFIGA_COF = 0x000f,
};

/**
 * @brief ADC bias current bits in the ADC_CONFIG_nB register.
 */

enum ADC_BIAS_CURRENT {
    CONFIGB_BIAS0, CONFIGB_BIAS_1_8 = 0x0000,
    CONFIGB_BIAS1, CONFIGB_BIAS_2_8 = 0x0010,
    CONFIGB_BIAS2, CONFIGB_BIAS_3_8 = 0x0020,
    CONFIGB_BIAS3, CONFIGB_BIAS_4_8 = 0x0030,
    CONFIGB_BIAS4, CONFIGB_BIAS_5_8 = 0x0040,
    CONFIGB_BIAS5, CONFIGB_BIAS_6_8 = 0x0050,
    CONFIGB_BIAS6, CONFIGB_BIAS_7_8 = 0x0060,
    CONFIGB_BIAS7, CONFIGB_BIAS_8_8 = 0x0070,
};

/**
 * @brief ADC reference source bits in the ADC_CONFIG_nB register.
 */

enum ADC_REF_SOURCE {
    CONFIGB_REF0, CONFIGB_REF_VDD   = 0x0000,
    CONFIGB_REF1, CONFIGB_REF_2VREF = 0x0001,
    CONFIGB_REF2, CONFIGB_REF_4VBG  = 0x0002,
};


/**
 * @brief DOPn_CONTROL register bits.
 */

enum DOP_CONTROL {
    DOP_CONTROL_ENPWM = 0x0010,
    DOP_CONTROL_ENDAC = 0x0001,
};

/**
 * @brief DOPn_CONFIG register bits.
 */

enum DOP_CONFIG {
    DOP_CONFIG_PWMLG = 0x0100,
    DOP_CONFIG_DACLG = 0x0010,
    DOP_CONFIG_REF   = 0x0001,
};


/**
 * @brief OPAMP_CONFIG register bits.
 */

enum OPAMP_CONFIG {
    OPAMP_BUF1  = 0x0001,
    OPAMP_BUF2  = 0x0002,
};


/**
 * @brief GPIOn_CONTROL register bits.
 */

enum GPIO_CONTROL {
    GPIO_OUT_HIGH   = 0x0030,
    GPIO_OUT_LOW    = 0x0010,
    GPIO_INPUT	    = 0x0000,
    GPIO_RISE_EDGE  = 0x0005,
    GPIO_FALL_EDGE  = 0x0007,
    GPIO_EDGE       = 0x0001,
    GPIO_INV        = 0x0002,
    GPIO_CLR        = 0x0004,
    GPIO_IN         = 0x0008,
    GPIO_EN         = 0x0010,
    GPIO_OUT        = 0x0020,
};


/**
 * @brief TMR_CONTROL register bits.
 */

enum TMR_CONTROL {
    TMR_CONTROL_TMDN    = 0x8000,
    TMR_CONTROL_TMEN    = 0x4000,
    TMR_CONTROL_ENAHALT = 0x0001,
};

/**
 * @brief TMR_CONFIG register bits.
 */

enum TMR_CONFIG {
    TMR_CONFIG_PS_1   	= 0x0000,
    TMR_CONFIG_PS_2   	= 0x2000,
    TMR_CONFIG_PS_4   	= 0x4000,
    TMR_CONFIG_PS_8   	= 0x6000,
    TMR_CONFIG_PS_16  	= 0x8000,
    TMR_CONFIG_PS_32  	= 0xa000,
    TMR_CONFIG_PS_64  	= 0xc000,
    TMR_CONFIG_PS_128  = 0xe000,
    TMR_CONFIG_PS_3   	= 0x1000,
    TMR_CONFIG_PS_6   	= 0x3000,
    TMR_CONFIG_PS_12  	= 0x5000,
    TMR_CONFIG_PS_24  	= 0x7000,
    TMR_CONFIG_PS_48  	= 0x9000,
    TMR_CONFIG_PS_96  	= 0xb000,
    TMR_CONFIG_PS_192 	= 0xd000,
    TMR_CONFIG_PS_384 	= 0xf000,
    TMR_CONFIG_500ns	= 0x0000,
    TMR_CONFIG_1us  	= 2 - 1,
    TMR_CONFIG_2us  	= 4 - 1,
    TMR_CONFIG_5us  	= 10 - 1,
    TMR_CONFIG_10us  	= 20 - 1,
    TMR_CONFIG_20us  	= 40 - 1,
    TMR_CONFIG_50us  	= 100 - 1,
    TMR_CONFIG_100us  	= 200 - 1,
    TMR_CONFIG_200us  	= 400 - 1,
    TMR_CONFIG_500us  	= 1000 - 1,
    TMR_CONFIG_1ms  	= 2000 - 1,
    TMR_CONFIG_2ms  	= 4000 - 1,
    TMR_CONFIG_5ms  	= TMR_CONFIG_PS_3 | 3333, // 10000 - 1
    TMR_CONFIG_10ms  	= TMR_CONFIG_PS_32 | 625, // 20000
    TMR_CONFIG_20ms  	= TMR_CONFIG_PS_64 | 625, // 40000
    TMR_CONFIG_50ms  	= TMR_CONFIG_PS_32 | 3125, // 100000
    TMR_CONFIG_100ms	= TMR_CONFIG_PS_64 | 3125, // 200000
    TMR_CONFIG_200ms	= TMR_CONFIG_PS_128 | 3125, // 400000
    TMR_CONFIG_500ms	= TMR_CONFIG_PS_384 | 2604,
    TMR_CONFIG_786ms	= TMR_CONFIG_PS_384 | 4095,
};


/**
 * @brief PO_CONTROL register bits.
 */

enum PO_CONTROL {
    PWR_ADC     = 0x0100,
    PWR_DAC2	= 0x0020,
    PWR_DAC1	= 0x0010,
    PWR_OP2     = 0x0002,
    PWR_OP1     = 0x0001,
    PWR_ALL_ON	= PWR_ADC | PWR_DAC2 | PWR_DAC1 | PWR_OP2 | PWR_OP1,
    PWR_ALL_OFF  = 0x0000,
};


/**
 * @brief OSC_CONTROL register bits.
 */

enum OSC_CONTROL {
    OSC_TRIM_15     = 0x0f00,
    OSC_TRIM_14     = 0x0e00,
    OSC_TRIM_13     = 0x0d00,
    OSC_TRIM_12     = 0x0c00,
    OSC_TRIM_11     = 0x0b00,
    OSC_TRIM_10     = 0x0a00,
    OSC_TRIM_9      = 0x0900,
    OSC_TRIM_8      = 0x0800,
    OSC_TRIM_7      = 0x0700,
    OSC_TRIM_6      = 0x0600,
    OSC_TRIM_5      = 0x0500,
    OSC_TRIM_4      = 0x0400,
    OSC_TRIM_3      = 0x0300,
    OSC_TRIM_2      = 0x0200,
    OSC_TRIM_1      = 0x0100,
    OSC_TRIM_0      = 0x0000,
    OSC_TRIM_m1     = 0x1000,
    OSC_TRIM_m2     = 0x1100,
    OSC_TRIM_m3     = 0x1200,
    OSC_TRIM_m4     = 0x1300,
    OSC_TRIM_m5     = 0x1400,
    OSC_TRIM_m6     = 0x1500,
    OSC_TRIM_m7     = 0x1600,
    OSC_TRIM_m8     = 0x1700,
    OSC_TRIM_m9     = 0x1800,
    OSC_TRIM_m10    = 0x1900,
    OSC_TRIM_m11    = 0x1a00,
    OSC_TRIM_m12    = 0x1b00,
    OSC_TRIM_m13    = 0x1c00,
    OSC_TRIM_m14    = 0x1d00,
    OSC_TRIM_m15    = 0x1e00,
    OSC_TRIM_m16    = 0x1f00,
    OSC_ENCKOUT	    = 0x0001,
};


}  // namespace

#endif // MAX1464_ENUMS_H
