#include "USB_Upgrade.h"
#include "packet.h"
#include <qmessagebox.h>
#include <qfiledialog.h>
#include <iostream>
//#include <direct.h>
//#include <Tlhelp32.h>
static int packet_count = 0;
USB_Upgrade::USB_Upgrade(QWidget *parent)
    : QMainWindow(parent), current_thread(nullptr)
{
    ui.setupUi(this);
	this->setWindowTitle("USB_Upgrade  V1.23");
	this->setWindowIcon(QIcon("./Logo.png"));
	connect(this, SIGNAL(sed_progress(int)), this, SLOT(progress_bar(int)));
	connect(this, SIGNAL(sed_log_msg(QString)), this, SLOT(log_msg(QString)));
	ui.progressBar->setValue(0);
}

USB_Upgrade::~USB_Upgrade()
{
	if (current_thread != nullptr)
	{
		current_thread->join();
		delete current_thread;
		current_thread = nullptr;
	}
}


void USB_Upgrade::readIni()
{
	//terminateMYSQL();
	uint8_t addr[PARA_LEN * 7] = { 0 };
	QString strPath = "./PacketFile/monocular_lock_combine_1P5M.ini";
	QString filePath = "./PacketFile/flash_download_file.bin";
	QByteArray fileData;
	QSettings setIni(strPath,QSettings::IniFormat);
	QString offset = setIni.value("boot_para/flash offset").toString();
	QString offset_805_dtcm = setIni.value("805_dtcm/flash offset").toString();
	QString offset_804_app = setIni.value("804_app/flash offset").toString();
	QString offset_805_ddr = setIni.value("805_ddr/flash offset").toString();
	QString offset_weight = setIni.value("weight/flash offset").toString();
	QString offset_ddr_rate = setIni.value("boot_para/ddr_rate").toString();
	QString offset_flash_div = setIni.value("boot_para/flash_div").toString();
	QString offset_flash_capture_delay = setIni.value("boot_para/flash_capture_delay").toString();

	int off_boot_para = offset.toInt(nullptr, isX(offset));
	int off_805_dtcm = offset_805_dtcm.toInt(nullptr, isX(offset_805_dtcm));
	int off_804_app = offset_804_app.toInt(nullptr, isX(offset_804_app));
	int off_805_ddr = offset_805_ddr.toInt(nullptr, isX(offset_805_ddr));
	int off_weight = offset_weight.toInt(nullptr, isX(offset_weight));
	int off_ddr_rate = offset_ddr_rate.toInt(nullptr, isX(offset_ddr_rate));
	int off_flash_div = offset_flash_div.toInt(nullptr, isX(offset_flash_div));
	int off_flash_capture_delay = offset_flash_capture_delay.toInt(nullptr, isX(offset_flash_capture_delay));
	QFile file(filePath);
	if (file.open(QIODevice::ReadOnly))
	{
		fileData = file.readAll();
	}
	else
	{
		return;
	}
	file.close();
	add_table(addr, off_805_dtcm, 0);
	add_table(addr + PARA_LEN, off_804_app, 0);
	add_table(addr + PARA_LEN * 2, off_805_ddr, 0);
	add_table(addr + PARA_LEN * 3, off_weight, 0);
	add_table(addr + PARA_LEN * 4, off_ddr_rate, 0);
	add_table(addr + PARA_LEN * 5, off_flash_div, 0);
	add_table(addr + PARA_LEN * 6, off_flash_capture_delay, 0);
	memcpy(fileData.data() + off_boot_para + PARA_LEN * 4, addr, PARA_LEN * 7);
	//QString write_path = "./PacketFile/new_flash_download_file.bin";
	QFile file_write(filePath);
	if (file_write.open(QIODevice::WriteOnly))
	{
		file_write.write(fileData);
	}
	file_write.close();
}

void USB_Upgrade::runCmd()
{
	system("cd ./PacketFile&JT_combine_and_load.bat");
	//_chdir("./PacketFile");   
	//system("JT_combine_and_load.bat");
}

