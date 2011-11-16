/*
 * Copyright (c) 2010, STMicroelectronics.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above
 *    copyright notice, this list of conditions and the following
 *    disclaimer in the documentation and/or other materials provided
 *    with the distribution.
 * 3. The name of the author may not be used to endorse or promote
 *    products derived from this software without specific prior
 *    written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * This file is part of the Contiki OS
 *
 * $Id: stm32w-radio.c,v 1.2 2010/10/27 14:05:23 salvopitru Exp $
 */
/*---------------------------------------------------------------------------*/
/**
* \file
*					Machine dependent STM32W radio code.
* \author
*					Salvatore Pitrulli
*/
/*---------------------------------------------------------------------------*/

#include PLATFORM_HEADER
#include "hal/error.h"
#include "hal/hal.h"

#include "contiki.h"

#include "net/mac/frame802154.h"

#include "dev/stm32w-radio.h"
#include "net/netstack.h"

#include "net/packetbuf.h"
#include "net/rime/rimestats.h"
#include "sys/rtimer.h"


#define DEBUG 0
#define LED_RDC 1
#include "dev/leds.h"
#define LED_ACTIVITY 1


#if DEBUG > 0
#include <stdio.h>
#define PRINTF(...) printf(__VA_ARGS__)
#else
#define PRINTF(...) do {} while (0)
#endif

#if LED_ACTIVITY
#define LED_TX_ON() leds_on(LEDS_GREEN)
#define LED_TX_OFF() leds_off(LEDS_GREEN)
//#define LED_RX_ON() leds_on(LEDS_RED)
//#define LED_RX_OFF() leds_off(LEDS_RED)
#define LED_RX_ON()     {                                       \
                                if(LED_RDC == 0){               \
                                  leds_on(LEDS_RED);            \
                                }                               \
                        }
#define LED_RX_OFF()    {                                       \
                                if(LED_RDC == 0){               \
                                  leds_off(LEDS_RED);            \
                                }                               \
                        }
#define LED_RDC_ON()    {                                       \
                                if(LED_RDC == 1){               \
                                  leds_on(LEDS_RED);            \
                                }                               \
                        }
#define LED_RDC_OFF()   {                                       \
                                if(LED_RDC == 1){               \
                                  leds_off(LEDS_RED);            \
                                }                               \
                        }
#else
#define LED_TX_ON()
#define LED_TX_OFF()
#define LED_RX_ON()
#define LED_RX_OFF()
#define LED_RDC_ON()
#define LED_RDC_OFF() 
#endif

#ifndef MAC_RETRIES
#define MAC_RETRIES 0
#endif

#if MAC_RETRIES

 int8_t mac_retries_left;

 #define INIT_RETRY_CNT() (mac_retries_left = packetbuf_attr(PACKETBUF_ATTR_MAX_MAC_TRANSMISSIONS))
 #define DEC_RETRY_CNT() (mac_retries_left--)
 #define RETRY_CNT_GTZ() (mac_retries_left > 0)

#else

 #define INIT_RETRY_CNT()
 #define DEC_RETRY_CNT()
 #define RETRY_CNT_GTZ() 0

#endif

#define RADIO_WAIT_FOR_PACKET_SENT 1
/* If set to 1, a send() returns only after the packet has been transmitted.
  This is necessary if you use the x-mac module, for example. */
#ifndef RADIO_WAIT_FOR_PACKET_SENT
#define RADIO_WAIT_FOR_PACKET_SENT 1
#endif

#define TO_PREV_STATE()       {                                       \
                                if(onoroff == OFF){                   \
				  toff = RTIMER_NOW();	\
                                  ST_RadioSleep();                    \
                                  ENERGEST_OFF(ENERGEST_TYPE_LISTEN); \
                                }                                     \
                              }

const RadioTransmitConfig radioTransmitConfig = {
  TRUE,  // waitForAck;
  FALSE, // checkCca;     // Set to FALSE with low-power MACs.
  0,     // ccaAttemptMax;
  0,     // backoffExponentMin;
  0,     // backoffExponentMax;
  TRUE   // appendCrc;
};

/*
 * The buffers which hold incoming data.
 */
#ifndef RADIO_RXBUFS
#define RADIO_RXBUFS 1
#endif

