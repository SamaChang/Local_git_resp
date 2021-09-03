#include "packet.h"
#include <iostream>
#include <mutex>
static uint32_t Table2[256];

/*static*/ uint64_t reflect(uint64_t ref, uint8_t ch)
{
	int i;
	uint64_t value = 0;
	for (i = 1; i < (ch + 1); i++) {
		if (ref & 1) {
			value |= 1 << (ch - i);
		}
		ref >>= 1;
	}
	return value;
}

/*static*/ void gen_normal_table(uint32_t *table)
{
	uint32_t gx = 0x04c11db7;
	uint32_t temp;
	int i, j;
	for (i = 0; i <= 0xFF; i++) {
		temp = reflect(i, 8);
		table[i] = temp << 24;
		for (j = 0; j < 8; j++) {
			unsigned long int t1, t2;
			unsigned long int flag = table[i] & 0x80000000;
			t1 = (table[i] << 1);
			if (flag == 0) {
				t2 = 0;
			}
			else {
				t2 = gx;
			}
			table[i] = t1 ^ t2;
		}
		table[i] = reflect(table[i], 32);
	}
}

/*static*/ uint32_t reverse_table_crc(uint8_t *data, int32_t len, uint32_t *table)
{
	uint32_t crc = 0xffffffff;
	uint8_t *p = data;
	int i;
	for (i = 0; i < len; i++) {
		crc = table[(crc ^ (*(p + i))) & 0xff] ^ (crc >> 8);
	}
	return  ~crc;
}

/*static*/ uint32_t crc32_bit(uint8_t *ptr, uint32_t len)
{
	uint32_t crc;
	static uint8_t init_table = 0;
	if (init_table == 0) {
		init_table = 1;
		gen_normal_table(Table2);
	}
	crc = reverse_table_crc(ptr, len, Table2);
	return crc;
}
uint32_t htonl(uint32_t value)
{
	return ((value << 24) | ((value << 8) & 0x00FF0000) | ((value >> 8) & 0x0000FF00) | (value >> 24));
}
void sm_store_le_uint32(uint8_t *addr, uint32_t value_1)   /*small endian*/
{
	uint32_t value = htonl(value_1);
	addr[0] = value >> 24;
	addr[1] = (value >> 16) & 0xff;
	addr[2] = (value >> 8) & 0xff;
	addr[3] = value & 0xff;
}

void store_le_uint32(uint8_t *addr, uint32_t value)     /* big endian */
{
	addr[0] = value >> 24;
	addr[1] = (value >> 16) & 0xff;
	addr[2] = (value >> 8) & 0xff;
	addr[3] = value & 0xff;
}

uint32_t reverse_uint32(uint8_t *uint32_value)          /* big endian */
{
	return  uint32_value[0] << 24 |
		uint32_value[1] << 16 |
		uint32_value[2] << 8 |
		uint32_value[3];
}

void add_table(uint8_t *addr, uint32_t value, uint32_t res)
{
	para_struct *para = (para_struct *)addr;
	para->magic[0] = 'Q';
	para->magic[1] = 'W';
	para->magic[2] = 'Z';
	para->magic[3] = 'N';
	sm_store_le_uint32(para->offset, value);
	sm_store_le_uint32(para->res, res);
}

void packet_send(uint8_t cmd, uint32_t id, uint32_t payload_len,uint8_t *data)
{
	req_pack_head_t *req = (req_pack_head_t *)data;
	req->head[0] = 'T';
	req->head[1] = 'S';
	req->head[2] = 'M';
	req->cmd = cmd;
	store_le_uint32(req->id, id);
	store_le_uint32(req->len, payload_len);
}

