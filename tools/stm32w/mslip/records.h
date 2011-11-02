#ifndef RECORDS_H__
#define RECORDS_H__ 1

#include <arpa/inet.h>

struct uip_lladdr_t {
  bool          defined;
  unsigned char byte[8];
  //  public:
  //  uip_lladdr_t() : defined(false) {} pb with union
  void setUndefined(void) { defined = false; }
  void set(const unsigned char Eui64[8]) {
    for(int i=0;i<8;i++)
      byte[i] = Eui64[i];
    defined = true;
  }
  void set(unsigned long long Eui64) {
    for(int i=7;i>=0;i--) {
      byte[i] = (unsigned char)Eui64;
      Eui64 = Eui64>>8;
    }
    defined = true;
  }
  void get(unsigned char Eui64[8]) const {
    for(int i=0;i<8;i++)
      Eui64[i] = byte[i]; 
  } 
  void str(char buffer[5*4]) const {
    if (defined) {
      sprintf(buffer,
	      "%02x%02x:%02x%02x:%02x%02x:%02x%02x\n",
	      byte[0],
	      byte[1],
	      byte[2],
	      byte[3],
	      byte[4],
	      byte[5],
	      byte[6],
	      byte[7]);
    } else {
      strcpy(buffer,"undefined");
    }
  }
};

struct uip_ipaddr_t {
  bool            defined;
  struct in6_addr in6_addr; 
 public:
 // no constructor for union
  void set(const struct in6_addr & In6_addr) {
    in6_addr = In6_addr;
    defined  = true;
  }
  void set(const unsigned char ipaddr[16]) {
    for(int i=0;i<16;i++)
      in6_addr.s6_addr[i] = ipaddr[i];
    defined = true;
  }
  void setZero(void) {
    for(int i=0;i<16;i++)
      in6_addr.s6_addr[i] = 0;
    defined = true;
  }
  void setEui64(unsigned long long Eui64) {
    for(int i=0;i<8;i++)
      in6_addr.s6_addr[i] = 0; // prefix 0 for now
    for(int i=16;--i>=8;) {
      in6_addr.s6_addr[i] = (unsigned char)Eui64;
      Eui64 = Eui64>>8;
    }
    defined = true;
  }
  void setPrefix64(const struct in6_addr & prefix) {
    for(int i=0;i<7;i++)
      in6_addr.s6_addr[i] = prefix.s6_addr[i];
  }
  void setpton(const char ipAddrStrWithoutPrefix[5*8]) {
    const int res = inet_pton(AF_INET6,ipAddrStrWithoutPrefix, &in6_addr);
    defined = (res >= 0);
  }
  void get(unsigned char ipaddr[16]) const {
    for(int i=0;i<16;i++)
      ipaddr[i] = in6_addr.s6_addr[i]; 
  } 
  void str(char buffer[5*8]) const {
    if (defined) {
      sprintf(buffer,
	      "%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x",
	      in6_addr.s6_addr[0],
	      in6_addr.s6_addr[1],
	      in6_addr.s6_addr[2],
	      in6_addr.s6_addr[3],
	      in6_addr.s6_addr[4],
	      in6_addr.s6_addr[5],
	      in6_addr.s6_addr[6],
	      in6_addr.s6_addr[7],
	      in6_addr.s6_addr[8],
	      in6_addr.s6_addr[9],
	      in6_addr.s6_addr[10],
	      in6_addr.s6_addr[11],
	      in6_addr.s6_addr[12],
	      in6_addr.s6_addr[13],
	      in6_addr.s6_addr[14],
	      in6_addr.s6_addr[15]);
    } else {
      strcpy(buffer,"undefined");
    }
  } // str
  const struct in6_addr & getIn6Addr(void) const { return in6_addr; }
  bool equalOrSetPrefix(const struct in6_addr & clientAddr) {
#if 0
    char clientAddrStr[5*8];
    uip_ipaddr_t tmp;
    tmp.set(clientAddr);
    tmp.str(clientAddrStr);
    
    char boardAddrStr[5*8];
    str(boardAddrStr);
    gnTrace.printf("compare clientAddr=%s to boardAddr=%s\n",clientAddrStr, boardAddrStr);
#endif
    if (IN6_ARE_ADDR_EQUAL(&clientAddr.s6_addr,in6_addr.s6_addr))
      return true;
    // know we can accept to set prefix addr (board id table)
    bool nullPrefixAndEui64Equal = true;
    for(int i=0;i<16;i++) {
      if (i<8) {
	if (in6_addr.s6_addr[i]!=0) {
	  nullPrefixAndEui64Equal = false;
	  break;
	}
      } else {
	if (in6_addr.s6_addr[i]!=clientAddr.s6_addr[i]) {
	  nullPrefixAndEui64Equal = false;
	  break;
	}
      }
    }
    if (nullPrefixAndEui64Equal) {
      setPrefix64(clientAddr);
      return true;
    } else
      return false;
  }
}; // struct uip_ipaddr_t

