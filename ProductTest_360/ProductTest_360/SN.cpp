#include "SN.h"
#include "packet.h"
#include "common.h"
#include "SNInformation.h"
//QString snInf;
SN::SN(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->setWindowTitle(QString::fromLocal8Bit("SN"));
	this->setWindowFlags(Qt::WindowCloseButtonHint);
	this->setWindowIcon(QIcon("./Logo.png"));
	buttonStyle(ui.pushButton, "./Button_Small.qss");
	buttonStyle(ui.pushButton_2, "./Button.qss");
	buttonStyle(ui.pushButton_3, "./Button_Small.qss");
}

SN::~SN()
{
}

void SN::on_pushButton_clicked()
{
	//saveLog(snInf, QString::fromLocal8Bit("写入SN"), "Pass");
	QDateTime time;
	QString currentTime = time.currentDateTime().toString("yyyy/MM/dd HH:mm:ss");
	writeCSV(snInf, NULL, "PASS", QString::number(0), currentTime, QString::fromLocal8Bit("写入SN"), NULL, NULL, NULL, NULL, NULL);
	this->close();
	emit nextTest(true, 28);
	emit finishedInfo();
}

void SN::on_pushButton_3_clicked()
{
	//saveLog(snInf, QString::fromLocal8Bit("写入SN"), "Fail");
	QDateTime time;
	QString currentTime = time.currentDateTime().toString("yyyy/MM/dd HH:mm:ss");
	recordResult("FAIL");
	writeCSV(snInf, NULL, "FAIL", QString::number(0), currentTime, QString::fromLocal8Bit("写入SN"), NULL, NULL, NULL, NULL, NULL);
	this->close();
	emit nextTest(false, 28);
	emit finishedInfo();
}

void SN::on_pushButton_2_clicked()
{
	//QString qStr = ui.textEdit->toPlainText();
	//snInf = qStr;
	uint32_t dateY = 0;
	uint32_t devN = 0;
	QByteArray ba = snInf.toLatin1();
	if (ba.length() == 14)
	{
		uint8_t dateYear[4] = { ba.at(6),ba.at(7),ba.at(8),ba.at(9) };
		uint8_t devNum[4] = { ba.at(10),ba.at(11),ba.at(12),ba.at(13) };
		dateY = reverse_uint32(dateYear);
		devN = reverse_uint32(devNum);
	}
	//uint8_t dateYear[4] = { ba.at(6),ba.at(7),ba.at(8),ba.at(9) };
	//uint8_t devNum[4] = { ba.at(10),ba.at(11),ba.at(12),ba.at(13) };
	//uint32_t dateY = reverse_uint32(dateYear);
	//uint32_t devN = reverse_uint32(devNum);
	
	if (usb_initial() < 0)
	{
		QMessageBox::critical(nullptr, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("USB初始化错误！"), QMessageBox::Ok);
		return;
	}

	uint8_t send_buf[BUF_SEND_LEN] = { 0 };
	uint8_t recv_buf[BUF_RESERVE_LEN] = { 0 };
	//协议两种写法
	//SN_360 *sn_360 = new SN_360();
	SN_360 sn_360;
	//Hwid *hwid =new Hwid()/*= nullptr*/;
	Hwid hwid;
	//Wifi_mac *wifi =new Wifi_mac()/*= nullptr*/;
	Wifi_mac wifi;
	//Bt_mac *bt =new Bt_mac()/*= nullptr*/;
	Bt_mac bt;
	//Eth_mac *eth =new Eth_mac()/*= nullptr*/;
	Eth_mac eth;
	pack_360_SN(5, 1, 'A', 'E', dateY, devN, /*(uint8_t *)*/&sn_360);
	pack_360_hwid('P', 1, 0, /*send_buf + sizeof(SN_360)*/&hwid);
	pack_360_wifi_mac(0xB4, 0xef, 0x1c, 0x01, 0x39, 0xaa, &wifi);
	pack_360_bt_mac(0xB4, 0xef, 0x1c, 0x01, 0x39, 0xaa, &bt);
	pcak_360_eth_mac(0xB4, 0xef, 0x1c, 0x01, 0x39, 0xaa, &eth);
	pack_360_Info(send_buf + sizeof(send_360Protocol), 3, 4, 32, sn_360, hwid, wifi, bt, eth);
	uint32_t payload_len = sizeof(product_info);
	pack360_head(CMD_SN, payload_len, send_buf);
	if (send_packet(send_buf, GET_360_SEND_LEN(send_buf)) < 0)
	{
		QMessageBox::critical(nullptr, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("USB发送错误！"), QMessageBox::Ok);
		usb_release();
		return;
	}

	if (get_response(0, send_buf, recv_buf) < 0)
	{
		QMessageBox::critical(nullptr, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("USB发送错误！"), QMessageBox::Ok);
		usb_release();
		return;
	}

	usb_release();

	if (recv_buf[3] == 1)
		QMessageBox::information(nullptr, QString::fromLocal8Bit("通过"), QString::fromLocal8Bit("SN写入通过！"), QMessageBox::Ok);
	if (recv_buf[3] == 0)
		QMessageBox::critical(nullptr, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("SN写入不通过"), QMessageBox::Ok);
}
