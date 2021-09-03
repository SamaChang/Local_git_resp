#include "RTC.h"
#include "packet.h"
#include "qmessagebox.h"
#include "SNInformation.h"
#include "TCP.h"

RTC::RTC(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->setWindowTitle(QString::fromLocal8Bit("RTC测试"));
	this->setWindowFlags(Qt::WindowCloseButtonHint);
	this->setWindowIcon(QIcon("./Logo.png"));
	buttonStyle(ui.pushButton, "./Button_Small.qss");
	buttonStyle(ui.pushButton_2, "./Button_Small.qss");
	buttonStyle(ui.pushButton_3, "./Button.qss");
}

RTC::~RTC()
{
}

void RTC::on_pushButton_clicked()
{
	//saveLog(snInf, QString::fromLocal8Bit("光感测试"), "Pass");
	QDateTime time;
	QString currentTime = time.currentDateTime().toString("yyyy/MM/dd HH:mm:ss");
	writeCSV(snInf, NULL, "PASS", QString::number(16), currentTime, QString::fromLocal8Bit("RTC"), NULL, NULL, NULL, NULL, NULL);
	this->close();
	emit nextTest(true, 34);
	emit finishedInfo();
}

void RTC::on_pushButton_2_clicked()
{
	//saveLog(snInf, QString::fromLocal8Bit("光感测试"), "Fail");
	QDateTime time;
	QString currentTime = time.currentDateTime().toString("yyyy/MM/dd HH:mm:ss");
	recordResult("FAIL");
	writeCSV(snInf, NULL, "FAIL", QString::number(16), currentTime, QString::fromLocal8Bit("RTC"), NULL, NULL, NULL, NULL, NULL);
	this->close();
	emit nextTest(false, 34);
	emit finishedInfo();
}

void RTC::on_pushButton_3_clicked()
{
	uint8_t send_buf[BUF_SEND_LEN] = { 0 };
	uint8_t recv_buf[BUF_RESERVE_LEN] = { 0 };

	uint32_t payload_len = sizeof(calibration_param);
	pack360_head(CMD_RTC, payload_len, send_buf);   //加头
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

	Sleep(1000);
	QByteArray ay = tcp->socket_read_data(send_buf, (char *)recv_buf);
	if (ay != nullptr)
	{
		if (ay.at(4) == 1)
			QMessageBox::information(nullptr, QString::fromLocal8Bit("通过"), QString::fromLocal8Bit("RTC测试通过！"), QMessageBox::Ok);
		if (ay.at(4) == 0)
			QMessageBox::critical(nullptr, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("RTC测试不通过"), QMessageBox::Ok);
	}
	if (ay == nullptr)
	{
		QMessageBox::critical(nullptr, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("TCP读取数据错误！"), QMessageBox::Ok);
	}

	delete tcp;
	if (tcp != nullptr)
		tcp = nullptr;
}
