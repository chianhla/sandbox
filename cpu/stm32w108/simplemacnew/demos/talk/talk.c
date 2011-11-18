/**
* @file  talk.c
* @brief This is an example of RF application which shows point-to-point 802.15.4 wireless communication using the STM32W108 microcontroller.
 * <!-- Copyright 2011 by STMicroelectronics.  All rights reserved.       *80*-->

* \section IAR_project IAR project
  To use the project with IAR Embedded Workbench for ARM, please follow the instructions below:
  -# Open the Embedded Workbench for ARM.
  -# From the File->Open->Workspace menu, open the IAR workspace
     <tt> ...\\simplemac\\demos\\talk\\EWARMv5\\talk.eww </tt>
  -# Select desired configuration to build
  -# Select Project->Rebuild All. This will recompile and link the entire application
  -# To launch a debug session, please connect IAR Jlink to JTAG connector (P1) in your board.
  -# Select Project->Download and Debug. The related binary image
     is downloaded into the STM32W108xx Flash memory and interactive debug session is stared.
  -# Connect the application board to a PC USB port. Open a hyperterminal on the
     corresponding USB virtual COMx port with the configuration as described in \ref Serial_IO.

* \subsection IAR_project_configurations IAR project configurations

  - \c STM32W108xB - STM32W108xB configuration
  - \c STM32W108xB-btl - STM32W108xB configuration (for node with OTA bootloader)
  - \c STM32W108CC - STM32W108CC configuration

* \section Atollic_project Atollic project
  To use the project with Atollic TrueStudio, please follow the instructions below:
  -# Open Atollic TrueStudio and select a workspace of your choice
  -# From File->Import, select General/Existing Projects into Workspace and click Next
  -# Browse for root directory and select the path: <tt> ...\\simplemac\\demos\\talk\\TrueStudio </tt>
  -# Select the project talk and click Finish
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
  - \c STM32W108xB - STM32W108xB configuration
  - \c STM32W108xB-btl - STM32W108xB configuration (for node with OTA bootloader)
  - \c STM32W108CC - STM32W108CC configuration

* \section Prebuilt_images Prebuilt images
  - <tt> ...\\prebuilt\\STM32W108xB\\talk.s37 </tt> STM32W108xB Prebuilt version
  - <tt> ...\\prebuilt\\STM32W108xB\\talk-btl.s37 </tt> STM32W108xB Prebuilt version for OTA bootloader
  - <tt> ...\\prebuilt\\STM32W108CC\\talk.s37 </tt> STM32W108CC Prebuilt version

* \section Jumper_settings Jumper settings
@table
----------------------------------------------
| Jumper name       | STM32W108xB            | 
----------------------------------------------
| JP1, if available | Don't care             | 
| P1, if available  | 1-2 (battery) 5-6 (USB)| 
@endtable 


* \section Board_supported Board supported
@table
| Board name      | Board revision | STM32W108xB |
--------------------------------------------------
| Primer2 + MB850 | A              | -           |
| MB851           | A, B           | X           |
| MB851           | C              | X           |
| MB954           | A              | X           |
| MB954           | B              | X           |
| MB950           | A              | X           |
| MB951           | A              | X           |
@endtable

* \section Serial_IO Serial I/O
  The application will listen for keys typed in one node and it will send them to the remote node.
  The remote node will listen for RF messages and it will output them in the serial port.
  In other words everything typed in one node will be visible to the other node and viceversa.
@table
| Parameter name  | Value          | Unit        |
--------------------------------------------------
| Baudrate        | 115200         | bit/sec     |
| Data bits       | 8              | bit         |
| Parity          | None           | bit         |
| Stop bits       | 1              | bit         |
@endtable
  
* \section LEDs_description LEDs description

@table
| LED name | Event               | STM32W108xB                                                                                |
-------------------------------------------------------------------------------------------------------------------------------
| D1       | Button press        | On when a button is pressed, off when the message corresponding to the button press is sent|
| D3       | Button press        | None                                                                                       |
| D1       | RF message received | According to table in @ref Buttons_description                                             |
| D3       | RF message received | According to table in @ref Buttons_description                                             |
| D1+D3    | Error in tx         | Flash together for a second                                                                |
@endtable

\section Buttons_description Buttons description
Button presses on the board will result in sending an RF message to the other board and
the action taken by the other board is described in the following table
@table
| Button name      | STM32W108xB                                      |
-----------------------------------------------------------------------
| S1               | Toggle led D1 in the remote node                 |
| S2, if available | Toggle led D3 in the remote node                 |
| S3, if available | Toggle leds D1 and D3 in the remote node         |
| S4, if available | Blinks led D1 for few seconds in the remote node |
| S5, if available | Blinks led D3 for few seconds in the remote node |
@endtable

\section Usage Usage
This demo shows two use case scenarios:
- RS232 cable replacement. That is a scenario where an existing point-to-point communication based on a wired
  RS232 connection is replaced by 802.15.4 2.4GHz RF link.
- Simple remote control implementation. That is a scenario where button pushes in one board (remote control) will
  result in LED activities in the other board (actuator).

You need to use two boards to exercise the demo.
Step by step instructions are as follow:
-# Load the two boards with talk application, that is: <tt> stm32w_flasher.exe -p COMxx -f -r talk.s37 </tt>
-# Open a terminal on both boards and you should be able to see the keystrokes from one terminal sent to the other terminal. This is an RS232 cable replacement demo.
-# Push any button on one board and observe the corresponding action on the other boards LEDs. This is a simple remote control implementation

\note Notes and limitations
\li You cannot use more than two nodes with talk application in the same radio range, since RF conflicts will arise
\li When pressing a button on the Talk Application Board 1, LED D1 is turned on for indicating
a packet is going to be sent.
\li When pressing a button on the Talk Application Board 1, if something is wrong with the 
current RF communication (packet transmission failed or no acknowledgment received from
the Talk Application Board 2), the Talk Application Board 1 LEDs D1 and D3 start blinking for
few seconds.  
**/

