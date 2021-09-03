#pragma once

#include <QWidget>
#include "ui_ChoosePro.h"
#include "DeviceInformation.h"
#include "downA.h"
#include "RunA.h"
#include "SN.h"
#include "CameraTest.h"
#include "LED.h"
#include "BTAndWifi.h"
#include "Sensor.h"
#include "MicAndSpeaker.h"
#include "NetWork.h"
#include "DataCode.h"
#include "PreventRemove.h"
#include "LCD.h"
#include "Warn.h"
#include "Wgen.h"
#include "UsbPro.h"
#include "Uart.h"
#include "IRLamp.h"
#include "GPIO.h"
#include "RTC.h"
#include "BlueTooth.h"

class ChoosePro : public QWidget
{
	Q_OBJECT

public:
	ChoosePro(QWidget *parent = Q_NULLPTR);
	~ChoosePro();
	//QVector<QCheckBox *>testVector;
private:
	Ui::ChoosePro ui;
	DeviceInformation *dInfo;
	downA *Adown;
	RunA *runA;
	SN *sn;
	CameraTest *camera;
	LED *led;
	BTAndWifi *btAndWifi;
	Sensor *sensor;
	MicAndSpeaker *micAndSpeaker;
	NetWork *netWork;
	DataCode *dataCode;
	PreventRemove *preventRemove;
	LCD *lcd;
	Warn *warn;
	Wgen *wgen;
	UsbPro *usb;
	Uart *uart;
	IRLamp *irLamp;
	GPIO *gpio;
	RTC *rtc;
	BlueTooth *blueTooth;
	void pointNull();
	void unA();   //关机漏电测试
	void deviceInfo(/*QCheckBox *box*/);  //设备信息检测
	void runningA();   //开机电流测试
	void writeSN();    //写SN
	void cameraTest();   //摄像头检测
	void ledTest();    //LED检测
	void btAndWifiTest();    //蓝牙/wifi检测
	void sensorTest();   //光感测试
	void micAndSpeakerTest();  //Mic/Speaker检测
	void netWorkTest();
	void dataCodeTest();
	void preventRemoveTest();
	void lcdTest();
	void warnTest();
	void wgenTest();
	void usbTest();
	void uartTest();
	void irLampTest();
	void gpioTest();
	void rtcTest();
	void blueToothTest();
private slots:
	void mainForm();
	void SecletAll();
	void startTest();
	void foreachTest(bool judge,int index);
signals:
	void testForm();
	void showTest(/*QCheckBox *box*/);
};
