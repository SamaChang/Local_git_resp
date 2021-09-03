#include "BCTC.h"
#include <qicon.h>
//#include <qserialport.h>
#include <qmessagebox.h>
#include <qfile.h>
#include <qdir.h>
#include <qdatetime.h>
#include <qeventloop.h>


BCTC::BCTC(QWidget *parent)
    : QWidget(parent),serial(new SerialPort)
{
    ui.setupUi(this);
	this->setWindowIcon(QIcon("./Logo.png"));
	this->setWindowTitle("BCTC V1.3");
	ui.pushButton->setVisible(false);
	initSerialPortList();
	QStringList list = serial->getPortNameList();
	ui.comboBox->addItems(list);
	ui.comboBox_6->addItems(list);
	//SerialPort *serial = new SerialPort();
	//serial->send_serial_data();
	//seri_cmd_send_data();
	connect(this, SIGNAL(start_write_file(unsigned char *, short, ushort, ushort, int)), this, SLOT(write_file(unsigned char *, short, ushort, ushort, int)));
	connect(serial, SIGNAL(usb_send(bool)), this, SLOT(usb_send_fun(bool)));
	connect(ui.comboBox_6, SIGNAL(sed_list(QStringList)), this, SLOT(update_port_list(QStringList)));
}

BCTC::~BCTC()
{
	//if (serial != nullptr)
	//{
	//	delete serial;
	//	serial = nullptr;
	//}
	delete serial;
	serial = nullptr;
}

void BCTC::update_port_list(QStringList list)
{
	ui.comboBox->clear();
	ui.comboBox_6->clear();
	ui.comboBox->addItems(list);
	ui.comboBox_6->addItems(list);
}

void BCTC::initSerialPortList()
{
	QStringList list;
	QStringList list_1;
	QStringList list_2;
	QStringList list_3;
	list << "56000" << "115200" << "128000" << "921600";
	ui.comboBox_2->addItems(list);
	ui.comboBox_2->setCurrentIndex(1);
	list_1 << "NONE" << "ODD" << "EVEN" << "MARK" << "SPACE";
	ui.comboBox_3->addItems(list_1);;
	list_2 << "5" << "6" << "7" << "8";
	ui.comboBox_4->addItems(list_2);
	ui.comboBox_4->setCurrentIndex(3);
	list_3 << "1" << "1.5" << "2";
	ui.comboBox_5->addItems(list_3);
}

void BCTC::creatFilePath(QString fileName)
{
	QDir dir;
	if (!dir.exists(fileName))
	{
		dir.mkdir(fileName);
	}
}