int connect_send(uint8_t *packet, uint32_t len/*,int count*/)
{
	int ret;
	int i = 0;
	//usb_dev_handle *handle = get_handle_list()[count];
	uint32_t send_times = ROUND_DOWN_TIMES(len, FRAME_LEN);      //数据长度除以一帧长度，得出几帧
	for (i = 0; i < send_times; i++) {
		ret = usb_write((char*)packet + i * FRAME_LEN, FRAME_LEN, TIMEOUT/*, handle*/);        //一帧一帧的发，指针一直右移一帧长度
		if (ret < 0)
			return ESENDPACK;
	}
	uint32_t left_len = len - i * FRAME_LEN;     //不够一帧的长度
	if (left_len) {
		ret = usb_write((char*)packet + i * FRAME_LEN, left_len, TIMEOUT/*, handle*/);        //参数：指针位置，发送数据长度，超时时间 
		if (ret < 0)
			return ESENDPACK;
	}

	return SUCCESS;
}
/*
packet:每个512包
len:数据部分长度
data:总数据
*/
//int data_packet_send(uint8_t *packet, uint32_t len, char *data, uint8_t *recv)
//{
//	int ret;
//	int i = 0;
//	uint8_t crc_data[4] = { 0 };
//	resp_pack_head_t *resp = (resp_pack_head_t *)recv;
//
//	uint32_t send_times = ROUND_DOWN_TIMES(len, DATA_PER_LEN);      //数据长度除以一帧长度，得出几帧
//	for (i = 0; i < send_times; i++) {
//		packet_send(USB_UPGRADE_SEND_BIN_CMD, 0, DATA_PER_LEN, packet);
//		memcpy(packet/* + i * FRAME_LEN*/ + sizeof(req_pack_head_t), data + i * DATA_PER_LEN, DATA_PER_LEN);
//		//uint32_t crc_value = crc32_bit(data + i * DATA_PER_LEN, DATA_PER_LEN);
//		memset(crc_data, 0, CRC_LEN);
//		uint32_t crc_value = crc32_bit(packet + sizeof(req_pack_head_t), DATA_PER_LEN);
//		store_le_uint32(crc_data, crc_value);
//		std::cout << "发送数据的CRC:" << " " << crc_value << std::endl;
//		memcpy(packet + sizeof(req_pack_head_t) + DATA_PER_LEN, crc_data, CRC_LEN);
//		ret = usb_write((char*)packet /*+ i * FRAME_LEN*/, FRAME_LEN, TIMEOUT);        //一帧一帧的发，指针一直右移一帧长度
//		if (ret < 0)
//			return ESENDPACK;
//		ret = usb_read((char*)resp, FRAME_LEN, TIMEOUT);   //参数：指针位置，读取长度，超时时间//返回是读取实际长度
//		if (ret < 0)
//			return EGETSTS;
//		if (resp->head[0] != 'T' || resp->head[1] != 'S' || resp->head[2] != 'M')
//		{
//			return EGETDAT;
//		}
//		if (resp->cmd != USB_UPGRADE_ACK_BIN_OK_CMD)
//			return EGETDAT;
//
//		int rec_data_len= reverse_uint32(resp->len);
//		uint32_t rec_cal = crc32_bit((uint8_t *)resp + sizeof(resp_pack_head_t), rec_data_len);   //计算出的CRC
//		int crc_rec_value = reverse_uint32((uint8_t *)resp + sizeof(resp_pack_head_t) + rec_data_len);   //实际收到的CRC转int
//		//if (crc_rec_value == rec_cal)
//		//	return SUCCESS;
//		if(crc_rec_value != rec_cal)
//		{
//			//i--;   //重传
//			return EGETDAT;
//		}
//	}
//	uint32_t left_len = len - i * DATA_PER_LEN;     //不够一帧的纯数据的长度
//	if (left_len) {
//		packet_send(USB_UPGRADE_SEND_BIN_CMD, 0, left_len, packet);
//		memcpy(packet + sizeof(req_pack_head_t), data + i * DATA_PER_LEN, left_len);
//		memset(crc_data, 0, CRC_LEN);
//		uint32_t crc_last_value = crc32_bit(packet + sizeof(req_pack_head_t), left_len);
//		store_le_uint32(crc_data, crc_last_value);
//		memcpy(packet + sizeof(req_pack_head_t) + left_len, crc_data, CRC_LEN);
//		std::cout << "发送最后一包数据的CRC:" << " " << crc_last_value << std::endl;
//		ret = usb_write((char*)packet, left_len + sizeof(req_pack_head_t) + CRC_LEN, TIMEOUT);        //参数：指针位置，发送数据长度，超时时间 
//		if (ret < 0)
//			return ESENDPACK;
//		ret = usb_read((char*)resp, FRAME_LEN, TIMEOUT);   //参数：指针位置，读取长度，超时时间//返回是读取实际长度
//		if (ret < 0)
//			return EGETSTS;
//		if (resp->head[0] != 'T' || resp->head[1] != 'S' || resp->head[2] != 'M')
//		{
//			return EGETDAT;
//		}
//		if (resp->cmd != USB_UPGRADE_ACK_BIN_OK_CMD)
//			return EGETDAT;
//		int rec_data_len = reverse_uint32(resp->len);
//		uint32_t rec_cal = crc32_bit((uint8_t *)resp + sizeof(resp_pack_head_t), rec_data_len);   //计算出的CRC
//		int crc_rec_value = reverse_uint32((uint8_t *)resp + sizeof(resp_pack_head_t) + rec_data_len);   //实际收到的CRC转int
//		//if (crc_rec_value == rec_cal)
//		//	return SUCCESS;
//		if (crc_rec_value != rec_cal)
//		{
//			//usb_write((char*)packet, left_len + sizeof(req_pack_head_t) + CRC_LEN, TIMEOUT);  //重传
//			return EGETDAT;
//		}
//	}
//
//	return SUCCESS;
//}
std::mutex m_lock;
int get_con_acd(uint32_t id, uint8_t *send, uint8_t *recv,uint8_t send_cmd, uint8_t rec_cmd/*,int thread_id*/)
{
	
	std::lock_guard<std::mutex> locks(m_lock);
	int ret;
	uint8_t crc_packet[CRC_LEN] = { 0 };
	resp_pack_head_t *resp = (resp_pack_head_t *)recv;
	uint8_t ddd[20] = { 0 };
	static int count = 0;
	packet_send(send_cmd, id, 0, send);
	uint32_t crc_value = crc32_bit(send + sizeof(req_pack_head_t), 0);
	std::cout << "握手发送CRC:" <<" "<< crc_value << std::endl;
	store_le_uint32(crc_packet, crc_value);
	memcpy(send + sizeof(req_pack_head_t), crc_packet, CRC_LEN);
	while (1) {
		if (connect_send(send, GET_REQ_LEN(send)+CRC_LEN/*, thread_id*/) < 0)
			return ESENDSTS;
		std::cout << "握手包已经发送" << std::endl;
		ret = usb_read((char*)resp, FRAME_LEN, TIMEOUT);   //参数：指针位置，读取长度，超时时间//返回是读取实际长度
		std::cout << "收到下位机握手回复,数据接收长度为:" << " " << ret << std::endl;
		memcpy(ddd, resp, 20);
		//std::cout << "收到数据:" << " "<<std::hex << (unsigned int)(unsigned char)ddd[0] << " " << std::hex << (unsigned int)(unsigned char)ddd[1] << " " << std::hex << (unsigned int)(unsigned char)ddd[2] << " " << std::hex << (unsigned int)(unsigned char)ddd[3] << " " << std::hex << (unsigned int)(unsigned char)ddd[4] << " " << std::hex << (unsigned int)(unsigned char)ddd[5] << " " << std::hex << (unsigned int)(unsigned char)ddd[6] << " " << std::hex << (unsigned int)(unsigned char)ddd[7] << " " << std::hex << (unsigned int)(unsigned char)ddd[8] << " " << std::hex << (unsigned int)(unsigned char)ddd[9] << " " << std::hex << (unsigned int)(unsigned char)ddd[10] << " " << std::hex << (unsigned int)(unsigned char)ddd[11] << " " << std::hex << (unsigned int)(unsigned char)ddd[12] << " " << std::hex << (unsigned int)(unsigned char)ddd[13] << " " << std::hex << (unsigned int)(unsigned char)ddd[14] << " " << std::hex << (unsigned int)(unsigned char)ddd[15] << " " << std::hex << (unsigned int)(unsigned char)ddd[16] << " " << std::hex << (unsigned int)(unsigned char)ddd[17] << " " << std::hex << (unsigned int)(unsigned char)ddd[18] << " " << std::hex << (unsigned int)(unsigned char)ddd[19] << std::endl;
		if (ret < 0)
			return EGETSTS;
		if (resp->head[0] != 'T' || resp->head[1] != 'S' || resp->head[2] != 'M')
			return EGETDAT;
		std::cout << "判断TSM成功" << std::endl;
		if (resp->cmd != rec_cmd)
			return EGETDAT;
		std::cout << "判断cmd成功" << std::endl;

		int rec_data_len = reverse_uint32(resp->len);
		std::cout << "握手收到的长度:" << " " << rec_data_len << std::endl;
		uint32_t rec_cal = crc32_bit((uint8_t *)resp + sizeof(resp_pack_head_t), rec_data_len);   //计算出的CRC
		std::cout << "握手计算出的CRC:" <<" "<< rec_cal << std::endl;
		int crc_rec_value = reverse_uint32((uint8_t *)resp + sizeof(resp_pack_head_t) + rec_data_len);   //实际收到的CRC转int
		std::cout << "握手实际收到的CRC:" << " " << crc_rec_value << std::endl;
		count++;
		std::cout << "发送包数量:" <<count << std::endl;
		if (crc_rec_value == rec_cal)
			return SUCCESS;
		else
		{
			Sleep(50);
			connect_send(send, GET_REQ_LEN(send) + CRC_LEN/*,0*/);   //重传
		}

		

		//if (resp->head[0] == 'T' && resp->head[1] == 'S' && resp->head[2] == 'M')      //第一帧512包含13B的头+6B的头+数据部分；后面收到的512数据帧都是纯数据
		//{
		//	if (resp->cmd == rec_cmd)
		//	{
		//		return SUCCESS;
		//	}
		//	//if (reverse_uint32(resp->id) == 1)
		//	//	return SUCCESS;
		//	Sleep(50);  //只要图片没准备好，not_ready的话，那就继续要，但是只要我要，下位机就给，如果没图数据，就给not_ready
		//	
		//}


		/* msg route */
		MSG msg;
		while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
	}

	//if (GET_REQ_CMD(resp) == USB_UPGRADE_CONNECT_ACK_CMD) {
	//	uint8_t *dep_map = recv;
	//	uint32_t tot_len = GET_REQ_LEN(resp);        //收到第一帧数据的头里的len可以显示数据部分的总长度（下位机发的，告诉一共有多少数据），这里是加了头的总长度
	//	uint32_t valid_len = ret;                         /* first pack */

	//	tot_len -= valid_len;        //减去刚才收到的一帧长度
	//	dep_map += valid_len;        //刚刚收到一帧，这是下一帧开始的地址

	//	uint32_t recv_times = ROUND_UP_TIMES(tot_len, FRAME_LEN);   //又加上刚才的减去的一帧长度了（900）
	//	//一次读512，读很多次，全数据，用于保存图
	//	for (int i = 0; i < recv_times; i++) {
	//		ret = usb_read((char*)dep_map + i * FRAME_LEN, FRAME_LEN, TIMEOUT);   //从第二帧的地方开始存，存899次，再加上开始的一帧
	//		if (ret < 0)
	//			return EGETDAT;
	//	}
	//}
	return SUCCESS;
}

