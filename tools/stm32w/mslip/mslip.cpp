/* mslip.cpp
*/

/*****************************************************************************/
/*** greennet interface on pc                                              ***/
/***                                                                       ***/
/*** Demonstrate IPv6 connections linux tun interface and usb ports        ***/
/*****************************************************************************/
// configuration
#define NONBLOCKING_SOCKET 1
#define MAX_REPLY_ARGS     (3)
#define SLIP_BAUD          (115200)
#define NB_MB851           (14)
#define NETWORK_SETUP_TIME_IN_SECOND         (5)
// end configuration

#define AVERAGE_BYTES_PER_IP_PACKET          (52)
#define MAX_IP_PACKETS_PER_SECOND            (SLIP_BAUD/(AVERAGE_BYTES_PER_IP_PACKET*8))
#define MAX_IP_PACKETS_PER_TARGET_PER_SECOND (MAX_IP_PACKETS_PER_SECOND/NB_MB851)
// UDP_POLL_TIMEOUT in ms
//#define UDP_POLL_TIMEOUT                         (1000/MAX_IP_PACKETS_PER_TARGET_PER_SECOND)
#define UDP_POLL_TIMEOUT (100)
// URGENT_POLL_TIMEOUT in ms
#define URGENT_POLL_TIMEOUT (100)

#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <resolv.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/poll.h>
#include <arpa/inet.h>
#include <signal.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <ctype.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/timeb.h>
#include <sys/time.h>
#include <assert.h>

#include "records.h"
#include "ippacket.h"

struct ugid_t {
  int uid;
  int gid;
  ugid_t(){}
  ugid_t(const int Uid,
	 const int Gid) :
    uid(Uid),
    gid(Gid)
  {}
  void get() {
    uid = geteuid();
    gid = getegid();
  } // stack
  void printCurrent(void) const {
    fprintf(stderr,"geteuid=%d,getegid=%d\n",geteuid(),getegid()); 
  }
  void set(void) const {
    int res;
    res = setegid(gid);
    if(res<0) { // user required (access to OS network & /dev)
      perror("setegid:");
      printCurrent();
      fprintf(stderr,"getegid(%d): setegid %d fails\n",getegid(),gid);
      assert(0);
    }
    res = seteuid(uid);
    if(res<0) { // user required (access to OS network & /dev)
      perror("seteuid:");
      printCurrent();
      fprintf(stderr,"geteuid(%d): seteuid %d fails\n",geteuid(),uid);
      assert(0);
    }
  }
}; // struct ugid_t;
static ugid_t ug_fm5(1000,1000);
static const ugid_t ug_root(0,0);
class perm_t {
  unsigned sp;
  ugid_t   prevUgid[10];
public:
  perm_t() : sp(0) {}
  void rootRequired(void) {
    assert(sp<10);
    prevUgid[sp++] = ugid_t(geteuid(),getegid()); 
    ug_root.set();
 }
  void userRequired(void) {
    assert(sp<10);
    prevUgid[sp++] = ugid_t(geteuid(),getegid());
    ug_fm5.set();
  }
  void pop(void) {
    assert(sp>0);
    const ugid_t prev = prevUgid[--sp];
    prev.set();
  }
};
perm_t perm; // TBD find uid

class sysErr_t {
  int ret;
  int sysErrno;
  char errorMsg[1024];
 public:
  sysErr_t(void) {
    ret         = 0;
    sysErrno    = 0;
    errorMsg[0] = '\0';
  }
  void panic(int retCode,const char * const format, ...) {
    ret      = retCode;
    sysErrno = errno;
    strcpy(errorMsg,"ERROR: ");
    va_list ap;
    va_start(ap, format);
    vsprintf(errorMsg+strlen(errorMsg), format,ap);
    va_end(ap);
    perror(errorMsg);
  }
};

class trace_t {
  class stream_t {
    char prefix[1024];
    char filename[1024];
    int  fd;
    sysErr_t sysErr;
  public:
    void activate(void) {
      if ((fd<0) && (filename[0]!=0)) {
	perm.userRequired();
	fprintf(stderr,"open log file '%s' ",filename);
	ugid_t().printCurrent();
	fd = ::open(filename,O_WRONLY|O_CREAT|O_TRUNC/*|O_APPEND*/|O_LARGEFILE,0666);
	if (fd<0) {
	  sysErr.panic(fd,"cannot open %s file in write mode\n",filename);
	  ugid_t().printCurrent();
	}
	fprintf(stderr,"fd=%d ",fd);
	const int res = ::write(fd,filename,strlen(filename));
	if (res<0) {
	  sysErr.panic(res,"cannot write header to '%s' log file\n",fd,filename);
	  ugid_t().printCurrent();
	}
	perm.pop(); 
      }
    }
    void desactivate(void) {
      if (fd>2) {
	perm.userRequired();
	fprintf(stderr,"close log file '%s' ",filename);
	const int res = ::close(fd);
	if (res<0) {
	  sysErr.panic(res,"cannot close %d '%s' log file\n",fd,filename);
	  ugid_t().printCurrent();
	}
	perm.pop(); 
	fd = -1;
      }
    }
    stream_t(const char * const Prefix,
	     const char * const Filename) {
      if (Prefix!=NULL)
	strcpy(prefix,Prefix);
      else
	prefix[0]='\0';
      if (Filename!=NULL)
	strcpy(filename,Filename);
      else
	filename[0]='\0';
      if (strcmp(filename,"stdout")==0)
	fd = 1;
      else if (strcmp(filename,"stderr")==0)
	fd = 2;
      else
	fd = -1;
      activate();
    } // stream_t(const char * const Prefix,const char * const Filename)
    void addPrefix(void) {
      if (fd<0)
	return;
      char buffer[128];
      buffer[0] = '\n';
      int size = 1;
      if (prefix[0]!=0) 
	size += sprintf(buffer,"%s: ",prefix);
      perm.userRequired();
      const int ret = ::write(fd,buffer,size);
      if (ret != size) {
	sysErr.panic(fd,"cannot write prefix %d/%d bytes to %s file (fd=%d)",ret,size,filename,fd);
	ugid_t().printCurrent();
      }
      perm.pop();
    } // void addPrefix(void)
    void write(const char * const userMsg) {
      if (fd<0)
	return;
      for(unsigned i=0;userMsg[i]!=0;) {
	if ((userMsg[i]=='\n') && (userMsg[i+1]=='\0'))
	  addPrefix();
	int size = 0;
	bool writeIt  = false;
	do {
	  switch (userMsg[i+size]) {
	  case '\n':
	    size++;
	  case 0:
	    writeIt = true;
	    break;
	  default:
	    size++;
	  } // switch (userMsg[i+size])
	} while(!writeIt);
	perm.userRequired();
	const int ret = ::write(fd,&userMsg[i],size);
	if (ret != size) {
	  sysErr.panic(fd,"cannot write %d/%d bytes to %s file (fd=%d)",ret,size,filename,fd);
	  ugid_t().printCurrent();
	}
	perm.pop();
	i += size;
      } // for(unsigned i=0;userMsg[i]!=0;i++)
    } // void write(const char * const userMsg)
    ~stream_t(void) {
      desactivate();
    }
  }; // class stream_t
  stream_t first,second;
public:
  //  trace_t(void) : first(NULL,NULL),second(NULL,NULL) {}
  trace_t(const char * const Prefix1,
	  const char * const Filename1,
	  const char * const Prefix2,
	  const char * const Filename2) : first(Prefix1,Filename1),second(Prefix2,Filename2) {}
  void printf(const char * const format, ...) {
    char userMsg[10*1024];
    va_list ap;
    va_start(ap, format);
    vsprintf(userMsg,format,ap);
    first.write(userMsg);
    second.write(userMsg);
  }
  void addPrefix(void) {
    first.addPrefix();
    second.addPrefix();
  }
  void write(const char * const buffer,
	     const unsigned int size) {
    char userMsg[10*1024];
    strncpy(userMsg,buffer,size);
    userMsg[size]=0;
    second.write(userMsg);
    first.write(userMsg);
  }   
  //  int ssystem(const char *fmt, ...) __attribute__((__format__ (__printf__, 1, 2)));

  int ssystem(const char *fmt, ...) {
    char cmd[128];
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(cmd, sizeof(cmd), fmt, ap);
    va_end(ap);
    printf("%s\n",cmd);
    return system(cmd);
  }
}; // class trace_t

trace_t * gnTrace = NULL;

static int got_sigalarm;
static void sigalarm(int signo) {
  got_sigalarm = 1;
  return;
}
static void sigalarm_reset(void) {
#ifdef linux
#define TIMEOUT (997*1000)
#else
#define TIMEOUT (2451*1000)
#endif
  //  ualarm(TIMEOUT, TIMEOUT);
  got_sigalarm = 0;
}

//#define PROGRESS(s) fprintf(stderr, s)
#define PROGRESS(s) do { } while (0)

struct slipPort_t {
  int      portFd;      // serialIO
  char     portName[64];
  sysErr_t sysErr;
  enum {
    SERIAL_IO,
    SOCKET,
    FILESTREAM,
  } portType;
  void cleanup(void) {
    if (portFd>=0) {
      const bool root = (portType==SERIAL_IO);
      if (root) perm.rootRequired();
      fprintf(stderr,"closing slipPort fd=%d '%s'\n",portFd,portName);
      const int res = ::close(portFd);
      if (res<0) {
	sysErr.panic(res,"cannot close fd=%d\n",portFd);
	ugid_t().printCurrent();
      }
      if (root) perm.pop();
      gnTrace->printf("disconnect %s\n",portName);
      portFd = -1;
    }
    sysErr = sysErr_t(); // clear error
  } // void cleanup(void);
  const char * getPortName(void) const { return portName; }
  int   getPortFd(void) const { return portFd;  }
  ~slipPort_t(void) {
    cleanup();
  }
}; // class socketOrSerialIO_t

