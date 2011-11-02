#ifndef __IPPACKET_H__
#define __IPPACKET_H__ 1

//#include <QtNetwork>
#include <stdio.h>

struct uip_80211_addr_t {
  unsigned char addr[6];
};
struct uip_eth_addr_t {
  unsigned char addr[6];
};
struct uip_ip6addr_t {
  unsigned char addr[16];
};

static inline bool is_unspecified_addr(const unsigned char * addr) {

  return 
    ((addr[0] == 0) &&		    
     (addr[1] == 0) &&	
    (addr[2] == 0) &&		    
     (addr[3] == 0) &&		    
     (addr[4] == 0) &&		    
     (addr[5] == 0) &&		    
     (addr[6] == 0) &&		    
     (addr[7] == 0) &&		    
     (addr[8] == 0) &&		    
     (addr[9] == 0) &&		    
     (addr[10] == 0) &&		    
     (addr[11] == 0) &&		    
     (addr[12] == 0) &&		    
     (addr[13] == 0) &&		    
     (addr[14] == 0) &&		    
     (addr[15] == 0));
}
static inline bool is_linklocal_allnodes(const unsigned char * addr) {

  return 
    ((addr[0] == 0xff) &&		    
     (addr[1] == 0x02) &&	
     (addr[2] == 0) &&		    
     (addr[3] == 0) &&		    
     (addr[4] == 0) &&		    
     (addr[5] == 0) &&		    
     (addr[6] == 0) &&		    
     (addr[7] == 0) &&		    
     (addr[8] == 0) &&		    
     (addr[9] == 0) &&		    
     (addr[10] == 0) &&		    
     (addr[11] == 0) &&		    
     (addr[12] == 0) &&		    
     (addr[13] == 0) &&		    
     (addr[14] == 0) &&		    
     (addr[15] == 0x01));
}
static inline bool is_linklocal_allrouters(const unsigned char * addr) {

  return 
    ((addr[0]  == 0xff) &&		    
     (addr[1]  == 0x02) &&	
     (addr[2]  == 0) &&		    
     (addr[3]  == 0) &&		    
     (addr[4]  == 0) &&		    
     (addr[5]  == 0) &&		    
     (addr[6]  == 0) &&		    
     (addr[7]  == 0) &&		    
     (addr[8]  == 0) &&		    
     (addr[9]  == 0) &&		    
     (addr[10] == 0) &&		    
     (addr[11] == 0) &&		    
     (addr[12] == 0) &&		    
     (addr[13] == 0) &&		    
     (addr[14] == 0) &&		    
     (addr[15] == 0x02));
}
static inline bool is_linklocal(const unsigned char * addr) {

  return 
    ((addr[0] == 0xfe) &&		    
     (addr[1] == 0x80));
}
static inline bool is_solicited_node_prefix(const unsigned char * addr) {

  return 
    ((addr[0]  == 0xff) &&		    
     (addr[1]  == 0x02) &&	
     (addr[2]  == 0) &&		    
     (addr[3]  == 0) &&		    
     (addr[4]  == 0) &&		    
     (addr[5]  == 0) &&		    
     (addr[6]  == 0) &&		    
     (addr[7]  == 0) &&		    
     (addr[8]  == 0) &&		    
     (addr[9]  == 0) &&		    
     (addr[10] == 0) &&		    
     (addr[11] == 0x01) &&		    
     (addr[12] == 0xFF));
}
struct uip_packet_t {
  enum link_offset_t {
    //-------------------- link header if tap
    dst80211 = 0,
    src80211 = dst80211 + 6,
    type1    = src80211 + 6, // type = 0x86dd = IPv6
    type0,
    link_header_size
  };
  short getType(const unsigned char * const linkPtr) const {
    return (linkPtr[type1]<<8) + linkPtr[type0];
  }
  enum ipv6_offset_t {
    //-------------------- raw header if tun 
    ipv6version, // 0x60 (ipv6Ptr)
    tdb0,        // 0x00 0x00 0x00
    payload1 = ipv6version + 4, // size after this header
    payload0,
    nextHeader,  // UDP=0x11 ICMP6=0x3a
    hopLimit,
    ipsrc,
    ipdst   = ipsrc + 16,
    ipv6_header_size = ipdst + 16,
  };
  const char * getNextHeaderStr(const unsigned char * const ipv6Ptr) const {
    const char * str;
    switch(ipv6Ptr[nextHeader]) {
    case 0x11:
      str = "UDP";
      break;
    case 0x3a:
      str = "ICMPv6";
      break;
    default:
      str = "ILL NextHeader";
      break;
    }
    fprintf(stderr,"NextHeader=%s\n",str);
    return str;
  }
  const unsigned char *  getIPSrc(const unsigned char * const ipv6Ptr) const {
    fprintf(stderr,"ipsrc=%d =>%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x\n",
	    ipsrc,
	    ipv6Ptr[ipsrc+0],ipv6Ptr[ipsrc+1],	    	    
	    ipv6Ptr[ipsrc+2],ipv6Ptr[ipsrc+3],	    	    
	    ipv6Ptr[ipsrc+4],ipv6Ptr[ipsrc+5],	    	    
	    ipv6Ptr[ipsrc+6],ipv6Ptr[ipsrc+7],	    	    
	    ipv6Ptr[ipsrc+8],ipv6Ptr[ipsrc+9],	    	    
	    ipv6Ptr[ipsrc+10],ipv6Ptr[ipsrc+11],	    	    
	    ipv6Ptr[ipsrc+11],ipv6Ptr[ipsrc+13],	    	    
	    ipv6Ptr[ipsrc+12],ipv6Ptr[ipsrc+15]);	    	    
    return &ipv6Ptr[ipsrc];
  }
  const unsigned char * getIPDst(const unsigned char * const ipv6Ptr) const {
    fprintf(stderr,"ipdst=%d =>%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x\n",
	    ipdst,
	    ipv6Ptr[ipdst+0],ipv6Ptr[ipdst+1],	    	    
	    ipv6Ptr[ipdst+2],ipv6Ptr[ipdst+3],	    	    
	    ipv6Ptr[ipdst+4],ipv6Ptr[ipdst+5],	    	    
	    ipv6Ptr[ipdst+6],ipv6Ptr[ipdst+7],	    	    
	    ipv6Ptr[ipdst+8],ipv6Ptr[ipdst+9],	    	    
	    ipv6Ptr[ipdst+10],ipv6Ptr[ipdst+11],	    	    
	    ipv6Ptr[ipdst+11],ipv6Ptr[ipdst+13],	    	    
	    ipv6Ptr[ipdst+12],ipv6Ptr[ipdst+15]);	    	    
    return &ipv6Ptr[ipdst];
  }
  //------------------- cf RPL page 30 
  enum icmp6_type_t {
    ICMP6_DST_UNREACH		= 1,
    ICMP6_PACKET_TOO_BIG	= 2,
    ICMP6_TIME_EXCEEDED		= 3,
    ICMP6_PARAM_PROB		= 4,
    ICMP6_ECHO_REQUEST	        = 128,
    ICMP6_ECHO_REPLY		= 129,
    ICMP6_MEMBERSHIP_QUERY	= 130,
    ICMP6_MEMBERSHIP_REPORT	= 131,
    ICMP6_MEMBERSHIP_REDUCTION	= 132,
    ICMP6_ND_ROUTER_SOLICIT	= 133,
    ICMP6_ND_ROUTER_ADVERT	= 134,
    ICMP6_ND_NEIGHBOR_SOLICIT	= 135,
    ICMP6_ND_NEIGHBOR_ADVERT	= 136,
    ICMP6_ND_REDIRECT		= 137,
    ICMP6_ROUTER_RENUMBERING	= 138,
    ICMP6_NI_QUERY		= 139,
    ICMP6_NI_REPLY		= 140,
    ICMP6_IND_SOLICIT		= 141,
    ICMP6_IND_ADVERT		= 142,
    ICMP6_MLDV2_REPORT		= 143,
    ICMP6_MIP6_DHAAD_REQUEST	= 144,
    ICMP6_MIP6_DHAAD_REPLY	= 145,
    ICMP6_MIP6_MPS		= 146,
    ICMP6_MIP6_MPA		= 147,
    ICMP6_CERT_PATH_SOL		= 148,
    ICMP6_CERT_PATH_AD		= 149,
    ICMP6_EXPERIMENTAL_MOBILITY	= 150,
    ICMP6_MCAST_ROUTER_ADVERT	= 151,
    ICMP6_MCAST_ROUTER_SOLICIT	= 152,
    ICMP6_MCAST_ROUTER_TERM	= 153,
    ICMP6_FMIPV6_MESSAGES	= 154,
    ICMP6_RPL_CONTROL		= 155,
  };
  enum rpl_offset_t {
    type = 0, // 155=RPL  (133=RS)
    code, // 1 DIO
    checksum1,
    checksum0,
    RPLInstanceID,
    version,
    rank1,
    rank0,
    flags, 
    DestinationAdvertismentTriggerSequenceNumber,
    flags2,
    reserved,
    dodagid,
    opt = dodagid + 16, // TBD
  };
  enum rplCode_t {
    rpl_DIS              = 0x00,
    rpl_DIO              = 0x01,
    rpl_DAO              = 0x02,
    rpl_DAO_ACK          = 0x03,
    rpl_SECURE_DIS       = 0x80,
    rpl_SECURE_DIO       = 0x81,
    rpl_SECURE_DAO       = 0x82,
    rpl_SECURE_DAO_ACK   = 0x83,
    rpl_CONSITENCY_CHECK = 0x8A,
  };
  const char * decodeRplCode(const rplCode_t rplCode) const {
    switch(rplCode) {
    case rpl_DIS              :
      return "DIS              ";
    case rpl_DIO              : 
      return "DIO              ";
    case rpl_DAO              : 
      return "DAO              ";
    case rpl_DAO_ACK          :
      return "DAO_ACK          ";
    case rpl_SECURE_DIS       :
      return "SECURE_DIS       ";
    case rpl_SECURE_DIO       :
      return "SECURE_DIO       ";
    case rpl_SECURE_DAO       :
      return "SECURE_DAO       ";
    case rpl_SECURE_DAO_ACK   :
      return "SECURE_DAO_ACK   ";
    case rpl_CONSITENCY_CHECK :
      return "CONSITENCY_CHECK";
    default:
      return "ILLEGAL RPL CODE ";
    } // switch(rplCode)
  }
  const char * getRplType(const unsigned char * const rplPtr) const {
    const char * str;
    switch(rplPtr[type]) {
    case ICMP6_DST_UNREACH		: str = "ICMP6_DST_UNREACH		";break;
    case ICMP6_PACKET_TOO_BIG   	: str = "ICMP6_PACKET_TOO_BIG	";break;
    case ICMP6_TIME_EXCEEDED		: str = "ICMP6_TIME_EXCEEDED		";break;
    case ICMP6_PARAM_PROB		: str = "ICMP6_PARAM_PROB		";break;
    case ICMP6_ECHO_REQUEST	        : str = "ICMP6_ECHO_REQUEST	        ";break;
    case ICMP6_ECHO_REPLY		: str = "ICMP6_ECHO_REPLY		";break;
    case ICMP6_MEMBERSHIP_QUERY 	: str = "ICMP6_MEMBERSHIP_QUERY	";break;
    case ICMP6_MEMBERSHIP_REPORT	: str = "ICMP6_MEMBERSHIP_REPORT	";break;
    case ICMP6_MEMBERSHIP_REDUCTION	: str = "ICMP6_MEMBERSHIP_REDUCTION	";break;
    case ICMP6_ND_ROUTER_SOLICIT	: str = "ICMP6_ND_ROUTER_SOLICIT	";break;
    case ICMP6_ND_ROUTER_ADVERT 	: str = "ICMP6_ND_ROUTER_ADVERT	";break;
    case ICMP6_ND_NEIGHBOR_SOLICIT	: str = "ICMP6_ND_NEIGHBOR_SOLICIT	";break;
    case ICMP6_ND_NEIGHBOR_ADVERT	: str = "ICMP6_ND_NEIGHBOR_ADVERT	";break;
    case ICMP6_ND_REDIRECT		: str = "ICMP6_ND_REDIRECT		";break;
    case ICMP6_ROUTER_RENUMBERING	: str = "ICMP6_ROUTER_RENUMBERING	";break;
    case ICMP6_NI_QUERY  		: str = "ICMP6_NI_QUERY		";break;
    case ICMP6_NI_REPLY	        	: str = "ICMP6_NI_REPLY		";break;
    case ICMP6_IND_SOLICIT		: str = "ICMP6_IND_SOLICIT		";break;
    case ICMP6_IND_ADVERT		: str = "ICMP6_IND_ADVERT		";break;
    case ICMP6_MLDV2_REPORT		: str = "ICMP6_MLDV2_REPORT		";break;
    case ICMP6_MIP6_DHAAD_REQUEST	: str = "ICMP6_MIP6_DHAAD_REQUEST	";break;
    case ICMP6_MIP6_DHAAD_REPLY 	: str = "ICMP6_MIP6_DHAAD_REPLY	";break;
    case ICMP6_MIP6_MPS	        	: str = "ICMP6_MIP6_MPS		";break;
    case ICMP6_MIP6_MPA	          	: str = "ICMP6_MIP6_MPA		";break;
    case ICMP6_CERT_PATH_SOL		: str = "ICMP6_CERT_PATH_SOL		";break;
    case ICMP6_CERT_PATH_AD		: str = "ICMP6_CERT_PATH_AD		";break;
    case ICMP6_EXPERIMENTAL_MOBILITY	: str = "ICMP6_EXPERIMENTAL_MOBILITY	";break;
    case ICMP6_MCAST_ROUTER_ADVERT	: str = "ICMP6_MCAST_ROUTER_ADVERT	";break;
    case ICMP6_MCAST_ROUTER_SOLICIT	: str = "ICMP6_MCAST_ROUTER_SOLICIT	";break;
    case ICMP6_MCAST_ROUTER_TERM	: str = "ICMP6_MCAST_ROUTER_TERM	";break;
    case ICMP6_FMIPV6_MESSAGES	        : str = "ICMP6_FMIPV6_MESSAGES	";break;
    case ICMP6_RPL_CONTROL		: str = "ICMP6_RPL_CONTROL		";break;
    default:
      str = "ILLTYPE";
    }
    fprintf(stderr,"ipType='%s'\n",str);
    return str;
  }
  const char * getRplCode(const unsigned char * const rplPtr) const {
    const char * str = decodeRplCode((rplCode_t)rplPtr[code]);
    fprintf(stderr,"ipRplCode='%s'\n",str);
    return str;
  }
  unsigned short getChecksum(const unsigned char * const rplPtr) const {
    return (rplPtr[checksum1]<<8) + rplPtr[checksum0];
  }
  unsigned short getRank(const unsigned char * const rplPtr) const {
    return (rplPtr[rank1]<<8) + rplPtr[rank0];
  }
  union {
    struct {
      unsigned char recType;
      unsigned char tunType;
      unsigned char tunId;
      unsigned char s1;
      unsigned char s0;
    } header;
    char h[5];
  } u;
  unsigned char buffer[2048];
};
static inline bool isIPv6LinkHeader(const unsigned char * const linkPtr) {
  return
    ((linkPtr[uip_packet_t::type1]==0x86) && // type == IPv6
     (linkPtr[uip_packet_t::type0]==0xdd));
}
static inline bool isIPv6Packet(const unsigned char * const ipv6Ptr) {
  return
    ((ipv6Ptr[uip_packet_t::ipv6version]==0x60) &&
     (ipv6Ptr[uip_packet_t::ipv6version+1]==0) &&
     (ipv6Ptr[uip_packet_t::ipv6version+2]==0) &&
     (ipv6Ptr[uip_packet_t::ipv6version+3]==0));
}
static inline unsigned getPayload(const unsigned char * const ipv6Ptr) {
  return (ipv6Ptr[uip_packet_t::payload1]<<8) + ipv6Ptr[uip_packet_t::payload0];
}

#endif
