#pragma once
#include "def.h"

#define TIMEOUT     3000
#define ESENDPACK   -21
#define ESENDSTS    -22
#define EGETSTS     -23
#define EGETDAT     -24

#define GET_REQ_CMD(req)       ((((req_pack_head_t*)req)->cmd))

#define GET_REQ_LEN(req)       (sizeof(req_pack_head_t) + ((((req_pack_head_t*)req)->len[0]) << 24) \
                                + ((((req_pack_head_t*)req)->len[1]) << 16) + ((((req_pack_head_t*)req)->len[2]) << 8) \
                                + (((req_pack_head_t*)req)->len[3]))

#define GET_RESP_LEN(resp)     (sizeof(resp_pack_head_t) + ((((resp_pack_head_t*)resp)->len[0]) << 24) \
                                + ((((resp_pack_head_t*)resp)->len[1]) << 16) + ((((resp_pack_head_t*)resp)->len[2]) << 8) \
                                + (((resp_pack_head_t*)resp)->len[3]))

#define GET_RESP_RESULT(resp)  ((((resp_pack_head_t*)resp)->result))
//发送的头
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

//16字节对齐头
typedef struct {
	uint8_t magic[4];
	uint8_t load_addr[4];
	uint8_t img_len[4];
	uint8_t res[4];
}bin_head;

//参数结构
typedef struct {
	uint8_t magic[4];
	uint8_t offset[4];
	uint8_t res[4];
}para_struct;


void packet_send(uint8_t cmd, uint32_t id, uint32_t payload_len, uint8_t *data);
void store_le_uint32(uint8_t *addr, uint32_t value);
int connect_send(uint8_t *packet, uint32_t len/*,int count*/);   //握手发送
//int data_packet_send(uint8_t *packet, uint32_t len , char *data, uint8_t *recv);     //数据分包发送
int get_con_acd(uint32_t id, uint8_t *send, uint8_t *recv, uint8_t send_cmd, uint8_t rec_cmd/*,int count*/);   //握手接收
int get_rec(uint8_t *recv, uint8_t cmd, int timeout);
/*static*/ uint64_t reflect(uint64_t ref, uint8_t ch);
/*static*/ void gen_normal_table(uint32_t *table);
/*static*/ uint32_t reverse_table_crc(uint8_t *data, int32_t len, uint32_t *table);
/*static*/ uint32_t crc32_bit(uint8_t *ptr, uint32_t len);
uint32_t reverse_uint32(uint8_t *uint32_value);
void add_bin_head(uint32_t addr, uint32_t bin_len, uint32_t tmp_res, uint8_t *data);
void sm_store_le_uint32(uint8_t *addr, uint32_t value);
uint32_t htonl(uint32_t value);
void add_table(uint8_t *addr, uint32_t value, uint32_t res);
