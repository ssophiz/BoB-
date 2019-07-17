//#pragma comment(lib,"ws2_32")
#include<stdio.h>
#include<cstdlib>
#include<stdint.h>
#include<stdlib.h>
//#include<WinSock2.h>
uint8_t packet[] = "\x2c\x21\x72\x93\xdf\x00\x3c\xf0\x11\x28\x37\x6e\x08\x00\x45\x00" \
"\x01\x9e\xe7\x4d\x40\x00\x80\x06\x00\x00\xc0\xa8\x03\xcb\xaf\xd5" \
"\x23\x27\xcf\xce\x00\x50\x3f\x77\xb5\x2f\x50\xd0\x94\x38\x50\x18" \
"\x01\xfe\x99\x00\x00\x00\x47\x45\x54\x20\x2f\x66\x61\x76\x69\x63" \
"\x6f\x6e\x2e\x69\x63\x6f\x20\x48\x54\x54\x50\x2f\x31\x2e\x31\x0d" \
"\x0a\x48\x6f\x73\x74\x3a\x20\x74\x65\x73\x74\x2e\x67\x69\x6c\x67" \
"\x69\x6c\x2e\x6e\x65\x74\x0d\x0a\x43\x6f\x6e\x6e\x65\x63\x74\x69" \
"\x6f\x6e\x3a\x20\x6b\x65\x65\x70\x2d\x61\x6c\x69\x76\x65\x0d\x0a" \
"\x55\x73\x65\x72\x2d\x41\x67\x65\x6e\x74\x3a\x20\x4d\x6f\x7a\x69" \
"\x6c\x6c\x61\x2f\x35\x2e\x30\x20\x28\x57\x69\x6e\x64\x6f\x77\x73" \
"\x20\x4e\x54\x20\x31\x30\x2e\x30\x3b\x20\x57\x69\x6e\x36\x34\x3b" \
"\x20\x78\x36\x34\x29\x20\x41\x70\x70\x6c\x65\x57\x65\x62\x4b\x69" \
"\x74\x2f\x35\x33\x37\x2e\x33\x36\x20\x28\x4b\x48\x54\x4d\x4c\x2c" \
"\x20\x6c\x69\x6b\x65\x20\x47\x65\x63\x6b\x6f\x29\x20\x43\x68\x72" \
"\x6f\x6d\x65\x2f\x37\x35\x2e\x30\x2e\x33\x37\x37\x30\x2e\x31\x30" \
"\x30\x20\x53\x61\x66\x61\x72\x69\x2f\x35\x33\x37\x2e\x33\x36\x0d" \
"\x0a\x41\x63\x63\x65\x70\x74\x3a\x20\x69\x6d\x61\x67\x65\x2f\x77" \
"\x65\x62\x70\x2c\x69\x6d\x61\x67\x65\x2f\x61\x70\x6e\x67\x2c\x69" \
"\x6d\x61\x67\x65\x2f\x2a\x2c\x2a\x2f\x2a\x3b\x71\x3d\x30\x2e\x38" \
"\x0d\x0a\x52\x65\x66\x65\x72\x65\x72\x3a\x20\x68\x74\x74\x70\x3a" \
"\x2f\x2f\x74\x65\x73\x74\x2e\x67\x69\x6c\x67\x69\x6c\x2e\x6e\x65" \
"\x74\x2f\x0d\x0a\x41\x63\x63\x65\x70\x74\x2d\x45\x6e\x63\x6f\x64" \
"\x69\x6e\x67\x3a\x20\x67\x7a\x69\x70\x2c\x20\x64\x65\x66\x6c\x61" \
"\x74\x65\x0d\x0a\x41\x63\x63\x65\x70\x74\x2d\x4c\x61\x6e\x67\x75" \
"\x61\x67\x65\x3a\x20\x6b\x6f\x2d\x4b\x52\x2c\x6b\x6f\x3b\x71\x3d" \
"\x30\x2e\x39\x2c\x65\x6e\x2d\x55\x53\x3b\x71\x3d\x30\x2e\x38\x2c" \
"\x65\x6e\x3b\x71\x3d\x30\x2e\x37\x0d\x0a\x0d\x0a";
void print_Mac(uint8_t* mac) {
	printf("Dmap : %02X:%02X:%02X:%02X:%02X:%02X\n", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
} // header 14

void print_ip(uint8_t* ip) {
	printf("%u.%u.%u.%u\n", ip[0], ip[1], ip[2], ip[3]);
} // header 20
void print_port(uint16_t*  port) {
	uint16_t temp = ((*port >> 8) | (*port << 8));
	printf("%u\n", temp);	//ntohs(*port));
}
int main(void) {
	
	printf("Dmap:");
	print_Mac(&packet[0]);
	printf("Smap :");
	print_Mac(&packet[6]);

	printf("Sip: ");
	print_ip(&packet[26]);

	printf("Dip: ");
	print_ip(&packet[30]);  // 포트까지 출력

	printf("sport: \n");
	print_port((uint16_t*)&packet[34]);

	printf("dport: \n");
	print_port((uint16_t*)&packet[36]);

	
}