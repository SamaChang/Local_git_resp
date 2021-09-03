#include "packet.h"
#include "pic_deal.h"
#include "usb.h"
#include "common.h"
#include "def.h"


void exposure_pack_payload(int sel, uint8_t *buf)
{
	exposure_para_t *payload = (exposure_para_t *)buf;

	payload->expo = sel;
}

void resolution_pack_payload(int sel, uint8_t *buf)
{
	img_param_payload_t *payload = (img_param_payload_t *)buf;

	if (SEL_ALL_IMGS == sel) {
		store_le_uint16(payload->ir.ch, ALL_IMGS_IR_CH);
		store_le_uint16(payload->ir.width, ALL_IMGS_WIDTH);
		store_le_uint16(payload->ir.height, ALL_IMGS_HEIGHT);
		store_le_uint16(payload->rgb.ch, ALL_IMGS_RGB_CH);
		store_le_uint16(payload->rgb.width, ALL_IMGS_WIDTH);
		store_le_uint16(payload->rgb.height, ALL_IMGS_HEIGHT);
		store_le_uint16(payload->depth.ch, ALL_IMGS_DEPTH_CH);
		store_le_uint16(payload->depth.width, ALL_IMGS_WIDTH);
		store_le_uint16(payload->depth.height, ALL_IMGS_HEIGHT);
	}
	else if (SEL_ALL_IMGS_SPK == sel) {
		store_le_uint16(payload->ir.ch, ALL_IMGS_IR_CH);
		store_le_uint16(payload->ir.width, ALL_IMGS_WIDTH);
		store_le_uint16(payload->ir.height, ALL_IMGS_HEIGHT);
		store_le_uint16(payload->rgb.ch, ALL_IMGS_RGB_CH);
		store_le_uint16(payload->rgb.width, ALL_IMGS_WIDTH);
		store_le_uint16(payload->rgb.height, ALL_IMGS_HEIGHT);
		store_le_uint16(payload->depth.ch, ALL_IMGS_DEPTH_CH);
		store_le_uint16(payload->depth.width, ALL_IMGS_WIDTH);
		store_le_uint16(payload->depth.height, ALL_IMGS_HEIGHT);
	}
	else if (SEL_ALL_IMGS_SPK_DBG == sel) {
		store_le_uint16(payload->ir.ch, ALL_IMGS_IR_CH);
		store_le_uint16(payload->ir.width, ALL_IMGS_WIDTH);
		store_le_uint16(payload->ir.height, ALL_IMGS_HEIGHT);
		store_le_uint16(payload->rgb.ch, ALL_IMGS_RGB_CH);
		store_le_uint16(payload->rgb.width, ALL_IMGS_WIDTH);
		store_le_uint16(payload->rgb.height, ALL_IMGS_HEIGHT);
		store_le_uint16(payload->depth.ch, ALL_IMGS_DEPTH_CH);
		store_le_uint16(payload->depth.width, ALL_IMGS_WIDTH);
		store_le_uint16(payload->depth.height, ALL_IMGS_HEIGHT);
	}
	else if (SEL_IR_IMG == sel) {
		store_le_uint16(payload->ir.ch, IR_IMG_CH);
		store_le_uint16(payload->ir.width, IR_IMG_WIDTH);
		store_le_uint16(payload->ir.height, IR_IMG_HEIGHT);
		store_le_uint16(payload->rgb.ch, DEFAULT_IMG_RGB_CH);
		store_le_uint16(payload->rgb.width, DEFAULT_IMG_WIDTH);
		store_le_uint16(payload->rgb.height, DEFAULT_IMG_HEIGHT);
		store_le_uint16(payload->depth.ch, DEFAULT_IMG_DEPTH_CH);
		store_le_uint16(payload->depth.width, DEFAULT_IMG_WIDTH);
		store_le_uint16(payload->depth.height, DEFAULT_IMG_HEIGHT);

	}
	else if (SEL_RGB_IMG == sel) {
		store_le_uint16(payload->ir.ch, DEFAULT_IMG_IR_CH);
		store_le_uint16(payload->ir.width, DEFAULT_IMG_WIDTH);
		store_le_uint16(payload->ir.height, DEFAULT_IMG_HEIGHT);
		store_le_uint16(payload->rgb.ch, RGB_IMG_CH);
		store_le_uint16(payload->rgb.width, RGB_IMG_WIDTH);
		store_le_uint16(payload->rgb.height, RGB_IMG_HEIGHT);
		store_le_uint16(payload->depth.ch, DEFAULT_IMG_DEPTH_CH);
		store_le_uint16(payload->depth.width, DEFAULT_IMG_WIDTH);
		store_le_uint16(payload->depth.height, DEFAULT_IMG_HEIGHT);
	}

	//欧菲
	else if (SEL_OFI_DEPTH == sel) {
		store_le_uint16(payload->ir.ch, DEPTH_OFI_CH);
		store_le_uint16(payload->ir.width, DEPTH_OFI_WIDTH);
		store_le_uint16(payload->ir.height, DEPTH_OFI_HEIGHT);
		store_le_uint16(payload->rgb.ch, DEFAULT_IMG_RGB_CH);
		store_le_uint16(payload->rgb.width, DEFAULT_IMG_WIDTH);
		store_le_uint16(payload->rgb.height, DEFAULT_IMG_HEIGHT);
		store_le_uint16(payload->depth.ch, DEFAULT_IMG_DEPTH_CH);
		store_le_uint16(payload->depth.width, DEFAULT_IMG_WIDTH);
		store_le_uint16(payload->depth.height, DEFAULT_IMG_HEIGHT);
	}

	else if (SEL_OFI_IR == sel) {
		store_le_uint16(payload->ir.ch, IR_OFI_CH);
		store_le_uint16(payload->ir.width, IR_OFI_WIDTH);
		store_le_uint16(payload->ir.height, IR_OFI_HEIGHT);
		store_le_uint16(payload->rgb.ch, DEFAULT_IMG_RGB_CH);
		store_le_uint16(payload->rgb.width, DEFAULT_IMG_WIDTH);
		store_le_uint16(payload->rgb.height, DEFAULT_IMG_HEIGHT);
		store_le_uint16(payload->depth.ch, DEFAULT_IMG_DEPTH_CH);
		store_le_uint16(payload->depth.width, DEFAULT_IMG_WIDTH);
		store_le_uint16(payload->depth.height, DEFAULT_IMG_HEIGHT);
	}

	else if (SEL_OFI_SPK == sel) {
		store_le_uint16(payload->ir.ch, SPK_OFI_CH);
		store_le_uint16(payload->ir.width, DEPTH_OFI_WIDTH);
		store_le_uint16(payload->ir.height, DEPTH_OFI_HEIGHT);
		store_le_uint16(payload->rgb.ch, DEFAULT_IMG_RGB_CH);
		store_le_uint16(payload->rgb.width, DEFAULT_IMG_WIDTH);
		store_le_uint16(payload->rgb.height, DEFAULT_IMG_HEIGHT);
		store_le_uint16(payload->depth.ch, DEFAULT_IMG_DEPTH_CH);
		store_le_uint16(payload->depth.width, DEFAULT_IMG_WIDTH);
		store_le_uint16(payload->depth.height, DEFAULT_IMG_HEIGHT);
	}
}

