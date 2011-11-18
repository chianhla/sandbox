/**
* @file  bootloader_demo.c
* @brief   Demo about over the air (OTA) ST bootloader protocol (see AN3262 )
 * <!-- Copyright 2011 by STMicroelectronics.  All rights reserved.       *80*-->

* \section IAR_project IAR project
  To use the project with IAR Embedded Workbench for ARM, please follow the instructions below:
  -# Open the IAR Embedded Workbench for ARM.
  -# From the File->Open->Workspace menu, open the IAR workspace
     <tt> ...\\simplemac\\demos\\bootloader_demo\\EWARMv5\\bootloader_demo.eww  </tt>
  -# Select desired configuration to build
  -# Select Project->Rebuild All. This will recompile and link the entire application
  -# To launch a debug session, please connect IAR Jlink to JTAG connector (P1) in your board.
  -# Select Project->Download and Debug. The related binary image
     is downloaded into the STM32W108xx Flash memory and interactive debug session is stared.
  -# Connect the application board to a PC USB port. Open a hyperterminal on the
     corresponding USB virtual COMx port with the configuration as described in \ref Serial_IO.

* \subsection IAR_project_configurations IAR project configurations

  \li \c STM32W108xB - STM32W108xB configuration
  \li \c STM32W108CC - STM32W108CC configuration

* \section Atollic_project Atollic project
  To use the project with Atollic TrueStudio, please follow the instructions below:
  -# Open Atollic TrueStudio and select a workspace of your choice
  -# From File->Import, select General/Existing Projects into Workspace and click Next
  -# Browse for root directory and select the path: <tt> ...\\simplemac\\demos\\bootloader_demo\\TrueStudio </tt>
  -# Select the project bootloader_demo and click Finish
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

  \li \c STM32W108xB - STM32W108xB configuration
  \li \c STM32W108CC - STM32W108CC configuration

* \section Prebuilt_images Prebuilt images
  \li <tt> ...\\prebuilt\\STM32W108xB\\bootloader_demo.s37 </tt> Prebuilt version
  \li <tt> ...\\prebuilt\\STM32W108CC\\bootloader_demo.s37 </tt> Prebuilt version

* \section Jumper_settings Jumper settings
@table
----------------------------------------------
| Jumper name       | STM32W108xB            | 
----------------------------------------------
| JP1, if available | Don't care             | 
| P1, if available  | 5-6 (USB)              | 
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
  The application will listen for commands sent over the serial port with the following settings:
@table
| Parameter name  | Value          | Unit        |
--------------------------------------------------
| Baudrate        | 115200         | bit/sec     |
| Data bits       | 8              | bit         |
| Parity          | None           | bit         |
| Stop bits       | 1              | bit         |
@endtable
  
The list of supported commands is as follow:
@table
| Command name     | Command parameters         | Description                                                                              |
--------------------------------------------------------------------------------------------------------------------------------------------
| loadImage        |None                        | Find first node in bootlader mode  and load test image to it                             |
| findBLNodes      |None                        | Return the list of nodes in bootloader mode in the radio range                           |
| setDestEui64     |\a eui64                    | Set the destination EUI64 for bootloader commands                                        |
| getDestEui64     |None                        | Return the currently used EUI64 for bootloader commands                                  |
| get              |None                        | GET command (see AN3262)                                                                 |
| bget             |None                        | GET command broadcast (see AN3262)                                                       |
| getid            |None                        | GET_ID command (see AN3262)                                                              |
| bgetid           |None                        | GET_ID command broadcast (see AN3262)                                                    |
| getversion       |None                        | GET_VERSION command (see AN3262)                                                         |
| bgetversion      |None                        | GET_VERSION command braodcast (see AN3262)                                               |
| read             |\a address \a bytes         | READ command: read \a bytes of memory from \a address (see AN3262)                       |
| write            |\a address \a bytes \a data | WRITE command: write  \a bytes of \a data to  memory \a address (see AN3262)             |
| writeIncremental |\a bytes \a data            | WRITE_INCREMENTAL command: write  \a bytes of \a data to next memory address (see AN3262)|
| erase            |\a pages \a page_list       | ERASE command: erase a list of pages in flash (see AN3262)                               |
| go               |\a address                  | GO command: Jump to \a address (see AN3262)                                              |
| help             | None                       | List commands                                                                            |
@endtable
\li \a eui64 format is is hex array (e.g. {0080E10200000798})
\li \a address format is decimal number or hex number (e.g 0xaabbccdd)
\li \a bytes format is decimal number or hex number
\li \a data format is is hex array (e.g. {aabbccddeeff0011})
\li \a pages is decimal number or hex number
\li \a page_list is hex array (e.g. {11121314})

* \section LEDs_description LEDs description
@table
| LED name  | STM32W108xB |
---------------------------
| D1        | Not used    |
| D3        | Not used    |
@endtable

\section Buttons_description Buttons description
@table
| Button name      | STM32W108xB  |
-----------------------------------
| S1               | Not used     |
| S2, if available | Not used     |
| S3, if available | Not used     |
| S4, if available | Not used     |
| S5, if available | Not used     |
@endtable

\section Usage Usage
The bootloader demo show how to use the bootloader OTA commands described in AN 3262. 
It also show how to load a simple test image to a node in OTA bootloader mode.
Step by step instructions are as follow:
-# Load a first board with iap bootloader application, that is: <tt> stm32w_flasher.exe -p COMxx -m -f -r ...\\prebuilt\\iap_booloader.s37 </tt>
-# Load the bootloader application on a second board, that is: <tt> stm32w_flasher.exe -p COMyy -f -r booloader_demo.s37 </tt>
-# Open an terminal on port COMyy and run the command \c loadImage
-# Open an terminal on port COMxx and verify that the test application is now present.

\note Notes and limitations
\li User is requested to set the destination EUI64 addres (setDestEui64 b eui64) before being able to raise all the other supported commands, except loadImage which will find the node by itself. 
\li If the loadImage command fails, user is requested to put the destination device in bootloader mode and repeat the command (no recovery mechanism is supported currently). 
\li The iap_bootloader.s37 image can be also built through the iap_bootloader IAR project. 
  
**/
/** @addtogroup demos
 * Bootloader demo \see bootloader_demo.c for documentation.
 *
 *@{
 */

