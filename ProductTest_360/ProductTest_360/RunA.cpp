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
	this->setWindowTitle(QString::fromLocal8Bit("�������е�������"));
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
	//saveLog(snInf, QString::fromLocal8Bit("�������е���"), "Pass");
	QDateTime time;
	QString currentTime = time.currentDateTime().toString("yyyy/MM/dd HH:mm:ss");
	writeCSV(snInf, NULL, "PASS", QString::number(1), currentTime, QString::fromLocal8Bit("�������е���"), "mA"/*NULL*/, NULL, NULL, NULL, NULL);
	this->close();
	emit nextTest(true, 27);
	emit finishedInfo();
}

void RunA::on_pushButton_2_clicked()
{
	//saveLog(snInf, QString::fromLocal8Bit("�������е���"), "Fail");
	QDateTime time;
	QString currentTime = time.currentDateTime().toString("yyyy/MM/dd HH:mm:ss");
	recordResult("FAIL");
	writeCSV(snInf, NULL, "FAIL", QString::number(1), currentTime, QString::fromLocal8Bit("�������е���"), "mA"/*NULL*/, NULL, NULL, NULL, NULL);
	this->close();
	emit nextTest(false, 27);
	emit finishedInfo();
}

void RunA::on_pushButton_3_clicked()
{
	ViStatus nReturnStatus = 0;                         // ���淵����ֵ
	ViSession rmSession = 0, pnInstrHandle;
	ViUInt32 retCnt = 0;
	//ViByte wrtBuf[MAX_SCPI_LENGTH];                     // д������
	ViByte rdBuf[255];                      // ��������
	char buffer[255] = { 0 };
	nReturnStatus = viOpenDefaultRM(&rmSession);
	//nReturnStatus = viOpen(rmSession, "USB::0xFFFF::0x6300::802060092746810025::INSTR", VI_NULL, VI_NULL, &pnInstrHandle);  //�����ļ��豸
	nReturnStatus = viOpen(rmSession, "USB::0xFFFF::0x6300::602060010717020038::INSTR", VI_NULL, VI_NULL, &pnInstrHandle);  //�����豸
	/*- Configure VISA Formatted I/O ----------------------------------------*/
	nReturnStatus = viSetAttribute(pnInstrHandle, VI_ATTR_TMO_VALUE, 5000);        // ���ó�ʱ
	nReturnStatus = viSetAttribute(pnInstrHandle, VI_ATTR_SUPPRESS_END_EN, VI_FALSE);        // ��������ֹ��
	nReturnStatus = viSetAttribute(pnInstrHandle, VI_ATTR_SEND_END_EN, VI_FALSE);        // ��������ֹ��

	nReturnStatus = viPrintf(pnInstrHandle, "system: remote\n");   //����Զ��
	nReturnStatus = viPrintf(pnInstrHandle, "INSTrument CH1\n");   //����ͨ��
	nReturnStatus = viQueryf(pnInstrHandle, "MEASure:CURRent? \n", "%s", buffer);  //��ȡ����
	//nReturnStatus = viQueryf(pnInstrHandle, "MEASure:VOLTent? \n", "%s", buffer);  //��ȡ��ѹ
	float curr = atof(buffer);
	if (curr <= 0.5f)
	{
		QMessageBox::information(nullptr, QString::fromLocal8Bit("ͨ��"), QString::fromLocal8Bit("�ؼ�©��������ͨ����"), QMessageBox::Ok);

	}
	else
	{
		QMessageBox::critical(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("�ؼ�©�������Բ�ͨ��"), QMessageBox::Ok);

	}
	viClose(pnInstrHandle);
	viClose(rmSession);
}