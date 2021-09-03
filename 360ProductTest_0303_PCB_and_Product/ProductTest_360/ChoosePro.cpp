#include "ChoosePro.h"
#include "packet.h"

ChoosePro::ChoosePro(QWidget *parent)
	: QWidget(parent), dInfo(nullptr), Adown(nullptr), runA(nullptr),sn(nullptr),
	camera(nullptr),led(nullptr),btAndWifi(nullptr),sensor(nullptr), micAndSpeaker(nullptr),
	netWork(nullptr), dataCode(nullptr), preventRemove(nullptr), lcd(nullptr),
	warn(nullptr),wgen(nullptr),usb(nullptr),uart(nullptr),irLamp(nullptr),gpio(nullptr)
	,rtc(nullptr), blueTooth(nullptr)
{
	ui.setupUi(this);
	this->setWindowTitle(QString::fromLocal8Bit("测试项"));
	//this->setWindowFlags(Qt::WindowCloseButtonHint);
	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(mainForm()));
	connect(ui.checkBox_25, SIGNAL(toggled(bool)), this, SLOT(SecletAll()));
	connect(ui.pushButton_2, SIGNAL(clicked()), this, SLOT(startTest()));
	dInfo = new DeviceInformation();
	Adown = new downA();
	runA = new RunA();
	sn = new SN();
	camera = new CameraTest();
	led = new LED();
	btAndWifi = new BTAndWifi();
	sensor = new Sensor();
	micAndSpeaker = new MicAndSpeaker();
	netWork = new NetWork();
	dataCode = new DataCode();
	preventRemove = new PreventRemove();
	lcd = new LCD();
	warn = new Warn();
	wgen = new Wgen();
	usb = new UsbPro();
	uart = new Uart();
	irLamp = new IRLamp();
	gpio = new GPIO();
	rtc = new RTC();
	blueTooth = new BlueTooth();
	connect(dInfo, SIGNAL(nextTest(bool, int)), this, SLOT(foreachTest(bool,int)));
	connect(Adown, SIGNAL(nextTest(bool, int)), this, SLOT(foreachTest(bool, int)));
	connect(runA, SIGNAL(nextTest(bool, int)), this, SLOT(foreachTest(bool, int)));
	connect(sn, SIGNAL(nextTest(bool, int)), this, SLOT(foreachTest(bool, int)));
	connect(camera, SIGNAL(nextTest(bool, int)), this, SLOT(foreachTest(bool, int)));
	connect(led, SIGNAL(nextTest(bool, int)), this, SLOT(foreachTest(bool, int)));
	connect(btAndWifi, SIGNAL(nextTest(bool, int)), this, SLOT(foreachTest(bool, int)));
	connect(sensor, SIGNAL(nextTest(bool, int)), this, SLOT(foreachTest(bool, int)));
	connect(micAndSpeaker, SIGNAL(nextTest(bool, int)), this, SLOT(foreachTest(bool, int)));
	connect(netWork, SIGNAL(nextTest(bool, int)), this, SLOT(foreachTest(bool, int)));
	connect(dataCode, SIGNAL(nextTest(bool, int)), this, SLOT(foreachTest(bool, int)));
	connect(preventRemove, SIGNAL(nextTest(bool, int)), this, SLOT(foreachTest(bool, int)));
	connect(lcd, SIGNAL(nextTest(bool, int)), this, SLOT(foreachTest(bool, int)));
	connect(warn, SIGNAL(nextTest(bool, int)), this, SLOT(foreachTest(bool, int)));
	connect(wgen, SIGNAL(nextTest(bool, int)), this, SLOT(foreachTest(bool, int)));
	connect(usb, SIGNAL(nextTest(bool, int)), this, SLOT(foreachTest(bool, int)));
	connect(uart, SIGNAL(nextTest(bool, int)), this, SLOT(foreachTest(bool, int)));
	connect(irLamp, SIGNAL(nextTest(bool, int)), this, SLOT(foreachTest(bool, int)));
	connect(gpio, SIGNAL(nextTest(bool, int)), this, SLOT(foreachTest(bool, int)));
	connect(rtc, SIGNAL(nextTest(bool, int)), this, SLOT(foreachTest(bool, int)));
	connect(blueTooth, SIGNAL(nextTest(bool, int)), this, SLOT(foreachTest(bool, int)));
	this->setWindowIcon(QIcon("./Logo.png"));
	buttonStyle(ui.pushButton, "./Button_Small.qss");
	buttonStyle(ui.pushButton_2, "./Button_Small.qss");
	QObjectList list = children();
	QCheckBox *box;
	foreach(QObject *obj, list)
	{
		box = qobject_cast<QCheckBox*>(obj);
		if (box)
		{
			checkStyle(box, "./CheckBox.qss");
		}
	}
	if (box != nullptr)
		box = nullptr;
	checkStyle(ui.checkBox_25, "./CheckBox.qss");

	ui.checkBox->setVisible(false);
	ui.checkBox_3->setVisible(false);
	ui.checkBox_4->setVisible(false);
	ui.checkBox_5->setVisible(false);
	ui.checkBox_8->setVisible(false);
	ui.checkBox_9->setVisible(false);
	ui.checkBox_11->setVisible(false);
	ui.checkBox_13->setVisible(false);
	ui.checkBox_12->setVisible(false);
	ui.checkBox_14->setVisible(false);
	ui.checkBox_15->setVisible(false);
	ui.checkBox_17->setVisible(false);
	//ui.checkBox_18->setVisible(false);
	ui.checkBox_19->setVisible(false);
	ui.checkBox_20->setVisible(false);
	//ui.checkBox_21->setVisible(false);
	ui.checkBox_22->setVisible(false);
	//ui.checkBox_24->setVisible(false);
	//ui.checkBox_29->setVisible(false);
	ui.checkBox_26->setVisible(false);
	//ui.checkBox_31->setVisible(false);
	ui.checkBox_33->setVisible(false);
}