/** @} */
/** \cond DOXYGEN_SHOULD_SKIP_THIS
 */

#include PLATFORM_HEADER
#include BOARD_HEADER
#include <stdio.h>
#include <string.h>
#include "error.h"
#include "hal/hal.h"
#include "serial_utils.h"
#include "command-interpreter2.h"
#include "phy-library.h"
#include "image.h"
#include "image256K.h"
#include "bl.h"
#include "timer.h"
#include "micro/cortexm3/iap_bootloader.h"

#define MAC_ACK_RETRIES 3
#define TX_BUFFER(a) (txBufferControl.broadcast ? (txBroadcastBuffer.a) : (txBuffer.a))
#define TX_BUFFER_GET_POINTER(a) (txBufferControl.broadcast ? (&txBroadcastBuffer.a) : (&txBuffer.a))

typedef u8 IEEEAddr[8];

enum txStatus {
  TX_SUCCESS = 0,
  TX_PENDING = 1,
  TX_FAILED = 2
};

typedef struct txBufferControlTypeStruct {
  u8 payload[128];
  u8 broadcast;
  u8 retryNumber;
  u8 retries;
  volatile u8 status;
  u8 pointer;
  u8 sequenceCounter;
} txBufferControlType;

#pragma pack(1)
typedef struct txBufferTypeStruct {
  u8 length;
  u16 fc;
  u8 seqNo;
  u16 dstPanID;
  IEEEAddr destEui64;
  IEEEAddr srcEui64;
  u8 payload[128];
} txBufferType;
typedef struct txBroadcastBufferTypeStruct {
  u8 length;
  u16 fc;
  u8 seqNo;
  u16 dstPanID;
  u16 dstShortAddr;
  u16 srcPanID;
  IEEEAddr srcEui64;
  u8 payload[128];
} txBroadcastBufferType;
typedef struct rxBufferTypeStruct {
  u8 length;
  u16 fc;
  u8 seqNo;
  u16 dstPanID;
  IEEEAddr destEui64;
  IEEEAddr srcEui64;
  u8 payload[128];
  u16 lastSequenceNumber;
  u8 packetReceived;
  u8 payloadLength;
  u8 payloadPointer;
} rxBufferType;
#pragma pack()

