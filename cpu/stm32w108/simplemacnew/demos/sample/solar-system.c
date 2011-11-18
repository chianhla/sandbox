/**
* @file  solar-system.c
* @brief   This is an example of RF application which shows an 802.15.4 star topology using the STM32W108 microcontroller.
 * <!-- Copyright 2011 by STMicroelectronics.  All rights reserved.       *80*-->

* \section IAR_project IAR project
  To use the project with IAR Embedded Workbench for ARM, please follow the instructions below:
  -# Open the Embedded Workbench for ARM.
  -# From the File->Open->Workspace menu, open the IAR workspace
     <tt> ...\\simplemac\\demos\\sample\\EWARMv5\\sample.eww </tt>
  -# Select desired configuration to build
  -# Select Project->Rebuild All. This will recompile and link the entire application
  -# To launch a debug session, please connect IAR Jlink to JTAG connector (P1) in your board.
  -# Select Project->Download and Debug. The related binary image
     is downloaded into the STM32W108xx Flash memory and interactive debug session is stared.
  -# Connect the application board to a PC USB port. Open a hyperterminal on the
     corresponding USB virtual COMx port with the configuration as described in \ref Serial_IO.

* \subsection IAR_project_configurations IAR project configurations

  - \c STM32W108xB_SUN - STM32W108xB configuration for sun role
  - \c STM32W108xB_PLANET - STM32W108xB configuration for planet tole
  - \c STM32W108xB_SUN-btl - STM32W108xB configuration for sun role for nodes with OTA bootloader
  - \c STM32W108xB_PLANET-btl - STM32W108xB configuration for planet role for nodes with OTA bootloader
  - \c STM32W108CC_SUN - STM32W108CC configuration for sun role
  - \c STM32W108CC_PLANET - STM32W108CC configuration for planet tole

* \section Atollic_project Atollic project
  To use the project with Atollic TrueStudio, please follow the instructions below:
  -# Open Atollic TrueStudio and select a workspace of your choice
  -# From File->Import, select General/Existing Projects into Workspace and click Next
  -# Browse for root directory and select the path: <tt> ...\\simplemac\\demos\\sample\\TrueStudio </tt>
  -# Select the project sample and click Finish
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

  - \c STM32W108xB_SUN - STM32W108xB configuration for sun role
  - \c STM32W108xB_PLANET - STM32W108xB configuration for planet role
  - \c STM32W108xB_SUN-btl - STM32W108xB configuration for sun role for nodes with OTA bootloader
  - \c STM32W108xB_PLANET-btl - STM32W108xB configuration for planet role for nodes with OTA bootloader
  - \c STM32W108CC_SUN - STM32W108CC configuration for sun role
  - \c STM32W108CC_PLANET - STM32W108CC configuration for planet role

* \section Prebuilt_images Prebuilt images
  - <tt> ...\\prebuilt\\STM32W108xB\\sample_sun.s37 </tt> Prebuilt version for sun role
  - <tt> ...\\prebuilt\\STM32W108xB\\sample_sun-btl.s37 </tt> Prebuilt version for sun role for OTA bootloader
  - <tt> ...\\prebuilt\\STM32W108xB\\sample_planet.s37 </tt> Prebuilt version for planet role
  - <tt> ...\\prebuilt\\STM32W108xB\\sample_planet-btl.s37 </tt> Prebuilt version for planet role for OTA bootloader
  - <tt> ...\\prebuilt\\STM32W108CC\\sample_sun.s37 </tt> Prebuilt version for sun role
  - <tt> ...\\prebuilt\\STM32W108CC\\sample_planet.s37 </tt> Prebuilt version for planet role

* \section Jumper_settings Jumper settings
@table
----------------------------------------------
| Jumper name       | All configuration      | 
----------------------------------------------
| JP1, if available | Don't care             | 
| P1, if available  | 1-2 (battery) 5-6 (USB)| 
@endtable 

* \section Board_supported Board supported
@table
| Board name      | Board revision | STM32W108xB_SUN | STM32W108xB_PLANET |
---------------------------------------------------------------------------
| Primer2 + MB850 | A              | -               | -                  |
| MB851           | A, B           | X               | X                  |
| MB851           | C              | X               | X                  |
| MB954           | A              | X               | X                  |
| MB954           | B              | X               | X                  |
| MB950           | A              | X               | X                  |
| MB951           | A              | X               | X                  |
@endtable

* \section Serial_IO Serial I/O
  The application will listen for commands sent over the serial port.
  The serial port configuration is as follow:
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
| LED name | STM32W108xB_SUN | STM32W108xB_PLANET                               |
---------------------------------------------------------------------------------
| D1       | Not used        | Not used                                         |
| D3       | Not used        | On when joined to a network, off when not joined |
@endtable

\section Buttons_description Buttons description
@table
| Button name      | STM32W108xB_SUN | STM32W108xB_PLANET |
-----------------------------------------------------------
| S1               | Not used        | Join network       |
| S2, if available | Not used        | Not used           |
| S3, if available | Not used        | Not used           |
| S4, if available | Not used        | Not used           |
| S5, if available | Not used        | Not used           |
@endtable

\section Usage Usage
This demo represent an Application Framework that allows to setup a basic star topology and supports parent and child roles. To prevent name collisions with other software, applications, and implementations the parent role is called "sun" and the child role is called "planet". These roles are implemented using specific defines: SUN_ROLE and PLANET_ROLE. On a node loaded with the sun image, executing the form command will cause the node to form a network. On a node loaded with the planet image, executing the join command will cause the node to join to the network formed by the sun node. Executing the leave command will cause each node to leave the network. Remember that there cannot be multiple suns on the same PAN ID. 

<b>The sample applications demonstrate: </b>
- Management of a simple direct transmission queue 
- Management of a simple indirect transmit queue including interaction with the receive ISR to handle setting the ACK frame pending bit in response to a data poll. 
- Sleepy planets automatically sleep the radio when no more data is available to transmit 
- Retry of packet on ACK failure 
- Active search for a sun implemented as simple blocking code 
- Energy search for a channel with low activity implemented as simple blocking code. 
- Capture of transmit SFD time and insertion of time value into packet payload. 
- Conversion of correlator error count to LQI 
- Planets deep sleeping 

\note
All references to "sleep" and "sleepy" are referring to deep sleep operations

\subsection Serial_commands Serial commands supported
@table
|Command | Description                  | STM32W108xB_SUN | STM32W108xB_PLANET |
-------------------------------------------------------------------------------
|i       |Display status information    | X               | X                  |
|f       |Form a network                | X               | -                  |
|j       |Join a network                | -               | X                  | 
|l       |Leave a network               | X               | X                  |
|s       |Send data                     | X               | X                  | 
|c       |Clear indirect transmit queue | X               | -                  |
|p       |Poll for data                 | -               | X                  |
|r       |Adjust send/poll rates        | X               | X                  |
|t       |Display the planet table      | X               | -                  |
|o       |Enter OTA bootloader mode     | X               | X                  | 
|u       |Enter Uart bootloader mode    | X               | X                  | 
|?       |Display this help menu        | X               | X                  | 
@endtable
\note
All the commands are invoked as a single character.

\subsection Commands_detailed_description Commands detailed description

\b i - Display status information 

It displays the status of the node. This includes information such as: 
- Network role 
- Radio on/off state 
- In or out of a network 
- Channel 
- Power 
- EUI64 
- PAN ID 
- Node ID 
- Send Rate 
- Poll Rate 

\b f - Form a network 

This command can only be executed while not already in a network. To form the network, the node first initializes all persistent state then loops over all channels searching for a channel with the lowest energy. The node dwells on each channel taking multiple energy readings and records the highest energy level seen on every channel. After obtaining a maximum energy reading for each channel, the node selects the channel with the lowest maximum energy reading and configures itself for that channel. The node then assigns itself a random PAN ID and assigns itself the short address (node ID) 0x0000. 

\b j - Join a network 

This command can only be executed while not already in a network. To join the network, the node first initializes all persistent state then loops over all channels searching for a channel with a sun. On each channel, the node transmits a sun search broadcast packet and then waits a healthy 200ms for a sun available response. If the node does not receive a sun available broadcast response after 200ms it moves on to the next channel. If the node never receives a sun available response or cannot complete the join process on any channel, the node indicates this fact to the user and the user must invoke the join network command to try again. The sun will only send the sun available response if there is room in the sun's planet table. If the node does receive a sun available response, the response includes the sun's PAN ID as the source PAN ID. If the node receives more than one sun available response, the node tries to join to the first response it receives. It is not valid to have multiple suns on the same PAN ID and there is no collision detection for this situation. The planet sends a join request unicast packet using long addressing and the sun's PAN ID. When the sun receives the join request, the sun attempts to place to the planet in its planet table. The planet table is a fixed size. If there is no room in the planet table, the sun responds with a join denied unicast packet. If there is room in the planet table, the sun allocates a new short ID to the planet, puts the planet in its planet table, and responds with a join accepted unicast packet. There is no error detection if the join process fails before the join accepted or denied packet has been received. The sun does not remove planets from its planet table unless the planet specifically sends a leaving network packet.
 
\b l - Leave a network 

This command can only be executed while already in a network. On sun nodes, this command simply clears out key persistent state indicating it is no longer active in a network. On planet nodes, this command sends a message to the sun indicating that it is leaving the network. After sending the leaving message, key persistent state is cleared out indicating it is no longer active in a network. The sun does not acknowledge the leave message. After the leave is complete, on either a sun or planet, forming a new network or joining an existing network is now allowed. 

\b s - Send data 

This command can only be executed while already in a network. Send a single unicast message. Automatically sending is controlled with the command "r - Adjust send/poll rates". On planet nodes, a unicast message is placed on the direct transmission queue and sent directly to the sun. On sun nodes, the user is first presented a table of all planet nodes that are active in the sun's planet table. The user must then select the node that the unicast message will be sent to. The unicast message is placed on the indirect transmission queue. The message will stay on the queue until that destination node polls for messages at which point the sun will transmit the message to the planet. These unicast messages use short addresses for both the destination and source. The payload includes the 16 bit VDD_PADS measurement as provided by the related API. Additionally, the 20 bit (3 byte) transmit SFD time of the packet being transmitted is added to the end of the packet payload while the packet is being transmitted. The MSB of the 3 byte SFD time is set last indicating to the receiver that the SFD was correctly placed into the packet. 

\b c - Clear indirect transmit queue 

This command can only be executed while already in a network. It forcefully clears the indirect transmit queue of all packets that are not already in flight. This command is necessary due to the limited size of the indirect transmit queue, the persistance of the packets in the queue, and the fact that a planet with pending data could disappear from the network and never poll for its pending data. 

\b p - Poll for data 

This command can only be executed while already in a network and this command is ineffectual on sun nodes. Poll once. Automatically polling is controlled with the command "r - Adjust send/poll rates". Non-sleepy planets are allowed to poll but since the sun will not queue up indirect transmission for non-sleepy planets the poll will never result in receiving messages. This command sends a short unicast poll packet to the sun. If the sun has data pending for the polling planet, the sun sets the frame pending bit in the MAC ACK. When the planet receives the MAC ACK it observes the frame pending bit. If the frame pending bit is not set, the planet immediately goes back to sleep. If the frame pending bit is set, the planet stays awake for 200ms with receiver on waiting for the sun to transmit the message. After 200ms, the planet goes back to sleep. 

\b r - Adjust send/poll rates 

This command can only be executed while already in a network. Sending data at a regular rate is valid on both the sun and planets, but polling at a regular rate is only valid on sleepy planets. The rate command implements a sub menu for independently controlling automatic/periodic sends and polls. Rates are chosen as the number of quarter-seconds between the events. A rate of zero will turn off that event. The send data command performs a single send whereas the rate command enables automatic and regular sending. The poll command performs a single poll whereas the rate command enables automatic and regular polling. It is valid to issue a send command while the send rate is greater than zero and it is valid to issue a poll command while poll rate is greater than zero. Manually issuing a send or poll command while the rates are greater than zero will simply add those commands to the queue and not disrupt rate controlled operations. This command implements a series of sub menus which configure: 

- which planets get regular messages from the sun 
- the rate at which the sun sends regular messages to the planet 
- the rate at which the planet sends regular messages to the sun 
- the rate at which the planet polls for messages from the sun 

\b t - Display the planet table 
On sun nodes this command displays the entire planet table. Each entry in the table indicates: 
- if that entry is active, which means the planet is still joined to the sun 0
- if there is pending data in the indirect transmission queue for that planet 
- the short address (node ID) of that planet 
- the long address (EUI64) of that planet 

\b o - Enter OTA bootloader mode 
This command activates the IAP bootloader in Over the Air mode. User is requested to provide the application binary image over the air (see the stm32w_flasher -i rf option or the bootloader_demo application example) 

\b u - Enter Uart bootloader mode 
This command activates the IAP bootloader in Uart mode.User is requested to provide the application binary image through the uart interface (see the stm32w_flasher -b option). 

\b ? - Display help menu 
Displays the help menu showing the top level commands and their associated single character command. 

\subsection Notes Notes
<em> Packet Reception: </em>

Commands will print status information while those commands are operating. For example, when forming a network the form command will display the selected channel, that channels energy, and the chosen PAN ID. As for received packets, only data (unicast) messages will be printed. These messages are the result of the send command or the rate command. When a node receives a data message it will print: 
- Short address of the sender (hex number) 
- VDD_PADS, stored in the message payload (decimal number) 
- The 20 bit SFD time from the receiver (hex number) 
- The 20 bit SFD time from the transmitter, stored in the message payload (hex number) 
- The RSSI (decimal number) 
- LQI (hex number) 

<em> Deepsleep Behavior: </em>

When a node is not connected to a network or is a planet, the node will immediately begin deep sleep operations. The user is also informed that the node is entering deepsleep operations and the command interface is dormant. Wakeup can occur due to debugger activity, periodic events, or UART activity. If the node wakes up due to the debugger or periodic events, the node will inform the user that it is awake and return to deep sleep as soon a possible. In this situation, the command interface stays dormant. To wakeup from deepsleep and reactivate the command interface, the user must send a character on the UART. When the node wakes up from UART activity the user will be prompted that the node is awake and the command interface is capable of accepting a command. The node will stay awake with the command interface active until the user executes any command. After a command is executed and completed, the node will return to deep sleep. 

<em> Periodic Events: </em>

In addition to constantly driving network activity in the main loop, the application performs periodic and scheduled events. The timing of two of these periodic events, send and poll, are controlled by the use via the rate command. In addition to the send and poll events, there is a periodic maintenance event that occurs every 60 seconds and performs tasks that are critical to keeping the chip in optimal operating conditions. The maintenance event: 
- checks the radio and invokes calibration if necessary 
- checks the 24MHz crystal bias trim and adjust the trim if necessary 
- checks the GPIO pad drive strength and adjusts the drive strength if necessary 

<em> Primer2 sun application : </em>

- When a planet device joins to the network, a green box with the assigned node ID is displayed on the LCD (up to 5 planets). 
- The Primer2 sun application displays the received VDD_PADS value from each planet (in mV) 
- The "Send data" command is not supported through the Primer2 LCD menu 
- The Primer2 sun application doesn't display the "poll" message coming from a planet 
- When interacting with the Primer2 sun application, it is recommended to keep the planet send rate to a value not lower than the default set value. 


You need to use at least two boards to exercise the demo.
Step by step instructions are as follow:
-# Load the one board with sun role application, that is: <tt> stm32w_flasher.exe -p COMxx -f -r sample_sun.s37 </tt>
-# Load the remaining boards with planet role application, that is: <tt> stm32w_flasher.exe -p COMxx -f -r sample_planet.s37 </tt>
-# Open a terminal on the sun board and type \b f.
-# Push S1 button on all the planet role boards in sequence waiting for led D3 to switch on indicating successfull connection to sun.
-# All the planets should have led D3 on and you should now see messages coming from planets to the sun
  
**/