static uint8_t stm32w_rxbufs[RADIO_RXBUFS][STM32W_MAX_PACKET_LEN+1]; // +1 because of the first byte, which will contain the length of the packet.

#if RADIO_RXBUFS > 1
static volatile int8_t first = -1, last=0;
#else
static const int8_t first=0, last=0;
#endif

#if RADIO_RXBUFS > 1
 #define CLEAN_RXBUFS() do{first = -1; last = 0;}while(0)
 #define RXBUFS_EMPTY() (first == -1)

int RXBUFS_FULL(){

    int8_t first_tmp = first;
    return first_tmp == last;
}

#else /* RADIO_RXBUFS > 1 */
 #define CLEAN_RXBUFS() (stm32w_rxbufs[0][0] = 0)
 #define RXBUFS_EMPTY() (stm32w_rxbufs[0][0] == 0)
 #define RXBUFS_FULL() (stm32w_rxbufs[0][0] != 0)
#endif /* RADIO_RXBUFS > 1 */

static uint8_t __attribute__(( aligned(2) )) stm32w_txbuf[STM32W_MAX_PACKET_LEN+1];
rtimer_clock_t ton, toff;  

#define CLEAN_TXBUF() (stm32w_txbuf[0] = 0)
#define TXBUF_EMPTY() (stm32w_txbuf[0] == 0)

#define CHECKSUM_LEN 2

/*
 * The transceiver state.
 */
#define ON     0
#define OFF    1

#define BUSYWAIT_UNTIL(cond, max_time)                                  \
  do {                                                                  \
    rtimer_clock_t t0;                                                  \
    t0 = RTIMER_NOW();  \
    while(!(cond) && RTIMER_CLOCK_LT(RTIMER_NOW(), t0 + (max_time)));   \
  } while(0)
static volatile uint8_t onoroff = OFF;
static uint8_t receiving_packet = 0;
static s8 last_rssi;
static volatile StStatus last_tx_status;
static volatile can_turn_on;
/*---------------------------------------------------------------------------*/
PROCESS(stm32w_radio_process, "STM32W radio driver");
/*---------------------------------------------------------------------------*/

static int stm32w_radio_init(void);
static int stm32w_radio_prepare(const void *payload, unsigned short payload_len);
static int stm32w_radio_transmit(unsigned short payload_len);
static int stm32w_radio_send(const void *data, unsigned short len);
static int stm32w_radio_read(void *buf, unsigned short bufsize);
static int stm32w_radio_channel_clear(void);
static int stm32w_radio_receiving_packet(void);
static int stm32w_radio_pending_packet(void);
static int stm32w_radio_on(void);
static int stm32w_radio_off(void);

static int add_to_rxbuf(uint8_t * src);
static int read_from_rxbuf(void * dest, unsigned short len);
static volatile rtimer_clock_t t0, t1;
static volatile uint8_t is_transmit_ack;
const struct radio_driver stm32w_radio_driver =
 {
    stm32w_radio_init,
    stm32w_radio_prepare,
    stm32w_radio_transmit,
    stm32w_radio_send,
    stm32w_radio_read,
    stm32w_radio_channel_clear,
    stm32w_radio_receiving_packet,
    stm32w_radio_pending_packet,
    stm32w_radio_on,
    stm32w_radio_off,
  };
