#include "downA.h"
#include "usb.h"
#include "def.h"
#include "packet.h"
#include "qmessagebox.h"
#include <visa.h>
#include <visatype.h>
#include "SNInformation.h"

downA::downA(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->setWindowTitle(QString::fromLocal8Bit("关机漏电流测试"));
	this->setWindowFlags(Qt::WindowCloseButtonHint);
	this->setWindowIcon(QIcon("./Logo.png"));
	buttonStyle(ui.pushButton_2, "./Button.qss");
	buttonStyle(ui.pushButton, "./Button_Small.qss");
	buttonStyle(ui.pushButton_3, "./Button_Small.qss");
}

downA::~downA()
{
}

void downA::on_pushButton_clicked()
{
	//saveLog(snInf, QString::fromLocal8Bit("关机漏电流"), "Pass");
	QDateTime time;
	QString currentTime = time.currentDateTime().toString("yyyy/MM/dd HH:mm:ss");
	writeCSV(snInf, NULL, "PASS", QString::number(2), currentTime, QString::fromLocal8Bit("关机漏电流"), NULL, NULL, NULL, QString("%1").arg(curr), NULL);
	this->close();
	emit nextTest(true, 26);
	emit finishedInfo();
}

void downA::on_pushButton_3_clicked()
{
	//saveLog(snInf, QString::fromLocal8Bit("关机漏电流"), "Fail");
	QDateTime time;
	QString currentTime = time.currentDateTime().toString("yyyy/MM/dd HH:mm:ss");
	recordResult("FAIL");
	writeCSV(snInf, NULL, "FAIL", QString::number(2), currentTime, QString::fromLocal8Bit("关机漏电流"), NULL, NULL, NULL, QString("%1").arg(curr), NULL);
	this->close();
	emit nextTest(false, 26);
	emit finishedInfo();
}

void downA::on_pushButton_2_clicked()
{
	ViStatus nReturnStatus = 0;                         // 保存返回数值
	ViSession rmSession = 0, pnInstrHandle;
	ViUInt32 retCnt = 0;
	//ViByte wrtBuf[MAX_SCPI_LENGTH];                     // 写缓冲区
	ViByte rdBuf[255];                      // 读缓冲区
	char buffer[255] = { 0 };
	nReturnStatus = viOpenDefaultRM(&rmSession);
	//nReturnStatus = viOpen(rmSession, "USB::0xFFFF::0x6300::802060092746810025::INSTR", VI_NULL, VI_NULL, &pnInstrHandle);
	//nReturnStatus = viOpen(rmSession, "USB::0xFFFF::0x6300::602060010717020038::INSTR", VI_NULL, VI_NULL, &pnInstrHandle);
	nReturnStatus = viOpen(rmSession, "USB::0xFFFF::0x6300::802060092746810016::INSTR", VI_NULL, VI_NULL, &pnInstrHandle);  //可以通过桌面的IT9000来获取此时的设备名

	if (nReturnStatus < 0)
	{
		QMessageBox::critical(nullptr, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("程控电源打开失败"), QMessageBox::Ok);
		viClose(pnInstrHandle);
		viClose(rmSession);
		return;
	}
	/*- Configure VISA Formatted I/O ----------------------------------------*/
	nReturnStatus = viSetAttribute(pnInstrHandle, VI_ATTR_TMO_VALUE, 5000);        // 设置超时
	nReturnStatus = viSetAttribute(pnInstrHandle, VI_ATTR_SUPPRESS_END_EN, VI_FALSE);        // 不发送终止符
	nReturnStatus = viSetAttribute(pnInstrHandle, VI_ATTR_SEND_END_EN, VI_FALSE);        // 不接收终止符

	nReturnStatus = viPrintf(pnInstrHandle, "system: remote\n");
	nReturnStatus = viPrintf(pnInstrHandle, "INSTrument CH1\n");
	nReturnStatus = viQueryf(pnInstrHandle, "MEASure:CURRent? \n", "%s", buffer);
	curr = atof(buffer);
	if (curr <= 0.004)
	{
		QMessageBox::information(nullptr, QString::fromLocal8Bit("通过"), QString::fromLocal8Bit("关键漏电流测试通过！"), QMessageBox::Ok);

	}
	else
	{
		QMessageBox::critical(nullptr, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("关键漏电流测试不通过"), QMessageBox::Ok);

	}

	viClose(pnInstrHandle);
	viClose(rmSession);
}