/** @addtogroup demos
 * Star topology demo \see solar-system.c for documentation.
 *
 *@{
 */

/** @} */
/** \cond DOXYGEN_SHOULD_SKIP_THIS
 */

/*******************************************************************************
* SimpleMAC sample application: solar-system.c
*
* It supports sun and planet roles. 
* Sun role allows user to form a network. 
* Planet role allows an user to join to a network created by a sun.
*
* COPYRIGHT 2010 STMicroelectronics. All rights reserved.                 
*******************************************************************************/

#include PLATFORM_HEADER
#include BOARD_HEADER
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "error.h"
#include "hal/hal.h"
#include "include/phy-library.h"
#include "hal/micro/cortexm3/iap_bootloader.h"

#include "transmit.h"

//RX_DETAILS is a debugging macro for printing receive details.
//WARNING:  THIS MACRO WILL CAUSE PRINTS FROM ISR CONTEXT!
#define RX_DETAILS(x)   
//This macro causes the main loop to print details of the periodic events
//and sleep events.
#define MAIN_DETAILS(x) x

//This mask is passed into halSleepForQsWithOptions, indicating that
//the chip should wake on UART receive activity (GPIO PB2).
#define UART_ACTIVE_MASK (0x00000400)

//Define the number of quarter seconds between periodic maintenance events.
//The periodic events do not need to occur very often, so run these
//events once a minute.
#define PERIODIC_MAINTENANCE_EVENTS_RATE (1*60*4)

