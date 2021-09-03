#include "UsbConnect.h"
#include <qmessagebox.h>

UsbConnect::UsbConnect()
{

}

int UsbConnect::send_usb_data(uint8_t *packet, uint32_t len)
{
	int ret;
	int i = 0;

	uint32_t send_times = ROUND_DOWN_TIMES(len, FRAME_LEN);      
	for (i = 0; i < send_times; i++) {
		ret = usb_write((char*)packet + i * FRAME_LEN, FRAME_LEN, TIMEOUT);        
		if (ret < 0)
			return ESENDPACK;
	}
	uint32_t left_len = len - i * FRAME_LEN;     //不够一帧的长度
	if (left_len) {
		ret = usb_write((char*)packet + i * FRAME_LEN, left_len, TIMEOUT);        //参数：指针位置，发送数据长度，超时时间 
		if (ret < 0)
			return ESENDPACK;
	}

	return SUCCESS;
}

int UsbConnect::rec_usb_data(uint32_t id, uint8_t *send, uint8_t *recv)
{
	int ret;
	uint8_t *packet;
	resp_pack_head_t *resp = (resp_pack_head_t *)recv;

	pack_head(CMD_GET_RESULT, id, 0, send);
	while (1) {
		if (send_usb_data(send, GET_REQ_LEN(send)) < 0)    //第二次发送，头变了result为03
			return ESENDSTS;
		ret = usb_read((char*)resp, FRAME_LEN, TIMEOUT);   //参数：指针位置，读取长度，超时时间//返回是读取实际长度
		if (ret < 0)
			return EGETSTS;
		if (resp->head[0] == 'T' && resp->head[1] == 'S' && resp->head[2] == 'M'      //第一帧512包含13B的头+6B的头+数据部分；后面收到的512数据帧都是纯数据
			&& GET_RESP_RESULT(resp) != RESULT_NOT_READY)
		{
			Sleep(50);  //只要图片没准备好，not_ready的话，那就继续要，但是只要我要，下位机就给，如果没图数据，就给not_ready
			break;
		}


		/* msg route */
		MSG msg;
		while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
	}

	if (GET_RESP_RESULT(resp) == RESULT_SUCCESS) {
		uint8_t *dep_map = recv;
		uint32_t tot_len = GET_RESP_LEN(resp);        //收到第一帧数据的头里的len可以显示数据部分的总长度（下位机发的，告诉一共有多少数据），这里是加了头的总长度
		uint32_t valid_len = ret;                         /* first pack */

		tot_len -= valid_len;        //减去刚才收到的一帧长度
		dep_map += valid_len;        //刚刚收到一帧，这是下一帧开始的地址

		uint32_t recv_times = ROUND_UP_TIMES(tot_len, FRAME_LEN);   //又加上刚才的减去的一帧长度了（900）
		//一次读512，读很多次，全数据，用于保存图
		for (int i = 0; i < recv_times; i++) {
			ret = usb_read((char*)dep_map + i * FRAME_LEN, FRAME_LEN, TIMEOUT);   //从第二帧的地方开始存，存899次，再加上开始的一帧
			if (ret < 0)
				return EGETDAT;
		}
	}
	return SUCCESS;
}

int UsbConnect::get_ir_image(uint8_t *recv)
{
	int ret;
	uint8_t *packet;
	resp_pack_head_t *resp = (resp_pack_head_t *)recv;

	ret = usb_read((char*)resp, FRAME_LEN, TIMEOUT);
	if (ret < 0)
		return EGETDAT;
	if (resp->head[0] != 'T' || resp->head[1] != 'S' || resp->head[2] != 'M')
		return EGETDAT;   //没有解析到图片数据（BCTC新加）

	uint8_t *ir_img = recv;
	uint32_t tot_len = GET_RESP_LEN(resp);
	uint32_t valid_len = ret;                         /* first pack */

	tot_len -= valid_len;
	ir_img += valid_len;

	uint32_t recv_times = ROUND_UP_TIMES(tot_len, FRAME_LEN);
	for (int i = 0; i < recv_times; i++) {
		ret = usb_read((char*)ir_img + i * FRAME_LEN, FRAME_LEN, TIMEOUT);
		if (ret < 0)
			return EGETDAT;
	}

	return SUCCESS;
}