int get_rec(uint8_t *recv, uint8_t cmd,int timeout)
{
	int ret;
	uint8_t *packet;
	resp_pack_head_t *resp = (resp_pack_head_t *)recv;

	ret = usb_read((char*)resp, FRAME_LEN, timeout/*, 0*/);
	if (ret < 0)
		return EGETDAT;
	if (resp->head[0] != 'T' || resp->head[1] != 'S' || resp->head[2] != 'M')
		return EGETDAT;
	//if (reverse_uint32(resp->id) == 4)
	//	return EGETDAT;
	//if (reverse_uint32(resp->id) == 3)
	//	return SUCCESS;
	if (resp->cmd != cmd)
		return EGETDAT;

	int rec_data_len = reverse_uint32(resp->len);
	uint32_t rec_cal = crc32_bit((uint8_t *)resp + sizeof(resp_pack_head_t), rec_data_len);   //计算出的CRC
	int crc_rec_value = reverse_uint32((uint8_t *)resp + sizeof(resp_pack_head_t) + rec_data_len);   //实际收到的CRC转int
	//if (crc_rec_value == rec_cal)
	//	return SUCCESS;
	if (crc_rec_value != rec_cal)
	{
		return EGETDAT;
		//connect_send(send, GET_REQ_LEN(send) + CRC_LEN);   //重传
	}




	uint8_t *ir_img = recv;
	uint32_t tot_len = GET_RESP_LEN(resp);
	uint32_t valid_len = ret;                         /* first pack */

	tot_len -= valid_len;
	ir_img += valid_len;

	uint32_t recv_times = ROUND_UP_TIMES(tot_len, FRAME_LEN);
	for (int i = 0; i < recv_times; i++) {
		ret = usb_read((char*)ir_img + i * FRAME_LEN, FRAME_LEN, timeout/*,0*/);
		if (ret < 0)
			return EGETDAT;
	}

	return SUCCESS;
}
//小端保存
void add_bin_head(uint32_t addr, uint32_t bin_len, uint32_t tmp_res, uint8_t *data)
{
	bin_head *head = (bin_head *)data;
	head->magic[0] = 'Q';
	head->magic[1] = 'W';
	head->magic[2] = 'Z';
	head->magic[3] = 'N';

	/****************小端**********************/
	sm_store_le_uint32(head->load_addr, addr);
	sm_store_le_uint32(head->img_len, bin_len);
	sm_store_le_uint32(head->res, tmp_res);
	/*****************************************/

	/****************大端************************/
	//store_le_uint32(head->load_addr, addr);
	//store_le_uint32(head->img_len, bin_len);
	//store_le_uint32(head->res, tmp_res);
	/***************************************/
}