#include <pcap.h>
#include <stdio.h>
#include<stdint.h>
//#include<wchar.h>
#define ETHER_LEN 14

typedef struct _ether{
    u_int8_t dest_mac[6];
    u_int8_t src_mac[6];
    u_int8_t type[2];
}ether;
typedef struct _ip{
    u_int8_t dest_ip[4];
    u_int8_t src_ip[4];
    u_int8_t proto;
    u_int8_t ihl;
}ip;
typedef struct _tcp{
    u_int8_t src_port[2];
    u_int8_t dst_port[2];
    u_int8_t tcp_header_length;
}tcp;

u_int16_t ntohs(u_int16_t* port){
    return *port >>8 | *port << 8;
}
int Input_Mac(const u_char* ptr, ether* mc){
    int cursor=0, idx;

    for(idx=0;idx<6;idx++)
        mc->dest_mac[idx]=ptr[cursor++];

    for(idx=0;idx<6;idx++)
        mc->src_mac[idx]=ptr[cursor++];

	if(ptr[cursor] == 0x08 && ptr[cursor+1]== 0x00){ 
		mc->type[0] = ptr[cursor];
        mc->type[1] = ptr[cursor+1];
        return ++cursor;
	}
	
	return -1;	

}

void print_HTTP_TCP_Data(const u_char* ptr, ip* p, tcp* tp,int cursor){

    int idx;
    if(ntohs((u_int16_t*)tp->src_port) == 80 || ntohs((u_int16_t*)tp->dst_port) == 80 ){ //get HTTP, HTTPS
	    //cursor += 6;
	    idx = 0 ;
	    while(ptr[cursor+idx] != 0x0d && ptr[cursor+idx+1] != 0x0a){ // check carriage return
		printf("%c ", ptr[cursor+idx]);
		idx++;
		}
       printf("\n");
    }
    else
    {
        printf("TCP Bytes:");
        for(idx=0;idx<10;idx++){
            printf("%02x ", ptr[cursor+idx]);
        }
        printf("\n");
    }


}
void print_All(const u_char* ptr ,ether* e, ip* p ,tcp* tp){

    int idx;

    for(idx=0;idx<5;idx++)
        printf ("%02x:", e->src_mac[idx]);
    printf("%02x ",e->src_mac[idx]);

    for(idx=0;idx<3;idx++)
        printf("%u.", p->src_ip[idx]);
    printf("%u ", p->src_ip[idx]);

    printf(" :: %u -> ",ntohs((u_int16_t*)tp->src_port));

    for(idx=0;idx<5;idx++)
        printf ("%02x:", e->dest_mac[idx]);
    printf("%02x ",e->dest_mac[idx]);

    for(idx=0;idx<3;idx++)
        printf("%u.", p->dest_ip[idx]);
    printf("%u ", p->dest_ip[idx]);

    printf(" :: %0u\n", ntohs((u_int16_t*)tp->dst_port));

    print_HTTP_TCP_Data(ptr,p,tp,p->ihl+tp->tcp_header_length+ETHER_LEN);

}

void Input_Ip_Port(const u_char* ptr, ether* mc , ip* p, tcp* tp, int cursor){


    int idx, ip_eth_length;
    if(cursor++ == 13){
        p->ihl = (ptr[cursor] & 0x0f)*4;

        cursor += 9; //jump to tcp
        if(ptr[cursor] == 0x06){ // tcp
            p->proto = ptr[cursor];
            cursor += 3; // jump to src ip;

            for(idx=0; idx<4;idx++)
                p->src_ip[idx] = ptr[cursor++];

            for(idx=0;idx<4;idx++)
                p->dest_ip[idx] = ptr[cursor++];

             ip_eth_length = cursor = ETHER_LEN + p->ihl;

            for(idx=0;idx<2;idx++)
                tp->src_port[idx]=ptr[cursor++]; // big endian

            for(idx=0;idx<2;idx++)
                tp->dst_port[idx]=ptr[cursor++]; //big endian;

        cursor += 8; //tcp header length jump;
        tp->tcp_header_length = (ptr[cursor] >> 4 ) * 4; // get tcp header length

        cursor = tp->tcp_header_length + ip_eth_length; // A cursor goes packet body

        }
    }
}
void usage() {
  printf("syntax: pcap_test <interface>\n");
  printf("sample: pcap_test wlan0\n");
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    usage();
    return -1;
  }
  char* dev = argv[1];
  char errbuf[PCAP_ERRBUF_SIZE];
  ether mc;
  ip p;
  tcp tp;
  int cursor;
  pcap_t* handle = pcap_open_live(dev, BUFSIZ, 1, 1000, errbuf);
  if (handle == NULL) {
    fprintf(stderr, "couldn't open device %s: %s\n", dev, errbuf);
    return -1;
  }
	char track[] = "취약점";
	char name[] = "김원겸";
	printf("[bob8][%s]pcap_test[%s]", track, name);

  while (true) {
    struct pcap_pkthdr* header;
    const u_char* packet;
    int res = pcap_next_ex(handle, &header, &packet);
    if (res == 0) continue;
    if (res == -1 || res == -2) break;
    cursor=Input_Mac(packet,&mc);
    Input_Ip_Port(packet,&mc,&p,&tp,cursor);
    print_All(packet, &mc,&p,&tp);
  }

  pcap_close(handle);
  return 0;
}
