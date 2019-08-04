#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <pcap/pcap.h>
#include <stdint.h>
#include <arpa/inet.h>


#define ARPHRD_ETHER    0x1
#define ETTHER_LEN 0xe
#define ETHER_ADDR_LEN 0x06
#define IPv4_ADDR_LEN 0x04
#define ETHERTYPE_IP            0x0800  /* IP protocol */
#define ETHERTYPE_ARP           0x0806  /* addr. resolution protocol */
#define LIBNET_ARP_H            0x08    /**< ARP header w/o addrs: 8 bytes */
#define LIBNET_ARP_ETH_IP_H     0x1c    /**< ARP w/ ETH and IP:   28 bytes */
#define ARPOP_REQUEST    1  /* req to resolve address */
#define ARPOP_REPLY      2
#define ARP_CACHE       "/proc/net/arp"
#define ARP_STRING_LEN  200
#define ARP_BUFFER_LEN  (ARP_STRING_LEN + 1)

#define ARP_LINE_FORMAT "%100s %*s 0x%100s %100s %*s %100s"

struct libnet_ethernet_hdr
{
    uint8_t  ether_dhost[ETHER_ADDR_LEN];/* destination ethernet address */
    uint8_t  ether_shost[ETHER_ADDR_LEN];/* source ethernet address */
    uint16_t ether_type;                 /* protocol */
};
struct libnet_ether_addr
{
    uint8_t  ether_addr_octet[6];        /* Ethernet address */
};
struct libnet_ipv4_hdr /* ip header */
{
    uint8_t ip_v:4,       /* version */
           ip_hl:4;        /* header length */
    uint8_t ip_tos;       /* type of service */
    uint16_t ip_len;         /* total length */
    uint16_t ip_id;          /* identification */
    uint16_t ip_off;
    uint8_t ip_ttl;          /* time to live */
    uint8_t ip_p;            /* protocol */
    uint16_t ip_sum;         /* checksum */
    struct in_addr ip_src, ip_dst; /* source and dest address */
};
struct libnet_arp_hdr
{
    uint16_t ar_hrd;         /* format of hardware address */
    uint16_t ar_pro;         /* format of protocol address */
    uint8_t  ar_hln;         /* length of hardware address */
    uint8_t  ar_pln;         /* length of protocol addres */
    uint16_t ar_op;          /* operation type */
     /* address information allocated dynamically */

};
struct libnet_tcp_hdr
{
    uint16_t th_sport;       /* source port */
    uint16_t th_dport;       /* destination port */
    uint32_t th_seq;          /* sequence number */
    uint32_t th_ack;          /* acknowledgement number */
    uint8_t  th_off:4,        /* data offset */
             th_x2:4;         /* (unused) */
    uint8_t  th_flags;       /* control flags */
    uint16_t th_win;         /* window */
    uint16_t th_sum;         /* checksum */
    uint16_t th_urp;         /* urgent pointer */
};

void get_my_mac(char str_MAC[7])
{
    int s,i;
    struct ifreq ifr;
    s = socket(AF_INET, SOCK_DGRAM, 0);
    strcpy(ifr.ifr_name, "ens33");
    ioctl(s, SIOCGIFHWADDR, &ifr);
    for (i=0; i<ETHER_ADDR_LEN; i++)
        sprintf(&str_MAC[i],"%2X",((unsigned char*)ifr.ifr_hwaddr.sa_data)[i]);
    str_MAC[6]='\0';
}

void get_my_ip(char* get_myaddr ){

        int fd;
        struct ifreq ifr;
        char iface[] = "ens33";

        fd = socket(AF_INET, SOCK_DGRAM, 0);

        //Type of address to retrieve - IPv4 IP address
        ifr.ifr_addr.sa_family = AF_INET;

        //Copy the interface name in the ifreq structure
        strncpy(ifr.ifr_name , iface , IFNAMSIZ-1);

        ioctl(fd, SIOCGIFADDR, &ifr);



        //display result
      //  printf("%s - %s\n" , iface , inet_ntoa(( (struct sockaddr_in *)&ifr.ifr_addr )->sin_addr) );

        get_myaddr = inet_ntoa(( (struct sockaddr_in *)&ifr.ifr_addr )->sin_addr);
//        get_myaddr=inet_ntoa((sturct sockaddr_in*)&ifr.ifr_addr->sin_addr);
//        close(fd);
}

void usage() {
    printf("send_arp <interface> <sender ip> <target ip>\n");
    printf("ex : send_arp wlan0 192.168.10.2 192.168.10.1\n");
}

