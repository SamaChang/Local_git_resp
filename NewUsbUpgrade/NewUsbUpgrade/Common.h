#pragma once

#include <QObject>

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

class Common : public QObject
{
	Q_OBJECT

public:
	Common(QObject *parent=nullptr);
	~Common();
	void store_uint32(uint8_t *addr, uint32_t value_1);
	void add_table(uint8_t *addr, uint32_t value, uint32_t res);
	void add_bin_head(uint32_t addr, uint32_t bin_len, uint32_t tmp_res, uint8_t *data);
};