static uint8_t locked;
#define GET_LOCK() locked++
static void RELEASE_LOCK(void) {
  if(locked>0)
       locked--;
}
/*---------------------------------------------------------------------------*/
static int stm32w_radio_init(void)
{
  
  // A channel needs also to be setted.
  ST_RadioSetChannel(RF_CHANNEL);
  printf("R SECOND %u\n", RTIMER_SECOND);
  // Initialize radio (analog section, digital baseband and MAC).
  // Leave radio powered up in non-promiscuous rx mode.
  ST_RadioInit(ST_RADIO_POWER_MODE_OFF);
  onoroff = OFF;
  can_turn_on = 1;
  ST_RadioSetNodeId(STM32W_NODE_ID);   // To be deleted.
  ST_RadioSetPanId(IEEE802154_PANID);
  ton = RTIMER_NOW();
  toff = RTIMER_NOW(); 
  CLEAN_RXBUFS();
  CLEAN_TXBUF();
  locked = 0;
  process_start(&stm32w_radio_process, NULL);
  
  return 0;
}
/*---------------------------------------------------------------------------*/
int stm32w_radio_set_channel(u8_t channel)
{
  if (ST_RadioSetChannel(channel) == ST_SUCCESS)
    return 0;
  else
    return 1;
}
/*---------------------------------------------------------------------------*/
static int wait_for_tx(void){
  
  struct timer t;
  
  if(onoroff == ON){
	//printf("stm32w: detected on during ack waiting.\r\n");
  }
  else{
       //printf("stm32w: detected off during ack waiting.\r\n");
       stm32w_radio_on();		
  }
  timer_set(&t, CLOCK_SECOND/100);
  while(!TXBUF_EMPTY()){
    //printf("stm32w: busy checking ack waiting.\r\n");	
    if(timer_expired(&t)){
      //printf("stm32w: tx buffer full no ack.\r\n");
      //CLEAN_TXBUF();	
      return 1;
    }
    /* Put CPU in sleep mode. */
    halSleepWithOptions(SLEEPMODE_IDLE,0);
  }

  //printf("stm32w: tx buffer with ack.\r\n");
  return 0;  
}
/*---------------------------------------------------------------------------*/
static int stm32w_radio_prepare(const void *payload, unsigned short payload_len)
{
    if(payload_len > STM32W_MAX_PACKET_LEN){
        PRINTF("stm32w: payload length=%d is too long.\r\n", payload_len);
        return RADIO_TX_ERR;
    }
    
#if !RADIO_WAIT_FOR_PACKET_SENT
    /* Check if the txbuf is empty.
     *  Wait for a finite time.
     * This sould not occur if we wait for the end of transmission in stm32w_radio_transmit().
    */
    if(wait_for_tx()){
      PRINTF("stm32w: tx buffer full.\r\n");
      return RADIO_TX_ERR;
    }
#endif /* RADIO_WAIT_FOR_PACKET_SENT */
    
    /* Copy to the txbuf. 
     * The first byte must be the packet length.
     */
    CLEAN_TXBUF();    
    memcpy(stm32w_txbuf + 1, payload, payload_len);
    
    return RADIO_TX_OK;
    
}
/*---------------------------------------------------------------------------*/
static int stm32w_radio_transmit(unsigned short payload_len)
{    
    stm32w_txbuf[0] = payload_len + CHECKSUM_LEN;
    
    INIT_RETRY_CNT();
    
    if(onoroff == OFF){
      printf("stm32w: Radio is off, turning it on.\r\n");
      ton = RTIMER_NOW();	
      ST_RadioWake();
      if((ton - toff)<5){
      printf("TIME AFTER OFF ON TO TRANSMIT %lu\n", (signed long)(ton - toff));	
      } 	
      ENERGEST_ON(ENERGEST_TYPE_LISTEN);
    }

#if RADIO_WAIT_FOR_PACKET_SENT
GET_LOCK();
#endif /* RADIO_WAIT_FOR_PACKET_SENT */  
    LED_TX_ON();
    last_tx_status = -1;
    if(ST_RadioTransmit(stm32w_txbuf)==ST_SUCCESS){
        
      ENERGEST_OFF(ENERGEST_TYPE_LISTEN);
      ENERGEST_ON(ENERGEST_TYPE_TRANSMIT);
        
      PRINTF("stm32w: sending %d bytes\r\n", payload_len);
      //printf("stm32w: sending len %d\r\n", stm32w_txbuf[0]); 
      
#if DEBUG > 1
      
      u8_t c=1;
      do {
        printf("%x:",stm32w_txbuf[c]);
        c++;
      } while (c <= stm32w_txbuf[0]-2);
      printf("\r\n");
#endif   
      
#if RADIO_WAIT_FOR_PACKET_SENT
      //printf("ST_-1\r\n");	
      if(wait_for_tx()){
        PRINTF("stm32w: unknown tx error.\r\n");
        printf("stm32w: wait tx\r\n");
        TO_PREV_STATE();
        LED_TX_OFF();
        RELEASE_LOCK();
        return RADIO_TX_NOACK;
      }
      //should wait a while for ST_RadioTransmitCompleteIsrCallback to return the correct status??
      while(last_tx_status==-1)
      {
	  //printf("ST_-1\r\n");	
      }
      //if(last_tx_status == ST_SUCCESS || last_tx_status == ST_PHY_ACK_RECEIVED){
      //  return RADIO_TX_OK;
      //}
      //if(last_tx_status == ST_SUCCESS)
		//printf("ST_SUCCESS\r\n");
      //if(last_tx_status == ST_PHY_ACK_RECEIVED)
		//printf("ST_PHY_ACK_RECEIVED\r\n");	
      //printf("stm32w: status %u\r\n", last_tx_status);
      //printf("ST_%u\r\n", last_tx_status);
      
      if(last_tx_status == ST_SUCCESS || last_tx_status == ST_PHY_ACK_RECEIVED || last_tx_status == ST_MAC_NO_ACK_RECEIVED){
          RELEASE_LOCK();
	  if(last_tx_status == ST_PHY_ACK_RECEIVED){
		return RADIO_TX_OK; //ACK status
          } 
          else if (last_tx_status == ST_MAC_NO_ACK_RECEIVED){
                return RADIO_TX_NOACK; 
          }
          else if (last_tx_status == ST_SUCCESS){
                return 5; 
          } 	
          
      }
      
      LED_TX_OFF();
      RELEASE_LOCK();
      TO_PREV_STATE();
      if (last_tx_status == ST_PHY_TX_CCA_FAIL){
      return 6;
  }
  else if(last_tx_status ==  ST_PHY_TX_UNDERFLOW){
      return 7;
  }
  else {
      return last_tx_status;
  }	
      //return RADIO_TX_ERR;
     
#else /* RADIO_WAIT_FOR_PACKET_SENT */      
       
      //printf("stm32w: no wiat ffor qend %u %u %u ", last_tx_status, ST_SUCCESS, ST_PHY_ACK_RECEIVED ); 
      //printf("\r\n");	 
      TO_PREV_STATE();
      LED_TX_OFF();
      return RADIO_TX_NOACK;    
      
#endif /* RADIO_WAIT_FOR_PACKET_SENT */
      
    }
#if RADIO_WAIT_FOR_PACKET_SENT
RELEASE_LOCK();
#endif /* RADIO_WAIT_FOR_PACKET_SENT */     
    TO_PREV_STATE();
    
    printf("stm32w: transmission never started.\r\n");
    /* TODO: Do we have to retransmit? */
  
    CLEAN_TXBUF();
    LED_TX_OFF();
if (last_tx_status == ST_PHY_TX_CCA_FAIL){
      return 6;
  }
  else if(last_tx_status ==  ST_PHY_TX_UNDERFLOW){
      return 7;
  }
  else {
      return last_tx_status;
  }
  
    //return RADIO_TX_ERR;
   
}
/*---------------------------------------------------------------------------*/
static int stm32w_radio_send(const void *payload, unsigned short payload_len)
{
  if(stm32w_radio_prepare(payload, payload_len) == RADIO_TX_ERR)
    return RADIO_TX_ERR;
  
  return stm32w_radio_transmit(payload_len);
  
}
/*---------------------------------------------------------------------------*/
static int stm32w_radio_channel_clear(void)
{ 
  return ST_RadioChannelIsClear();
}
/*---------------------------------------------------------------------------*/
static int stm32w_radio_receiving_packet(void)
{
  return receiving_packet;
}
/*---------------------------------------------------------------------------*/
static int stm32w_radio_pending_packet(void)
{
  return !RXBUFS_EMPTY();
}
/*---------------------------------------------------------------------------*/
void wait_until_next_on(void)
{
    //BUSYWAIT_UNTIL(0, RTIMER_SECOND / 500); //no on until a waiting time of 250us
    can_turn_on = 1;	
}
static int stm32w_radio_off(void)
{  
  /* Any transmit or receive packets in progress are aborted.
   * Waiting for end of transmission or reception have to be done.
   */
  //rtimer_clock_t t0;                                                  \
     
  //printf("TIME OFF %i\n", (short)t0);
  
  if(locked)
  {
   printf("stm32w: try to off while sending/receving %u.\r\n", locked);
  }
  if(onoroff == ON && !locked && TXBUF_EMPTY()){
    LED_RDC_OFF();
    //BUSYWAIT_UNTIL(!receiving_packet, RTIMER_SECOND / 10);
    can_turn_on = 0;
    //t1 = RTIMER_NOW();
    //printf("TIME OFF %i\n", (short)(t1 - t0));
    toff = RTIMER_NOW(); 
    ST_RadioSleep();
    onoroff = OFF;
    //wait_until_next_on();  
    CLEAN_TXBUF();
    CLEAN_RXBUFS();  
  
    ENERGEST_OFF(ENERGEST_TYPE_LISTEN);
  }
  
  return 1;
}
/*---------------------------------------------------------------------------*/
static int stm32w_radio_on(void)
{ //printf("TIME OFF");
  if(onoroff == OFF){
    //rtimer_clock_t t0;                                                  \
    //t0 = RTIMER_NOW();  
    //printf("TIME ON %i\n", (short)(t0 - t1));
    
    //BUSYWAIT_UNTIL(can_turn_on, RTIMER_SECOND / 100); //no on until a waiting time of 250us
    LED_RDC_ON();
    //t0 = RTIMER_NOW();  
    //printf("TIME ON WITH DECALAGE %i\n", (short)(t0 - t1));
    ton = RTIMER_NOW();	
    ST_RadioWake();
    onoroff = ON;
      if((ton - toff)<5){
      printf("TIME AFTER OFF ON %lu\n", (signed long)(ton - toff));	
      } 
    ENERGEST_ON(ENERGEST_TYPE_LISTEN);
  }
  
  return 1;
}
/*---------------------------------------------------------------------------*/
int stm32w_radio_is_on(void)
{
  return onoroff == ON;
}
/*---------------------------------------------------------------------------*/