class rawData_t {
public:
  typedef unsigned short recSize_t;
private:
  unsigned char  rawData[257]; // max record + Reclen
  recSize_t ptr;
public:
  enum recType_t {
    ACC_ABSOLUTE=0,
    ACC_RELATIVE,
    TEMP_ABSOLUTE,
    INFO_NONE,
    INFO_ADDRESS,
    INFO_NEIGHBOR,
    INFO_DEFRT,
    INFO_PREFIX,
    INFO_ROUTE,
    INFO_ENERGY,
    TCPIP_SERVER,
    RADIO_INFO,
  };
  int writeTo(int fd) const { return write(fd,rawData,1+getSize()); }
  unsigned char * getAddr(unsigned short received) { return &rawData[received]; }
  void setPtr(unsigned short Ptr) { ptr = Ptr; }
  unsigned short getPtr(void) const { return ptr; }
  unsigned char getSize(void) const { return rawData[0]; }
  unsigned char getType(void) const { return rawData[1]; }
  void setData(unsigned short i,unsigned char c) { rawData[i] = c; }
  unsigned char getData(unsigned short i) const { return rawData[i]; }
  unsigned char get1to1u(void) { return rawData[ptr++]; }
  signed char get1to1s(void) { return (signed char)rawData[ptr++]; }
  short get1to2s(void) { return (signed char)rawData[ptr++]; }
  short get2to2s(void) { short b1 = (signed char)(rawData[ptr++]); unsigned short b0 = rawData[ptr++]; return (b1<<8 | b0); }
  unsigned short get1to2u(void) { return (signed char)rawData[ptr++]; }
  unsigned short get2to2u(void) { unsigned short b1 =rawData[ptr++]; unsigned short b0 = rawData[ptr++]; return (b1<<8 | b0); }
  int   get1to4s(void) { return (signed char)rawData[ptr++]; }
  int   get2to4s(void) { int b1 = (signed char)(rawData[ptr++]); unsigned b0 = rawData[ptr++]; return (b1<<8 | b0); }
  int   get4to4s(void) {
    int      b3 = (signed char)(rawData[ptr++]);
    unsigned b2 = rawData[ptr++];
    unsigned b1 = rawData[ptr++];
    unsigned b0 = rawData[ptr++];
    return (b3<<3*8) | (b2<<2*8) | (b1<<1*8) | b0;
  }
  unsigned get1to4u(void) { return rawData[ptr++]; }
  unsigned get2to4u(void) { unsigned b1 = rawData[ptr++]; unsigned b0 = rawData[ptr++]; return (b1<<8 | b0); }
  unsigned get4to4u(void) {
    unsigned b3 = rawData[ptr++];
    unsigned b2 = rawData[ptr++];
    unsigned b1 = rawData[ptr++];
    unsigned b0 = rawData[ptr++];
    return (b3<<3*8) | (b2<<2*8) | (b1<<1*8) | b0;
  }
  unsigned long long get4to8u(void) {
    unsigned b3 = rawData[ptr++];
    unsigned b2 = rawData[ptr++];
    unsigned b1 = rawData[ptr++];
    unsigned b0 = rawData[ptr++];
    return (b3<<3*8) | (b2<<2*8) | (b1<<1*8) | b0;
  }
  unsigned long long get8to8u(void) {
    unsigned long long b7 = rawData[ptr++];
    unsigned long long b6 = rawData[ptr++];
    unsigned long long b5 = rawData[ptr++];
    unsigned long long b4 = rawData[ptr++];
    unsigned long long b3 = rawData[ptr++];
    unsigned long long b2 = rawData[ptr++];
    unsigned long long b1 = rawData[ptr++];
    unsigned long long b0 = rawData[ptr++];
    return (b7<<7*8) | (b6<<6*8) | (b5<<5*8) | (b4<<7*8) | (b3<<3*8) | (b2<<2*8) | (b1<<1*8) | b0;
  }
  void getIpAddr(uip_ipaddr_t & ipaddr) {
    ipaddr.set(&rawData[ptr]);
    ptr += 16;
  }
  void getLlAddr(uip_lladdr_t & lladdr) {
    lladdr.set(&rawData[ptr]);
    ptr += 8;
  }
  void set1(unsigned char c) { rawData[ptr++] = c; }
  void set2(short s) { rawData[ptr++] = s; rawData[ptr++] = (s>>8); }
  void set4(int i) {
    rawData[ptr++] = i;
    rawData[ptr++] = i>>(1*8);
    rawData[ptr++] = i>>(2*8);
    rawData[ptr++] = i>>(3*8);
  }
  void set8(unsigned long long i) {
    rawData[ptr++] = i;
    rawData[ptr++] = i>>(1*8);
    rawData[ptr++] = i>>(2*8);
    rawData[ptr++] = i>>(3*8);
    rawData[ptr++] = i>>(4*8);
    rawData[ptr++] = i>>(5*8);
    rawData[ptr++] = i>>(6*8);
    rawData[ptr++] = i>>(7*8);
  }
  void setCopy(unsigned char size,
	       const unsigned char * src) {
    for(unsigned i=0;i<size;i++)
       rawData[ptr++] = src[i];
  }
  void setIpAddr(const uip_ipaddr_t & ipaddr) {
    ipaddr.get(&rawData[ptr]);
    ptr+=16;
  }
  void setIpAddr(const struct in6_addr & in6_addr) {
    for(unsigned i=0;i<16;i++)
      rawData[ptr++] = in6_addr.s6_addr[i];
  }
  void setLlAddr(const uip_lladdr_t & lladdr) {
    lladdr.get(&rawData[ptr]);
    ptr+=8;
  }
}; // struct rawData_t