void compressedBf(uint8_t *packet,uint8_t *data)
{
	compressData *da = (compressData *)packet;
	da->data = data;
}

//默认发送参数
void defaultParam(uint8_t *packet)
{
	calibration_param *par = (calibration_param *)packet;
	par->cmd = CMD_OFI_CALC_DEFAULT;
}

//计算后的参数
void calcIrPam(uint8_t *packet,double calValue)
{
	calc_after_ir *param = (calc_after_ir *)packet;
	//param->cmd = CMD_OFI_CALC_AFTER;
	param->value = calValue;
}

//发送SPK参数
void calibrationParamSpk(uint8_t *packet)
{
	calibration_param *par = (calibration_param *)packet;
	par->cmd = CMD_OFI_SPK;
}
//发送IR标定参数
void calibrationParamIr(uint8_t *packet)
{
	calibration_param *par = (calibration_param *)packet;
	par->cmd = CMD_OFI_IR;
	//par->mA = 0x59;
	//par->time[0] = 0x24;
	//par->time[1] = 0xe6;
	//par->gain = 0x10;
}

//暂定4位的sn
void pack_sn(uint8_t *packet, uint32_t snNum,uint8_t offset)
{
	img_sn_inf *req = (img_sn_inf *)packet;
	store_le_uint32((req + offset / (sizeof(img_sn_inf)))->sn, snNum);  //以大端序方式存储到发送数据中，offset为偏移pack_head长度的偏移量
}//(img_sn_inf)的单位是4字节，加offset并不是指针向右移动了offset个字节，而是向右移动了offset个（img_sn_inf），所以要除以4