//Define the number of entries in the planet table.
#define PLANET_TABLE_SIZE (5)

//Define the number of energy readings that shold be taken on a given
//channel when forming a network and looking for a channel with the
//least ammount of activity.
#define ENERGY_SAMPLES_COUNT (32)

RadioTransmitConfig radioTransmitConfig = RADIO_TRANSMIT_CONFIG_DEFAULTS;

//******************************************************************************
// Define values used in constructing and decoding packets

//These define the magic values needed when constructing the FCF of the
//packets.  802.15.4 defines these numbers.
#define FCF_DATA     (0x01)
#define FCF_MACCMD   (0x03)
#define FCF_ACKREQ   (0x20)
#define FCF_INTRAPAN (0x40)
#define FCF_NODST    (0x00)
#define FCF_SHORTDST (0x08)
#define FCF_LONGDST  (0x0C)
#define FCF_NOSRC    (0x00)
#define FCF_SHORTSRC (0x80)
#define FCF_LONGSRC  (0xC0)

//This app uses only two frame types: MAC Command and Data.
#define FT_DATA          (FCF_DATA)
#define FT_MAC_COMMAND   (FCF_MACCMD)

//The following seven payload types are used with FT_DATA and the numerical
//values are custom to this app.
#define PT_GENERIC_DATA  (0x00)
#define PT_SUN_SEARCH    (0x01)
#define PT_SUN_AVAILABLE (0x02)
#define PT_JOIN_REQUEST  (0x03)
#define PT_JOIN_ACCEPTED (0x04)
#define PT_JOIN_DENIED   (0x05)
#define PT_LEAVING       (0x06)
//This payload type is used with FT_MAC_COMMAND and the numerical value
//is defined by 802.15.4.
#define PT_POLLING       (0x04)

//The packet type is identified by its frame type and its payload type.
//These are stored in different parts of the packet.  Since payload type
//requires a specific frame type, I roll these two values into definitions
//that are easier to read when switching on a decoded packet.  Frame type
//occupies the upper nibble and payload type occupies the lower.
#define GENERIC_DATA_PACKET  ((FT_DATA       <<4) | (PT_GENERIC_DATA <<0))
#define SUN_SEARCH_PACKET    ((FT_DATA       <<4) | (PT_SUN_SEARCH   <<0))
#define SUN_AVAILABLE_PACKET ((FT_DATA       <<4) | (PT_SUN_AVAILABLE<<0))
#define JOIN_REQUEST_PACKET  ((FT_DATA       <<4) | (PT_JOIN_REQUEST <<0))
#define JOIN_ACCEPTED_PACKET ((FT_DATA       <<4) | (PT_JOIN_ACCEPTED<<0))
#define JOIN_DENIED_PACKET   ((FT_DATA       <<4) | (PT_JOIN_DENIED  <<0))
#define LEAVING_PACKET       ((FT_DATA       <<4) | (PT_LEAVING      <<0))
#define POLLING_PACKET       ((FT_MAC_COMMAND<<4) | (PT_POLLING      <<0))

//******************************************************************************
// Define data structures
typedef struct {
  boolean packetBeingProcessed;
  u8 packet[128];
  boolean ackFramePendingSet;
  u32 time;
  u16 errors;
  s8 rssi;
  u8 lqi;
} RadioReceiveType;
RadioReceiveType rxData = {FALSE,};

typedef struct {
  boolean active;
  u16 shortAddr;
  u8 longAddr[8];
} PlanetTableType;


//******************************************************************************
// Define global radio state and convenience macros
RadioPowerMode radioPowerState = ST_RADIO_POWER_MODE_OFF;
#define TURN_RADIO_ON()                             \
  do {                                              \
    ST_RadioWake();                               \
    radioPowerState = ST_RADIO_POWER_MODE_RX_ON; \
  } while(0)
#define TURN_RADIO_OFF()                          \
  do {                                            \
    ST_RadioSleep();                            \
    radioPowerState = ST_RADIO_POWER_MODE_OFF; \
  } while(0)


//******************************************************************************
// Define global network state; initialized when forming/joining/leaving
boolean activeInNetwork = FALSE;
boolean availableSunFound = FALSE;
boolean networkJoinedStopSearching = FALSE;
u8 shortAddrCounter = 0;
u8 currSeqNum = 0;
u8 autoSendRate = 0;
u16 autoSendRateDstShortAddr = 0x0000;
u16 autoSendLastQsTick;
u8 autoPollRate = 0;
u16 autoPollLastQsTick;
PlanetTableType planetTable[PLANET_TABLE_SIZE];

#ifdef PLANET_ROLE
u8 planet_join_by_button = 0;
#endif
       
void initNetworkState(void)
{
  u8 i;
  
  activeInNetwork = FALSE;
  networkJoinedStopSearching = FALSE;
  shortAddrCounter = 0;
  currSeqNum = halCommonGetRandom()&0xFF; //802.15.4 says to start with a random seq num
  autoSendRate = 0;
  autoPollRate = 0;
  txPacketInFlight = FALSE;
  framePendingPktEnroute = FALSE;
  for(i=0;i<PLANET_TABLE_SIZE;i++) {
    planetTable[i].active = FALSE;
    planetTable[i].shortAddr = 0x0000;
    memset(planetTable[i].longAddr, 0, sizeof(planetTable[i].longAddr));
  }
  ST_RadioSetPanId(0xFFFF);  //return to broadcast PAN ID
  ST_RadioSetNodeId(0xFFFE); //return to long addressing node ID
  clearDirectQueue();
  clearIndirectQueue();
}


//******************************************************************************
// LQI calculation.
u8 calculateLqi(u16 chipErrors, u8 packetLength)
{
  //The chipErrors parameter is the 10 bit chip error count from the radio.
  //The packetLength parameter is the byte size of the packet, including
  //  the length byte at the start and the 2 crc bytes at the end.
  u32 lqi;
  
  //To obtain the LQI, convert the total chip errors in a packet (err/packet)
  //to the chip errors per byte (err/byte).  Scale up the chipErrors value
  //to maintain reasonable precision during the division.  We don't
  //care about packets that have more than 4 chip errors per byte (6.25% chip
  //error rate), so we scale up by a factor of 64.
  lqi = chipErrors << 6;
  lqi /= packetLength;
  
  //802.15.4 says that an LQI should represent the best link quality as 0xFF
  //and the worst LQI as 0x00.
  return (0xFF - (u8)((lqi > 0xFF) ? (0xFF) : (lqi)));
}


//******************************************************************************
// Packet reception processing

//ST_RadioReceiveIsrCallback executes in ISR context and copies the
//incoming packet into the rxData structure so it can be processed
//outside of ISR context by processRxPacket.
void ST_RadioReceiveIsrCallback(u8 *packet,
                                  boolean ackFramePendingSet,
                                  u32 time,
                                  u16 errors,
                                  s8 rssi)
{
  u8 i;
  RX_DETAILS(printf("#");)
  if(activeInNetwork) {
    //If there isn't already one being processed, save the
    //incoming packet into the app's buffer for processing
    //outside of ISR context.
    if(!rxData.packetBeingProcessed) {
      for(i=0;i<=packet[0];i++) {
        rxData.packet[i] = packet[i];
      }
      rxData.ackFramePendingSet = ackFramePendingSet;
      rxData.time = time;
      rxData.errors = errors;
      rxData.rssi = rssi;
      rxData.packetBeingProcessed = TRUE;
      //processRxPacket() in the main loop handles the rest
    }
  }
}

