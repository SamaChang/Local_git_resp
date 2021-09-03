#include "PreventRemove.h"
#include "usb.h"
#include "def.h"
#include "packet.h"
#include "qmessagebox.h"
#include "SNInformation.h"

PreventRemove::PreventRemove(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->setWindowTitle(QString::fromLocal8Bit("∑¿≤≤‚ ‘"));
	this->setWindowFlags(Qt::WindowCloseButtonHint);
	this->setWindowIcon(QIcon("./Logo.png"));
	buttonStyle(ui.pushButton, "./Button_Small.qss");
	buttonStyle(ui.pushButton_2, "./Button_Small.qss");
	buttonStyle(ui.pushButton_3, "./Button.qss");
}

PreventRemove::~PreventRemove()
{
}

void PreventRemove::on_pushButton_clicked()
{
	saveLog(snInf, QString::fromLocal8Bit("∑¿≤≤‚ ‘"), "Pass");
	this->close();
	emit nextTest(true, 31);
	emit finishedInfo();
}

void PreventRemove::on_pushButton_2_clicked()
{
	saveLog(snInf, QString::fromLocal8Bit("∑¿≤≤‚ ‘"), "Fail");
	this->close();
	emit nextTest(false, 31);
	emit finishedInfo();
}

void PreventRemove::on_pushButton_3_clicked()
{
	uint8_t send_buf[BUF_SEND_LEN] = { 0 };
	uint8_t recv_buf[BUF_RESERVE_LEN] = { 0 };
	//saveLog("232", QString::fromLocal8Bit("π‚∏–≤‚ ‘"), "Pass");
	if (usb_initial() < 0)
	{
		QMessageBox::critical(nullptr, QString::fromLocal8Bit("¥ÌŒÛ"), QString::fromLocal8Bit("USB≥ı ºªØ¥ÌŒÛ£°"), QMessageBox::Ok);
		return;
	}
	uint32_t payload_len = sizeof(calibration_param);
	pack360_head(CMD_PREVENT, payload_len, send_buf);   //º”Õ∑
	pcak360_buffer(send_buf + sizeof(send_360Protocol), FIRST);  //º”Õ∑∫Û√Ê ˝æ›
	if (send_packet(send_buf, GET_360_SEND_LEN(send_buf)) < 0)
	{
		QMessageBox::critical(nullptr, QString::fromLocal8Bit("¥ÌŒÛ"), QString::fromLocal8Bit("USB∑¢ÀÕ¥ÌŒÛ£°"), QMessageBox::Ok);
		usb_release();
		return;
	}
	if (get_response(0, send_buf, recv_buf) < 0)
	{
		QMessageBox::critical(nullptr, QString::fromLocal8Bit("¥ÌŒÛ"), QString::fromLocal8Bit("USBΩ” ’¥ÌŒÛ"), QMessageBox::Ok);
		usb_release();
		return;
	}
	if (recv_buf[3] == 1)
		QMessageBox::information(nullptr, QString::fromLocal8Bit("Õ®π˝"), QString::fromLocal8Bit("∑¿≤≤‚ ‘Õ®π˝£°"), QMessageBox::Ok);
	if (recv_buf[3] == 0)
		QMessageBox::critical(nullptr, QString::fromLocal8Bit("¥ÌŒÛ"), QString::fromLocal8Bit("∑¿≤≤‚ ‘≤ªÕ®π˝"), QMessageBox::Ok);

	usb_release();
}