void ST_RadioReceiveIsrCallback(int8u *packet,
                                         boolean ackFramePendingSet,
                                         u32 time,
                                         u16 errors,
                                         s8 rssi)
{ 
  
  LED_RX_ON();
  //wait for ACK transmit
  //BUSYWAIT_UNTIL(0, RTIMER_SECOND / 1500);
  receiving_packet = 0;
  //RELEASE_LOCK();
  /* Copy packet into the buffer. It is better to do this here. */
  if(add_to_rxbuf(packet)){
    process_poll(&stm32w_radio_process);
    last_rssi = rssi;
  }
  //rtimer_clock_t wt;
  //wt = RTIMER_NOW();
  //while(RTIMER_CLOCK_LT(RTIMER_NOW(), wt + 11)) { 
	//halSleepWithOptions(SLEEPMODE_IDLE,0);
  //}
  LED_RX_OFF();
  GET_LOCK();
  is_transmit_ack = 1;
  //printf("Wait ack sending\n");
  BUSYWAIT_UNTIL(!is_transmit_ack, RTIMER_SECOND / 1500);
  //printf("ACK sent\n");
  RELEASE_LOCK();
  
}

void ST_RadioTxAckIsrCallback (void)
{	is_transmit_ack = 0;
	//RELEASE_LOCK();
printf("TIME OFF \n");

}

