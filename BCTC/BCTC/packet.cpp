#include "packet.h"

void store_le_uint32(unsigned char *addr, unsigned int value)     /* big endian */
{
	addr[0] = value >> 24;
	addr[1] = (value >> 16) & 0xff;
	addr[2] = (value >> 8) & 0xff;
	addr[3] = value & 0xff;
}

unsigned short reverse_uint16(unsigned char *uint16_value)          /* big endian */
{
	return uint16_value[0] << 8 |
		uint16_value[1];
}

uint32_t reverse_uint32(uint8_t *uint32_value)          /* big endian */
{
	return  uint32_value[0] << 24 |
		uint32_value[1] << 16 |
		uint32_value[2] << 8 |
		uint32_value[3];
}
//´®¿Ú·¢ËÍ
void port_send_msg(unsigned char *data,unsigned int size,unsigned char cmd)
{
	PortDataProtorl *sendData = (PortDataProtorl *)data;
	sendData->SynWord[0] = 0xef;
	sendData->SynWord[1] = 0xaa;
	sendData->Cmd = cmd;
	store_le_uint32(sendData->Size, size);
}
//usb·¢ËÍ
void pack_head(uint8_t cmd, uint32_t id, uint32_t payload_len, uint8_t *packet)
{
	req_pack_head_t *req = (req_pack_head_t *)packet;
	req->head[0] = 'T';
	req->head[1] = 'S';
	req->head[2] = 'M';
	req->cmd = cmd;
	store_le_uint32(req->id, id);
	store_le_uint32(req->len, payload_len);

	return;
}