//processRxPacket handles decoding all received packets and taking action
//in response to received packets.  This function executes outside of
//ISR context and operates on the rxData structure.  The rxData structure
//is populated by ST_RadioReceiveIsrCallback.
void processRxPacket(void)
{
  u8 i;
  boolean pktHasSrcPanId = FALSE;
  u8 srcAddrOffset = 0;
  u16 srcPanId=0xFFFF;
  u16 shortSrcAddr=0;
  u8 longSrcAddr[8]={0,};
  u8 payloadStart;
  u8 packetType;
  u8 packet[128];
  
  if(!rxData.packetBeingProcessed) {
    return;
  }
  
  RX_DETAILS(
    printf("\r\n");
    printf("RX:");
    for(i=0;i<=rxData.packet[0];i++) {
      printf(" %02X", rxData.packet[i]);
    }
    printf("\r\n");
    printf("ackFramePendingSet = %d\r\n", rxData.ackFramePendingSet);
    printf("time = 0x%05X\r\n", rxData.time);
    printf("errors = %d\r\n", rxData.errors);
    printf("rssi = %d\r\n", rxData.rssi);
  );
  
  //At a minimum there must be a dst PAN, a short dst addr, a short src
  //addr, and a payload/command type.  That's a minimum of 10 bytes.
  if(rxData.packet[0]<10) {
    RX_DETAILS(printf("Length byte too short\r\n");)
    goto stopProcessing;
  }
  
  //Determine the frame type.
  switch(rxData.packet[1]&0x7) {
    case FT_DATA:
      RX_DETAILS(printf("FT_DATA\r\n");)
      packetType = (FT_DATA<<4);
      break;
    case FT_MAC_COMMAND:
      RX_DETAILS(printf("FT_MAC_COMMAND\r\n");)
      packetType = (FT_MAC_COMMAND<<4);
      break;
    default:
      RX_DETAILS(printf("Unknown frame type\r\n");)
      goto stopProcessing;
  };
  
  //Is there a source PAN ID in the packet?
  if((rxData.packet[1]&0x40)!=0x40) {
    pktHasSrcPanId=TRUE;
    srcAddrOffset = 2;
  }
  
  //There are 4 possible addressing modes in our application:
  switch(rxData.packet[2]) {
    case FCF_SHORTDST + FCF_SHORTSRC:
      RX_DETAILS(printf("short dst, short src\r\n");)
      shortSrcAddr = (rxData.packet[8+srcAddrOffset+1]<<8)|
                     (rxData.packet[8+srcAddrOffset+0]<<0);
      payloadStart = 10+srcAddrOffset;
      if(pktHasSrcPanId) {
        srcPanId = (rxData.packet[9]<<8)|(rxData.packet[8]<<0);
      }
      break;
    case FCF_SHORTDST + FCF_LONGSRC:
      RX_DETAILS(printf("short dst, long src\r\n");)
      memcpy(longSrcAddr, (rxData.packet+8+srcAddrOffset), 8);
      payloadStart = 16+srcAddrOffset;
      if(pktHasSrcPanId) {
        srcPanId = (rxData.packet[9]<<8)|(rxData.packet[8]<<0);
      }
      break;
    case FCF_LONGDST + FCF_SHORTSRC:
      RX_DETAILS(printf("long dst, short src\r\n");)
      shortSrcAddr = (rxData.packet[14+srcAddrOffset+1]<<8)|
                     (rxData.packet[14+srcAddrOffset+0]<<0);
      payloadStart = 16+srcAddrOffset;
      if(pktHasSrcPanId) {
        srcPanId = (rxData.packet[15]<<8)|(rxData.packet[14]<<0);
      }
      break;
    case FCF_LONGDST + FCF_LONGSRC:
      RX_DETAILS(printf("long dst, long src\r\n");)
      memcpy(longSrcAddr, (rxData.packet+14+srcAddrOffset), 8);
      payloadStart = 22+srcAddrOffset;
      if(pktHasSrcPanId) {
        srcPanId = (rxData.packet[15]<<8)|(rxData.packet[14]<<0);
      }
      break;
    default:
      RX_DETAILS(printf("Unknown addressing mode\r\n");)
      goto stopProcessing;
  }
  
  RX_DETAILS(
    if(pktHasSrcPanId) {
      printf("src pan = 0x%04X\r\n", srcPanId);
    }
  )
  
  //Make sure the packet is long enough to obtain a payload type
  if(rxData.packet[0]<payloadStart) {
    RX_DETAILS(printf("Length byte too short\r\n");)
    goto stopProcessing;
  }
  
  //Finish deriving the packet type by obtaining the payload type.
  packetType |= (rxData.packet[payloadStart]<<0);
  RX_DETAILS(printf("packet type = 0x%02X\r\n", packetType);)
  
  switch(packetType) {
    case (GENERIC_DATA_PACKET): //executes on SUN and PLANET
      RX_DETAILS(printf("GENERIC_DATA_PACKET\r\n");)
      //The LQI calculation wants the entire packet length.  The length
      //byte in the received packet does not include the length byte
      //itself or the two CRC bytes.
      rxData.lqi = calculateLqi(rxData.errors, (rxData.packet[0]+3));
      printf("RX: Addr=0x%04X, VDD=%dmV, RxSFD=0x%05X, ",
             shortSrcAddr,
             ((rxData.packet[payloadStart+1]<<0)|
              (rxData.packet[payloadStart+2]<<8)),
             rxData.time);
      if(rxData.packet[payloadStart+5]&0x80) {
        //Only show the TX SFD if the transmitter was capable of getting
        //the SFD into the packet in time.
        rxData.packet[payloadStart+5] &= ~0x80;
        printf("TxSFD=0x%05X, ",
               ((rxData.packet[payloadStart+3]<< 0)|
                (rxData.packet[payloadStart+4]<< 8)|
                (rxData.packet[payloadStart+5]<<16)));
      } else {
        printf("TxSFD=-------, ");
      }
      printf("RSSI=%ddBm, LQI=0x%02X\r\n",
             rxData.rssi,
             rxData.lqi);
      break;
    
    case (SUN_SEARCH_PACKET): //executes on SUN
      RX_DETAILS(printf("SUN_SEARCH_PACKET\r\n");)
      //As a sun, if I have room in my planet table I transmit that
      //I am available.  Otherwise, I don't transmit anything.
      for(i=0;i<PLANET_TABLE_SIZE;i++) {
        if(!planetTable[i].active) {
          //Length
          packet[0] = (24+2);
          packet[1] = FCF_DATA;
          packet[2] = FCF_LONGDST + FCF_LONGSRC;
          //New sequence number
          currSeqNum++;
          packet[3]=currSeqNum;
          //dst PAN ID
          packet[4] = (0xFFFF>>0)&0xFF;
          packet[5] = (0xFFFF>>8)&0xFF;
          //long dst addr
          memcpy((packet+6), longSrcAddr, 8);
          //src PAN ID
          packet[14] = (ST_RadioGetPanId()>>0)&0xFF;
          packet[15] = (ST_RadioGetPanId()>>8)&0xFF;
          //Long src addr
          memcpy((packet+16), ST_RadioGetEui64(), 8);
          //payload type
          packet[24] = PT_SUN_AVAILABLE;
          //Broadcast response
          enqueueTxPacket(TRUE, 0xFFFF, packet, 0);
          break;
        }
      }
      break;
    
    case (SUN_AVAILABLE_PACKET): //executes on PLANET
      RX_DETAILS(printf("SUN_AVAILABLE_PACKET\r\n");)
      //If I already found a sun, ignore any subsequent available messages
      if(availableSunFound) {
        return;
      }
      availableSunFound=TRUE;
      //As a planet, send a unicast join request to the sun.  But first,
      //switch to the sun's PAN in anticipation of completing the join.
      ST_RadioSetPanId(srcPanId);
      //Length
      packet[0] = (22+2);
      packet[1] = FCF_DATA + FCF_ACKREQ + FCF_INTRAPAN;
      packet[2] = FCF_LONGDST + FCF_LONGSRC;
      //New sequence number
      currSeqNum++;
      packet[3]=currSeqNum;
      //dst PAN ID
      packet[4] = (ST_RadioGetPanId()>>0)&0xFF;
      packet[5] = (ST_RadioGetPanId()>>8)&0xFF;
      //long dst addr
      memcpy((packet+6), longSrcAddr, 8);
      //long src addr
      memcpy((packet+14), ST_RadioGetEui64(), 8);
      //payload type
      packet[22] = PT_JOIN_REQUEST;
      //Unicast join request
      enqueueTxPacket(TRUE, 0xFFFF, packet, 0);
      break;
      
    case (JOIN_REQUEST_PACKET): //executes on SUN
      RX_DETAILS(printf("JOIN_REQUEST_PACKET\r\n");)
      {
        u8 pt = PT_JOIN_DENIED;
        u8 assignedShortId[2] = {0xFE, 0xFF};
        //sun responds with unicast packet to long ID, acceptance, and the
        //assigned short ID as payload.  denied packets have a short ID 0xFFFE
        //Length
        packet[0] = (24+2);
        packet[1] = FCF_DATA + FCF_ACKREQ + FCF_INTRAPAN;
        packet[2] = FCF_LONGDST + FCF_LONGSRC;
        //New sequence number
        currSeqNum++;
        packet[3]=currSeqNum;
        //dst PAN ID
        packet[4] = (ST_RadioGetPanId()>>0)&0xFF;
        packet[5] = (ST_RadioGetPanId()>>8)&0xFF;
        //long dst addr
        memcpy((packet+6), longSrcAddr, 8);
        //long src addr
        memcpy((packet+14), ST_RadioGetEui64(), 8);
        
        //sun looks for a free spot in the planet table
        //if none, sun sends a unicast join denied, then idles
        //if one, sun allocates the planet a short ID and sends a unicast
        //  join accepted to long id with short id in payload, then idles
        for(i=0;i<PLANET_TABLE_SIZE;i++) {
          if(!planetTable[i].active) {
            planetTable[i].active = TRUE;
            shortAddrCounter++;
            planetTable[i].shortAddr = shortAddrCounter;
            memcpy(planetTable[i].longAddr, longSrcAddr, 8);
            pt = PT_JOIN_ACCEPTED;
            assignedShortId[0] = (shortAddrCounter>>0)&0xFF;
            assignedShortId[1] = (shortAddrCounter>>8)&0xFF;
            printf("Join: Planet 0x%04X (index %d) has joined the network\r\n", shortAddrCounter, i);

            break;
          }
        }
        //payload type
        packet[22] = pt;
        packet[23] = assignedShortId[0];
        packet[24] = assignedShortId[1];
        //Unicast join request response
        enqueueTxPacket(TRUE, 0xFFFF, packet, 0);
      }
      break;
      
    case (JOIN_ACCEPTED_PACKET): //executes on PLANET
      RX_DETAILS(printf("JOIN_ACCEPTED_PACKET\r\n");)
      //pan ID is already set during PT_SUN_AVAILABLE
      //set my short ID to the one assigned to me via the payload
      ST_RadioSetNodeId((rxData.packet[payloadStart+1]<<0)|
                          (rxData.packet[payloadStart+2]<<8));
      //join complete, halt the search
      networkJoinedStopSearching = TRUE;
      break;
      
    case (JOIN_DENIED_PACKET): //executes on PLANET
      RX_DETAILS(printf("JOIN_DENIED_PACKET\r\n");)
      //return to broadcast PAN ID and try other suns/channels
      ST_RadioSetPanId(0xFFFF);
      break;
      
    case (POLLING_PACKET): //executes on SUN
      RX_DETAILS(printf("POLLING_PACKET\r\n");)
      //Remember: ST_RadioDataPendingShortIdIsrCallback already did
      //the hard work of determining is the polling node has data.  If
      //ackFramePendingSet is true then we definitely have data from
      //the polling device.  Send the packet now.
      if(rxData.ackFramePendingSet) {
        //When transmitting a packet in response to receiving a packet,
        //we must wait 1ms to ensure our new transmission does not disrupt
        //the ACK automatically sent in response to the reception.
        halCommonDelayMilliseconds(1);
        transmitIndirectPacketNow();
      }
      break;
      
    case (LEAVING_PACKET): //executes on SUN
      RX_DETAILS(printf("LEAVING_PACKET\r\n");)
      //Try to remove the child from the table (but don't worry about it
      //if we can't).
      for(i=0;i<PLANET_TABLE_SIZE;i++) {
        if(planetTable[i].active && (planetTable[i].shortAddr==shortSrcAddr)) {
          printf("Leave: Planet 0x%04X (index %d) has left the network\r\n", shortSrcAddr, i);
          planetTable[i].active = FALSE;
          break;
        }
      }
      break;
      
    default:
      RX_DETAILS(printf("Unknown payload type\r\n");)
      goto stopProcessing;
  }
  
stopProcessing:
  rxData.packetBeingProcessed = FALSE;
}

