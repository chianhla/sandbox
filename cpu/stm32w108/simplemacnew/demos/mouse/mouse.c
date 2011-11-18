/**
* @file   mouse.c
* @brief   This is a mouse demo application, based on detection of MEMS movements
* @warning THIS APPLICATION SOFTWARE IS PROVIDED FOR INTERNAL DEMONSTRATION PURPOSE ONLY AND NO OTHER USE IS PERMITTED.
* THIS APPLICATION IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTY OF ANY KIND, EITHER STATUTORY, EXPRESS OR IMPLIED,
* INCLUDING WITHOUT LIMITATION, WARRANTIES OF TITLE, NON-INFRINGEMENT, MERCHANTABILITY, SATISFACTORY QUALITY AND FITNESS
* FOR A PARTICULAR PURPOSE. WITHOUT LIMITING THE GENERALITY OF THE FOREGOING, ST EXPRESSLY DOES NOT WARRANT THE ACCURACY,
* SAFETY, OR USEFULNESS FOR ANY PURPOSE, OF THE SOFTWARE APPLICATION. <br>
* ST HEREBY DISCLAIMS, TO THE FULLEST EXTENT PERMITTED BY APPLICABLE MANDATORY LAW, ANY AND ALL LIABILITY FOR THE USE OF 
* THE SOFTWARE APPLICATION, INCLUDING BUT NOT LIMITED TO ANY LIABILITY IN CONTRACT, TORT, OR OTHERWISE, WHATEVER THE CAUSE
* THEREOF, LIABILITY FOR ANY LOSS OF PROFIT, BUSINESS OR GOODWILL OR ANY DIRECT, INDIRECT, SPECIAL, CONSEQUENTIAL,
* INCIDENTAL OR PUNITIVE COST, DAMAGES OR EXPENSE OF ANY KIND, HOWSOEVER ARISING UNDER OR IN CONNECTION WITH THIS USE.
 * <!-- Copyright 2011 by STMicroelectronics.  All rights reserved.       *80*-->

* \section IAR_project IAR project
  To use the project with IAR Embedded Workbench for ARM, please follow the instructions below:
  -# Open the Embedded Workbench for ARM.
  -# From the File->Open->Workspace menu, open the IAR workspace
     <tt> ...\\simplemac\\demos\\mouse\\EWARMv5\\mouse.eww </tt>
  -# Select desired configuration to build
  -# Select Project->Rebuild All. This will recompile and link the entire application
  -# To launch a debug session, please connect IAR Jlink to JTAG connector (P1) in your board.
  -# Select Project->Download and Debug. The related binary image
     is downloaded into the STM32W108xx Flash memory and interactive debug session is stared.
  -# Connect the application board to a PC USB port. Open a hyperterminal on the
     corresponding USB virtual COMx port with the configuration as described in \ref Serial_IO.

* \subsection IAR_project_configurations IAR project configurations

  \li \c STM32W108xB_TX - STM32W108xB RF MEMS mouse transmitter
  \li \c STM32W108xB_TX-btl STM32W108xB RF MEMS mouse transmitter (for node with OTA bootloader)
  \li \c STM32W108xB_RX - STM32W108xB for RF mouse receiver attached to PC via USB
  \li \c STM32W108xB_RX-btl - STM32W108xB for RF mouse receiver attached to PC via USB (for node with OTA bootloader)
  \li \c STM32W108CC_TX - STM32W108CC RF MEMS mouse transmitter
  \li \c STM32W108CC_RX - STM32W108CC for RF mouse receiver attached to PC via USB

* \section Atollic_project Atollic project
  To use the project with Atollic TrueStudio, please follow the instructions below:
  -# Open Atollic TrueStudio and select a workspace of your choice
  -# From File->Import, select General/Existing Projects into Workspace and click Next
  -# Browse for root directory and select the path: <tt> ...\\simplemac\\demos\\mouse\\TrueStudio </tt>
  -# Select the project mouse and click Finish
  -# Select Project->Build Project (this will build the project with the currently selected configuration)
  -# To launch a debug session, please connect your JTAG Probe to JTAG connector (P1) in your board
  -# Select Run->Debug Configurations
  -# Select the matching debugging configuration from Embedded C/C++ Application
     and click Debug.  The related binary image is downloaded into the STM32W108xx Flash memory
      and interactive debug session is started.
  -# Connect the application board to a PC USB port. Open a hyperterminal on the
     corresponding USB virtual COMx port with the configuration as described in \ref Serial_IO.
 * \note
 * TrueStudio Lite only supports ST-LINK as JTAG Probe
 *
 * \par 
 * The provided debug configuration use ST-LINK as JTAG Probe which is not provided 
 * with STM32W development kits. Users wishing to use ST-LINK should order it apart from STM32W kits
 *
 * \par
 * If you have a TrueStudio Professional, you can select IAR Jlink as JTAG Probe

* \subsection Atollic_project_configurations Atollic project configurations

  \li \c STM32W108xB_TX - STM32W108xB RF MEMS mouse transmitter
  \li \c STM32W108xB_TX-btl STM32W108xB RF MEMS mouse transmitter (for node with OTA bootloader)
  \li \c STM32W108xB_RX - STM32W108xB for RF mouse receiver attached to PC via USB
  \li \c STM32W108xB_RX-btl - STM32W108xB for RF mouse receiver attached to PC via USB (for node with OTA bootloader)
  \li \c STM32W108CC_TX - STM32W108CC RF MEMS mouse transmitter
  \li \c STM32W108CC_RX - STM32W108CC for RF mouse receiver attached to PC via USB

* \section Prebuilt_images Prebuilt images
  \li <tt> ...\\prebuilt\\STM32W108xB\\mouse_tx.s37 </tt> MEMS mouse transmitter
  \li <tt> ...\\prebuilt\\STM32W108xB\\mouse_rx.s37 </tt> Mouse receiver
  \li <tt> ...\\prebuilt\\STM32W108xB\\mouse_tx-btl.s37 </tt> MEMS mouse transmitter (for node with OTA bootloader)
  \li <tt> ...\\prebuilt\\STM32W108xB\\mouse_rx-btl.s37 </tt> Mouse receiver (for node with OTA bootloader)
  \li <tt> ...\\prebuilt\\STM32W108CC\\mouse_tx.s37 </tt> MEMS mouse transmitter
  \li <tt> ...\\prebuilt\\STM32W108CC\\mouse_rx.s37 </tt> Mouse receiver

* \section Jumper_settings Jumper settings
@table
---------------------------------------------------------------
| Jumper name       | STM32W108xB_TX         | STM32W108xB_RX |
---------------------------------------------------------------
| JP1, if available | Fitted                 | Don't care     |
| P1, if available  | 1-2 (battery) 5-6 (USB)| 5-6            |
@endtable 


* \section Board_supported Board supported
@table
| Board name      | Board revision | STM32W108xB_TX| STM32W108xB_RX |
---------------------------------------------------------------------
| Primer2 + MB850 | A              | -             | -              |
| MB851           | A, B           | X             | -              |
| MB851           | C              | X             | X              |
| MB954           | A              | X             | -              |
| MB954           | B              | X             | X              |
| MB950           | A              | X             | X              |
| MB951           | A              | -             | X              |
@endtable

* \section Serial_IO Serial I/O
  Debug info only in case of errors

* \section LEDs_description LEDs description
@table
| LED name  | STM32W108xB_TX                          | STM32W108xB_RX                  |
-----------------------------------------------------------------------------------------
| D1        | On when RF transmission is taking place | Not used                        |
| D3        | Not used                                | On when an RF packet is received|
@endtable

\section Buttons_description Buttons description
@table
| Button name      | STM32W108xB_TX      | STM32W108xB_RX |
-----------------------------------------------------------
| S1               | Left click, Wakeup  | Not used       |
| S2, if available | Left click, Wakeup  | Not used       |
| S3, if available | Right click, Wakeup | Not used       |
| S4, if available | Right click, Wakeup | Not used       |
| S5, if available | Wakeup              | Not used       |
@endtable

\section Usage Usage
The mouse demo is based on the detection of the MEMS axis accelerations that are translate to mouse movement and sent to the receiver attached to the PC.
Please flash one of the supported board with \c mouse_tx.s37 image and flash another board with \c mouse_rx.s37 image. Connect the mouse receiver to the PC and you should be able to use the mouse transmitter as mouse for your PC.
Tilt the mouse transmitter in a direction and the speed of the mouse will be proportional to the tilt angle.
In particular:
\li Tilting towards ground will move mouse down
\li Tilting towards ceiling will move mouse up
\li Tilting left will move mouse left
\li Tilting right will move mouse right

The mouse demo will put the device in deep sleep after 10 seconds of inactivity. To wakeup the mouse is necessary to push any button.
  
**/
/** @addtogroup demos
 * MEMS mouse demo \see mouse.c for documentation.
 *
 *@{
 */