class receiveRawData_t : public rawData_t {
  int       socket;   // socket
  int       step;     // while reading buffer
  recSize_t received; // byte index in buffer
  recSize_t expected; // byte index in buffer 
  public:
  receiveRawData_t(const int Socket) :
    socket(Socket),
    step(0),
    received(0),
    expected(1)
  {}
  void prepareForNextRecord(void) {
    step     = 0;
    received = 0;
    expected = 1;
  }
  enum recStatus_t {
    ERROR           = -1,
    NOT_COMPLETED   = 0,
    RECORD_RECEIVED = 1
  };
  recStatus_t receive(struct sockaddr_in6 & srcsockaddr_in6,
		      socklen_t & srcAddrLen) { // returns 0 if not fully read 1 when Ok
    switch(step) {
    case 0:
      bzero(&srcsockaddr_in6, sizeof(srcsockaddr_in6));
      srcsockaddr_in6.sin6_family = AF_INET6; // !!!!
      srcAddrLen = sizeof(srcsockaddr_in6); // man recvfrom: The argument addrlen is a value-result argument, which the caller should initialize before  the  call
      expected = 1; // read reclen first
      break;
    case 1:
      expected = 1+getSize();
      break;
    default:
      //      gnTrace.printf("receiveUrgent:step=%d\n",step);
      assert(0);
    }
    if (received < expected) {
      // gnTrace.printf("TRY RECEIVED step=%d %d/%d\n",step,received,expected);
      int ret;
      //fprintf(stderr,"read received=%d expected=%d\n",received,expected);
      ret = recvfrom(socket,
		     getAddr(received),
		     expected-received,
		     0, // noflags
		     (struct sockaddr*)&srcsockaddr_in6,
		     &srcAddrLen);
      if (ret<=0) {
	if ((errno==EAGAIN) || (errno==EWOULDBLOCK)) {
	  return NOT_COMPLETED;// wait return 0; // retry later
	} else {
	  return ERROR;
	}
      } else { // ret > 0
	received           += ret;
	if (received<1) {
	  step = 0;
	} else if (received < 1U+getSize()) {
	  step = 1;
	} else {
	  step = 2;
	}
	return (step==2) ? RECORD_RECEIVED : NOT_COMPLETED;
	//    gnTrace.printf("\tread received=%d expected=%d\n",received,expected);
      }  // else (receinived == expected)
    } else { // if (received >= expected)
      return (step==2) ? RECORD_RECEIVED : NOT_COMPLETED;
    }
  } // int receive(void) { // returns 0 if not fully read 1 when Ok
  void init() { setPtr(2); }
  bool check(void) const { return getPtr()==getSize()+1U; }
#if 0
  void debug(trace_t & trace) const {
    unsigned size = getSize();
    trace.printf("RAWDATA=recLen=%d,type=%d,",size,getType());
    for(unsigned i=0;i<size-1;i++)
      trace.printf("%02x ",getData(i+2));
    trace.printf("\n");
  }
#endif
}; // struct receiveRawData_t