//This callback must be defined.  This callback is enabled using the function
//ST_RadioEnableOverflowNotification but should never be called by the phy
//library.  If it is called, something went wront with receive.  Probably
//long latency.
void ST_RadioOverflowIsrCallback(void)
{
  assert(FALSE);
}


//******************************************************************************
// Convenience function for obtaining an u8 value from the command line
// where the value is provided by the user as a decimal.
u8 getInt8uFromUser(void)
{
  int ch;
  char textEntry[4]={0,};
  u8 number;
  u8 i=0;
  
  //Obtain the number from the user.  The most I can accept is a 3 digit
  //decimal number < 256
  printf("(8bit decimal num)> ");
  //Flush any input characters left over (could be some stray line endings)
  ch=getchar();
  ch=getchar();
  do {
    halResetWatchdog();
    processRxPacket();
    txTick();
    ch=getchar();
    if(ch>=0) {
      if(ch=='\r' || ch=='\n') {
        printf("\r\n");
      } else {
        printf("%c", ch);
      }
      textEntry[i]=ch;
      i++;
    }
  } while(ch!='\r' && ch!='\n' && i<sizeof(textEntry));
  textEntry[3] = '\0';
  number = atoi(textEntry);
  
  printf("Entered number: %d\r\n", number);
  return number;
}


//******************************************************************************
// Attempt to deep sleep for a duration define by qsToNextEvent.  Deepsleep
// will also wakeup from UART_ACTIVE_MASK.  This function will check for
// and prevent sleep if the application is active, expecting further
// operations, and should not go to sleep.
void tryToSleep(int32u qsToNextEvent)
{ 
  
  //Sleep can only occur while we're not the sun.  When a node
  //resets or leaves, it's default node ID is not 0x0000 so the device
  //will begin to sleep.
#ifdef SUN_ROLE
  return;
#else
  StStatus status = ST_SUCCESS;

  static boolean commandPromptOn=TRUE;
  
  if(ST_RadioGetNodeId() == 0x0000) {
    return;
  }
  
  //Don't sleep if the radio is busy
  if(txPacketInFlight ||
     rxData.packetBeingProcessed ||
     framePendingPktEnroute) {
    return;
  }

  //Don't sleep if there has been GPIO activity
  if(INT_PENDSET&INT_IRQD) {
    if(!commandPromptOn) {
      printf("\r\nStaying awake until next command:\r\n");
      printf("> ");
      commandPromptOn=TRUE;
    }
    return;
  }
  
  
  MAIN_DETAILS(printf("Sleep... ");)
  if(commandPromptOn) {
    printf("(perform UART activity to wake)\r\n");
    commandPromptOn=FALSE;
  }
  fflush(stdout);
  
  ST_RadioSleep();
  ATOMIC(
    halPowerDown();
#ifdef PLANET_ROLE
   halSleepForQsWithOptions(&qsToNextEvent, UART_ACTIVE_MASK|BUTTON_S1_WAKE_SOURCE);
#else
    halSleepForQsWithOptions(&qsToNextEvent, UART_ACTIVE_MASK);
#endif
    halPowerUp();
    //It is the application's responsibility to reinitialize the UART
    uartInit(115200, 8, PARITY_NONE, 1);
  )
  //The SimpleMAC library states that the radio should not be woken within
  //250us of calling ST_RadioSleep.  Since I do not know the shortest
  //possible time sleeping could take, I just tack on a delay here.  If
  //sleep time becomes critical, this tryToSleep() function should be
  //analyzed and optimized.
  halCommonDelayMicroseconds(200);
  status = ST_RadioInit(radioPowerState);
  assert(status==ST_SUCCESS);  
  MAIN_DETAILS(printf("awake\r\n");)

#endif /* SUN_ROLE */
}


//******************************************************************************
// This section defines all of the commands that the user can invoke
// from the command line.

//Command invoked with 'i'.  Print information about the node.
void infoCmd(void)
{
  u8 i;
  u8 * EUI64 = ST_RadioGetEui64();
  
  printf("\r\n");
  if(activeInNetwork) {
    if(ST_RadioGetNodeId()==0x0000) {
      printf("Network role: sun\r\n");
    } else {
      printf("Network role: planet\r\n");
    }
  } else {
    printf("Network role: <not active in a network>\r\n");
  }
  
  if(radioPowerState == ST_RADIO_POWER_MODE_OFF) {
    printf("Radio:        Off\r\n");
  } else {
    printf("Radio:        On\r\n");
  }
  if(activeInNetwork) {
    printf("In network:   Yes\r\n");
  } else {
    printf("In network:   No\r\n");
  }
  printf("Channel:      %d\r\n", ST_RadioGetChannel());
  printf("Power:        %d dBm\r\n", ST_RadioGetPower());
  printf("EUI64:        0x");
  i=8;
  while(i--) {
    printf("%02X", EUI64[i]);
  }
  printf("\r\n");
  printf("PAN ID:       0x%04X\r\n", ST_RadioGetPanId());
  printf("Node ID:      0x%04X\r\n", ST_RadioGetNodeId());
  printf("Send Rate:    %d\r\n", autoSendRate);
  printf("Poll Rate:    %d\r\n", autoPollRate);
}


