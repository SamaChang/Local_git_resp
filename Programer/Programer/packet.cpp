#include "packet.h"

void short2char(char *size, short len)
{
	size[0] = len >> 8;
	size[1] = len & 0xff;
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

void store_le_uint32(unsigned char *addr, unsigned int value)     /* big endian */
{
	addr[0] = value >> 24;
	addr[1] = (value >> 16) & 0xff;
	addr[2] = (value >> 8) & 0xff;
	addr[3] = value & 0xff;
}

void data2protorl(char *data,short size,char id)
{
	dataProtorl *pro = (dataProtorl*)data;
	pro->SyncWord[0] = 0x55;
	pro->SyncWord[1] = 0xaa;
	pro->SyncWord[2] = 0x5a;
	pro->SyncWord[3] = 0x5a;
	short2char(pro->MsgSize, size);
	pro->MsgID = id;
}

void insertEraseDataBody()
{
	
}


void pc2tx231(char *data)
{

}