class serialIO_t : public slipPort_t {
 public:
  serialIO_t(const int id) {
    portType = SERIAL_IO; 
    sprintf(portName,"/dev/ttyUSB%d",id);
    perm.rootRequired();
    portFd = ::open(portName, O_RDWR | O_NONBLOCK);
    perm.pop();
    if(portFd == -1) {
      sysErr.panic(portFd, "can't open portName ``%s''",portName);
      return;
    }
    struct termios tty;
    speed_t speed = B115200;
    int i,ret;
 
    perm.rootRequired();
#if 0
    if((ret=tcflush(portFd, TCIOFLUSH)) == -1) { sysErr.panic(ret,"tcflush ``%s''",portName); goto error;}
#endif

    if((ret=tcgetattr(portFd, &tty)) == -1) { sysErr.panic(ret,"tcgetattr ``%s''",portName); goto error;}

    cfmakeraw(&tty);

    /* Nonblocking read. */
    tty.c_cc[VTIME] = 0;
    tty.c_cc[VMIN] = 0;
    tty.c_cflag &= ~CRTSCTS;
    tty.c_cflag &= ~HUPCL;
    tty.c_cflag &= ~CLOCAL;

    cfsetispeed(&tty, speed);
    cfsetospeed(&tty, speed);

    if((ret=tcsetattr(portFd, TCSAFLUSH, &tty)) == -1) { sysErr.panic(ret,"tcsetattr ``%s''",portName); goto error;}

    /* Nonblocking read and write. */
    /* if(fcntl(portFd, F_SETFL, O_NONBLOCK) == -1) err(1, "fcntl"); */

    tty.c_cflag |= CLOCAL;
    if((ret=tcsetattr(portFd, TCSAFLUSH, &tty)) == -1) { sysErr.panic(ret,"tcsetattr ``%s''",portName); goto error;}

    i = TIOCM_DTR;
    if((ret=ioctl(portFd, TIOCMBIS, &i)) == -1) { sysErr.panic(ret,"ioctl ``%s''",portName); goto error;}

#if 0
    //usleep(10*1000);		/* Wait for hardware 10ms. */
    usleep(1*1000);		/* Wait for hardware 10ms. */

    /* Flush input and output buffers. */
    if((ret=tcflush(portFd, TCIOFLUSH)) == -1) { sysErr.panic(ret,"tcflush ``%s''",portName); goto error;}
    gnTrace->printf("connect %s at 115200 bauds\n",portName);
#endif
    perm.pop();
    return;
  error:
    cleanup();
  }
}; // class serialIO_t

class socketIO_t : public slipPort_t {
 public:
  socketIO_t(const int  PortFd,
	     const char PortName[64]) {
    portType = SOCKET; 
    portFd   = PortFd;
    strcpy(portName,PortName);
    sysErr = sysErr_t();
  }
}; // class socketIO_t : public slipPort_t 

#include <linux/if.h>
#include <linux/if_tun.h>

class remoteClientAddr_t {
  int                 clientSd; // socket descriptor  <0 if no client
  struct sockaddr_in6 clientSockAddr;
  socklen_t           clientSockAddrlen;
  sysErr_t            sysErr;
 public:
  remoteClientAddr_t() {
    clientSd    = -1;
    bzero(&clientSockAddr, sizeof(clientSockAddr));
    clientSockAddrlen = sizeof(clientSockAddr); // init mandatory beforef accept
  }
  int getClientSd(void) const { return clientSd; }
  bool closed(void) const { return clientSd<0; } // to handle closed by peer
  const struct in6_addr & getIn6Addr(void) const { return clientSockAddr.sin6_addr; }
  void getIpAddrFilemane(char buffer[5*8]) const {
    sprintf(buffer,
	    "%02x%02x_%02x%02x_%02x%02x_%02x%02x_%02x%02x_%02x%02x_%02x%02x_%02x%02x",
	    clientSockAddr.sin6_addr.s6_addr[0],
	    clientSockAddr.sin6_addr.s6_addr[1],
	    clientSockAddr.sin6_addr.s6_addr[2],
	    clientSockAddr.sin6_addr.s6_addr[3],
	    clientSockAddr.sin6_addr.s6_addr[4],
	    clientSockAddr.sin6_addr.s6_addr[5],
	    clientSockAddr.sin6_addr.s6_addr[6],
	    clientSockAddr.sin6_addr.s6_addr[7],
	    clientSockAddr.sin6_addr.s6_addr[8],
	    clientSockAddr.sin6_addr.s6_addr[9],
	    clientSockAddr.sin6_addr.s6_addr[10],
	    clientSockAddr.sin6_addr.s6_addr[11],
	    clientSockAddr.sin6_addr.s6_addr[12],
	    clientSockAddr.sin6_addr.s6_addr[13],
	    clientSockAddr.sin6_addr.s6_addr[14],
	    clientSockAddr.sin6_addr.s6_addr[15]);
  }
  void getIpAddrStr(char buffer[5*8]) const {
    inet_ntop(AF_INET6,
	      &clientSockAddr.sin6_addr.s6_addr[0],
	      buffer,
	      sizeof(clientSockAddr.sin6_addr.s6_addr));
  }
  void cleanup(void) {
    if (clientSd >= 0) {
      char buffer[5*8];
      getIpAddrStr(buffer);
      fprintf(stderr,"close connection from %s\n",buffer);
      close(clientSd);
      clientSd = -1;
    }
  }
  int acceptIfAny(const int serverSd) {
    clientSd                   = -1;
    bzero(&clientSockAddr, sizeof(clientSockAddr));
    clientSockAddrlen          = sizeof(clientSockAddr); // init mandatory beforef accept
    clientSockAddr.sin6_family = AF_INET6; // !!!!
    struct pollfd fds[1]; /* cleared with bzero() */
    fds[0].fd                  = serverSd;
    fds[0].events              = POLLIN | POLLRDHUP;
    /* POLLRDHUP (since Linux 2.6.17)
       Stream socket peer closed connection, or shut down  writ‐
       ing  half  of  connection.   The _GNU_SOURCE feature test
       macro must be defined in order to obtain this definition.
    */
    fds[0].revents = 0;
    int ret;
    if ( (ret = poll(fds, 1, 0)) > 0 ) {
      if (fds[0].revents & (POLLIN | POLLRDHUP)) { /* If input ready, echo it back */
	//fprintf(stderr,"."); 
	clientSd = accept(serverSd,
			  NULL,  //(struct sockaddr *)&clientSockAddr,
			  NULL); //&clientSockAddrlen);
	//  fprintf(stderr," returns %d\n",clientSd); 
	if (clientSd<0) {
	  if ((errno==EAGAIN) || (errno==EWOULDBLOCK)) {
	  } else
	    sysErr.panic(clientSd,"accept returns %d ",clientSd);
	  return 0;
	} else {
	  int ret;
	  if ( (ret=fcntl(clientSd, F_SETFL, O_NONBLOCK)) != 0 ) {
	    sysErr.panic(ret,"setting nonblocking I/O for non blocking clientSd=%d\n",clientSd);
	    clientSd = -1;
	    return 0;
	  }
	  /*****************************************************************/
	  /* Display the client address.  Note that if the client is       */
	  /* an IPv4 client, the address will be shown as an IPv4 Mapped   */
	  /* IPv6 address.                                                 */
	  /*****************************************************************/
	  getpeername(clientSd,
		      (struct sockaddr *)&clientSockAddr,
		      &clientSockAddrlen);
	  char clientAddrStr[5*8];
	  if(inet_ntop(AF_INET6,
		       &clientSockAddr.sin6_addr,
		       clientAddrStr,
		       sizeof(clientAddrStr))) {
            gnTrace->printf("Client address is %s\n", clientAddrStr);
            gnTrace->printf("Client port is %d\n", ntohs(clientSockAddr.sin6_port));
	  }
	  gnTrace->printf("tcpConnection from %s.%d accepted (sd=%d) ======================================\n",
			 clientAddrStr,
			 ntohs(clientSockAddr.sin6_port),
			 clientSd);
	  return 1;
	}
      } // if ((fds[0].revents & POLLIN))  /* If input ready, echo it back */
    } // if ( (ret = poll(fds, 1, 0)) > 0 )
    return 0;
  } // int acceptIfAny(const int serverSd)
}; // class remoteClientAddr_t

class tun_t; // forward

