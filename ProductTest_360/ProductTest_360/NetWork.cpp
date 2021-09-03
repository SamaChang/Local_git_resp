#include "NetWork.h"
#include "usb.h"
#include "def.h"
#include "packet.h"
#include "qmessagebox.h"
#include <qprocess.h>
#include "SNInformation.h"

NetWork::NetWork(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->setWindowTitle(QString::fromLocal8Bit("�����豸����"));
	this->setWindowFlags(Qt::WindowCloseButtonHint);
	this->setWindowIcon(QIcon("./Logo.png"));
	buttonStyle(ui.pushButton, "./Button_Small.qss");
	buttonStyle(ui.pushButton_2, "./Button_Small.qss");
	buttonStyle(ui.pushButton_3, "./Button.qss");
}

NetWork::~NetWork()
{
}

void NetWork::on_pushButton_clicked()
{
	//saveLog(snInf, QString::fromLocal8Bit("�����豸"), "Pass");
	QDateTime time;
	QString currentTime = time.currentDateTime().toString("yyyy/MM/dd HH:mm:ss");
	writeCSV(snInf, NULL, "PASS", QString::number(5), currentTime, QString::fromLocal8Bit("�����豸"), NULL, NULL, NULL, NULL, NULL);
	this->close();
	emit nextTest(true, 10);
	emit finishedInfo();
}

void NetWork::on_pushButton_2_clicked()
{
	//saveLog(snInf, QString::fromLocal8Bit("�����豸"), "Fail");
	QDateTime time;
	QString currentTime = time.currentDateTime().toString("yyyy/MM/dd HH:mm:ss");
	recordResult("FAIL");
	writeCSV(snInf, NULL, "FAIL", QString::number(5), currentTime, QString::fromLocal8Bit("�����豸"), NULL, NULL, NULL, NULL, NULL);
	this->close();
	emit nextTest(false, 10);
	emit finishedInfo();
}

void NetWork::on_pushButton_3_clicked()
{
	uint8_t send_buf[BUF_SEND_LEN] = { 0 };
	uint8_t recv_buf[BUF_RESERVE_LEN] = { 0 };
	//saveLog("232", QString::fromLocal8Bit("���ݼ���"), "Pass");
	if (usb_initial() < 0)
	{
		QMessageBox::critical(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("USB��ʼ������"), QMessageBox::Ok);
		return;
	}
	uint32_t payload_len = sizeof(calibration_param);
	pack360_head(CMD_NETWORK, payload_len, send_buf);   //��ͷ
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


	QString remoteIP = ui.lineEdit->text();
	QProcess cmd(this);
	cmd.start("ping " + remoteIP);
	//��׼ping
	while (cmd.waitForFinished(20) == false) {
		QByteArray out = cmd.readAllStandardOutput();
		if (!out.isEmpty()) {
			ui.textBrowser->append(QString::fromLocal8Bit(out));
			repaint();
		}
	}
	QByteArray out = cmd.readAllStandardOutput();
	ui.textBrowser->append(QString::fromLocal8Bit(out));
	//����ʽ
	//cmd.waitForFinished(-1);
	//QByteArray out = cmd.readAllStandardOutput();
	//ui.textBrowser->append(QString::fromLocal8Bit(out));
}
