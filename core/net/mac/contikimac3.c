/*
 * Copyright (c) 2010, Swedish Institute of Computer Science.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * This file is part of the Contiki operating system.
 *
 * $Id: contikimac.c,v 1.48 2011/01/25 14:29:46 adamdunkels Exp $
 */

/**
 * \file
 *         Implementation of the ContikiMAC power-saving radio duty cycling protocol
 * \author
 *         Adam Dunkels <adam@sics.se>
 *         Niclas Finne <nfi@sics.se>
 *         Joakim Eriksson <joakime@sics.se>
 */

#include "contiki-conf.h"
#include "dev/leds.h"
#include "dev/radio.h"
#include "dev/watchdog.h"
#include "lib/random.h"
#include "net/mac/contikimac.h"
#include "net/netstack.h"
#include "net/rime.h"
#include "sys/compower.h"
#include "sys/pt.h"
#include "sys/rtimer.h"

#include "hal/error.h"
#include "hal/hal.h"
#include <string.h>

#ifndef WITH_PHASE_OPTIMIZATION
#define WITH_PHASE_OPTIMIZATION      1
#endif
#ifndef WITH_STREAMING
#define WITH_STREAMING               0
#endif
#ifdef CONTIKIMAC_CONF_WITH_CONTIKIMAC_HEADER
#define WITH_CONTIKIMAC_HEADER       CONTIKIMAC_CONF_WITH_CONTIKIMAC_HEADER
#else
#define WITH_CONTIKIMAC_HEADER       0
#endif
#ifndef WITH_FAST_SLEEP
#define WITH_FAST_SLEEP              0
#endif

#if NETSTACK_RDC_CHANNEL_CHECK_RATE >= 64
#undef WITH_PHASE_OPTIMIZATION
#define WITH_PHASE_OPTIMIZATION 0
#endif

#if WITH_CONTIKIMAC_HEADER
#define CONTIKIMAC_ID 0x00

struct hdr {
  uint8_t id;
  uint8_t len;
};
#endif /* WITH_CONTIKIMAC_HEADER */

#ifdef CONTIKIMAC_CONF_CYCLE_TIME
#define CYCLE_TIME (CONTIKIMAC_CONF_CYCLE_TIME)
#else
#define CYCLE_TIME (RTIMER_ARCH_SECOND / NETSTACK_RDC_CHANNEL_CHECK_RATE)
#endif


/* ContikiMAC performs periodic channel checks. Each channel check
   consists of two or more CCA checks. CCA_COUNT_MAX is the number of
   CCAs to be done for each periodic channel check. The default is
   two.*/
#define CCA_COUNT_MAX                      5

/* CCA_CHECK_TIME is the time it takes to perform a CCA check. */
#define CCA_CHECK_TIME                     1 + RTIMER_ARCH_SECOND / 8192//5208//8192
#define TEST_SECOND (4096U*8)
/* CCA_SLEEP_TIME is the time between two successive CCA checks. */
#define CCA_SLEEP_TIME                     RTIMER_ARCH_SECOND / 2000//1157//2000

/* CHECK_TIME is the total time it takes to perform CCA_COUNT_MAX
   CCAs. */
#define CHECK_TIME                         (CCA_COUNT_MAX * (CCA_CHECK_TIME + CCA_SLEEP_TIME))

/* LISTEN_TIME_AFTER_PACKET_DETECTED is the time that we keep checking
   for activity after a potential packet has been detected by a CCA
   check. */
#define LISTEN_TIME_AFTER_PACKET_DETECTED  RTIMER_ARCH_SECOND / 80

/* MAX_SILENCE_PERIODS is the maximum amount of periods (a period is
   CCA_CHECK_TIME + CCA_SLEEP_TIME) that we allow to be silent before
   we turn of the radio. */
#define MAX_SILENCE_PERIODS                5

/* MAX_NONACTIVITY_PERIODS is the maximum number of periods we allow
   the radio to be turned on without any packet being received, when
   WITH_FAST_SLEEP is enabled. */
#define MAX_NONACTIVITY_PERIODS            10



/* STROBE_TIME is the maximum amount of time a transmitted packet
   should be repeatedly transmitted as part of a transmission. */
#define STROBE_TIME                        (CYCLE_TIME + 2 * CHECK_TIME)

/* GUARD_TIME is the time before the expected phase of a neighbor that
   a transmitted should begin transmitting packets. */
#define GUARD_TIME                         11 * CHECK_TIME

/* INTER_PACKET_INTERVAL is the interval between two successive packet transmissions */
#define INTER_PACKET_INTERVAL              RTIMER_ARCH_SECOND / 2500//5000//1157//