class immoConnection_t {
  remoteClientAddr_t & immoClientAddr;
  sysErr_t             sysErr;
  char                 recBuffer[1024];
  unsigned             received,expected;
  unsigned             level; // of perenthsis
  void sendBuff(const int                    clientSd,
		const  unsigned char * const sendBuffer,
		const unsigned               size) {
    if (clientSd < 0) // closed by peer (immo)? 
      return;
    for(unsigned sent=0; sent < size;) {
      int res = ::send(clientSd,
		       &sendBuffer[sent],
		       size-sent,
		       0);
      if (res>0) {
	sent += res;
      } else {
	if ((errno==EAGAIN) || (errno==EWOULDBLOCK)) {
	  continue;
	} else {
	  sysErr.panic(res,"send");
	  immoClientAddr.cleanup();
	  return;
	}
      }
    } // for(int sent=0;sent<toSend)
  } // void sendBuff(...)
public:
  immoConnection_t(remoteClientAddr_t & ImmoClientAddr);
  bool closed(void) const;
  void immoPacket(const unsigned char recType,
		  const unsigned char tunType,
		  const unsigned char tunId,
		  const unsigned char * const  sendBuffer,
		  const unsigned      size);
  int receiveFromImmo(void);
  int pollImmoConnection(/*const slipSet_t & slipSet*/void);
  void onConnectCallback(const tun_t * const tun);
  void onDisconnectCallback(const tun_t * const tun);
}; // class immoConnection_t

class tun_t {
 public:
  enum tunType_t {
    TUN,
    TAP
  };
 private:
  int          id;
  tunType_t    tunType;
  char         tundev[32];
  int          tunfd;       // tun
  int          step;
  sysErr_t     sysErr;
  uip_ipaddr_t ipAddr;
  unsigned     prefixSize;
  trace_t    * trace;
  class immoConnection_t * immoConnection;
  void cleanup(void); // impl after immoConnection_t def
 public:
  bool invalid(void) const { return tunfd < 0; }
  tun_t(const tunType_t    TunType,
	const int          id,
	const char * const ipAddrStrWithPrefix,
	trace_t          * Trace,
	immoConnection_t * const ImmoConnection); // impl after immoConnection_t def
  int getTunId(void) const { return id; }
  tunType_t getTunType(void) const { return tunType; }
  const char * getTundev(void) const { return tundev; }
  int   getTunFd(void) const { return tunfd;  }
  const uip_ipaddr_t & getIpAddr(void) const { return ipAddr;  }
  unsigned printConfig(char * buffer) const {
    unsigned size = 0;
    buffer[size++] = '"';
    ipAddr.str(&buffer[size]);
    size = strlen(buffer);
    buffer[size++] = '"';
    return size;
  } // unsigned printConfig(char * buffer) const
  ~tun_t(void) {
    cleanup();
  }
}; // class tun_t

