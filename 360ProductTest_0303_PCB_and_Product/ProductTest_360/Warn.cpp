#include "Warn.h"
#include "usb.h"
#include "def.h"
#include "packet.h"
#include "qmessagebox.h"
#include "SNInformation.h"
#include "TCP.h"

Warn::Warn(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->setWindowTitle(QString::fromLocal8Bit("报警测试"));
	this->setWindowFlags(Qt::WindowCloseButtonHint);
	this->setWindowIcon(QIcon("./Logo.png"));
	buttonStyle(ui.pushButton, "./Button_Small.qss");
	buttonStyle(ui.pushButton_2, "./Button_Small.qss");
	buttonStyle(ui.pushButton_3, "./Button.qss");
}

Warn::~Warn()
{
}

void Warn::on_pushButton_clicked()
{
	//saveLog(snInf, QString::fromLocal8Bit("报警测试"), "Pass");
	//this->close();
	//emit nextTest(true, 21);
	//emit finishedInfo();


	QDateTime time;
	QString currentTime = time.currentDateTime().toString("yyyy/MM/dd HH:mm:ss");
	writeCSV(snInf, NULL, "PASS", QString::number(7), currentTime, QString::fromLocal8Bit("报警测试"), NULL, NULL, NULL, NULL, NULL);
	this->close();
	emit nextTest(true, 21);
	emit finishedInfo();
}

void Warn::on_pushButton_2_clicked()
{
	//saveLog(snInf, QString::fromLocal8Bit("报警测试"), "Fail");
	//this->close();
	//emit nextTest(false, 21);
	//emit finishedInfo();


	QDateTime time;
	QString currentTime = time.currentDateTime().toString("yyyy/MM/dd HH:mm:ss");
	recordResult("FAIL");
	writeCSV(snInf, NULL, "FAIL", QString::number(7), currentTime, QString::fromLocal8Bit("报警测试"), NULL, NULL, NULL, NULL, NULL);
	this->close();
	emit nextTest(false, 21);
	emit finishedInfo();
}

void Warn::on_pushButton_3_clicked()
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
	//pack360_head(CMD_WARNING, payload_len, send_buf);   //加头
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
	//if (recv_buf[3] == 1)
	//	QMessageBox::information(nullptr, QString::fromLocal8Bit("通过"), QString::fromLocal8Bit("报警测试通过！"), QMessageBox::Ok);
	//if (recv_buf[3] == 0)
	//	QMessageBox::critical(nullptr, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("报警测试不通过！"), QMessageBox::Ok);

	//usb_release();




	uint8_t send_buf[BUF_SEND_LEN] = { 0 };
	uint8_t recv_buf[BUF_RESERVE_LEN] = { 0 };

	uint32_t payload_len = sizeof(calibration_param);
	pack360_head(CMD_WARNING, payload_len, send_buf);   //加头
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
			QMessageBox::information(nullptr, QString::fromLocal8Bit("通过"), QString::fromLocal8Bit("报警测试通过！"), QMessageBox::Ok);
		if (ay.at(4) == 0)
			QMessageBox::critical(nullptr, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("报警测试不通过"), QMessageBox::Ok);
	}
	if (ay == nullptr)
	{
		QMessageBox::critical(nullptr, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("TCP读取数据错误！"), QMessageBox::Ok);
	}

	delete tcp;
	if (tcp != nullptr)
		tcp = nullptr;
}