//Command invoked with 'f'.  Form a network and become a sun.
void formCmd(void)
{
  u8 i;
  u8 searchChannel;
  s8 searchEnergy;
  u8 minEnergyChannel = ST_MIN_802_15_4_CHANNEL_NUMBER;
  s8 minEnergy = 127;
  StStatus status = ST_SUCCESS;

  printf("\r\n");
  if(activeInNetwork) {
    printf("Already in network\r\n");
    return;
  }
  printf("Inactive node forming network and becoming the sun\r\n");
  
  initNetworkState();
  
  TURN_RADIO_ON();
  
  //Loop across all channels
  for(searchChannel=ST_MIN_802_15_4_CHANNEL_NUMBER;
      searchChannel<=ST_MAX_802_15_4_CHANNEL_NUMBER;
      searchChannel++) {
    s8 maxEnergy=-128;
    status = ST_RadioSetChannel(searchChannel);
    assert(status==ST_SUCCESS);
    
    for(i=0;i<ENERGY_SAMPLES_COUNT;i++) {
      //Wait 16 symbol periods for energy readings to settle.
      halCommonDelayMicroseconds(256);
      //Find the max energy for this channel
      searchEnergy = ST_RadioEnergyDetection();
      if(searchEnergy > maxEnergy) {
        maxEnergy = searchEnergy;
      }
    }
    //Find the channel with the lowest max energy
    if(maxEnergy < minEnergy) {
      minEnergy = maxEnergy;
      minEnergyChannel = searchChannel;
    }
  }
  
  //Select the channel with the lowest max energy
  status = ST_RadioSetChannel(minEnergyChannel);
  assert(status==ST_SUCCESS);
  printf("Selected channel %d with energy %d dBm\r\n",
         minEnergyChannel, minEnergy);
  
  //Give our new network a random PAN ID
  ST_RadioSetPanId(halCommonGetRandom());
  printf("Randomly chose PAN ID: 0x%04X\r\n", ST_RadioGetPanId());
  
  //When forming a network, the sun always assigns itself Node ID 0.
  //(shortAddrCounter is initialized to 0 by initNetworkState)
  ST_RadioSetNodeId(shortAddrCounter);
  
  //Address filtering was already enabled during  app initialization
  //Planet table was already cleared out by initNetworkState()
  
  //The new network is now formed and ready
  activeInNetwork = TRUE;
}


//Command invoked with 'j'.  Join a network and become a planet.  After
//the first packet is transmitted here, the rest of the join process
//is handled by processRxPacket.
void joinCmd(void)
{
  u8 packet[128];
  u8 searchChannel;
  u32 lastTime;
  StStatus status = ST_SUCCESS;

  printf("\r\n");
  if(activeInNetwork) {
    printf("Already in network\r\n");
    return;
  }
  printf("Inactive node joining network and becoming a planet\r\n");
  
  initNetworkState();
  
  TURN_RADIO_ON();
  //While we're not joined to a network yet, the receive ISR needs to be able
  //to process packets.  This state will either stay TRUE if the join
  //succeeds or return to FALSE if it doesn't.
  activeInNetwork = TRUE;
  
  //Length
  packet[0] = (18+2);
  packet[1] = FCF_DATA;
  packet[2] = FCF_SHORTDST + FCF_LONGSRC;
  //packet[3] - New sequence number is handled immediately before transmission
  //dst PAN ID
  packet[4] = (0xFFFF>>0)&0xFF;
  packet[5] = (0xFFFF>>8)&0xFF;
  //Short dst addr
  packet[6] = (0xFFFF>>0)&0xFF;
  packet[7] = (0xFFFF>>8)&0xFF;
  //src PAN ID
  packet[8] = (0xFFFF>>0)&0xFF;
  packet[9] = (0xFFFF>>8)&0xFF;
  //Long src addr
  memcpy((packet+10), ST_RadioGetEui64(), 8);
  //payload type
  packet[18] = PT_SUN_SEARCH;
  
  printf("Trying channel");
  //Loop across all channels
  for(searchChannel=ST_MIN_802_15_4_CHANNEL_NUMBER;
      searchChannel<=ST_MAX_802_15_4_CHANNEL_NUMBER;
      searchChannel++) {
    //Since we wait 200ms per channel while trying to join, the watchdog
    //must be reset to prevent it from triggering.
    halResetWatchdog();
    
    printf(" %d", searchChannel);
    status = ST_RadioSetChannel(searchChannel);
    assert(status==ST_SUCCESS);

    //Populate the join packet with a new sequence number
    currSeqNum++;
    packet[3]=currSeqNum;
    
    //Broadcast searching for any suns
    availableSunFound = FALSE;
    enqueueTxPacket(TRUE, 0xFFFF, packet, 0);
    
    //Dwell for 200ms trying to complete a join with any sun on this channel
    lastTime = halCommonGetInt32uMillisecondTick();
    do {
      processRxPacket();
      txTick();
    } while(elapsedTimeInt32u(lastTime, halCommonGetInt32uMillisecondTick())<
            200);
    
    //If our join was accepted and we've successfully transmitted our join
    //acceptence acknowledgment, we can exit the join channel search.
    if(networkJoinedStopSearching) {
      printf("\r\n");
      printf("Joined on channel %d with PAN ID 0x%04X.  My ID is now 0x%04X.\r\n",
             ST_RadioGetChannel(),
             ST_RadioGetPanId(),
             ST_RadioGetNodeId());
      activeInNetwork = TRUE;
#ifdef PLANET_ROLE
      autoSendRate = 60;
      halSetLed(LED_D3);
#endif
      return;
    }
  }
  
  printf("\r\n");
  printf("Did not join.  Returning to inactive state.\r\n");
  //Getting here means we did not successful join a network.
  activeInNetwork = FALSE;
}


//Command invoked with 'l'.  Leave a network.
void leaveCmd(void)
{
  u8 packet[128];
  u16 dstShortAddr = 0x0000;
  u32 lastTime;
  
  printf("\r\n");
  if(!activeInNetwork) {
    printf("Not in network\r\n");
    return;
  }
  printf("Leaving network and becoming an inactive node\r\n");
  
  //A planet sends a courtesy leave message.  Don't bother with an ACK since
  //the planet will leave no matter what.
  if(ST_RadioGetNodeId() != 0x0000) {
    //Length
    packet[0] = (10+2);
    packet[1] = FCF_DATA + FCF_INTRAPAN;
    packet[2] = FCF_SHORTDST + FCF_SHORTSRC;
    //New sequence number
    currSeqNum++;
    packet[3] = currSeqNum;
    //dst PAN ID
    packet[4] = (ST_RadioGetPanId()>>0)&0xFF;
    packet[5] = (ST_RadioGetPanId()>>8)&0xFF;
    //Short dst addr
    packet[6] = (dstShortAddr>>0)&0xFF;
    packet[7] = (dstShortAddr>>8)&0xFF;
    //Short src addr
    packet[8] = (ST_RadioGetNodeId()>>0)&0xFF;
    packet[9] = (ST_RadioGetNodeId()>>8)&0xFF;
    //payload type
    packet[10] = PT_LEAVING;
    enqueueTxPacket(TRUE, dstShortAddr, packet, 0);
    //Give ourselves 200ms to complete any transactions before disappearing.
    lastTime = halCommonGetInt32uMillisecondTick();
    do {
      processRxPacket();
      txTick();
    } while(elapsedTimeInt32u(lastTime, halCommonGetInt32uMillisecondTick())<
            200);
  }
  
  //Initilizing will return us to a clean, inactive state
  initNetworkState();
  TURN_RADIO_OFF();
#ifdef PLANET_ROLE
  halClearLed(LED_D3);
#endif
      
}


//This function is indirectly invoked by the command 's' to send a data packet.
void sendVddDataPacket(u16 vddMillivolts,
                       u16 dstShortAddr,
                       boolean sendDirectly)
{
  u8 packet[128];
  
  //Length
  packet[0] = (15+2);
  packet[1] = FCF_DATA + FCF_ACKREQ + FCF_INTRAPAN;
  packet[2] = FCF_SHORTDST + FCF_SHORTSRC;
  //New sequence number
  currSeqNum++;
  packet[3] = currSeqNum;
  //dst PAN ID
  packet[4] = (ST_RadioGetPanId()>>0)&0xFF;
  packet[5] = (ST_RadioGetPanId()>>8)&0xFF;
  //Short dst addr
  packet[6] = (dstShortAddr>>0)&0xFF;
  packet[7] = (dstShortAddr>>8)&0xFF;
  //Short src addr
  packet[8] = (ST_RadioGetNodeId()>>0)&0xFF;
  packet[9] = (ST_RadioGetNodeId()>>8)&0xFF;
  //payload type
  packet[10] = PT_GENERIC_DATA;
  //my VDD_PADS
  packet[11] = (vddMillivolts>>0)&0xFF;
  packet[12] = (vddMillivolts>>8)&0xFF;
  //Zero out the TX SFD payload.  The MSB is used to indicate SFD valid.
  packet[13] = 0;
  packet[14] = 0;
  packet[15] = 0;
  
  enqueueTxPacket(sendDirectly, dstShortAddr, packet, 13);
}


