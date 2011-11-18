/** @file hal/micro/cortexm3/micro-common.h
 * @brief Utility and convenience functions for STM32W108 microcontroller,
 *        common to both the full and minimal hal.
 * See @ref micro for documentation.
 *
 * <!--(C) COPYRIGHT 2010 STMicroelectronics. All rights reserved.        -->
 */

/** @addtogroup micro
 * See also hal/micro/cortexm3/micro.h for source code.
 *@{
 */

#ifndef __STM32W108XX_MICRO_COMMON_H__
#define __STM32W108XX_MICRO_COMMON_H__

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#ifndef __STSTATUS_TYPE__
#define __STSTATUS_TYPE__
  //This is necessary here because halSleepForQsWithOptions returns an
  //StStatus and not adding this typedef to this file breaks a
  //whole lot of builds.
  typedef int8u StStatus;
#endif //__STSTATUS_TYPE__
#endif // DOXYGEN_SHOULD_SKIP_THIS

#define PORTA (0 << 3)
#define PORTB (1 << 3)
#define PORTC (2 << 3)

/**
 * @brief Some registers and variables require identifying GPIO by
 * a single number instead of the port and pin.  This macro converts
 * Port A pins into a single number.
 */
#define PORTA_PIN(y) (PORTA|y)
/**
 * @brief Some registers and variables require identifying GPIO by
 * a single number instead of the port and pin.  This macro converts
 * Port B pins into a single number.
 */
#define PORTB_PIN(y) (PORTB|y)
/**
 * @brief Some registers and variables require identifying GPIO by
 * a single number instead of the port and pin.  This macro converts
 * Port C pins into a single number.
 */
#define PORTC_PIN(y) (PORTC|y)

/**
 * @brief Some registers and variables require identifying GPIO by
 * a single number instead of the port and pin.  This macro converts
 * Port C pins into a single number.
 */
#define PORTx_PIN(x, y) (x|y)

/**
 * @brief Resets the watchdog timer.  This function is pointed
 * to by the macro ::halResetWatchdog(). 
 * @warning Be very careful when using this as you can easily get into an 
 * infinite loop.
 */
void halInternalResetWatchDog( void );


/**
 * @brief Configure an IO pin's operating mode
 *
 * @param io  The io pin to use, can be specified with the convenience macros
 *            PORTA_PIN(), PORTB_PIN(), PORTC_PIN()
 * @param config   The configuration mode to use.
 *
 */
void halGpioConfig(int32u io, int32u config);

/**
 * @brief Set/Clear single GPIO bit
 *
 * @param io  The io pin to use, can be specified with the convenience macros
 *            PORTA_PIN(), PORTB_PIN(), PORTC_PIN()
 * @param value   A flag indicating whether to set or clear the io.
 *
 */
void halGpioSet(int32u io, boolean value);


/**
 * @brief Calibrates the internal SlowRC to generate a 1024 Hz (1kHz) clock.
 */
void halInternalCalibrateSlowRc( void );

/**
 * @brief Calibrates the internal FastRC to generate a 12MHz clock.
 */
void halInternalCalibrateFastRc(void);


/**
 * @brief Sets the trim values for the 1.8V and 1.2V regulators based upon
 * manufacturing configuration.
 *
 * @param boostMode  Alter the regulator trim based upon the state
 * of boost mode.  TRUE if boost mode is active, FALSE otherwise.
 */
void halInternalSetRegTrim(boolean boostMode);

/** @brief Determine VREG_OUT in the current mode (normal or boost).
 *
 * @return VREG_OUT in millivolts, depending on normal or boost mode
 */
int16u halInternalGetVreg(void);

/** @brief Takes a slow ADC measurement of VDD_PADS in millivolts.  Due to
 * the conversions performed, this function takes slightly under 3.2ms with a
 * variation across successive conversions approximately +/-2mv of the average
 * conversion.
 *
 * @return A slow measurement of VDD_PADS in millivolts.
 */
int16u stMeasureVddSlow(void);


/** @brief Takes a fast ADC measurement of VDD_PADS in millivolts.
 * Due to the conversions performed, this function takes slightly under 150us
 * with a variation across successive conversions approximately +/-20mv of
 * the average conversion.
 *
 * @return A fast measurement of VDD_PADS in millivolts.
 */
int16u stMeasureVddFast(void);


/**
 * @brief Calibrates the GPIO pads.  This function is called from within
 * the stack and HAL at appropriate times.
 */
void halCommonCalibratePads(void);


