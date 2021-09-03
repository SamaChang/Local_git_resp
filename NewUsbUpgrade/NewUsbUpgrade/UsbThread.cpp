#include "UsbThread.h"
#include <qdebug.h>
static int packet_count = 0;
static uint32_t Table2[256];
UsbThread::UsbThread(QObject *parent)
	: QObject(parent)
{
	m_thread = new QThread;
	usbControl = new UsbControl;
	this->moveToThread(m_thread);
	usbControl->moveToThread(m_thread);
	connect(m_thread, &QThread::finished, this, &QObject::deleteLater);
	usbControl->get_dev();
	m_thread->start();
}

UsbThread::~UsbThread()
{
	//int a = 0;
	//QThread::sleep(3);
	delete usbControl;
	usbControl = nullptr;
	//m_thread->quit();
	//m_thread->wait();
	//delete m_thread;
	//m_thread = nullptr;

	
}

uint32_t reverse_uint32(uint8_t *uint32_value)          /* big endian */
{
	return  uint32_value[0] << 24 |
		uint32_value[1] << 16 |
		uint32_value[2] << 8 |
		uint32_value[3];
}

void store_le_uint32(uint8_t *addr, uint32_t value)     /* big endian */
{
	addr[0] = value >> 24;
	addr[1] = (value >> 16) & 0xff;
	addr[2] = (value >> 8) & 0xff;
	addr[3] = value & 0xff;
}


uint32_t reverse_table_crc(uint8_t *data, int32_t len, uint32_t *table)
{
	uint32_t crc = 0xffffffff;
	uint8_t *p = data;
	int i;
	for (i = 0; i < len; i++) {
		crc = table[(crc ^ (*(p + i))) & 0xff] ^ (crc >> 8);
	}
	return  ~crc;
}


uint64_t reflect(uint64_t ref, uint8_t ch)
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

void gen_normal_table(uint32_t *table)
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

uint32_t crc32_bit(uint8_t *ptr, uint32_t len)
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


void packet_send(uint8_t cmd, uint32_t id, uint32_t payload_len, uint8_t *data)
{
	req_pack_head_t *req = (req_pack_head_t *)data;
	req->head[0] = 'T';
	req->head[1] = 'S';
	req->head[2] = 'M';
	req->cmd = cmd;
	store_le_uint32(req->id, id);
	store_le_uint32(req->len, payload_len);
}

int UsbThread::connect_send(uint8_t *packet, uint32_t len)
{
	int ret;
	int i = 0;
	//usb_dev_handle *handle = usbControl->handle_lists[count];
	//usb_dev_handle *handle = usbControl->usb_handle;
	uint32_t send_times = ROUND_DOWN_TIMES(len, FRAME_LEN);      //数据长度除以一帧长度，得出几帧
	for (i = 0; i < send_times; i++) {
		ret = usbControl->usb_write((char*)packet + i * FRAME_LEN, FRAME_LEN, TIMEOUT/*, handle*/);        //一帧一帧的发，指针一直右移一帧长度
		if (ret < 0)
			return ESENDPACK;
	}
	uint32_t left_len = len - i * FRAME_LEN;     //不够一帧的长度
	if (left_len) {
		ret = usbControl->usb_write((char*)packet + i * FRAME_LEN, left_len, TIMEOUT/*, handle*/);        //参数：指针位置，发送数据长度，超时时间 
		if (ret < 0)
			return ESENDPACK;
	}

	return SUCCESS;
}

