#include "NetWork.h"
#include "usb.h"
#include "def.h"
#include "packet.h"
#include "qmessagebox.h"
#include <qprocess.h>
#include "SNInformation.h"
#include "TCP.h"

NetWork::NetWork(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->setWindowTitle(QString::fromLocal8Bit("网络设备测试"));
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
	//saveLog(snInf, QString::fromLocal8Bit("网络设备"), "Pass");
	QDateTime time;
	QString currentTime = time.currentDateTime().toString("yyyy/MM/dd HH:mm:ss");
	writeCSV(snInf, NULL, "PASS", QString::number(8), currentTime, QString::fromLocal8Bit("网络设备"), NULL, NULL, NULL, NULL, NULL);
	this->close();
	emit nextTest(true, 10);
	emit finishedInfo();
}

void NetWork::on_pushButton_2_clicked()
{
	//saveLog(snInf, QString::fromLocal8Bit("网络设备"), "Fail");
	QDateTime time;
	QString currentTime = time.currentDateTime().toString("yyyy/MM/dd HH:mm:ss");
	recordResult("FAIL");
	writeCSV(snInf, NULL, "FAIL", QString::number(8), currentTime, QString::fromLocal8Bit("网络设备"), NULL, NULL, NULL, NULL, NULL);
	this->close();
	emit nextTest(false, 10);
	emit finishedInfo();
}

void NetWork::on_pushButton_3_clicked()
{
	//uint8_t send_buf[BUF_SEND_LEN] = { 0 };
	//uint8_t recv_buf[BUF_RESERVE_LEN] = { 0 };
	////saveLog("232", QString::fromLocal8Bit("数据加密"), "Pass");
	//if (usb_initial() < 0)
	//{
	//	QMessageBox::critical(nullptr, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("USB初始化错误！"), QMessageBox::Ok);
	//	return;
	//}
	//uint32_t payload_len = sizeof(calibration_param);
	//pack360_head(CMD_NETWORK, payload_len, send_buf);   //加头
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
	pack360_head(CMD_NETWORK, payload_len, send_buf);   //加头
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


	QString remoteIP = ui.lineEdit->text();
	QProcess cmd(this);
	cmd.start("ping " + remoteIP);
	//标准ping
	while (cmd.waitForFinished(20) == false) {
		QByteArray out = cmd.readAllStandardOutput();
		if (!out.isEmpty()) {
			ui.textBrowser->append(QString::fromLocal8Bit(out));
			repaint();
		}
	}
	QByteArray out = cmd.readAllStandardOutput();
	ui.textBrowser->append(QString::fromLocal8Bit(out));
	//阻塞式
	//cmd.waitForFinished(-1);
	//QByteArray out = cmd.readAllStandardOutput();
	//ui.textBrowser->append(QString::fromLocal8Bit(out));
}
