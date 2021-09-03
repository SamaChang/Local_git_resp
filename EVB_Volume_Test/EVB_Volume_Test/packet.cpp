#include "packet.h"

void store_le_uint16(unsigned char *addr, unsigned short value)      /* big endian */
{
	addr[0] = value >> 8;
	addr[1] = value & 0xff;
}

unsigned short reverse_uint16(unsigned char *uint16_value)          /* big endian */
{
	//return  uint32_value[0] << 24 |
	//	uint32_value[1] << 16 |
	//	uint32_value[2] << 8 |
	//	uint32_value[3];
	return uint16_value[0] << 8 |
		uint16_value[1];
}

void send_msg(char *packet, unsigned char cmd, unsigned short size, unsigned char check)
{
	sendInfo *sed = (sendInfo *)packet;
	sed->Syn[0] = 0xef;
	sed->Syn[1] = 0xaa;
	sed->Msd = cmd;
	store_le_uint16(sed->Size, size);
	sed->checksum = check;
}