//This function is indirectly invoked by the command 's' to allow the user
//to select which planet a sun should send a data packet to.
boolean selectPlanetFromTable(u16 * dstShortAddr)
{
  u8 entry;
  u8 i, k;
  
  printf("Select an entry number from the (active) planet list:\r\n");
  printf("Entry | Short Address |    Long Address\r\n");
  for(i=0;i<PLANET_TABLE_SIZE;i++) {
    if(planetTable[i].active) {
      printf("   %d  | ", i);
      printf("    0x%04X    | 0x", planetTable[i].shortAddr);
      k=8;
      while(k--) {
        printf("%02X", planetTable[i].longAddr[k]);
      }
      printf("\r\n");
    }
  }
  entry = getInt8uFromUser();
  
  if(entry>=PLANET_TABLE_SIZE) {
    printf("Chosen number outside of planet table scope\r\n");
    return FALSE;
  }
  if(!planetTable[entry].active) {
    printf("Chosen number is not an active planet\r\n");
    return FALSE;
  }
  
  *dstShortAddr = planetTable[entry].shortAddr;
  
  return TRUE;
}


//This function is indirectly invoked by the command 's' to implement
//sending data on a sun node.
void sunSendCmd(boolean autoSend)
{
  u16 vddMillivolts = halMeasureVdd(ADC_SAMPLE_CLOCKS_512);
  u16 dstShortAddr=autoSendRateDstShortAddr;
  
  if(!autoSend) {
    printf("Send my VDD measurement (%d mV) to a planet...\r\n",
           vddMillivolts);
    
    if(!selectPlanetFromTable(&dstShortAddr)) {
      return;
    }
    
    printf("Sending indirectly to sleepy planet 0x%04X (waiting for poll...)\r\n",
           dstShortAddr);
  }
  
  sendVddDataPacket(vddMillivolts, dstShortAddr, FALSE);
}


//This function is indirectly invoked by the command 's' to implement
//sending data on a planet node.
void planetSendCmd(boolean autoSend)
{
  u16 vddMillivolts = halMeasureVdd(ADC_SAMPLE_CLOCKS_512);
  //A planet only sends to the sun which is always short address 0x0000
  u16 dstShortAddr=0x0000;
  
  if(!autoSend) {
    printf("Sending my VDD measurement (%d mV) to sun (0x0000)\r\n",
           vddMillivolts);
  }
  
  sendVddDataPacket(vddMillivolts, dstShortAddr, TRUE);
}


//Command invoked with 's'.  Send a data packet.  In addition to being
//invoked manually by the user, this function can be called due to
//periodic auotmatic send events, controlled by the rate command.
void sendCmd(boolean autoSend)
{
  if(!autoSend) {
    printf("\r\n");
    if(!activeInNetwork) {
      printf("Not active in a network\r\n");
      return;
    }
  }
  if(ST_RadioGetNodeId() == 0x0000) {
    sunSendCmd(autoSend);
    return;
  } else {
    planetSendCmd(autoSend);
  }
}


//Command invoked with 'c'.  Clear the indirect transmission queue.
void clearQCmd(void)
{
  printf("\r\n");
  if(!activeInNetwork) {
    printf("Not active in a network\r\n");
    return;
  }
  if(ST_RadioGetNodeId() != 0x0000) {
    printf("Only the sun has an indirect transmit queue\r\n");
    return;
  }
  
  printf("Clearing indirect transmit queue\r\n");
  clearIndirectQueue();
}


//Command invoked with 'p'.  Poll for a data packet.  In addition to being
//invoked manually by the user, this function can be called due to
//periodic auotmatic poll events, controlled by the rate command.
void pollCmd(boolean autoPoll)
{
  u8 packet[128];
  //polls are always sent to the sun
  u16 dstShortAddr = 0x0000;
  
  if(!autoPoll) {
    printf("\r\n");
    if(!activeInNetwork) {
      printf("Not active in a network\r\n");
      return;
    }
    if(ST_RadioGetNodeId() == 0x0000) {
      printf("Only a planet can poll\r\n");
      return;
    }
    
    printf("Sending poll packet to sun\r\n");
  }
  
  //Length
  packet[0] = (10+2);
  packet[1] = FCF_MACCMD + FCF_ACKREQ + FCF_INTRAPAN;
  packet[2] = FCF_SHORTDST + FCF_SHORTSRC;
  //New sequence number
  currSeqNum++;
  packet[3] = currSeqNum;
  //dst PAN ID
  packet[4] = (ST_RadioGetPanId()>>0)&0xFF;
  packet[5] = (ST_RadioGetPanId()>>8)&0xFF;
  //Short dst addr
  packet[6] = (dstShortAddr>>0)&0xFF;
  packet[7] = (dstShortAddr>>8)&0xFF;
  //Short src addr
  packet[8] = (ST_RadioGetNodeId()>>0)&0xFF;
  packet[9] = (ST_RadioGetNodeId()>>8)&0xFF;
  //payload type
  packet[10] = PT_POLLING;
  
  enqueueTxPacket(TRUE, dstShortAddr, packet, 0);
}


//Command invoked with 'r'.  Define the rate of periodic automatic send and
//poll events.  This function implements a sub-menu to determine which
//event the user wants to control and obtain the new rate value.
void rateCmd(void)
{
  int ch;
  
  printf("\r\n");
  if(!activeInNetwork) {
    printf("Not active in a network\r\n");
    return;
  }
  
  if(ST_RadioGetNodeId() == 0x0000) {
    autoSendRate = 0;
    if(!selectPlanetFromTable(&autoSendRateDstShortAddr)) {
      printf("Send rate is now %d qs\r\n", autoSendRate);
      return;
    }
    printf("Set send rate in quarterseconds.  rate=0 is off.  255 max.\r\n");
    autoSendRate = getInt8uFromUser();
    printf("Send rate is now %d qs\r\n", autoSendRate);
    //Put the last tick in the past so it immediately triggers a new event
    autoSendLastQsTick = (u16)
      ((u16)halCommonGetInt16uQuarterSecondTick() - (u16)autoSendRate);
    return;
  }
  
  printf("Enter 's' to adjust send rate or 'p' to adjust poll rate: ");
  do {
    halResetWatchdog();
    processRxPacket();
    txTick();
    ch=getchar();
  } while(ch!='s' && ch!='p');
  printf("\r\n");
  switch(ch) {
    case 's':
      autoSendRate = 0;
      autoSendRateDstShortAddr = 0x0000; //Planet always sends to sun
      printf("Set send rate in quarterseconds.  rate=0 is off.  255 max.\r\n");
      autoSendRate = getInt8uFromUser();
      printf("Send rate is now %d qs\r\n", autoSendRate);
      //Put the last tick in the past so it immediately triggers a new event
      autoSendLastQsTick = (u16)
        ((u16)halCommonGetInt16uQuarterSecondTick() - (u16)autoSendRate);
      return;
    case 'p':
      autoPollRate = 0;
      printf("Set poll rate in quarterseconds.  rate=0 is off.  255 max.\r\n");
      autoPollRate = getInt8uFromUser();
      printf("Poll rate is now %d qs\r\n", autoPollRate);
      //Put the last tick in the past so it immediately triggers a new event
      autoPollLastQsTick = (u16)
        ((u16)halCommonGetInt16uQuarterSecondTick() - (u16)autoPollRate);
      return;
  }
}


//Command invoked with 'p'.  Print the planet table.
void planetTableCmd(void)
{
  u8 i,k;
  
  printf("\r\n");
  if(!activeInNetwork) {
    printf("Not active in a network\r\n");
    return;
  }
  if(ST_RadioGetNodeId() != 0x0000) {
    printf("Not a sun\r\n");
    return;
  }
  
  printf("Planet Table\r\n");
  printf("Active | DataPending | Short Address |    Long Address\r\n");
  for(i=0;i<PLANET_TABLE_SIZE;i++) {

    printf("   %d   | ", planetTable[i].active);
    printf("      %d     | ", isDataPendingForShortId(planetTable[i].shortAddr));
    printf("    0x%04X    | 0x", planetTable[i].shortAddr);
    k=8;
    while(k--) {
      printf("%02X", planetTable[i].longAddr[k]);
    }
    printf("\r\n");
  }
}


