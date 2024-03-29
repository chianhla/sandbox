/** @file hal/micro/mems_regs.h
 *  @brief stm32w108 mems registers 
 *  
 * <!--(C) COPYRIGHT 2010 STMicroelectronics. All rights reserved.        -->
 */

#ifndef _MEMS_REGS_H_
#define _MEMS_REGS_H_

//---Size of MEMs data---
#define MEMS_DATA_SIZE 6

//---address of slave I want to communicate with---
#define kLIS3L02DQ_SLAVE_ADDR    0x38

//-----------------------------------------------------------------------------
//---accelerometer register addresses---
#define OFFSET_X         0x16
#define OFFSET_Y         0x17
#define OFFSET_Z         0x18
#define GAIN_X           0x19
#define GAIN_Y           0x1A
#define GAIN_Z           0x1B
#define CTRL_REG1        0x20
#define CTRL_REG2        0x21
#define STATUS_REG       0x27
#define OUTX_L           0x28
#define OUTX_H           0x29
#define OUTY_L           0x2A
#define OUTY_H           0x2B
#define OUTZ_L           0x2C
#define OUTZ_H           0x2D
#define FF_WU_CFG        0x30
#define FF_WU_SRC        0x31
#define FF_WU_ACK        0x32
#define FF_WU_THS_L      0x34
#define FF_WU_THS_H      0x35
#define FF_WU_DURATION   0x36
#define DD_CFG           0x38
#define DD_SRC           0x39
#define DD_ACK           0x3A
#define DD_THSI_L        0x3C
#define DD_THSI_H        0x3D
#define DD_THSE_L        0x3E
#define DD_THSE_H        0x3F

// Communication control settings
// I2C
#define REPETIR          0x80
// SPI
#define MEMS_SPI_WRITE   0x00
#define MEMS_SPI_READ    0x80
#define MEMS_SPI_MULTIPLE_BYTES 0x40

//-----------------------------------------------------------------------------
//---Settings for CTRL_REG1---

// Power Down Control (PD)
#define LIS_PD_OFF 0x00
#define LIS_PD_ON  0x40

// Decimation Factor Control (DF)
#define LIS_DF_BY128 0x00
#define LIS_DF_BY64  0x10
#define LIS_DF_BY32  0x20
#define LIS_DF_BY8   0x30

// Self Test
#define LIS_ST_NORMAL 0x00
#define LIS_ST_TEST   0x08

// Enable Axis
#define LIS_EA_ALL    0x07

//-----------------------------------------------------------------------------
//---Settings for CTRL_REG2---

// Full Scale (FS)
#define LIS_FS_2G 0x00
#define LIS_FS_6G 0x80

// Block Data Update (BDU)
#define LIS_BDU_CONTINUOUS 0x00
#define LIS_BDU_WAIT       0x40

// Big/Little Endian Selection (BLE)
#define LIS_BLE_LE 0x00
#define LIS_BLE_BE 0x20

// Data Alignment Selection DAS
#define LIS_DAS_12BIT 0x00
#define LIS_DAS_16BIT 0x01

// Interrupt Enable
#define LIS_INTR_DISABLE 0x00
#define LIS_INTR_ENABLE  0x08

// Data Ready Enable
#define LIS_DRDY_DISABLE 0x00
#define LIS_DRDY_ENABLE  0x04

//-----------------------------------------------------------------------------

#define LIS_BLE_XX LIS_BLE_BE

//-----------------------------------------------------------------------------
//---Settings for STATUS_REG---

// X, Y and Z axis data overrun.
#define STATUS_REG_ZXYOR     (1 << 7)
// Z axis data overrun
#define STATUS_REG_ZOR       (1 << 6)
// Y axis data overrun
#define STATUS_REG_YOR       (1 << 5)
// X axis data overrun
#define STATUS_REG_XOR       (1 << 4)
// X, Y and Z axis new data available
#define STATUS_REG_ZYXDA     (1 << 3)
// Z axis new data available.
#define STATUS_REG_ZDA       (1 << 2)
// Y axis new data available.
#define STATUS_REG_YDA       (1 << 1)
// X axis new data available.
#define STATUS_REG_XDA       (1 << 0)


/* Private Functions Prototypes ----------------------------------------------*/

//*********************i2c_read_reg***********************//
//----------Reads a register on the I2C target------------//
//------slave addr is the is the I2C target device--------//
//-reg_addr is the address of the register to be written--//
//-pBuffer is the storage destination for the read data---//
//-NoOfBytes is the amount of data to read----------------//
int8u i2c_read_reg (int8u slave_addr, int8u reg_addr, int8u *pBuffer, int8u NoOfBytes);

//*********************i2c_write_reg**********************//
//----------Writes a register on the I2C target-----------//
//------slave addr is the is the I2C target device--------//
//-reg_addr is the address of the register to be written--//
//-reg_value is the value of the register to be written---//
int8u i2c_write_reg (int8u slave_addr, int8u reg_addr, int8u reg_value);

#endif /* _MEMS_REGS_H_ */

