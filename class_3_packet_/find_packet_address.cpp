#include<stdint.h>
#include<stdio.h>
#include<WinSock2.h>
//#pragma 
uint16_t my_ntohs(uint16_t n)
{
	return n >> 8 | n << 8;

}
uint16_t my_htons(uint16_t n) {
	return n << 8 | n >> 8;
}
uint32_t my_ntohl(uint32_t n)
{
	return n << 24 | n << 8  & 0x00ff0000 | n >> 8  & 0x0000ff0000  | n >> 24;
}
uint16_t my_htonl(uint32_t n) {
	return  n >> 24 | n >> 8 & 0x00ff0000 | n << 8 & 0x0000ff0000 | n << 24;
}
int main(void) {
	uint8_t packet[]{ 0x12, 0x34 , 0x56, 0x78};
	uint32_t* p = reinterpret_cast<uint32_t*>(packet);
	uint32_t ip = *p;
	//port = my_ntohs(*p);
	ip = ntohl(ip);
	printf("%02x ", ip );
	//printf("%x\n", i);

}