/**
 * @brief This is the core function for enabling the XTAL, biasing
 * the XTAL, checking the XTAL biasing, switching to the XTAL,
 * configuring FCLK, and configuring flash access settings.  The ultimate
 * result of calling this function until it returns TRUE is the chip is
 * operating from the 24MHz XTAL, the XTAL is biased for lowest current
 * consumption, the CPU's FCLK is being sourced from SYSCLK, and the flash
 * is configured for optimal current consumption.
 *
 * The basic principle of this function is that it takes time for the
 * XTAL to stabilize whenever it is enabled and/or the biasing is change;
 * about 1.5ms every time the bias is changed.  This function will handle
 * the XTAL configuration, set an interrupt event to indicate when the
 * appropriate delay has elapsed, and return immediately.  This interrupt
 * event should not be monitored directly by any code other than the clock
 * module itself.  The state of the XTAL is learned by the return code
 * of this function.  As long as this function returns FALSE, the XTAL
 * is unstable.  Calling code can perform other actions until the XTAL
 * is stable.
 *
 * The suggested use of the four XTAL API functions is as follows:
 *  - halCommonStartXtal() is called once as soon as possible to start
 *    the XTAL.  Other actions may be performed while waiting for the XTAL
 *    to stabilize.
 *  - halCommonTryToSwitchToXtal() is called repeatedly to drive 
 *    the biasing and switch process.  Other actions that do not require
 *    a stable XTAL may be performed until this function returns TRUE.
 *  - halCommonSwitchToXtal() is called just once when a stable XTAL is
 *    required before moving on.  This function will block in the idle
 *    sleep state until the switch procedure has completed.
 *  - halCommonCheckXtalBiasTrim() is called periodically, after a switch
 *    has occurred, to check that the XTAL biasing is optimal and
 *    adjust if needed.
 *
 * halCommonTryToSwitchToXtal() function will return immediately.  This
 * function drives the switch process.  This function can be called
 * any number of times and at anytime.
 *
 * @return
 *   TRUE: The chip has switched to and is now using the XTAL.  No further
 *         bias events are in process.
 *   FALSE: The XTAL is <b>unstable<b>.  The chip has not modified it's
 *          XTAL selection; it remains on the same clock source (OSCHF
 *          or XTAL).  There is a bias event in process.
 */
boolean halCommonTryToSwitchToXtal(void);

void halInternalPowerUpKickXtal(void);
void halInternalInitMgmtIsrLo(void);
void halInternalBlockUntilXtal(void);
void halCommonBlockUntilXtal(void);

enum {
  WAKEUP_XTAL_STATE_START          = 0,
  WAKEUP_XTAL_STATE_BEFORE_LO_EN   = 1,
  WAKEUP_XTAL_STATE_LO_EN          = 2,
  WAKEUP_XTAL_STATE_READY_SWITCH   = 3,
  WAKEUP_XTAL_STATE_WAITING_FINAL  = 4,
  WAKEUP_XTAL_STATE_FINAL          = 5,
};
typedef int8u WakeupXtalState;

extern volatile WakeupXtalState wakeupXtalState;

/**
 * @brief This function is intended to be called periodically, from the
 * HAL and application, to check the XTAL bias trim is within
 * appropriate levels and adjust if not.  It will return immediately.
 * This function can be called any number of times and at anytime.
 */
#ifdef DOXYGEN_SHOULD_SKIP_THIS
void halCommonCheckXtalBiasTrim(void);
#else //DOXYGEN_SHOULD_SKIP_THIS
//Simply redirect to the primary switch function, which handles all XTAL
//switching and biasing activities.  We don't care about the return code.
//TRUE is ideal but we could get FALSE (even if on the XTAL) because there
//is a biasing event in process and the XTAL is unstable.
#define halCommonCheckXtalBiasTrim() halCommonTryToSwitchToXtal()
#endif //DOXYGEN_SHOULD_SKIP_THIS

/**
 * @brief This function is intended to initiate the XTAL start, bias, and
 * switch procedure. It will return immediately.  This allows the calling
 * code to do other things while waiting for the XTAL to stabilize.  The
 * functions halCommonTryToSwitchToXtal() and halCommonSwitchToXtal() are
 * intended for completing the process.  This function can be called any
 * number of times and at anytime.
 */
#ifdef DOXYGEN_SHOULD_SKIP_THIS
void halCommonStartXtal(void);
#else //DOXYGEN_SHOULD_SKIP_THIS
//Simply redirect to the primary switch function, which handles all XTAL
//switching and biasing activities.  We don't care about the return code.
//TRUE is ideal but we could get FALSE (even if on the XTAL) because there
//is a biasing event in process and the XTAL is unstable.
#define halCommonStartXtal() halCommonTryToSwitchToXtal()
#endif //DOXYGEN_SHOULD_SKIP_THIS

/**
 * @brief This function switches the chip to using the XTAL.  This includes
 * biasing the XTAL and changing the CPU to 24MHz (FCLK sourced from SYSCLK).
 * This function <b>blocks</b> until the switch procedure has occurred.
 * While blocking, this function invokes idle sleep to reduce current
 * consumption.
 *
 * NOTE: It is possible to use this function as a replacement for 
 * the three other XTAL APIs, including halCommonCheckXtalBiasTrim(), as
 * long as blocking is acceptable.
 *
 * This function can be called any number of times and at anytime.
 */
void halCommonSwitchToXtal(void);

/** @brief Blocks the current thread of execution for the specified
 * amount of time, in milliseconds.
 *
 * The function is implemented with cycle-counted busy loops
 * and is intended to create the short delays required when interfacing with
 * hardware peripherals.  This function works by simply adding another
 * layer on top of halCommonDelayMicroseconds().
 *
 * @param ms  The specified time, in milliseconds. 
 */
