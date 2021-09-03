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
	this->setWindowTitle(QString::fromLocal8Bit("�ػ�©��������"));
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
	//saveLog(snInf, QString::fromLocal8Bit("�ػ�©����"), "Pass");
	QDateTime time;
	QString currentTime = time.currentDateTime().toString("yyyy/MM/dd HH:mm:ss");
	writeCSV(snInf, NULL, "PASS", QString::number(2), currentTime, QString::fromLocal8Bit("�ػ�©����"), NULL, NULL, NULL, QString("%1").arg(curr), NULL);
	this->close();
	emit nextTest(true, 26);
	emit finishedInfo();
}

void downA::on_pushButton_3_clicked()
{
	//saveLog(snInf, QString::fromLocal8Bit("�ػ�©����"), "Fail");
	QDateTime time;
	QString currentTime = time.currentDateTime().toString("yyyy/MM/dd HH:mm:ss");
	recordResult("FAIL");
	writeCSV(snInf, NULL, "FAIL", QString::number(2), currentTime, QString::fromLocal8Bit("�ػ�©����"), NULL, NULL, NULL, QString("%1").arg(curr), NULL);
	this->close();
	emit nextTest(false, 26);
	emit finishedInfo();
}

void downA::on_pushButton_2_clicked()
{
	ViStatus nReturnStatus = 0;                         // ���淵����ֵ
	ViSession rmSession = 0, pnInstrHandle;
	ViUInt32 retCnt = 0;
	//ViByte wrtBuf[MAX_SCPI_LENGTH];                     // д������
	ViByte rdBuf[255];                      // ��������
	char buffer[255] = { 0 };
	nReturnStatus = viOpenDefaultRM(&rmSession);
	//nReturnStatus = viOpen(rmSession, "USB::0xFFFF::0x6300::802060092746810025::INSTR", VI_NULL, VI_NULL, &pnInstrHandle);
	//nReturnStatus = viOpen(rmSession, "USB::0xFFFF::0x6300::602060010717020038::INSTR", VI_NULL, VI_NULL, &pnInstrHandle);
	nReturnStatus = viOpen(rmSession, "USB::0xFFFF::0x6300::802060092746810016::INSTR", VI_NULL, VI_NULL, &pnInstrHandle);  //����ͨ�������IT9000����ȡ��ʱ���豸��

	if (nReturnStatus < 0)
	{
		QMessageBox::critical(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("�̿ص�Դ��ʧ��"), QMessageBox::Ok);
		viClose(pnInstrHandle);
		viClose(rmSession);
		return;
	}
	/*- Configure VISA Formatted I/O ----------------------------------------*/
	nReturnStatus = viSetAttribute(pnInstrHandle, VI_ATTR_TMO_VALUE, 5000);        // ���ó�ʱ
	nReturnStatus = viSetAttribute(pnInstrHandle, VI_ATTR_SUPPRESS_END_EN, VI_FALSE);        // ��������ֹ��
	nReturnStatus = viSetAttribute(pnInstrHandle, VI_ATTR_SEND_END_EN, VI_FALSE);        // ��������ֹ��

	nReturnStatus = viPrintf(pnInstrHandle, "system: remote\n");
	nReturnStatus = viPrintf(pnInstrHandle, "INSTrument CH1\n");
	nReturnStatus = viQueryf(pnInstrHandle, "MEASure:CURRent? \n", "%s", buffer);
	curr = atof(buffer);
	if (curr <= 0.004)
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