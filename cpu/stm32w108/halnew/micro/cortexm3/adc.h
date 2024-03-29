/** @file /hal/micro/cortexm3/adc.h
 * @brief Header for STM32W A/D converter.
 *
 * See @ref adc for documentation.
 *
 * <!--(C) COPYRIGHT 2010 STMicroelectronics. All rights reserved.        -->
 */


/** @addtogroup adc
 * Sample A/D converter driver.
 *
 * @note EM35x ADC driver support is preliminary and essentailly untested -
 * please do not attempt to use this ADC driver on this platform.  It may be 
 * changed in a future release
 *
 *@{
 */


#ifndef __STM32W108_ADC_H__
#define __STM32W108_ADC_H__

#ifndef DOXYGEN_SHOULD_SKIP_THIS
  #ifndef __ADC_H__
    #error do not include this file directly - include micro/adc.h
  #endif
#endif


/** @brief ADCReferenceType Enumeration.
 *         Note: STM32W108 only supports one reference type: Internal
 */
enum {
  /** Internal reference. */
  ADC_REF_INT  = 42
};


/** @brief ADCRateType enumeration.  
 *         These rates are specified in the number of clock cycles
 *         That a conversion takes.  The actual time taken will depend on the
 *         selected ADC clock rate.  (Default is 6MHz)
 */
enum {
  /** Rate 32 cycles, 5 effective bits in ADC_DATA[15:11] */
  ADC_SAMPLE_CLOCKS_32   = 0x0,
  /** Rate 64 cycles, 6 effective bits in ADC_DATA[15:10] */
  ADC_SAMPLE_CLOCKS_64   = 0x1,
  /** Rate 128 cycles, 7 effective bits in ADC_DATA[15:9] */
  ADC_SAMPLE_CLOCKS_128  = 0x2,
  /** Rate 256 cycles, 8 effective bits in ADC_DATA[15:8] */
  ADC_SAMPLE_CLOCKS_256  = 0x3,
  /** Rate 512 cycles, 9 effective bits in ADC_DATA[15:7] */
  ADC_SAMPLE_CLOCKS_512  = 0x4,
  /** Rate 1024 cycles, 10 effective bits in ADC_DATA[15:6] */
  ADC_SAMPLE_CLOCKS_1024 = 0x5,
  /** Rate 2048 cycles, 11 effective bits in ADC_DATA[15:5] */
  ADC_SAMPLE_CLOCKS_2048 = 0x6,
  /** Rate 4096 cycles, 12 effective bits in ADC_DATA[15:4] */
  ADC_SAMPLE_CLOCKS_4096 = 0x7,
};


/** @brief ADC rates for compatibility with EM2xx applications.  For EM35x only
 *  applications, the ADC_SAMPLE_CLOCKS_nnn definitions should be used instead
 */
enum
{
  /** Rate 32 us, 5 effective bits in ADC_DATA[15:11] */
  ADC_CONVERSION_TIME_US_32   = 0x0,
  /** Rate 64 us, 6 effective bits in ADC_DATA[15:10] */
  ADC_CONVERSION_TIME_US_64   = 0x1,
  /** Rate 128 us, 7 effective bits in ADC_DATA[15:9] */
  ADC_CONVERSION_TIME_US_128  = 0x2,
  /** Rate 256 us, 8 effective bits in ADC_DATA[15:8] */
  ADC_CONVERSION_TIME_US_256  = 0x3,
  /** Rate 512 us, 9 effective bits in ADC_DATA[15:7] */
  ADC_CONVERSION_TIME_US_512  = 0x4,
  /** Rate 1024 us, 10 effective bits in ADC_DATA[15:6] */
  ADC_CONVERSION_TIME_US_1024 = 0x5,
  /** Rate 2048 us, 11 effective bits in ADC_DATA[15:5] */
  ADC_CONVERSION_TIME_US_2048 = 0x6,
  /** Rate 4096 us, 12 effective bits in ADC_DATA[15:4] */
  ADC_CONVERSION_TIME_US_4096 = 0x7,
};


#if defined(EMBER_TEST) && !defined(ADC_MUXN_BITS)
  #define ADC_MUXN_BITS (4)
#endif
  
  /** Channel 0 : ADC0 on PB5 */
#define ADC_MUX_ADC0    0x0
  /** Channel 1 : ADC0 on PB6 */
#define ADC_MUX_ADC1    0x1
  /** Channel 2 : ADC0 on PB7 */
#define ADC_MUX_ADC2    0x2
  /** Channel 3 : ADC0 on PC1 */
#define ADC_MUX_ADC3    0x3
  /** Channel 4 : ADC0 on PA4 */
#define ADC_MUX_ADC4    0x4
  /** Channel 5 : ADC0 on PA5 */
#define ADC_MUX_ADC5    0x5
  /** Channel 8 : VSS (0V) - not for high voltage range */
#define ADC_MUX_GND     0x8
  /** Channel 9 : VREF/2 (0.6V) */
#define ADC_MUX_VREF2   0x9
  /** Channel A : VREF (1.2V)*/
#define ADC_MUX_VREF    0xA
  /** Channel B : Regulator/2 (0.9V) - not for high voltage range */
#define ADC_MUX_VREG2   0xB

// ADC_SOURCE_<pos>_<neg> selects <pos> as the positive input and <neg> as  
// the negative input.
enum
{
  ADC_SOURCE_ADC0_VREF2  = ((ADC_MUX_ADC0  <<ADC_MUXN_BITS) + ADC_MUX_VREF2),
  ADC_SOURCE_ADC0_GND    = ((ADC_MUX_ADC0  <<ADC_MUXN_BITS) + ADC_MUX_GND),