/** @} */
/** \cond DOXYGEN_SHOULD_SKIP_THIS
 */
/* Includes ------------------------------------------------------------------*/

#include PLATFORM_HEADER
#include BOARD_HEADER
#include "hal/hal.h"
#include "hal/micro/cortexm3/uart.h"
#include "hal/micro/mems.h"
#include "include/phy-library.h"
#include "hal/error.h"
#include "stdio.h"
#include "stdlib.h"
#include <math.h>

/* Private define ------------------------------------------------------------*/
#define MAX_RETRIES 3
#define BUFFER_SIZE 64
#define TYPE_SERIAL 0
#define TYPE_BUTTON 1
#define STEADY_THRESHOLD 8

//Define the number of quarter seconds between periodic maintenance events.
//The periodic events do not need to occur very often, so run these
//events once a minute.
#define PERIODIC_MAINTENANCE_EVENTS_RATE (1*60*4)

#define BUTTON_STATE_IDLE         0
#define BUTTON_STATE_DOWN         1
#define BUTTON_STATE_PRESSED      2
#define BUTTON_STATE_WAIT_RELEASE 3
#define BUTTON_STATE_CLICKED      4

#define BUTTON_LEFT_MASK         ((1 << 0) | (1 << 1))
#define BUTTON_RIGHT_MASK        ((1 << 2) | (1 << 3))