/** @addtogroup demos
 * Point-to-point demo \see talk.c for documentation.
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
#include "include/phy-library.h"
#include "hal/error.h"
#include "stdio.h"
#include "stdlib.h"

/* Private define ------------------------------------------------------------*/
#define TIMEOUT_VALUE 100
#define MAX_RETRIES 3
#define BUFFER_SIZE 64
#define TYPE_SERIAL 0
#define TYPE_BUTTON 1
//Define the number of quarter seconds between periodic maintenance events.
//The periodic events do not need to occur very often, so run these
//events once a minute.
#define PERIODIC_MAINTENANCE_EVENTS_RATE (1*60*4)

#define BUTTON_CLICKED 1
#define BUTTON_IDLE    0

#define BUTTON_ACTION_1 0
#define BUTTON_ACTION_2 1
#define BUTTON_ACTION_3 2
#define BUTTON_ACTION_4 3
#define BUTTON_ACTION_5 4

#define PTP_PAN_ID                   0x1406
#define PTP_SHORT_ID                 0x1406

#define INACTIVE_TIMEOUT (10 * 4) // 10 seconds
/* Private variables ---------------------------------------------------------*/

/* radioTransmitConfig variables required from the SimpleMac library for packet 
   transmission */
RadioTransmitConfig radioTransmitConfig = RADIO_TRANSMIT_CONFIG_DEFAULTS;

/* generic data packet */
ALIGN_VAR(u8 txPacket[128], 2);
u8 txPacket[128] = { 
  0x0a, // length
  0x61, // fcf - intra pan, ack request, data
  0x08, // fcf - src, dst mode
  0x00, // seq
  BYTE_0(PTP_PAN_ID), // dst pan l
  BYTE_1(PTP_PAN_ID), // dst pan h
  BYTE_0(PTP_SHORT_ID), // dst addr l
  BYTE_1(PTP_SHORT_ID), // dst addr h
  0x00  // data
};

/* buffer for received packet */
u8 rxPacket[128];
/* received packet flag */
volatile boolean packetReceived = FALSE;
/* Retries counter */
u8 retries = MAX_RETRIES;

/* packet transmission complete flag */
volatile boolean txComplete = TRUE;

/* Private Functions ---------------------------------------------------------*/

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

  while (txComplete == FALSE);
  txPacket[8] = type;
  halCommonMemCopy(txPacket+9, data, length);
  txPacket[0] = length + 2 + 7 + 1;
  txPacket[3]++; /* increment sequence number */

  txComplete = FALSE;
  ST_RadioTransmit(txPacket);
}/* end sendSerialData() */

/*******************************************************************************
* Function Name  : getButtonStatus
* Description    : Return whether a button has been pressed and released
* Input          : - button
* Output         : None
* Return         : BUTTON_CLICKED or BUTTON_IDLE
*******************************************************************************/
int8u getButtonStatus(HalBoardButton button)
{
  if (halGetButtonStatus(button) == BUTTON_PRESSED) {
    // Indicate button pression detected
    halSetLed(LED_D1);
    /* Wait for release */
    while (halGetButtonStatus(button) == BUTTON_PRESSED);
    halCommonDelayMilliseconds(50);
    while (halGetButtonStatus(button) == BUTTON_PRESSED);
    return BUTTON_CLICKED;
  } else {
    return BUTTON_IDLE;
  }
}

/*******************************************************************************
* Function Name  : buttonAction
* Description    : Send packet to remote node and shortly flashed LED_D1
* Input          : - button
* Output         : None
* Return         : None
*******************************************************************************/
void buttonAction(int8u buttonAction)
{
  sendData(1, &buttonAction, TYPE_BUTTON);
}