void BCTC::usb_connect_data(std::vector<char> result,bool flag)
{	
	unsigned char send_data[BUF_SEND_LEN] = { 0 };
	unsigned char *rec_data = (unsigned char *)malloc(20 * 1024 * 1024);
	unsigned char *live = nullptr;
	unsigned char *live_face = nullptr;
	unsigned char *live_ir = nullptr;     //如果模组支持ir
	unsigned char *live_all_dep = nullptr;   //如果模组支持深度
	unsigned int offset = sizeof(resp_pack_head_t) + sizeof(pic_payload_t);
	if (usb_initial() < 0)
	{
		QMessageBox::warning(nullptr, QString::fromLocal8Bit("Error"), QString::fromLocal8Bit("USB Init error!"), QMessageBox::Ok);
		return;
	}
	UsbConnect usb;
	pack_head(BCTC_CMD, 0, result.size(), send_data);
	memcpy(send_data + sizeof(req_pack_head_t), result.data(), result.size());
   //不管活体还是假体，最多4张图，活体2张（不管ir还是rgb）,全部活体（ir和dep）
	live = rec_data;
	live_face = live + BUF_RECV_IR_SPK_DEPTH;
	live_ir = live_face + BUF_RECV_IR_SPK_DEPTH;
	live_all_dep = live_ir + BUF_RECV_IR_SPK_DEPTH;
	if (usb.send_usb_data(send_data, GET_REQ_LEN(send_data)) < 0)
	{
		QMessageBox::warning(nullptr, "Error", "USB Send Error!", QMessageBox::Ok);
		return;
	}
	if (usb.rec_usb_data(0, send_data, live) < 0)
	{
		QMessageBox::warning(nullptr, QString::fromLocal8Bit("Error"), QString::fromLocal8Bit("USB Receive error!"), QMessageBox::Ok);
		if (rec_data != nullptr) {
			free(rec_data);
			rec_data = nullptr;
		}
		usb_release();
		return;
	}
	//unsigned char *ee = live + sizeof(resp_pack_head_t);
	//unsigned char channel_1 = GET_PIC_CHANNEL(ee);
	//uint8_t jia[100] = { 0 };
	//memcpy(jia, live, 100);
	short channel_1 = GET_PIC_CHANNEL(live + sizeof(resp_pack_head_t));
	ushort height_1 = GET_PIC_HEIGHT(live + sizeof(resp_pack_head_t));
	ushort width_1 = GET_PIC_WIDTH(live + sizeof(resp_pack_head_t));
	int pic_id_1 = GET_ID(live);
	emit start_write_file(live, channel_1, height_1, width_1, pic_id_1);
	std::cout << "pic_1:" << "channel_1:" << channel_1 << " " << "height_1:" << height_1 << " " << "width_1:" << width_1 << std::endl;
	if (channel_1 == PROSTHESIS)
		ui.textEdit->setText(QString::fromLocal8Bit("活体检测失败"));
	else
	{
		ui.textEdit->setText(QString::fromLocal8Bit("活体检测成功"));
	}
	if (usb.get_ir_image(live_face) < 0)
	{
		//QMessageBox::information(nullptr, QString::fromLocal8Bit("Sucessful"), QString::fromLocal8Bit("Completed！"), QMessageBox::Ok);
		if (rec_data != nullptr) {
			free(rec_data);
			rec_data = nullptr;
		}
		usb_release();
		return;
	}
	//uint8_t stru[100] = { 0 };
	//memcpy(stru, live_face, 100);
	short channel_2 = GET_PIC_CHANNEL(live_face + sizeof(resp_pack_head_t));
	ushort height_2 = GET_PIC_HEIGHT(live_face + sizeof(resp_pack_head_t));
	ushort width_2 = GET_PIC_WIDTH(live_face + sizeof(resp_pack_head_t));
	int pic_id_2 = GET_ID(live_face);
	emit start_write_file(live_face, channel_2, height_2, width_2, pic_id_2);
	std::cout << "pic_2:" << "channel_2:" << channel_2 << " " << "height_2:" << height_2 << " " << "width_2:" << width_2 << std::endl;
	if (usb.get_ir_image(live_ir) < 0)
	{
		//QMessageBox::information(nullptr, QString::fromLocal8Bit("Sucessful"), QString::fromLocal8Bit("Completed！"), QMessageBox::Ok);
		if (rec_data != nullptr) {
			free(rec_data);
			rec_data = nullptr;
		}
		usb_release();
		return;
	}
	short channel_3 = GET_PIC_CHANNEL(live_ir + sizeof(resp_pack_head_t));
	ushort height_3 = GET_PIC_HEIGHT(live_ir + sizeof(resp_pack_head_t));
	ushort width_3 = GET_PIC_WIDTH(live_ir + sizeof(resp_pack_head_t));
	int pic_id_3 = GET_ID(live_ir);
	emit start_write_file(live_ir, channel_3, height_3, width_3, pic_id_3);
	std::cout << "pic_3:" << "channel_3:" << channel_3 << " " << "height_3:" << height_3 << " " << "width_3:" << width_3 << std::endl;
	if (usb.get_ir_image(live_all_dep) < 0)
	{
		//QMessageBox::information(nullptr, QString::fromLocal8Bit("Sucessful"), QString::fromLocal8Bit("Completed！"), QMessageBox::Ok);
		if (rec_data != nullptr) {
			free(rec_data);
			rec_data = nullptr;
		}
		usb_release();
		return;
	}
	short channel_4 = GET_PIC_CHANNEL(live_all_dep + sizeof(resp_pack_head_t));
	ushort height_4 = GET_PIC_HEIGHT(live_all_dep + sizeof(resp_pack_head_t));
	ushort width_4 = GET_PIC_WIDTH(live_all_dep + sizeof(resp_pack_head_t));
	int pic_id_4 = GET_ID(live_all_dep);
	emit start_write_file(live_all_dep, channel_4, height_4, width_4, pic_id_4);
	std::cout << "pic_4:" << "channel_4:" << channel_4 << " " << "height_4:" << height_4 << " " << "width_4:" << width_4 << std::endl;
	//QMessageBox::information(nullptr, QString::fromLocal8Bit("Sucessful"), QString::fromLocal8Bit("Completed！"), QMessageBox::Ok);
	if (rec_data != nullptr) {
		free(rec_data);
		rec_data = nullptr;
	}
	usb_release();
	return;
}