#define BUTTON_LEFT_BIT          0
#define BUTTON_RIGHT_BIT         1

#define MOUSE_PAN_ID                   0x2506
#define MOUSE_SHORT_ID                 0x2506

#define INACTIVE_TIMEOUT (10 * 4) // 10 seconds
#define NO_MOVEMENT_TIMEOUT (10000) // in milliseconds
#define X_THRESHOLD 5
#define Y_THRESHOLD 5
/* Private variables ---------------------------------------------------------*/

/* radioTransmitConfig variables required from the SimpleMac library for packet 
   transmission */
RadioTransmitConfig radioTransmitConfig = RADIO_TRANSMIT_CONFIG_DEFAULTS;

/* generic data packet */
ALIGN_VAR(u8 txPacket[128], 2);
u8 txPacket[128] = { 
  0x0a,             // length
  0x41,             // fcf - intra pan, no ack request, data
  0x08,             // fcf - src, dst mode
  0x00,             // seq
  BYTE_0(MOUSE_PAN_ID),   // dst pan l
  BYTE_1(MOUSE_PAN_ID),   // dst pan h
  BYTE_0(MOUSE_SHORT_ID), // dst addr l
  BYTE_1(MOUSE_SHORT_ID), // dst addr h
  0x00              // data
};

/* buffer for received packet */
u8 rxPacket[128];
/* received packet flag */
boolean packetReceived = FALSE;
/* Retries counter */
u8 retries = MAX_RETRIES;

/* packet transmission complete flag */
volatile boolean txComplete = TRUE;

/* Number of transmission errors */
u32 txErrors = 0;