//ѡ��bin�ļ�
void USB_Upgrade::selected_file()
{
	if (!fileData.isEmpty())
		fileData.clear();
	QString str = QFileDialog::getOpenFileName(this, "Selected File", "", "*.bin");
	QFile file(str);
	if (!file.open(QIODevice::ReadOnly))
	{
		QMessageBox::warning(this, "Error", "Can Not Open File!", QMessageBox::Ok);
		return;
	}
	fileData = file.readAll();
	file.close();
	ui.textEdit->append(QString::fromLocal8Bit("ѡ���ļ���") + str);
}

//usb����
void USB_Upgrade::packet_connect_send()
{
	packet_count = 0;
	uint8_t con_sed[BUF_SEND_LEN] = { 0 };
	uint8_t con_rec[BUF_SEND_LEN] = { 0 };
	if (usb_initial() < 0)
	{
		QMessageBox::critical(nullptr, QString::fromLocal8Bit("Error"), QString::fromLocal8Bit("USB Init error!"), QMessageBox::Ok);
		return;
	}
	if (get_con_acd(packet_count, con_sed , con_rec, USB_UPGRADE_CONNECT_SEND_CMD,USB_UPGRADE_CONNECT_ACK_CMD) < 0)
	{
		QMessageBox::critical(nullptr, QString::fromLocal8Bit("Error"), QString::fromLocal8Bit("USB connect error!"), QMessageBox::Ok);
		usb_release();
		return;
	}
	ui.textEdit->append(QString::fromLocal8Bit("������ɣ�"));
	packet_count++;
	usb_release();
	QMessageBox::information(nullptr, QString::fromLocal8Bit("Sucess"), QString::fromLocal8Bit("USB connect Sucess!"), QMessageBox::Ok);
}