ChoosePro::~ChoosePro()
{
	delete dInfo;
	if (dInfo != nullptr)
		dInfo = nullptr;
	delete Adown;
	if (Adown != nullptr)
		Adown = nullptr;
	delete runA;
	if (runA != nullptr)
		runA = nullptr;
	delete sn;
	if (sn != nullptr)
		sn = nullptr;
	delete camera;
	if (camera != nullptr)
		camera = nullptr;
	delete led;
	if (led != nullptr)
		led = nullptr;
	delete btAndWifi;
	if (btAndWifi != nullptr)
		btAndWifi = nullptr;
	delete sensor;
	if (sensor != nullptr)
		sensor = nullptr;
	delete micAndSpeaker;
	if (micAndSpeaker != nullptr)
		micAndSpeaker = nullptr;
	delete netWork;
	if (netWork != nullptr)
		netWork = nullptr;
	delete dataCode;
	if (dataCode != nullptr)
		dataCode = nullptr;
	delete preventRemove;
	if (preventRemove != nullptr)
		preventRemove = nullptr;
	delete lcd;
	if (lcd != nullptr)
		lcd = nullptr;
	delete warn;
	if (warn != nullptr)
		warn = nullptr;
	delete wgen;
	if (wgen != nullptr)
		wgen = nullptr;
	delete usb;
	if (usb != nullptr)
		usb = nullptr;
	delete uart;
	if (uart != nullptr)
		uart = nullptr;
	delete irLamp;
	if (irLamp != nullptr)
		irLamp = nullptr;
	delete gpio;
	if (gpio != nullptr)
		gpio = nullptr;
	delete rtc;
	if (rtc != nullptr)
		rtc = nullptr;
	delete blueTooth;
	if (blueTooth != nullptr)
		blueTooth = nullptr;
}

void ChoosePro::mainForm()
{
	this->close();
	emit testForm();
}

