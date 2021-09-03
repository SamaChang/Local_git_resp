#include "DeviceInformation.h"
#include "packet.h"
#include "SNInformation.h"

DeviceInformation::DeviceInformation(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->setWindowTitle(QString::fromLocal8Bit("设备信息"));
	this->setWindowFlags(Qt::WindowCloseButtonHint);
	this->setWindowIcon(QIcon("./Logo.png"));
	buttonStyle(ui.pushButton, "./Button_Small.qss");
}

DeviceInformation::~DeviceInformation()
{
}

void DeviceInformation::on_pushButton_clicked()
{
	this->close();
	emit nextTest(true, 1);
	emit finishedInfo();
}