struct send2guiRawData_t : public rawData_t {
  enum rawType_t {
    RAW_TYPE_NEW_NODE,
    RAW_TYPE_NEW_REJECTED_NODE,
    RAW_TYPE_USE_SUBTYPE,
  };
  void setTypeAndNodeId(const unsigned char  dataLen, // init data record len (as stored in data record)
			const rawType_t      type,
			const unsigned short nodeId) {
    setData(0, dataLen+3); // does not include itself
    setData(1, type);
    setData(2, nodeId);
    setData(3, nodeId>>8);
    setPtr(4); // 0=totalRecSize,1==type,2=nodeidlsb,3=nodeidmsb,4=subtype,5=data0
  }
  bool check(void) const { return getPtr()==getSize()+1U; }
#if 0
  void debug(trace_t & trace) const {
    unsigned size = getSize();
    trace.printf("SENDRAWDATA=recLen=%d,type=%d,id=%d,subtype=%d,",
		 size,
		 getType(),
		 getData(2)+(((int)getData(3))<<8),
		 getData(4));
    for(unsigned i=0;i<size-1;i++)
      trace.printf("%02x ",getData(i+2));
    trace.printf("\n");
  }
#endif
}; // struct send2guiRawData_t

class guiConnection_t {
  int guiTcpFd; // -1 if not connected
public:
  guiConnection_t(const int port = 7763) {
#define SERVER_ADDR     "127.0.0.1"     /* localhost */
    /*---Create socket and connect to server---*/
    guiTcpFd = socket(PF_INET, SOCK_STREAM, 0);        /* create socket */
    if ( guiTcpFd < 0 ) 
      return;
    struct sockaddr_in guiServerAddr;
    memset(&guiServerAddr, 0, sizeof(guiServerAddr));       /* create & zero struct */
    guiServerAddr.sin_family = AF_INET;            /* select internet protocol */
    guiServerAddr.sin_port   = htons(port);        /* set the port # */
    if ( inet_aton(SERVER_ADDR, &guiServerAddr.sin_addr/*.s_addr*/) == 0 ) {
      perror(SERVER_ADDR);
      guiTcpFd = -1;
      return;
    }
    fprintf(stderr,"connecting to gui (%s.%d) ...\n",SERVER_ADDR,port);
    if ( connect(guiTcpFd, (struct sockaddr*)&guiServerAddr, sizeof(guiServerAddr)) != 0 ) {
      perror("Connect ");
      guiTcpFd = -1;
      return;
    }
    fprintf(stderr,"connection to gui (%s.%d) established\n",SERVER_ADDR,port);
  }
  bool isConnected(void) const { return guiTcpFd>=0; }
  void sendRecord(const send2guiRawData_t & send2guiRawData) { // first byte is rec size followed by rec size byte
    if (!isConnected())
      return;
    send2guiRawData.writeTo(guiTcpFd);
  }
}; // class guiConnection_t



