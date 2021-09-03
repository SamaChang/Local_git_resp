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
	uint32_t left_len = len - i * FRAME_LEN;     //����һ֡�ĳ���
	if (left_len) {
		ret = usb_write((char*)packet + i * FRAME_LEN, left_len, TIMEOUT);        //������ָ��λ�ã��������ݳ��ȣ���ʱʱ�� 
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
		if (send_usb_data(send, GET_REQ_LEN(send)) < 0)    //�ڶ��η��ͣ�ͷ����resultΪ03
			return ESENDSTS;
		ret = usb_read((char*)resp, FRAME_LEN, TIMEOUT);   //������ָ��λ�ã���ȡ���ȣ���ʱʱ��//�����Ƕ�ȡʵ�ʳ���
		if (ret < 0)
			return EGETSTS;
		if (resp->head[0] == 'T' && resp->head[1] == 'S' && resp->head[2] == 'M'      //��һ֡512����13B��ͷ+6B��ͷ+���ݲ��֣������յ���512����֡���Ǵ�����
			&& GET_RESP_RESULT(resp) != RESULT_NOT_READY)
		{
			Sleep(50);  //ֻҪͼƬû׼���ã�not_ready�Ļ����Ǿͼ���Ҫ������ֻҪ��Ҫ����λ���͸������ûͼ���ݣ��͸�not_ready
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
		uint32_t tot_len = GET_RESP_LEN(resp);        //�յ���һ֡���ݵ�ͷ���len������ʾ���ݲ��ֵ��ܳ��ȣ���λ�����ģ�����һ���ж������ݣ��������Ǽ���ͷ���ܳ���
		uint32_t valid_len = ret;                         /* first pack */

		tot_len -= valid_len;        //��ȥ�ղ��յ���һ֡����
		dep_map += valid_len;        //�ո��յ�һ֡��������һ֡��ʼ�ĵ�ַ

		uint32_t recv_times = ROUND_UP_TIMES(tot_len, FRAME_LEN);   //�ּ��ϸղŵļ�ȥ��һ֡�����ˣ�900��
		//һ�ζ�512�����ܶ�Σ�ȫ���ݣ����ڱ���ͼ
		for (int i = 0; i < recv_times; i++) {
			ret = usb_read((char*)dep_map + i * FRAME_LEN, FRAME_LEN, TIMEOUT);   //�ӵڶ�֡�ĵط���ʼ�棬��899�Σ��ټ��Ͽ�ʼ��һ֡
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
		return EGETDAT;   //û�н�����ͼƬ���ݣ�BCTC�¼ӣ�

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