/* Private Functions ---------------------------------------------------------*/
void getPitchAndRoll (s8 x, s8 y, s8 z, s16 *Pitch_Angle, s16 *Roll_Angle)
{
    s16 Longitudinal_axis, Lateral_axis, Vertical_axis;
    double inclination_tg_squere;

    /*************************************************** 
        ACCELEROMETER AXIS ORIENTATION
	****************************************************

		-------------------------
                |           TV          |
		-------------------------

       
                   + Longitudinal_axis
                            ^
                            |
                            |
                          -----
                          | R |
                          | E |
                          | M |
        + Lateral_axis <--| O |
                          | T |
                          | E |
                          -----
                           (.) + Vertical_axis
        
    ***************************************************/

    // Set next parameter accordingly to LIS302DL orientation
    Longitudinal_axis = y;        // Add the right sign (+/-) to match figure!
    Lateral_axis = x;             // Add the right sign (+/-) to match figure!
    Vertical_axis = - z;     // Add the right sign (+/-) to match figure!       
    
    // MOUSE UP DOWN HAVE TO BE PROPORTIONAL TO PITCH ANGLE
    inclination_tg_squere = (s32)(Longitudinal_axis * Longitudinal_axis);
    inclination_tg_squere/= (s32)((Lateral_axis * Lateral_axis)+(Vertical_axis * Vertical_axis));
    inclination_tg_squere = sqrt(inclination_tg_squere);
    
    *Pitch_Angle = (s16) ((atan(inclination_tg_squere) * 360/ (2 * 3.14)) * ((Longitudinal_axis < 0) ? 1 : -1));
    
    // MOUSE UP DOWN HAVE TO BE PROPORTIONAL TO ROLL ANGLE
    inclination_tg_squere = (s32)(Lateral_axis * Lateral_axis);
    inclination_tg_squere/= (s32)((Vertical_axis * Vertical_axis)+(Longitudinal_axis * Longitudinal_axis));
    inclination_tg_squere = sqrt(inclination_tg_squere);
    
    *Roll_Angle = (s16) ((atan(inclination_tg_squere) * 360/ (2 * 3.14)) * ((Lateral_axis < 0) ? -1 : 1));
}
/*******************************************************************************
* Function Name  : sendData
* Description    : It allows to transmit the data
* Input          : - lenght of the data
*                  - data to be transmitted
*                  - type type of data (serial or buttons)
* Output         : None
* Return         : None
*******************************************************************************/
void sendData(u8 length, u8 *data, u8 type)
{
  u32 startTime = halCommonGetInt32uMillisecondTick ();
  while (txComplete == FALSE) {
    u32 now = halCommonGetInt32uMillisecondTick();
    if ((now - startTime) > 200) {
      startTime = now;
      halToggleLed(LED_D3);
    }
  }
  txPacket[8] = type;
  halCommonMemCopy(txPacket+9, data, length);
  txPacket[0] = length + 2 + 7 + 1;
  txPacket[3]++; /* increment sequence number */

  halSetLed(LED_D1);
  txComplete = FALSE;
  if (ST_RadioTransmit(txPacket) != ST_SUCCESS) {
    txComplete = TRUE;
  }
}/* end sendSerialData() */

/*******************************************************************************
* Function Name  : buttonStateMachine
* Description    : Filter in software rebouncing
* Input          : - button
* Output         : None
* Return         : BUTTON_CLICKED or BUTTON_IDLE
*******************************************************************************/
u8 buttonStateMachine(HalBoardButton button, u8 state, u32 thisMillisecondTick, u32 *lastMillisecondsTick)
{
  u8 nextState = state;

  nextState = state;
  switch (state) {
  case BUTTON_STATE_IDLE:
    if (halGetButtonStatus(button) == BUTTON_PRESSED) {
      nextState = BUTTON_STATE_DOWN;
      *lastMillisecondsTick = halCommonGetInt32uMillisecondTick();
    }
    break;
  case BUTTON_STATE_DOWN:
    if (halGetButtonStatus(button) == BUTTON_PRESSED) {
      if ((thisMillisecondTick - *lastMillisecondsTick) > 50) {
	nextState = BUTTON_STATE_PRESSED;
      }
    } else {
      nextState = BUTTON_STATE_IDLE;
    }
    break;
  case BUTTON_STATE_PRESSED:
    nextState = BUTTON_STATE_WAIT_RELEASE;
    break;
  case BUTTON_STATE_WAIT_RELEASE:
    if (halGetButtonStatus(button) != BUTTON_PRESSED) {
      nextState = BUTTON_STATE_CLICKED;
    }
    break;
  case BUTTON_STATE_CLICKED:
    nextState = BUTTON_STATE_IDLE;
  default:
    break;
  }

  return nextState;
}
/*******************************************************************************
* Function Name  : getButtonsStatus
* Description    : Check button status
* Input          : None
* Output         : None
* Return         : Bit mask bit with button status and validity bit
*******************************************************************************/
void getButtonsStatus(u8 *buttonsMask, u8 *buttonsStatus)
{
  static u8 buttonStatus[5] = {BUTTON_STATE_IDLE, BUTTON_STATE_IDLE, BUTTON_STATE_IDLE, BUTTON_STATE_IDLE, BUTTON_STATE_IDLE};
  static u32 buttonStatusTime[5] = {0,0,0,0,0};
  u32 thisMillisecondTick = halCommonGetInt32uMillisecondTick();
  static HalBoardButton buttonList[5];
  static u8 firstTime = 1;
  u8 i;

  if (firstTime) {
    firstTime = 0;
    buttonList[0] = BUTTON_S1;
    buttonList[1] = BUTTON_S2;
    buttonList[2] = BUTTON_S3;
    buttonList[3] = BUTTON_S4;
    buttonList[4] = BUTTON_S5;
  }

  *buttonsMask = 0;
  *buttonsStatus = 0;

  for (i = 0; i < (sizeof(buttonList) / sizeof (HalBoardButton)); i++) {
    buttonStatus[i] = buttonStateMachine(buttonList[i], buttonStatus[i], thisMillisecondTick, &buttonStatusTime[i]);
    if (buttonStatus[i] == BUTTON_STATE_PRESSED) {
      /* Button i pressed */
      *buttonsMask |= (1 << i);
      *buttonsStatus |= (1 << i);
    }
    if (buttonStatus[i] == BUTTON_STATE_CLICKED) {
      /* Button i released */
      *buttonsMask |= (1 << i);
    }
  }
  return;
}