//Command invoked with 'h'.  Print the help menu.
void helpCmd(void)
{
  printf("\r\n");
  printf("CMD Description  (compatible roles)\r\n");
  printf("i   Display status information  (both)\r\n");
#ifdef SUN_ROLE
  printf("f   Form a network  (make inactive node a sun)\r\n");
#endif
#ifdef PLANET_ROLE
  printf("j   Join a network  (make inactive node a planet)\r\n");
#endif
  printf("l   Leave a network  (both)\r\n");
  printf("s   Send data  (both)\r\n");
#ifdef SUN_ROLE
  printf("c   Clear indirect transmit queue  (sun only)\r\n");
#endif
#ifdef PLANET_ROLE
  printf("p   Poll for data  (planet only)\r\n");
#endif
  printf("r   Adjust send/poll rates  (both)\r\n");
#ifdef SUN_ROLE
  printf("t   Display the planet table  (sun only)\r\n");
#endif
  //#ifdef PLANET_ROLE
  printf("o   Enter OTA bootloader mode \r\n");
  printf("u   Enter Uart bootloader mode \r\n");
  //#endif
  printf("?   Display this help menu\r\n");
}


//******************************************************************************
// Application main:  Entry point, initialization, command line implementation,
// and event control.

int main(void)
{
  u8 ch;
  u32 seed;
  u16 currQsTick=0;
  u16 lastPeriodicEventsQsTick;
  StStatus status = ST_SUCCESS;

  //Initialize the HAL.
  halInit();
  
  //Initialize the UART.  uartInit will configure PB1=OUT_ALT and PB2=IN.
  uartInit(115200, 8, PARITY_NONE, 1);
  
  //Connect IRQD to PB2/SC1RXD
  GPIO_IRQDSEL = PORTB_PIN(2);
  //Allow the IRQD flag to set on any IRQD activity.  This does not
  //enable the top level interrupt since no interrupt is desired; just
  //an activity flag is needed to know when to avoid deep sleep.
  GPIO_INTCFGD = (3<<GPIO_INTMOD_BIT);
  INT_GPIOFLAG = INT_IRQDFLAG;
  INT_PENDCLR = INT_IRQD;
  
  lastPeriodicEventsQsTick = halCommonGetInt16uQuarterSecondTick();
  
  INTERRUPTS_ON();

#ifdef PLANET_ROLE
  printf("\r\nSimpleMAC (%s) Sample Application: 'Planet role'!\r\n",SIMPLEMAC_VERSION_STRING);
#endif
  
#ifdef SUN_ROLE
  printf("\r\nSimpleMAC (%s) Sample Application: 'Sun role'!\r\n",SIMPLEMAC_VERSION_STRING);
#endif
  
  //Initialize random number generation.
  ST_RadioGetRandomNumbers((u16 *)&seed, 2);
  halCommonSeedRandom(seed);
  
  //Initialize the radio.
  ST_RadioEnableOverflowNotification(TRUE);
  status = ST_RadioInit(radioPowerState);
  assert(status==ST_SUCCESS);  
  
  printf("Enter ? for list of commands\r\n");
  
  while(TRUE) {
    printf("\r\n> ");
    
    do {
      halResetWatchdog();
      processRxPacket();
      txTick();
      currQsTick = halCommonGetInt16uQuarterSecondTick();
      //Run periodic poll event
      if(autoPollRate > 0) {
        if(elapsedTimeInt16u(autoPollLastQsTick, currQsTick)>autoPollRate) {
          autoPollLastQsTick = currQsTick;
          MAIN_DETAILS(printf("Automatic poll\r\n");)
          pollCmd(TRUE);
        }
      }
      //Run periodic send event
      if(autoSendRate > 0) {
        if(elapsedTimeInt16u(autoSendLastQsTick, currQsTick)>autoSendRate) {
          autoSendLastQsTick = currQsTick;
          MAIN_DETAILS(printf("Automatic send\r\n");)
          sendCmd(TRUE);
        }
      }
      //Calculate events and attempt to sleep.  (tryToSleep will not do
      //anything on a sun.)
      {
        u32 qsToNextEvent=0xFFFFFFFF;
        u16 now = halCommonGetInt16uQuarterSecondTick();
        if(autoPollRate>0) {
          u16 qsDelta;
          if(timeGTorEqualInt16u(now, (autoPollLastQsTick+autoPollRate))) {
            qsToNextEvent=0;
          } else {
            qsDelta = elapsedTimeInt16u(now,(autoPollLastQsTick+autoPollRate));
            qsToNextEvent = (qsDelta < qsToNextEvent) ? qsDelta : qsToNextEvent;
          }
        }
        if(autoSendRate>0) {
          u16 qsDelta;
          if(timeGTorEqualInt16u(now, (autoSendLastQsTick+autoSendRate))) {
            qsToNextEvent=0;
          } else {
            qsDelta = elapsedTimeInt16u(now,(autoSendLastQsTick+autoSendRate));
            qsToNextEvent = (qsDelta < qsToNextEvent) ? qsDelta : qsToNextEvent;
          }
        }
        //If there are no timed events, qsToNextEvent is maximally large,
        //which is 34 years.  That should be long enough.
        
        if(framePendingPktEnroute) {
          //If framePending got set, stay awake for 200ms giving plenty
          //of time for packet(s) to come in.
          if(elapsedTimeInt16u(framePendingMsTick,
                               halCommonGetInt16uMillisecondTick())>200) {
            framePendingPktEnroute = FALSE;
          }
        } else{
          //Only sleep if qsToNextEvent says there an event is coming up.  If
          //qsToNextEvent is 0, halSleepForQsWithOptions() will immediately
          //return.  This is not a problem except for the fact that tryToSleep()
          //prints status and would fill the screen with extraneous
          //messages.
          //NOTE: If there is no upcoming events, qsToNextEvent will
          //      be set to 0xFFFFFFFF so we will enter sleep and only
          //      wake on non-timed events.
          if(qsToNextEvent>0) {
            tryToSleep(qsToNextEvent);
          }
        }
      }
      //Run periodic maintenance events
      if(elapsedTimeInt16u(lastPeriodicEventsQsTick, currQsTick) >
         PERIODIC_MAINTENANCE_EVENTS_RATE) {
        MAIN_DETAILS(printf("Periodic maintenance events\r\n");)
        if(ST_RadioCheckRadio()) {
          ST_RadioCalibrateCurrentChannel();
        }
        halCommonCheckXtalBiasTrim();
        halCommonCalibratePads();
        lastPeriodicEventsQsTick = halCommonGetInt16uQuarterSecondTick();
      }
#ifdef SUN_ROLE
    } while ((!__io_getcharNonBlocking(&ch)));
#endif
#ifdef PLANET_ROLE
      if (halGetButtonStatus(BUTTON_S1) == BUTTON_PRESSED)
        planet_join_by_button = 1;
      
    } while ((!__io_getcharNonBlocking(&ch)) && (!planet_join_by_button));
    
    if (planet_join_by_button)
    {
      planet_join_by_button = 0;
      joinCmd();
    }
    else /* do switch */
#endif 
            
    switch(ch) {
      case 'i':
        infoCmd();
        break;
#ifdef SUN_ROLE
      case 'f':
        formCmd();
        break;
#endif
#ifdef PLANET_ROLE
      case 'j':
        joinCmd();
        break;
#endif
      case 'l':
        leaveCmd();
        break;
      case 's':
        sendCmd(FALSE);
        break;
#ifdef SUN_ROLE
      case 'c':
        clearQCmd();
        break;
#endif
#ifdef PLANET_ROLE
      case 'p':
        pollCmd(FALSE);
        break;
#endif
      case 'r':
        rateCmd();
        break;
#ifdef SUN_ROLE
      case 't':
        planetTableCmd();
        break;
#endif
	//#ifdef PLANET_ROLE
      case 'o':
	printf ("Entering OTA bootloader mode ...\r\n");
	fflush(stdout);
        halBootloaderStart(BOOTLOADER_MODE_OTA, IAP_BOOTLOADER_DEFAULT_CHANNEL, IAP_BOOTLOADER_PAN_ID);
	printf ("Node does not contain IAP bootloader\r\n");
        break;

      case 'u':
	printf ("Entering Uart bootloader mode ...\r\n");
	fflush(stdout);
        halBootloaderStart(BOOTLOADER_MODE_UART, IAP_BOOTLOADER_DEFAULT_CHANNEL, IAP_BOOTLOADER_PAN_ID);
	printf ("Node does not contain IAP bootloader\r\n");
        break;
	//#endif
      case '?':
        helpCmd();
        break;
      default:
        printf("Unknown Command\r\n");
        break;
      case '\r':
      case '\n':
        //ignored
        break;
    }
    //After a command is executed, we're allowed to go back to sleep so
    //clear out the UART activity flag.  If there is packet or event
    //activity, it will independently keep us awake as needed.
    INT_GPIOFLAG = INT_IRQDFLAG;
    INT_PENDCLR = INT_IRQD;
  }
  
}


//******************************************************************************
//The MAC Timer compare functionality is not used in this app.
void ST_RadioMacTimerCompareIsrCallback(void) {}

/** \endcond
 */