/* AFTER_ACK_DETECTECT_WAIT_TIME is the time to wait after a potential
   ACK packet has been detected until we can read it out from the
   radio. */
#define AFTER_ACK_DETECTECT_WAIT_TIME      RTIMER_ARCH_SECOND / 1500//1157//1500//1157//

/* MAX_PHASE_STROBE_TIME is the time that we transmit repeated packets
   to a neighbor for which we have a phase lock. */
#define MAX_PHASE_STROBE_TIME              RTIMER_ARCH_SECOND / 60


/* SHORTEST_PACKET_SIZE is the shortest packet that ContikiMAC
   allows. Packets have to be a certain size to be able to be detected
   by two consecutive CCA checks, and here is where we define this
   shortest size. */
#define SHORTEST_PACKET_SIZE               43


#define ACK_LEN 3

#include <stdio.h>
static struct rtimer rt;
static struct pt pt;

static volatile uint8_t contikimac_is_on = 0;
static volatile uint8_t contikimac_keep_radio_on = 0;

static volatile unsigned char we_are_sending = 0;
static volatile unsigned char radio_is_on = 0;

#define DEBUG 0
#if DEBUG
#include <stdio.h>
#define PRINTF(...) printf(__VA_ARGS__)
#define PRINTDEBUG(...) printf(__VA_ARGS__)
#else
#define PRINTF(...)
#define PRINTDEBUG(...)
#endif

/* Flag that is used to keep track of whether or not we are snooping
   for announcements from neighbors. */
static volatile uint8_t is_snooping;

#if CONTIKIMAC_CONF_COMPOWER
static struct compower_activity current_packet;
#endif /* CONTIKIMAC_CONF_COMPOWER */

#if WITH_PHASE_OPTIMIZATION

#include "net/mac/phase.h"

#ifdef CONTIKIMAC_CONF_MAX_PHASE_NEIGHBORS
#define MAX_PHASE_NEIGHBORS CONTIKIMAC_CONF_MAX_PHASE_NEIGHBORS
#endif

#ifndef MAX_PHASE_NEIGHBORS
#define MAX_PHASE_NEIGHBORS 30
#endif

PHASE_LIST(phase_list, MAX_PHASE_NEIGHBORS);

#endif /* WITH_PHASE_OPTIMIZATION */

static volatile uint8_t is_streaming;
static rimeaddr_t is_streaming_to, is_streaming_to_too;
static volatile rtimer_clock_t stream_until;

#define DEFAULT_STREAM_TIME (4 * CYCLE_TIME)

#ifndef MIN
#define MIN(a, b) ((a) < (b)? (a) : (b))
#endif /* MIN */

struct seqno {
  rimeaddr_t sender;
  uint8_t seqno;
};

#ifdef NETSTACK_CONF_MAC_SEQNO_HISTORY
#define MAX_SEQNOS NETSTACK_CONF_MAC_SEQNO_HISTORY
#else /* NETSTACK_CONF_MAC_SEQNO_HISTORY */
#define MAX_SEQNOS 16
#endif /* NETSTACK_CONF_MAC_SEQNO_HISTORY */
static struct seqno received_seqnos[MAX_SEQNOS];

#if CONTIKIMAC_CONF_BROADCAST_RATE_LIMIT
static struct timer broadcast_rate_timer;
static int broadcast_rate_counter;
#endif /* CONTIKIMAC_CONF_BROADCAST_RATE_LIMIT */