/*******************************************************************************
* Function Name  : mouseSteady
* Description    : It detect whether the mouse is steady or is moving
* Input          : x,y mouse displacement
* Output         : None
* Return         : Boolean flag to say whether the mouse is still or not
*******************************************************************************/
boolean mouseSteady(s8 x, s8 y)
{
  static s8 xWindowMin = 127, yWindowMin = 127, xWindowMax = -128, yWindowMax = -128; 
  boolean returnValue = FALSE;

  if (x < xWindowMin)
    xWindowMin = x;
  if (x > xWindowMax)
    xWindowMax = x;

  if (y < yWindowMin)
    yWindowMin = y;
  if (y > yWindowMax)
    yWindowMax = y;

  if (((xWindowMax - xWindowMin) <= X_THRESHOLD) && ((yWindowMax - yWindowMin) <= Y_THRESHOLD)) {
    returnValue = TRUE;
  } else {
    xWindowMin = 127;
    yWindowMin = 127; 
    xWindowMax = -128;
    yWindowMax = -128; 
  }

  return returnValue;
}

/*******************************************************************************
* Function Name  : processInput
* Description    : It processes serial input and button presses
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void processInput(void)
{
  static u8 buffer[BUFFER_SIZE];
  static u32 lastMillisecondTick = 0, lastMouseMovemement = 0;
  u32 thisMillisecondTick;
  u8 buttonsStatus, buttonsMask;
  u8 buttonReport = 0;
  static u8 buttonTimeout = 0;
  static u8 lastButtonReport = 0;
  double gain = 1.0;
  s16 Pitch_Angle, Roll_Angle;

  getButtonsStatus(&buttonsMask, &buttonsStatus);

  if (buttonsMask) {
    /* Some bits are valid */
    if (buttonsMask & BUTTON_LEFT_MASK) {
      u8 pressed = (buttonsStatus & buttonsMask & BUTTON_LEFT_MASK) ? 1 : 0;
      /* Left button activity (pressed or released) */
      buttonReport |= (pressed << BUTTON_LEFT_BIT);
    } else {
      buttonReport |= lastButtonReport & (1 << BUTTON_LEFT_BIT);
    }

    if (buttonsMask & BUTTON_RIGHT_MASK) {
      u8 pressed = (buttonsStatus & buttonsMask & BUTTON_RIGHT_MASK) ? 1 : 0;
      /* Right button activity (pressed or released) */
      buttonReport |= (pressed << BUTTON_RIGHT_BIT);
    } else {
      buttonReport |= lastButtonReport & (1 << BUTTON_RIGHT_BIT);
    }

    buttonTimeout = 10;
    buffer[0] = 0xFC;
    buffer[1] = 0x00;
    buffer[2] = 0x06;
    buffer[3] = 0x1F;
    buffer[4] = 0;
    buffer[5] = buttonReport;
    buffer[6] = 0;
    buffer[7] = 0;
    buffer[8] = 0x00;
    buffer[9] = 0xCC;
    sendData(10, buffer, TYPE_SERIAL);
    lastButtonReport = buttonReport;
  }

  thisMillisecondTick = halCommonGetInt32uMillisecondTick();
  if (((thisMillisecondTick - lastMillisecondTick) >= 9) && 
      (halMemsGetStatus() & STATUS_REG_ZYXDA))
  {
    s8 MOUSE_X, MOUSE_Y;
    t_mems_data axyz;

    if (buttonTimeout > 0) {
      buttonTimeout--;
      return;
    }

    halMemsGetValue(&axyz); 

    lastMillisecondTick = halCommonGetInt32uMillisecondTick();

    getPitchAndRoll ((s8) axyz.outx_l,
		     (s8) axyz.outy_l,
		     (s8) axyz.outz_l,
		     &Pitch_Angle,
		     &Roll_Angle);

    if (abs(Pitch_Angle) < STEADY_THRESHOLD)
      Pitch_Angle = 0;
    else 
      Pitch_Angle += (Pitch_Angle < 0 ? 1: -1) * STEADY_THRESHOLD;

    if (abs(Roll_Angle) < STEADY_THRESHOLD)
      Roll_Angle = 0;
    else 
      Roll_Angle += (Roll_Angle < 0 ? 1: -1) * STEADY_THRESHOLD;

    MOUSE_X = (s8) (Pitch_Angle * gain);
    MOUSE_Y = (s8) (Roll_Angle * gain);

    buffer[0] = 0xFC;
    buffer[1] = 0x00;
    buffer[2] = 0x06;
    buffer[3] = 0x1F;
    buffer[4] = 0;
    buffer[5] = lastButtonReport;
    buffer[6] = MOUSE_X;
    buffer[7] = MOUSE_Y;
    buffer[8] = 0;
    buffer[9] = 0xCC;

    /* Keep mouse movement */
    if (!mouseSteady(MOUSE_X, MOUSE_Y)) {
      lastMouseMovemement = halCommonGetInt32uMillisecondTick();
    }

    if (((MOUSE_X != 0) || (MOUSE_Y != 0)) && ((halCommonGetInt32uMillisecondTick() - lastMouseMovemement) < NO_MOVEMENT_TIMEOUT)) {
      sendData(10, buffer, TYPE_SERIAL);
    }
  }
}/* end processSerialInput() */