/**
 * \defgroup stimer Seconds timer library
 *
 * The stimer library provides functions for setting, resetting and
 * restarting timers, and for checking if a timer has expired. An
 * application must "manually" check if its timers have expired; this
 * is not done automatically.
 *
 * A timer is declared as a \c struct \c stimer and all access to the
 * timer is made by a pointer to the declared timer.
 *
 * \note The stimer library is not able to post events when a timer
 * expires. The \ref etimer "Event timers" should be used for this
 * purpose.
 *
 * \note The stimer library uses the \ref clock "Clock library" to
 * measure time. Intervals should be specified in the seconds.
 *
 * \sa \ref etimer "Event timers"
 *
 * @{
 */
struct stimer {
  unsigned long start;
  unsigned long interval;
  void str(char * buffer) const {
    sprintf(buffer,
	    "stimer(start=%lu,interval=%lu seconds)",
	    start,
	    interval);
  }
  void getStimer(rawData_t & rawData) {
    start    = rawData.get4to4u();
    interval = rawData.get4to4u();
  }
  void setStimer(rawData_t & rawData) const {
    rawData.set4(start);
    rawData.set4(interval);
  }
};  
typedef unsigned long clock_time_t;
#define CLOCK_CONF_SECOND 1000
typedef unsigned u32_t;