/*---------------------------------------------------------------------------*/
static void
on(void)
{
  if(contikimac_is_on && radio_is_on == 0) {
    radio_is_on = 1;
    NETSTACK_RADIO.on();
    //printf("contikimac: on()\n");
  }
}
/*---------------------------------------------------------------------------*/
static void
off(void)
{
  if(contikimac_is_on && radio_is_on != 0 && /*is_streaming == 0 &&*/
     contikimac_keep_radio_on == 0) {
    radio_is_on = 0;
    NETSTACK_RADIO.off();
    //printf("contikimac: off()\n");	
  }
}
/*---------------------------------------------------------------------------*/
static volatile rtimer_clock_t cycle_start;
static char powercycle(struct rtimer *t, void *ptr);
static void
schedule_powercycle(struct rtimer *t, rtimer_clock_t time)
{
  int r;

  if(contikimac_is_on) {

    if(RTIMER_CLOCK_LT(RTIMER_TIME(t) + time, RTIMER_NOW() + 2)) {
      time = RTIMER_NOW() - RTIMER_TIME(t) + 2;
    }

    r = rtimer_set(t, RTIMER_TIME(t) + time, 1,
                   (void (*)(struct rtimer *, void *))powercycle, NULL);
    if(r != RTIMER_OK) {
      printf("schedule_powercycle: could not set rtimer\n");
    }
  }
}
/*---------------------------------------------------------------------------*/
static void
schedule_powercycle_fixed(struct rtimer *t, rtimer_clock_t fixed_time)
{ //printf("contikimac: schedule_powercycle_fixed\n");
  int r;

  if(contikimac_is_on) {

    if(RTIMER_CLOCK_LT(fixed_time, RTIMER_NOW() + 1)) {
      fixed_time = RTIMER_NOW() + 1;
    }

    r = rtimer_set(t, fixed_time, 1,
                   (void (*)(struct rtimer *, void *))powercycle, NULL);
    if(r != RTIMER_OK) {
      printf("schedule_powercycle: could not set rtimer\n");
    }
  }
}
/*---------------------------------------------------------------------------*/
static void
powercycle_turn_radio_off(void)
{
#if CONTIKIMAC_CONF_COMPOWER
  uint8_t was_on = radio_is_on;
#endif /* CONTIKIMAC_CONF_COMPOWER */
  
  if(we_are_sending == 0) {
    //printf("powercycle_turn_radio off\n");
    off();
#if CONTIKIMAC_CONF_COMPOWER
    if(was_on && !radio_is_on) {
      compower_accumulate(&compower_idle_activity);
    }
#endif /* CONTIKIMAC_CONF_COMPOWER */
  }
}
/*---------------------------------------------------------------------------*/
static void
powercycle_turn_radio_on(void)
{
  if(we_are_sending == 0) {
    on();
  }
}
/*---------------------------------------------------------------------------*/
static char
powercycle(struct rtimer *t, void *ptr)
{ //printf("contikimac: duty cycle call\n");
  PT_BEGIN(&pt);
  
  cycle_start = RTIMER_NOW();
  
  while(1) {
    static uint8_t packet_seen;
    static rtimer_clock_t t0;
    static uint8_t count;
    
    //cycle_start += CYCLE_TIME;
    //while(!RTIMER_CLOCK_LT(RTIMER_NOW(),cycle_start)) //bypass expired cycle time
    //{
    //   cycle_start += CYCLE_TIME;
    //}
     cycle_start = RTIMER_NOW();
    if(WITH_STREAMING && is_streaming) {
      if(!RTIMER_CLOCK_LT(RTIMER_NOW(), stream_until)) {
        is_streaming = 0;
        rimeaddr_copy(&is_streaming_to, &rimeaddr_null);
        rimeaddr_copy(&is_streaming_to_too, &rimeaddr_null);
      }
    }

    packet_seen = 0;

    do {
      for(count = 0; count < CCA_COUNT_MAX; ++count) {
        t0 = RTIMER_NOW();
        if(we_are_sending == 0) {
          powercycle_turn_radio_on();
          /* Check if a packet is seen in the air. If so, we keep the
             radio on for a while (LISTEN_TIME_AFTER_PACKET_DETECTED) to
             be able to receive the packet. We also continuously check
             the radio medium to make sure that we wasn't woken up by a
             false positive: a spurious radio interference that was not
             caused by an incoming packet. */
          if(NETSTACK_RADIO.channel_clear() == 0) {
            packet_seen = 1;
            break;
          }
          powercycle_turn_radio_off();
        }
        schedule_powercycle_fixed(t, RTIMER_NOW() + CCA_SLEEP_TIME);
        PT_YIELD(&pt);
      }

      if(packet_seen) {
        static rtimer_clock_t start;
        static uint8_t silence_periods, periods;
        start = RTIMER_NOW();
        
        periods = silence_periods = 0;
        while(we_are_sending == 0 && radio_is_on &&
              RTIMER_CLOCK_LT(RTIMER_NOW(),
                              (start + LISTEN_TIME_AFTER_PACKET_DETECTED))) {
          
          /* Check for a number of consecutive periods of
             non-activity. If we see two such periods, we turn the
             radio off. Also, if a packet has been successfully
             received (as indicated by the
             NETSTACK_RADIO.pending_packet() function), we stop
             snooping. */

          if(NETSTACK_RADIO.channel_clear()) {
            ++silence_periods;
          } else {
            silence_periods = 0;
          }
          
          ++periods;
        
          if(NETSTACK_RADIO.receiving_packet()) {
            silence_periods = 0;
          }
          if(silence_periods > MAX_SILENCE_PERIODS) {
            powercycle_turn_radio_off();
            break;
          }
          if(WITH_FAST_SLEEP &&
             periods > MAX_NONACTIVITY_PERIODS &&
             !(NETSTACK_RADIO.receiving_packet() ||
               NETSTACK_RADIO.pending_packet())) {
            powercycle_turn_radio_off();
            break;
          }
          if(NETSTACK_RADIO.pending_packet()) {
            break;
          }
          
          schedule_powercycle(t, CCA_CHECK_TIME + CCA_SLEEP_TIME);
          PT_YIELD(&pt);
        }
        if(radio_is_on) {
          if(!(NETSTACK_RADIO.receiving_packet() ||
               NETSTACK_RADIO.pending_packet()) ||
             !RTIMER_CLOCK_LT(RTIMER_NOW(),
                              (start + LISTEN_TIME_AFTER_PACKET_DETECTED))) {
            powercycle_turn_radio_off();
          }
        }
      }
    } while((is_snooping || is_streaming) &&
            RTIMER_CLOCK_LT(RTIMER_NOW() - cycle_start, CYCLE_TIME - CHECK_TIME * 8));

    if(RTIMER_CLOCK_LT(RTIMER_NOW() - cycle_start, CYCLE_TIME - CHECK_TIME * 4)) {
      schedule_powercycle_fixed(t, CYCLE_TIME + cycle_start);
      PT_YIELD(&pt);
    }
  }

  PT_END(&pt);
}
/*---------------------------------------------------------------------------*/
static int
broadcast_rate_drop(void)
{
#if CONTIKIMAC_CONF_BROADCAST_RATE_LIMIT
  if(!timer_expired(&broadcast_rate_timer)) {
    broadcast_rate_counter++;
    if(broadcast_rate_counter < CONTIKIMAC_CONF_BROADCAST_RATE_LIMIT) {
      return 0;
    } else {
      return 1;
    }
  } else {
    timer_set(&broadcast_rate_timer, CLOCK_SECOND);
    broadcast_rate_counter = 0;
    return 0;
  }
#else /* CONTIKIMAC_CONF_BROADCAST_RATE_LIMIT */
  return 0;
#endif /* CONTIKIMAC_CONF_BROADCAST_RATE_LIMIT */
}
/*---------------------------------------------------------------------------*/
static int
send_packet(mac_callback_t mac_callback, void *mac_callback_ptr)
{
  rtimer_clock_t t0;
  rtimer_clock_t encounter_time = 0, previous_txtime = 0;
  int strobes;
  uint8_t got_strobe_ack = 0;
  int hdrlen, len;
  uint8_t is_broadcast = 0;
  uint8_t is_reliable = 0;
  uint8_t is_known_receiver = 0;
  uint8_t collisions;
  int transmit_len;
  int i;
  int ret;
  uint8_t contikimac_was_on;
#if WITH_CONTIKIMAC_HEADER
  struct hdr *chdr;
#endif /* WITH_CONTIKIMAC_HEADER */

  if(packetbuf_totlen() == 0) {
    PRINTF("contikimac: send_packet data len 0\n");
    return MAC_TX_ERR_FATAL;
  }

  packetbuf_set_addr(PACKETBUF_ADDR_SENDER, &rimeaddr_node_addr);
  if(rimeaddr_cmp(packetbuf_addr(PACKETBUF_ADDR_RECEIVER), &rimeaddr_null)) {
    is_broadcast = 1;
    PRINTDEBUG("contikimac: send broadcast\n");

    if(broadcast_rate_drop()) {
      return MAC_TX_COLLISION;
    }
  } else {
#if UIP_CONF_IPV6
    PRINTDEBUG("contikimac: send unicast to %02x%02x:%02x%02x:%02x%02x:%02x%02x\n",
               packetbuf_addr(PACKETBUF_ADDR_RECEIVER)->u8[0],
               packetbuf_addr(PACKETBUF_ADDR_RECEIVER)->u8[1],
               packetbuf_addr(PACKETBUF_ADDR_RECEIVER)->u8[2],
               packetbuf_addr(PACKETBUF_ADDR_RECEIVER)->u8[3],
               packetbuf_addr(PACKETBUF_ADDR_RECEIVER)->u8[4],
               packetbuf_addr(PACKETBUF_ADDR_RECEIVER)->u8[5],
               packetbuf_addr(PACKETBUF_ADDR_RECEIVER)->u8[6],
               packetbuf_addr(PACKETBUF_ADDR_RECEIVER)->u8[7]);
#else /* UIP_CONF_IPV6 */
    PRINTDEBUG("contikimac: send unicast to %u.%u\n",
               packetbuf_addr(PACKETBUF_ADDR_RECEIVER)->u8[0],
               packetbuf_addr(PACKETBUF_ADDR_RECEIVER)->u8[1]);
#endif /* UIP_CONF_IPV6 */
  }
  is_reliable = packetbuf_attr(PACKETBUF_ATTR_RELIABLE) ||
    packetbuf_attr(PACKETBUF_ATTR_ERELIABLE);

  if(WITH_STREAMING) {
    if(packetbuf_attr(PACKETBUF_ATTR_PACKET_TYPE) ==
       PACKETBUF_ATTR_PACKET_TYPE_STREAM) {
      if(rimeaddr_cmp(&is_streaming_to, &rimeaddr_null)) {
        rimeaddr_copy(&is_streaming_to,
                      packetbuf_addr(PACKETBUF_ADDR_RECEIVER));
      } else if(!rimeaddr_cmp
                (&is_streaming_to, packetbuf_addr(PACKETBUF_ADDR_RECEIVER))) {
        rimeaddr_copy(&is_streaming_to_too,
                      packetbuf_addr(PACKETBUF_ADDR_RECEIVER));
      }
      stream_until = RTIMER_NOW() + DEFAULT_STREAM_TIME;
      is_streaming = 1;
    }
  }

  if(is_streaming) {
    packetbuf_set_attr(PACKETBUF_ATTR_PENDING, 1);
  }
  packetbuf_set_attr(PACKETBUF_ATTR_MAC_ACK, 1);

#if WITH_CONTIKIMAC_HEADER
  hdrlen = packetbuf_totlen();
  if(packetbuf_hdralloc(sizeof(struct hdr)) == 0) {
    /* Failed to allocate space for contikimac header */
    PRINTF("contikimac: send failed, too large header\n");
    return MAC_TX_ERR_FATAL;
  }
  chdr = packetbuf_hdrptr();
  chdr->id = CONTIKIMAC_ID;
  chdr->len = hdrlen;
  
  /* Create the MAC header for the data packet. */
  hdrlen = NETSTACK_FRAMER.create();
  if(hdrlen == 0) {
    /* Failed to send */
    PRINTF("contikimac: send failed, too large header\n");
    packetbuf_hdr_remove(sizeof(struct hdr));
    return MAC_TX_ERR_FATAL;
  }
  hdrlen += sizeof(struct hdr);
#else
  /* Create the MAC header for the data packet. */
  hdrlen = NETSTACK_FRAMER.create();
  if(hdrlen == 0) {
    /* Failed to send */
    PRINTF("contikimac: send failed, too large header\n");
    return MAC_TX_ERR_FATAL;
  }
#endif


  /* Make sure that the packet is longer or equal to the shortest
     packet length. */
  transmit_len = packetbuf_totlen();
  if(transmit_len < SHORTEST_PACKET_SIZE) {
    /* Pad with zeroes */
    uint8_t *ptr;
    ptr = packetbuf_dataptr();
    memset(ptr + packetbuf_datalen(), 0, SHORTEST_PACKET_SIZE - packetbuf_totlen());

    PRINTF("contikimac: shorter than shortest (%d)\n", packetbuf_totlen());
    transmit_len = SHORTEST_PACKET_SIZE;
  }


  packetbuf_compact();

  NETSTACK_RADIO.prepare(packetbuf_hdrptr(), transmit_len);

  /* Remove the MAC-layer header since it will be recreated next time around. */
  packetbuf_hdr_remove(hdrlen);

  if(!is_broadcast && !is_streaming) {
#if WITH_PHASE_OPTIMIZATION
    ret = phase_wait(&phase_list, packetbuf_addr(PACKETBUF_ADDR_RECEIVER),
                     CYCLE_TIME, GUARD_TIME,
                     mac_callback, mac_callback_ptr);
    PRINTF("contikimac: WITH_PHASE_OPTIMIZATION\n");
    if(ret == PHASE_DEFERRED) {
      PRINTF("contikimac: PHASE_DEFERRED\n");	
      return MAC_TX_DEFERRED;
    }
    if(ret != PHASE_UNKNOWN) {
      is_known_receiver = 1;
    }
#endif /* WITH_PHASE_OPTIMIZATION */ 
  }
  


  /* By setting we_are_sending to one, we ensure that the rtimer
     powercycle interrupt do not interfere with us sending the packet. */
  we_are_sending = 1;

  /* If we have a pending packet in the radio, we should not send now,
     because we will trash the received packet. Instead, we signal
     that we have a collision, which lets the packet be received. This
     packet will be retransmitted later by the MAC protocol
     instread. */
  if(NETSTACK_RADIO.receiving_packet() || NETSTACK_RADIO.pending_packet()) {
    we_are_sending = 0;
    //printf("contikimac: collision receiving %d, pending %d\n",
           //NETSTACK_RADIO.receiving_packet(), NETSTACK_RADIO.pending_packet());
    return MAC_TX_COLLISION;
  }
  
  /* Switch off the radio to ensure that we didn't start sending while
     the radio was doing a channel check. */
  //printf("contikimac: off to not sending\n");
  off();


  strobes = 0;

  /* Send a train of strobes until the receiver answers with an ACK. */
  collisions = 0;

  got_strobe_ack = 0;

  /* Set contikimac_is_on to one to allow the on() and off() functions
     to control the radio. We restore the old value of
     contikimac_is_on when we are done. */
  contikimac_was_on = contikimac_is_on;
  contikimac_is_on = 1;
  
  if(is_streaming == 0) {
    /* Check if there are any transmissions by others. */

    for(i = 0; i < CCA_COUNT_MAX; ++i) {
      t0 = RTIMER_NOW();
      on();
      while(RTIMER_CLOCK_LT(RTIMER_NOW(), t0 + CCA_CHECK_TIME)) { }
      if(NETSTACK_RADIO.channel_clear() == 0) {
        collisions++;
        off();
        break;
      }
      off();
      t0 = RTIMER_NOW();
      while(RTIMER_CLOCK_LT(RTIMER_NOW(), t0 + CCA_SLEEP_TIME)) { }
    }

  }

  if(collisions > 0) {
    we_are_sending = 0;
    //printf("contikimac: collisions off\n");
    off();
    //printf("contikimac: collisions before sending\n");
    contikimac_is_on = contikimac_was_on;
    return MAC_TX_COLLISION;
  }

  if(!is_broadcast) {
    on();
  }

  
  watchdog_periodic();
  t0 = RTIMER_NOW();

  for(strobes = 0, collisions = 0;
      got_strobe_ack == 0 && collisions == 0 &&
      RTIMER_CLOCK_LT(RTIMER_NOW(), t0 + STROBE_TIME); strobes++) {

    watchdog_periodic();
    
    if(is_known_receiver && !RTIMER_CLOCK_LT(RTIMER_NOW(), t0 + MAX_PHASE_STROBE_TIME)) {
      PRINTF("miss to %d\n", packetbuf_addr(PACKETBUF_ADDR_RECEIVER)->u8[0]);
      break;
    }
    
    len = 0;

    previous_txtime = RTIMER_NOW();
    {
      rtimer_clock_t wt;
      rtimer_clock_t txtime;
      int ret;

      txtime = RTIMER_NOW();
      ret = NETSTACK_RADIO.transmit(transmit_len);
      //printf("contikimac: transmit status %u!\n", ret);
      //wt = RTIMER_NOW();
      //while(RTIMER_CLOCK_LT(RTIMER_NOW(), wt + INTER_PACKET_INTERVAL)) { }

#if CONTIKIMAC_CONF_HARDWARE_ACKDETECT
/* For radios that block in the transmit routine and detect the ack in hardware */
if(!is_broadcast) {
     printf("contikimac: GOT STATUS (%u)\n", ret);	
     if(ret == RADIO_TX_OK) {
       
         got_strobe_ack = 1;
         encounter_time = previous_txtime;
	 printf("contikimac: GOT ACK ST_PHY_ACK_RECEIVED (%u)\n", ret);	
         break;
      
     } else {
         //printf("contikimac: collisions while sending\n"); //no break, colission
         //collisions++;
     }
 }
     wt = RTIMER_NOW();
     while(RTIMER_CLOCK_LT(RTIMER_NOW(), wt + INTER_PACKET_INTERVAL)) { }
#else
     wt = RTIMER_NOW();
     while(RTIMER_CLOCK_LT(RTIMER_NOW(), wt + INTER_PACKET_INTERVAL)) { }

     if(!is_broadcast && (NETSTACK_RADIO.receiving_packet() ||
                          NETSTACK_RADIO.pending_packet() ||
                          NETSTACK_RADIO.channel_clear() == 0)) {
       uint8_t ackbuf[ACK_LEN];
       wt = RTIMER_NOW();
       while(RTIMER_CLOCK_LT(RTIMER_NOW(), wt + AFTER_ACK_DETECTECT_WAIT_TIME)) { }

       len = NETSTACK_RADIO.read(ackbuf, 100);
       if(len >= ACK_LEN) {
	 printf("contikimac: GOT ACK (%u)\n", len);	
         got_strobe_ack = 1;
         encounter_time = previous_txtime;
         break;
       } else {
         PRINTF("contikimac: collisions while sending\n");
         //collisions++;
       }
     }
#endif /*  CONTIKIMAC_CONF_HARDWARE_ACKDETECT */

      previous_txtime = txtime;
    }
  }
  //printf("contikimac: after ack waiting off()\n");
  off();

  /*printf("contikimac: send (strobes=%u, len=%u, %s, %s), done\n", strobes,
         packetbuf_totlen(),
         got_strobe_ack ? "ack" : "no ack",
         collisions ? "collision" : "no collision");*/

#if CONTIKIMAC_CONF_COMPOWER
  /* Accumulate the power consumption for the packet transmission. */
  compower_accumulate(&current_packet);

  /* Convert the accumulated power consumption for the transmitted
     packet to packet attributes so that the higher levels can keep
     track of the amount of energy spent on transmitting the
     packet. */
  compower_attrconv(&current_packet);

  /* Clear the accumulated power consumption so that it is ready for
     the next packet. */
  compower_clear(&current_packet);
#endif /* CONTIKIMAC_CONF_COMPOWER */

  contikimac_is_on = contikimac_was_on;
  we_are_sending = 0;

  /* Determine the return value that we will return from the
     function. We must pass this value to the phase module before we
     return from the function.  */
  if(collisions > 0) {
    ret = MAC_TX_COLLISION;
  } else if(!is_broadcast && !got_strobe_ack) {
    ret = MAC_TX_NOACK;
  } else {
    ret = MAC_TX_OK;
  }

#if WITH_PHASE_OPTIMIZATION

  if(is_known_receiver && got_strobe_ack) {
    PRINTF("no miss %d wake-ups %d\n", packetbuf_addr(PACKETBUF_ADDR_RECEIVER)->u8[0],
           strobes);
  }

  if(!is_broadcast) {
    if(collisions == 0 && is_streaming == 0) {
      PRINTF("Phase updaded \n"); 	
      phase_update(&phase_list, packetbuf_addr(PACKETBUF_ADDR_RECEIVER), encounter_time,
                   ret);
    }
  }
#endif /* WITH_PHASE_OPTIMIZATION */

  if(WITH_STREAMING) {
    if(packetbuf_attr(PACKETBUF_ATTR_PACKET_TYPE) ==
       PACKETBUF_ATTR_PACKET_TYPE_STREAM_END) {
      is_streaming = 0;
    }
  }

  return ret;
}