/*******************************************************************************
* Function Name  : processReceivedPackets
* Description    : It processes packed received in RX
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void processReceivedPackets(void)
{
  u8 i;
  /* print out any packets that were received */
  if(packetReceived == TRUE) {
    halSetLed(LED_D3);
    if (rxPacket[8] == TYPE_SERIAL) {
      for (i = 9; i <= rxPacket[0]; i++)
	putchar(rxPacket[i]);
    }
    /* The packet has been processed, so free the single entry queue up */
    packetReceived = FALSE;
    halClearLed(LED_D3);
  }
}

/*******************************************************************************
* Function Name  : periodicMaintenanceEvents
* Description    : Perform periodic maintenance tasks required by STM32W108
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void periodicMaintenanceEvents(void)
{
    static int16u lastPeriodicEventsQsTick = 0;

    if (lastPeriodicEventsQsTick == 0) {
        lastPeriodicEventsQsTick = halCommonGetInt16uQuarterSecondTick();
    }

    //Run periodic maintenance events
    if(elapsedTimeInt16u(lastPeriodicEventsQsTick, halCommonGetInt16uQuarterSecondTick()) >
       PERIODIC_MAINTENANCE_EVENTS_RATE) {
      if(ST_RadioCheckRadio()) {
	ST_RadioCalibrateCurrentChannel();
      }
      halCommonCheckXtalBiasTrim();
      halCommonCalibratePads();
      lastPeriodicEventsQsTick = halCommonGetInt16uQuarterSecondTick();
    }
}

/*******************************************************************************
* Function Name  : powerManagement
* Description    : Check if the device needs to go to deep sleep to save power
* Input          : batteryOperated - Flag to activate the power management
*                : active - Flag to indicate whether the node is active or not
* Output         : None
* Return         : None
*******************************************************************************/
void powerManagement(boolean active, boolean batteryOperated)
{
  static u32 inactiveStartTime = 0;
  
  if (!batteryOperated)
    return;
  
  if (inactiveStartTime == 0) {
    inactiveStartTime = halCommonGetInt16uQuarterSecondTick();
  }
  
  if (active) {
    /* Reset inactive start time */
    inactiveStartTime = halCommonGetInt16uQuarterSecondTick();
  } else {
    if(elapsedTimeInt16u(inactiveStartTime, halCommonGetInt16uQuarterSecondTick()) > INACTIVE_TIMEOUT) {
      StStatus status;

      ST_RadioSleep();
      ATOMIC(
        halMemsPowerDown();
        halPowerDown();
        halSleepWithOptions(SLEEPMODE_NOTIMER,
                            BUTTON_S1_WAKE_SOURCE|
                            BUTTON_S2_WAKE_SOURCE|
                            BUTTON_S3_WAKE_SOURCE|
                            BUTTON_S4_WAKE_SOURCE|
                            BUTTON_S5_WAKE_SOURCE);
        halPowerUp();
      )
      //It is the application's responsibility to reinitialize the UART
      uartInit(115200, 8, PARITY_NONE, 1);
      status = ST_RadioInit(ST_RADIO_POWER_MODE_RX_ON);
      assert(status==ST_SUCCESS);  
      inactiveStartTime = halCommonGetInt16uQuarterSecondTick();
      halMemsInit();
      printf("Wakeup %08x\r\n", halGetWakeInfo());
    }
  }
}

