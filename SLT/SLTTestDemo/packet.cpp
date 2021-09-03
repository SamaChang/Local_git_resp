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

void send_info(char *packet, unsigned char cmd, unsigned short size, unsigned char check)
{
	send_packet *sendInfo = (send_packet *)packet;
	sendInfo->SyncWord[0] = 0xef;
	sendInfo->SyncWord[1] = 0xaa;
	sendInfo->Msgid = cmd;
	store_le_uint16(sendInfo->Size, size);
	sendInfo->CheckSum = check;
}

void rec_info(char *packet)
{
	rec_ack *recInfo = (rec_ack *)packet;
}