void ST_RadioTransmitCompleteIsrCallback(StStatus status,
                                           u32 txSyncTime,
                                           boolean framePending)
{

  ENERGEST_OFF(ENERGEST_TYPE_TRANSMIT); 
  ENERGEST_ON(ENERGEST_TYPE_LISTEN);
  LED_TX_OFF();
  
  if(status == ST_SUCCESS || status == ST_PHY_ACK_RECEIVED){
  //if(status == ST_PHY_ACK_RECEIVED){
      
      CLEAN_TXBUF();
  }
  else {

      if(RETRY_CNT_GTZ()){
          // Retransmission
          LED_TX_ON();
          if(ST_RadioTransmit(stm32w_txbuf)==ST_SUCCESS){
              
              ENERGEST_OFF(ENERGEST_TYPE_LISTEN);
              ENERGEST_ON(ENERGEST_TYPE_TRANSMIT);
               
              PRINTF("stm32w: retransmission.\r\n");
              
              DEC_RETRY_CNT();
          }
          else {
              CLEAN_TXBUF();
              LED_TX_OFF();
              PRINTF("stm32w: retransmission failed.\r\n");
          }
      }
      else {
          CLEAN_TXBUF();
      }      
  }
  last_tx_status = status;
  /* Debug outputs. */
  if(status == ST_SUCCESS || status == ST_PHY_ACK_RECEIVED){
      PRINTF("TX_END");
      if(status == ST_PHY_ACK_RECEIVED)
	{
           PRINTF("PHY_ACK_RECEIVED!!! %i\n", status);
   }	
  }
  else if (status == ST_MAC_NO_ACK_RECEIVED){
      PRINTF("TX_END_NOACK!!!");
  }
  else if (status == ST_PHY_TX_CCA_FAIL){
      PRINTF("TX_END_CCA!!!");
  }
  else if(status == ST_PHY_TX_UNDERFLOW){
      PRINTF("TX_END_UFL!!!");
  }
  else {
      PRINTF("TX_END_INCOMPL!!!");
  }
}


