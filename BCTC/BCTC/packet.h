#pragma once
#include "def.h"
#define BCTC_CMD    0xa0
#define BCTC_CMD_CAP    0xa1   //拍图
#define BCTC_PIC_SERIAL 0x14
#define TIMEOUT     3000
#define ESENDPACK   -21
#define ESENDSTS    -22
#define EGETSTS     -23
#define EGETDAT     -24
#define NOPIC		0xbb		//BCTC无照片
#define CMD_GET_RESULT			0x3
#define RESULT_NOT_READY		0xF0
#define RESULT_SUCCESS			0xF1
#define RESULT_FAIL				0xF2
#define BUF_RECV_IR_SPK_DEPTH            (5*1024*1024)                          /*5M*///图漾用

#define GET_RESP_RESULT(resp)  ((((resp_pack_head_t*)resp)->result))
#define GET_PIC_CHANNEL(pic_payload)   (((((pic_payload_t*)(pic_payload))->ch[0]) << 8) + (((pic_payload_t*)(pic_payload))->ch[1]))
#define GET_PIC_HEIGHT(pic_payload_height)   (((((pic_payload_t*)(pic_payload_height))->height[0]) << 8) + (((pic_payload_t*)(pic_payload_height))->height[1]))
#define GET_PIC_WIDTH(pic_payload_width)   (((((pic_payload_t*)(pic_payload_width))->width[0]) << 8) + (((pic_payload_t*)(pic_payload_width))->width[1]))
#define GET_ID(resp_id)			(((((resp_pack_head_t*)(resp_id))->id[0]) << 24) + ((((resp_pack_head_t*)(resp_id))->id[1]) << 16)+((((resp_pack_head_t*)(resp_id))->id[2]) << 8) \
								+((((resp_pack_head_t*)(resp_id))->id[3])))
#define GET_REQ_LEN(req)       (sizeof(req_pack_head_t) + ((((req_pack_head_t*)req)->len[0]) << 24) \
                                + ((((req_pack_head_t*)req)->len[1]) << 16) + ((((req_pack_head_t*)req)->len[2]) << 8) \
                                + (((req_pack_head_t*)req)->len[3]))
#define GET_RESP_LEN(resp)     (sizeof(resp_pack_head_t) + ((((resp_pack_head_t*)resp)->len[0]) << 24) \
                                + ((((resp_pack_head_t*)resp)->len[1]) << 16) + ((((resp_pack_head_t*)resp)->len[2]) << 8) \
                                + (((resp_pack_head_t*)resp)->len[3]))

//串口发送头
typedef struct 
{
	unsigned char SynWord[2];
	unsigned char Cmd;
	unsigned char Size[4];
	//unsigned char sendCmd[8];
	//unsigned char data[0];
}PortDataProtorl;

//usb发送的头
typedef struct {
	uint8_t head[3];
	uint8_t cmd;
	uint8_t id[4];
	uint8_t len[4];
	uint8_t dat[0];
} req_pack_head_t;

//读取数据的协议的帧头
typedef struct {
	uint8_t head[3];
	uint8_t cmd;
	uint8_t result;
	uint8_t id[4];
	uint8_t len[4];
	uint8_t dat[0];
} resp_pack_head_t;

typedef struct {
	uint8_t ch[2];
	uint8_t height[2];
	uint8_t width[2];
	uint8_t dat[0];
} pic_payload_t;

enum /*PIC_FORMAT*/
{
	IR_RAW = 0,
	IR_YUYV422,
	RGB_YUYV422,
	SPK_RAW,
	DEPTH_RAW,
	DEPTH_YUYV422
};
enum 
{
	BCTC_QA_ERROR_RESOLUTION = 0,
	BCTC_QA_ERROR_COVER,
	BCTC_QA_ERROR_INTERPUPILLARY_DISTANCE,
	BCTC_QA_ERROR_FUZZY,
	BCTC_QA_ERROR_EXPRESSION,
	BCTC_QA_ERROR_ANGLE,
	BCTC_QA_ERROR_LUX,
	BCTC_QA_ERROR_MULTIPLE_FACE,
};

void store_le_uint32(unsigned char *addr, unsigned int value);
void port_send_msg(unsigned char *data, unsigned int size, unsigned char cmd);
unsigned short reverse_uint16(unsigned char *uint16_value);
uint32_t reverse_uint32(uint8_t *uint32_value);
void pack_head(uint8_t cmd, uint32_t id, uint32_t payload_len, uint8_t *packet);