int UsbThread::get_con_acd(uint32_t id, uint8_t *send, uint8_t *recv, uint8_t send_cmd, uint8_t rec_cmd)
{
	int ret;
	uint8_t crc_packet[CRC_LEN] = { 0 };
	resp_pack_head_t *resp = (resp_pack_head_t *)recv;
	uint8_t ddd[20] = { 0 };
	static int count = 0;
	packet_send(send_cmd, id, 0, send);
	uint32_t crc_value = crc32_bit(send + sizeof(req_pack_head_t), 0);
	//std::cout << "握手发送CRC:" << " " << crc_value << std::endl;
	store_le_uint32(crc_packet, crc_value);
	memcpy(send + sizeof(req_pack_head_t), crc_packet, CRC_LEN);
	while (1) {
		if (connect_send(send, GET_REQ_LEN(send) + CRC_LEN) < 0)
			return ESENDSTS;
		//std::cout << "握手包已经发送" << std::endl;
		ret = usbControl->usb_read((char*)resp, FRAME_LEN, TIMEOUT/*, thread_id*/);   //参数：指针位置，读取长度，超时时间//返回是读取实际长度
		//std::cout << "收到下位机握手回复,数据接收长度为:" << " " << ret << std::endl;
		memcpy(ddd, resp, 20);
		//std::cout << "收到数据:" << " "<<std::hex << (unsigned int)(unsigned char)ddd[0] << " " << std::hex << (unsigned int)(unsigned char)ddd[1] << " " << std::hex << (unsigned int)(unsigned char)ddd[2] << " " << std::hex << (unsigned int)(unsigned char)ddd[3] << " " << std::hex << (unsigned int)(unsigned char)ddd[4] << " " << std::hex << (unsigned int)(unsigned char)ddd[5] << " " << std::hex << (unsigned int)(unsigned char)ddd[6] << " " << std::hex << (unsigned int)(unsigned char)ddd[7] << " " << std::hex << (unsigned int)(unsigned char)ddd[8] << " " << std::hex << (unsigned int)(unsigned char)ddd[9] << " " << std::hex << (unsigned int)(unsigned char)ddd[10] << " " << std::hex << (unsigned int)(unsigned char)ddd[11] << " " << std::hex << (unsigned int)(unsigned char)ddd[12] << " " << std::hex << (unsigned int)(unsigned char)ddd[13] << " " << std::hex << (unsigned int)(unsigned char)ddd[14] << " " << std::hex << (unsigned int)(unsigned char)ddd[15] << " " << std::hex << (unsigned int)(unsigned char)ddd[16] << " " << std::hex << (unsigned int)(unsigned char)ddd[17] << " " << std::hex << (unsigned int)(unsigned char)ddd[18] << " " << std::hex << (unsigned int)(unsigned char)ddd[19] << std::endl;
		if (ret < 0)
			return EGETSTS;
		if (resp->head[0] != 'T' || resp->head[1] != 'S' || resp->head[2] != 'M')
			return EGETDAT;
		//std::cout << "判断TSM成功" << std::endl;
		if (resp->cmd != rec_cmd)
			return EGETDAT;
		//std::cout << "判断cmd成功" << std::endl;

		int rec_data_len = reverse_uint32(resp->len);
		//std::cout << "握手收到的长度:" << " " << rec_data_len << std::endl;
		uint32_t rec_cal = crc32_bit((uint8_t *)resp + sizeof(resp_pack_head_t), rec_data_len);   //计算出的CRC
		//std::cout << "握手计算出的CRC:" << " " << rec_cal << std::endl;
		int crc_rec_value = reverse_uint32((uint8_t *)resp + sizeof(resp_pack_head_t) + rec_data_len);   //实际收到的CRC转int
		//std::cout << "握手实际收到的CRC:" << " " << crc_rec_value << std::endl;
		count++;
		//std::cout << "发送包数量:" << count << std::endl;
		if (crc_rec_value == rec_cal)
			return SUCCESS;
		else
		{
			Sleep(50);
			connect_send(send, GET_REQ_LEN(send) + CRC_LEN);   //重传
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


int UsbThread::get_rec(uint8_t *recv, uint8_t cmd, int timeout)
{
	int ret;
	uint8_t *packet;
	resp_pack_head_t *resp = (resp_pack_head_t *)recv;

	ret = usbControl->usb_read((char*)resp, FRAME_LEN, timeout/*, 0*/);
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
		ret = usbControl->usb_read((char*)ir_img + i * FRAME_LEN, FRAME_LEN, timeout/*, 0*/);
		if (ret < 0)
			return EGETDAT;
	}

	return SUCCESS;
}
//握手
void UsbThread::packet_connect_send(int dev_num)
{
	packet_count = 0;
	uint8_t con_sed[BUF_SEND_LEN] = { 0 };
	uint8_t con_rec[BUF_SEND_LEN] = { 0 };
	if (usbControl->usb_initial(dev_num) < 0)
	{
		//QMessageBox::critical(nullptr, QString::fromLocal8Bit("Error"), QString::fromLocal8Bit("USB Init error!"), QMessageBox::Ok);
		return;
	}
	if (get_con_acd(0, con_sed, con_rec, USB_UPGRADE_CONNECT_SEND_CMD, USB_UPGRADE_CONNECT_ACK_CMD) < 0)
	{
		//QMessageBox::critical(nullptr, QString::fromLocal8Bit("Error"), QString::fromLocal8Bit("USB connect error!"), QMessageBox::Ok);
		usbControl->usb_release(/*dev_num*/);
		return;
	}
	qDebug() << QThread::currentThreadId() << ":" << con_rec[0]<< con_rec[1]<< con_rec[2] << con_rec[3] << con_rec[4] << con_rec[5];
	//ui.textEdit->append(QString::fromLocal8Bit("握手完成！"));
	packet_count++;
	usbControl->usb_release(/*0*/);
	//QMessageBox::information(nullptr, QString::fromLocal8Bit("Sucess"), QString::fromLocal8Bit("USB connect Sucess!"), QMessageBox::Ok);
	
	
	
	emit sed_handshake_status();
	
	//int count = 100;
	//while (count)
	//{
	//	emit get_count(count);
	//	Sleep(1000);
	//	count--;
	//}
	
}


int UsbThread::data_packet_send(uint8_t *packet, uint32_t len, char *data, uint8_t *recv,int usb_num)
{
	int ret;
	int i = 0;
	//int count = 0;
	uint8_t crc_data[4] = { 0 };
	resp_pack_head_t *resp = (resp_pack_head_t *)recv;
	//usb_dev_handle *handle = usbControl->handle_lists[usb_num];

	uint32_t send_times = ROUND_DOWN_TIMES(len, DATA_PER_LEN);      //数据长度除以一帧长度，得出几帧
	for (i = 0; i < send_times; i++) {
		//int val = (100 * i) / (send_times + 1);
		//emit sed_progress(val);
		packet_send(USB_UPGRADE_SEND_BIN_CMD, packet_count, DATA_PER_LEN, packet);
		memcpy(packet/* + i * FRAME_LEN*/ + sizeof(req_pack_head_t), data + i * DATA_PER_LEN, DATA_PER_LEN);
		//uint32_t crc_value = crc32_bit(data + i * DATA_PER_LEN, DATA_PER_LEN);
		memset(crc_data, 0, CRC_LEN);
		uint32_t crc_value = crc32_bit(packet + sizeof(req_pack_head_t), DATA_PER_LEN);
		store_le_uint32(crc_data, crc_value);
		//std::cout << "发送数据的CRC:" << " " << crc_value << std::endl;
		memcpy(packet + sizeof(req_pack_head_t) + DATA_PER_LEN, crc_data, CRC_LEN);
		ret = usbControl->usb_write((char*)packet /*+ i * FRAME_LEN*/, FRAME_LEN, TIMEOUT/*, handle*/);        //一帧一帧的发，指针一直右移一帧长度
		if (ret < 0)
			return ESENDPACK;
		ret = usbControl->usb_read((char*)resp, FRAME_LEN, TIMEOUT/*, usb_num*/);   //参数：指针位置，读取长度，超时时间//返回是读取实际长度
		if (ret < 0)
			return EGETSTS;
		if (resp->head[0] != 'T' || resp->head[1] != 'S' || resp->head[2] != 'M')
		{
			return EGETDAT;
		}
		if (resp->cmd != USB_UPGRADE_ACK_BIN_OK_CMD)
			return EGETDAT;

		int rec_data_len = reverse_uint32(resp->len);
		uint32_t rec_cal = crc32_bit((uint8_t *)resp + sizeof(resp_pack_head_t), rec_data_len);   //计算出的CRC
		int crc_rec_value = reverse_uint32((uint8_t *)resp + sizeof(resp_pack_head_t) + rec_data_len);   //实际收到的CRC转int
		//if (crc_rec_value == rec_cal)
		//	return SUCCESS;
		if (crc_rec_value != rec_cal)
		{
			//i--;   //重传
			return EGETDAT;
		}
		packet_count++;
		//count++;
		//std::cout << "发送包数：" << " " << count << std::endl;
	}
	//return SUCCESS;
	uint32_t left_len = len - i * DATA_PER_LEN;     //不够一帧的纯数据的长度
	if (left_len) {
		packet_send(USB_UPGRADE_SEND_BIN_CMD, packet_count, left_len, packet);
		memcpy(packet + sizeof(req_pack_head_t), data + i * DATA_PER_LEN, left_len);
		memset(crc_data, 0, CRC_LEN);
		uint32_t crc_last_value = crc32_bit(packet + sizeof(req_pack_head_t), left_len);
		store_le_uint32(crc_data, crc_last_value);
		memcpy(packet + sizeof(req_pack_head_t) + left_len, crc_data, CRC_LEN);
		//std::cout << "发送最后一包数据的CRC:" << " " << crc_last_value << std::endl;
		ret = usbControl->usb_write((char*)packet, left_len + sizeof(req_pack_head_t) + CRC_LEN, TIMEOUT/*, handle*/);        //参数：指针位置，发送数据长度，超时时间 
		if (ret < 0)
			return ESENDPACK;
		ret = usbControl->usb_read((char*)resp, FRAME_LEN, TIMEOUT/*, usb_num*/);   //参数：指针位置，读取长度，超时时间//返回是读取实际长度
		if (ret < 0)
			return EGETSTS;
		if (resp->head[0] != 'T' || resp->head[1] != 'S' || resp->head[2] != 'M')
		{
			return EGETDAT;
		}
		if (resp->cmd != USB_UPGRADE_ACK_BIN_OK_CMD)
			return EGETDAT;
		int rec_data_len = reverse_uint32(resp->len);
		uint32_t rec_cal = crc32_bit((uint8_t *)resp + sizeof(resp_pack_head_t), rec_data_len);   //计算出的CRC
		int crc_rec_value = reverse_uint32((uint8_t *)resp + sizeof(resp_pack_head_t) + rec_data_len);   //实际收到的CRC转int
		//if (crc_rec_value == rec_cal)
		//	return SUCCESS;
		if (crc_rec_value != rec_cal)
		{
			//usb_write((char*)packet, left_len + sizeof(req_pack_head_t) + CRC_LEN, TIMEOUT);  //重传
			return EGETDAT;
		}
		packet_count++;
	}
	//emit sed_progress(100);
	return SUCCESS;
}
Common common;
void UsbThread::runUpgrade(int dev_num, int add,int len,bool check, int add_run, char *data_ptr)
{
	//QString str = ui.lineEdit->text();
	//int add = str.toInt(NULL, 16);
	//int len = fileData.size();
	uint8_t rec_data[BUF_RESERVE_LEN] = { 0 };
	uint8_t sed_data[BUF_SEND_LEN] = { 0 };
	uint8_t crc[CRC_LEN] = { 0 };
	uint8_t data_le[DATA_LEN] = { 0 };
	uint32_t send_times;
	int i = 0;

	/***********************裸bin打包+16字节对齐处理  *****************************/
	//uint8_t bin_head_len[BIN_HEAD_LENGTH] = { 0 };
	uint8_t *bin_head_len = (uint8_t *)malloc(BIN_HEAD_LENGTH + len + ADD_LEN);
	int add_byte = 0;
	if (check)
	{
		//QString str_run = ui.lineEdit_2->text();
		//int add_run = str_run.toInt(NULL, 16);
		uint8_t add_16[ADD_LEN] = { 0 };
		if (len % 16)
		{
			add_byte = 16 - (len % 16);
		}
		memcpy(/*fileData.data()*/data_ptr + len, add_16, add_byte);   //如果add_byte长度是0，会不会报错？
		common.add_bin_head(add_run, len + add_byte, 0, bin_head_len);
		memcpy(bin_head_len + BIN_HEAD_LENGTH, /*fileData.data()*/data_ptr, len + add_byte);   //复制的长度超过了filedata的长度，是否需要再memcpy

		////测试数据是否正确
		//QFile ff("./compare.bin");
		//if (ff.open(QIODevice::WriteOnly))
		//{
		//	ff.write((char *)bin_head_len, len + add_byte + BIN_HEAD_LENGTH);
		//}
		//ff.close();
	}
	/******************************************************************************/

	if (check)
	{
		send_times = ROUND_DOWN_TIMES(len + add_byte + BIN_HEAD_LENGTH, FIXED_BURNING_SIZE);
	}
	else
	{
		send_times = ROUND_DOWN_TIMES(len, FIXED_BURNING_SIZE);
	}




	if (usbControl->usb_initial(dev_num) < 0)
	{
		//QMessageBox::critical(nullptr, QString::fromLocal8Bit("Error"), QString::fromLocal8Bit("USB Init error!"), QMessageBox::Ok);
		return;
	}
	for (i = 0; i < send_times; i++)
	{
		int val = (100 * i) / (send_times);
		emit sed_progress(val);

		memset(sed_data, 0, BUF_SEND_LEN);
		memset(crc, 0, CRC_LEN);
		memset(rec_data, 0, BUF_RESERVE_LEN);
		memset(data_le, 0, DATA_LEN);
		//发送地址和数据信息包
		packet_send(USB_UPGRADE_SEND_BIN_LEN_CMD, packet_count, DATA_LEN, sed_data);    //bin的len+id存地址（data部分存4字节长度）
		store_le_uint32(data_le, add + i * FIXED_BURNING_SIZE);
		store_le_uint32(data_le + ADDRESS, FIXED_BURNING_SIZE);
		//std::cout << "文件长度：" << " " << FIXED_BURNING_SIZE << std::endl;
		memcpy(sed_data + sizeof(req_pack_head_t), data_le, DATA_LEN);
		uint32_t crcValue_len = crc32_bit(sed_data + sizeof(req_pack_head_t), DATA_LEN);
		store_le_uint32(crc, crcValue_len);
		memcpy(sed_data + sizeof(req_pack_head_t) + DATA_LEN, crc, CRC_LEN);

		if (connect_send(sed_data, GET_REQ_LEN(sed_data) + CRC_LEN) < 0)
		{
			usbControl->usb_release();
			return;
		}
		if (get_rec(rec_data, USB_UPGRADE_ACK_BIN_LEN_CMD, 1000) < 0)
		{
			usbControl->usb_release();
			return;
		}
		packet_count++;
		//ui.textEdit->append(QString::fromLocal8Bit("发送烧录地址和bin文件长度信息完成..."));
		//emit sed_log_msg(QString::fromLocal8Bit("发送烧录地址和bin文件长度信息完成..."));
		//发送数据
		//ui.textEdit->append(QString::fromLocal8Bit("开始传输64K数据..."));
		//emit sed_log_msg(QString::fromLocal8Bit("开始传输64K数据..."));
		memset(sed_data, 0, BUF_SEND_LEN);
		memset(rec_data, 0, BUF_RESERVE_LEN);


		if (check)   //发送加16字节头和16字节对齐后的bin
		{
			if (data_packet_send(sed_data, FIXED_BURNING_SIZE, (char *)bin_head_len + i * FIXED_BURNING_SIZE, rec_data, dev_num) < 0)
			{
				usbControl->usb_release();
				return;
			}
		}
		else              //发送打包的bin
		{
			if (data_packet_send(sed_data, FIXED_BURNING_SIZE, /*fileData.data()*/data_ptr + i * FIXED_BURNING_SIZE, rec_data, dev_num) < 0)
			{
				//QMessageBox::critical(nullptr, QString::fromLocal8Bit("Error"), QString::fromLocal8Bit("USB Receive Data error!"), QMessageBox::Ok);
				usbControl->usb_release();
				return;
			}
		}


		//ui.textEdit->append(QString::fromLocal8Bit("64K数据传输完成..."));
		//emit sed_log_msg(QString::fromLocal8Bit("64K数据传输完成..."));
		//烧录
		memset(sed_data, 0, BUF_SEND_LEN);
		memset(crc, 0, CRC_LEN);
		memset(rec_data, 0, BUF_RESERVE_LEN);
		packet_send(USB_UPGRADE_PROGRAMMER_BIN_CMD, packet_count, 0, sed_data);
		uint32_t crcValue_len_bin = crc32_bit(sed_data + sizeof(req_pack_head_t), 0);
		store_le_uint32(crc, crcValue_len_bin);
		memcpy(sed_data + sizeof(req_pack_head_t), crc, CRC_LEN);
		if (connect_send(sed_data, GET_REQ_LEN(sed_data) + CRC_LEN) < 0)
		{
			//QMessageBox::critical(nullptr, QString::fromLocal8Bit("Error"), QString::fromLocal8Bit("USB Send Start Programmer error!"), QMessageBox::Ok);
			usbControl->usb_release();
			return;
		}
		//ui.textEdit->append(QString::fromLocal8Bit("开始烧录..."));
		//emit sed_log_msg(QString::fromLocal8Bit("开始烧录..."));
		if (get_rec(rec_data, USB_UPGRADE_PROGRAMMER_OK_CMD, 10000) < 0)
		{
			//QMessageBox::critical(nullptr, QString::fromLocal8Bit("Error"), QString::fromLocal8Bit("USB Receive Start Programmer error!"), QMessageBox::Ok);
			usbControl->usb_release();
			return;
		}
		//ui.textEdit->append(QString::fromLocal8Bit("烧录64K完成..."));
		//emit sed_log_msg(QString::fromLocal8Bit("烧录64K完成..."));
		packet_count++;
		//emit sed_progress(100);
	}


	uint32_t left_len;    //不够64k的纯数据的长度
	if (check)
	{
		left_len = (len + add_byte + BIN_HEAD_LENGTH) - i * FIXED_BURNING_SIZE;
	}
	else
	{
		left_len = len - i * FIXED_BURNING_SIZE;
	}



	if (left_len)
	{
		memset(sed_data, 0, BUF_SEND_LEN);
		memset(crc, 0, CRC_LEN);
		memset(rec_data, 0, BUF_RESERVE_LEN);
		memset(data_le, 0, DATA_LEN);
		packet_send(USB_UPGRADE_SEND_BIN_LEN_CMD, packet_count, DATA_LEN, sed_data);    //bin的len+id存地址（data部分存4字节长度）
		store_le_uint32(data_le, add + i * FIXED_BURNING_SIZE);
		store_le_uint32(data_le + ADDRESS, left_len);
		//std::cout << "文件长度：" << " " << FIXED_BURNING_SIZE << std::endl;
		memcpy(sed_data + sizeof(req_pack_head_t), data_le, DATA_LEN);
		uint32_t crcValue_len = crc32_bit(sed_data + sizeof(req_pack_head_t), DATA_LEN);
		store_le_uint32(crc, crcValue_len);
		memcpy(sed_data + sizeof(req_pack_head_t) + DATA_LEN, crc, CRC_LEN);

		if (connect_send(sed_data, GET_REQ_LEN(sed_data) + CRC_LEN) < 0)
		{
			usbControl->usb_release();
			return;
		}
		if (get_rec(rec_data, USB_UPGRADE_ACK_BIN_LEN_CMD, 1000) < 0)
		{
			usbControl->usb_release();
			return;
		}
		packet_count++;
		//发送数据
		memset(sed_data, 0, BUF_SEND_LEN);
		memset(rec_data, 0, BUF_RESERVE_LEN);



		if (check)   //发送加16字节头和16字节对齐后的bin
		{
			if (data_packet_send(sed_data, left_len, (char *)bin_head_len + i * FIXED_BURNING_SIZE, rec_data, dev_num) < 0)
			{
				usbControl->usb_release();
				return;
			}
		}
		else
		{
			if (data_packet_send(sed_data, left_len, /*fileData.data()*/data_ptr + i * FIXED_BURNING_SIZE, rec_data, dev_num) < 0)
			{
				//QMessageBox::critical(nullptr, QString::fromLocal8Bit("Error"), QString::fromLocal8Bit("USB Receive Data error!"), QMessageBox::Ok);
				usbControl->usb_release();
				return;
			}
		}

		//烧录
		memset(sed_data, 0, BUF_SEND_LEN);
		memset(crc, 0, CRC_LEN);
		memset(rec_data, 0, BUF_RESERVE_LEN);
		packet_send(USB_UPGRADE_PROGRAMMER_BIN_CMD, packet_count, 0, sed_data);
		uint32_t crcValue_len_bin = crc32_bit(sed_data + sizeof(req_pack_head_t), 0);
		store_le_uint32(crc, crcValue_len_bin);
		memcpy(sed_data + sizeof(req_pack_head_t), crc, CRC_LEN);
		if (connect_send(sed_data, GET_REQ_LEN(sed_data) + CRC_LEN) < 0)
		{
			//QMessageBox::critical(nullptr, QString::fromLocal8Bit("Error"), QString::fromLocal8Bit("USB Send Start Programmer error!"), QMessageBox::Ok);
			usbControl->usb_release();
			return;
		}
		//ui.textEdit->append(QString::fromLocal8Bit("开始烧录..."));
		//emit sed_log_msg(QString::fromLocal8Bit("开始烧录..."));
		if (get_rec(rec_data, USB_UPGRADE_PROGRAMMER_OK_CMD, 10000) < 0)
		{
			//QMessageBox::critical(nullptr, QString::fromLocal8Bit("Error"), QString::fromLocal8Bit("USB Receive Start Programmer error!"), QMessageBox::Ok);
			usbControl->usb_release();
			return;
		}
		//ui.textEdit->append(QString::fromLocal8Bit("烧录64K完成..."));
		//emit sed_log_msg(QString::fromLocal8Bit("烧录64K完成..."));
		packet_count++;

	}
	emit sed_progress(100);
	if (bin_head_len != nullptr)
	{
		free(bin_head_len);
		bin_head_len = nullptr;
	}
	usbControl->usb_release();
	emit sed_run_flash_status();
}

void UsbThread::reset_usb_flash(int dev_num)
{
	uint8_t rec_data[BUF_RESERVE_LEN] = { 0 };
	uint8_t sed_data[BUF_SEND_LEN] = { 0 };
	if (usbControl->usb_initial(dev_num) < 0)
	{
		//QMessageBox::critical(nullptr, QString::fromLocal8Bit("Error"), QString::fromLocal8Bit("USB Init error!"), QMessageBox::Ok);
		return;
	}
	//ui.textEdit->append(QString::fromLocal8Bit("发送复位！"));
	if (get_con_acd(packet_count, sed_data, rec_data, USB_UPGRADE_RESET_SEND_CMD, USB_UPGRADE_RESET_OK_CMD) < 0)
	{
		//QMessageBox::critical(nullptr, QString::fromLocal8Bit("Error"), QString::fromLocal8Bit("USB Receive Reset error!"), QMessageBox::Ok);
		usbControl->usb_release();
		return;
	}
	packet_count++;
	//ui.textEdit->append(QString::fromLocal8Bit("复位完成！"));
	usbControl->usb_release();
	//QMessageBox::information(nullptr, QString::fromLocal8Bit("Sucess"), QString::fromLocal8Bit("USB Reset Sucess!"), QMessageBox::Ok);
	emit sed_reset_status();
	emit delete_thread();
}