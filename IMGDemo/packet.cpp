#include "packet.h"
#include "pic_deal.h"
#include "usb.h"
#include "common.h"



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


int send_packet(uint8_t *packet, uint32_t len)
{
    int ret;   
    int i = 0; 

    uint32_t send_times = ROUND_DOWN_TIMES(len, FRAME_LEN);
    for(i = 0; i < send_times; i++) {
        ret = usb_write((char*)packet + i * FRAME_LEN, FRAME_LEN, TIMEOUT);
        if (ret < 0)
            return ESENDPACK;
    }
    uint32_t left_len = len - i * FRAME_LEN;
    if (left_len) {
        ret = usb_write((char*)packet + i * FRAME_LEN, left_len, TIMEOUT);
        if (ret < 0)
            return ESENDPACK;
    }
    
    return SUCCESS;
}

int get_response(uint32_t id, uint8_t *send, uint8_t *recv)
{   
    int ret;
    uint8_t *packet;
	resp_pack_head_t *resp = (resp_pack_head_t *)recv;

    pack_head(CMD_GET_RESULT, id, 0, send);
    while(1) {
		if (send_packet(send, GET_REQ_LEN(send)) < 0)
			return ESENDSTS;
        ret = usb_read((char*)resp, FRAME_LEN, TIMEOUT);
		if (ret < 0)
			return EGETSTS;
		if (resp->head[0] == 'T' && resp->head[1] == 'S' && resp->head[2] == 'M'
			&& GET_RESP_ID(resp) == id && GET_RESP_RESULT(resp) != RESULT_NOT_READY)
            break;   

		/* msg route */
		MSG msg;
		while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
    }

    return SUCCESS;
}