class slip_t {
  slip_t     * next;
  int          id;
  slipPort_t * slipPort;                // contructor may vary
  unsigned   & nbTun;
  tun_t      * tunPort;                 // may be NULL if just printf
#define SLIP_END     0300
#define SLIP_ESC     0333
#define SLIP_ESC_END 0334
#define SLIP_ESC_ESC 0335
  class tun2slipPort_t {
    unsigned char      buf[2000];
    unsigned           end;
    unsigned           begin;
    sysErr_t           sysErr;
    const slipPort_t * slipPort;
    tun_t          * & tunPtr; // may be NULL if just printf
    int                verbose;
    trace_t          * tun2slipPortTrace;
   public:
    inline int empty(void) const { return end == 0; }
    inline int getSerialIOfd(void) const { return slipPort->getPortFd(); }
    inline int getTunfd(void) const { return (tunPtr==NULL) ? -1 :tunPtr->getTunFd(); }
    int send(const unsigned char c) {
      if(end >= sizeof(buf)) {
	tun2slipPortTrace->printf("send overflow\n");
	return 1;
      }
      buf[end++] = c;
      return 0;
    }
    inline int flushbuf(void) {
      if(empty()) {
	return 0;
      }
      while (end > begin) {
	perm.rootRequired();
	const int ret = write(slipPort->getPortFd(), buf + begin, (end - begin));
	if(ret == -1 && errno != EAGAIN) {
	  perm.pop();
	  sysErr.panic(ret,"write");
	  tun2slipPortTrace->printf("%s: error flushbuf write failed\n",slipPort->getPortName());
	  return 1;
	} else if(ret == -1) {
	  perm.pop();
	  PROGRESS("Q");		/* Outqueueis full! */
	  return 0;
	} else {
	  perm.pop();
	  begin += ret;
	}
      }
      begin = end = 0;
      return 0;
    } // inline int flushbuf(serial2tunState_t * const s)
    tun2slipPort_t(const int          Id,
		   tun_t          * & TunPtr,
		   const slipPort_t * SlipPort,
		   const int          Verbose) :
      slipPort(SlipPort),
      tunPtr(TunPtr),
      verbose(Verbose) {
      char Prefix1[1024];
      sprintf(Prefix1,"tun2slipPort%d",Id);
      char Filename2[1024];
      sprintf(Filename2,"tun2slipPort%d.log",Id);
      tun2slipPortTrace = new trace_t(Prefix1,
				      "stderr",
				      "",
				      Filename2);
      end   = 0;
      begin = 0;
      send(SLIP_END);
    }
    int forward_tun2slipPort(void) {
      if (tunPtr==NULL) {
	return 0;
      }
      unsigned char inbuf[2000];
      int size;
      const char * const tundev = tunPtr->getTundev();
      tun2slipPortTrace->printf("READ Packet from TUN=%s\n",tundev);
      const char * const slipPortdev = slipPort->getPortName();
      if((size = read(tunPtr->getTunFd(), inbuf, 2000)) < 0) {
	sysErr.panic(size,"%s: error tun_to_serial: read failed\n",tundev);
	return 1;
      }
      if (size==0)
	return 0;
      u_int8_t *p = inbuf;
      int i;
      if(verbose>2) {
	//if (timestamp) stamptime();
	tun2slipPortTrace->printf("Packet from TUN=%s of length %d - write SLIP=%s\n         ",tundev,size,slipPortdev);
	if (verbose>4) {
	  printf("         ");
	  for(i = 0; i < size; i++) {
	    tun2slipPortTrace->printf("%02x", p[i]);
	    if((i & 3) == 3) {
	      tun2slipPortTrace->printf(" ");
	    }
	    if((i & 15) == 15)
	      tun2slipPortTrace->printf("\n         ");
	  }
	  tun2slipPortTrace->printf("\n");
	}
      }

      /* It would be ``nice'' to send a SLIP_END here but it's not
       * really necessary.
       */
      /* slip_send(outfd, SLIP_END); */

      for(i = 0; i < size; i++) {
	switch(p[i]) {
	case SLIP_END:
	  send(SLIP_ESC);
	  send(SLIP_ESC_END);
	  break;
	case SLIP_ESC:
	  send(SLIP_ESC);
	  send(SLIP_ESC_ESC);
	  break;
	default:
	  send(p[i]);
	  break;
	}
      }
      send(SLIP_END);
      PROGRESS("t");
      return 0;
    } // int tun2slipPort(void)
    ~tun2slipPort_t() {
      if (tun2slipPortTrace != NULL)
	delete tun2slipPortTrace;
    }
  } tun2slipPort;
  class slipPort2tun_t {
    int           id;                      // record it for potential delayed tunPort creation
    char          ipAddrWithPrefix[5*8+5]; // record it for potential delayed tunPort creation
#if WITH_FDOPEN
    FILE *        inslip; // slipPort
#else
    /*
     * Read from serial, when we have a packet write it to tun. No output
     * buffering, input not buffered expet 1 char
     */
    // return 0 if Ok else error code
    // update nbTun when creating tun interface
    class inBuffer_t {
      unsigned char buffer;
      bool          empty;
      int           slipFd;
    public:
      inBuffer_t(slipPort_t * slipPort) :
	empty(true),
	slipFd(slipPort==NULL ? -1 : slipPort->getPortFd())
      {}
      enum ret_t {
	NO_BYTE,
	BYTE_RECEIVED,
	ERROR
      };
      ret_t getByte(unsigned char & byte) {
	ret_t retCode = NO_BYTE;
	if (slipFd<0)
	  return ERROR;
	if (!empty) {
	  byte    = buffer;
	  empty   = true;
	  retCode = BYTE_RECEIVED;
	} 
	// empty == true => fill buffer
	const int ret         = read(slipFd,&buffer,1);
	switch (ret) {
	case 0:
	  // keep empty = true for next time
	  break;
	case -1:
	  // keep empty = true for next time
	  if (retCode != BYTE_RECEIVED) {
	    if (errno==EAGAIN) {
	      retCode = NO_BYTE;
	    } else {
	      slipFd = -1; // error is persitent
	    }
	  } // else we don't care about read error
	  break;
	case 1:
	  if (retCode == NO_BYTE) {
	    byte    = buffer;
	    retCode = BYTE_RECEIVED;
	  } else {
	    empty   = false;
	  }
	  break;
	} // switch (ret)
	return retCode;
      } // ret_t getByte(unsigned char & byte)
      void putByte(const unsigned char byte) {
	assert(empty);
	buffer = byte;
	empty = false;
      }
    }; // class inBuffer_t 
    inBuffer_t inBuffer;
#endif
    unsigned char inbuf[2000];
    unsigned      inbufptr;
    unsigned      firstSlipEnd;
    sysErr_t      sysErr;
    tun2slipPort_t   & tun2slipPort; // modified by send prefix on border router request
    unsigned    & nbTun;
    tun_t     * & tunPtr;
    const slipPort_t * slipPort;
    int           verbose;
    trace_t     * slipPort2tunTrace;
    inline int is_sensible_string(void) {
      unsigned i;
      for(i = 1; i < inbufptr; i++) {
	if(inbuf[i] == 0 || inbuf[i] == '\r' || inbuf[i] == '\n' || inbuf[i] == '\t') {
	  continue;
	} else if (inbuf[i] < ' ' || '~' < inbuf[i]) {
	  return 0;
	}
      }
      return 1;
    } // inline int is_sensible_string(void)
    int tunRequired(const tun_t::tunType_t tunType,
		    immoConnection_t * & ImmoConnection
		   ) {
      if (tunPtr==NULL) { // open tun only when required
	tunPtr = new tun_t(tunType,
			   id,
			   ipAddrWithPrefix,
			   slipPort2tunTrace,
			   
			   ImmoConnection);
	if (tunPtr->invalid()) {
	  delete tunPtr;
	  tunPtr = NULL;
	  sysErr.panic(0,"%s: cannot create tun%d interface (%s) abort\n",slipPort->getPortName(),id,ipAddrWithPrefix);
	  // inbufptr = 0;
	  return 1;
	} else {
	  nbTun++;
	  slipPort2tunTrace->printf("%s: create tun%d interface(%s) fd=%d\n",
				    slipPort->getPortName(),
				    id,
				    ipAddrWithPrefix,
				    tunPtr->getTunFd());
	}
      }
      return 0;
    }
  public:
    slipPort2tun_t(const int          Id,
		   const char * const IpAddrWithPrefix,
		   unsigned         & NbTun,
		   tun2slipPort_t   & Tun2slipPort,
		   slipPort_t       * slipPort,
		   tun_t *          & TunPtr,  // create only when slip_t detect slip protocol on slipPort
		   const int          Verbose) :
      id(Id),
      inBuffer(slipPort),
      inbufptr(0),
      firstSlipEnd(1),
      tun2slipPort(Tun2slipPort),
      nbTun(NbTun),
      tunPtr(TunPtr),
      slipPort(slipPort),
      verbose(Verbose)
    {
      char Prefix1[1024];
      sprintf(Prefix1,"slipPort2tun%d",Id);
      char Filename2[1024];
      sprintf(Filename2,"slipPort2tun%d.log",Id);
      slipPort2tunTrace = new trace_t(Prefix1,
				      "stderr",
				      "",
				      Filename2);
      strcpy(ipAddrWithPrefix,IpAddrWithPrefix);
    }
    int forward(immoConnection_t * & ImmoConnection) {
      tun_t::tunType_t tunType = (tunPtr == NULL) ? tun_t::TUN : tunPtr->getTunType(); 
      const char * const slipPortdev = slipPort->getPortName();
      //slipPort2tunTrace->printf("forward\n");
      unsigned char c;

      inBuffer_t::ret_t retCode = inBuffer.getByte(c);
      switch (retCode) {
      case inBuffer_t::NO_BYTE:
	// keep existing bytes	inbufptr = 0;
	return 0;
      case inBuffer_t::ERROR:
	//	inbufptr = 0;
	return 1;
      case inBuffer_t::BYTE_RECEIVED:
	break;
      }
      goto after_fread;
      
    read_more:
      if(inbufptr >= sizeof(inbuf)) {
	//     if(timestamp) stamptime();
	slipPort2tunTrace->printf("*** dropping too large packet from %s:\n",slipPortdev);
	slipPort2tunTrace->write((char*)inbuf, inbufptr);
	inbufptr  = 0;
      }
      retCode = inBuffer.getByte(c);
    after_fread:
      switch (retCode) {
      case inBuffer_t::NO_BYTE:
	return 0;
      case inBuffer_t::ERROR:
	sysErr.panic(0,"%s: error serial_to_tun: read\n",slipPortdev);
	// inbufptr = 0;
	return 1;
      case inBuffer_t::BYTE_RECEIVED:
	break;
      }
      /* slipPort2tunTrace->printf(".");*/
      //      slipPort2tunTrace->printf("%c",c);
      switch(c) {
      case SLIP_END:
	if (firstSlipEnd) {
	  firstSlipEnd = 0;
	  if ((slipPort2tunTrace!=NULL) && (inbufptr>0)) {
	    slipPort2tunTrace->addPrefix();
	    slipPort2tunTrace->printf("FLUSH DEBUG: ");
	    slipPort2tunTrace->write((char *)&inbuf[0], inbufptr-1);
	  }
	  inbufptr     = 0;
	}
	if(inbufptr > 0) {	
	  const char * const tundev = tunPtr->getTundev();
	  if(inbuf[0] == '!') {
	    switch(inbuf[1]) {
	    case 'M': {
	      inbufptr = 0;
	      /* Read gateway MAC address and autoconfigure tap0 interface */
	      char macs[24];
	      int i, pos;
	      for(i = 0, pos = 0; i < 16; i++) {
		macs[pos++] = inbuf[2 + i];
		if((i & 1) == 1 && i < 14) {
		  macs[pos++] = ':';
		}
	      }
	      //          if(timestamp) stamptime();
	      macs[pos] = '\0';
	      if (tunRequired(tunType,
			      ImmoConnection)) // error
		return 1;
	      //	  slipPort2tunTrace->printf("*** Gateway's MAC address: %s\n", macs);
	      slipPort2tunTrace->printf("*** Gateway's MAC address: %s\n", macs);
	      //          if (timestamp) stamptime();
	      slipPort2tunTrace->ssystem("ifconfig %s down", tundev);
	      //          if (timestamp) stamptime();
	      slipPort2tunTrace->ssystem("ifconfig %s hw ether %s", tundev, &macs[6]);
	      //          if (timestamp) stamptime();
	      slipPort2tunTrace->ssystem("ifconfig %s up", tundev);
	      break;
	    }
	    case 'S': // prefix from sniffer (=>tap)
	    case 'P': { // prefix from edge router (=>tun)
	      /* Prefix info requested */
	      inbufptr = 0; // ack the request
	      tunType = (inbuf[1]=='S') ? tun_t::TAP : tun_t::TUN;
	      if (tunRequired(tunType,
			      ImmoConnection)) // error
		return 1;
	      const struct in6_addr & addr = tunPtr->getIpAddr().getIn6Addr();
	      int i;
	      //          if(timestamp) stamptime();
	      char buffer[5*8];
	      tunPtr->getIpAddr().str(buffer);
	      slipPort2tunTrace->printf(
		      "*** Address:%s => send %s prefix %02x%02x:%02x%02x:%02x%02x:%02x%02x\n",
		      //         slipPort2tunTrace->printf("*** Address:%s => %02x%02x:%02x%02x:%02x%02x:%02x%02x\n",
		      buffer,
		      tunPtr->getTundev(),
		      addr.s6_addr[0], addr.s6_addr[1],
		      addr.s6_addr[2], addr.s6_addr[3],
		      addr.s6_addr[4], addr.s6_addr[5],
		      addr.s6_addr[6], addr.s6_addr[7]);
	      tun2slipPort.send('!');
	      tun2slipPort.send('P');
	      for(i = 0; i < 8; i++) {
		tun2slipPort.send(addr.s6_addr[i]);
	      }
	      tun2slipPort.send(SLIP_END);
	      tun2slipPort.flushbuf(); // MFG added
	      break;
	    } // case 'S' 'P'
	    default:
	      assert(0);
	    } // switch
#define DEBUG_LINE_MARKER '\r'
	  } else if(inbuf[0] == DEBUG_LINE_MARKER) {    
	    assert(slipPort2tunTrace!=NULL);
	    slipPort2tunTrace->addPrefix();
	    //slipPort2tunTrace->printf("DEBUG_LINE_MARKER:\n");
	    slipPort2tunTrace->write((char *)inbuf + 1, inbufptr - 1);
	    inbufptr = 0;
	  } else if(is_sensible_string()) {
	    assert(slipPort2tunTrace!=NULL);
	    slipPort2tunTrace->addPrefix();
	    //slipPort2tunTrace->printf("SENSIBLE_STRING:");
	    slipPort2tunTrace->write((char *)inbuf, inbufptr);
	    inbufptr = 0;
	  } else {
	    assert(slipPort2tunTrace!=NULL);
	    //if (timestamp) stamptime();
	    slipPort2tunTrace->addPrefix();
	    if (tunRequired(tunType,
			    ImmoConnection)) // error
	      return 1;
	    const char * const tundev = tunPtr->getTundev();
	    slipPort2tunTrace->printf("Packet from SLIP=%s of length %d - write TUN=%s\n",slipPortdev,inbufptr,tundev);
	    slipPort2tunTrace->printf("         ");
	    for(unsigned i = 0; i < inbufptr; i++) {
	      if((i & 3) == 0) {
		slipPort2tunTrace->printf(" %2d ",i);
	      }
	      slipPort2tunTrace->printf("%02x",inbuf[i]);
	      if((i & 15) == 15)
		slipPort2tunTrace->printf("\n         ");
	    }
	    slipPort2tunTrace->printf("\n");
	    if (ImmoConnection!=NULL) {
	      if (tunRequired(tunType,
			      ImmoConnection)) // error
		return 1;
	      fprintf(stderr,"send packet to GUI +++++++++++++++++++\n");
	      bool isTap = (tunPtr->getTunType()==tun_t::TAP);
	      ImmoConnection->immoPacket('P', // IP packet
					 isTap ? 'S' : 'T', // sniffer or tunnel
					 tunPtr->getTunId(),
					 inbuf,
					 inbufptr);
	    }
#if 1
	    if (tunRequired(tunType,
			    ImmoConnection)) // error
	      return 1;
#endif
	    perm.rootRequired();
	    //	    sleep(2);
	    int ret;
	    if((ret = write(tunPtr->getTunFd(), inbuf, inbufptr)) != (int)inbufptr) {
	      sysErr.panic(ret,
			   "%s: serial_to_tun: write fd=%d size=%d,res=%d\n",
			   tundev,
			   tunPtr->getTunFd(),
			   inbufptr,
			   ret);
	      perm.pop();
	      inbufptr = 0;
	      return 1;
	    }
	    fprintf(stderr,"send packet to TUNNEL ---------");
	    inbufptr = 0;
	    perm.pop();
	  } // else
	  //slipPort2tunTrace->fprintf("RESET: inbufptr after write to TUN\n");
	}
	inbufptr = 0;
	break;

      case SLIP_ESC:
	if (tunRequired(tunType, // TBD case of SNIFFER starting here!!!
			ImmoConnection)) // error
	  return 1;
	retCode = inBuffer.getByte(c);
	switch (retCode) {
	case inBuffer_t::NO_BYTE:
	  /* Put ESC back and give up! */
	  inBuffer.putByte(SLIP_ESC);
	  return 0;
	case inBuffer_t::ERROR:
	  return 1;
	case inBuffer_t::BYTE_RECEIVED:
	  break;
	}

	switch(c) {
	case SLIP_ESC_END:
	  c = SLIP_END;
	  break;
	case SLIP_ESC_ESC:
	  c = SLIP_ESC;
	  break;
	}
	/* FALLTHROUGH */
      default:
	inbuf[inbufptr++] = c;
#if 1
	if (c == '\n') { 
	  int print = 1;
	  unsigned i;
	  for(i=0;i<inbufptr;i++) {
	    char c = inbuf[i];
	    if (!(c == '\r' || c == '\n' || c == '\t' || (c >= ' ' && c <= '~'))) {
	      //fprintf(stderr,"#%d (0x%x)\n",i,(unsigned char)c);
	      print = 0;
	      //break;
	    }
	  }
	  if (print) {
	    slipPort2tunTrace->addPrefix();
	    //	    slipPort2tunTrace->printf("DEBUG: ");
	    slipPort2tunTrace->write((char *)&inbuf[0], inbufptr);
	    inbufptr = 0;
	  }
	}
#endif
	break;
      } // switch
      goto read_more;
    }
  } slipPort2tun;
  sysErr_t sysErr;
  unsigned short basedelay,delaymsec;
  unsigned startsec,startmsec,delaystartsec,delaystartmsec;
 public:
  inline const tun_t * getTunPort(void) const { return tunPort; }
  void cleanup(void) {
    if (tunPort != NULL) {
      nbTun--;
      if (slipPort != NULL) {
	const char * const slipPortdev = slipPort->getPortName();
	gnTrace->printf("%s: delete tun%d interface nbTun=%d\n",slipPortdev,id,nbTun);
      }
      delete tunPort;
      tunPort = NULL;
    }
    if (slipPort != NULL) {
      slipPort->cleanup();
      slipPort = NULL;
    }
  }
  slip_t(const int          Id,
	 slipPort_t       * SlipPort,
	 const char * const IpAddrWithPrefix,
	 unsigned         & NbTun,
	 const int          verboseTun2slipPort,
	 const int          verboseslipPort2Tun) :
    id(Id),
    slipPort(SlipPort),
    nbTun(NbTun),
    tunPort(NULL), // create only when slip_t detect slip protocol on slipPort
    tun2slipPort(Id,
	    tunPort,
	    slipPort,
	    verboseTun2slipPort),
    slipPort2tun(Id,
		 IpAddrWithPrefix,
		 nbTun,
		 tun2slipPort,
		 slipPort,
		 tunPort,
		 verboseslipPort2Tun),
    basedelay(0),
    delaymsec(0) {
  } // slip_t
  void pollSlip(immoConnection_t * & ImmoConnection) {
    int maxfd = 0;
    fd_set rset, wset;
    FD_ZERO(&rset);
    FD_ZERO(&wset);
    /* do not send IPA all the time... - add get MAC later... */
    /*     if(got_sigalarm) { */
    /*       /\* Send "?IPA". *\/ */
    /*       slip_send(slipfd, '?'); */
    /*       slip_send(slipfd, 'I'); */
    /*       slip_send(slipfd, 'P'); */
    /*       slip_send(slipfd, 'A'); */
    /*       slip_send(slipfd, SLIP_END); */
    /*       got_sigalarm = 0; */
    /*     } */
    const int  slipPortFd = slipPort->getPortFd();
    const bool slipPortOk = (slipPortFd >= 0);
    if(slipPortOk) {
      if(!tun2slipPort.empty()) { /* Anything to flush? */
	FD_SET(slipPortFd, &wset);
      }
      FD_SET(slipPortFd, &rset);	/* Read from slip ASAP! */
      if(slipPortFd > maxfd) maxfd = slipPortFd;
    }
    const int  tunFd = (tunPort == NULL) ? -1 : tunPort->getTunFd();
    const bool tunOk = (tunFd >= 0);
    if (tunOk) {
      //slipTrace.printf("POLL READ TUN tun2slipPort.empty()=%d tunFd=%d\n",tun2slipPort.empty(),tunFd);
      /* We only have one packet at a time queued for slip output. */
      if (tun2slipPort.empty()) {
	FD_SET(tunFd, &rset);
	if(tunFd > maxfd) maxfd = tunFd;
      }
    }
    struct timeval timeout;
    timeout.tv_sec  = 0;
    timeout.tv_usec = 0;
    perm.rootRequired(); // by tunfd and slipPortFd (if serialIO)
    int ret = select(maxfd + 1, &rset, &wset, NULL, &timeout);
    perm.pop();
    if(ret == -1 && errno != EINTR) {
      sysErr.panic(ret,"select");
    } else if(ret > 0) {
      if (FD_ISSET(slipPortFd, &rset)) {
	//slipTrace.printf(,"SERIALIO=%s to TUN=%s\n",slipPort->getPortName(),tunPort.getTundev());
        slipPort2tun.forward(ImmoConnection);
	//slipTrace.printf("SERIALIO=%s to TUN=%s done\n",slipPort->getPortName(),tunPort.getTundev());
      }
      if (FD_ISSET(slipPortFd, &wset)) {
	//slipTrace.printf("TUN=%s to SERIALIO=%s\n",tunPort.getTundev(),slipPort->getPortName());
	tun2slipPort.flushbuf();
	//slipTrace.printf(TUN=%s to SERIALIO=%s done\n",tunPort.getTundev(),slipPort->getPortName());
	sigalarm_reset();
      }
      if(tunOk) {
	//if (tun2slipPort.empty()) { // try to read new data from tun if available
	// slipTrace.printf(,"POLL READ TUN FD_ISSET(tunFd, &rset)=%d tunFd=%d\n",FD_ISSET(tunFd, &rset),tunFd);
	if (FD_ISSET(tunFd, &rset)) {
	  /* TBD const int size= */ tun2slipPort.forward_tun2slipPort();
	} // if (FD_ISSET(tunFd, &rset))
	//}
	tun2slipPort.flushbuf();
      } // if(tunOk)
    } // else if(ret > 0)
  } // void pollSlip(void)
  unsigned printConfig(const bool first,char * const buffer) const {
    unsigned size = 0;
    if (tunPort!=NULL) {
      if (!first)
	buffer[size++] = ',';
      size += tunPort->printConfig(&buffer[size]);
    }
    return size;
  } // unsigned printConfig(char * buffer) const
  ~slip_t(void) {
    cleanup();
  } // ~slip_t(void)
}; // class slip_t

