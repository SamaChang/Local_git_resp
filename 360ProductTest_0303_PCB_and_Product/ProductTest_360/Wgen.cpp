#include "Wgen.h"
#include "usb.h"
#include "def.h"
#include "packet.h"
#include "qmessagebox.h"
#include "SNInformation.h"
#include "TCP.h"

Wgen::Wgen(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->setWindowTitle(QString::fromLocal8Bit("韦根/干接点测试"));
	this->setWindowFlags(Qt::WindowCloseButtonHint);
	this->setWindowIcon(QIcon("./Logo.png"));
	buttonStyle(ui.pushButton, "./Button_Small.qss");
	buttonStyle(ui.pushButton_2, "./Button_Small.qss");
	buttonStyle(ui.pushButton_3, "./Button.qss");
	buttonStyle(ui.pushButton_4, "./Button.qss");

	//ui.pushButton_3->setVisible(false);   //韦根暂时不测
}

Wgen::~Wgen()
{
}

void Wgen::on_pushButton_clicked()
{
	//uint8_t send_buf[BUF_SEND_LEN] = { 0 };
	//uint8_t recv_buf[BUF_RESERVE_LEN] = { 0 };
	////saveLog("232", QString::fromLocal8Bit("网络设备"), "Pass");
	//if (usb_initial() < 0)
	//{
	//	QMessageBox::critical(nullptr, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("USB初始化错误！"), QMessageBox::Ok);
	//	return;
	//}
	//uint32_t payload_len = sizeof(calibration_param);
	//pack360_head(CMD_WG, payload_len, send_buf);   //加头
	//pcak360_buffer(send_buf + sizeof(send_360Protocol), SEVENTH);  //加头后面数据
	//if (send_packet(send_buf, GET_360_SEND_LEN(send_buf)) < 0)
	//{
	//	QMessageBox::critical(nullptr, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("USB发送错误！"), QMessageBox::Ok);
	//	usb_release();
	//	return;
	//}
	//if (get_response(0, send_buf, recv_buf) < 0)
	//{
	//	QMessageBox::critical(nullptr, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("USB接收错误"), QMessageBox::Ok);
	//	usb_release();
	//	return;
	//}

	//usb_release();
	////saveLog(snInf, QString::fromLocal8Bit("韦根/干接点测试"), "Pass");
	//QDateTime time;
	//QString currentTime = time.currentDateTime().toString("yyyy/MM/dd HH:mm:ss");
	//writeCSV(snInf, NULL, "PASS", QString::number(6), currentTime, QString::fromLocal8Bit("韦根/干接点测试"), NULL, NULL, NULL, NULL, NULL);
	//this->close();
	//emit nextTest(true, 16);
	//emit finishedInfo();



	uint8_t send_buf[BUF_SEND_LEN] = { 0 };
	uint8_t recv_buf[BUF_RESERVE_LEN] = { 0 };

	uint32_t payload_len = sizeof(calibration_param);
	pack360_head(CMD_WG, payload_len, send_buf);   //加头
	pcak360_buffer(send_buf + sizeof(send_360Protocol), SEVENTH);  //加头后面数据

	TCP *tcp = new TCP(this);
	tcp->initSocket();
	if (tcp->connectSocket() < 0)
	{
		QMessageBox::critical(nullptr, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("TCP连接超时！"), QMessageBox::Ok);
	}
	//tcp->connectSocket();
	tcp->send_data((char *)send_buf, GET_360_SEND_LEN(send_buf));
	//if (tcp->socket_read_data(send_buf, (char *)recv_buf) < 0)
	//{
	//	QMessageBox::critical(nullptr, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("TCP读取数据错误！"), QMessageBox::Ok);
	//}
	QByteArray ay = tcp->socket_read_data(send_buf, (char *)recv_buf);
	//if (ay != nullptr)
	//{
	//	QByteArray ay;
	//	ay = tcp->socket_read_data(send_buf, (char *)recv_buf);
	//}
	if (ay == nullptr)
	{
		QMessageBox::critical(nullptr, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("TCP读取数据错误！"), QMessageBox::Ok);
	}

	delete tcp;
	if (tcp != nullptr)
		tcp = nullptr;



	QDateTime time;
	QString currentTime = time.currentDateTime().toString("yyyy/MM/dd HH:mm:ss");
	writeCSV(snInf, NULL, "PASS", QString::number(9), currentTime, QString::fromLocal8Bit("韦根/干接点"), NULL, NULL, NULL, NULL, NULL);
	this->close();
	emit nextTest(true, 16);
	emit finishedInfo();
}

