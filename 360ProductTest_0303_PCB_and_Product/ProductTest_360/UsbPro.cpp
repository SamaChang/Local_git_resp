#include "UsbPro.h"
#include "usb.h"
#include "def.h"
#include "packet.h"
#include "qmessagebox.h"
#include "SNInformation.h"

UsbPro::UsbPro(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->setWindowTitle(QString::fromLocal8Bit("USB����"));
	this->setWindowFlags(Qt::WindowCloseButtonHint);
	this->setWindowIcon(QIcon("./Logo.png"));
	buttonStyle(ui.pushButton, "./Button_Small.qss");
	buttonStyle(ui.pushButton_2, "./Button_Small.qss");
	buttonStyle(ui.pushButton_3, "./Button.qss");
}

UsbPro::~UsbPro()
{
}

void UsbPro::on_pushButton_clicked()
{
	saveLog(snInf, QString::fromLocal8Bit("USB����"), "Pass");
	this->close();
	emit nextTest(true, 15);
	emit finishedInfo();
}

void UsbPro::on_pushButton_2_clicked()
{
	saveLog(snInf, QString::fromLocal8Bit("USB����"), "Fail");
	this->close();
	emit nextTest(false, 15);
	emit finishedInfo();
}

void UsbPro::on_pushButton_3_clicked()
{
	uint8_t send_buf[BUF_SEND_LEN] = { 0 };
	uint8_t recv_buf[BUF_RESERVE_LEN] = { 0 };
	//saveLog("232", QString::fromLocal8Bit("�����豸"), "Pass");
	if (usb_initial() < 0)
	{
		QMessageBox::critical(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("USB��ʼ������"), QMessageBox::Ok);
		return;
	}
	uint32_t payload_len = sizeof(calibration_param);
	pack360_head(CMD_USB_OTG, payload_len, send_buf);   //��ͷ
	pcak360_buffer(send_buf + sizeof(send_360Protocol), FIRST);  //��ͷ��������
	if (send_packet(send_buf, GET_360_SEND_LEN(send_buf)) < 0)
	{
		QMessageBox::critical(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("USB���ʹ���"), QMessageBox::Ok);
		usb_release();
		return;
	}
	if (get_response(0, send_buf, recv_buf) < 0)
	{
		QMessageBox::critical(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("USB���մ���"), QMessageBox::Ok);
		usb_release();
		return;
	}

	usb_release();
}