/*******************************************************************************
* Function Name  : ledAction
* Description    : Perform some led toggling according to the button received from
*                  remote node
* Input          : - button
* Output         : None
* Return         : None
*******************************************************************************/
void ledAction(int8u buttonAction)
{
  int32u i;

  if (buttonAction == BUTTON_ACTION_1) {
    halToggleLed(LED_D1);
  } else if (buttonAction == BUTTON_ACTION_2) {
    halToggleLed(LED_D3);
  } else if (buttonAction == BUTTON_ACTION_3) {
    halToggleLed(LED_D1);
    halToggleLed(LED_D3);
  } else if (buttonAction == BUTTON_ACTION_4) {
    halClearLed(LED_D1);
    for (i = 0; i < 5; i++) {
      halToggleLed(LED_D1);
      halCommonDelayMilliseconds(200);
    }
  } else if (buttonAction == BUTTON_ACTION_5) {
    halClearLed(LED_D3);
    for (i = 0; i < 5; i++) {
      halToggleLed(LED_D3);
      halCommonDelayMilliseconds(200);
    }
  }
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
  static u8 bufferSize = 0;
  static u32 bufferTimeout = TIMEOUT_VALUE;

  if (bufferSize ==0)
     bufferTimeout = TIMEOUT_VALUE;

  if (__io_getcharNonBlocking(buffer+bufferSize))
  {
     bufferSize+=1;
  }

  if (getButtonStatus(BUTTON_S1) == BUTTON_CLICKED) {
    buttonAction(BUTTON_ACTION_1);
  } else if (getButtonStatus(BUTTON_S2) == BUTTON_CLICKED) {
    buttonAction(BUTTON_ACTION_2);
  } else if (getButtonStatus(BUTTON_S3) == BUTTON_CLICKED) {
    buttonAction(BUTTON_ACTION_3);
  } else if (getButtonStatus(BUTTON_S4) == BUTTON_CLICKED) {
    buttonAction(BUTTON_ACTION_4);
  } else if (getButtonStatus(BUTTON_S5) == BUTTON_CLICKED) {
    buttonAction(BUTTON_ACTION_5);
  } else {
    bufferTimeout--;
    if ((bufferTimeout == 0) || (bufferSize == BUFFER_SIZE)) {
      if (bufferSize > 0) {
	sendData(bufferSize, buffer, TYPE_SERIAL);
	bufferSize = 0;
      }
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
      if (rxPacket[8] == TYPE_SERIAL) {
	for (i = 9; i <= rxPacket[0]; i++)
	  putchar(rxPacket[i]);
      }
      if (rxPacket[8] == TYPE_BUTTON) {
	ledAction(rxPacket[9]);
      }
      /* The packet has been processed, so free the single entry queue up */
      packetReceived = FALSE;
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
        halPowerDown();
        halSleepWithOptions(SLEEPMODE_NOTIMER,
                            BUTTON_S1_WAKE_SOURCE|
                            BUTTON_S2_WAKE_SOURCE|
                            BUTTON_S3_WAKE_SOURCE|
                            BUTTON_S4_WAKE_SOURCE|
                            BUTTON_S5_WAKE_SOURCE|
                            UART_RX_WAKE_SOURCE);
        halPowerUp();
      )
      //It is the application's responsibility to reinitialize the UART
      uartInit(115200, 8, PARITY_NONE, 1);
      status = ST_RadioInit(ST_RADIO_POWER_MODE_RX_ON);
      assert(status==ST_SUCCESS);  
      inactiveStartTime = halCommonGetInt16uQuarterSecondTick();
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
  /* note this is executed from interupt context */
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
    case ST_SUCCESS:
      // This should not happen
      break;
    case ST_PHY_TX_CCA_FAIL:
    case ST_MAC_NO_ACK_RECEIVED:
      // Retry
      if (retries > 0) {
	retries--;
	ST_RadioTransmit(txPacket);
	break;
      } else {
	int32u i;
        halSetLed(LED_D1);
        halSetLed(LED_D3);
	for (i = 0; i < 10; i++) {
          halToggleLed(LED_D1);
          halToggleLed(LED_D3);
          halCommonDelayMilliseconds(100);
	}
        halClearLed(LED_D1);
        halClearLed(LED_D3);
      }
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
* Description    : talk main routine.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
int main(void)
{
  u32 seed;
  StStatus status = ST_SUCCESS;
  boolean batteryOperated = FALSE;
  
  /* Initialization */
  halInit();

  ST_RadioGetRandomNumbers((u16 *)&seed, 2);
  halCommonSeedRandom(seed);
  uartInit(115200, 8, PARITY_NONE, 1);
  INTERRUPTS_ON();

  batteryOperated = powerFromBatteries();
 
  /* Initialize radio (analog section, digital baseband and MAC).
  Leave radio powered down */
  status = ST_RadioInit(ST_RADIO_POWER_MODE_RX_ON);
  assert(status==ST_SUCCESS); 

  /* Set channel */
  ST_RadioSetChannel(ST_MIN_802_15_4_CHANNEL_NUMBER);
  
  /* Setup some node and pan ids.  The packet above is also sent to a device
     with the same node and pan id so that two nodes running this same image
     will talk to each other, even though its not right to have two nodes
     with the same node id */
  ST_RadioSetNodeId(PTP_SHORT_ID);
  ST_RadioSetPanId(PTP_PAN_ID);

  printf("\r\nSimpleMAC (%s) Talk Application\r\n",SIMPLEMAC_VERSION_STRING);

  while(1) {

    processInput();

    powerManagement(!txComplete || packetReceived, batteryOperated);

    processReceivedPackets();

    periodicMaintenanceEvents();

  }
}/* end main ()*/

/** \endcond
 */