/*******************************************************************************
* Function Name  : powerFromBatteries
* Description    : Check whether the system is battery powered or not
* Input          : None
* Output         : None
* Return         : Flag to indicate whether battery operated or not
*******************************************************************************/
boolean powerFromBatteries(void)
{
  u16 threshold = 3200;
  BoardResourcesType const *boardDescription = halBoardGetDescription();

  /* Optional printf */
  printf ("Measured Vdd (mV) = %d\r\n", halMeasureVdd(ADC_SAMPLE_CLOCKS_512));
  if (halCommonMemCompare(boardDescription->name, "MB950", 5) == 0) {
    /* MB950 has a BAT46 diode to avoid conflict between battery and USB power, so threshold is lowered by 400 mV */
    threshold -= 400;
  }
  return halMeasureVdd(ADC_SAMPLE_CLOCKS_512) > threshold ? FALSE : TRUE;
}

/* ********************* SimpleMac callbacks functions ************************/

/*******************************************************************************
* Function Name  : ST_RadioReceiveIsrCallback
* Description    : Radio Receiver callback function
* Input          : - packet: received packet
*                  - ackFramePendingSet: frame pending bit in the received packet
*                  - time: MAC timer when the SFD was received
*                  - errors: numbers of correlator erros in the packet
*                  - rssi: energy detected in the packet
* Output         : None
* Return         : None
*******************************************************************************/
void ST_RadioReceiveIsrCallback(u8 *packet,
                                boolean ackFramePendingSet,
                                u32 time,
                                u16 errors,
                                s8 rssi)
{
  /* note this is executed from interrupt context */
  u8 i;

  /* Copy the packet to a buffer that can be accessed from the main loop;
     don't do the copy if there is already a packet there being processed */
  if(packetReceived == FALSE) {
    for(i=0; i<=packet[0]; i++) {
      rxPacket[i] = packet[i];
    }
    packetReceived = TRUE;
  }
}/* end ST_RadioReceiveIsrCallback() */

/*******************************************************************************
* Function Name  : ST_RadioTransmitCompleteIsrCallback
* Description    : Radio Transmit callback function
* Input          : - status: status of the packet transmission
*                  - sfdSentTime: MAC timer when the SFD was sent 
*                  - framePending: TRUE if the received ACK indicates that data 
*                    is pending for this node
* Output         : None
* Return         : None
*******************************************************************************/
void ST_RadioTransmitCompleteIsrCallback(StStatus status,
                                         u32 sfdSentTime,
                                         boolean framePending)
{
  switch(status) {
    case ST_PHY_TX_CCA_FAIL:
    case ST_MAC_NO_ACK_RECEIVED:
      // Retry
      if (retries > 0) {
	retries--;
	ST_RadioTransmit(txPacket);
	break;
      } else {
	txErrors++;
      }
    case ST_SUCCESS:
    case ST_PHY_ACK_RECEIVED:
      retries = MAX_RETRIES;
      txComplete = TRUE;
      // Clear led to indicate transmission complete
      halClearLed(LED_D1);
      break;
    default:
      break;
  }
}/* end ST_RadioTransmitCompleteIsrCallback() */