  ADC_SOURCE_ADC1_VREF2  = ((ADC_MUX_ADC1  <<ADC_MUXN_BITS) + ADC_MUX_VREF2),
  ADC_SOURCE_ADC1_GND    = ((ADC_MUX_ADC1  <<ADC_MUXN_BITS) + ADC_MUX_GND),

  ADC_SOURCE_ADC2_VREF2  = ((ADC_MUX_ADC2  <<ADC_MUXN_BITS) + ADC_MUX_VREF2),
  ADC_SOURCE_ADC2_GND    = ((ADC_MUX_ADC2  <<ADC_MUXN_BITS) + ADC_MUX_GND),

  ADC_SOURCE_ADC3_VREF2  = ((ADC_MUX_ADC3  <<ADC_MUXN_BITS) + ADC_MUX_VREF2),
  ADC_SOURCE_ADC3_GND    = ((ADC_MUX_ADC3  <<ADC_MUXN_BITS) + ADC_MUX_GND),

  ADC_SOURCE_ADC4_VREF2  = ((ADC_MUX_ADC4  <<ADC_MUXN_BITS) + ADC_MUX_GND),

  ADC_SOURCE_ADC5_VREF2  = ((ADC_MUX_ADC5  <<ADC_MUXN_BITS) + ADC_MUX_GND),

  ADC_SOURCE_ADC1_ADC0   = ((ADC_MUX_ADC1  <<ADC_MUXN_BITS) + ADC_MUX_ADC0),
  ADC_SOURCE_ADC0_ADC1   = ((ADC_MUX_ADC1  <<ADC_MUXN_BITS) + ADC_MUX_ADC0),

  ADC_SOURCE_ADC3_ADC2   = ((ADC_MUX_ADC3  <<ADC_MUXN_BITS) + ADC_MUX_ADC2),
  ADC_SOURCE_ADC2_ADC3   = ((ADC_MUX_ADC3  <<ADC_MUXN_BITS) + ADC_MUX_ADC2),

  ADC_SOURCE_ADC5_ADC4   = ((ADC_MUX_ADC5  <<ADC_MUXN_BITS) + ADC_MUX_ADC4),

  ADC_SOURCE_GND_VREF2   = ((ADC_MUX_GND   <<ADC_MUXN_BITS) + ADC_MUX_VREF2),
  ADC_SOURCE_VGND        = ((ADC_MUX_GND   <<ADC_MUXN_BITS) + ADC_MUX_GND),

  ADC_SOURCE_VREF_VREF2  = ((ADC_MUX_VREF  <<ADC_MUXN_BITS) + ADC_MUX_VREF2),
  ADC_SOURCE_VREF        = ((ADC_MUX_VREF  <<ADC_MUXN_BITS) + ADC_MUX_GND),

/* Modified the original ADC driver for enabling the ADC extended range mode required for 
   supporting the STLM20 temperature sensor.
   NOTE: 
   The ADC extended range is inaccurate due to the high voltage mode bug of the general purpose ADC 
   (see STM32W108 errata). As consequence, it is not reccomended to use this ADC driver for getting
   the temperature values 
*/
#ifdef ENABLE_ADC_EXTENDED_RANGE_BROKEN
  ADC_SOURCE_VREF2_VREF2  = ((ADC_MUX_VREF2  <<ADC_MUXN_BITS) + ADC_MUX_VREF2),
  ADC_SOURCE_VREF2        = ((ADC_MUX_VREF2  <<ADC_MUXN_BITS) + ADC_MUX_GND),
#endif /* ENABLE_ADC_EXTENDED_RANGE_BROKEN */

  ADC_SOURCE_VREG2_VREF2 = ((ADC_MUX_VREG2 <<ADC_MUXN_BITS) + ADC_MUX_VREF2),
  ADC_SOURCE_VDD_GND     = ((ADC_MUX_VREG2 <<ADC_MUXN_BITS) + ADC_MUX_GND)
};

/** @brief Macro that returns the ADCChannelType, from a given couple of sources
 * (positive and negative). To be used with halStartAdcConversion().
 */
#define ADC_SOURCE(P,N)   (( P << ADC_MUXN_BITS ) + N)


/** @brief Returns the ADC channel from a given GPIO. Its value can can be used
 * inside the ADC_SOURCE(P,N) macro to retrieve the input pair for
 * halStartAdcConversion().
 *
 * @param io  The GPIO pin (it can be specified with the convenience macros
 *            PORTA_PIN(), PORTB_PIN(), PORTC_PIN() )
 * 
 * @return The ADC_MUX value connected to the given GPIO.
 */
int8u halGetADCChannelFromGPIO(int32u io);

void halAdcSetClock(boolean slow);
boolean halAdcGetClock(void);
void halAdcSetRange(boolean high);
boolean halAdcGetRange(void);


/** @brief  Measures VDD_PADS in millivolts at the specified sample rate
 * Due to the conversions performed, this function takes slightly under 250us
 * with a variation across successive conversions approximately +/-20mv of
 * the average conversion.
 *
 * @return A measurement of VDD_PADS in millivolts.
 */
int16u halMeasureVdd(ADCRateType rate);


/** @} // END addtogroup
 */


#endif //__STM32W108_ADC_H__