struct uip_ds6_nbr_t {
  uint8_t       nscount;
  uint8_t       isrouter;
  uint8_t       state;
  uip_ipaddr_t  ipaddr;
  uip_lladdr_t  lladdr;
  struct stimer reachable;
  struct stimer sendns;
  clock_time_t  last_lookup;
  void getReceivedRecord(rawData_t & rawData) {
    nscount  = rawData.get1to1u();
    isrouter = rawData.get1to1u();
    state    = rawData.get1to1u();
    rawData.getIpAddr(ipaddr);
    rawData.getLlAddr(lladdr);
    reachable.getStimer(rawData);
    sendns.getStimer(rawData);
    last_lookup = rawData.get8to8u();
  }
  void setSendRecord(rawData_t & rawData) const {
    rawData.set1(nscount);
    rawData.set1(isrouter);
    rawData.set1(state);
    rawData.setIpAddr(ipaddr);
    rawData.setLlAddr(lladdr);
    reachable.setStimer(rawData);
    sendns.setStimer(rawData);
    rawData.set8(last_lookup);
  }
#if 0
  void trace(trace_t & Trace) const {
    char ipaddrStr [5*8+5];
    uip_ipaddr_t(ipaddr).getIpAddrStr(ipaddrStr);
    char lladdrStr[5*4];
    lladdr.str(lladdrStr);   
    char reachableStr[64];
    reachable.trace(reachableStr);
    char sendnsStr[64];
    sendns.trace(sendnsStr);
    Trace.printf("nbr: nscount=%d,isrouter=%d,state=%d,ipaddr=%s,lladdr=%s,reachable=%s,sendns=%s,last_lookup=%lx\n",
		 nscount,
		 isrouter,
		 state,
		 ipaddrStr,
		 lladdrStr,
		 reachableStr,
		 sendnsStr,
		 last_lookup);
  }
#endif
}; // class uip_ds6_nbr_t
struct uip_ds6_defrt_t {
  uint8_t       isinfinite;
  uip_ipaddr_t  ipaddr;
  struct stimer lifetime;
  void getReceivedRecord(rawData_t & rawData) {
    isinfinite = rawData.get1to1u();
    rawData.getIpAddr(ipaddr);
    lifetime.getStimer(rawData);
  }
  void setSendRecord(rawData_t & rawData) const {
    rawData.set1(isinfinite);
    rawData.setIpAddr(ipaddr);
    lifetime.setStimer(rawData);
  }
#if 0
  void trace(trace_t & Trace) const {
    char ipaddrStr [5*8+5];
    uip_ipaddr_t(ipaddr).getIpAddrStr(ipaddrStr);
    char lifetimeStr[32];
    lifetime.trace(lifetimeStr);
    Trace.printf("defrt: isinfinite=%d,ipaddr=%s,lifetime=%s\n",
		 isinfinite,
		 ipaddrStr,
		 lifetimeStr);
  }
#endif
}; // class uip_ds6_defrt_t
struct uip_ds6_prefix_t {
  uint8_t       length;
  uint8_t       advertise;
  uint8_t       l_a_reserved; /**< on-link and autonomous flags + 6 reserved bits */
  uip_ipaddr_t  ipaddr;
  u32_t         vlifetime;
  u32_t         plifetime;
public:
  void getReceivedRecord(rawData_t & rawData) {
    length       = rawData.get1to1u();
    advertise    = rawData.get1to1u();
    l_a_reserved = rawData.get1to1u();
    rawData.getIpAddr(ipaddr); 
    vlifetime    = rawData.get4to4u();
    plifetime    = rawData.get4to4u();
  }
  void setSendRecord(rawData_t & rawData) const {
    rawData.set1(length);
    rawData.set1(advertise);
    rawData.set1(l_a_reserved);
    rawData.setIpAddr(ipaddr);
    rawData.set4(vlifetime);
    rawData.set4(plifetime);
  }
#if 0
  void trace(trace_t & Trace) const {
    char ipaddrStr [5*8+5];
    uip_ipaddr_t(ipaddr).getIpAddrStr(ipaddrStr);
    Trace.printf("prefix: length=%d,advertise=%d,ipaddr=%s,vlifetime=%d,plifetime=%d\n",
		 length,
		 advertise,
		 ipaddrStr,
		 vlifetime,
		 plifetime);
  }
#endif
}; // class uip_ds6_prefix_t
struct uip_ds6_route_t {
  uint8_t       length;
  uint8_t       metric;
  uip_ipaddr_t  ipaddr;
  uip_ipaddr_t  nexthop;
  void getReceivedRecord(rawData_t & rawData) {
    length = rawData.get1to1u();
    metric = rawData.get1to1u();
    rawData.getIpAddr(ipaddr); 
    rawData.getIpAddr(nexthop); 
  }
  void setSendRecord(rawData_t & rawData) const {
    rawData.set1(length);
    rawData.set1(metric);
    rawData.setIpAddr(ipaddr);
    rawData.setIpAddr(nexthop);
  }
#if 0
  void trace(trace_t & Trace) const {
    char ipaddrStr [5*8+5];
    uip_ipaddr_t(ipaddr).getIpAddrStr(ipaddrStr);
    char nexthopStr[5*8+5];
    uip_ipaddr_t(nexthop).getIpAddrStr(nexthopStr);
    Trace.printf("route: length=%d,metric=%d,ipaddr=%s,nexthop=%s\n",
		 length,
		 metric,
		 ipaddrStr,
		 nexthopStr);
  }
#endif
}; // class uip_ds6_route_t
static const char * const energest_type_descr [] = {
  "CPU",
  "LPM",
  "IRQ",
  "LED_GREEN",
  "LED_YELLOW",
  "LED_RED",
  "TRANSMIT",
  "LISTEN",
  
  "FLASH_READ",
  "FLASH_WRITE",
  
  "SENSORS",
  
  "SERIAL",
};
class energy_t {
  enum energest_type {
    ENERGEST_TYPE_CPU,
    ENERGEST_TYPE_LPM,
    ENERGEST_TYPE_IRQ,
    ENERGEST_TYPE_LED_GREEN,
    ENERGEST_TYPE_LED_YELLOW,
    ENERGEST_TYPE_LED_RED,
    ENERGEST_TYPE_TRANSMIT,
    ENERGEST_TYPE_LISTEN,
    
    ENERGEST_TYPE_FLASH_READ,
    ENERGEST_TYPE_FLASH_WRITE,
    
    ENERGEST_TYPE_SENSORS,
    
    ENERGEST_TYPE_SERIAL,
    
