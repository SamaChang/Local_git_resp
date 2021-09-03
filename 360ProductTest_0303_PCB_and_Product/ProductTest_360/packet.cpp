#include "packet.h"
//#include "pic_deal.h"
#include "usb.h"
#include "common.h"
#include "def.h"
#include "SNInformation.h"

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

void pcak_360_eth_mac(uint8_t one, uint8_t two, uint8_t three, uint8_t four, uint8_t five, uint8_t six,/*uint8_t *packet*/Eth_mac *eth)
{
	//Eth_mac *eth = (Eth_mac *)packet;
	eth->One = one;
	eth->Two = two;
	eth->Three = three;
	eth->Four = four;
	eth->Five = five;
	eth->Six = six;
}
void pack_360_bt_mac(uint8_t one, uint8_t two, uint8_t three, uint8_t four, uint8_t five, uint8_t six, /*uint8_t *packet*/Bt_mac *bt)
{
	//Bt_mac *bt = (Bt_mac *)packet;
	bt->One = one;
	bt->Two = two;
	bt->Three = three;
	bt->Four = four;
	bt->Five = five;
	bt->Six = six;
}
void pack_360_wifi_mac(uint8_t one, uint8_t two, uint8_t three, uint8_t four, uint8_t five, uint8_t six, /*uint8_t *packet*/Wifi_mac *wifi)
{
	//Wifi_mac *wifi = (Wifi_mac *)packet;
	wifi->One = one;
	wifi->Two = two;
	wifi->Three = three;
	wifi->Four = four;
	wifi->Five = five;
	wifi->Six = six;
}
void pack_360_hwid(uint8_t one, uint8_t two, uint8_t three, /*uint8_t *packet*/Hwid *hwid)
{
	//Hwid *hwid = (Hwid *)packet;
	hwid->One = one;
	hwid->Two = two;
	hwid->Three = three;
}

void pack_360_SN(uint8_t proName, uint8_t factory, uint8_t reserved, uint8_t version, uint32_t date, uint32_t prductNum ,/*uint8_t *packet*/SN_360 *req)
{
	//SN_360 *req = (SN_360 *)packet;
	//SN_360 req;
	req->company[0] = 'S';
	req->company[1] = 'T';
	req->proName = proName;
	req->factory = factory;
	req->reserved = reserved;
	req->version = version;
	store_le_uint32(req->date, date);
	store_le_uint32(req->prductNum, prductNum);
}
//360写信息
void pack_360_Info(uint8_t *packet, uint8_t switchs, uint8_t hwboardid, unsigned int deviceType, SN_360 sn, Hwid hwid,Wifi_mac wifi, Bt_mac bt, Eth_mac eth)
{
	product_info *req = (product_info *)packet;
	req->sn = sn;
	req->hwid = hwid;
	req->switchs = switchs;
	req->hwboardid = hwboardid;
	req->deviceType = deviceType;
	req->wifi_mac = wifi;
	req->bt_mac = bt;
	req->eth_mac = eth;
}

void match_sn_mac(uint8_t *mac_w,uint8_t *mac_b,uint8_t *mac_e)
{
	QByteArray ba = snInf.toLatin1();
	//uint8_t devNum[4] = { ba.at(10) & 0xf,ba.at(11) & 0xf,ba.at(12) & 0xf,ba.at(13) & 0xf};
	uint8_t devNum[4] = { ba.at(10),ba.at(11),ba.at(12),ba.at(13)};
	//uint8_t dd = ba.at(13) & 0xf;  //char字符去''
	int base = atoi((char *)devNum);   //char转int
	uint16_t mac_wifi = 3 * (base - 1) + 0x39a3;
	store_le_uint16(mac_w, mac_wifi);
	uint16_t mac_bt = 3 * (base - 1) + 0x39a4;
	store_le_uint16(mac_b, mac_bt);
	uint16_t mac_eth = 3 * (base - 1) + 0x39a5;
	store_le_uint16(mac_e, mac_eth);
}


void buttonStyle(QPushButton *button,QString path)
{
	QFile styleFile(path);
	styleFile.open(QFile::ReadOnly);
	QString setQSS(styleFile.readAll());
	button->setStyleSheet(setQSS);
}

void checkStyle(QCheckBox *box, QString path)
{
	QFile styleFile(path);
	styleFile.open(QFile::ReadOnly);
	QString setQSS(styleFile.readAll());
	box->setStyleSheet(setQSS);
}

float pack360_A(uint8_t *packet)
{
	rec_360Data *data = (rec_360Data *)packet;
	return data->A;
}

//360
void pcak360_buffer(uint8_t *packet, uint8_t cmd)
{
	calibration_param *par = (calibration_param *)packet;
	par->cmd = cmd;
}

//默认发送参数
void defaultParam(uint8_t *packet)
{
	calibration_param *par = (calibration_param *)packet;
	par->cmd = CMD_OFI_CALC_DEFAULT;
}

//计算后的参数
void calcIrPam(uint8_t *packet, double calValue)
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
void pack_sn(uint8_t *packet, uint32_t snNum, uint8_t offset)
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

void pack360_head(uint8_t cmd, uint32_t payload_len, uint8_t *packet)
{
	send_360Protocol *send = (send_360Protocol *)packet;
	send->head[0] = 'T';
	send->head[1] = 'S';
	send->head[2] = 'M';
	send->cmd = cmd;
	store_le_uint32(send->len, payload_len);
}