class slipSet_t {
  unsigned nbTun;  // <= nbSlip
  struct serialIo_t {
    unsigned nbSlip;
#define NB_TTYUSB (10)
    slip_t * slip[NB_TTYUSB]; // 1 entry per slipPort connection
    serialIo_t(void) {
      nbSlip = 0;
      for(int i=0;i<NB_TTYUSB;i++)
	slip[i] = NULL;
    }
    void cleanup(void) {
      for(int i=0;i<NB_TTYUSB;i++)
	if (slip[i] != NULL) {
	  gnTrace->printf("closing slip%d\n",i);
	  delete slip[i];
	  slip[i] = NULL;
	}
    } // void cleanup(void);
    inline bool slipPortConnected(const int id) const {
      char slipPortdev[32];
      sprintf(slipPortdev,"/dev/ttyUSB%d",id);
      perm.rootRequired();
      int slipPortFd = access(slipPortdev, O_RDWR);
      perm.pop(); 
      if(slipPortFd == -1) {
	return false;
      } else {
	return true;
      }
    }
    void pollSlipConnections(unsigned & nbTun,
			     immoConnection_t * & ImmoConnection) { // update nb of active tun connection
      // create/delete slip according to ttyUSB detection 
      for(int i=0;i<NB_TTYUSB;i++) {
	const bool connected = slipPortConnected(i);
	const bool inUse = (slip[i] != NULL);
	if ((!connected) && inUse) { // old
	  gnTrace->printf("closing slip%d\n",i);
	  delete slip[i];
	  slip[i] = NULL;
	  nbSlip--;
	} else if (connected && (!inUse)) { // new
	  char ipAddrWithPrefix[64];
	  sprintf(ipAddrWithPrefix,"fc00:%x::2/64",i);
	  gnTrace->printf("connecting slip%d to tun%d(%s)\n",i,i,ipAddrWithPrefix);
	  slip[i] = new slip_t(i,
			       new serialIO_t(i), // TBD delete
			       ipAddrWithPrefix,
			       nbTun,
			       5, // verboseTun2slipPort,
			       5); // verboseslipPort2Tun
	  nbSlip++;
	} else if (connected && inUse) { // working connexion
	  slip[i]->pollSlip(ImmoConnection);
	}
      } // for(int i=0;i<NB_TTYUSB;i++)
    } // void pollSlipConnections(unsigned & NbTun) { // update nb of active tun connection
    unsigned printConfig(bool & first,char * const buffer) const {
      unsigned size = 0;
      for(int i=0;i<NB_TTYUSB;i++) {
	if (slip[i] != NULL) {
	  size += slip[i]->printConfig(first,
				       &buffer[size]);
	  first = false;
	}
      }
      return size;
    } // unsigned printConfig(char * buffer) const
  } serialIo;
  struct socketIo_t {
    class coojaServer_t { // wait for cooja tcp6 client connection on ::1.1234
#define COOJA_SERVER_DEFAULT_PORT 1234
      unsigned short port;
      int            serverSd;
      int            nbCoojaConnections; // nb of active connection (which have passed accept)
      sysErr_t       sysErr;
      void close(void) {
	const int res = ::close(serverSd);
	if (res<0) {
	  sysErr.panic(res,"cannot close fd=%d\n",serverSd);
	  ugid_t().printCurrent();
	}
	serverSd = -1; // invalid
      }
    public:
      coojaServer_t(void) : port(COOJA_SERVER_DEFAULT_PORT) {
	serverSd = socket(PF_INET6, SOCK_STREAM, 0);
	if (serverSd < 0) {
	  sysErr.panic(serverSd,"socket SOCK_STREAM");
	  return;
	}
	int ret;
	if ( (ret=fcntl(serverSd, F_SETFL, O_NONBLOCK)) != 0 ) {
	  sysErr.panic(ret,"setting nonblocking I/O for non blocking accept");
	  close();
	  return;
	}
	struct sockaddr_in6 sockAddr;
	bzero(&sockAddr, sizeof(sockAddr));
	sockAddr.sin6_family = AF_INET6;
	sockAddr.sin6_port   = htons(port);
	//in6addr_any : Address already in use hown to unbind
	sockAddr.sin6_addr   = in6addr_any/*loopback*/; // allow cooja clients to conntct to on ::1.1234
	if ( (ret=bind(serverSd, (struct sockaddr*)&sockAddr, sizeof(sockAddr))) != 0 ) {
	  sysErr.panic(ret,"socketIo_t::coojaServer_t::bind ::1 ");
	  ::close(serverSd);
	  serverSd = -1; // retry later
	  sleep(1);
	  return;
	}
	if ( (ret=listen(serverSd, NB_MB851)) != 0 ) {
	  sysErr.panic(ret,"listen ::1 ");
	  close();
	  return;
	}
	nbCoojaConnections = 0;
	fprintf(stderr,
		" ::1.%d (serverSd=%d) ready to accept tcpip connections from cooja clients\n",
		port,
		serverSd);
      } // coojaServer_t(void)
      int newCoojaConnectionAccepted(char portName[64]) { // return -1 if no connection and set portname to "error"
	int clientSd               = -1;
	strcpy(portName,"error");
	struct pollfd fds[1]; /* cleared with bzero() */
	fds[0].fd                  = serverSd;
	fds[0].events              = POLLIN | POLLRDHUP;
	/* POLLRDHUP (since Linux 2.6.17)
	   Stream socket peer closed connection, or shut down  writ‐
	   ing  half  of  connection.   The _GNU_SOURCE feature test
	   macro must be defined in order to obtain this definition.
	*/
	fds[0].revents = 0;
	int ret;
	if ( (ret = poll(fds, 1, 0)) > 0 ) {
	  if (fds[0].revents & (POLLIN | POLLRDHUP)) { /* If input ready, echo it back */
	    //fprintf(stderr,"."); 
	    clientSd = ::accept(serverSd,
				NULL,
				NULL);
	    //  fprintf(stderr," returns %d\n",clientSd); 
	    if (clientSd<0) {
	      if ((errno==EAGAIN) || (errno==EWOULDBLOCK)) {
	      } else
		sysErr.panic(clientSd,"accept returns %d ",clientSd);
	      return -1;
	    } else {
	      /*****************************************************************/
	      /* Display the client address.  Note that if the client is       */
	      /* an IPv4 client, the address will be shown as an IPv4 Mapped   */
	      /* IPv6 address.                                                 */
	      /*****************************************************************/
	      struct sockaddr_in6 clientSockAddr;
	      socklen_t           clientSockAddrlen;
	      getpeername(clientSd,
			  (struct sockaddr *)&clientSockAddr,
			  &clientSockAddrlen);
	      char clientAddrStr[5*8];
	      if(inet_ntop(AF_INET6,
			   &clientSockAddr.sin6_addr,
			   clientAddrStr,
			   sizeof(clientAddrStr))) {
		gnTrace->printf("cooja Client address is %s\n", clientAddrStr);
		gnTrace->printf("cooja Client port is %d\n", ntohs(clientSockAddr.sin6_port));
	      }
	      gnTrace->printf("cooja Client (clientSd=%d) tcpConnection from %s accepted ======================================\n",
			     clientSd,
			     clientAddrStr);
	      sprintf(portName,"%s.%d",clientAddrStr,ntohs(clientSockAddr.sin6_port));
	      int ret;
	      if ( (ret=fcntl(clientSd, F_SETFL, O_NONBLOCK)) != 0 ) {
		sysErr.panic(ret,"setting nonblocking I/O for non blocking clientSd=%d\n",clientSd);
		clientSd = -1;
	      }
	      return clientSd;
	    }
	  } // if ((fds[0].revents & POLLIN))  /* If input ready, echo it back */
	} // if ( (ret = poll(fds, 1, 0)) > 0 )
	return -1;
      } // int newCoojaConnectionAccepted(void)
      void cleanup(void) {
	if (serverSd>=0) {
	  fprintf(stderr,"closing coojaServer\n");
	  close();
	}
	nbCoojaConnections = 0;
	// TBD who close all open cooja connections
      } // void cleanup(void)
      ~coojaServer_t(void) {
	cleanup();
      }
    }; // class coojaServer_t
    coojaServer_t coojaServer; // in order to route slip on coaja socketd
    unsigned nbSlip;
#define NB_COOJA_SERIAL_IO 1000
    slip_t * slip[NB_COOJA_SERIAL_IO]; // 1 entry per logical slipPort connection
    socketIo_t(void) : coojaServer() {
      nbSlip = 0;
      for(int i=0;i<NB_TTYUSB;i++)
	slip[i] = NULL;
    }
    void cleanup(void) {
      for(unsigned i=0;i<nbSlip;i++)
	if (slip[i] != NULL) {
	  gnTrace->printf("closing slip%d\n",i);
	  delete slip[i];
	  slip[i] = NULL;
	}
    } // void cleanup(void);
    void pollSlipConnections(unsigned & nbTun,
			     immoConnection_t * & ImmoConnection) { // update nb of active tun connection
      // create/delete slip according to ttyUSB detection 
      for(;;) {
	char portName[64];
	const int clientSd = coojaServer.newCoojaConnectionAccepted(portName); // return -1 if no connection and set portname to "error"
	if (clientSd>=0) {
	  const unsigned i = nbSlip++;
	  char ipAddrWithPrefix[64];
	  sprintf(ipAddrWithPrefix,"fc00:%x::2/64",i);
	  gnTrace->printf("connecting cooja slip%d to tun%d(%s)\n",i,i,ipAddrWithPrefix);
	  slip[i] = new slip_t(i,
			       new socketIO_t(clientSd,
					      portName), // TBD delete
			       ipAddrWithPrefix,
			       nbTun,
			       5, // verboseTun2slipPort,
			       5); // verboseslipPort2Tun
	} else
	  break;
      } // for(;;)
      // poll existing connection
      for(unsigned i=0;i<nbSlip;i++) {
	if (slip[i] != NULL)
	  slip[i]->pollSlip(ImmoConnection);
      }
    } // void pollSlipConnections(unsigned & NbTun) { // update nb of active tun connection
    unsigned printConfig(bool & first,char * const buffer) const {
      unsigned size = 0;
      for(int i=0;i<NB_TTYUSB;i++) {
	if (slip[i] != NULL) {
	  size += slip[i]->printConfig(first,
				       &buffer[size]);
	  first = false;
	}
      }
      return size;
    } // unsigned printConfig(char * buffer) const
  }; // class socketIo_t
  socketIo_t socketIo;
 public:
  slipSet_t(void) : serialIo(), socketIo() {
    nbTun  = 0;
  }
  void cleanup(void) {
    serialIo.cleanup();
    socketIo.cleanup();
  }
  const slip_t * getSlip(const unsigned i) const { return (i<NB_TTYUSB) ? serialIo.slip[i] : socketIo.slip[i-NB_TTYUSB]; }
  const tun_t * getTunPort(const unsigned i) const {
    const slip_t * s = getSlip(i);
    return (s==NULL) ? NULL : s->getTunPort();
  }
  void cleanUpPreviousTunConnections(void) {
    for(int i=0;i<NB_TTYUSB;i++) {
      char tundev[32];
      sprintf(tundev,"tun%d",i);
      if (gnTrace->ssystem("ifconfig %s",tundev)==0) {
	gnTrace->ssystem("ifconfig %s down",tundev);
	gnTrace->ssystem("netstat -nr"
			" | awk '{ if ($2 == \"%s\") print \"route delete -net \"$1; }'"
			" | sh",
			tundev);
      }
    }
  }
  void pollSlipConnections(unsigned & nbTun,
			   immoConnection_t * & ImmoConnection) { // return nb of active tun connection
    // create/delete slip according to ttyUSB detection 
    serialIo.pollSlipConnections(nbTun,
				 ImmoConnection);
    // create/delete slip according to cooja client tcp6 connection
    socketIo.pollSlipConnections(nbTun,
				 ImmoConnection);
  }
  unsigned printConfig(char * const buffer) const {
    bool first = true;
    unsigned size = serialIo.printConfig(first,buffer);
    size += socketIo.printConfig(first,&buffer[size]);
    return size;
  } // unsigned printConfig(char * buffer) const
  ~slipSet_t(void) {
    cleanup();
  }
}; // class slipSet_t