ALIGN_VAR(txBufferType txBuffer, 2);
ALIGN_VAR(txBroadcastBufferType txBroadcastBuffer, 2);
rxBufferType rxBuffer;
txBufferControlType txBufferControl;

u8 len;
u8 buff[COMMAND_BUFFER_LENGTH];
u8 currIndex = 0;
u8 serialPort = 1;
u8 interactive;

RadioTransmitConfig radioTransmitConfig = RADIO_TRANSMIT_CONFIG_DEFAULTS;
static const u8 prodId256k[] = {0x01,0x09,0xB0};

extern boolean responsePrintf(const char * formatString, ...);
static u8 transmitByte(u8 *data, u8 lastByte);
static u8 receiveByte(u8 *data);
static void txBufferInit(u8 broadcast);
static void rxBufferInit(void);
u8 findNodesInBootloaderMode (IEEEAddr *eui64, u8 maxEUI64);

static char *commandName(u8 cmdCode)
{
  char *returnValue = "Unknown";
  switch (cmdCode) {
  case GET: returnValue = "GET";
    break;
  case GET_VERSION: returnValue = "GET_VERSION";
    break;
  case GET_ID: returnValue = "GET_ID";
    break;
  case ERASE: returnValue = "ERASE";
    break;
  case WRITE: returnValue = "WRITE";
    break;
  case WRITE_INCREMENTAL: returnValue = "WRITE_INCREMENTAL";
    break;  
  case READ: returnValue = "READ";
    break;
  case GO: returnValue = "GO";
    break;
  default: 
    break;
  }

  return returnValue;
}

boolean processCmdInput (u8 interactive)
{
  if (interactive) {
    // continue calling emberSerialReadPartialLine() until it returns success, indicating a full line has been read 
    if (!serialReadPartialLine((char *)buff, COMMAND_BUFFER_LENGTH, &currIndex)) {
      return FALSE;
    }
    
    len=0;
    //search foward looking for first CR, LF, or NULL to determine length of the string
    while((buff[len]!='\n') && (buff[len] !='\r') && (buff[len]!='\0')) {
      len++;
    }
    buff[len ++] = '\r'; //set the final char to be CR
    buff[len ++] = '\n'; //set the final char to be CR
    
    currIndex = 0;
    return processCommandString(buff, len);
  } else {
    return processCommandInput();
  }
}

void setDestEui64Action (void)
{
  IEEEAddr destEui64;
  copyStringArgument(0, (u8 *) &destEui64, 8, 0);
  { int i; for (i = 7; i >= 0; i--) {
      txBuffer.destEui64[i] = destEui64[7-i];
    }
  }
  responsePrintf("{&N call... OK}\r\n", "SetDestEui64");
}

void getDestEui64Action (void)
{
  responsePrintf("{&N call... OK, ", "getEui64");
  responsePrintf("{%t:","destEui64");
  { int i; for (i = 7; i >= 0; i--) {
      responsePrintf("%x",(txBuffer.destEui64)[i]);
    }
    responsePrintf("}");
  }
  responsePrintf("}\r\n");
}

