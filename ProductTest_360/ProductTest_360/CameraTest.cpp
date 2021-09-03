#include "CameraTest.h"
#include "usb.h"
#include "def.h"
#include "packet.h"
#include "qmessagebox.h"
#include "SNInformation.h"

CameraTest::CameraTest(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->setWindowTitle(QString::fromLocal8Bit("摄像头测试"));
	this->setWindowFlags(Qt::WindowCloseButtonHint);
	this->setWindowIcon(QIcon("./Logo.png"));
	buttonStyle(ui.pushButton, "./Button_Small.qss");
	buttonStyle(ui.pushButton_2, "./Button_Small.qss");
	buttonStyle(ui.pushButton_3, "./Button.qss");
	buttonStyle(ui.pushButton_4, "./Button.qss");
}

CameraTest::~CameraTest()
{
}

void CameraTest::on_pushButton_clicked()
{
	uint8_t send_buf[BUF_SEND_LEN] = { 0 };
	uint8_t recv_buf[BUF_RESERVE_LEN] = { 0 };
	//saveLog("232", QString::fromLocal8Bit("摄像头"), "Pass");
	if (usb_initial() < 0)
	{
		QMessageBox::critical(nullptr, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("USB初始化错误！"), QMessageBox::Ok);
		return;
	}
	uint32_t payload_len = sizeof(calibration_param);
	pack360_head(CMD_CAMERA, payload_len, send_buf);   //加头
	pcak360_buffer(send_buf + sizeof(send_360Protocol), SEVENTH);  //加头后面数据，关摄像头
	if (send_packet(send_buf, GET_360_SEND_LEN(send_buf)) < 0)
	{
		QMessageBox::critical(nullptr, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("USB发送错误！"), QMessageBox::Ok);
		usb_release();
		return;
	}
	if (get_response(0, send_buf, recv_buf) < 0)
	{
		QMessageBox::critical(nullptr, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("USB接收错误"), QMessageBox::Ok);
		usb_release();
		return;
	}

	usb_release();
	//saveLog(snInf, QString::fromLocal8Bit("摄像头"), "Pass");
	QDateTime time;
	QString currentTime = time.currentDateTime().toString("yyyy/MM/dd HH:mm:ss");
	writeCSV(snInf, NULL, "PASS", QString::number(3), currentTime, QString::fromLocal8Bit("摄像头"), NULL, NULL, NULL, NULL, NULL);
	this->close();
	emit nextTest(true, 6);
	emit finishedInfo();
}

void CameraTest::on_pushButton_2_clicked()
{
	uint8_t send_buf[BUF_SEND_LEN] = { 0 };
	uint8_t recv_buf[BUF_RESERVE_LEN] = { 0 };
	//saveLog("232", QString::fromLocal8Bit("摄像头"), "Pass");
	if (usb_initial() < 0)
	{
		QMessageBox::critical(nullptr, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("USB初始化错误！"), QMessageBox::Ok);
		return;
	}
	uint32_t payload_len = sizeof(calibration_param);
	pack360_head(CMD_CAMERA, payload_len, send_buf);   //加头
	pcak360_buffer(send_buf + sizeof(send_360Protocol), SEVENTH);  //加头后面数据，关摄像头
	if (send_packet(send_buf, GET_360_SEND_LEN(send_buf)) < 0)
	{
		QMessageBox::critical(nullptr, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("USB发送错误！"), QMessageBox::Ok);
		usb_release();
		return;
	}
	if (get_response(0, send_buf, recv_buf) < 0)
	{
		QMessageBox::critical(nullptr, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("USB接收错误"), QMessageBox::Ok);
		usb_release();
		return;
	}

	usb_release();
	//saveLog(snInf, QString::fromLocal8Bit("摄像头"), "Fail");
	QDateTime time;
	QString currentTime = time.currentDateTime().toString("yyyy/MM/dd HH:mm:ss");
	recordResult("FAIL");
	writeCSV(snInf, NULL, "FAIL", QString::number(3), currentTime, QString::fromLocal8Bit("摄像头"), NULL, NULL, NULL, NULL, NULL);
	this->close();
	emit nextTest(false, 6);
	emit finishedInfo();
}
//RGB
void CameraTest::on_pushButton_3_clicked()
{
	uint8_t send_buf[BUF_SEND_LEN] = { 0 };
	uint8_t recv_buf[BUF_RESERVE_LEN] = { 0 };
	//saveLog("232", QString::fromLocal8Bit("摄像头"), "Pass");
	if (usb_initial() < 0)
	{
		QMessageBox::critical(nullptr, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("USB初始化错误！"), QMessageBox::Ok);
		return;
	}
	uint32_t payload_len = sizeof(calibration_param);
	pack360_head(CMD_CAMERA, payload_len, send_buf);   //加头
	pcak360_buffer(send_buf + sizeof(send_360Protocol), FIRST);  //加头后面数据
	if (send_packet(send_buf, GET_360_SEND_LEN(send_buf)) < 0)
	{
		QMessageBox::critical(nullptr, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("USB发送错误！"), QMessageBox::Ok);
		usb_release();
		return;
	}
	if (get_response(0, send_buf, recv_buf) < 0)
	{
		QMessageBox::critical(nullptr, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("USB接收错误"), QMessageBox::Ok);
		usb_release();
		return;
	}

	usb_release();
}
//IR
void CameraTest::on_pushButton_4_clicked()
{
	uint8_t send_buf[BUF_SEND_LEN] = { 0 };
	uint8_t recv_buf[BUF_RESERVE_LEN] = { 0 };
	//saveLog("232", QString::fromLocal8Bit("摄像头"), "Pass");
	if (usb_initial() < 0)
	{
		QMessageBox::critical(nullptr, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("USB初始化错误！"), QMessageBox::Ok);
		return;
	}
	uint32_t payload_len = sizeof(calibration_param);
	pack360_head(CMD_CAMERA, payload_len, send_buf);   //加头
	pcak360_buffer(send_buf + sizeof(send_360Protocol), SECOND);  //加头后面数据
	if (send_packet(send_buf, GET_360_SEND_LEN(send_buf)) < 0)
	{
		QMessageBox::critical(nullptr, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("USB发送错误！"), QMessageBox::Ok);
		usb_release();
		return;
	}
	if (get_response(0, send_buf, recv_buf) < 0)
	{
		QMessageBox::critical(nullptr, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("USB接收错误"), QMessageBox::Ok);
		usb_release();
		return;
	}

	usb_release();
}