    ENERGEST_TYPE_MAX
  };
  unsigned long rtimer_now;
  unsigned long current[ENERGEST_TYPE_MAX]; // rtimer units
public:
  void getReceivedRecord(rawData_t & rawData) {
    rtimer_now = rawData.get4to4u();
    for(unsigned i=0;i<ENERGEST_TYPE_MAX;i++)
      current[i] = rawData.get4to4u();
  }
  void setSendRecord(rawData_t & rawData) const {
    rawData.set4(rtimer_now);
    for(unsigned i=0;i<ENERGEST_TYPE_MAX;i++)
      rawData.set4(current[i]);
  }
#if 0
  void trace(trace_t & Trace) const {
    const unsigned long totalRtimerCpu = current[ENERGEST_TYPE_CPU] + current[ENERGEST_TYPE_LPM]; // bosse ou bosse pas!
    if (totalRtimerCpu==0) // personne de bosse... (contiki default)
      Trace.printf("energy: not reported\n");
    else { // totalRtimerCpu>0
      Trace.printf("energy: NOW=%d\n",rtimer_now);
      for(unsigned i=0;i<ENERGEST_TYPE_MAX;i++) {
	switch(i) {
	case ENERGEST_TYPE_CPU:
	case ENERGEST_TYPE_LPM:
	  Trace.printf("energy: %s=%lu %d%% %d%%(NOW)\n",
		       energest_type_descr[i],
		       current[i],
		       (100*current[i])/totalRtimerCpu,
		       (100*current[i])/rtimer_now);
	  break;
	default:
	  Trace.printf("energy: %s=%lu %d%%(NOW)\n",
		       energest_type_descr[i],
		       current[i],
		       (100*current[i])/rtimer_now);
	}
      } // for(unsigned i=0;i<ENERGEST_TYPE_MAX;i++)
    } // totalRtimerCpu>0
  }
#endif
}; // class energy_t
class tcpip_server_t { // how the node adress the server
  unsigned long  rtimer;
  uip_ipaddr_t   ipaddr;
  unsigned short port;
public:
  void getReceivedRecord(rawData_t & rawData) {
    rtimer = rawData.get4to4u();
    rawData.getIpAddr(ipaddr); 
    port   = rawData.get2to2u();
  }
  void setSendRecord(rawData_t & rawData) const {
    rawData.set4(rtimer);
    rawData.setIpAddr(ipaddr);
    rawData.set2(port);
  }
#if 0
  void trace(trace_t & Trace) const {
    char ipaddrStr[5*8+5];
    uip_ipaddr_t(ipaddr).getIpAddrStr(ipaddrStr);
    Trace.printf("tcpip_server: t=%d, %s.%d\n",rtimer,ipaddrStr,port);
  }
#endif
}; // class tcpip_server_t
class radio_info_t {
  class dBm_t {
  public:
    signed char dBm;
    void set(signed char dbm) {
      dBm = dbm;
    }
    void trace(char * buffer) const {
      sprintf(buffer,"%d dBm",dBm);
    }
  };
  unsigned long  rtimer;
  unsigned char  channel;            // chan number
  unsigned short panid;              // 16-bit PAN id to use for filtering packets when address filtering is enabled.
  unsigned long  eui64;
  unsigned short nodeId;             // nodeId the 16-bit address to use for filtering short-addressed
  dBm_t EdCcaThreshold;              // he Energy Detection Clear Channel Assessment threshold in units of dBm.
  dBm_t transmitPower;               // radio transmit power level in units of dBm
  bool RadioAddressFilteringEnabled; // TRUE if address filtering is enabled, FALSE otherwise.
  bool RadioDeviceIsCoordinator;     // TRUE if the node is configured as a coordinator, FALSE otherwise.
  dBm_t RadioEnergyDetection;        //  gets a reading of the average energy detected over the previous eight symbol periods (128us total) dBm
  unsigned short RadioGetPowerMode;  // the radio power mode (boost/normal, bi-directional/alternate transmit path) encoded as bits in a 16-bit word
public:
  void getReceivedRecord(rawData_t & rawData) {
    rtimer                       = rawData.get4to4u();
    channel                      = rawData.get1to1u();
    panid                        = rawData.get2to2u();
    eui64                        = rawData.get4to4u();
    EdCcaThreshold.set(rawData.get1to1s());
    transmitPower.set(rawData.get1to1s());
    RadioAddressFilteringEnabled = (rawData.get1to1u() != 0);
    RadioDeviceIsCoordinator     = (rawData.get1to1u() != 0);
    RadioEnergyDetection.set(rawData.get1to1s());
    RadioGetPowerMode            = rawData.get2to2u();
  }
  void setSendRecord(rawData_t & rawData) const {
    rawData.set4(rtimer);
    rawData.set1(channel);
    rawData.set2(panid);
    rawData.set4(eui64);
    rawData.set1(EdCcaThreshold.dBm);
    rawData.set1(transmitPower.dBm);
    rawData.set1(RadioAddressFilteringEnabled);
    rawData.set1(RadioDeviceIsCoordinator);
    rawData.set1(RadioEnergyDetection.dBm);
    rawData.set2(RadioGetPowerMode);
  }
#if 0
  void trace(trace_t & Trace) const {
    char EdCcaThresholdStr[20];
    EdCcaThreshold.trace(EdCcaThresholdStr);
    char transmitPowerStr[20];
    transmitPower.trace(transmitPowerStr);
    char RadioEnergyDetectionStr[20];
    RadioEnergyDetection.trace(RadioEnergyDetectionStr);
    Trace.printf("radio_info: t=%d channel=%d panid=0x%016x,eui64=0x%08x,EdCcaThreshold=%s,transmitPowerS=%s,"
		 "RadioAddressFilteringEnabled=%d,RadioDeviceIsCoordinator=%d,RadioEnergyDetection=%s,RadioGetPowerMode=0x04x\n",
		 rtimer,
		 channel,
		 panid,
		 eui64,
		 EdCcaThresholdStr,
		 transmitPowerStr,
		 RadioAddressFilteringEnabled,
		 RadioDeviceIsCoordinator,
		 RadioEnergyDetectionStr,
		 RadioGetPowerMode);
  }
#endif
}; // class radio_info_t
class accRelative_t {
public:
  unsigned short dt;
  signed char    dx;
  signed char    dy;
  signed char    dz;
  void set0(void) {
    dx=0;
    dy=0;
    dz=0;
    dt=0;
  }
  void set(const signed char    dX,
	   const signed char    dY,
	   const signed char    dZ,
	   const unsigned short dT) {
    dx = dX;
    dy = dY;
    dz = dZ;
    dt = dT;
  }
  void getReceivedRecord(rawData_t & rawData) {
    // TBD endian remote -> PC DT
    dt = rawData.get2to2u();
    dx = rawData.get1to1s();
    dy = rawData.get1to1s();
    dz = rawData.get1to1s();
    fprintf(stderr,
	    "dt=%d\n",
	    dt);
  }
  void setSendRecord(rawData_t & rawData) const {
    rawData.set2(dt);
    rawData.set1(dx);
    rawData.set1(dy);
    rawData.set1(dz);
  }
}; // TBD delata overflow