void loadImageAction (void)
{
  u32 bytesWritten;
  u32 state;
  u32 startTime, totalTime = 0;
  u8  failed = 0;
  u8 found = 0;
  u8 is256K = FALSE;
  imageDescType imageDesc;

  /* Take first node in bootloader mode */
  found = findNodesInBootloaderMode(&txBuffer.destEui64, 1);

  if (found) {

    /* Detect if node is 128K or 256K using the product ID */
    {
      u8 reply[3];
      u8 status;
      status = bootloadCommand(GET_ID, NULL, sizeof(reply), reply);
      
      if ((status == BOOTLOAD_COMMAND_SUCCESS) && (halCommonMemCompare(reply, prodId256k, 3) == 0))
	is256K = TRUE;
    }

    printf ("Loading image on remote node with EUI64(%s): ", is256K ? "256K" : "128K");
    { int i; for (i = 7; i >= 0; i--) {
	printf("%02X",(txBuffer.destEui64)[i]);
      }
    }
    printf ("\r\n");


    txBufferInit(FALSE);
    rxBufferInit();
    if (is256K) {
      imageDesc.imagePtr = image256K;
      imageDesc.imageSize = sizeof(image256K);
      imageDesc.imageOffset = 0;
    } else {
      imageDesc.imagePtr = image;
      imageDesc.imageSize = sizeof(image);
      imageDesc.imageOffset = IAP_BOOTLOADER_APPLICATION_ADDRESS - MFB_BOTTOM;
    }

    blInit(&imageDesc, transmitByte, receiveByte);

    while (TRUE) {
      startTime = TIME_CurrentTime();
      state = blStateMachine(&bytesWritten);
      totalTime += TIME_CurrentTime() - startTime;
      if (state == BL_STATE_FAILURE)
	failed = 1;
      printf ("Written %05u/%05d\r", bytesWritten, sizeof(image));
      TIMER_Tick();
      if (state == BL_STATE_IDLE) {
	printf ("\r\n%s\r\n", failed ? "Failed" : "OK");
	break;
      }
    }
    if (!failed)
      printf ("Total time (not including screen messages) = %u.%06u sec.\r\n", (totalTime)/1000000, (totalTime) % 1000000);
  } else {
    printf ("No nodes found in bootloader mode\r\n");
  }
}
static void cmdExecution(u8 cmdCode, btlCommandArgType *args, u16 replyLength, u8 *reply, u8 broadcast)
{
  u8 status;
  char *command;
  char commandString[64];

  txBufferInit(broadcast);
  rxBufferInit();

  status = bootloadCommand(cmdCode, args, replyLength, reply);

  command = commandName(cmdCode);
  strcpy(commandString, command);
  if (broadcast) {
    strcpy(commandString + strlen(commandString), "(broadcast)");
  }

  responsePrintf("{&N Bootload command... &t2x \r\n", commandString, "status", status);
  responsePrintf("{%t:","reply");
  if (replyLength == 0xFFFF) {
    replyLength = reply[0]+2;
  }
  if (status == BOOTLOAD_COMMAND_SUCCESS)
  {
    u8 i;
    for (i = 0; i < replyLength; i++) {
      responsePrintf("%x", reply[i]);
    }
    responsePrintf ("}");
  }
  responsePrintf ("}\r\n");
}
void getCommandAction(void)
{
  u8 reply[64];

  cmdExecution(GET, NULL, 0xFFFF, reply, FALSE); 
}

void getIdCommandAction(void)
{
  u8 reply[3];

  cmdExecution(GET_ID, NULL, sizeof(reply), reply, FALSE); 
}

void getVersionCommandAction(void)
{
  u8 reply[3];

  cmdExecution(GET_VERSION, NULL, sizeof(reply), reply, FALSE); 
}

void readCommandAction(void)
{
  u8 reply[128];
  u32 address;
  u32 bigEndianAddress;
  u8 bytes;
  btlCommandArgType args[3];  

  address = unsignedCommandArgument(0);
  args[0].length = 4;
  args[0].data = (u8 *) &bigEndianAddress;

  // Address must be sent big endian
  {
    u8 i;
    u8 *addr = (u8 *) &address;
    u8 *BEaddr = (u8 *) &bigEndianAddress;
    for (i = 0; i < 4; i++)
      BEaddr[3-i] = addr[i];
  }

  bytes = unsignedCommandArgument(1) - 1;
  args[1].length = 1;
  args[1].data = &bytes;

  // Terminate args list
  args[2].length = 0;

  cmdExecution(READ, args, bytes + 1, reply, FALSE); 
}
void writeCommandAction(void)
{
  u8 data[128];
  u32 address;
  u32 bigEndianAddress;
  btlCommandArgType args[3];  

  address = unsignedCommandArgument(0);
  args[0].length = 4;
  args[0].data = (u8 *) &bigEndianAddress;

  // Address must be sent big endian
  {
    u8 i;
    u8 *addr = (u8 *) &address;
    u8 *BEaddr = (u8 *) &bigEndianAddress;
    for (i = 0; i < 4; i++)
      BEaddr[3-i] = addr[i];
  }

  data[0] = unsignedCommandArgument(1) - 1;
  copyStringArgument(2, (u8 *) data+1, data[0] + 1, 0);

  args[1].length = data[0] + 2;
  args[1].data = data;

  // Terminate args list
  args[2].length = 0;

  cmdExecution(WRITE, args, 0, NULL, FALSE); 
}