/*
packet:ÿ��512��
len:���ݲ��ֳ���
data:������
*/
int USB_Upgrade::data_packet_send(uint8_t *packet, uint32_t len, char *data, uint8_t *recv)
{
	int ret;
	int i = 0;
	//int count = 0;
	uint8_t crc_data[4] = { 0 };
	resp_pack_head_t *resp = (resp_pack_head_t *)recv;

	uint32_t send_times = ROUND_DOWN_TIMES(len, DATA_PER_LEN);      //���ݳ��ȳ���һ֡���ȣ��ó���֡
	for (i = 0; i < send_times; i++) {
		//int val = (100 * i) / (send_times + 1);
		//emit sed_progress(val);
		packet_send(USB_UPGRADE_SEND_BIN_CMD, packet_count, DATA_PER_LEN, packet);
		memcpy(packet/* + i * FRAME_LEN*/ + sizeof(req_pack_head_t), data + i * DATA_PER_LEN, DATA_PER_LEN);
		//uint32_t crc_value = crc32_bit(data + i * DATA_PER_LEN, DATA_PER_LEN);
		memset(crc_data, 0, CRC_LEN);
		uint32_t crc_value = crc32_bit(packet + sizeof(req_pack_head_t), DATA_PER_LEN);
		store_le_uint32(crc_data, crc_value);
		//std::cout << "�������ݵ�CRC:" << " " << crc_value << std::endl;
		memcpy(packet + sizeof(req_pack_head_t) + DATA_PER_LEN, crc_data, CRC_LEN);
		ret = usb_write((char*)packet /*+ i * FRAME_LEN*/, FRAME_LEN, TIMEOUT);        //һ֡һ֡�ķ���ָ��һֱ����һ֡����
		if (ret < 0)
			return ESENDPACK;
		ret = usb_read((char*)resp, FRAME_LEN, TIMEOUT);   //������ָ��λ�ã���ȡ���ȣ���ʱʱ��//�����Ƕ�ȡʵ�ʳ���
		if (ret < 0)
			return EGETSTS;
		if (resp->head[0] != 'T' || resp->head[1] != 'S' || resp->head[2] != 'M')
		{
			return EGETDAT;
		}
		if (resp->cmd != USB_UPGRADE_ACK_BIN_OK_CMD)
			return EGETDAT;

		int rec_data_len = reverse_uint32(resp->len);
		uint32_t rec_cal = crc32_bit((uint8_t *)resp + sizeof(resp_pack_head_t), rec_data_len);   //�������CRC
		int crc_rec_value = reverse_uint32((uint8_t *)resp + sizeof(resp_pack_head_t) + rec_data_len);   //ʵ���յ���CRCתint
		//if (crc_rec_value == rec_cal)
		//	return SUCCESS;
		if (crc_rec_value != rec_cal)
		{
			//i--;   //�ش�
			return EGETDAT;
		}
		packet_count++;
		//count++;
		//std::cout << "���Ͱ�����" << " " << count << std::endl;
	}
	//return SUCCESS;
	uint32_t left_len = len - i * DATA_PER_LEN;     //����һ֡�Ĵ����ݵĳ���
	if (left_len) {
		packet_send(USB_UPGRADE_SEND_BIN_CMD, packet_count, left_len, packet);
		memcpy(packet + sizeof(req_pack_head_t), data + i * DATA_PER_LEN, left_len);
		memset(crc_data, 0, CRC_LEN);
		uint32_t crc_last_value = crc32_bit(packet + sizeof(req_pack_head_t), left_len);
		store_le_uint32(crc_data, crc_last_value);
		memcpy(packet + sizeof(req_pack_head_t) + left_len, crc_data, CRC_LEN);
		//std::cout << "�������һ�����ݵ�CRC:" << " " << crc_last_value << std::endl;
		ret = usb_write((char*)packet, left_len + sizeof(req_pack_head_t) + CRC_LEN, TIMEOUT);        //������ָ��λ�ã��������ݳ��ȣ���ʱʱ�� 
		if (ret < 0)
			return ESENDPACK;
		ret = usb_read((char*)resp, FRAME_LEN, TIMEOUT);   //������ָ��λ�ã���ȡ���ȣ���ʱʱ��//�����Ƕ�ȡʵ�ʳ���
		if (ret < 0)
			return EGETSTS;
		if (resp->head[0] != 'T' || resp->head[1] != 'S' || resp->head[2] != 'M')
		{
			return EGETDAT;
		}
		if (resp->cmd != USB_UPGRADE_ACK_BIN_OK_CMD)
			return EGETDAT;
		int rec_data_len = reverse_uint32(resp->len);
		uint32_t rec_cal = crc32_bit((uint8_t *)resp + sizeof(resp_pack_head_t), rec_data_len);   //�������CRC
		int crc_rec_value = reverse_uint32((uint8_t *)resp + sizeof(resp_pack_head_t) + rec_data_len);   //ʵ���յ���CRCתint
		//if (crc_rec_value == rec_cal)
		//	return SUCCESS;
		if (crc_rec_value != rec_cal)
		{
			//usb_write((char*)packet, left_len + sizeof(req_pack_head_t) + CRC_LEN, TIMEOUT);  //�ش�
			return EGETDAT;
		}
		packet_count++;
	}
	//emit sed_progress(100);
	return SUCCESS;
}
/*
ÿ����64k�ͽ�����¼�ķ���
*/
void USB_Upgrade::test()
{
	QString str = ui.lineEdit->text();
	int add = str.toInt(NULL, 16);
	int len = fileData.size();
	uint8_t rec_data[BUF_RESERVE_LEN] = { 0 };
	uint8_t sed_data[BUF_SEND_LEN] = { 0 };
	uint8_t crc[CRC_LEN] = { 0 };
	uint8_t data_le[DATA_LEN] = { 0 };
	uint32_t send_times;
	int i = 0;

	/***********************��bin���+16�ֽڶ��봦��  *****************************/
	//uint8_t bin_head_len[BIN_HEAD_LENGTH] = { 0 };
	uint8_t *bin_head_len = (uint8_t *)malloc(BIN_HEAD_LENGTH + len + ADD_LEN);
	int add_byte = 0;
	if (ui.checkBox->isChecked())
	{
		QString str_run = ui.lineEdit_2->text();
		int add_run = str_run.toInt(NULL, 16);
		uint8_t add_16[ADD_LEN] = { 0 };
		if (len % 16)
		{
			add_byte = 16 - (len % 16);
		}
		memcpy(fileData.data() + len, add_16, add_byte);   //���add_byte������0���᲻�ᱨ��
		add_bin_head(add_run, len + add_byte, 0, bin_head_len);
		memcpy(bin_head_len + BIN_HEAD_LENGTH, fileData.data(), len + add_byte);   //���Ƶĳ��ȳ�����filedata�ĳ��ȣ��Ƿ���Ҫ��memcpy
		
		////���������Ƿ���ȷ
		//QFile ff("./compare.bin");
		//if (ff.open(QIODevice::WriteOnly))
		//{
		//	ff.write((char *)bin_head_len, len + add_byte + BIN_HEAD_LENGTH);
		//}
		//ff.close();
	}
	/******************************************************************************/

	if (ui.checkBox->isChecked())
	{
		send_times = ROUND_DOWN_TIMES(len + add_byte + BIN_HEAD_LENGTH, FIXED_BURNING_SIZE);
	}
	else
	{
		send_times = ROUND_DOWN_TIMES(len, FIXED_BURNING_SIZE);
	}
	



	if (usb_initial() < 0)
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
		//���͵�ַ��������Ϣ��
		packet_send(USB_UPGRADE_SEND_BIN_LEN_CMD, packet_count, DATA_LEN, sed_data);    //bin��len+id���ַ��data���ִ�4�ֽڳ��ȣ�
		store_le_uint32(data_le, add + i * FIXED_BURNING_SIZE);
		store_le_uint32(data_le + ADDRESS, FIXED_BURNING_SIZE);
		//std::cout << "�ļ����ȣ�" << " " << FIXED_BURNING_SIZE << std::endl;
		memcpy(sed_data + sizeof(req_pack_head_t), data_le, DATA_LEN);
		uint32_t crcValue_len = crc32_bit(sed_data + sizeof(req_pack_head_t), DATA_LEN);
		store_le_uint32(crc, crcValue_len);
		memcpy(sed_data + sizeof(req_pack_head_t) + DATA_LEN, crc, CRC_LEN);
		
		if (connect_send(sed_data, GET_REQ_LEN(sed_data) + CRC_LEN) < 0)
		{
			usb_release();
			return;
		}
		if (get_rec(rec_data, USB_UPGRADE_ACK_BIN_LEN_CMD, 1000) < 0)
		{
			usb_release();
			return;
		}
		packet_count++;
		//ui.textEdit->append(QString::fromLocal8Bit("������¼��ַ��bin�ļ�������Ϣ���..."));
		emit sed_log_msg(QString::fromLocal8Bit("������¼��ַ��bin�ļ�������Ϣ���..."));
		//��������
		//ui.textEdit->append(QString::fromLocal8Bit("��ʼ����64K����..."));
		emit sed_log_msg(QString::fromLocal8Bit("��ʼ����64K����..."));
		memset(sed_data, 0, BUF_SEND_LEN);
		memset(rec_data, 0, BUF_RESERVE_LEN);


		if (ui.checkBox->isChecked())   //���ͼ�16�ֽ�ͷ��16�ֽڶ�����bin
		{
			if (data_packet_send(sed_data, FIXED_BURNING_SIZE, (char *)bin_head_len + i * FIXED_BURNING_SIZE, rec_data) < 0)
			{
				usb_release();
				return;
			}
		}
		else              //���ʹ����bin
		{
			if (data_packet_send(sed_data, FIXED_BURNING_SIZE, fileData.data() + i * FIXED_BURNING_SIZE, rec_data) < 0)
			{
				//QMessageBox::critical(nullptr, QString::fromLocal8Bit("Error"), QString::fromLocal8Bit("USB Receive Data error!"), QMessageBox::Ok);
				usb_release();
				return;
			}
		}


		//ui.textEdit->append(QString::fromLocal8Bit("64K���ݴ������..."));
		emit sed_log_msg(QString::fromLocal8Bit("64K���ݴ������..."));
		//��¼
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
			usb_release();
			return;
		}
		//ui.textEdit->append(QString::fromLocal8Bit("��ʼ��¼..."));
		emit sed_log_msg(QString::fromLocal8Bit("��ʼ��¼..."));
		if (get_rec(rec_data, USB_UPGRADE_PROGRAMMER_OK_CMD, 10000) < 0)
		{
			//QMessageBox::critical(nullptr, QString::fromLocal8Bit("Error"), QString::fromLocal8Bit("USB Receive Start Programmer error!"), QMessageBox::Ok);
			usb_release();
			return;
		}
		//ui.textEdit->append(QString::fromLocal8Bit("��¼64K���..."));
		emit sed_log_msg(QString::fromLocal8Bit("��¼64K���..."));
		packet_count++;
		//emit sed_progress(100);
	}


	uint32_t left_len;    //����64k�Ĵ����ݵĳ���
	if (ui.checkBox->isChecked())
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
		packet_send(USB_UPGRADE_SEND_BIN_LEN_CMD, packet_count, DATA_LEN, sed_data);    //bin��len+id���ַ��data���ִ�4�ֽڳ��ȣ�
		store_le_uint32(data_le, add + i * FIXED_BURNING_SIZE);
		store_le_uint32(data_le + ADDRESS, left_len);
		//std::cout << "�ļ����ȣ�" << " " << FIXED_BURNING_SIZE << std::endl;
		memcpy(sed_data + sizeof(req_pack_head_t), data_le, DATA_LEN);
		uint32_t crcValue_len = crc32_bit(sed_data + sizeof(req_pack_head_t), DATA_LEN);
		store_le_uint32(crc, crcValue_len);
		memcpy(sed_data + sizeof(req_pack_head_t) + DATA_LEN, crc, CRC_LEN);

		if (connect_send(sed_data, GET_REQ_LEN(sed_data) + CRC_LEN) < 0)
		{
			usb_release();
			return;
		}
		if (get_rec(rec_data, USB_UPGRADE_ACK_BIN_LEN_CMD, 1000) < 0)
		{
			usb_release();
			return;
		}
		packet_count++;
		//��������
		memset(sed_data, 0, BUF_SEND_LEN);
		memset(rec_data, 0, BUF_RESERVE_LEN);



		if (ui.checkBox->isChecked())   //���ͼ�16�ֽ�ͷ��16�ֽڶ�����bin
		{
			if (data_packet_send(sed_data, left_len, (char *)bin_head_len + i * FIXED_BURNING_SIZE, rec_data) < 0)
			{
				usb_release();
				return;
			}
		}
		else
		{
			if (data_packet_send(sed_data, left_len, fileData.data() + i * FIXED_BURNING_SIZE, rec_data) < 0)
			{
				//QMessageBox::critical(nullptr, QString::fromLocal8Bit("Error"), QString::fromLocal8Bit("USB Receive Data error!"), QMessageBox::Ok);
				usb_release();
				return;
			}
		}
		
		//��¼
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
			usb_release();
			return;
		}
		//ui.textEdit->append(QString::fromLocal8Bit("��ʼ��¼..."));
		emit sed_log_msg(QString::fromLocal8Bit("��ʼ��¼..."));
		if (get_rec(rec_data, USB_UPGRADE_PROGRAMMER_OK_CMD, 10000) < 0)
		{
			//QMessageBox::critical(nullptr, QString::fromLocal8Bit("Error"), QString::fromLocal8Bit("USB Receive Start Programmer error!"), QMessageBox::Ok);
			usb_release();
			return;
		}
		//ui.textEdit->append(QString::fromLocal8Bit("��¼64K���..."));
		emit sed_log_msg(QString::fromLocal8Bit("��¼64K���..."));
		packet_count++;
		
	}
	emit sed_progress(100);
	if (bin_head_len != nullptr)
	{
		free(bin_head_len);
		bin_head_len = nullptr;
	}
	usb_release();
}