void send_ack(void)
{packetbuf_hdralloc(ACK_LEN);
 NETSTACK_RADIO.prepare(packetbuf_hdrptr(), ACK_LEN);
 NETSTACK_RADIO.transmit(ACK_LEN);
}
/*---------------------------------------------------------------------------*/
static void
qsend_packet(mac_callback_t sent, void *ptr)
{ PRINTF("contikimac: qsend_packet\n");
  int ret = send_packet(sent, ptr);
  if(ret != MAC_TX_DEFERRED) {
    PRINTF("contikimac: mac_call_sent_callback\n");	
    mac_call_sent_callback(sent, ptr, ret, 1);
  } else {
	PRINTF("contikimac: MAC_TX_DEFERRED\n");
  }
}
/*---------------------------------------------------------------------------*/
static void
input_packet(void)
{ PRINTF("contikimac: input_packet\n");
  /* We have received the packet, so we can go back to being
     asleep. */
  //send_ack();
  //rtimer_clock_t wt;
  //wt = RTIMER_NOW();
  //while(RTIMER_CLOCK_LT(RTIMER_NOW(), wt + AFTER_ACK_DETECTECT_WAIT_TIME)) { }
  //printf("contikimac: after packet receiving off()\n");
  off();

  /*  printf("cycle_start 0x%02x 0x%02x\n", cycle_start, cycle_start % CYCLE_TIME);*/
  
  
  if(packetbuf_totlen() > 0 && NETSTACK_FRAMER.parse()) {

#if WITH_CONTIKIMAC_HEADER
    struct hdr *chdr;
    chdr = packetbuf_dataptr();
    if(chdr->id != CONTIKIMAC_ID) {
      PRINTF("contikimac: failed to parse hdr (%u)\n", packetbuf_totlen());
      return;
    }
    packetbuf_hdrreduce(sizeof(struct hdr));
    packetbuf_set_datalen(chdr->len);
#endif /* WITH_CONTIKIMAC_HEADER */

    if(packetbuf_datalen() > 0 &&
       packetbuf_totlen() > 0 &&
       (rimeaddr_cmp(packetbuf_addr(PACKETBUF_ADDR_RECEIVER),
                     &rimeaddr_node_addr) ||
        rimeaddr_cmp(packetbuf_addr(PACKETBUF_ADDR_RECEIVER),
                     &rimeaddr_null))) {
      /* This is a regular packet that is destined to us or to the
         broadcast address. */

#if WITH_PHASE_OPTIMIZATION
      /* If the sender has set its pending flag, it has its radio
         turned on and we should drop the phase estimation that we
         have from before. */
      if(packetbuf_attr(PACKETBUF_ATTR_PENDING)) {
        phase_remove(&phase_list, packetbuf_addr(PACKETBUF_ADDR_SENDER));
      }
#endif /* WITH_PHASE_OPTIMIZATION */

      /* Check for duplicate packet by comparing the sequence number
         of the incoming packet with the last few ones we saw. */
      {
        int i;
        for(i = 0; i < MAX_SEQNOS; ++i) {
          if(packetbuf_attr(PACKETBUF_ATTR_PACKET_ID) == received_seqnos[i].seqno &&
             rimeaddr_cmp(packetbuf_addr(PACKETBUF_ADDR_SENDER),
                          &received_seqnos[i].sender)) {
            /* Drop the packet. */
            /*        printf("Drop duplicate ContikiMAC layer packet\n");*/
            return;
          }
        }
        for(i = MAX_SEQNOS - 1; i > 0; --i) {
          memcpy(&received_seqnos[i], &received_seqnos[i - 1],
                 sizeof(struct seqno));
        }
        received_seqnos[0].seqno = packetbuf_attr(PACKETBUF_ATTR_PACKET_ID);
        rimeaddr_copy(&received_seqnos[0].sender,
                      packetbuf_addr(PACKETBUF_ADDR_SENDER));
      }

#if CONTIKIMAC_CONF_COMPOWER
      /* Accumulate the power consumption for the packet reception. */
      compower_accumulate(&current_packet);
      /* Convert the accumulated power consumption for the received
         packet to packet attributes so that the higher levels can
         keep track of the amount of energy spent on receiving the
         packet. */
      compower_attrconv(&current_packet);

      /* Clear the accumulated power consumption so that it is ready
         for the next packet. */
      compower_clear(&current_packet);
#endif /* CONTIKIMAC_CONF_COMPOWER */

      PRINTDEBUG("contikimac: data (%u)\n", packetbuf_datalen());
      NETSTACK_MAC.input();
      
      return;
    } else {
      PRINTDEBUG("contikimac: data not for us\n");
    }
  } else {
    PRINTF("contikimac: failed to parse (%u)\n", packetbuf_totlen());
  }
}
/*---------------------------------------------------------------------------*/
static void
init(void)
{ PRINTF("contikimac: init\n");
  printf("contikimac: init CCA_CHECK_TIME (%d) RTIMER_ARCH_SECOND (%d)\n", CCA_CHECK_TIME, RTIMER_ARCH_SECOND);     
printf("contikimac: init TEST_SECOND (%d) \n", TEST_SECOND);  
  radio_is_on = 0;
  PT_INIT(&pt);
  rtimer_set(&rt, RTIMER_NOW() + CYCLE_TIME, 1,
             (void (*)(struct rtimer *, void *))powercycle, NULL);

  contikimac_is_on = 1;

#if WITH_PHASE_OPTIMIZATION
  phase_init(&phase_list);
#endif /* WITH_PHASE_OPTIMIZATION */

}
/*---------------------------------------------------------------------------*/
static int
turn_on(void)
{ PRINTF("contikimac: turn_on\n");
  if(contikimac_is_on == 0) {
    contikimac_is_on = 1;
    contikimac_keep_radio_on = 0;
    rtimer_set(&rt, RTIMER_NOW() + CYCLE_TIME, 1,
               (void (*)(struct rtimer *, void *))powercycle, NULL);
  }
  return 1;
}
/*---------------------------------------------------------------------------*/
static int
turn_off(int keep_radio_on)
{ PRINTF("contikimac: turn_off\n");
  contikimac_is_on = 0;
  contikimac_keep_radio_on = keep_radio_on;
  if(keep_radio_on) {
    radio_is_on = 1;
    //printf("contikimac: turn_on()\n");	
    return NETSTACK_RADIO.on();
  } else {
    radio_is_on = 0; 
    //printf("contikimac: turn_off()\n");		
    return NETSTACK_RADIO.off();
  }
}
/*---------------------------------------------------------------------------*/
static unsigned short
duty_cycle(void)
{ PRINTF("contikimac: duty_cycle\n");
  return (1ul * CLOCK_SECOND * CYCLE_TIME) / RTIMER_ARCH_SECOND;
}
/*---------------------------------------------------------------------------*/
const struct rdc_driver contikimac_driver = {
  "ContikiMAC",
  init,
  qsend_packet,
  input_packet,
  turn_on,
  turn_off,
  duty_cycle,
};
/*---------------------------------------------------------------------------*/
uint16_t
contikimac_debug_print(void)
{
  return 0;
}
/*---------------------------------------------------------------------------*/