void eraseCommandAction(void)
{
  u8 data[128];
  btlCommandArgType args[2];  

  data[0] = unsignedCommandArgument(0) - 1;
  copyStringArgument(1, (u8 *) data+1, data[0] + 1, 0);

  args[0].length = data[0] + 2;
  args[0].data = data;

  // Terminate args list
  args[1].length = 0;

  cmdExecution(ERASE, args, 0, NULL, FALSE); 
}

void goAddressCommandAction(void)
{
  u32 address = unsignedCommandArgument(0);
  u32 bigEndianAddress;
  btlCommandArgType args[2];  

  args[0].length = 4;
  args[0].data = (u8 *) &bigEndianAddress;
  args[1].length = 0;
  // Address must be sent big endian
  {
    u8 i;
    u8 *addr = (u8 *) &address;
    u8 *BEaddr = (u8 *) &bigEndianAddress;
    for (i = 0; i < 4; i++)
      BEaddr[3-i] = addr[i];
  }
  cmdExecution(GO, args, 0, NULL, FALSE); 
}

void writeIncrementalCommandAction(void)
{
  u8 data[128];
  btlCommandArgType args[2];  

  data[0] = unsignedCommandArgument(0) - 1;
  copyStringArgument(1, (u8 *) data+1, data[0] + 1, 0);

  args[0].length = data[0] + 2;
  args[0].data = data;

  // Terminate args list
  args[1].length = 0;

  cmdExecution(WRITE_INCREMENTAL, args, 0, NULL, FALSE); 
}

void broadcastGetCommandAction(void)
{
  u8 reply[64];

  cmdExecution(GET, NULL, 0xFFFF, reply, TRUE); 
}

void broadcastGetIdCommandAction(void)
{
  u8 reply[3];

  cmdExecution(GET_ID, NULL, sizeof(reply), reply, TRUE); 
}

void broadcastGetVersionCommandAction(void)
{
  u8 reply[3];

  cmdExecution(GET_VERSION, NULL, sizeof(reply), reply, TRUE); 
}

u8 findNodesInBootloaderMode (IEEEAddr *eui64, u8 maxEUI64)
{
  u8 status;
  u8 reply[3];
  u8 count = 0;

  txBufferInit(TRUE);
  rxBufferInit();

  status = bootloadCommand(GET_VERSION, NULL, sizeof(reply), reply);

  if (status == BOOTLOAD_COMMAND_SUCCESS) {
    if (count < maxEUI64) {
	halCommonMemCopy(eui64[count++], &rxBuffer.srcEui64, sizeof(IEEEAddr));
    }
    while (count < maxEUI64) {
      u32 startTime;
      u8 found = FALSE;

      startTime = TIME_CurrentTime();
      while (TIME_ELAPSED(startTime) < 1000000) {
	if (rxBuffer.packetReceived) {
	  halCommonMemCopy(eui64[count++], &rxBuffer.srcEui64, sizeof(IEEEAddr));
	  rxBuffer.packetReceived = FALSE;
	  found = TRUE;
	  break;
	}
      }
      if (! found)
	break;
    }
  }
  return count;
}