//�������������ݣ�(ȫ���洢��ddr��Ȼ�������¼�ķ���)
void USB_Upgrade::send_packet()
{
	//���ͳ��Ƚ׶�
	int len = fileData.size();
	//uint8_t *send_data = (uint8_t *)malloc(BUF_SEND_BIN);
	uint8_t rec_data[BUF_RESERVE_LEN] = { 0 };
	uint8_t sed_data[BUF_SEND_LEN] = { 0 };
	uint8_t crc[CRC_LEN] = { 0 };
	uint8_t data_le[DATA_LEN] = { 0 };
	QString str = ui.lineEdit->text();
	int add = str.toInt(NULL, 16);
	if (usb_initial() < 0)
	{
		//QMessageBox::critical(nullptr, QString::fromLocal8Bit("Error"), QString::fromLocal8Bit("USB Init error!"), QMessageBox::Ok);
		return;
	}
	packet_send(USB_UPGRADE_SEND_BIN_LEN_CMD, packet_count, DATA_LEN, sed_data);    //bin��len+id���ַ��data���ִ�4�ֽڳ��ȣ�
	store_le_uint32(data_le, add);
	store_le_uint32(data_le + ADDRESS, len);
	std::cout << "�ļ����ȣ�" << " " << len << std::endl;
	memcpy(sed_data + sizeof(req_pack_head_t), data_le, DATA_LEN);
	uint32_t crcValue_len = crc32_bit(sed_data + sizeof(req_pack_head_t), DATA_LEN);
	store_le_uint32(crc, crcValue_len);
	memcpy(sed_data + sizeof(req_pack_head_t) + DATA_LEN, crc, CRC_LEN);
	if (connect_send(sed_data, GET_REQ_LEN(sed_data) + CRC_LEN) < 0)
	{
		//QMessageBox::critical(nullptr, QString::fromLocal8Bit("Error"), QString::fromLocal8Bit("USB Data Length & Address Send error!"), QMessageBox::Ok);
		//if (send_data != nullptr) {
		//	free(send_data);
		//	send_data = nullptr;
		//}
		usb_release();
		return;
	}
	if (get_rec(rec_data, USB_UPGRADE_ACK_BIN_LEN_CMD,1000) < 0)
	{
		//QMessageBox::critical(nullptr, QString::fromLocal8Bit("Error"), QString::fromLocal8Bit("USB Receive error!"), QMessageBox::Ok);
		//if (send_data != nullptr) {
		//	free(send_data);
		//	send_data = nullptr;
		//}
		usb_release();
		return;
	}
	ui.textEdit->append(QString::fromLocal8Bit("������¼��ַ��bin�ļ�������Ϣ��ɣ�"));
	packet_count++;
	//�������ݽ׶�
	ui.textEdit->append(QString::fromLocal8Bit("��ʼ����bin�ļ���"));
	memset(sed_data, 0, BUF_SEND_LEN);
	memset(rec_data, 0, BUF_RESERVE_LEN);
	if (data_packet_send(sed_data, len, fileData.data(), rec_data) < 0)
	{
		//QMessageBox::critical(nullptr, QString::fromLocal8Bit("Error"), QString::fromLocal8Bit("USB Receive Data error!"), QMessageBox::Ok);
		usb_release();
		return;
	}
	ui.textEdit->append(QString::fromLocal8Bit("bin�ļ����ݴ�����ɣ�"));
	
	//���Ϳ�ʼ��¼
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
		usb_release();
		return;
	}
	ui.textEdit->append(QString::fromLocal8Bit("��ʼ��¼��"));
	if (get_rec(rec_data, USB_UPGRADE_PROGRAMMER_OK_CMD,-1) < 0)
	{
		//QMessageBox::critical(nullptr, QString::fromLocal8Bit("Error"), QString::fromLocal8Bit("USB Receive Start Programmer error!"), QMessageBox::Ok);
		usb_release();
		return;
	}
	ui.textEdit->append(QString::fromLocal8Bit("��¼��ɣ�"));
	packet_count++;
	//���͸�λ
	//memset(sed_data, 0, BUF_SEND_LEN);
	//memset(crc, 0, CRC_LEN);
	//memset(rec_data, 0, BUF_RESERVE_LEN);
	//if (get_con_acd(0, sed_data, rec_data, USB_UPGRADE_RESET_SEND_CMD, USB_UPGRADE_RESET_OK_CMD) < 0)
	//{
	//	QMessageBox::critical(nullptr, QString::fromLocal8Bit("Error"), QString::fromLocal8Bit("USB Receive Start Programmer error!"), QMessageBox::Ok);
	//	usb_release();
	//	return;
	//}
	usb_release();
	//QMessageBox::information(nullptr, QString::fromLocal8Bit("Sucess"), QString::fromLocal8Bit("USB upgrade Sucess!"), QMessageBox::Ok);
}
//ѡ���ļ�
void USB_Upgrade::on_pushButton_clicked()
{
	//uint8_t dds[4] = { 0xaa,0xaa,0xaa,0xaa };
	//int a = crc32_bit(dds, 4);
	//std::cout << a << std::endl;
	readIni();
	selected_file();
}
//����
void USB_Upgrade::on_pushButton_2_clicked()
{
	packet_connect_send();
}
//����
void USB_Upgrade::on_pushButton_3_clicked()
{
	//send_packet();
	startThread();
}
//��λ
void USB_Upgrade::on_pushButton_4_clicked()
{
	uint8_t rec_data[BUF_RESERVE_LEN] = { 0 };
	uint8_t sed_data[BUF_SEND_LEN] = { 0 };
	if (usb_initial() < 0)
	{
		QMessageBox::critical(nullptr, QString::fromLocal8Bit("Error"), QString::fromLocal8Bit("USB Init error!"), QMessageBox::Ok);
		return;
	}
	ui.textEdit->append(QString::fromLocal8Bit("���͸�λ��"));
	if (get_con_acd(packet_count, sed_data, rec_data, USB_UPGRADE_RESET_SEND_CMD, USB_UPGRADE_RESET_OK_CMD) < 0)
	{
		QMessageBox::critical(nullptr, QString::fromLocal8Bit("Error"), QString::fromLocal8Bit("USB Receive Reset error!"), QMessageBox::Ok);
		usb_release();
		return;
	}
	packet_count++;
	ui.textEdit->append(QString::fromLocal8Bit("��λ��ɣ�"));
	usb_release();
	QMessageBox::information(nullptr, QString::fromLocal8Bit("Sucess"), QString::fromLocal8Bit("USB Reset Sucess!"), QMessageBox::Ok);


	if (current_thread != nullptr)
	{
		current_thread->join();
		delete current_thread;
		current_thread = nullptr;
	}
}

//�ļ����
void USB_Upgrade::on_pushButton_5_clicked()
{
	runCmd();
}

void USB_Upgrade::progress_bar(int value)
{
	ui.progressBar->setValue(value);
}

void USB_Upgrade::log_msg(QString str)
{
	ui.textEdit->append(str);
}

void USB_Upgrade::startThread(/*uint8_t *packet, uint32_t len, char *data, uint8_t *recv*/)
{
	//std::thread *current_thread = new std::thread(&USB_Upgrade::send_packet, this);
	/*std::thread **/current_thread = new std::thread(&USB_Upgrade::test, this);
	//current_thread->join();
	//delete current_thread;
	//current_thread = nullptr;
}