void ChoosePro::SecletAll()
{
	
	if (ui.checkBox_25->isChecked())
	{
		ui.checkBox_25->setText(QString::fromLocal8Bit("取消全选"));
		QObjectList list = children();
		QCheckBox *box;
		foreach(QObject *obj, list)
		{
			box = qobject_cast<QCheckBox*>(obj);
			if (box)
			{
				box->setChecked(true);
			}
		}
		if (box != nullptr)
			box = nullptr;
	}
	else
	{
		ui.checkBox_25->setText(QString::fromLocal8Bit("全选"));
		QObjectList list = children();
		QCheckBox *box;
		foreach(QObject *obj, list)
		{
			box = qobject_cast<QCheckBox*>(obj);
			if (box)
			{
				box->setChecked(false);
			}
		}
		if (box != nullptr)
			box = nullptr;
	}
	//loop->exec();
}


void ChoosePro::startTest()
{
	QObjectList list = children();
	QCheckBox *box;           //用智能指针或者释放
	//QVector<QCheckBox *> currentBox;
	foreach(QObject *obj, list)
	{
		box = qobject_cast<QCheckBox*>(obj);
		if (box)
		{
			if (box->isChecked())
			{
				//testVector.push_back(box);    //测试发现是按check创建的顺序存的，不是按照上下顺序存的
				if (/*testVector[count]*/box == ui.checkBox_26/* && box->styleSheet() != QString("background-color: rgb(0,255,127);")*/)
					unA();
				if (/*testVector[count]*/box == ui.checkBox_27/* && box->styleSheet() != QString("background-color: rgb(0,255,127);")*/)
					runningA();
				if (/*testVector[count]*/box == ui.checkBox_28/* && box->styleSheet() != QString("background-color: rgb(0,255,127);")*/)
					writeSN();
				if (/*testVector[count]*/box == ui.checkBox/* && box->styleSheet() != QString("background-color: rgb(0,255,127);")*/)
					deviceInfo();
				if (box == ui.checkBox_6/* && box->styleSheet() != QString("background-color: rgb(0,255,127);")*/)
					cameraTest();
				if (box == ui.checkBox_7/* && box->styleSheet() != QString("background-color: rgb(0,255,127);")*/)
					ledTest();
				if (box == ui.checkBox_29/* && box->styleSheet() != QString("background-color: rgb(0,255,127);")*/)
					btAndWifiTest();
				if (box == ui.checkBox_23/* && box->styleSheet() != QString("background-color: rgb(0,255,127);")*/)
					sensorTest();
				if (box == ui.checkBox_30/* && box->styleSheet() != QString("background-color: rgb(0,255,127);")*/)
					micAndSpeakerTest();
				if (box == ui.checkBox_10/* && box->styleSheet() != QString("background-color: rgb(0,255,127);")*/)
					netWorkTest();
				if (box == ui.checkBox_24/* && box->styleSheet() != QString("background-color: rgb(0,255,127);")*/)
					dataCodeTest();
				if (box == ui.checkBox_31/* && box->styleSheet() != QString("background-color: rgb(0,255,127);")*/)
					preventRemoveTest();
				if (box == ui.checkBox_2/* && box->styleSheet() != QString("background-color: rgb(0,255,127);")*/)
					lcdTest();
				if (box == ui.checkBox_21/* && box->styleSheet() != QString("background-color: rgb(0,255,127);")*/)
					warnTest();
				if (box == ui.checkBox_16/* && box->styleSheet() != QString("background-color: rgb(0,255,127);")*/)
					wgenTest();
				if (box == ui.checkBox_15/* && box->styleSheet() != QString("background-color: rgb(0,255,127);")*/)
					usbTest();
				if (box == ui.checkBox_18/* && box->styleSheet() != QString("background-color: rgb(0,255,127);")*/)
					uartTest();
				if (box == ui.checkBox_32)
					irLampTest();
				if (box == ui.checkBox_33)
					gpioTest();
				if (box == ui.checkBox_34)
					rtcTest();
				if (box == ui.checkBox_35)
					blueToothTest();
			}
		}
	}
	if (box != nullptr)
		box = nullptr;
}