void halCommonDelayMilliseconds(int16u ms);


/** @brief Puts the microcontroller to sleep in a specified mode, allows
 * the GPIO wake sources to be determined at runtime.  This function 
 * requires the GPIO wake sources to be defined at compile time in the board
 * file.
 *
 * @note This routine always enables interrupts.
 *
 * @param sleepMode  A microcontroller sleep mode.
 *
 * @param gpioWakeBitMask  A bit mask of the GPIO that are allowed to wake
 * the chip from deep sleep.  A high bit in the mask will enable waking
 * the chip if the corresponding GPIO changes state.  bit0 is PA0, bit1 is
 * PA1, bit8 is PB0, bit16 is PCO, bit23 is PC7, bits[31:24] are ignored.
 * 
 * @sa ::SleepModes
 */
void halSleepWithOptions(SleepModes sleepMode, int32u gpioWakeBitMask);


/**
 * @brief Uses the system timer to enter ::SLEEPMODE_WAKETIMER for
 * approximately the specified amount of time (provided in quarter seconds),
 * the GPIO wake sources can be provided at runtime.
 *
 * This function returns ::ST_SUCCESS and the duration parameter is
 * decremented to 0 after sleeping for the specified amount of time.  If an
 * interrupt occurs that brings the chip out of sleep, the function returns
 * ::ST_SLEEP_INTERRUPTED and the duration parameter reports the amount of
 * time remaining out of the original request.
 *
 * @note This routine always enables interrupts.
 *
 * @note The maximum sleep time of the hardware is limited on STM32W108 platforms
 * to 48.5 days.  Any sleep duration greater than this limit will wake up
 * briefly (e.g. 16 microseconds) to reenable another sleep cycle.
 *
 * @param duration The amount of time, expressed in quarter seconds, that the
 * micro should be placed into ::SLEEPMODE_WAKETIMER.  When the function returns,
 * this parameter provides the amount of time remaining out of the original
 * sleep time request (normally the return value will be 0).
 * 
 * @param gpioWakeBitMask  A bit mask of the GPIO that are allowed to wake
 * the chip from deep sleep.  A high bit in the mask will enable waking
 * the chip if the corresponding GPIO changes state.  bit0 is PA0, bit1 is
 * PA1, bit8 is PB0, bit16 is PCO, bit23 is PC7, bits[31:24] are ignored.
 * 
 * @return An StStatus value indicating the success or
 *  failure of the command.
 */
StStatus halSleepForQsWithOptions(int32u *duration, int32u gpioWakeBitMask);

/**
 * @brief Provides access to assembly code which triggers idle sleep.
 */
void halInternalIdleSleep(void);

/** @brief Puts the microcontroller to sleep in a specified mode.  This
 *  internal function performs the actual sleep operation.  This function
 *  assumes all of the wake source registers are configured properly.
 *
 * @note This routine always enables interrupts.
 *
 * @param sleepMode  A microcontroller sleep mode
 */
void halInternalSleep(SleepModes sleepMode);


/**
 * @brief Obtains the events that caused the last wake from sleep.  The
 * meaning of each bit is as follows:
 * - [31] = WakeInfoValid
 * - [30] = SleepSkipped
 * - [29] = CSYSPWRUPREQ
 * - [28] = CDBGPWRUPREQ
 * - [27] = PWRUP_WAKECORE
 * - [26] = PWRUP_SLEEPTMRWRAP
 * - [25] = PWRUP_SLEEPTMRCOMPB
 * - [24] = PWRUP_SLEEPTMRCOMPA
 * - [23:0] = corresponding GPIO activity
 *  
 * WakeInfoValid means that ::halSleepWithOptions (::halInternalSleep) has been called
 * at least once.  Since the power on state clears the wake event info,
 * this bit says the sleep code has been called since power on.
 *
 * SleepSkipped means that the chip never left the running state.  Sleep can
 * be skipped if any wake event occurs between going ::ATOMIC and transferring
 * control from the CPU to the power management state machine.  Sleep can
 * also be skipped if the debugger is connected (JTAG/SerialWire CSYSPWRUPREQ
 * signal is set).  The net affect of skipping sleep is the Low Voltage
 * domain never goes through a power/reset cycle.
 *
 * @return The events that caused the last wake from sleep. 
 */
int32u halGetWakeInfo(void);


/** @brief Seeds the ::halCommonGetRandom() pseudorandom number
 * generator.
 *
 * It should be called by the application during initialization with a seed
 * from the radio randon number generator.
 *
 * @param seed  A seed for the pseudorandom number generator.
 */
void halCommonSeedRandom(int32u seed);

/** @brief Runs a standard LFSR to generate pseudorandom numbers.
 *
 * Called by the MAC in the stack to choose random backoff slots.
 *
 * Complicated implementations may improve the MAC's
 * ability to avoid collisions in large networks, but it is \b critical to
 * implement this function to return quickly.
 */
int16u halCommonGetRandom(void);
void halCommonBlockUntilXtal(void);
#endif //__STM32W108XX_MICRO_COMMON_H__

/**@} // END micro group
 */

