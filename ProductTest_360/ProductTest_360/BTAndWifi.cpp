#include "BTAndWifi.h"
#include "usb.h"
#include "def.h"
#include "packet.h"
#include "qmessagebox.h"
#include "SNInformation.h"

BTAndWifi::BTAndWifi(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->setWindowTitle(QString::fromLocal8Bit("????/Wifi????"));
	this->setWindowFlags(Qt::WindowCloseButtonHint);
	this->setWindowIcon(QIcon("./Logo.png"));
	buttonStyle(ui.pushButton, "./Button_Small.qss");
	buttonStyle(ui.pushButton_2, "./Button_Small.qss");
	buttonStyle(ui.pushButton_3, "./Button.qss");
	buttonStyle(ui.pushButton_4, "./Button.qss");
}

BTAndWifi::~BTAndWifi()
{
}

void BTAndWifi::on_pushButton_clicked()
{
	saveLog(snInf, QString::fromLocal8Bit("??????Wifi"), "Pass");
	this->close();
	emit nextTest(true, 29);
	emit finishedInfo();
}

void BTAndWifi::on_pushButton_2_clicked()
{
	saveLog(snInf, QString::fromLocal8Bit("??????Wifi"), "Fail");
	this->close();
	emit nextTest(false, 29);
	emit finishedInfo();
}

void BTAndWifi::on_pushButton_3_clicked()
{
	uint8_t send_buf[BUF_SEND_LEN] = { 0 };
	uint8_t recv_buf[BUF_RESERVE_LEN] = { 0 };
	//saveLog("232", QString::fromLocal8Bit("????"), "Pass");
	if (usb_initial() < 0)
	{
		QMessageBox::critical(nullptr, QString::fromLocal8Bit("????"), QString::fromLocal8Bit("USB??ʼ????????"), QMessageBox::Ok);
		return;
	}
	uint32_t payload_len = sizeof(calibration_param);
	pack360_head(CMD_BT_WIFI, payload_len, send_buf);   //??ͷ
	pcak360_buffer(send_buf + sizeof(send_360Protocol), FIRST);  //??ͷ????????
	if (send_packet(send_buf, GET_360_SEND_LEN(send_buf)) < 0)
	{
		QMessageBox::critical(nullptr, QString::fromLocal8Bit("????"), QString::fromLocal8Bit("USB???ʹ?????"), QMessageBox::Ok);
		usb_release();
		return;
	}
	if (get_response(0, send_buf, recv_buf) < 0)
	{
		QMessageBox::critical(nullptr, QString::fromLocal8Bit("????"), QString::fromLocal8Bit("USB???մ???"), QMessageBox::Ok);
		usb_release();
		return;
	}

	usb_release();
}

void BTAndWifi::on_pushButton_4_clicked()
{
	uint8_t send_buf[BUF_SEND_LEN] = { 0 };
	uint8_t recv_buf[BUF_RESERVE_LEN] = { 0 };
	//saveLog("232", QString::fromLocal8Bit("Wifi"), "Pass");
	if (usb_initial() < 0)
	{
		QMessageBox::critical(nullptr, QString::fromLocal8Bit("????"), QString::fromLocal8Bit("USB??ʼ????????"), QMessageBox::Ok);
		return;
	}
	uint32_t payload_len = sizeof(calibration_param);
	pack360_head(CMD_BT_WIFI, payload_len, send_buf);   //??ͷ
	pcak360_buffer(send_buf + sizeof(send_360Protocol), SECOND);  //??ͷ????????
	if (send_packet(send_buf, GET_360_SEND_LEN(send_buf)) < 0)
	{
		QMessageBox::critical(nullptr, QString::fromLocal8Bit("????"), QString::fromLocal8Bit("USB???ʹ?????"), QMessageBox::Ok);
		usb_release();
		return;
	}
	if (get_response(0, send_buf, recv_buf) < 0)
	{
		QMessageBox::critical(nullptr, QString::fromLocal8Bit("????"), QString::fromLocal8Bit("USB???մ???"), QMessageBox::Ok);
		usb_release();
		return;
	}
	usb_release();
}