immoConnection_t::immoConnection_t(remoteClientAddr_t & ImmoClientAddr) :
  immoClientAddr(ImmoClientAddr),
  received(0),
  expected(1024),
  level(0) {}
bool immoConnection_t::closed(void) const { return immoClientAddr.closed(); } // to handle closed by peer
void immoConnection_t::immoPacket(const unsigned char recType,
				  const unsigned char tunType,
				  const unsigned char tunId,
				  const unsigned char * const  sendBuffer,
				  const unsigned      size) {
  const int clientSd = immoClientAddr.getClientSd();
  struct {
    unsigned char recType;
    unsigned char tunType;
    unsigned char tunId;
    unsigned char s1;
    unsigned char s0;
  } header;
  header.recType = recType;
  header.tunType = tunType;
  header.tunId   = tunId;
  header.s1      = size>>8;
  header.s0      = size;
  gnTrace->printf("send2immo recType=%c,tunType=%c,tunId=%d,size=%d\n",
		 recType,
		 tunType,
		 tunId,
		 size);
  sendBuff(clientSd,
	   (unsigned char *)&header,
	   5);
  sendBuff(clientSd,
	   sendBuffer,
	   size);
#if 0
  if (recType=='P') {
    const uip_packet_t * const p = (const uip_packet_t *)sendBuffer;
    
    gnTrace->printf("\tsrc=%s,dst=%s,type=%d\n",
		   );
  }
#endif
}
int immoConnection_t::receiveFromImmo(void) { // returns 0 if not fully read 1 when Ok
  if (immoClientAddr.closed())
    return -1;
  while (received < expected) {
    struct sockaddr_in6 srcsockaddr_in6;
    bzero(&srcsockaddr_in6, sizeof(srcsockaddr_in6));
    srcsockaddr_in6.sin6_family = AF_INET6; // !!!!
    socklen_t srcAddrLen = sizeof(srcsockaddr_in6); // man recvfrom: The argument addrlen is a value-result argument, which the caller should initialize before  the  call
    int ret;
    const int clientSd = immoClientAddr.getClientSd();
    //fprintf(stderr,"read received=%d expected=%d\n",received,expected);
    ret = recvfrom(clientSd,
		   &recBuffer[received],
		   1,
		   0, // noflags
		   (struct sockaddr*)&srcsockaddr_in6,
		   &srcAddrLen);
    if (ret<=0) {
      if ((errno==EAGAIN) || (errno==EWOULDBLOCK)) {
	return 0;// wait return 0; // retry later
      } else {
	char srcAddrStr[64];
	srcAddrStr[0] = '\0';
	inet_ntop(srcsockaddr_in6.sin6_family,
		  &srcsockaddr_in6.sin6_addr,
		  srcAddrStr,
		  sizeof(srcAddrStr));
	unsigned short srcPort = ntohs(srcsockaddr_in6.sin6_port);
	sysErr.panic(ret,"recvfrom %s.%d",srcAddrStr,srcPort);
	immoClientAddr.cleanup();
	return ret;
      }
    } else { // ret > 0
      switch(recBuffer[received]) {
      case '{' :
	level++;
	break;
      case '}' :
	level--;
	if (level<=0) {
	  recBuffer[++received]=0;
	  // reset for next time
	  expected = 1024;
	  received = 0;
	  return 1;
	}
	break;
      }
      received += ret;
    }  // else (receinived == expected)
  } // while
  return (1);
} // int receiveFromImmo(void)
int immoConnection_t::pollImmoConnection(/*const slipSet_t & slipSet*/void) { // return 1 if reset by peer else 0
  const int clientSd = immoClientAddr.getClientSd();
  //gnTrace->printf("POLL IMMO RECEIVED read urgent msg from,clientSd=%d step=%d %d/%d\n",clientSd,step,received,expected);
  if (clientSd >= 0) {
    struct pollfd fds[1]; /* cleared with bzero() */
    fds[0].fd      = clientSd;
    fds[0].events  = POLLIN | POLLHUP;
    fds[0].revents = 0;
    /* wait urgent for only URGENT_POLL_TIMEOUT ms */
    int ret;
    if ( (ret = poll(fds, 1, 0)) > 0 ) {
      if ((fds[0].revents & POLLIN)) { /* If input ready, echo it back */
	//gnTrace->printf("RECEIVED read urgent msg from, step=%d %d/%d\n",step,received,expected);
#if 0
	//make pollng somehwere else (top level) if required
	// by default send current conf at immo connexion before any other packet 
	xxx
	  const int res = receiveFromImmo(); // fill receiveRawData returns 0 if not fully read 1 when Ok
	if (res>0) { // packet fully received
	  char sendBuffer[1024*10];
	  unsigned toSend = 0;
	  char getConf [] = "{\"cmd\",\"getConfig\"}";
	  if (strcmp(recBuffer,getConf)==0) {
	    char head [] = "{\"config\",[";
	    toSend = sizeof(head)-1;
	    strcpy(sendBuffer,head);
	    toSend += slipSet.printConfig(&sendBuffer[toSend]);
	    sendBuffer[toSend++] = ']';
	    sendBuffer[toSend++] = '}';
	    sendBuffer[toSend] = 0; // for the trace
	    gnTrace->printf("received '%s' reply '",getConf);
	    gnTrace->write(sendBuffer,toSend);
	    gnTrace->printf("'\n");
	  } else
	    assert(0);
	  if (toSend)
	    sendBuff(clientSd,
		     sendBuffer,
		     toSend);
	} // if (res>0)
#endif
      } else if ( fds[0].revents & POLLHUP ) { /* if closed on other end, close here */
	gnTrace->printf("close channel required\n");
	return 1;
      }
    } else if ( ret < 0 ) { // if ( (ret = poll(fds+start, MAXRANGE, 100)) > 0 )
      sysErr.panic(ret,"urgent poll() error");
    } else { // reslut == 0
      //gnTrace->printf("urgent poll=0\n");
    }
  } // if (clientSd >= 0)
  return 0;
} // void pollImmoConnection(void)
void immoConnection_t::onConnectCallback(const tun_t * const tun) {
#if 0
  const int clientSd = immoClientAddr.getClientSd();
  char sendBuffer[1024];
  char ipAddr[5*8];
  tun->getIpAddr().str(ipAddr);
  sprintf(sendBuffer,"{\"connect\":\"%s\"}",ipAddr);
  const unsigned toSend = strlen(sendBuffer);
  sendBuff(clientSd,
	   sendBuffer,
	   toSend);
#else
  const struct in6_addr ipAddr = tun->getIpAddr().getIn6Addr();
  immoPacket('C', // connect
	     (tun->getTunType()==tun_t::TAP) ? 'S' : 'T', // sniffer or tunnel
	     tun->getTunId(),
	     ( unsigned char*)&ipAddr,
	     sizeof(ipAddr));
#endif
}
void immoConnection_t::onDisconnectCallback(const tun_t * const tun) {
#if 0
  const int clientSd = immoClientAddr.getClientSd();
  char sendBuffer[1024];
  char ipAddr[5*8];
  tun->getIpAddr().str(ipAddr);
  sprintf(sendBuffer,"{\"disconnect\":\"%s\"}",ipAddr);
  const unsigned toSend = strlen(sendBuffer);
  sendBuff(clientSd,
	   sendBuffer,
	   toSend);
#else
  const struct in6_addr ipAddr = tun->getIpAddr().getIn6Addr();
  immoPacket('D', // disconnect
	     (tun->getTunType()==tun_t::TAP) ? 'S' : 'T', // sniffer or tunnel
	     tun->getTunId(),
	     ( unsigned char*)&ipAddr,
	     sizeof(ipAddr));
#endif
}

