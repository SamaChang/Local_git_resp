#pragma once

#include "def.h"

#define TIMEOUT     1000
#define ESENDPACK   -21
#define ESENDSTS    -22
#define EGETSTS     -23

typedef struct {
    uint8_t head[3];
    uint8_t cmd;
    uint8_t id[4];
    uint8_t len[4];
    uint8_t dat[0];   
} req_pack_head_t;

typedef struct {
    uint8_t ch[2];
    uint8_t height[2];
    uint8_t width[2];
    uint8_t dat[0];
} pic_payload_t;

typedef struct {
    uint8_t head[3];
    uint8_t cmd;
    uint8_t result;
    uint8_t id[4];
    uint8_t len[4];
    uint8_t dat[0];   
} resp_pack_head_t;

typedef struct {
    uint8_t faceid[4];
    uint8_t score[2];
    uint8_t qvalue[2];
} pic_score_t;


#define CMD_REGISTER       0x1
#define CMD_RECOGNISE      0x2
#define CMD_GET_RESULT     0x3

#define RESULT_NOT_READY   0xF0
#define RESULT_SUCCESS     0xF1
#define RESULT_FAIL        0xF2


#define GET_REQ_CMD(req)       ((((req_pack_head_t*)req)->cmd))
#define GET_REQ_LEN(req)       (sizeof(req_pack_head_t) + ((((req_pack_head_t*)req)->len[0]) << 24) \
                                + ((((req_pack_head_t*)req)->len[1]) << 16) + ((((req_pack_head_t*)req)->len[2]) << 8) \
                                + (((req_pack_head_t*)req)->len[3]))


#define GET_RESP_CMD(resp)     ((((resp_pack_head_t*)resp)->cmd))
#define GET_RESP_RESULT(resp)  ((((resp_pack_head_t*)resp)->result))
#define GET_RESP_ID(resp)     (((((resp_pack_head_t*)resp)->id[0]) << 24) + ((((resp_pack_head_t*)resp)->id[1]) << 16) \
                                + ((((resp_pack_head_t*)resp)->id[2]) << 8) + (((resp_pack_head_t*)resp)->id[3]))

#define GET_RESP_LEN(resp)     (sizeof(resp_pack_head_t) + ((((resp_pack_head_t*)resp)->len[0]) << 24) \
                                + ((((resp_pack_head_t*)resp)->len[1]) << 16) + ((((resp_pack_head_t*)resp)->len[2]) << 8) \
                                + (((resp_pack_head_t*)resp)->len[3]))


#define GET_PIC_CHANNEL(pic_payload)   (((((pic_payload_t*)pic_payload)->ch[0]) << 8) + (((pic_payload_t*)pic_payload)->ch[1]))
#define GET_PIC_HEIGHT(pic_payload)    (((((pic_payload_t*)pic_payload)->height[0]) << 8) + (((pic_payload_t*)pic_payload)->height[1]))
#define GET_PIC_WIDTH(pic_payload)     (((((pic_payload_t*)pic_payload)->width[0]) << 8) + (((pic_payload_t*)pic_payload)->width[1]))


#define GET_PIC_ID(pic_score)   (((((pic_score_t*)pic_score)->faceid[0]) << 24) + ((((pic_score_t*)pic_score)->faceid[1]) << 16) \
                                + ((((pic_score_t*)pic_score)->faceid[2]) << 8) + (((pic_score_t*)pic_score)->faceid[3]))
#define GET_PIC_SCORE(pic_score)   (((((pic_score_t*)pic_score)->score[0]) << 8) + (((pic_score_t*)pic_score)->score[1]))
#define GET_PIC_QVALUE(pic_score)   (((((pic_score_t*)pic_score)->qvalue[0]) << 8) + (((pic_score_t*)pic_score)->qvalue[1]))


void pack_head(uint8_t cmd, uint32_t id, uint32_t payload_len, uint8_t *packet);
int send_packet(uint8_t *packet, uint32_t len);
int get_response(uint32_t id, uint8_t *send, uint8_t *recv);