void BCTC::write_file(unsigned char *data, short channel,ushort height,ushort width,int id)
{
	QString fileName_live = "./" + QString::fromLocal8Bit("活体");
	creatFilePath(fileName_live);
	QString fileName_unlive = "./" + QString::fromLocal8Bit("假体");
	creatFilePath(fileName_unlive);
	unsigned int offset = sizeof(resp_pack_head_t) + sizeof(pic_payload_t);
	QString huo = QString::fromLocal8Bit("活体");
	QString jia = QString::fromLocal8Bit("假体");
	std::string path_str;
	QDateTime time;
	QString str_time = time.currentDateTime().toString("yyyyMMddHHmmss");
	QString saveName;
	if (channel == PROSTHESIS)  //假体
	{
		saveName = fileName_unlive + "/" + str_time + "-" + QString::number(0) + ".raw";
		path_str = "./" + std::string((const char *)jia.toLocal8Bit().constData()) + "/" + str_time.toStdString() + "-0" + ".jpg";
	}
	if (channel == ALIVE_FULL)  //活体全景
	{
		saveName = fileName_live + "/" + str_time + "-" + QString::number(1) + ".raw";
		path_str = "./" + std::string((const char *)huo.toLocal8Bit().constData()) + "/" + str_time.toStdString() + "-1" + ".jpg";
	}
	if (channel == ALIVE_FACE)  //活体人脸
	{
		saveName = fileName_live + "/" + str_time + "-" + QString::number(2) + ".raw";
		path_str = "./" + std::string((const char *)huo.toLocal8Bit().constData()) + "/" + str_time.toStdString() + "-2" + ".jpg";
	}
	if (channel == ALL_ALIVE_IR)  //全部活体ir
	{
		saveName = fileName_live + "/" + str_time + "-" + QString::number(3) + ".raw";
		path_str = "./" + std::string((const char *)huo.toLocal8Bit().constData()) + "/" + str_time.toStdString() + "-3" + ".jpg";
	}
	if (channel == ALL_ALIVE_DEPTH)  //全部活体深度
	{
		saveName = fileName_live + "/" + str_time + "-" + QString::number(4) + ".raw";
		path_str = "./" + std::string((const char *)huo.toLocal8Bit().constData()) + "/" + str_time.toStdString() + "-4" + ".jpg";
	}
//#ifdef SAVE_RAW
	QFile file(saveName);
	if (!file.open(QIODevice::WriteOnly))
	{
		QMessageBox::critical(nullptr, QString::fromLocal8Bit("Error"), QString::fromLocal8Bit("Can't open file!"), QMessageBox::Ok);
		return;
	}
	file.write((const char *)data + offset, GET_RESP_LEN(data) - offset); 
	file.close();
//#endif 
	if (IR_RAW == id)
	{
		cv::Mat img(height, width, CV_8UC1, data + offset);
		cv::imwrite(path_str, img);
		emit finished();
		std::cout << "save pic completed:" << "channel:" << channel << " " << "height:" << height << " " << "width:" << width << std::endl;
	}
	if (RGB_YUYV422 == id)
	{

	}
	//cv::Mat img(height, width, CV_8UC1, data + offset);
	//cv::imwrite(saveName.toStdString(), img);
	//emit finished();
}
//串口抓图命令
void BCTC::seri_cmd_send_data(/*SerialPort *serial*/)
{
	serial->sendPicOrCmd = true;
	unsigned char sendData[16] = { 0 };
	unsigned char sendCmd[8] = { 0x31,0x30,0x31,0x30,0x39,0x39,0x00,0x01 };
	port_send_msg(sendData, 8, BCTC_CMD);
	memcpy(sendData + sizeof(PortDataProtorl), sendCmd, 8);
	char check = std::accumulate(sendData + 2, sendData + sizeof(PortDataProtorl) + 8, 0);
	char checkSum[1] = { check };
	memcpy(sendData + sizeof(PortDataProtorl) + 8, checkSum, 1);
	serial->send_serial_data(sendData, 16,serial->serial_port);
}