struct libnet_ethernet_hdr get_victim_mac(pcap_t* handle, char* my_mac,char* errbuf){

  //  pcap_t* req_handle = pcap_open_live("ens33", BUFSIZ, 1, 1000, errbuf);
    struct libnet_ethernet_hdr eth;
    struct libnet_arp_hdr arp;
    u_char Arp_packet[0x3c]={0,};
 //   uint32_t src_ip = htonl(inet_addr("192.168.1.104"));
  //  uint32_t dst_ip = htonl(inet_addr("192.168.1.1"));
    int idx;
    int size_eth=sizeof(eth);
    int size_arp_hd=sizeof(arp);


  //  get_my_ip(getmyip);
    //for(idx=0;idx<6;idx++)
      //  printf("%02x",my_mac[idx]);



    memcpy(eth.ether_dhost,(const void*)0xff,ETHER_ADDR_LEN);
    memcpy(eth.ether_shost,my_mac,ETHER_ADDR_LEN);
    for(idx=0;idx<6;idx++){
       printf("%02x",eth.ether_dhost[idx]);
       //printf("%02x",eth.ether_shost[idx]);
    }
    for(idx=0;idx<6;idx++){
       printf("%02x",eth.ether_shost[idx]);
       //printf("%02x",eth.ether_shost[idx]);
    }
  //  eth.ether_type=ETHERTYPE_ARP;
   // arp.ar_hrd=ARPHRD_ETHER;
   // arp.ar_hln=ETHER_ADDR_LEN;
    //arp.ar_pro=ETHERTYPE_IP;
    //arp.ar_pln=IPv4_ADDR_LEN;
    //arp.ar_op=ARPOP_REQUEST;



    //memcpy(Arp_packet,&eth,sizeof(eth));
    //memcpy(Arp_packet+ ETTHER_LEN,&arp,LIBNET_ARP_H);
    //memcpy(Arp_packet+ ETTHER_LEN+LIBNET_ARP_H,my_mac,6);
    //memcpy(Arp_packet+ETTHER_LEN+LIBNET_ARP_H+6,&src_ip,4);
    //memcpy(Arp_packet+ETTHER_LEN+LIBNET_ARP_H+10,my_mac,6);
    //memcpy(Arp_packet+ETTHER_LEN+LIBNET_ARP_H+16,&dst_ip,4);

    //for(idx=0;idx<=0x3c;idx++)
     //   printf("%x", Arp_packet[idx]);
    //Arp_packet
   //if(pcap_sendpacket(handle,Arp_packet,0x3c)!=0) perror("handler error");

   // pcap_close(handle);
}
int main(int argc, char* argv[]) {
//  if (argc != 3) {
 //   usage();
 //   return -1;
  //}
  //char* dev = argv[1];
  //const char* victim_ip = "192.168.1.1";
  //in_addr* gw_ip = arv[3];

  char errbuf[PCAP_ERRBUF_SIZE];


  pcap_t* handle = pcap_open_live("ens33", BUFSIZ, 1, 1000, errbuf);
  if (handle == NULL) {
      printf("error");
  }
  // fprintf(stderr, "couldn't open device %s: %s\n", dev, errbuf);
   // return -1;
  //}
  struct pcap_pkthdr* header;
  const u_char* packet;
  int i;
  char track[] = "취약점";
  char name[] = "김원겸";

  char my_mac[7]={0,};
  char vicitim_mac[13]={0,};
  //char my_ip[24]={0,};
//  unsigned char gw_mac_address[6];
 // printf("[bob8][%s]pcap_test[%s]\n", track, name);
    get_my_mac(my_mac);
    //for(i=0;i<6;i++)
        printf("%s",my_mac);
  //  get_victim_mac(handle,my_mac,errbuf);
 // get_my_ip(my_ip);

  //pcap_sendpacket(dev,&header,packet);
  

/*
  while (true) {
   struct pcap_pkthdr* header;
   const u_char* packet;
   int res = pcap_next_ex(handle, &header, &packet);

    if (res == 0) continue;
    if (res == -1 || res == -2) break;

    //int pcap_loop(pcap_t *p, int cnt, pcap_handler callback, u_char *user);

   // print_mac(packet);
    //cursor=Input_Mac(packet,&mc);
    //Input_Ip_Port(packet,&mc,&p,&tp,cursor);
    //print_All(packet, &mc,&p,&tp);
    //

  }
*/
  //pcap_close(handle);
  return 0;
}