tun_t::tun_t(const tunType_t    TunType,
	     const int          Id,
	     const char * const ipAddrStrWithPrefix,
	     trace_t          * Trace,
	     immoConnection_t * const ImmoConnection) :
  id(Id),
  tunType(TunType),
  trace(Trace),
  immoConnection(ImmoConnection)
{
  char ipAddrStrWithoutPrefix[5*8];
  for(int i=0;i<5*8;i++) {
    ipAddrStrWithoutPrefix[i] = ipAddrStrWithPrefix[i];
    if (ipAddrStrWithPrefix[i]=='/') {
      ipAddrStrWithoutPrefix[i] = 0;
      ipAddr.setpton(ipAddrStrWithoutPrefix);
      prefixSize = atoi(&ipAddrStrWithPrefix[i+1]);
      break;
    }
  }
  step = 0;
  char devpath[32];
  struct ifreq ifr;
  memset(&ifr, 0, sizeof(ifr));
  /* Flags: IFF_TUN   - TUN device (no Ethernet headers)
   *        IFF_TAP   - TAP device
   *
   *        IFF_NO_PI - Do not provide packet information
   */
  if (tunType==TUN) {
    sprintf(tundev,"tun%d",id);
    strcpy(devpath,"/dev/net/tun");
    ifr.ifr_flags = IFF_TUN | IFF_NO_PI;
  } else {
    sprintf(tundev,"tap%d",id);
    strcpy(devpath,"/dev/net/tun");
    ifr.ifr_flags = IFF_TAP | IFF_NO_PI;
  }
  perm.rootRequired();
  if (trace->ssystem("ifconfig %s",tundev)==0) { // if tundev exist before we start close it
    step  = 3;
    tunfd = -1; // no close (not open by this sesserialIOn)
    cleanup(); // start from any tun state
  }
  if ((tunfd = ::open(devpath, O_RDWR | O_NONBLOCK | O_TRUNC ))< 0 ) { // TBD block
    sysErr.panic(tunfd,"open %s",devpath);
    return;
  } else
    step = 1;
  strncpy(ifr.ifr_name, tundev, IFNAMSIZ);
  int ret;
  if((ret = ioctl(tunfd, TUNSETIFF, (void *) &ifr)) < 0 ) {
    sysErr.panic(ret,"ioctl TUNSETIFF %s",tundev);
    goto error;
  } else
    step = 2;
  strcpy(tundev, ifr.ifr_name);
  if (1/*tunType==TUN TBD taps*/) {
    if ((ret=trace->ssystem("ifconfig %s inet `hostname` up", tundev)) != 0) {
      sysErr.panic(ret,"ifconfig %s inet `hostname` up\n",tundev);
      goto error;
    } else
      step = 3;
    if ((ret=trace->ssystem("ifconfig %s add %s", tundev, ipAddrStrWithPrefix)) != 0) {
      sysErr.panic(ret,"ifconfig %s add %s\n", tundev, ipAddrStrWithPrefix);
      goto error;
    } else
      step = 4;
    if ((ret=trace->ssystem("ifconfig %s\n", tundev)) != 0) {
      sysErr.panic(ret,"ifconfig %s\n",tundev);
      goto error;
    } else
      step = 5;
  } else {
    assert(0);
  }
  perm.pop();
  if (immoConnection!=NULL)
    immoConnection->onConnectCallback(this);
  return;
 error:
  cleanup();
  perm.pop();
} // tun_t::tun_t(const int id, const char * const ipAddrWithPrefix)