void findNodesInBootloaderModeAction (void)
{
  IEEEAddr eui64List[8];
  u8 eui64Count = 0;
  u8 i;

  eui64Count = findNodesInBootloaderMode(eui64List, 
					 sizeof(eui64List) / sizeof (IEEEAddr));
  responsePrintf("{&N Bootload command... &t2x \r\n", "findNodesInBootloaderMode", "count", eui64Count);
  for (i = 0; i < eui64Count; i++) {
    s8 j;
    responsePrintf("{%t_%d:","EUI64", i);
    for (j = 7; j >= 0; j--)
      printf ("%02X", eui64List[i][j]);
    responsePrintf ("}\r\n");
  }
  responsePrintf ("}\r\n");
}

void helpAction(void)
{
  CommandEntry *cmd;

  for (cmd = CommandTable; cmd->name != NULL; cmd++) {
    printf ("%s %s %s\r\n\r\n", cmd->name, cmd->argumentTypes, cmd->description);
  }
}

CommandEntry CommandTable[] = {
  { "setDestEui64", setDestEui64Action, "b",
    "set destination EUI64 for booloader commands\r\n"
    "parameters: eui64"},
  { "getDestEui64", getDestEui64Action, "", ""},
  { "findBLNodes", findNodesInBootloaderModeAction, "", ""},
  { "loadImage", loadImageAction, "", "Find first bootlader node and load test image to it"},
  { "get", getCommandAction, "", "get command"},
  { "bget", broadcastGetCommandAction, "", "get command (broadcast)"},
  { "getid", getIdCommandAction, "", "get id command"},
  { "bgetid", broadcastGetIdCommandAction, "", "get id command (broadcast)"},
  { "getversion", getVersionCommandAction, "", "get version command"},
  { "bgetversion", broadcastGetVersionCommandAction, "", "get version command (broadcast)"},
  { "read", readCommandAction, "wu", 
    "Read memory command\r\n"
    "parameters: address bytes"},
  { "write", writeCommandAction, "wub", 
    "Write memory command\r\n"
    "parameters: address bytes data"},
  { "writeIncremental", writeIncrementalCommandAction, "ub", 
    "Write inc memory command\r\n"
    "parameters: bytes data"},
  { "erase", eraseCommandAction, "ub",
    "Erase memory command\r\n"
    "parameters: pages page_list"},
  { "go", goAddressCommandAction, "w", 
    "Go command\r\n"
    "parameters: address"},
  { "help", helpAction, "", "List commands"},
  { NULL, NULL, NULL, NULL } // NULL action makes this a terminator

};

static u8 transmitByte(u8 *data, u8 lastByte)
{
  u8 returnValue = TX_SUCCESS;

  txBufferControl.payload[txBufferControl.pointer++] = *data;
  if (lastByte) {
    if (txBufferControl.broadcast) {
      txBroadcastBuffer.length = txBufferControl.pointer + 19;
      txBroadcastBuffer.seqNo = txBufferControl.sequenceCounter++;
    } else {
      txBuffer.length = txBufferControl.pointer + 23;
      txBuffer.seqNo  = txBufferControl.sequenceCounter++;
    }
    
    txBufferControl.status = TX_PENDING;
    txBufferControl.retryNumber = 0;
    halCommonMemCopy(TX_BUFFER(payload), txBufferControl.payload, txBufferControl.pointer);

    returnValue = ST_RadioTransmit((u8 *) TX_BUFFER_GET_POINTER(length));
    if (returnValue != TX_SUCCESS) {
      txBufferControl.status = TX_FAILED;
    } 
    
    /* Wait for transmission to complete */
    while (txBufferControl.status == TX_PENDING);

    returnValue = txBufferControl.status;
    txBufferControl.pointer = 0;
  }
  return returnValue;
}