void Wgen::on_pushButton_2_clicked()
{
	//uint8_t send_buf[BUF_SEND_LEN] = { 0 };
	//uint8_t recv_buf[BUF_RESERVE_LEN] = { 0 };
	////saveLog("232", QString::fromLocal8Bit("网络设备"), "Pass");
	//if (usb_initial() < 0)
	//{
	//	QMessageBox::critical(nullptr, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("USB初始化错误！"), QMessageBox::Ok);
	//	return;
	//}
	//uint32_t payload_len = sizeof(calibration_param);
	//pack360_head(CMD_WG, payload_len, send_buf);   //加头
	//pcak360_buffer(send_buf + sizeof(send_360Protocol), SEVENTH);  //加头后面数据
	//if (send_packet(send_buf, GET_360_SEND_LEN(send_buf)) < 0)
	//{
	//	QMessageBox::critical(nullptr, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("USB发送错误！"), QMessageBox::Ok);
	//	usb_release();
	//	return;
	//}
	//if (get_response(0, send_buf, recv_buf) < 0)
	//{
	//	QMessageBox::critical(nullptr, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("USB接收错误"), QMessageBox::Ok);
	//	usb_release();
	//	return;
	//}

	//usb_release();
	////saveLog(snInf, QString::fromLocal8Bit("韦根/干接点测试"), "Fail");
	//QDateTime time;
	//QString currentTime = time.currentDateTime().toString("yyyy/MM/dd HH:mm:ss");
	//recordResult("FAIL");
	//writeCSV(snInf, NULL, "FAIL", QString::number(6), currentTime, QString::fromLocal8Bit("韦根/干接点测试"), NULL, NULL, NULL, NULL, NULL);
	//this->close();
	//emit nextTest(false, 16);
	//emit finishedInfo();


	uint8_t send_buf[BUF_SEND_LEN] = { 0 };
	uint8_t recv_buf[BUF_RESERVE_LEN] = { 0 };

	uint32_t payload_len = sizeof(calibration_param);
	pack360_head(CMD_WG, payload_len, send_buf);   //加头
	pcak360_buffer(send_buf + sizeof(send_360Protocol), SEVENTH);  //加头后面数据

	TCP *tcp = new TCP(this);
	tcp->initSocket();
	if (tcp->connectSocket() < 0)
	{
		QMessageBox::critical(nullptr, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("TCP连接超时！"), QMessageBox::Ok);
	}
	//tcp->connectSocket();
	tcp->send_data((char *)send_buf, GET_360_SEND_LEN(send_buf));
	//if (tcp->socket_read_data(send_buf, (char *)recv_buf) < 0)
	//{
	//	QMessageBox::critical(nullptr, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("TCP读取数据错误！"), QMessageBox::Ok);
	//}
	QByteArray ay = tcp->socket_read_data(send_buf, (char *)recv_buf);
	//if (ay != nullptr)
	//{
	//	QByteArray ay;
	//	ay = tcp->socket_read_data(send_buf, (char *)recv_buf);
	//}
	if (ay == nullptr)
	{
		QMessageBox::critical(nullptr, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("TCP读取数据错误！"), QMessageBox::Ok);
	}

	delete tcp;
	if (tcp != nullptr)
		tcp = nullptr;



	QDateTime time;
	QString currentTime = time.currentDateTime().toString("yyyy/MM/dd HH:mm:ss");
	recordResult("FAIL");
	writeCSV(snInf, NULL, "FAIL", QString::number(9), currentTime, QString::fromLocal8Bit("韦根/干接点"), NULL, NULL, NULL, NULL, NULL);
	this->close();
	emit nextTest(false, 16);
	emit finishedInfo();
}
//韦根
void Wgen::on_pushButton_3_clicked()
{
	//uint8_t send_buf[BUF_SEND_LEN] = { 0 };
	//uint8_t recv_buf[BUF_RESERVE_LEN] = { 0 };
	////saveLog("232", QString::fromLocal8Bit("网络设备"), "Pass");
	//if (usb_initial() < 0)
	//{
	//	QMessageBox::critical(nullptr, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("USB初始化错误！"), QMessageBox::Ok);
	//	return;
	//}
	//uint32_t payload_len = sizeof(calibration_param);
	//pack360_head(CMD_WG, payload_len, send_buf);   //加头
	//pcak360_buffer(send_buf + sizeof(send_360Protocol), FIRST);  //加头后面数据
	//if (send_packet(send_buf, GET_360_SEND_LEN(send_buf)) < 0)
	//{
	//	QMessageBox::critical(nullptr, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("USB发送错误！"), QMessageBox::Ok);
	//	usb_release();
	//	return;
	//}
	//if (get_response(0, send_buf, recv_buf) < 0)
	//{
	//	QMessageBox::critical(nullptr, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("USB接收错误"), QMessageBox::Ok);
	//	usb_release();
	//	return;
	//}

	//usb_release();


	uint8_t send_buf[BUF_SEND_LEN] = { 0 };
	uint8_t recv_buf[BUF_RESERVE_LEN] = { 0 };

	uint32_t payload_len = sizeof(calibration_param);
	pack360_head(CMD_WG, payload_len, send_buf);   //加头
	pcak360_buffer(send_buf + sizeof(send_360Protocol), FIRST);  //加头后面数据

	TCP *tcp = new TCP(this);
	tcp->initSocket();
	if (tcp->connectSocket() < 0)
	{
		QMessageBox::critical(nullptr, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("TCP连接超时！"), QMessageBox::Ok);
	}
	//tcp->connectSocket();
	tcp->send_data((char *)send_buf, GET_360_SEND_LEN(send_buf));
	//if (tcp->socket_read_data(send_buf, (char *)recv_buf) < 0)
	//{
	//	QMessageBox::critical(nullptr, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("TCP读取数据错误！"), QMessageBox::Ok);
	//}

	QByteArray ay = tcp->socket_read_data(send_buf, (char *)recv_buf);
	if (ay != nullptr)
	{
		if (ay.at(4) == 1)
			QMessageBox::information(nullptr, QString::fromLocal8Bit("通过"), QString::fromLocal8Bit("韦根测试通过！"), QMessageBox::Ok);
		if (ay.at(4) == 0)
			QMessageBox::critical(nullptr, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("韦根测试不通过"), QMessageBox::Ok);
	}
	if (ay == nullptr)
	{
		QMessageBox::critical(nullptr, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("TCP读取数据错误！"), QMessageBox::Ok);
	}

	delete tcp;
	if (tcp != nullptr)
		tcp = nullptr;
}
//干接点
void Wgen::on_pushButton_4_clicked()
{
	//uint8_t send_buf[BUF_SEND_LEN] = { 0 };
	//uint8_t recv_buf[BUF_RESERVE_LEN] = { 0 };
	////saveLog("232", QString::fromLocal8Bit("网络设备"), "Pass");
	//if (usb_initial() < 0)
	//{
	//	QMessageBox::critical(nullptr, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("USB初始化错误！"), QMessageBox::Ok);
	//	return;
	//}
	//uint32_t payload_len = sizeof(calibration_param);
	//pack360_head(CMD_WG, payload_len, send_buf);   //加头
	//pcak360_buffer(send_buf + sizeof(send_360Protocol), SECOND);  //加头后面数据
	//if (send_packet(send_buf, GET_360_SEND_LEN(send_buf)) < 0)
	//{
	//	QMessageBox::critical(nullptr, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("USB发送错误！"), QMessageBox::Ok);
	//	usb_release();
	//	return;
	//}
	//if (get_response(0, send_buf, recv_buf) < 0)
	//{
	//	QMessageBox::critical(nullptr, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("USB接收错误"), QMessageBox::Ok);
	//	usb_release();
	//	return;
	//}

	//usb_release();



	uint8_t send_buf[BUF_SEND_LEN] = { 0 };
	uint8_t recv_buf[BUF_RESERVE_LEN] = { 0 };

	uint32_t payload_len = sizeof(calibration_param);
	pack360_head(CMD_WG, payload_len, send_buf);   //加头
	pcak360_buffer(send_buf + sizeof(send_360Protocol), SECOND);  //加头后面数据

	TCP *tcp = new TCP(this);
	tcp->initSocket();
	if (tcp->connectSocket() < 0)
	{
		QMessageBox::critical(nullptr, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("TCP连接超时！"), QMessageBox::Ok);
	}
	//tcp->connectSocket();
	tcp->send_data((char *)send_buf, GET_360_SEND_LEN(send_buf));
	//if (tcp->socket_read_data(send_buf, (char *)recv_buf) < 0)
	//{
	//	QMessageBox::critical(nullptr, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("TCP读取数据错误！"), QMessageBox::Ok);
	//}

	QByteArray ay = tcp->socket_read_data(send_buf, (char *)recv_buf);
	//if (ay != nullptr)
	//{
	//	if (ay.at(4) == 1)
	//		QMessageBox::information(nullptr, QString::fromLocal8Bit("通过"), QString::fromLocal8Bit("Sensor测试通过！"), QMessageBox::Ok);
	//	if (ay.at(4) == 0)
	//		QMessageBox::critical(nullptr, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("Sensor测试不通过"), QMessageBox::Ok);
	//}
	if (ay == nullptr)
	{
		QMessageBox::critical(nullptr, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("TCP读取数据错误！"), QMessageBox::Ok);
	}

	delete tcp;
	if (tcp != nullptr)
		tcp = nullptr;
}