boolean ST_RadioDataPendingShortIdIsrCallback(u16 shortId) {
  printf("Short!!!");
  GET_LOCK();
  receiving_packet = 1;
  return FALSE;
}

boolean ST_RadioDataPendingLongIdIsrCallback(u8* longId) {
  //printf("Long!!!");
  //GET_LOCK();
  receiving_packet = 1;
  return FALSE;
}
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(stm32w_radio_process, ev, data)
{
  int len;
  
  PROCESS_BEGIN();

  PRINTF("stm32w_radio_process: started\r\n");
  
  while(1) {
    
    PROCESS_YIELD_UNTIL(ev == PROCESS_EVENT_POLL);    
    
    //PRINTF("stm32w_radio_process: calling receiver callback\r\n");

    //printf("stm32w_radio_process: received packet len %u \r\n", stm32w_rxbufs[0][0]);
    if(stm32w_rxbufs[0][0]-2 < 10)
    {

        //printf("stm32w_radio_process: ACK detected %u\r\n", stm32w_rxbufs[0][0]);
    }
#if DEBUG > 1
    printf("stm32w_radio_process: received packet len %u \r\n", stm32w_rxbufs[0][0]);
    u8_t c=1;
    do {	
      printf("%x",stm32w_rxbufs[0][c]);
      c++;
    } while (c <= stm32w_rxbufs[0][0]);
    printf("\r\n");
#endif
    
    packetbuf_clear();
    len = stm32w_radio_read(packetbuf_dataptr(), PACKETBUF_SIZE);
    if(len > 0) {
      packetbuf_set_datalen(len);   
      NETSTACK_RDC.input();
    }
    if(!RXBUFS_EMPTY()){
      // Some data packet still in rx buffer (this happens because process_poll doesn't queue requests),
      // so stm32w_radio_process need to be called again.
      process_poll(&stm32w_radio_process);
    }
  }

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
static int stm32w_radio_read(void *buf, unsigned short bufsize)
{  
  return read_from_rxbuf(buf,bufsize);  
}

/*---------------------------------------------------------------------------*/
void ST_RadioOverflowIsrCallback(void)
{
  PRINTF("OVERFLOW\r\n");
}
/*---------------------------------------------------------------------------*/
void ST_RadioSfdSentIsrCallback(u32 sfdSentTime)
{
}
/*---------------------------------------------------------------------------*/
void ST_RadioMacTimerCompareIsrCallback(void)
{
}
/*---------------------------------------------------------------------------*/
static int add_to_rxbuf(uint8_t * src)
{
    if(RXBUFS_FULL()){
        return 0;
    } 
    
    memcpy(stm32w_rxbufs[last], src, src[0] + 1);
#if RADIO_RXBUFS > 1
    last = (last + 1) % RADIO_RXBUFS; 
    if(first == -1){
        first = 0;
    }
#endif
    
    return 1;
}
/*---------------------------------------------------------------------------*/
static int read_from_rxbuf(void * dest, unsigned short len)
{
    
    if(RXBUFS_EMPTY()){ // Buffers are all empty
        return 0;
    }        
    
    if(stm32w_rxbufs[first][0] > len){  // Too large packet for dest.
        len = 0;
    }
    else {        
        len = stm32w_rxbufs[first][0];            
        memcpy(dest,stm32w_rxbufs[first]+1,len);
        packetbuf_set_attr(PACKETBUF_ATTR_RSSI, last_rssi);
    }
    
#if RADIO_RXBUFS > 1    
    ATOMIC(
           first = (first + 1) % RADIO_RXBUFS;
           int first_tmp = first;
           if(first_tmp == last){
               CLEAN_RXBUFS();
           }
    )
#else
    CLEAN_RXBUFS();
#endif
    
    return len;
}
/*---------------------------------------------------------------------------*/
short last_packet_rssi(){
    return last_rssi;
}