//设备信息窗口
void ChoosePro::deviceInfo()
{
	this->hide();
	dInfo->show();
	QEventLoop loop;
	connect(dInfo, SIGNAL(finishedInfo()), &loop, SLOT(quit()));
	loop.exec();
}

void ChoosePro::unA()
{
	this->hide();
	Adown->show();
	QEventLoop loop;
	connect(Adown, SIGNAL(finishedInfo()), &loop, SLOT(quit()));
	loop.exec();
}

void ChoosePro::runningA()
{
	this->hide();
	runA->show();
	QEventLoop loop;
	connect(runA, SIGNAL(finishedInfo()), &loop, SLOT(quit()));
	loop.exec();
}

void ChoosePro::writeSN()
{
	this->hide();
	sn->show();
	QEventLoop loop;
	connect(sn, SIGNAL(finishedInfo()), &loop, SLOT(quit()));
	loop.exec();
}

void ChoosePro::cameraTest()
{
	this->hide();
	camera->show();
	QEventLoop loop;
	connect(camera, SIGNAL(finishedInfo()), &loop, SLOT(quit()));
	loop.exec();
}

void ChoosePro::ledTest()
{
	this->hide();
	led->show();
	QEventLoop loop;
	connect(led, SIGNAL(finishedInfo()), &loop, SLOT(quit()));
	loop.exec();
}

void ChoosePro::btAndWifiTest()
{
	this->hide();
	btAndWifi->show();
	QEventLoop loop;
	connect(btAndWifi, SIGNAL(finishedInfo()), &loop, SLOT(quit()));
	loop.exec();
}

void ChoosePro::sensorTest()
{
	this->hide();
	sensor->show();
	QEventLoop loop;
	connect(sensor, SIGNAL(finishedInfo()), &loop, SLOT(quit()));
	loop.exec();
}

void ChoosePro::micAndSpeakerTest()
{
	this->hide();
	micAndSpeaker->show();
	QEventLoop loop;
	connect(micAndSpeaker, SIGNAL(finishedInfo()), &loop, SLOT(quit()));
	loop.exec();
}

void ChoosePro::netWorkTest()
{
	this->hide();
	netWork->show();
	QEventLoop loop;
	connect(netWork, SIGNAL(finishedInfo()), &loop, SLOT(quit()));
	loop.exec();
}

void ChoosePro::dataCodeTest()
{
	this->hide();
	dataCode->show();
	QEventLoop loop;
	connect(dataCode, SIGNAL(finishedInfo()), &loop, SLOT(quit()));
	loop.exec();
}

void ChoosePro::preventRemoveTest()
{
	this->hide();
	preventRemove->show();
	QEventLoop loop;
	connect(preventRemove, SIGNAL(finishedInfo()), &loop, SLOT(quit()));
	loop.exec();
}

void ChoosePro::lcdTest()
{
	this->hide();
	lcd->show();
	QEventLoop loop;
	connect(lcd, SIGNAL(finishedInfo()), &loop, SLOT(quit()));
	loop.exec();
}

void ChoosePro::warnTest()
{
	this->hide();
	warn->show();
	QEventLoop loop;
	connect(warn, SIGNAL(finishedInfo()), &loop, SLOT(quit()));
	loop.exec();
}

void ChoosePro::wgenTest()
{
	this->hide();
	wgen->show();
	QEventLoop loop;
	connect(wgen, SIGNAL(finishedInfo()), &loop, SLOT(quit()));
	loop.exec();
}

void ChoosePro::usbTest()
{
	this->hide();
	usb->show();
	QEventLoop loop;
	connect(usb, SIGNAL(finishedInfo()), &loop, SLOT(quit()));
	loop.exec();
}

void ChoosePro::uartTest()
{
	this->hide();
	uart->show();
	QEventLoop loop;
	connect(uart, SIGNAL(finishedInfo()), &loop, SLOT(quit()));
	loop.exec();
}