//int cal_pamra(uint8_t *packet, uint32_t len)
//{
//
//}

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
	//resp_pack_head_t *resp = (resp_pack_head_t *)recv;
	rec_360Protocol *resp = (rec_360Protocol *)recv;

	//pack_head(CMD_GET_RESULT, id, 0, send);
	pack360_head(CMD_GET_RESULT, 0, send);
	while (1) {
		if (send_packet(send, GET_360_SEND_LEN(send)) < 0)
			return ESENDSTS;
		ret = usb_read((char*)resp, FRAME_LEN, TIMEOUT);
		if (ret < 0)
			return EGETSTS;
		if (resp->head[0] == 'T' && resp->head[1] == 'S' && resp->head[2] == 'M'
			&& GET_360_REC_RESULT(resp) != RESULT_NOT_READY)
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

void saveLog(const QString &SN, const QString &item, const QString &isPass)
{
	QDateTime da_time;
	QString time_str = da_time.currentDateTime().toString("yyyy-MM-dd HH-mm-ss");
	QDir *DataFile = new QDir;    //创建文件路径（创建一个文件夹）
	bool exist = DataFile->exists("D:/LogFile_PCB");
	if (!exist)
	{
		bool isok = DataFile->mkdir("D:/LogFile_PCB"); // 新建文件夹
		if (!isok)
			QMessageBox::warning(nullptr, "sdf", "can't mkdir", QMessageBox::Ok);
	}
	//QString fileName = "D:/LogFile_PCB/"/* + time_str + */"log.txt";
	QString fileName = "D:/LogFile_PCB/" + SN + ".txt";
	QFile file(fileName);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
	{
		QMessageBox::warning(nullptr, "sdf", "can't open", QMessageBox::Ok);
	}
	QTextStream stream(&file);
	stream << time_str + "\t\t\t" + item + "\t\t" + isPass << "\n";
	file.close();
}
//问题：最后的result无法统计。解决办法：测试时，如果有FAIL的，直接在writeCSV函数记录result为FALI.
void writeCSV(QString SN,QString testPerson, QString result,QString number,QString currentTime,QString testName,QString unit,QString minValue ,QString maxValue,QString testValue,QString noGood)
{
	////QDateTime da_time;
	////QString time_str = da_time.currentDateTime().toString("yyyyMMddHHmmss");
	//QDir *DataFile = new QDir;    //创建文件路径（创建一个文件夹）
	//bool exist = DataFile->exists("D:/LogFile_PCB");
	//if (!exist)
	//{
	//	bool isok = DataFile->mkdir("D:/LogFile_PCB"); // 新建文件夹
	//	if (!isok)
	//		QMessageBox::warning(nullptr, "sdf", "can't mkdir", QMessageBox::Ok);
	//}
	////QString fileName = "D:/LogFile_PCB/"/* + time_str + */"log.txt";
	////QString SN = "SJ51AE20440001";
	////QString result = "PASS";
	QString fileName = "D:/LogFile_PCB/" + dateTimeFileName + "-" + SN + ".csv";
	QFile file(fileName);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))   //不加QIODevice::Append就擦除之前的内容，覆盖掉，如果加上就继续往下写
	{
		QMessageBox::warning(nullptr, "sdf", "can't open", QMessageBox::Ok);
	}
	QTextStream stream(&file);
	////stream << time_str + "\t\t\t" + item + "\t\t" + isPass << "\n";
	//stream << "SN:" << "," << SN << "\n";
	//stream << QString::fromLocal8Bit("测试结果:") << "," << result << "\n";
	//stream << QString::fromLocal8Bit("序号") << "," << QString::fromLocal8Bit("测试员") << "," << QString::fromLocal8Bit("测试时间") << "," << QString::fromLocal8Bit("测试项目")
	//	<< "," << QString::fromLocal8Bit("单位") << "," << QString::fromLocal8Bit("最小值") << "," << QString::fromLocal8Bit("最大值") << "," << QString::fromLocal8Bit("测试值")
	//	<< "," << QString::fromLocal8Bit("不良现象") << "," << QString::fromLocal8Bit("单项测试状态") << "\n";
	stream << number << "," << testPerson << "," << currentTime << "," << testName << "," << unit << "," << minValue << "," << maxValue << "," << testValue << "," << noGood << "," << result << "\n";
	file.close();
}

void recordResult(QString result)
{
	QDir *DataFile = new QDir;    //创建文件路径（创建一个文件夹）
	bool exist = DataFile->exists("D:/LogFile_PCB");
	if (!exist)
	{
		bool isok = DataFile->mkdir("D:/LogFile_PCB"); // 新建文件夹
		if (!isok)
			QMessageBox::warning(nullptr, "sdf", "can't mkdir", QMessageBox::Ok);
	}
	QString fileName = "D:/LogFile_PCB/" + dateTimeFileName + "-" + snInf + ".csv";
	QFile file(fileName);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))    //不加QIODevice::Append就擦除之前的内容，覆盖掉，如果加上就继续往下写（固定不变的格式，应该不用Append了吧，如果误点两次就创建两个表头了）
	{
		QMessageBox::warning(nullptr, "sdf", "can't open", QMessageBox::Ok);
	}
	QTextStream stream(&file);
	//stream.seek(19);  //sn长度决定了移动位置
	stream.seek(29);
	stream << "," << result << "\n";
}