/**@file temperature_sensor.c
 * @brief MB851 temperature sensor APIS 
 *
 *
 * <!--(C) COPYRIGHT 2010 STMicroelectronics. All rights reserved.        -->
 */
#include PLATFORM_HEADER
#include BOARD_HEADER
#include "hal/hal.h"
#include "hal/error.h"
#include "hal/micro/temperature_sensor.h"
#include "hal/micro/adc.h"

void halTempSensorInit(void)
{
   /* Configure temperature sensor GPIO */
   halGpioConfig(TEMPERATURE_SENSOR_GPIO,GPIOCFG_ANALOG);
   /* Init ADC driver */
   halInternalInitAdc();
  
   /*
    NOTE: 
    The ADC extended range is inaccurate due to the high voltage mode bug of the general purpose ADC 
    (see STM32W108 errata). As consequence, it is not reccomended to use this ADC driver for getting
    the temperature values. 
    */
#ifdef ENABLE_ADC_EXTENDED_RANGE_BROKEN
    halAdcSetRange(TRUE);
#endif /* ENABLE_ADC_EXTENDED_RANGE_BROKEN */
}/* end halTempSensorInit() */

int32u halTempSensorGetValue(void)
{
   static int16u ADCvalue;
   static int16s volts;

    /*
     NOTE: 
     The ADC extended range is inaccurate due to the high voltage mode bug of the general purpose ADC 
     (see STM32W108 errata). As consequence, it is not reccomended to use this ADC driver for getting
     the temperature values. 
    */
    halStartAdcConversion(ADC_USER_APP, ADC_REF_INT, ADC_SOURCE(halGetADCChannelFromGPIO(TEMPERATURE_SENSOR_GPIO),ADC_MUX_VREF2), ADC_CONVERSION_TIME_US_4096);
  
    halReadAdcBlocking(ADC_USER_APP, &ADCvalue); // This blocks for a while, about 4ms.
  
    // 100 uVolts
    volts = halConvertValueToVolts(ADCvalue);
  
    return ((18641 - (int32s)volts)*100)/1171;  
}/* halTempSensorGetValue() */