std::vector<char> BCTC::get_checkBox_result()
{
	//std::vector<int> result;
	//result.resize(3);
	std::vector<char> result(3);
	if (ui.checkBox->isChecked())
	{
		result[0] = 1;
	}
	if (ui.checkBox_2->isChecked())
	{
		result[1] = 1;
	}
	if (ui.checkBox_3->isChecked())
	{
		result[2] = 1;
	}
	return result;
}

void BCTC::on_pushButton_clicked()
{
	//SerialPort *serial = new SerialPort();
	//serial = new SerialPort();
	//connect(serial, SIGNAL(usb_send(bool)), this, SLOT(usb_send_fun(bool)));
	serial->connectSig();
	seri_cmd_send_data(/*serial*/);
}

void BCTC::usb_send_fun(bool flag)
{
	//delete serial;
	//serial = nullptr;

	unsigned char send_data[4] = { 0 };
	if (flag)
		memset(send_data, 0x41, 4);
	else
		memset(send_data, 0x43, 4);
	serial->send_serial_data(send_data, 4,serial->another_pc);

	std::vector<char> result = get_checkBox_result();
	usb_connect_data(result, flag);
}
//选择文件夹
void BCTC::on_pushButton_2_clicked()
{
	//QStringList fileName = QFileDialog::getOpenFileNames(nullptr, QString::fromLocal8Bit("选择文件夹"), "", "");
	//QString fileName = QFileDialog::getOpenFileName(nullptr, QString::fromLocal8Bit("选择文件夹"), "", "");
	QString fileName = QFileDialog::getExistingDirectory(nullptr, QString::fromLocal8Bit("选择文件夹"), "");
	QDir dir(fileName);
	int count = dir.count();
	if (count > 2)
	{
		for (int i = 2; i < dir.count(); i++)
		{
			files.push_back(fileName + "/" + dir[i]);
		}
	}
	else
	{
		QMessageBox::critical(nullptr, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("文件夹下没有文件！"), QMessageBox::Ok);
	}
}

//串口发送图片
void BCTC::send_pic_serial()
{
	serial->sendPicOrCmd = false;
	unsigned char pic_data[200 * 1024] = { 0 };
	connect(serial, SIGNAL(toSavePic(int)), this, SLOT(save_check_pic_type(int)));
	QEventLoop loop;
	connect(serial, SIGNAL(finished_pic_send()), &loop, SLOT(quit()));
	QByteArray data;
	for (int i = 0; i < files.size(); i++)
	{
		QFile file(files[i]);
		if (file.open(QIODevice::ReadOnly))
		{
			data = file.readAll();
			file.close();
		}
		else
		{
			QMessageBox::critical(nullptr, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("文件打开失败！"), QMessageBox::Ok);
		}
		int len = data.count();
		port_send_msg(pic_data, len, BCTC_PIC_SERIAL);
		memcpy(pic_data + sizeof(PortDataProtorl), data, len);
		char sum = std::accumulate(pic_data + 2, pic_data + sizeof(PortDataProtorl) + len, 0);
		char check[1] = { sum };
		memcpy(pic_data + sizeof(PortDataProtorl) + len, check, 1);
		serial->send_serial_data(pic_data, sizeof(PortDataProtorl) + len + 1,serial->serial_port);
		std::cout << "发完一张图片" << std::endl;
		//emit send_pic_data(data.data(), len);
		current_file_name = files[i];
		loop.exec();
	}
	QMessageBox::information(nullptr, "Completed", "Send Picture Completed!");
}