void ChoosePro::irLampTest()
{
	this->hide();
	irLamp->show();
	QEventLoop loop;
	connect(irLamp, SIGNAL(finishedInfo()), &loop, SLOT(quit()));
	loop.exec();
}

void ChoosePro::gpioTest()
{
	this->hide();
	gpio->show();
	QEventLoop loop;
	connect(gpio, SIGNAL(finishedInfo()), &loop, SLOT(quit()));
	loop.exec();
}

void ChoosePro::rtcTest()
{
	this->hide();
	rtc->show();
	QEventLoop loop;
	connect(rtc, SIGNAL(finishedInfo()), &loop, SLOT(quit()));
	loop.exec();
}

void ChoosePro::blueToothTest()
{
	this->hide();
	blueTooth->show();
	QEventLoop loop;
	connect(blueTooth, SIGNAL(finishedInfo()), &loop, SLOT(quit()));
	loop.exec();
}

//通过的显示
void ChoosePro::foreachTest(bool judge,int index)
{
	if (index == 1)
	{
		if (judge)
			ui.checkBox->setStyleSheet(QString("background-color: rgb(0,255,127);"));
		else
			ui.checkBox->setStyleSheet(QString("background-color: rgb(255,0,0);"));
		ui.checkBox->setChecked(false);
	}
	if (index == 2)
	{
		if (judge)
			ui.checkBox_2->setStyleSheet(QString("background-color: rgb(0,255,127);"));
		else
			ui.checkBox_2->setStyleSheet(QString("background-color: rgb(255,0,0);"));
		ui.checkBox_2->setChecked(false);
	}
	if (index == 3)
	{
		if (judge)
			ui.checkBox_3->setStyleSheet(QString("background-color: rgb(0,255,127);"));
		else
			ui.checkBox_3->setStyleSheet(QString("background-color: rgb(255,0,0);"));
		ui.checkBox_3->setChecked(false);
	}
	if (index == 4)
	{
		if (judge)
			ui.checkBox_4->setStyleSheet(QString("background-color: rgb(0,255,127);"));
		else
			ui.checkBox_4->setStyleSheet(QString("background-color: rgb(255,0,0);"));
		ui.checkBox_4->setChecked(false);
	}
	if (index == 5)
	{
		if (judge)
			ui.checkBox_5->setStyleSheet(QString("background-color: rgb(0,255,127);"));
		else
			ui.checkBox_5->setStyleSheet(QString("background-color: rgb(255,0,0);"));
		ui.checkBox_5->setChecked(false);
	}
	if (index == 6)
	{
		if (judge)
			ui.checkBox_6->setStyleSheet(QString("background-color: rgb(0,255,127);"));
		else
			ui.checkBox_6->setStyleSheet(QString("background-color: rgb(255,0,0);"));
		ui.checkBox_6->setChecked(false);
	}
	if (index == 7)
	{
		if (judge)
			ui.checkBox_7->setStyleSheet(QString("background-color: rgb(0,255,127);"));
		else
			ui.checkBox_7->setStyleSheet(QString("background-color: rgb(255,0,0);"));
		ui.checkBox_7->setChecked(false);
	}
	if (index == 8)
	{
		if (judge)
			ui.checkBox_8->setStyleSheet(QString("background-color: rgb(0,255,127);"));
		else
			ui.checkBox_8->setStyleSheet(QString("background-color: rgb(255,0,0);"));
		ui.checkBox_8->setChecked(false);
	}
	if (index == 9)
	{
		if (judge)
			ui.checkBox_9->setStyleSheet(QString("background-color: rgb(0,255,127);"));
		else
			ui.checkBox_9->setStyleSheet(QString("background-color: rgb(255,0,0);"));
		ui.checkBox_9->setChecked(false);
	}
	if (index == 10)
	{
		if (judge)
			ui.checkBox_10->setStyleSheet(QString("background-color: rgb(0,255,127);"));
		else
			ui.checkBox_10->setStyleSheet(QString("background-color: rgb(255,0,0);"));
		ui.checkBox_10->setChecked(false);
	}
	if (index == 11)
	{
		if (judge)
			ui.checkBox_11->setStyleSheet(QString("background-color: rgb(0,255,127);"));
		else
			ui.checkBox_11->setStyleSheet(QString("background-color: rgb(255,0,0);"));
		ui.checkBox_11->setChecked(false);
	}
	if (index == 12)
	{
		if (judge)
			ui.checkBox_12->setStyleSheet(QString("background-color: rgb(0,255,127);"));
		else
			ui.checkBox_12->setStyleSheet(QString("background-color: rgb(255,0,0);"));
		ui.checkBox_12->setChecked(false);
	}
	if (index == 13)
	{
		if (judge)
			ui.checkBox_13->setStyleSheet(QString("background-color: rgb(0,255,127);"));
		else
			ui.checkBox_13->setStyleSheet(QString("background-color: rgb(255,0,0);"));
		ui.checkBox_13->setChecked(false);
	}
	if (index == 14)
	{
		if (judge)
			ui.checkBox_14->setStyleSheet(QString("background-color: rgb(0,255,127);"));
		else
			ui.checkBox_14->setStyleSheet(QString("background-color: rgb(255,0,0);"));
		ui.checkBox_14->setChecked(false);
	}
	if (index == 15)
	{
		if (judge)
			ui.checkBox_15->setStyleSheet(QString("background-color: rgb(0,255,127);"));
		else
			ui.checkBox_15->setStyleSheet(QString("background-color: rgb(255,0,0);"));
		ui.checkBox_15->setChecked(false);
	}
	if (index == 16)
	{
		if (judge)
			ui.checkBox_16->setStyleSheet(QString("background-color: rgb(0,255,127);"));
		else
			ui.checkBox_16->setStyleSheet(QString("background-color: rgb(255,0,0);"));
		ui.checkBox_16->setChecked(false);
	}
	if (index == 17)
	{
		if (judge)
			ui.checkBox_17->setStyleSheet(QString("background-color: rgb(0,255,127);"));
		else
			ui.checkBox_17->setStyleSheet(QString("background-color: rgb(255,0,0);"));
		ui.checkBox_17->setChecked(false);
	}
	if (index == 18)
	{
		if (judge)
			ui.checkBox_18->setStyleSheet(QString("background-color: rgb(0,255,127);"));
		else
			ui.checkBox_18->setStyleSheet(QString("background-color: rgb(255,0,0);"));
		ui.checkBox_18->setChecked(false);
	}
	if (index == 19)
	{
		if (judge)
			ui.checkBox_19->setStyleSheet(QString("background-color: rgb(0,255,127);"));
		else
			ui.checkBox_19->setStyleSheet(QString("background-color: rgb(255,0,0);"));
		ui.checkBox_19->setChecked(false);

	}
	if (index == 20)
	{
		if (judge)
			ui.checkBox_20->setStyleSheet(QString("background-color: rgb(0,255,127);"));
		else
			ui.checkBox_20->setStyleSheet(QString("background-color: rgb(255,0,0);"));
		ui.checkBox_20->setChecked(false);
	}
	if (index == 21)
	{
		if (judge)
			ui.checkBox_21->setStyleSheet(QString("background-color: rgb(0,255,127);"));
		else
			ui.checkBox_21->setStyleSheet(QString("background-color: rgb(255,0,0);"));
		ui.checkBox_21->setChecked(false);
	}
	if (index == 22)
	{
		if (judge)
			ui.checkBox_22->setStyleSheet(QString("background-color: rgb(0,255,127);"));
		else
			ui.checkBox_22->setStyleSheet(QString("background-color: rgb(255,0,0);"));
		ui.checkBox_22->setChecked(false);
	}
	if (index == 23)
	{
		if (judge)
			ui.checkBox_23->setStyleSheet(QString("background-color: rgb(0,255,127);"));
		else
			ui.checkBox_23->setStyleSheet(QString("background-color: rgb(255,0,0);"));
		ui.checkBox_23->setChecked(false);
	}
	if (index == 24)
	{
		if (judge)
			ui.checkBox_24->setStyleSheet(QString("background-color: rgb(0,255,127);"));
		else
			ui.checkBox_24->setStyleSheet(QString("background-color: rgb(255,0,0);"));
		ui.checkBox_24->setChecked(false);
	}
	if (index == 25)
	{
		if (judge)
			ui.checkBox_25->setStyleSheet(QString("background-color: rgb(0,255,127);"));
		else
			ui.checkBox_25->setStyleSheet(QString("background-color: rgb(255,0,0);"));
		ui.checkBox_25->setChecked(false);
	}
	if (index == 26)
	{
		if (judge)
			ui.checkBox_26->setStyleSheet(QString("background-color: rgb(0,255,127);"));
		else
			ui.checkBox_26->setStyleSheet(QString("background-color: rgb(255,0,0);"));
		ui.checkBox_26->setChecked(false);
	}
	if (index == 27)
	{
		if (judge)
			ui.checkBox_27->setStyleSheet(QString("background-color: rgb(0,255,127);"));
		else
			ui.checkBox_27->setStyleSheet(QString("background-color: rgb(255,0,0);"));
		ui.checkBox_27->setChecked(false);
	}
	if (index == 28)
	{
		if (judge)
			ui.checkBox_28->setStyleSheet(QString("background-color: rgb(0,255,127);"));
		else
			ui.checkBox_28->setStyleSheet(QString("background-color: rgb(255,0,0);"));
		ui.checkBox_28->setChecked(false);
	}
	if (index == 29)
	{
		if (judge)
			ui.checkBox_29->setStyleSheet(QString("background-color: rgb(0,255,127);"));
		else
			ui.checkBox_29->setStyleSheet(QString("background-color: rgb(255,0,0);"));
		ui.checkBox_29->setChecked(false);
	}
	if (index == 30)
	{
		if (judge)
			ui.checkBox_30->setStyleSheet(QString("background-color: rgb(0,255,127);"));
		else
			ui.checkBox_30->setStyleSheet(QString("background-color: rgb(255,0,0);"));
		ui.checkBox_30->setChecked(false);
	}
	if (index == 31)
	{
		if (judge)
			ui.checkBox_31->setStyleSheet(QString("background-color: rgb(0,255,127);"));
		else
			ui.checkBox_31->setStyleSheet(QString("background-color: rgb(255,0,0);"));
		ui.checkBox_31->setChecked(false);
	}
	if (index == 32)
	{
		if (judge)
			ui.checkBox_32->setStyleSheet(QString("background-color: rgb(0,255,127);"));
		else
			ui.checkBox_32->setStyleSheet(QString("background-color: rgb(255,0,0);"));
		ui.checkBox_32->setChecked(false);
	}
	if (index == 33)
	{
		if (judge)
			ui.checkBox_33->setStyleSheet(QString("background-color: rgb(0,255,127);"));
		else
			ui.checkBox_33->setStyleSheet(QString("background-color: rgb(255,0,0);"));
		ui.checkBox_33->setChecked(false);
	}
	if (index == 34)
	{
		if (judge)
			ui.checkBox_34->setStyleSheet(QString("background-color: rgb(0,255,127);"));
		else
			ui.checkBox_34->setStyleSheet(QString("background-color: rgb(255,0,0);"));
		ui.checkBox_34->setChecked(false);
	}
	if (index == 35)
	{
		if (judge)
			ui.checkBox_35->setStyleSheet(QString("background-color: rgb(0,255,127);"));
		else
			ui.checkBox_35->setStyleSheet(QString("background-color: rgb(255,0,0);"));
		ui.checkBox_35->setChecked(false);
	}
	this->show();
}