void tun_t::cleanup(void) {
  if (step>=3) {
    perm.rootRequired();
    int ret;
    if((ret = trace->ssystem("ifconfig %s down",tundev)) != 0) {
      sysErr.panic(ret,"ifconfig %s down\n",tundev);
      perm.pop();
      goto error;
    }
    if((ret = trace->ssystem("netstat -nr"
			     " | awk '{ if ($2 == \"%s\") print \"route delete -net \"$1; }'"
			     " | sh",
			     tundev)) != 0) {
      sysErr.panic(ret,
		   "netstat -nr"
		   " | awk '{ if ($2 == \"%s\") print \"route delete -net \"$1; }'"
		   " | sh",
		   tundev);
    }
    perm.pop();
  } // if (step>=3)
 error:
  if (tunfd>=0) {
    trace->printf("disconnect %s (fd=%d) step=%d\n",tundev,tunfd,step);
    if (immoConnection!=NULL)
      immoConnection->onDisconnectCallback(this);
    perm.rootRequired();
    fprintf(stderr,"closing tunFd fd=%d '%s'\n",tunfd,tundev);
    const int res = ::close(tunfd);
    if (res<0) {
      sysErr.panic(res,"cannot close fd=%d\n",tunfd);
      ugid_t().printCurrent();
    }
    perm.pop();
  }
  tunfd  = -1; // signal error
  sysErr = sysErr_t(); // clear error
  step   = 0;
} // void tun_t::cleanup(void);

class immoServer_t {
#define IMMO_SERVER_DEFAULT_PORT 9966
  unsigned short     port;
  int                sd;
  sysErr_t           sysErr;
  remoteClientAddr_t immoClientAddr;
  void tryConnect(void) {
    struct sockaddr_in6 sockAddr;
    sd = socket(PF_INET6, SOCK_STREAM, 0);
    if (sd < 0) {
      sysErr.panic(sd,"immoServer_t::socket SOCK_STREAM");
      return;
    }
    int ret;
    if ( (ret=fcntl(sd, F_SETFL, O_NONBLOCK)) != 0 ) {
      sysErr.panic(ret,"immoServer_t::setting nonblocking I/O for non blocking accept");
      close(sd);
      sd = -1; // invalid
      return;
    }
    bzero(&sockAddr, sizeof(sockAddr));
    sockAddr.sin6_family = AF_INET6;
    sockAddr.sin6_port   = htons(port);
    sockAddr.sin6_addr   = in6addr_loopback; // security hole?
    if ( (ret=bind(sd, (struct sockaddr*)&sockAddr, sizeof(sockAddr))) != 0 ) {
      sysErr.panic(ret,"immoServer_t::bind in6addr_loopback.%d",port);
      close(sd);
      sd = -1; // invalid retry later
      sleep(1);
#if 0
      // shutdown for now
      void sigcleanup(int signo); // forward
      sigcleanup(0);
      exit(1); // how to avoid this
#endif
      return;
    }
    if ( (ret=listen(sd, 1)) != 0 ) { // one immo connection max
      sysErr.panic(ret,"immoServer_t::listen in6addr_loopback.%d",port);
      close(sd);
      sd = -1; // invalid
      return;
    }
    fprintf(stderr,
	    "immoServer %d (sd=%d) ready to accept the tcpip connection from immo interface\n",
	    port,
	    sd);
  } // void tryConnect(void)
public:
  immoConnection_t * immoConnection;
  immoServer_t(const unsigned short Port=IMMO_SERVER_DEFAULT_PORT) : port(Port), immoConnection(NULL) {
    tryConnect(); // bind may fail
  } // immoServer_t(void)`
  void cleanup(void) {
    if (sd>=0) {
      fprintf(stderr,"immoServer_t::closing immoServer\n");
      close(sd);
      sd = -1; // invalid
    }
    // must close all open connections
    //      perBoard[i].cleanupImmoConnection();
  } // void cleanup(void)
  void onConnectCallback(const tun_t * const tun) const {
    if (immoConnection!=NULL)
      immoConnection->onConnectCallback(tun);
  }
  void onDisconnectCallback(const tun_t * const tun) const {
    if (immoConnection!=NULL)
      immoConnection->onDisconnectCallback(tun);
  }
  bool poll(/*const slipSet_t & slipSet*/) {
    if (immoConnection!=NULL) {
      if (immoConnection->closed()) { // by peer or error
	delete immoConnection;
	immoConnection = NULL;
      } else {
	immoConnection->pollImmoConnection(/*slipSet*/);
	return true;
      }
    }
    if (sd<0)
      tryConnect();
    if ((sd >= 0) &&
	immoClientAddr.acceptIfAny(sd)>0) { // immoClientAddr contain a valid connection request
      immoConnection = new immoConnection_t(immoClientAddr);
      fprintf(stderr,"immoServer_t::immoConnection created\n");
      immoConnection->pollImmoConnection(/*slipSet*/);
      return true;
    } // TBD delete this connection
    return false; // no connection yet
  } // poll
  ~immoServer_t(void) {
    cleanup();
  }
}; // immoServer_t



slipSet_t      slipSet; // create the coojaServer listening on ::1.1234
immoServer_t   immoServer; // wait for java configRequest and send tunslip changes

void sigcleanup(int signo) {
  gnTrace->printf("signal %d\n", signo);
  slipSet.cleanup();
  exit(0);			/* exit(0) will call cleanup() */
}

#define GUI 1

static void cleanup(void) {
  // must call all cleanup
  slipSet.cleanup();
  exit(0);			/* exit(0) will call cleanup() */  
}

int main(int count, char *strings[]) {	
  ug_fm5.get(); // set default user id group id for log files
  gnTrace = new trace_t("mslip","stderr","","mslip.log");
  fprintf(stderr,"\n\ngreennet interface version 0.1\n\n");
  atexit(cleanup);
  signal(SIGHUP , sigcleanup);
  signal(SIGTERM, sigcleanup);
  signal(SIGINT , sigcleanup);
  signal(SIGALRM, sigalarm);
#if GUI
  const unsigned short port = (count>1) ? atoi(strings[1]) : 7763;
  guiConnection_t guiConnection(port);
#endif

  //  sleep(NETWORK_SETUP_TIME_IN_SECOND); // 10s to enable all the greenet network to get prefix 

  slipSet.cleanUpPreviousTunConnections();

  unsigned nbTun  = 0;
  int pleaseCount = 0;
  for(;;) {
    immoServer.poll(/*slipSet*/); // at most 1 tcp/ip connection from immo to get tunnelinterfaces status
    slipSet.pollSlipConnections(nbTun,
				immoServer.immoConnection);
    perm.userRequired();
    if (nbTun==0) {
      if ((pleaseCount++ % 100000)==0)
	fprintf(stderr,"please connect a border router on an USB port\n");
      //      sleep(1);
    } else {
    }
    perm.pop();
    usleep(1); // give a chance for others to work
  } // for(;;)
   return 0;
}