void BCTC::copyFile(QString path)
{
	QString filePath;
	QDir dir;
	QFileInfo info(current_file_name);
	QString fi = info.fileName();  //获取文件名
	if (!dir.exists(path))
	{
		dir.mkdir(path);
	}
	filePath = path + "\\" + fi;
	QFile file_new(filePath);
	if (file_new.exists())
		file_new.remove();
	if (!(QFile::copy(current_file_name, filePath)))
		QMessageBox::warning(nullptr, "Error", "File Save Error!");
}
//保存送检图片文件结果
void BCTC::save_check_pic_type(int id)
{
	if (id & 0x01)
	{
		QString dirName = "./" + QString::fromLocal8Bit("分辨率不满足");
		copyFile(dirName);
	}
	if (id & 0x02)
	{
		QString dirName = "./" + QString::fromLocal8Bit("人脸不完整");
		copyFile(dirName);
	}
	if (id & 0x04)
	{
		QString dirName = "./" + QString::fromLocal8Bit("瞳间距不满足");
		copyFile(dirName);
	}
	if (id & 0x08)
	{
		QString dirName = "./" + QString::fromLocal8Bit("模糊");
		copyFile(dirName);
	}
	if (id & 0x10)
	{
		QString dirName = "./" + QString::fromLocal8Bit("表情不满足");
		copyFile(dirName);
	}
	if (id & 0x20)
	{
		QString dirName = "./" + QString::fromLocal8Bit("角度不满足");
		copyFile(dirName);
	}
	if (id & 0x40)
	{
		QString dirName = "./" + QString::fromLocal8Bit("光照不满足");
		copyFile(dirName);
	}
	if (id & 0x80)
	{
		QString dirName = "./" + QString::fromLocal8Bit("多人脸");
		copyFile(dirName);
	}
	if (!id)
	{
		QString dirName = "./" + QString::fromLocal8Bit("合格");
		copyFile(dirName);
	}
}

void BCTC::on_pushButton_3_clicked()
{
	send_pic_serial();
}
//拍照
void BCTC::on_pushButton_4_clicked()
{
	static int pic_id = 0;
	uint8_t cap[BUF_SEND_LEN] = { 0 };
	uint8_t *save = (uint8_t *)malloc(BUF_RECV_IR_SPK_DEPTH);
	UsbConnect usb;
	pack_head(BCTC_CMD_CAP, pic_id, 0, cap);
	if (usb_initial() < 0)
	{
		QMessageBox::warning(nullptr, QString::fromLocal8Bit("Error"), QString::fromLocal8Bit("USB Init error!"), QMessageBox::Ok);
		return;
	}
	if (usb.send_usb_data(cap, GET_REQ_LEN(cap)) < 0)
	{
		QMessageBox::critical(nullptr, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("USB 发送失败!"), QMessageBox::Ok);
		if (save != nullptr) {
			free(save);
			save = nullptr;
		}
		usb_release();
		return;
	}
	if (usb.rec_usb_data(pic_id, cap, save) < 0)
	{
		QMessageBox::critical(nullptr, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("USB 接收失败!"), QMessageBox::Ok);
		if (save != nullptr) {
			free(save);
			save = nullptr;
		}
		usb_release();
		return;
	}
	uint32_t offset = sizeof(resp_pack_head_t) + sizeof(pic_payload_t);
	QString str = "./" + QString::fromLocal8Bit("拍照");
	creatFilePath(str);
	QDateTime time;
	QString str_time = time.currentDateTime().toString("yyyyMMddHHmmss");
	QString save_path = str + "/" + str_time + ".raw";
	QFile write_pic(save_path);
	if (!write_pic.open(QIODevice::WriteOnly))
	{
		return;
	}
	write_pic.write((char *)save + offset, GET_RESP_LEN(save) - offset);
	write_pic.close();
	int pic_id_ = GET_ID(save);
	ushort height = GET_PIC_HEIGHT(save + sizeof(resp_pack_head_t));
	ushort width = GET_PIC_WIDTH(save + sizeof(resp_pack_head_t));
	std::string save_jpg = "./" + std::string((const char *)str.toLocal8Bit().constData()) + "/" + str_time.toStdString() + ".jpg";
	if (IR_RAW == pic_id_)
	{
		cv::Mat img(height, width, CV_8UC1, save + offset);
		cv::imwrite(save_jpg, img);
	}
	pic_id++;
	usb_release();
}
//打开串口
void BCTC::on_pushButton_5_clicked()
{
	if (ui.pushButton_5->text() == QString::fromLocal8Bit("打开"))
	{
		QString portName = ui.comboBox->currentText();
		QString portName_2 = ui.comboBox_6->currentText();
		serial->initSerialPort(serial->serial_port, portName);
		serial->initSerialPort(serial->another_pc, portName_2);
		serial->connectSig();
		connect(serial, SIGNAL(toSendUsbCmd()), this, SLOT(seri_cmd_send_data(/*SerialPort *serial*/)));
		ui.pushButton_5->setText(QString::fromLocal8Bit("关闭"));
	}
	else
	{
		ui.pushButton_5->setText(QString::fromLocal8Bit("打开"));
	}
}