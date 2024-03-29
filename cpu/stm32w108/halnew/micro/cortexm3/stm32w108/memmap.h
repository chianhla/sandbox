/** @file hal/micro/cortexm3/stm32w108/memmap.h
 * @brief Definition of STM32W108 chip specific memory map information
 *
 * <!--(C) COPYRIGHT 2010 STMicroelectronics. All rights reserved.        -->
 */

#ifndef __MEMMAP_H__
  #error This header should not be included directly, use hal/micro/cortexm3/memmap.h
#endif

#ifndef __STM32W108_MEMMAP_H__
#define __STM32W108_MEMMAP_H__

#define RAM_BOTTOM          (0x20000000u)

#define RAM_SIZE_B          (0x2000)
#define RAM_SIZE_W          (RAM_SIZE_B/4)
#define RAM_TOP             (RAM_BOTTOM+RAM_SIZE_B-1)





#define MFB_BOTTOM          (0x08000000u)
#define MFB_SIZE_B          (0x20000)          
#define MFB_SIZE_W          (MFB_SIZE_B/4)
#define MFB_TOP             (MFB_BOTTOM+MFB_SIZE_B-1)    
#define MFB_PAGE_SIZE_B     (1024)
#define MFB_PAGE_SIZE_W     (MFB_PAGE_SIZE_B/4)
#define MFB_PAGE_MASK_B     (0xFFFFFC00)
#define MFB_REGION_SIZE     (4) // One write protection region is 4 pages.
#define MFB_ADDR_MASK       (0x0003FFFFu)



#define CIB_BOTTOM          (0x08040800u)
#define CIB_SIZE_B          (0x200)
#define CIB_SIZE_W          (CIB_SIZE_B/4)
#define CIB_TOP             (CIB_BOTTOM+CIB_SIZE_B-1)
#define CIB_PAGE_SIZE_B     (512)
#define CIB_PAGE_SIZE_W     (CIB_PAGE_SIZE_B/4)
#define CIB_OB_BOTTOM       (CIB_BOTTOM+0x00)   //bottom address of CIB option bytes
#define CIB_OB_TOP          (CIB_BOTTOM+0x0F)   //top address of CIB option bytes



#define FIB_BOTTOM          (0x08040000u)
#define FIB_SIZE_B          (0x800)
#define FIB_SIZE_W          (FIB_SIZE_B/4)
#define FIB_TOP             (FIB_BOTTOM+FIB_SIZE_B-1)
#define FIB_PAGE_SIZE_B     (1024)
#define FIB_PAGE_SIZE_W     (FIB_PAGE_SIZE_B/4)






#define FPEC_KEY1           0x45670123          //magic key defined in hardware
#define FPEC_KEY2           0xCDEF89AB          //magic key defined in hardware

// Constant for MPU initialization
#define MPU_FLASH_REGION_SIZE 0x12 // 512K including main user flash and FIB
#if MFB_SIZE_B == 0x40000
#define MPU_FLASH_SUBREGION_PROTECTION 0xE0
#elif MFB_SIZE_B == 0x20000
#define MPU_FLASH_SUBREGION_PROTECTION 0xEC
#endif
#define MPU_RAM_REGION_SIZE 0x0D // 16K RAM size max
#if RAM_SIZE_B == 0x4000
#define MPU_RAM_SUBREGION_PROTECTION 0x00
#elif RAM_SIZE_B == 0x2000
#define MPU_RAM_SUBREGION_PROTECTION 0xF0
#endif


//Translation between page number and simee (word based) address
#define SIMEE_ADDR_TO_PAGE(x)   ((int8u)(((int16u)(x)) / (MFB_PAGE_SIZE_B/2)))
#define PAGE_TO_SIMEE_ADDR(x)   (((int16u)(x)) * (MFB_PAGE_SIZE_B/2))

//Translation between page number and simee (word based) address
//#define SIMEE_ADDR_TO_PAGE(x)   ((int8u)(((int16u)(x)) >> 9))
//#define PAGE_TO_SIMEE_ADDR(x)   (((int16u)(x)) << 9)

//Translation between page number and code addresses, used by bootloaders
#define PROG_ADDR_TO_PAGE(x)    ((int8u)((((int32u)(x))&MFB_PAGE_MASK_B) / MFB_PAGE_SIZE_B))
#define PAGE_TO_PROG_ADDR(x)    ((((int32u)(x)) * MFB_PAGE_SIZE_B)|MFB_BOTTOM)

//Translation between page number and code addresses, used by bootloaders
//#define PROG_ADDR_TO_PAGE(x)    ((int8u)((((int32u)(x))&MFB_ADDR_MASK) >> 10))
//#define PAGE_TO_PROG_ADDR(x)    ((((int32u)(x)) << 10)|MFB_BOTTOM)








#endif //__STM32W108_MEMMAP_H__