void pack_new_sn(uint8_t *packet, uint32_t snNum)
{
	img_sn_inf *req = (img_sn_inf *)packet;
	store_le_uint32(req->sn, snNum);
}

void pack_head(uint8_t cmd, uint32_t id, uint32_t payload_len, uint8_t *packet)   //payload_len是计算去除头后的长度，必须加，因为发送数据的长度等于头+数据
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
	//img_sn_inf
	uint32_t send_times = ROUND_DOWN_TIMES(len, FRAME_LEN);      //数据长度除以一帧长度，得出几帧
	for (i = 0; i < send_times; i++) {
		ret = usb_write((char*)packet + i * FRAME_LEN, FRAME_LEN, TIMEOUT);        //一帧一帧的发，指针一直右移一帧长度
		if (ret < 0)
			return ESENDPACK;
	}
	uint32_t left_len = len - i * FRAME_LEN;     //不够一帧的长度
	if (left_len) {
		ret = usb_write((char*)packet + i * FRAME_LEN, left_len, TIMEOUT);        //参数：指针位置，剩余不够整帧的数据长度，超时时间 
		if (ret < 0)
			return ESENDPACK;
	}

	return SUCCESS;
}

int get_depth_map(uint32_t id, uint8_t *send, uint8_t *recv)
{
	int ret;
	//uint8_t *packet;
	resp_pack_head_t *resp = (resp_pack_head_t *)recv;

	pack_head(CMD_GET_RESULT, id, 0, send);
	while (1) {
		if (send_packet(send, GET_REQ_LEN(send)) < 0)    //第二次发送，头变了result为03
			return ESENDSTS;
		ret = usb_read((char*)resp, FRAME_LEN, TIMEOUT);   //参数：指针位置，读取长度，超时时间//返回是读取实际长度
		if (ret < 0)
			return EGETSTS;
		if (resp->head[0] == 'T' && resp->head[1] == 'S' && resp->head[2] == 'M'      //第一帧512包含13B的头+6B的头+数据部分；后面收到的512数据帧都是纯数据
			&& GET_RESP_RESULT(resp) != RESULT_NOT_READY)
			break;

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
//combox的第一个，ir和rgb都不发数据，直接读，ir和rgb一样逻辑
int get_ir_image(uint32_t id, uint8_t *send, uint8_t *recv)
{
	int ret;
	uint8_t *packet;
	resp_pack_head_t *resp = (resp_pack_head_t *)recv;

	ret = usb_read((char*)resp, FRAME_LEN, TIMEOUT);
	if (ret < 0)
		return EGETDAT;
	if (resp->head[0] != 'T' || resp->head[1] != 'S' || resp->head[2] != 'M')
		return EGETDAT;

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

int get_rgb_image(uint32_t id, uint8_t *send, uint8_t *recv)
{
	int ret;
	uint8_t *packet;
	resp_pack_head_t *resp = (resp_pack_head_t *)recv;

	ret = usb_read((char*)resp, FRAME_LEN, TIMEOUT);
	if (ret < 0)
		return EGETDAT;
	if (resp->head[0] != 'T' || resp->head[1] != 'S' || resp->head[2] != 'M')
		return EGETDAT;

	uint8_t *rgb_img = recv;
	uint32_t tot_len = GET_RESP_LEN(resp);
	uint32_t valid_len = ret;                         /* first pack */

	tot_len -= valid_len;
	rgb_img += valid_len;

	uint32_t recv_times = ROUND_UP_TIMES(tot_len, FRAME_LEN);
	for (int i = 0; i < recv_times; i++) {
		ret = usb_read((char*)rgb_img + i * FRAME_LEN, FRAME_LEN, TIMEOUT);
		if (ret < 0)
			return EGETDAT;
	}

	return SUCCESS;
}

int get_response(uint32_t id, uint8_t *send, uint8_t *recv)
{
	int ret;
	uint8_t *packet;
	resp_pack_head_t *resp = (resp_pack_head_t *)recv;

	pack_head(CMD_GET_RESULT, id, 0, send);
	while (1) {
		if (send_packet(send, GET_REQ_LEN(send)) < 0)
			return ESENDSTS;
		ret = usb_read((char*)resp, FRAME_LEN, TIMEOUT);
		if (ret < 0)
			return EGETSTS;
		if (resp->head[0] == 'T' && resp->head[1] == 'S' && resp->head[2] == 'M'
			&& GET_RESP_RESULT(resp) != RESULT_NOT_READY)
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