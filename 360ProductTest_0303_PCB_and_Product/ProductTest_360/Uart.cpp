#include "Uart.h"
#include "usb.h"
#include "def.h"
#include "packet.h"
#include "qmessagebox.h"
#include "SNInformation.h"
#include "TCP.h"

Uart::Uart(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->setWindowTitle(QString::fromLocal8Bit("���ڲ���"));
	this->setWindowFlags(Qt::WindowCloseButtonHint);
	this->setWindowIcon(QIcon("./Logo.png"));
	buttonStyle(ui.pushButton, "./Button_Small.qss");
	buttonStyle(ui.pushButton_2, "./Button_Small.qss");
	buttonStyle(ui.pushButton_3, "./Button.qss");
}

Uart::~Uart()
{
}

void Uart::on_pushButton_clicked()
{
	//saveLog(snInf, QString::fromLocal8Bit("UART����"), "Pass");
	//this->close();
	//emit nextTest(true, 18);
	//emit finishedInfo();


	QDateTime time;
	QString currentTime = time.currentDateTime().toString("yyyy/MM/dd HH:mm:ss");
	writeCSV(snInf, NULL, "PASS", QString::number(6), currentTime, QString::fromLocal8Bit("UART����"), NULL, NULL, NULL, NULL, NULL);
	this->close();
	emit nextTest(true, 18);
	emit finishedInfo();
}

void Uart::on_pushButton_2_clicked()
{
	//saveLog(snInf, QString::fromLocal8Bit("UART����"), "Fail");
	//this->close();
	//emit nextTest(false, 18);
	//emit finishedInfo();


	QDateTime time;
	QString currentTime = time.currentDateTime().toString("yyyy/MM/dd HH:mm:ss");
	recordResult("FAIL");
	writeCSV(snInf, NULL, "FAIL", QString::number(6), currentTime, QString::fromLocal8Bit("UART����"), NULL, NULL, NULL, NULL, NULL);
	this->close();
	emit nextTest(false, 18);
	emit finishedInfo();
}

void Uart::on_pushButton_3_clicked()
{
	//uint8_t send_buf[BUF_SEND_LEN] = { 0 };
	//uint8_t recv_buf[BUF_RESERVE_LEN] = { 0 };
	////saveLog("232", QString::fromLocal8Bit("�����豸"), "Pass");
	//if (usb_initial() < 0)
	//{
	//	QMessageBox::critical(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("USB��ʼ������"), QMessageBox::Ok);
	//	return;
	//}
	//uint32_t payload_len = sizeof(calibration_param);
	//pack360_head(CMD_UART, payload_len, send_buf);   //��ͷ
	//pcak360_buffer(send_buf + sizeof(send_360Protocol), FIRST);  //��ͷ��������
	//if (send_packet(send_buf, GET_360_SEND_LEN(send_buf)) < 0)
	//{
	//	QMessageBox::critical(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("USB���ʹ���"), QMessageBox::Ok);
	//	usb_release();
	//	return;
	//}
	//if (get_response(0, send_buf, recv_buf) < 0)
	//{
	//	QMessageBox::critical(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("USB���մ���"), QMessageBox::Ok);
	//	usb_release();
	//	return;
	//}
	//if(recv_buf[3]==1)
	//	QMessageBox::information(nullptr, QString::fromLocal8Bit("ͨ��"), QString::fromLocal8Bit("Uart����ͨ����"), QMessageBox::Ok);
	//if(recv_buf[3]==0)
	//	QMessageBox::critical(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("Uart���Բ�ͨ��"), QMessageBox::Ok);
	//
	//usb_release();



	uint8_t send_buf[BUF_SEND_LEN] = { 0 };
	uint8_t recv_buf[BUF_RESERVE_LEN] = { 0 };

	uint32_t payload_len = sizeof(calibration_param);
	pack360_head(CMD_UART, payload_len, send_buf);   //��ͷ
	pcak360_buffer(send_buf + sizeof(send_360Protocol), FIRST);  //��ͷ��������

	TCP *tcp = new TCP(this);
	tcp->initSocket();
	if (tcp->connectSocket() < 0)
	{
		QMessageBox::critical(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("TCP���ӳ�ʱ��"), QMessageBox::Ok);
	}
	//tcp->connectSocket();
	tcp->send_data((char *)send_buf, GET_360_SEND_LEN(send_buf));
	//if (tcp->socket_read_data(send_buf, (char *)recv_buf) < 0)
	//{
	//	QMessageBox::critical(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("TCP��ȡ���ݴ���"), QMessageBox::Ok);
	//}

	QByteArray ay = tcp->socket_read_data(send_buf, (char *)recv_buf);
	if (ay != nullptr)
	{
		if (ay.at(4) == 1)
			QMessageBox::information(nullptr, QString::fromLocal8Bit("ͨ��"), QString::fromLocal8Bit("Uart����ͨ����"), QMessageBox::Ok);
		if (ay.at(4) == 0)
			QMessageBox::critical(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("Uart���Բ�ͨ��"), QMessageBox::Ok);
	}
	if (ay == nullptr)
	{
		QMessageBox::critical(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("TCP��ȡ���ݴ���"), QMessageBox::Ok);
	}

	delete tcp;
	if (tcp != nullptr)
		tcp = nullptr;
}