/*******************************************************************************
* Function Name  : ST_RadioDataPendingShortIdIsrCallback
* Description    : Callback for Radio Short Id data pending
* Input          : shortId address
* Output         : TRUE/FALSE
* Return         : None
*******************************************************************************/
boolean ST_RadioDataPendingShortIdIsrCallback(u16 shortId)
{
  return FALSE;
}/* end ST_RadioDataPendingShortIdIsrCallback() */


/*******************************************************************************
* Function Name  : ST_RadioDataPendingLongIdIsrCallback
* Description    : Callback for Radio Long  Id data pending 
* Input          : long id address
* Output         : TRUE/FALSE
* Return         : None
*******************************************************************************/
boolean ST_RadioDataPendingLongIdIsrCallback(u8* longId)
{
  return FALSE;
}/* ST_RadioDataPendingShortIdIsrCallback() */


/*******************************************************************************
* Function Name  : ST_RadioOverflowIsrCallback
* Description    : Radio overflow event callback
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void ST_RadioOverflowIsrCallback(void)
{
 
}/* end ST_RadioOverflowIsrCallback() */

/*******************************************************************************
* Function Name  : ST_RadioSfdSentIsrCallback
* Description    : Radio SFD sent event callback
* Input          : sfdSentTime:MAC timer when the SFD was sent 
* Output         : None
* Return         : None
*******************************************************************************/
void ST_RadioSfdSentIsrCallback(u32 sfdSentTime)
{
}/* end ST_RadioSfdSentIsrCallback() */


/*******************************************************************************
* Function Name  : ST_RadioMacTimerCompareIsrCallback
* Description    : Radio MAC timer comapre Event callback
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void ST_RadioMacTimerCompareIsrCallback(void)
{
}/* end ST_RadioMacTimerCompareIsrCallback() */

/*******************************************************************************
* Function Name  : main.
* Description    : mouse main routine.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
int main(void)
{
  u32 seed;
  StStatus status = ST_SUCCESS;
#ifdef MOUSE_TX
  boolean batteryOperated = FALSE;
  char *role = "TX";
#else
  char *role = "RX";
#endif
  
  /* Initialization */
  halInit();

  ST_RadioGetRandomNumbers((u16 *)&seed, 2);
  halCommonSeedRandom(seed);
  uartInit(115200, 8, PARITY_NONE, 1);
  INTERRUPTS_ON();
#ifdef MOUSE_TX
  batteryOperated = powerFromBatteries();
  {
    BoardResourcesType const *bd = halBoardGetDescription();
    if ((bd->flags & BOARD_HAS_MEMS) == 0) {
      while (1) {
	printf("Error this application requires a board with MEMS device\r\n");
	halCommonDelayMilliseconds(1000);
      }
    }
    halMemsInit();
  }
#else
  {
    BoardResourcesType const *bd = halBoardGetDescription();
    if ((bd->flags & BOARD_HAS_STM32F) == 0) {
      while (1) {
	printf("Error this application requires a board with STM32F as PC interface\r\n");
	halCommonDelayMilliseconds(1000);
      }
    }
  }
#endif
  /* Initialize radio (analog section, digital baseband and MAC).
  Leave radio powered */
  status = ST_RadioInit(ST_RADIO_POWER_MODE_RX_ON);
  assert(status==ST_SUCCESS); 

  /* Setup some node and pan ids.  The packet above is also sent to a device
     with the same node and pan id so that two nodes running this same image
     will talk to each other, even though its not right to have two nodes
     with the same node id */
  ST_RadioSetNodeId(MOUSE_SHORT_ID);
  ST_RadioSetPanId(MOUSE_PAN_ID);

  /* Set channel */
  ST_RadioSetChannel(ST_MIN_802_15_4_CHANNEL_NUMBER);

  printf("\r\nSimpleMAC (%s) Mouse demo (%s)\r\n",SIMPLEMAC_VERSION_STRING, role);

  while(1) {
#ifdef MOUSE_TX
    processInput();
    powerManagement(!txComplete, batteryOperated);
#else
    processReceivedPackets();
#endif
    periodicMaintenanceEvents();

  }
}/* end main ()*/

/** \endcond
 */

