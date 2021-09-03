#include "RunA.h"
#include "usb.h"
#include "def.h"
#include "packet.h"
#include <visa.h>
#include <visatype.h>
#include "SNInformation.h"
//#include "qmessagebox.h"

RunA::RunA(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->setWindowTitle(QString::fromLocal8Bit("开机运行电流测试"));
	this->setWindowFlags(Qt::WindowCloseButtonHint);
	this->setWindowIcon(QIcon("./Logo.png"));
	buttonStyle(ui.pushButton, "./Button_Small.qss");
	buttonStyle(ui.pushButton_2, "./Button_Small.qss");
	buttonStyle(ui.pushButton_3, "./Button.qss");
}

RunA::~RunA()
{
}

void RunA::on_pushButton_clicked()
{
	//saveLog(snInf, QString::fromLocal8Bit("开机运行电流"), "Pass");
	QDateTime time;
	QString currentTime = time.currentDateTime().toString("yyyy/MM/dd HH:mm:ss");
	writeCSV(snInf, NULL, "PASS", QString::number(1), currentTime, QString::fromLocal8Bit("开机运行电流"), "mA"/*NULL*/, NULL, NULL, NULL, NULL);
	this->close();
	emit nextTest(true, 27);
	emit finishedInfo();
}

void RunA::on_pushButton_2_clicked()
{
	//saveLog(snInf, QString::fromLocal8Bit("开机运行电流"), "Fail");
	QDateTime time;
	QString currentTime = time.currentDateTime().toString("yyyy/MM/dd HH:mm:ss");
	recordResult("FAIL");
	writeCSV(snInf, NULL, "FAIL", QString::number(1), currentTime, QString::fromLocal8Bit("开机运行电流"), "mA"/*NULL*/, NULL, NULL, NULL, NULL);
	this->close();
	emit nextTest(false, 27);
	emit finishedInfo();
}

void RunA::on_pushButton_3_clicked()
{
	ViStatus nReturnStatus = 0;                         // 保存返回数值
	ViSession rmSession = 0, pnInstrHandle;
	ViUInt32 retCnt = 0;
	//ViByte wrtBuf[MAX_SCPI_LENGTH];                     // 写缓冲区
	ViByte rdBuf[255];                      // 读缓冲区
	char buffer[255] = { 0 };
	nReturnStatus = viOpenDefaultRM(&rmSession);
	//nReturnStatus = viOpen(rmSession, "USB::0xFFFF::0x6300::802060092746810025::INSTR", VI_NULL, VI_NULL, &pnInstrHandle);  //工厂寄家设备
	nReturnStatus = viOpen(rmSession, "USB::0xFFFF::0x6300::602060010717020038::INSTR", VI_NULL, VI_NULL, &pnInstrHandle);  //工厂设备
	/*- Configure VISA Formatted I/O ----------------------------------------*/
	nReturnStatus = viSetAttribute(pnInstrHandle, VI_ATTR_TMO_VALUE, 5000);        // 设置超时
	nReturnStatus = viSetAttribute(pnInstrHandle, VI_ATTR_SUPPRESS_END_EN, VI_FALSE);        // 不发送终止符
	nReturnStatus = viSetAttribute(pnInstrHandle, VI_ATTR_SEND_END_EN, VI_FALSE);        // 不接收终止符

	nReturnStatus = viPrintf(pnInstrHandle, "system: remote\n");   //设置远程
	nReturnStatus = viPrintf(pnInstrHandle, "INSTrument CH1\n");   //设置通道
	nReturnStatus = viQueryf(pnInstrHandle, "MEASure:CURRent? \n", "%s", buffer);  //读取电流
	//nReturnStatus = viQueryf(pnInstrHandle, "MEASure:VOLTent? \n", "%s", buffer);  //读取电压
	float curr = atof(buffer);
	if (curr <= 0.5f)
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