class accAbsolute_t {
public:
  unsigned long long t;
  signed short       x;
  signed short       y;
  signed short       z;
  void set0(void) {
    x=0;
    y=0;
    z=0;
    t=0;
  } 
  void set(const signed short       X,
	   const signed short       Y,
	   const signed short       Z,
	   const unsigned long long T) {
    x=X;
    y=Y;
    z=Z;
    t=T;
  }
  void addRelative(const accRelative_t & ar) {
    x += ar.dx;
    y += ar.dy;
    z += ar.dz;
    t += ar.dt;
  }
  void getReceivedRecord(rawData_t & rawData) {
    t = rawData.get4to8u();
    x = rawData.get2to2s();
    y = rawData.get2to2s();
    z = rawData.get2to2s();
  }
  void setSendRecord(rawData_t & rawData) const {
    rawData.set4(t);
    rawData.set2(x);
    rawData.set2(y);
    rawData.set2(z);
  }
#if 0
  void trace(trace_t & Trace) const {
    Trace.printf("%lld %d %d %d\n",
		 t,
		 x,
		 y,
		 z);
  }
#endif
};

class tempAbsolute_t {
public:
  unsigned long long t;
  signed short       temperature;
  void getReceivedRecord(rawData_t & rawData) {
    t = rawData.get4to8u();
    temperature = rawData.get2to2s();
  }
  void setSendRecord(rawData_t & rawData) const {
    rawData.set4(t);
    rawData.set2(temperature);
  }
#if 0
  void set(const unsigned long long T,
	   const signed short Temperature) {
    t = T;
    temperature = Temperature;
  }
#endif
#if 0
  void trace(trace_t & Trace) const {
    Trace.printf("%lld %d\n",
		 t,
		 temperature);
  }
#endif
}; 

#endif // #ifndef RECORDS_H__