static u8 receiveByte(u8 *data)
{
  u8 returnValue = FALSE;
  if (rxBuffer.packetReceived) {
    *data = rxBuffer.payload[rxBuffer.payloadPointer++];
    if (rxBuffer.payloadPointer >= rxBuffer.payloadLength)
      rxBuffer.packetReceived = FALSE;
    returnValue = TRUE;
  }
  return returnValue;
}
static void txBufferInit(u8 broadcast)
{
  if (broadcast) {
    txBufferControl.broadcast = TRUE;
    txBufferControl.retries = 0;

    txBroadcastBuffer.length = 0;
    txBroadcastBuffer.fc = 0xc801;
    txBroadcastBuffer.dstPanID = 0xFFFF;
    txBroadcastBuffer.dstShortAddr = 0xFFFF;
    txBroadcastBuffer.srcPanID = IAP_BOOTLOADER_PAN_ID;
  } else {
    txBufferControl.broadcast = FALSE;
    txBufferControl.retries =  MAC_ACK_RETRIES;

    txBuffer.length = 0;
    txBuffer.fc = 0xcc61;
    txBuffer.dstPanID = IAP_BOOTLOADER_PAN_ID;
  }

  halCommonMemCopy ((void *) TX_BUFFER(srcEui64), ST_RadioGetEui64(), 8);
  
  txBufferControl.retryNumber = 0;
  txBufferControl.status = TX_SUCCESS;
  txBufferControl.pointer = 0;

}
static void rxBufferInit(void)
{
  halCommonMemSet (&rxBuffer, 0x00, sizeof(rxBuffer));

  rxBuffer.lastSequenceNumber = 0xffff; // Invalid value
}

int main (void)
{
  u8 returnValue;
  u32 seed;

  interactive = 1;

  halInit();
  ST_RadioGetRandomNumbers((u16 *)&seed, 2);
  halCommonSeedRandom(seed);
  uartInit(115200, 8, PARITY_NONE, 1);
  INTERRUPTS_ON();  

  /* Initialize radio (analog section, digital baseband and MAC).
  Leave radio powered up in non-promiscuous rx mode */
  returnValue = ST_RadioInit(ST_RADIO_POWER_MODE_RX_ON);

  assert(returnValue==ST_SUCCESS); 

  TIMER_Init();

  printf("Bootloader demo application\r\n");
  
  responsePrintf("{&N API call... &t2x}\r\n", "halGetResetInfo", "resetInfo", 0);

  txBufferInit(FALSE);
  rxBufferInit();
  blInit(NULL, transmitByte, receiveByte);

  ST_RadioSetPanId(IAP_BOOTLOADER_PAN_ID);
  ST_RadioSetChannel(IAP_BOOTLOADER_DEFAULT_CHANNEL);

  commandReaderInit();

  while(1) {
    // Process input and print prompt if it returns TRUE.
    if (processCmdInput(interactive)) {
      if (interactive) {
	printf(">");
      }
      TIMER_Tick();
    }
  }
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
  rxBufferType *packetReceived = (rxBufferType *) packet;
  /* note this is executed from interupt context */

  /* Copy the packet to a buffer that can be accessed from the main loop;
     don't do the copy if there is already a packet there being processed */
  if ((packetReceived->seqNo != rxBuffer.lastSequenceNumber) &&
      (packetReceived->fc == 0xCC61)) {
    if(rxBuffer.packetReceived == FALSE) {
      halCommonMemCopy(&rxBuffer, packet, packet[0] + 1);
      rxBuffer.packetReceived = TRUE;
      rxBuffer.payloadPointer = 0;
      rxBuffer.payloadLength = rxBuffer.length - 21;
    } else {
      // This should not happen according to the protocol definition
    }
    rxBuffer.lastSequenceNumber = packetReceived->seqNo;
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
  txBufferControl.status = TX_FAILED;
  switch(status) {
    case ST_SUCCESS:
      /* Success for broadcast packets */
      txBufferControl.status = TX_SUCCESS;
      break;
    case ST_PHY_TX_CCA_FAIL:
    case ST_MAC_NO_ACK_RECEIVED:
      if (txBufferControl.retryNumber < txBufferControl.retries) {
	u8 returnValue;
	txBufferControl.retryNumber++;
	txBufferControl.status = TX_PENDING;
	returnValue = ST_RadioTransmit((u8 *) TX_BUFFER_GET_POINTER(length));
	if (returnValue != TX_SUCCESS) {
	  txBufferControl.status = TX_FAILED;
	} 
      }
      break;
    case ST_PHY_ACK_RECEIVED:
      txBufferControl.status = TX_SUCCESS;
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
/** \endcond
 */

