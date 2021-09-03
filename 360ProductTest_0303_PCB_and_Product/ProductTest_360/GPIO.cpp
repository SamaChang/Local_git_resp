#include "GPIO.h"
#include "usb.h"
#include "def.h"
#include "packet.h"
#include "qmessagebox.h"
#include "SNInformation.h"

GPIO::GPIO(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

GPIO::~GPIO()
{
}
//Í¨¹ý
void GPIO::on_pushButton_clicked()
{
	QDateTime time;
	QString currentTime = time.currentDateTime().toString("yyyy/MM/dd HH:mm:ss");
	writeCSV(snInf, NULL, "PASS", QString::number(7), currentTime, QString::fromLocal8Bit("GPIO"), NULL, NULL, NULL, NULL, NULL);
	this->close();
	emit nextTest(true, 33);
	emit finishedInfo();
}
//Ê§°Ü
void GPIO::on_pushButton_2_clicked()
{
	QDateTime time;
	QString currentTime = time.currentDateTime().toString("yyyy/MM/dd HH:mm:ss");
	recordResult("FAIL");
	writeCSV(snInf, NULL, "FAIL", QString::number(7), currentTime, QString::fromLocal8Bit("GPIO"), NULL, NULL, NULL, NULL, NULL);
	this->close();
	emit nextTest(false, 33);
	emit finishedInfo();
}
