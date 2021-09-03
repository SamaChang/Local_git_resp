#include "SLTTestDemo.h"
#include <QtCore/QtCore>
#include <qmessagebox.h>
#include <qfiledialog.h>
#include "packet.h"
#include <Windows.h>
#define REQUEST_SRQ -1   //�ȴ�GPIB�¼���ʱ,����

SLTTestDemo::SLTTestDemo(QWidget *parent)
    : QWidget(parent)/*, setting(nullptr)*/, m_serialPort1(nullptr), m_serialPort2(nullptr), 
	m_serialPort3(nullptr), m_serialPort4(nullptr), t1(nullptr),t2(nullptr)
	,t3(nullptr),t4(nullptr), stopThread1(false), stopThread2(false), stopThread3(false), stopThread4(false), 
	isComplete1(false),isComplete2(false),isComplete3(false), isComplete4(false), stopAutoTest(true), 
	closeControl(true), tControl(nullptr), m_timer4(nullptr), m_timer1(nullptr), m_timer2(nullptr), m_timer3(nullptr)
	, /*timerFlag(true),*/bin_good_1(false), bin_good_2(false),bin_good_3(false), bin_good_4(false), set_gpib(nullptr)
{
    ui.setupUi(this);
	this->setWindowTitle("SLTV_1.84");
	this->setWindowIcon(QIcon("./Logo.png"));
	set_gpib = new GPIBSet();   //�Ȳ����˹���

	m_timer1 = new QTimer(/*this*/);   //�����ﴴ������isActive�Ͳ����Ҹı���
	m_timer2 = new QTimer(/*this*/);
	m_timer3 = new QTimer(/*this*/);
	m_timer4 = new QTimer(/*this*/);
	connect(m_timer1, SIGNAL(timeout()), this, SLOT(timeRun1(/*QSerialPort **/))/*, Qt::DirectConnection*/);   //�ŵ�����Ͳ���Ҫ��ΰ󶨣���δ����ۺ�����(����һ���źŻ᲻�ᴥ����������)
	connect(m_timer2, SIGNAL(timeout()), this, SLOT(timeRun2(/*QSerialPort **/)));  
	connect(m_timer3, SIGNAL(timeout()), this, SLOT(timeRun3(/*QSerialPort **/))/*, Qt::DirectConnection*/);
	connect(m_timer4, SIGNAL(timeout()), this, SLOT(timeRun4(/*QSerialPort **/))); 

	m_serialPort1 = new QSerialPort();//ʵ����������һ������
	m_serialPort2 = new QSerialPort();//ʵ����������һ������
	m_serialPort3 = new QSerialPort();//ʵ����������һ������
	m_serialPort4 = new QSerialPort();//ʵ����������һ������
	initSerialPort(/*m_serialPort1*/);
	//initSerialPort(/*m_serialPort2*/);
	//initSerialPort(/*m_serialPort3*/);
	//initSerialPort(/*m_serialPort4*/);
	//����Ĭ�������ļ�
	setTableWidget(ui.tableWidget);
	setTableWidget(ui.tableWidget_2);
	setTableWidget(ui.tableWidget_3);
	setTableWidget(ui.tableWidget_4);

	ui.tableWidget->horizontalHeader()->setStretchLastSection(true);   //�������һ���Զ��������
	ui.tableWidget_2->horizontalHeader()->setStretchLastSection(true);
	ui.tableWidget_3->horizontalHeader()->setStretchLastSection(true);
	ui.tableWidget_4->horizontalHeader()->setStretchLastSection(true);
	

	QDateTime q_date_time;
	time_creatFile = q_date_time.currentDateTime().toString("yyyyMMdd_HHmmss");
	recordLog("SerialPort1");
	recordLog("SerialPort2");
	recordLog("SerialPort3");
	recordLog("SerialPort4");

	saveCSVFlie();  //����excel���
	creatPassRate();  //���������ļ�

	connect(m_serialPort1, SIGNAL(readyRead(/*int i*/)), this, SLOT(receiveInfo1()));
	connect(m_serialPort2, SIGNAL(readyRead(/*int i*/)), this, SLOT(receiveInfo2()));
	connect(m_serialPort3, SIGNAL(readyRead(/*int i*/)), this, SLOT(receiveInfo3()));
	connect(m_serialPort4, SIGNAL(readyRead(/*int i*/)), this, SLOT(receiveInfo4()));

	connect(this, SIGNAL(runT1()), this, SLOT(qtimerRun1()));
	connect(this, SIGNAL(runT2()), this, SLOT(qtimerRun2()));
	connect(this, SIGNAL(runT3()), this, SLOT(qtimerRun3()));
	connect(this, SIGNAL(runT4()), this, SLOT(qtimerRun4()));

	ui.lcdNumber->setMode(QLCDNumber::Dec);
	ui.lcdNumber->setSegmentStyle(QLCDNumber::Flat);
	ui.lcdNumber->setStyleSheet("border: 1px solid green; color: green; background: silver;");
	ui.lcdNumber_2->setMode(QLCDNumber::Dec);
	ui.lcdNumber_2->setSegmentStyle(QLCDNumber::Flat);
	ui.lcdNumber_2->setStyleSheet("border: 1px solid green; color: green; background: silver;");
	ui.lcdNumber_3->setMode(QLCDNumber::Dec);
	ui.lcdNumber_3->setSegmentStyle(QLCDNumber::Flat);
	ui.lcdNumber_3->setStyleSheet("border: 1px solid green; color: green; background: silver;");

	connect(this, SIGNAL(updateUI()), this, SLOT(lcdCount()));
	//connect(this, SIGNAL(finishedInfo1()), &loop1, SLOT(quit()));
	//connect(this, SIGNAL(finishedInfo2()), &loop2, SLOT(quit()));
	//connect(this, SIGNAL(finishedInfo3()), &loop3, SLOT(quit()));
	//connect(this, SIGNAL(finishedInfo4()), &loop4, SLOT(quit()));

	connect(this, SIGNAL(pushButton_3_disable()), this, SLOT(pushbutton3disable()));

	//connect(set_gpib, SIGNAL(send_gpib(QString)), this, SLOT(getGPIB_name(QString)));   //�Ȳ����˹���
}

static int serial1_cmd;
static int serial2_cmd;
static int serial3_cmd;
static int serial4_cmd;

static int chipID1;
static int chipID2;
static int chipID3;
static int chipID4;

static float allChipCount = 0;  //����оƬ����
static float failedChipCount = 0;  //ʧ��оƬ��

static char instrDescriptor[VI_FIND_BUFLEN];
static ViUInt32 numInstrs;
static ViFindList findList;
static ViSession defaultRM, instr;
static ViStatus status;
static ViEventType etype;
static ViEvent ehandle;
static ViUInt16 statusByte;   //SRQ:0x41
//char buffer[255] = { 0 };

SLTTestDemo::~SLTTestDemo()
{
	//timerFlag = false;
	//if (set_gpib != nullptr)
	//{
	//	delete set_gpib;
	//	set_gpib = nullptr;
	//}

	

	//emit fini1();
	//emit fini2();
	//emit fini3();
	//emit fini4();
	stopSerialPort(m_serialPort1,t1);
	stopSerialPort(m_serialPort2,t2);
	stopSerialPort(m_serialPort3,t3);
	stopSerialPort(m_serialPort4,t4);
	stopQtimer(m_timer1);
	stopQtimer(m_timer2);
	stopQtimer(m_timer3);
	stopQtimer(m_timer4);

	viClose(ehandle);
	viClose(instr);
	viClose(defaultRM);
}

//QVariant SLTTestDemo::getSetting(QString qstrnodename, QString qstrkeyname)
//{
//	QVariant qvar = setting->value(QString("/%1/%2").arg(qstrnodename).arg(qstrkeyname));
//	return qvar;
//}

//void SLTTestDemo::getGPIB_name(QString str)
//{
//	gpib_name = str;
//}

//����GPIB�豸
int SLTTestDemo::findRsrc()
{
	//static char instrDescriptor[VI_FIND_BUFLEN];
	//static ViUInt32 numInstrs;
	//static ViFindList findList;
	//static ViSession defaultRM, instr;
	//static ViStatus status;

	status = viOpenDefaultRM(&defaultRM);
	if (status < VI_SUCCESS)
	{
		printf("Could not open a session to the VISA Resource Manager!\n");
		exit(EXIT_FAILURE);
	}

	/*
	 * Find all the VISA resources in our system and store the number of resources
	 * in the system in numInstrs.  Notice the different query descriptions a
	 * that are available.

		Interface         Expression
	--------------------------------------
		GPIB              "GPIB[0-9]*::?*INSTR"
		VXI               "VXI?*INSTR"
		GPIB-VXI          "GPIB-VXI?*INSTR"
		Any VXI           "?*VXI[0-9]*::?*INSTR"
		Serial            "ASRL[0-9]*::?*INSTR"
		PXI               "PXI?*INSTR"
		All instruments   "?*INSTR"
		All resources     "?*"
	*/
	status = viFindRsrc(defaultRM, "?*INSTR", &findList, &numInstrs, instrDescriptor);
	if (status < VI_SUCCESS)
	{
		printf("An error occurred while finding resources.\nHit enter to continue.");
		fflush(stdin);
		getchar();
		viClose(defaultRM);
		return status;
	}

	printf("%d instruments, serial ports, and other resources found:\n\n", numInstrs);
	printf("%s \n", instrDescriptor);

	/* Now we will open a session to the instrument we just found. */
	status = viOpen(defaultRM, instrDescriptor, VI_NULL, VI_NULL, &instr);
	if (status < VI_SUCCESS)
	{
		printf("An error occurred opening a session to %s\n", instrDescriptor);
	}
	else
	{
		/* Now close the session we just opened.                            */
		/* In actuality, we would probably use an attribute to determine    */
		/* if this is the instrument we are looking for.                    */
		viClose(instr);
	}

	while (--numInstrs)
	{
		/* stay in this loop until we find all instruments */
		status = viFindNext(findList, instrDescriptor);  /* find next desriptor */
		if (status < VI_SUCCESS)
		{   /* did we find the next resource? */
			printf("An error occurred finding the next resource.\nHit enter to continue.");
			fflush(stdin);
			getchar();
			viClose(defaultRM);
			return status;
		}
		printf("%s \n", instrDescriptor);

		/* Now we will open a session to the instrument we just found */
		status = viOpen(defaultRM, instrDescriptor, VI_NULL, VI_NULL, &instr);
		if (status < VI_SUCCESS)
		{
			printf("An error occurred opening a session to %s\n", instrDescriptor);
		}
		else
		{
			/* Now close the session we just opened.                            */
			/* In actuality, we would probably use an attribute to determine    */
			/* if this is the instrument we are looking for.                    */
			viClose(instr);
		}
	}    /* end while */

	status = viClose(findList);
	status = viClose(defaultRM);
	printf("\nHit enter to continue.");
	fflush(stdin);
	getchar();

	return 0;
}
//��GPIB�豸
void SLTTestDemo::openGpib()
{
	char *name = "GPIB0::7::INSTR";  //Ĭ�������
	//ѡ�˱�ĺ�������¸�ֵ
	//QByteArray ba = gpib_name.toLatin1();
	//name = ba.data();

	char buffer_open[255] = { 0 };
	status = 0;                         // ���淵����ֵ
	defaultRM = 0;
	numInstrs = 0;
	//ViByte wrtBuf[MAX_SCPI_LENGTH];                     // д������
	ViByte rdBuf[255];                      // ��������
	//char buffer[255] = { 0 };

	status = viOpenDefaultRM(&defaultRM);
	//nReturnStatus = viOpen(rmSession, "USB::0xFFFF::0x6300::802060092746810025::INSTR", VI_NULL, VI_NULL, &pnInstrHandle);  //�����ļ��豸
	status = viOpen(defaultRM, /*instrDescriptor*//*"GPIB0::7::INSTR"*/name, VI_NULL, VI_NULL, &instr);  //�����豸
	status = viQueryf(instr, "FR?\n", "%s", /*buffer*/buffer_open);    //��ѯHandler״̬
	status = viEnableEvent(instr, VI_EVENT_SERVICE_REQ, VI_QUEUE, VI_NULL);
}

//��GPIB�豸����ѯ״̬
void SLTTestDemo::connectGpib()
{
	char buffer_fullsites[255] = { 0 };

	status = viWaitOnEvent(instr, VI_EVENT_SERVICE_REQ, REQUEST_SRQ, &etype, &ehandle);   //�ȴ�SRQ,�費��Ҫ�ӣ�
			//0x41�Ǵ���viReadSTB��statusByte����viRead��data��
	if (status >= VI_SUCCESS)
	{
		status = viReadSTB(instr, &statusByte);   //��viWaitOnEvent������ʱȷ���յ������Ƕ�ȡSRQ��ʱ����Ҫ��ѭ��ȥ���գ�
		//status = viRead(instr, data, 3000, &rcount);   //�����ݣ�0x41?
		if (statusByte != 0x41)
		{
			QMessageBox::warning(nullptr, "SRQ Error!", "Can't Receive SRQ:0x41!", QMessageBox::Ok);
			status = viClose(ehandle);
			//viClose(instr);
			//viClose(defaultRM);
			return;
		}
	}
	else
	{
		QMessageBox::warning(nullptr, "SRQ Error!", "Can't Receive SRQ:0x41!", QMessageBox::Ok);
		status = viClose(ehandle);
		//viClose(instr);
		//viClose(defaultRM);
		return;
	}
	status = viClose(ehandle);
	//char buffer_site[255] = { 0 };
	status = viQueryf(instr, "FULLSITES?\r\n", "%[^\n]", /*buffer*/buffer_fullsites);     //%s�����ַ��������ո�ʱֹͣ���º���������޷���ʾ��%[^\n]�������������\n�س���ʱ��ֹͣ
	//if (memcmp(buffer_fullsites, "Fullsites 0000000F", strlen("Fullsites 0000000F")) != 0)
	//{
	//	//QMessageBox::warning(nullptr, "Fullsites Error!", "Please Check Sites!", QMessageBox::Ok);
	//	//viClose(instr);
	//	//viClose(defaultRM);
	//	return;
	//}
	if (buffer_fullsites[1]!='u')   //ͨ�ų���ֻ�յ�һ��'F'
	{
		//��bin��ͨ�Ŵ�������
		char buffer[255] = { 0 };
		status = viQueryf(instr, "BINON:00000000,00000000,00000000,00002222;\r\n", "%s", buffer);
		//�����bin����������������bin����
		while (status < VI_SUCCESS)
		{
			Sleep(1000);   //��ʱһ�뷢�ͣ���Ȼ����̫�쵼�»�̨ͨ���մ�
			status = viQueryf(instr, "BINON:00000000,00000000,00000000,00002222;\r\n", "%s", buffer);
			//return;
		}
		status = viPrintf(instr, "ECHOOK\n");	
		//if (status < VI_SUCCESS)
		//{
		//	viClose(instr);
		//	viClose(defaultRM);
		//	return;
		//}
		
	}
	//status = viPrintf(instr, "FULLSITES?\r\n");
	//ViConstString rec = "";
	//status = viScanf(instr, rec);
	//status = viPrintf(instr, "FULLSITES?\r\n");
	//ViConstString rec1;
	//status = viScanf(instr, rec1);
	if (status < VI_SUCCESS)
	{
		//QMessageBox::warning(nullptr, "Fullsites Error!", "Please Check Sites!", QMessageBox::Ok);
		//viClose(instr);
		//viClose(defaultRM);
		return;
	}


	//GPIBģ��������̿ɲ鿴HandlerControl_201211�ļ�����
	//status = 0;                         // ���淵����ֵ
	//defaultRM = 0;
	//numInstrs = 0;
	////ViByte wrtBuf[MAX_SCPI_LENGTH];                     // д������
	//ViByte rdBuf[255];                      // ��������
	//char buffer[255] = { 0 };

	//status = viOpenDefaultRM(&defaultRM);
	////nReturnStatus = viOpen(rmSession, "USB::0xFFFF::0x6300::802060092746810025::INSTR", VI_NULL, VI_NULL, &pnInstrHandle);  //�����ļ��豸
	//status = viOpen(defaultRM, /*instrDescriptor*/"GPIB0::7::INSTR", VI_NULL, VI_NULL, &instr);  //�����豸
	//status = viQueryf(instr, "FR?\n", "%s", buffer);    //��ѯHandler״̬
	//status = viEnableEvent(instr, VI_EVENT_SERVICE_REQ, VI_QUEUE, VI_NULL);
	//while (true)
	//{
	//	//status = viEnableEvent(instr, VI_EVENT_SERVICE_REQ, VI_QUEUE, VI_NULL);
	//	status = viWaitOnEvent(instr, VI_EVENT_SERVICE_REQ, REQUEST_SRQ, &etype, &ehandle);   //�ȴ�SRQ,�費��Ҫ�ӣ�
	//	//0x41�Ǵ���viReadSTB��statusByte����viRead��data��
	//	if (status >= VI_SUCCESS)
	//	{
	//		status = viReadSTB(instr, &statusByte);   //��viWaitOnEvent������ʱȷ���յ������Ƕ�ȡSRQ��ʱ����Ҫ��ѭ��ȥ���գ�
	//		//status = viRead(instr, data, 3000, &rcount);   //�����ݣ�0x41?
	//		if (statusByte != 0x41)
	//		{
	//			status = viClose(ehandle);
	//			viClose(instr);
	//			viClose(defaultRM);
	//			return;
	//		}
	//	}
	//	else
	//	{
	//		status = viClose(ehandle);
	//		viClose(instr);
	//		viClose(defaultRM);
	//		return;
	//	}
	//	status = viClose(ehandle);
	//	//char buffer_site[255] = { 0 };
	//	status = viQueryf(instr, "FULLSITES?\r\n", "%s", buffer);
	//	//status = viPrintf(instr, "FULLSITES?\r\n");
	//	//ViConstString rec1;
	//	//status = viScanf(instr, rec1);
	//	if (status < VI_SUCCESS)
	//	{
	//		viClose(instr);
	//		viClose(defaultRM);
	//		return;
	//	}
	//	Sleep(10000);  //оƬ����ʱ��
	//	status = viQueryf(instr, "BINON:00000000,00000000,00000000,00001111;\r\n", "%s", buffer);
	//	if (status < VI_SUCCESS)
	//	{
	//		viClose(instr);
	//		viClose(defaultRM);
	//		return;
	//	}
	//	//��д�Ͷ��ķ�ʽȥ�ж�һ��������viQueryf��ѯ��ʽ������
	//	//status = viPrintf(instr, "BINON:00000000,00000000,00000000,00001111;\r\n");
	//	//ViConstString rec;
	//	//status = viScanf(instr, rec);
	//	//if (rec != "BINON:00000000,00000000,00000000,00001111;\r\n")
	//	//{
	//	//	viClose(instr);
	//	//	viClose(defaultRM);
	//	//	return;
	//	//}
	//	//else
	//	//{
	//	//	status = viPrintf(instr, "ECHOOK\n");
	//	//}
	//	status = viPrintf(instr, "ECHOOK\n");
	//	if (status < VI_SUCCESS)
	//	{
	//		viClose(instr);
	//		viClose(defaultRM);
	//		return;
	//	}
	//	//viClose(instr);
	//	//viClose(defaultRM);
	//}
	//viClose(instr);
	//viClose(defaultRM);
}

//������ɣ����з�bin
void SLTTestDemo::binON(/*bool bin1,bool bin2,bool bin3,bool bin4*/)
{
	//char buffer[255] = { 0 };
	//status = viOpenDefaultRM(&defaultRM);
	//status = viOpen(defaultRM, instrDescriptor, VI_NULL, VI_NULL, &instr);  //�����豸
	//status = viQueryf(instr, "BINON:00000000,00000000,00000000,00000015", "%s", buffer);   //��bin,����������site(socket),����15������1site�ֵ�5BIN,3�ֵ�1BIN.
	////_sleep(100);//ģ�������
	//Sleep(100);  //ģ�������
	//if (buffer == "ECHO:00000000,00000000,00000000,00000015")
	//{
	//	status = viPrintf(instr, "ECHOOK");
	//}
	//else
	//{
	//	status = viPrintf(instr, "ECHONG");
	//}


	//char idJudge[4] = { 1,1,1,1 };
	char idJudge[4] = { '1','1','1','1' };
	//char idJudge[4] = { chipID1,chipID2,chipID3,chipID4 };
	if (bin_good_1)
	{
		idJudge[chipID1]='2';
		//idJudge[chipID1]++;
	}
		
	if (bin_good_2)
	{
		idJudge[chipID2] = '2';
		//idJudge[chipID2]++;
	}
		
	if (bin_good_3)
	{
		idJudge[chipID3] = '2';
		//idJudge[chipID3]++;
	}
	if (bin_good_4)
	{
		idJudge[chipID4] = '2';
		//idJudge[chipID4]++;
	}
	//���ˣ�idJudge������Ƿ�bin��ɺ�Ľ������������鴫��bin�����ok��


	//�������滻
	char input_buffer[255] = "BINON:00000000,00000000,00000000,00001111;\r\n";
	input_buffer[37] = idJudge[3];
	input_buffer[38] = idJudge[2];
	input_buffer[39] = idJudge[1];
	input_buffer[40] = idJudge[0];



	char buffer_bin[255] = { 0 };
	//status = viQueryf(instr, "BINON:00000000,00000000,00000000,00001111;\r\n", "%s", /*buffer*/buffer_bin); //1����ɹ���bin,2����ʧ�ܵ�bin
	status = viQueryf(instr, /*"s%",*/input_buffer, "%s", /*buffer*/buffer_bin);
	if (status < VI_SUCCESS)
	{
		//QMessageBox::warning(nullptr, "BINON Error!", "Can't Receive BINON!", QMessageBox::Ok);
		//viClose(instr);
		//viClose(defaultRM);
		return;
	}
	//��д�Ͷ��ķ�ʽȥ�ж�һ��������viQueryf��ѯ��ʽ������
	//status = viPrintf(instr, "BINON:00000000,00000000,00000000,00001111;\r\n");
	//ViConstString rec = "";
	//status = viScanf(instr, rec);
	//if (rec != "BINON:00000000,00000000,00000000,00001111;\r\n")
	//{
	//	viClose(instr);
	//	viClose(defaultRM);
	//	return;
	//}
	//else
	//{
	//	status = viPrintf(instr, "ECHOOK\n");
	//}
	status = viPrintf(instr, "ECHOOK\n");
	if (status < VI_SUCCESS)
	{
		//QMessageBox::warning(nullptr, "ECHOOK Error!", "Can't Send ECHOOK!", QMessageBox::Ok);
		//viClose(instr);
		//viClose(defaultRM);
		return;
	}
}

void SLTTestDemo::lcdCount()
{
	ui.lcdNumber->display(allChipCount);
	ui.lcdNumber_2->display(failedChipCount);
	double passRate = (allChipCount - failedChipCount) * 100 / allChipCount ;
	QString str = QString::number(passRate, 10, 3);// +QString::fromLocal8Bit("%");
	QString strs;
	strs.sprintf("%.1f%%", passRate);
	//ui.lcdNumber_3->display((allChipCount - failedChipCount) / allChipCount);
	//ui.lcdNumber_3->display(passRate);
	ui.lcdNumber_3->display(strs);
}

void SLTTestDemo::pushbutton3disable()
{
	ui.pushButton_3->setEnabled(false);
}

void SLTTestDemo::saveCSVFlie()
{
	//QDateTime time;
	//QString currentTime = time.currentDateTime().toString("yyy/MM/dd HH:mm:ss");
	QString fileName = QCoreApplication::applicationDirPath() + "/" + "SLTRecord_" + time_creatFile + ".csv";
	QFile file(fileName);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))    //����QIODevice::Append�Ͳ���֮ǰ�����ݣ����ǵ���������Ͼͼ�������д���̶�����ĸ�ʽ��Ӧ�ò���Append�˰ɣ����������ξʹ���������ͷ�ˣ�
	{
		QMessageBox::warning(nullptr, "sdf", "can't open", QMessageBox::Ok);
	}
	QTextStream stream(&file);
	stream << "Chip ID" << "," << "Err Case" << "," << "Err Information" << "," << "Socket" << "," << "Timestamp" << "\n";
	file.close();
}

void SLTTestDemo::saveConnent(QString chipID,QString err,QString errInfo,QString socket,QString time)
{
	QString fileName = QCoreApplication::applicationDirPath() + "/" + "SLTRecord_" + time_creatFile + ".csv";
	QFile file(fileName);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))   //����QIODevice::Append�Ͳ���֮ǰ�����ݣ����ǵ���������Ͼͼ�������д
	{
		QMessageBox::warning(nullptr, "sdf", "can't open", QMessageBox::Ok);
	}
	QTextStream stream(&file);
	stream << chipID << "," << err << "," << errInfo << "," << socket << "," << time << "\n";
	file.close();
}
//��������
void SLTTestDemo::creatPassRate()
{
	QString fileName = QCoreApplication::applicationDirPath() + "/" + "SLTPassRate_" + time_creatFile + ".csv";
	QFile file(fileName);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
	{
		QMessageBox::warning(nullptr, "sdf", "can't open", QMessageBox::Ok);
	}
	QTextStream stream(&file);
	stream << "Fail Chip" << "," << "All Chip" << "," << "Pass Rate" << "\n";
	file.close();
}

void SLTTestDemo::savePassRate(QString fail, QString all, QString passRate)
{
	QString fileName = QCoreApplication::applicationDirPath() + "/" + "SLTPassRate_" + time_creatFile + ".csv";
	QFile file(fileName);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
	{
		QMessageBox::warning(nullptr, "sdf", "can't open", QMessageBox::Ok); 
	}
	QTextStream stream(&file);
	stream.seek(29);
	stream /*<< "\n"*/ << fail << "," << all << "," << passRate << "\n";
	file.close();
}

void SLTTestDemo::recordLog(QString saveLogName/*,QString send_info,QString rec_info*/)
{
	//QDateTime time;
	//QString date_time = time.currentDateTime.toString("yyyy/MM/dd HH:mm:ss");
	filePath = QCoreApplication::applicationDirPath() + "/" + saveLogName + ".txt";
	if (!filePath.isEmpty())
	{
		QFile file(filePath);
		if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
		{
			QMessageBox::warning(0, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("���ļ�ʧ��!"), QMessageBox::Ok);
		}
		//QTextStream tStream(&file);
		//tStream << date_time << "\t\t\t" << send_info << "\n";
		file.close();
	}
}

void SLTTestDemo::send_rec(QString path, QString send_info,QString sendOrRec)
{
	QDateTime time;
	QString date_time = time.currentDateTime().toString("yyyy/MM/dd_HH:mm:ss.zzz");
	if (!path.isEmpty())
	{
		QFile file(path);
		if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
		{
			QMessageBox::warning(0, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("���ļ�ʧ��!"), QMessageBox::Ok);
		}
		QTextStream tStream(&file);
		tStream << date_time << "\t" << sendOrRec << send_info << "\n";
		file.close();
	}
}


void SLTTestDemo::stopSerialPort(QSerialPort *qsp,std::thread *t)
{
	if (t != nullptr)
	{
		//������̵߳ĺ�����QEvnetLoop�ȴ�����Ҫ�ȷ����˳��ȴ��źţ�Ȼ��break����ѭ���ȴ��������������߳������˳�
		
		stopAutoTest = false;
		stopThread1 = true;
		stopThread2 = true;
		stopThread3 = true;
		stopThread4 = true;

		//closeControl = false;

		isComplete1 = true;   //���̲߳�����ͬ���ȴ���
		isComplete2 = true;
		isComplete3 = true;
		isComplete4 = true;
		//�رմ���
		if (qsp->isOpen())
		{
			qsp->close();
		}
		delete qsp;
		qsp = nullptr;

		emit finishedInfo1();  //�����Ƿ�Ҫ����������ȴ��ź��أ���Ϊ�����һ��ȴ���������forѭ���������ܿ��ڵȴ�ͬ�������ĵȴ��̡߳�����ټ�һ������ȴ���Ҫ����ʱ���ܱ�֤�ͷŽ���ȴ��ź�ʱ�������̴߳��ڵȴ�״̬��Ҳ���Բ����̵߳ȴ���ֱ��ͬ��flag��Ϊtrue��ok�ˡ�
		
		emit finishedInfo2();
	
		emit finishedInfo3();
		
		emit finishedInfo4();

		//m_condition.notify_all();
		
		t->join();
		delete t;
		t = nullptr;

		

	}

	if (tControl != nullptr)
	{
		closeControl = false;
		//emit finishedInfoControl();
		tControl->join();
		delete tControl;
		tControl = nullptr;
	}
	
}

void SLTTestDemo::stopQtimer(QTimer *timer)
{
	if (timer!=nullptr)
	{
		timer->stop();
		delete timer;
		timer = nullptr;
	}
}

void SLTTestDemo::qtimerRun1()
{
	//while (timerFlag)
	//{
	//	//connect(m_timer1, SIGNAL(timeout()), this, SLOT(timeRun1(/*QSerialPort **/))/*, Qt::DirectConnection*/);
	//	m_timer1->start(20000);
	//	QEventLoop loop;
	//	connect(this, SIGNAL(fini1()), &loop, SLOT(quit()));
	//	loop.exec();
	//}

	m_timer1->start(17000);
}

void SLTTestDemo::qtimerRun2()
{
	//while (timerFlag)
	//{
	//	//connect(m_timer2, SIGNAL(timeout()), this, SLOT(timeRun2(/*QSerialPort **/))/*, Qt::DirectConnection*/);
	//	m_timer2->start(20000);
	//	QEventLoop loop;
	//	connect(this, SIGNAL(fini2()), &loop, SLOT(quit()));
	//	loop.exec();
	//}

	m_timer2->start(17000);
}

void SLTTestDemo::qtimerRun3()
{
	//while (timerFlag)
	//{
	//	//connect(m_timer3, SIGNAL(timeout()), this, SLOT(timeRun3(/*QSerialPort **/))/*, Qt::DirectConnection*/);
	//	m_timer3->start(20000);
	//	QEventLoop loop;
	//	connect(this, SIGNAL(fini3()), &loop, SLOT(quit()));
	//	loop.exec();
	//}

	m_timer3->start(17000);
}

void SLTTestDemo::qtimerRun4()
{
	//while (timerFlag)
	//{
	//	//connect(m_timer4, SIGNAL(timeout()), this, SLOT(timeRun4(/*QSerialPort **/))/*, Qt::DirectConnection*/);
	//	m_timer4->start(20000);
	//	QEventLoop loop;
	//	connect(this, SIGNAL(fini4()), &loop, SLOT(quit()));
	//	loop.exec();
	//}

	m_timer4->start(17000);
}

//�����б�
QStringList SLTTestDemo::getPortNameList()//��ȡ���п��õĴ����б�
{
	QStringList m_serialPortName;
	foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
	{
		//if (info.portName() == "COM24" || info.portName() == "COM21")
		//{
			//m_serialPortName << info.portName();
		//m_serialPortName << info.description() + info.portName();
		//}
		if (info.description() == "Silicon Labs CP210x USB to UART Bridge")
		{
			m_serialPortName << info.portName();
		}
	}
	return m_serialPortName;
}

//��ʼ������
void SLTTestDemo::initSerialPort(/*QSerialPort *sp*/)
{
	QSerialPort *sp;
	//static int i = 0;
	QStringList serialList = getPortNameList();
	if (!serialList.empty())
	{
		for (int i = 0; i < /*4*/ serialList.length(); i++)
		{
			if (i == 0)
			{
				sp = m_serialPort1;
			}
			if (i == 1)
			{
				sp = m_serialPort2;
			}
			if (i == 2)
			{
				sp = m_serialPort3;
			}
			if (i == 3)
			{
				sp = m_serialPort4;
			}
			if (sp->isOpen())//��������Ѿ����� �ȸ����ر���
			{
				sp->clear();
				sp->close();
			}
			//���ô������� �������������Ѿ��ɹ���ȡ���� ����ʹ�õ�һ��
			QString serportName = serialList.at(i);
			sp->setPortName(serportName);
			//sp->setPortName(/*ui.comboBox->currentText()*/"COM21");
			if (!sp->open(QIODevice::ReadWrite))//��ReadWrite ��ģʽ���Դ򿪴���
			{
				QMessageBox::warning(0, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("���ڴ�ʧ�ܻ򴮿��ѱ�ռ��!"), QMessageBox::Ok);
				return;
			}
			//�򿪳ɹ�
			//sp->setBaudRate(921600, QSerialPort::AllDirections);
			sp->setBaudRate(QSerialPort::Baud115200, QSerialPort::AllDirections);//���ò����ʺͶ�д����
			sp->setDataBits(QSerialPort::Data8);		//����λΪ8λ
			sp->setFlowControl(QSerialPort::NoFlowControl);//��������
			sp->setParity(QSerialPort::NoParity);	//��У��λ
			sp->setStopBits(QSerialPort::OneStop); //һλֹͣλ
			//i++;
		}
		
	}
	else
	{
		QMessageBox::warning(0, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("δ��⵽����!"), QMessageBox::Ok);
	}
	
}
//��ȡ�����ļ�
void SLTTestDemo::setTableWidget(QTableWidget *tb)
{
	fileName = QCoreApplication::applicationDirPath() + "/" + QString::fromLocal8Bit("���ò�����.xls");
	if (!fileName.isEmpty())
	{
		QFile file;
		file.setFileName(fileName);
		//���ļ�
		if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		{
			QMessageBox msg;
			msg.setText(QString::fromLocal8Bit("���ļ�ʧ��!"));
			msg.exec();
		}
		else
		{
			if (!file.size())
			{
				QMessageBox::warning(0, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("�ļ���СΪ��!"), QMessageBox::Ok);
			}
			else
			{
				//���ļ����ݵ�����
				int r_count = 0;        //ͳ���ļ�������
				QStringList textList;   //��¼�ļ���ÿһ�е�����
				QTextStream in(&file);
				while (!in.atEnd())
				{
					QString line = in.readLine();
					textList.append(line);          //�����ļ�������
					r_count++;                      //��¼�ļ������� ǰ����Ϊ��ͷ
				}
				file.close();       //�ر��ļ�
				if (!textList.isEmpty())
				{
					//QStringList listColHeader = textList.at(1).split("\t");
					QStringList listRowHeader = textList.at(0).split("\t");
					int c_count = listRowHeader.count();
					tb->clear();
					tb->setRowCount(r_count - 1);      //ǰ���������б�ͷ
					tb->setColumnCount(c_count/* - 1*/);   //���һ���ǡ�\t"   �������д���ļ��Ļ�����\t,��Ҫ-1���ֶ������ļ�д�Ļ�����Ҫ-1.���TestTry��Ŀ����  
					tb->setHorizontalHeaderLabels(listRowHeader);
					//ui.tableWidget->setVerticalHeaderLabels(listColHeader);
					for (int row = 1; row < r_count; row++)
					{
						QStringList tmpList;
						tmpList = textList.at(row).split("\t");
						for (int col = 0; col < c_count; col++)
						{
							QTableWidgetItem *item = new QTableWidgetItem(tmpList.at(col));
							tb->setItem(row - 1, col, item);
						}
					}
					//QMessageBox::information(0, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("����ɹ�!"));
				}
			}
		}
	}
	else
	{
		QMessageBox::warning(0, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("�ļ���δָ��!"), QMessageBox::Ok);
	}
}

//�������������ر��
void SLTTestDemo::saveTableToFile(QTableWidget *tb)
{
	QString path = QCoreApplication::applicationDirPath();
	if (!path.isEmpty())
	{
		//���������д���ļ�
		if (QFileInfo(path).suffix().isEmpty())
		{
			path.append(".xls");
		}
		QFile file;
		file.setFileName(path);
		//���ļ�
		if (!file.open(QIODevice::WriteOnly | QIODevice::Text))      //�ô˷���������excel����ͨ��excel��һ�����������ڴ���ٵģ����Է��ִ˷����½���excel��ʵ���Ǵ���һ���ı��ĵ�����.txt��Ϊ.xls����ͨ��������Ҫ�õ�QAxObject�⣬�����ٶȺ�����������Ҫ�����淽����ȡ�ļ�����񣬱����������ַ�������excel��񣬷�����ͨ������excel�޷��������ȡ�ķ�����ȡ�����ݡ�
		{
			QMessageBox msg;
			msg.setText(QString::fromLocal8Bit("���ļ�ʧ��!"));
			msg.exec();
		}
		else
		{
			QTextStream out(&file);
			int rowCount = ui.tableWidget->rowCount();
			int colCount = ui.tableWidget->columnCount();
			//����ͷд���ļ�
			for (int i = 0; i < colCount; i++)
			{
				QString rowHeaderString = ui.tableWidget->horizontalHeaderItem(i)->text();
				out << rowHeaderString << "\t";
			}
			out << "\n";
			//for (int j = 0; j < rowCount; j++)
			//{
			//	QString colHeaderString = ui.tableWidget->verticalHeaderItem(j)->text();
			//	out << colHeaderString << "\t";
			//}
			//out << "\n";
			//��ȡ��Ԫ������ݲ�д���ļ�
			for (int row = 0; row < rowCount; row++)
			{
				for (int col = 0; col < colCount; col++)
				{
					QString text = ui.tableWidget->item(row, col)->text();
					if (text.isEmpty())
					{
						out << "null" << "\t";
					}
					else
					{
						out << text << "\t";
					}
				}
				out << "\n";       //linux�»��з���'\n'
			}
			out.flush();
			file.close();       //�ر��ļ�
			QMessageBox::information(0, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("�����ɹ�!"));
		}
	}
	else
	{
		QMessageBox::warning(0, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("�ļ���δָ��!"), QMessageBox::Ok);
	}
}

//GPIB����
void SLTTestDemo::on_pushButton_clicked()
{
	set_gpib->show();
}

//���������ļ�
void SLTTestDemo::on_pushButton_2_clicked()
{
	//fileName = QFileDialog::getOpenFileName(0, tr("InputFile"),
	//	tr("/root/Projects/product/bin/config"),
	//	tr("file(*.txt *.xls);;Allfile(*.*)"));
	//setTableWidget(ui.tableWidget);
	//setTableWidget(ui.tableWidget_2);
	//setTableWidget(ui.tableWidget_3);
	//setTableWidget(ui.tableWidget_4);
}

//�������ݷ���
//ԭ��˼·����һ�����ͺ������ĸ��߳�ȥ���ÿ���ʵ��ͬʱ���ͣ���������connect(/*m_serialPort*/this  /*t3*/, SIGNAL(finishedInfo(/*int*//* num*/)), &loop, SLOT(quit()));
//���ź���һ�������������̻߳�����ǰ�̵߳ĵȴ����������4���˺���,����4�ֲ�ͬ�ź�
//void SLTTestDemo::serialPortSend(QSerialPort *sp/*,int num*/)
//{	
//	//char cmd[31] = { MCUID ,RUN510 ,DPU ,DDR ,RTC ,Timer1_0 ,DMA ,USI1_SPI ,USI2_UART ,UART1 ,OTPC ,I2C0_1_2 ,ADC ,SDIO0 ,SDIO1 ,GMAC ,
//	//CRYPTO ,VPU ,PWM ,I2S ,Mailbox ,RNE ,_3D ,AMR ,USB2_0 ,MIPI_TX_USB3_0 ,WDT ,SMU,GETPOWER,UPGRADE,OVER };
//
//	int len = ui.tableWidget->rowCount();
//	for (int i = 0; i < len; i++)
//	{
//		char send_data[6] = { 0 };
//		QString cmdStr = ui.tableWidget->item(i, 1)->text();
//		int cmd = cmdStr.toInt(nullptr,16);
//		send_info(send_data, cmd, 0, cmd);
//		sp->write(send_data, 6);
//		sp->waitForBytesWritten(10000);
//
//		//��ǰ�̵߳ȴ�����������̷߳�����finishedInfo()�źţ����߳̾ͻ��������������
//		//�����Զ���4����ͬ�źţ�һ���̶߳�Ӧһ���źţ�ÿ���̷߳��䲻ͬ���ź�
//		QEventLoop loop;
//		connect(/*m_serialPort*/this  /*t3*/, SIGNAL(finishedInfo(/*int*//* num*/)), &loop, SLOT(quit()));
//		loop.exec();
//	}
//
//	//for (int i = 0; i < 31; i++)
//	//{
//	//	char send_data[6] = { 0 };
//	//	//std::string str = ui.tableWidget->item(i, 1)->text().toStdString();
//	//	//char sumCheck = std::accumulate(send_data + 2, send_data + sizeof(send_packet) - 1, 0);
//	//	char sumCheck = cmd[i];
//	//	send_info(send_data, sumCheck, 0, sumCheck);
//	//	//rec_info.clear();
//	//	sp->write(send_data, 6);
//	//	sp->waitForBytesWritten(10000);    //��������߳�ʹ��write�������ݣ�����waitForBytesWritten�޷����͡�
//
//	//	QEventLoop loop;
//	//	connect(/*m_serialPort*/this, SIGNAL(finishedInfo()), &loop, SLOT(quit()));
//	//	loop.exec();
//	//}
//}

//20s�󴥷��˺�����ÿ20s����һ�Σ����Բ����Լ�forѭ����3��
void SLTTestDemo::timeRun1(/*QSerialPort *m_serial*/)
{
	//3�γ�ʱ�ش����к���жϵ紦��
	//static int count = 0;
	//if (count < 3)
	//{
	//	char send_data[6] = { 0 };
	//	send_info(send_data, serial1_cmd, 0, serial1_cmd);
	//	m_serialPort1->write(send_data, 6);
	//	m_serialPort1->waitForBytesWritten(10000);

	//	//QString path = QCoreApplication::applicationDirPath() + "/" + "SerialPort1.txt";
	//	//QByteArray SEN = QByteArray(send_data, 6);
	//	//QString str = SEN.toHex(' ').toUpper();
	//	//send_rec(path, str, "Timeout Send:");

	//	QDateTime time;
	//	QString currentTime = time.currentDateTime().toString("yyyy/MM/dd_HH:mm:ss.zzz");
	//	//QString errCase = ui.tableWidget->item(id, 0)->text();
	//	saveConnent(NULL, QString::number(serial1_cmd), QString("Can not receive ACK time out"), QString::number(chipID1), currentTime);
	//}
	//else
	//{
	//	QDateTime time;
	//	QString now = time.currentDateTime().toString("yyyy/MM/dd_HH:mm:ss");
	//	ui.textEdit->append(now + ":" + QString::fromLocal8Bit("��ʱ�ش�3�Σ����´��ڳ�ʼ�����ϵ磡"));
	//	//if (!m_serialPort1->open(QIODevice::ReadWrite))
	//	//{
	//	//	QMessageBox::warning(0, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("���ڴ�ʧ�ܻ򴮿��ѱ�ռ��!"), QMessageBox::Ok);
	//	//	return;
	//	//}
	//	initSerialPort();  //��ֹͨ���жϣ���Ҫ���³�ʼ������
	//	m_timer1->stop();   //������˺�����
	//	char send_data[6] = { 0xef,0xaa,0xff,0x00,0x00,0xff };   //����3�Σ���ô�Ͷϵ��оƬ������ȴ�
	//	m_serialPort1->write(send_data, 6);
	//	m_serialPort1->waitForBytesWritten(10000);
	//	stopThread1 = true;
	//	emit finishedInfo1();
	//	count = 0;
	//}

	//count++;



	//��ʱ17sһ�ξ�ֱ�ӽ��жϵ紦��
	QDateTime time;
	QString now = time.currentDateTime().toString("yyyy/MM/dd_HH:mm:ss");
	ui.textEdit->append(now + ":" + QString::fromLocal8Bit("��ʱ�ش������´��ڳ�ʼ�����ϵ磡"));
	saveConnent(NULL, QString::number(serial1_cmd), QString("Can not receive ACK time out"), QString::number(chipID1), now);
	//if (!m_serialPort1->open(QIODevice::ReadWrite))
	//{
	//	QMessageBox::warning(0, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("���ڴ�ʧ�ܻ򴮿��ѱ�ռ��!"), QMessageBox::Ok);
	//	return;
	//}
	initSerialPort();  //��ֹͨ���жϣ���Ҫ���³�ʼ������
	//m_timer1->stop();   //������˺����ˣ�//��ʵ���Ҳ���üӣ�����0xff�ϵ����Ȼ���յ��ظ���ack����˻�������رյ�
	char send_data[6] = { 0xef,0xaa,0xff,0x00,0x00,0xff };   //����3�Σ���ô�Ͷϵ��оƬ������ȴ�
	m_serialPort1->write(send_data, 6);
	m_serialPort1->waitForBytesWritten(10000);
	stopThread1 = true;
	bin_good_1 = true;   //�ϵ��ش��󣬷ֵ�bin��������
	//emit finishedInfo1();  //��ʵ���Ҳ���üӣ�����0xff�ϵ����Ȼ���յ��ظ���ack����˻ᷢ������źŵ�
	
}

//20s�󴥷��˺�����ÿ20s����һ�Σ����Բ����Լ�forѭ����3��
void SLTTestDemo::timeRun2(/*QSerialPort *m_serial*/)
{

	//static int count = 0;
	//if (count < 3)
	//{
	//	char send_data[6] = { 0 };
	//	send_info(send_data, serial2_cmd, 0, serial2_cmd);
	//	m_serialPort2->write(send_data, 6);
	//	m_serialPort2->waitForBytesWritten(10000);

	//	//QString path = QCoreApplication::applicationDirPath() + "/" + "SerialPort2.txt";
	//	//QByteArray SEN = QByteArray(send_data, 6);
	//	//QString str = SEN.toHex(' ').toUpper();
	//	//send_rec(path, str, "Timeout Send:");

	//	QDateTime time;
	//	QString currentTime = time.currentDateTime().toString("yyyy/MM/dd_HH:mm:ss.zzz");
	//	//QString errCase = ui.tableWidget->item(id, 0)->text();
	//	saveConnent(NULL, QString::number(serial2_cmd), QString("Can not receive ACK time out"), QString::number(chipID2), currentTime);
	//}
	//else
	//{
	//	QDateTime time;
	//	QString now = time.currentDateTime().toString("yyyy/MM/dd_HH:mm:ss");
	//	ui.textEdit->append(now + ":" + QString::fromLocal8Bit("��ʱ�ش�3�Σ����´��ڳ�ʼ�����ϵ磡"));
	//	initSerialPort(); //��ֹͨ���жϣ���Ҫ���³�ʼ������
	//	m_timer2->stop();   //������˺�����
	//	char send_data[6] = { 0xef,0xaa,0xff,0x00,0x00,0xff };   //����3�Σ���ô�Ͷϵ��оƬ������ȴ�
	//	m_serialPort2->write(send_data, 6);
	//	m_serialPort2->waitForBytesWritten(10000);
	//	stopThread2 = true;
	//	emit finishedInfo2();
	//	count = 0;
	//}

	//count++;



	QDateTime time;
	QString now = time.currentDateTime().toString("yyyy/MM/dd_HH:mm:ss");
	ui.textEdit->append(now + ":" + QString::fromLocal8Bit("��ʱ�ش������´��ڳ�ʼ�����ϵ磡"));
	saveConnent(NULL, QString::number(serial2_cmd), QString("Can not receive ACK time out"), QString::number(chipID2), now);
	initSerialPort(); //��ֹͨ���жϣ���Ҫ���³�ʼ������
	//m_timer2->stop();   //������˺�����
	char send_data[6] = { 0xef,0xaa,0xff,0x00,0x00,0xff };   //����3�Σ���ô�Ͷϵ��оƬ������ȴ�
	m_serialPort2->write(send_data, 6);
	m_serialPort2->waitForBytesWritten(10000);
	stopThread2 = true;
	bin_good_2 = true;//�ϵ��ش��󣬷ֵ�bin��������
	//emit finishedInfo2();
}

//20s�󴥷��˺�����ÿ20s����һ�Σ����Բ����Լ�forѭ����3��
void SLTTestDemo::timeRun3(/*QSerialPort *m_serial*/)
{
	//static int count = 0;
	//if (count < 3)
	//{
	//	char send_data[6] = { 0 };
	//	send_info(send_data, serial3_cmd, 0, serial3_cmd);
	//	m_serialPort3->write(send_data, 6);
	//	m_serialPort3->waitForBytesWritten(10000);

	//	//QString path = QCoreApplication::applicationDirPath() + "/" + "SerialPort3.txt";
	//	//QByteArray SEN = QByteArray(send_data, 6);
	//	//QString str = SEN.toHex(' ').toUpper();
	//	//send_rec(path, str, "Timeout Send:");

	//	QDateTime time;
	//	QString currentTime = time.currentDateTime().toString("yyyy/MM/dd_HH:mm:ss.zzz");
	//	//QString errCase = ui.tableWidget->item(id, 0)->text();
	//	saveConnent(NULL, QString::number(serial3_cmd), QString("Can not receive ACK time out"), QString::number(chipID3), currentTime);
	//}
	//else
	//{
	//	QDateTime time;
	//	QString now = time.currentDateTime().toString("yyyy/MM/dd_HH:mm:ss");
	//	ui.textEdit->append(now + ":" + QString::fromLocal8Bit("��ʱ�ش�3�Σ����´��ڳ�ʼ�����ϵ磡"));
	//	initSerialPort(); //��ֹͨ���жϣ���Ҫ���³�ʼ������
	//	m_timer3->stop();   //������˺�����
	//	char send_data[6] = { 0xef,0xaa,0xff,0x00,0x00,0xff };   //����3�Σ���ô�Ͷϵ��оƬ������ȴ�
	//	m_serialPort3->write(send_data, 6);
	//	m_serialPort3->waitForBytesWritten(10000);
	//	stopThread3 = true;
	//	emit finishedInfo3();
	//	count = 0;
	//}

	//count++;


	QDateTime time;
	QString now = time.currentDateTime().toString("yyyy/MM/dd_HH:mm:ss");
	ui.textEdit->append(now + ":" + QString::fromLocal8Bit("��ʱ�ش������´��ڳ�ʼ�����ϵ磡"));
	saveConnent(NULL, QString::number(serial3_cmd), QString("Can not receive ACK time out"), QString::number(chipID3), now);
	initSerialPort(); //��ֹͨ���жϣ���Ҫ���³�ʼ������
	//m_timer3->stop();   //������˺�����
	char send_data[6] = { 0xef,0xaa,0xff,0x00,0x00,0xff };   //����3�Σ���ô�Ͷϵ��оƬ������ȴ�
	m_serialPort3->write(send_data, 6);
	m_serialPort3->waitForBytesWritten(10000);
	stopThread3 = true;
	bin_good_3 = true;//�ϵ��ش��󣬷ֵ�bin��������
	//emit finishedInfo3();

}

//20s�󴥷��˺�����ÿ20s����һ�Σ����Բ����Լ�forѭ����3��
void SLTTestDemo::timeRun4(/*QSerialPort *m_serial*/)
{
	//�Ӹ���3�ε��߼�����һ�Σ�����лظ����ͻ��ͷŽ���ȴ��źţ����û�лظ�������δ����˺����ٴη���
	//3���ط�
	//for (int i = 0; i < 3; i++)
	//{
	//	
	//	if (m_timer->isActive())  //��������Ǳ�û���յ�ack����ôm_timer��û��stop()����ôisActive()��true
	//	{
	//		char send_data[6] = { 0 };
	//		send_info(send_data, serial4_cmd, 0, serial4_cmd);
	//		m_serialPort4->write(send_data, 6);
	//		m_serialPort4->waitForBytesWritten(10000);
	//	}
	//	Sleep(20000);  //ÿ20s��һ�γ�ʱ����������ʹ��qtimer���в��������̵߳���ʱ
	//}


	//static int count = 0;
	//if (count < 3)
	//{
	//	char send_data[6] = { 0 };
	//	send_info(send_data, serial4_cmd, 0, serial4_cmd);
	//	m_serialPort4->write(send_data, 6);
	//	m_serialPort4->waitForBytesWritten(10000);

	//	//QString path = QCoreApplication::applicationDirPath() + "/" + "SerialPort4.txt";
	//	//QByteArray SEN = QByteArray(send_data, 6);
	//	//QString str = SEN.toHex(' ').toUpper();
	//	//send_rec(path, str, "Timeout Send:");

	//	QDateTime time;
	//	QString currentTime = time.currentDateTime().toString("yyyy/MM/dd_HH:mm:ss.zzz");
	//	//QString errCase = ui.tableWidget->item(id, 0)->text();
	//	saveConnent(NULL, QString::number(serial4_cmd), QString("Can not receive ACK time out"), QString::number(chipID4), currentTime);
	//}
	//else
	//{
	//	QDateTime time;
	//	QString now = time.currentDateTime().toString("yyyy/MM/dd_HH:mm:ss");
	//	ui.textEdit->append(now + ":" + QString::fromLocal8Bit("��ʱ�ش�3�Σ����´��ڳ�ʼ�����ϵ磡"));
	//	initSerialPort(); //��ֹͨ���жϣ���Ҫ���³�ʼ������
	//	m_timer4->stop();   //������˺�����
	//	char send_data[6] = { 0xef,0xaa,0xff,0x00,0x00,0xff };   //����3�Σ���ô�Ͷϵ��оƬ������ȴ�
	//	m_serialPort4->write(send_data, 6);
	//	m_serialPort4->waitForBytesWritten(10000);
	//	stopThread4 = true;
	//	emit finishedInfo4();
	//	count = 0;
	//}
	//
	//count++;



	//���ｫm_timer4->stop();��emit finishedInfo4();ע�͵��ˡ�1.m_timer4->stop()�����ȥ������ô���ͨ�Ŷ��ˣ�17s�󴥷�һ�ξ�ͣ�ˣ���������ȣ�Ӧ����һֱ17s����һ�Σ�
	//ֱ��ͨ���޺��ˣ��ٴδ�����ʱ������0xff�ϵ������ʱ�򣬻�ظ�ACK����ִ��m_timer4->stop();��emit finishedInfo4();
	QDateTime time;
	QString now = time.currentDateTime().toString("yyyy/MM/dd_HH:mm:ss");
	ui.textEdit->append(now + ":" + QString::fromLocal8Bit("��ʱ�ش������´��ڳ�ʼ�����ϵ磡"));
	saveConnent(NULL, QString::number(serial4_cmd), QString("Can not receive ACK time out"), QString::number(chipID4), now);
	initSerialPort(); //��ֹͨ���жϣ���Ҫ���³�ʼ������
	//m_timer4->stop();   //������˺�����
	char send_data[6] = { 0xef,0xaa,0xff,0x00,0x00,0xff };   //����3�Σ���ô�Ͷϵ��оƬ������ȴ�
	m_serialPort4->write(send_data, 6);
	m_serialPort4->waitForBytesWritten(10000);
	stopThread4 = true;
	bin_good_4 = true;//�ϵ��ش��󣬷ֵ�bin��������
	//emit finishedInfo4();
}


void SLTTestDemo::serialPortSend1()
{
	int len = ui.tableWidget->rowCount();
	while (stopAutoTest)
	{
		//connectGpib();
		bin_good_1 = false;    //оƬ����ǰ��Ϊfalse���д������Ϊtrue
		isComplete1 = false;
		stopThread1 = false;
		//std::unique_lock<std::mutex> lock(m_mutex);
		clearConnent(ui.tableWidget);
		QEventLoop loop;
		connect(this, SIGNAL(finishedInfo1()), &loop, SLOT(quit()));
		//Sleep(1000);
		for (int i = 0; i < len; i++)
		{
			if (stopThread1)
				break;

			//rec_info1.clear();
			//FD�⹦�ĵ�������Ҫ�ڲ�����֮ǰ��һ�Σ������������һ��0xfd(�Ѿ��������ļ������)
			char send_data[6] = { 0 };
			QString cmdStr = ui.tableWidget->item(i, 1)->text();
			int cmd = cmdStr.toInt(nullptr, 16);
			send_info(send_data, cmd, 0, cmd);
			Sleep(10);   //��mcuʱ��ȥ�ȴ�����pc��Ϣ
			m_serialPort1->write(send_data, 6);
			m_serialPort1->waitForBytesWritten(10000);

			serial1_cmd = cmd;
			emit runT1();
			//m_timer1 = new QTimer(this);
			//m_timer1->setInterval(20000);//������˾Ͳ�����start�������ˡ�
			//connect(m_timer1, SIGNAL(timeout()), this, SLOT(timeRun1(/*QSerialPort **/)), Qt::DirectConnection); //�涨���۵Ĳ������ܶ����źŵĲ������޷�ʵ��һ����ȥ��4��������//��ʱ����isActive()=true��״̬�£�start()��һ�κ󣩣�����ٴΰ��źŲۺ�������ô��ͬʱ�������Σ����߶�Σ����󶨼��Σ�
			//if (!m_timer1->isActive())   //stop()֮��isActive����false.
			//	m_timer1->start();
			
			//emit fini1();
			//recordLog("SerialPort1");

			//���淢�����ݵ����أ���������ת����ʽ���԰ѡ�0xef,0xaa��ת����0xef 0xaa��������ֵ��ʾ�������QString(QLatin1String(send_data))��,�ǽ�����תΪ�ַ��������硰0x32,0xa1����"success"����ʾ��
			//QString path = QCoreApplication::applicationDirPath() + "/" + "SerialPort1.txt";
			//QByteArray SEN = QByteArray(send_data, 6);
			//QString str = SEN.toHex(' ').toUpper();
			//send_rec(path, str, "Send:");

			//��ǰ�̵߳ȴ�����������̷߳�����finishedInfo()�źţ����߳̾ͻ��������������
			//�����Զ���4����ͬ�źţ�һ���̶߳�Ӧһ���źţ�ÿ���̷߳��䲻ͬ���ź�
			//QEventLoop loop;
			//connect(this, SIGNAL(finishedInfo1(/*int value*/)), &loop, SLOT(quit()));
			//send_rec(path, "Connect loop", "Send:");
			loop.exec();
			//if (value == len-1)   //�ϵ����
			//{
			//	QString cmdStr = "0xff";
			//	int cmd = cmdStr.toInt(nullptr, 16);
			//	send_info(send_data, cmd, 0, cmd);
			//	m_serialPort1->write(send_data, 6);
			//	m_serialPort1->waitForBytesWritten(10000);
			//}
			//���ԣ�
			//send_rec(path, "loop quit", "Send:");
		}
		allChipCount++;
		if (bin_good_1)
			failedChipCount++;
		emit updateUI();
		//ui.lcdNumber->display(allChipCount);
		//ui.lcdNumber_2->display(failedChipCount);
		//ui.lcdNumber_3->display((allChipCount - failedChipCount) / allChipCount);
		savePassRate(QString::number(failedChipCount), QString::number(allChipCount), QString::number((allChipCount - failedChipCount) / allChipCount));
		std::unique_lock<std::mutex>lock(m_mutex);
		//QString path = QCoreApplication::applicationDirPath() + "/" + "SerialPort1.txt";
		//send_rec(path, "over will to wait", "over pre:");
		isComplete1 = true;
		cond.notify_one();
		m_condition.wait(lock);//�ͷ���lock��ʹ�����߳̿���ִ�д�std::unique_lock<std::mutex>lock(m_mutex)��ʼ�Ĵ���
		//send_rec(path, "wait to be awake", "over aft:");
	}
}
void SLTTestDemo::serialPortSend2()
{
	int len = ui.tableWidget_2->rowCount();
	while (stopAutoTest)
	{
		isComplete2 = false;
		stopThread2 = false;
		bin_good_2 = false;    //оƬ����ǰ��Ϊfalse���д������Ϊtrue
		//std::unique_lock<std::mutex> lock(m_mutex);
		clearConnent(ui.tableWidget_2);
		QEventLoop loop;
		connect(this, SIGNAL(finishedInfo2()), &loop, SLOT(quit()));
		//Sleep(1000);
		for (int i = 0; i < len; i++)
		{
			if (stopThread2)
				break;
			char send_data[6] = { 0 };
			QString cmdStr = ui.tableWidget_2->item(i, 1)->text();
			int cmd = cmdStr.toInt(nullptr, 16);
			send_info(send_data, cmd, 0, cmd);
			Sleep(10);   //��mcuʱ��ȥ�ȴ�����pc��Ϣ
			m_serialPort2->write(send_data, 6);
			m_serialPort2->waitForBytesWritten(10000);

			serial2_cmd = cmd;
			emit runT2();
			//emit fini2();

			//QString path = QCoreApplication::applicationDirPath() + "/" + "SerialPort2.txt";
			//QByteArray SEN = QByteArray(send_data, 6);
			//QString str = SEN.toHex(' ').toUpper();
			//send_rec(path, str, "Send:");

			//��ǰ�̵߳ȴ�����������̷߳�����finishedInfo()�źţ����߳̾ͻ��������������
			//�����Զ���4����ͬ�źţ�һ���̶߳�Ӧһ���źţ�ÿ���̷߳��䲻ͬ���ź�
			//QEventLoop loop;
			//connect(this, SIGNAL(finishedInfo2()), &loop, SLOT(quit()));
			//send_rec(path, "Connect loop", "Send:");
			loop.exec();

			//send_rec(path, "loop quit", "Send:");
		}
		//isComplete2 = true;

		//if (isComplete1&&isComplete3&&isComplete4)   //˵���������ˣ���ǰ���߳������һ������ģ�Ҫ���������ȴ����߳�
		//{
		//	//m_condition.notify_all();

		//	emit finishedInfoControl();
		//}
		////else   //������˵������û������ģ���ô��ǰ���߳�Ҫ����ȴ����������߳�����
		////{
		////	//m_condition.wait(lock);
		////	QEventLoop loop;
		////	connect(this, SIGNAL(finishedInfo2()), &loop, SLOT(quit()));
		////	loop.exec();
		////}

		//QEventLoop loop;
		//connect(this, SIGNAL(finishedInfo2()), &loop, SLOT(quit()));
		//loop.exec();
		allChipCount++;
		if (bin_good_2)
			failedChipCount++;
		emit updateUI();
		//ui.lcdNumber->display(allChipCount);
		//ui.lcdNumber_2->display(failedChipCount);
		//ui.lcdNumber_3->display((allChipCount - failedChipCount) / allChipCount);
		savePassRate(QString::number(failedChipCount), QString::number(allChipCount), QString::number((allChipCount - failedChipCount) / allChipCount));
		std::unique_lock<std::mutex>lock(m_mutex);
		//QString path = QCoreApplication::applicationDirPath() + "/" + "SerialPort2.txt";
		//send_rec(path, "over will to wait", "over pre:");
		isComplete2 = true;
		cond.notify_one();
		m_condition.wait(lock);
		//send_rec(path, "wait to be awake", "over aft:");
	}
}
void SLTTestDemo::serialPortSend3()
{
	int len = ui.tableWidget->rowCount();
	while (stopAutoTest)
	{
		isComplete3 = false;
		stopThread3 = false;
		bin_good_3 = false;    //оƬ����ǰ��Ϊfalse���д������Ϊtrue
		//std::unique_lock<std::mutex> lock(m_mutex);
		clearConnent(ui.tableWidget_3);
		QEventLoop loop;
		connect(this, SIGNAL(finishedInfo3()), &loop, SLOT(quit()));
		//Sleep(1000);
		for (int i = 0; i < len; i++)
		{
			if (stopThread3)
				break;
			char send_data[6] = { 0 };
			QString cmdStr = ui.tableWidget->item(i, 1)->text();
			int cmd = cmdStr.toInt(nullptr, 16);
			send_info(send_data, cmd, 0, cmd);
			Sleep(10);   //��mcuʱ��ȥ�ȴ�����pc��Ϣ
			m_serialPort3->write(send_data, 6);
			m_serialPort3->waitForBytesWritten(10000);

			serial3_cmd = cmd;
			emit runT3();
			//emit fini3();

			//QString path = QCoreApplication::applicationDirPath() + "/" + "SerialPort3.txt";
			//QByteArray SEN = QByteArray(send_data, 6);
			//QString str = SEN.toHex(' ').toUpper();
			//send_rec(path, str, "Send:");

			//��ǰ�̵߳ȴ�����������̷߳�����finishedInfo()�źţ����߳̾ͻ��������������
			//�����Զ���4����ͬ�źţ�һ���̶߳�Ӧһ���źţ�ÿ���̷߳��䲻ͬ���ź�
			//QEventLoop loop;
			//connect(this, SIGNAL(finishedInfo3()), &loop, SLOT(quit()));
			//send_rec(path, "Connect loop", "Send:");
			loop.exec();

			//send_rec(path, "loop quit", "Send:");
		}
		//isComplete3 = true;

		//if (isComplete1&&isComplete2&&isComplete4)   //˵���������ˣ���ǰ���߳������һ������ģ�Ҫ���������ȴ����߳�
		//{
		//	//m_condition.notify_all();

		//	emit finishedInfoControl();
		//}
		////else   //������˵������û������ģ���ô��ǰ���̵߳ȴ������߳�����
		////{
		////	//m_condition.wait(lock);
		////	QEventLoop loop;
		////	connect(this, SIGNAL(finishedInfo3()), &loop, SLOT(quit()));
		////	loop.exec();
		////}
		//
		//QEventLoop loop;
		//connect(this, SIGNAL(finishedInfo3()), &loop, SLOT(quit()));
		//loop.exec();
		allChipCount++;
		if (bin_good_3)
			failedChipCount++;
		emit updateUI();
		//ui.lcdNumber_2->display(failedChipCount);
		//ui.lcdNumber_3->display((allChipCount - failedChipCount) / allChipCount);
		//ui.lcdNumber->display(allChipCount);
		savePassRate(QString::number(failedChipCount), QString::number(allChipCount), QString::number((allChipCount - failedChipCount) / allChipCount));
		std::unique_lock<std::mutex>lock(m_mutex);
		//QString path = QCoreApplication::applicationDirPath() + "/" + "SerialPort3.txt";
		//send_rec(path, "over will to wait", "over pre:");
		isComplete3 = true;
		cond.notify_one();
		m_condition.wait(lock);
		//send_rec(path, "wait to be awake", "over aft:");
	}
}
void SLTTestDemo::serialPortSend4()
{
	int len = ui.tableWidget->rowCount();
	while (stopAutoTest)
	{
		isComplete4 = false;
		stopThread4 = false;
		bin_good_4 = false;    //оƬ����ǰ��Ϊfalse���д������Ϊtrue
		//std::unique_lock<std::mutex> lock(m_mutex);
		clearConnent(ui.tableWidget_4);
		QEventLoop loop;
		connect(this, SIGNAL(finishedInfo4()), &loop, SLOT(quit()));
		//Sleep(1000);
		for (int i = 0; i < len; i++)
		{
			if (stopThread4)
				break;
			char send_data[6] = { 0 };
			QString cmdStr = ui.tableWidget->item(i, 1)->text();
			int cmd = cmdStr.toInt(nullptr, 16);  //16�������
			send_info(send_data, cmd, 0, cmd);
			Sleep(10);   //��mcuʱ��ȥ�ȴ�����pc��Ϣ
			m_serialPort4->write(send_data, 6);
			m_serialPort4->waitForBytesWritten(10000);

			serial4_cmd = cmd;
			emit runT4();
			//emit fini4();

			//QString path = QCoreApplication::applicationDirPath() + "/" + "SerialPort4.txt";
			//QByteArray SEN = QByteArray(send_data, 6);
			//QString str = SEN.toHex(' ').toUpper();
			//send_rec(path, str, "Send:");

			//��ǰ�̵߳ȴ�����������̷߳�����finishedInfo()�źţ����߳̾ͻ��������������
			//�����Զ���4����ͬ�źţ�һ���̶߳�Ӧһ���źţ�ÿ���̷߳��䲻ͬ���ź�
			//QEventLoop loop;
			//connect(this, SIGNAL(finishedInfo4()), &loop, SLOT(quit()));
			//send_rec(path, "Connect loop", "Send:");
			loop.exec();

			//send_rec(path, "loop quit", "Send:");
		}
		allChipCount++;
		if (bin_good_4)
			failedChipCount++;
		emit updateUI();
		//ui.lcdNumber->display(allChipCount);
		//ui.lcdNumber_2->display(failedChipCount);
		//ui.lcdNumber_3->display((allChipCount - failedChipCount) / allChipCount);
		savePassRate(QString::number(failedChipCount), QString::number(allChipCount), QString::number((allChipCount - failedChipCount) / allChipCount));
		std::unique_lock<std::mutex>lock(m_mutex);
		//QString path = QCoreApplication::applicationDirPath() + "/" + "SerialPort4.txt";
		//send_rec(path, "over will to wait", "over pre:");
		isComplete4 = true;
		cond.notify_one();
		m_condition.wait(lock);   //�ͷ���lock
		//send_rec(path, "wait to be awake", "over aft:");
	}
}

//ÿ�������һ�����һ��
void SLTTestDemo::clearConnent(QTableWidget *table)
{
	table->removeColumn(2);
	table->removeColumn(2);
	table->setColumnCount(4);
	QStringList header;
	header << QString::fromLocal8Bit("������") << QString::fromLocal8Bit("������") << QString::fromLocal8Bit("���") << QString::fromLocal8Bit("��Ϣ");
	table->setHorizontalHeaderLabels(header);
}

void SLTTestDemo::control()
{
	while (closeControl)
	{
		//20ms��ʱ��ʹÿ��������һ�ֲ����Ƚ�isComplete1..����Ϊfalse�ˣ��ٽ���������жϣ�
		//��Ȼ������ѵ�5���̺߳󣬵�5���߳��Ƚ���true�Ļ����Ǿ��ַ���һ�η�bin���������һ��оƬ�շ���һС�����ȥ��binȥ�ˣ���ʵ��û�в��ԣ�
		Sleep(20);   
		if (isComplete1&&isComplete2&&isComplete3&&isComplete4)  //����оƬһ�ֲ�����ɣ���оƬ
		{
			//Sleep(500);  //��֤���д��ڷ��Ͷ�����ȴ�״̬

			Sleep(1000);   //����оƬ�ϵ���ַŵ�

			binON(); 
			connectGpib();
			//ui.textEdit->append(QString::fromLocal8Bit("����оƬ������") + QString::number(allChipCount));
			m_condition.notify_all();
			
			//emit finishedInfo1();
			//emit finishedInfo2();
			//emit finishedInfo3();
			//emit finishedInfo4();
		}
		else   //�Ƚ���ȴ�����4��оƬ������һ�ֺ���
		{
			//QEventLoop loop;
			//connect(this, SIGNAL(finishedInfoControl()), &loop, SLOT(quit()));
			//loop.exec();
			std::unique_lock<std::mutex>lock(mut);
			cond.wait(lock);
		}
	}
}

//��ʼ����
void SLTTestDemo::on_pushButton_3_clicked()
{
	//ui.pushButton_3->setEnabled(false);
	emit pushButton_3_disable();
	QDateTime time;
	QString now = time.currentDateTime().toString("yyyy/MM/dd_HH:mm:ss");
	ui.textEdit->append(now + ":" + QString::fromLocal8Bit("��ʼ����."));
	//findRsrc();
	openGpib();
	connectGpib();
	t1 = new std::thread(&SLTTestDemo::serialPortSend1, this/*, m_serialPort1*//*, 1*/);
	t2 = new std::thread(&SLTTestDemo::serialPortSend2, this/*, m_serialPort2*//*, 2*/);
	t3 = new std::thread(&SLTTestDemo::serialPortSend3, this/*, m_serialPort3*//*, 3*/);
	t4 = new std::thread(&SLTTestDemo::serialPortSend4, this/*, m_serialPort4*//*, 4*/);

	tControl = new std::thread(&SLTTestDemo::control, this);

}
//������ͣ/����
void SLTTestDemo::on_pushButton_4_clicked()
{
	//QEventLoop loop;
	//connect(/*m_serialPort*/this, SIGNAL(finishedInfo()), &loop, SLOT(quit()));
	//loop.exec();

	//����
	emit finishedInfo1(/*5*/);   //�źŴ��ݲ������ۣ��ź�emitʱ��ʲô���Ǿ���ʲô���������������5����connect(/*m_serialPort*/this  /*t3*/, SIGNAL(finishedInfo(int/* num*/)), &loop, SLOT(quit()));������������ж���5�����ԼӲ��Ӳ���û��
	//emit finishedInfo(2);
	//emit finishedInfo(3);
	//emit finishedInfo(4);

}


//�����յ�����
void SLTTestDemo::recDataParse(char *packet, QTableWidget *tb/*,int id*/)
{
	//static int id = 0;
	//if (id > 30)
	//{
	//	id = 0;
	//}
	//char compare[3] = { 0xef,0xaa,0x00 };
	//rec_ack *rec = (rec_ack *)packet;
	//if (rec->SyncWord[0] == compare[0] && rec->SyncWord[1] == compare[1] /*&& rec->Msgid== compare[2]*/)
	//{
	//	if (rec->Result == compare[1])
	//	{
	//		tb->setItem(id, 2, new QTableWidgetItem(QString::fromLocal8Bit("���Գɹ�")));
	//	}
	//	else
	//	{
	//		tb->setItem(id, 2, new QTableWidgetItem(QString::fromLocal8Bit("����ʧ��")));
	//	}
	//	emit finishedInfo();
	//	id++;
	//}
}

//m_serialPort1�Ľ���
void SLTTestDemo::receiveInfo1()
{
	//QString path = QCoreApplication::applicationDirPath() + "/" + "SerialPort1.txt";
	//QByteArray qArray = m_serialPort1->readAll();
	//QString str = qArray.toHex(' ').toUpper();
	//send_rec(path, str, "Receive_Src:");

	//QByteArray rec_info = m_serialPort1->readAll();    //���ַ�����ã����ǻ����մ������������Ƿ����ν����ˣ���һ��һ����һ��һ�룬�����յ��Ĳ��������޷��ж�Ϊ����
	//QByteArray rec_info;
	rec_info1.append(m_serialPort1->readAll()/*qArray*/);
	//������־
	//QString path = QCoreApplication::applicationDirPath() + "/" + "SerialPort1.txt";
	char send_data[6] = { 0xef,0xaa,0xff,0x00,0x00,0xff };
	int id;
	int rowSize = ui.tableWidget->rowCount();
	char compare[6] = { 0xef,0xaa,0x00,0x55,0xfb,0x33 };

	for (int j = 0; j < rec_info1.length(); j++)
	{
		if (rec_info1.at(j) == compare[0] && j < rec_info1.length() - 5)//����������һ��Ԫ��������0xef����j+1��ֱ��Խ�籨���ˡ����ȼ�5�ǿ��Լ��㵽size
		{
			if (rec_info1.at(j + 1) == compare[1])  //����ֻ�Ƕ�����0xef,0xaa�ˣ�����Ҫ�ж�У����Ƿ���ȷ�����������жϳ��Ƿ�������һ��
			{
				unsigned char Size[2] = { rec_info1.at(j + 3),rec_info1.at(j + 4) };
				unsigned short size = reverse_uint16(Size);
				if (size + j + 5 < rec_info1.length())   //�ӵ�У��ͣ������ڼ���У��͵�ʱ�򳬳��˳��ȷ�Χ//size+5+j��λ����У��ͣ�����������if�˵���յ����ݳ��ȹ���
				{
					char checkSum = std::accumulate(rec_info1.data() + j + 2, rec_info1.data() + j + 5 + size, 0);//У��ʹ�CMD��ʼ��size�����ĳ��ȣ���4��û��У��ͣ���5����У���
					if (rec_info1.at(j + 5 + size) == checkSum)  //����ȷ��Ϊһ������//size+5+j��λ����У���
					{
						static int timeoutCount1 = 0;
						static int IDnumber;
						if (rec_info1.at(j + 2) == compare[4])   //�յ�������Ϣ��
						{
							//char *rec = rec_info1.data() + j + 5;
							//QByteArray qba = QByteArray(rec, size);
							//send_rec(path, QString(qba), "Receive:");
							rec_info1.remove(j, 5 + size + 1);   //��j��λ�ÿ�ʼ����5+size+1��У��͵ĳ���

						}
						else
						{
							//Sleep(1000);
							//QString str = rec_info1.toHex(' ').toUpper();
							//send_rec(path, str, "Receive:");
							for (int i = 0; i < rowSize; i++)
							{
								QString cmdStr = ui.tableWidget->item(i, 1)->text();
								if (rec_info1.at(j + 2) == (char)cmdStr.toInt(nullptr, 16))
								{
									id = i;
								}
							}
							//Ӧ��д��rec_info.at(2)==0x00,rec_info.at(2)==0x01,rec_info.at(2)==0xff,Ӧ�ø��������ļ��ߣ����ø���id��
							if (id == 0 || id == 1 || id == rowSize)         //char compare[6] = { 0xef,0xaa,0x00,0x55,0xfb,0x33 };
							{
								if (id == 0)
								{
									int xinID = rec_info1.at(j + 5);  //size�����һ��λ��//��Ϣ����int���͵�оƬλ��id ��0,1,2,3�ĸ�
									IDnumber = xinID;
									chipID1 = xinID;
									QByteArray information = QByteArray(rec_info1.data() + j + 6, size - 1);   //��Ϊsize�ĳ�����������1���ֽڵ�оƬ��Ϣ
									//QString str = QString(QLatin1String(rec_info.data() + j + 6));//////////��ȷת����ʽ�����ԣ������������һλ��У��ͣ���ȥ��
									ui.tableWidget->setItem(id, 3, new QTableWidgetItem(QString::number(xinID) + "," + QString(information)));
									rec_info1.remove(j, 5 + size + 1);
									m_timer1->stop();
									emit finishedInfo1();
									//send_rec(path, "Send signal to quit", "Receive:");
								}
								else
								{
									if (rec_info1.at(j + 5) == compare[5])   //0x33�ǳ�ʱ���᲻��������������԰��ĵ�6��Ԫ��Ҳ������0x33,�����͵��ɳ�ʱȥ��ʾ�ˣ�����ʾ����
									{
										////3�γ�ʱ�����ϵ��������Ϊ1�γ�ʱ�Ͷϵ�
										//bin_good_1 = true;
										//QByteArray info = QByteArray(rec_info1.data() + j + 6, size - 1);
										//QTableWidgetItem *item = new QTableWidgetItem(QString(info));
										//item->setBackgroundColor(QColor(255, 0, 0));
										//ui.tableWidget->setItem(id, 3, item);
										//timeoutCount1++;
										//QDateTime time;
										//QString currentTime = time.currentDateTime().toString("yyyy/MM/dd_HH:mm:ss.zzz");
										//QString errCase = ui.tableWidget->item(id, 0)->text();
										//saveConnent(NULL, errCase, QString(info), QString::number(IDnumber), currentTime);
										//if (timeoutCount1 == 3)
										//{
										//	//bin_good_1 = true;
										//	timeoutCount1 = 0;
										//	//char send_data[6] = { 0 };
										//	//QString cmdStr = "0xff";
										//	//int cmd = cmdStr.toInt(nullptr, 16);
										//	//send_info(send_data, cmd, 0, cmd);
										//	QDateTime time;
										//	QString now = time.currentDateTime().toString("yyyy/MM/dd_HH:mm:ss");
										//	ui.textEdit->append(now + ":" + QString::fromLocal8Bit("510��ʱ3�Σ�ִ�жϵ磡"));
										//	m_serialPort1->write(send_data, 6);                 //�յ�3�γ�ʱ���ͷ��Ͷϵ����ͬʱ�����߳��˳�ѭ������ȴ�
										//	m_serialPort1->waitForBytesWritten(10000);
										//	stopThread1 = true;
										//	//failedChipCount++;
										//}
										//rec_info1.remove(j, 5 + size + 1);
										//m_timer1->stop();
										//emit finishedInfo1();
										////send_rec(path, "Send signal to quit", "Receive:");




										//1�γ�ʱ��ִ�жϵ����
										bin_good_1 = true;
										QByteArray info = QByteArray(rec_info1.data() + j + 6, size - 1);
										QTableWidgetItem *item = new QTableWidgetItem(QString(info));
										item->setBackgroundColor(QColor(255, 0, 0));
										ui.tableWidget->setItem(id, 3, item);
										QDateTime time;
										QString currentTime = time.currentDateTime().toString("yyyy/MM/dd_HH:mm:ss.zzz");
										QString errCase = ui.tableWidget->item(id, 0)->text();
										saveConnent(NULL, errCase, QString(info), QString::number(IDnumber), currentTime);
										ui.textEdit->append(currentTime + ":" + QString::fromLocal8Bit("510��ʱ��ִ�жϵ磡"));
										m_serialPort1->write(send_data, 6);		              //�յ�3�γ�ʱ���ͷ��Ͷϵ����ͬʱ�����߳��˳�ѭ������ȴ�
										m_serialPort1->waitForBytesWritten(10000);
										stopThread1 = true;
										rec_info1.remove(j, 5 + size + 1);
										m_timer1->stop();
										emit finishedInfo1();
									}
									else  //���ǳ�ʱ��ʱ��
									{
										QByteArray info = QByteArray(rec_info1.data() + j + 5, size);
										ui.tableWidget->setItem(id, 3, new QTableWidgetItem(QString(info)));
										rec_info1.remove(j, 5 + size + 1);
										m_timer1->stop();
										emit finishedInfo1();
										//send_rec(path, "Send signal to quit", "Receive:");
									}
									//QByteArray info = QByteArray(rec_info1.data() + j + 5, size);
									//ui.tableWidget->setItem(id, 3, new QTableWidgetItem(QString(info)));
									//rec_info1.remove(j, 5 + size + 1);
									//emit finishedInfo1();
								}
							}
							if (id > 1 && id != rowSize)
							{
								if (size == 1)   //ֻ��result��û��һЩ��Ϣ
								{
									if (rec_info1.at(j + 5) == compare[1])
									{
										ui.tableWidget->setItem(id, 2, new QTableWidgetItem(QString::fromLocal8Bit("���Գɹ�")));
										//rec_info1.remove(j, 5 + size + 1);
									}
									if (rec_info1.at(j + 5) == compare[3])
									{
										bin_good_1 = true;
										QTableWidgetItem *item = new QTableWidgetItem(QString::fromLocal8Bit("����ʧ��"));
										item->setBackgroundColor(QColor(255, 0, 0));
										ui.tableWidget->setItem(id, 2, item);
										//rec_info1.remove(j, 5 + size + 1);
										//failedChipCount++;
									}
									rec_info1.remove(j, 5 + size + 1);
									m_timer1->stop();
									emit finishedInfo1(/*1*/);
									//send_rec(path, "Send signal to quit", "Receive:");
									//return;
								}
								else
								{
									if (rec_info1.at(j+5) == compare[1])
									{
										ui.tableWidget->setItem(id, 2, new QTableWidgetItem(QString::fromLocal8Bit("���Գɹ�")));
										//QString info(rec_info.data() + 6);
										//QString str = QString(QLatin1String(rec_info.data() + 6));//////////��ȷת����ʽ�����ԣ������������һλ��У��ͣ���ȥ��
										QByteArray info = QByteArray(rec_info1.data() + j + 6, size - 1);  //��Ϊsize�ĳ�����������1���ֽڵ�result 0xaa
										ui.tableWidget->setItem(id, 3, new QTableWidgetItem(QString(info)));
										//rec_info1.remove(j, 5 + size + 1);
									}
									if (rec_info1.at(j+5) == compare[3])
									{
										bin_good_1 = true;
										ui.tableWidget->setItem(id, 2, new QTableWidgetItem(QString::fromLocal8Bit("����ʧ��")));
										//QString info(rec_info.data() + 6);
										QByteArray info = QByteArray(rec_info1.data() + j + 6, size - 1);        //��Ϊsize�ĳ�����������1���ֽڵ�result 0x55
										QTableWidgetItem *item = new QTableWidgetItem(QString(info));
										item->setBackgroundColor(QColor(255, 0, 0));
										ui.tableWidget->setItem(id, 3, item);
										//rec_info1.remove(j, 5 + size + 1);
										//failedChipCount++;
										QDateTime time;
										QString currentTime = time.currentDateTime().toString("yyyy/MM/dd_HH:mm:ss.zzz");
										QString errCase = ui.tableWidget->item(id, 0)->text();
										saveConnent(NULL, errCase, QString(info), QString::number(IDnumber), currentTime);
										
									}
									if (rec_info1.at(j + 5) == compare[5])   //0x33�ǳ�ʱ
									{
										//��ʱ3��ִ�жϵ����
										//bin_good_1 = true;
										//QByteArray info = QByteArray(rec_info1.data() + j + 6, size - 1);
										//QTableWidgetItem *item = new QTableWidgetItem(QString(info));
										//item->setBackgroundColor(QColor(255, 0, 0));
										//ui.tableWidget->setItem(id, 3, item);
										//timeoutCount1++;
										//QDateTime time;
										//QString currentTime = time.currentDateTime().toString("yyyy/MM/dd_HH:mm:ss.zzz");
										//QString errCase = ui.tableWidget->item(id, 0)->text();
										//saveConnent(NULL, errCase, QString(info), QString::number(IDnumber), currentTime);
										//if (timeoutCount1 == 3)
										//{
										//	//bin_good_1 = true;
										//	QDateTime time;
										//	QString now = time.currentDateTime().toString("yyyy/MM/dd_HH:mm:ss");
										//	ui.textEdit->append(now + ":" + QString::fromLocal8Bit("510��ʱ3�Σ�ִ�жϵ磡"));
										//	timeoutCount1 = 0;
										//	m_serialPort1->write(send_data, 6);                 //�յ�3�γ�ʱ���ͷ��Ͷϵ����ͬʱ�����߳��˳�ѭ������ȴ�
										//	m_serialPort1->waitForBytesWritten(10000);
										//	stopThread1 = true;
										//	//emit finishedInfo1();
										//	//failedChipCount++;
										//}


										
										//��ʱ1�ξ�ִ�жϵ����
										bin_good_1 = true;
										QByteArray info = QByteArray(rec_info1.data() + j + 6, size - 1);
										QTableWidgetItem *item = new QTableWidgetItem(QString(info));
										item->setBackgroundColor(QColor(255, 0, 0));
										ui.tableWidget->setItem(id, 3, item);
										QDateTime time;
										QString currentTime = time.currentDateTime().toString("yyyy/MM/dd_HH:mm:ss.zzz");
										QString errCase = ui.tableWidget->item(id, 0)->text();
										saveConnent(NULL, errCase, QString(info), QString::number(IDnumber), currentTime);
										ui.textEdit->append(currentTime + ":" + QString::fromLocal8Bit("510��ʱ��ִ�жϵ磡"));
										m_serialPort1->write(send_data, 6);                 //�յ�3�γ�ʱ���ͷ��Ͷϵ����ͬʱ�����߳��˳�ѭ������ȴ�
										m_serialPort1->waitForBytesWritten(10000);
										stopThread1 = true;
									}
									rec_info1.remove(j, 5 + size + 1);
									m_timer1->stop();
									emit finishedInfo1(/*1*/);
									//send_rec(path, "Send signal to quit", "Receive:");
								}
							}
						}
						//�������һ���Ľ����������´�ѭ��Ӧ��ֱ��������һ�������������j��һ��һ�������ӣ���һ���������д���0xef,���ֽ����ˡ�
						//if (j + 6 + size < rec_info.length())//���size��0����ôһ����������6�Ĺ̶�����,���Ǽ�5������Ϊ���е�forѭ�����ֽ�����һ��j++��
						//{
						//	j = j + 5 + size;
						//}
						if (rec_info1.length() > 0)//�����ǽ�����һ����ɾһ��
							j = -1;
					}
				}
			}
		}
	}


	
	
	//QByteArray rec_info = m_serialPort1->readAll();

	//int id;
	//int rowSize = ui.tableWidget->rowCount();
	//char compare[5] = { 0xef,0xaa,0x00,0x55,0xfb };
	//char checkSum = std::accumulate(rec_info.data() + 2, rec_info.data() + rec_info.length() - 1, 0);
	//unsigned char Size[2] = { rec_info.at(3),rec_info.at(4) };
	//unsigned short size = reverse_uint16(Size);

	//////������־
	//QString path = QCoreApplication::applicationDirPath() + "/" + "SerialPort1.txt";
	////QString str = rec_info.toHex(' ').toUpper();
	////send_rec(path, str, "Receive:");

	////�յ�MCU��PC�ĵ�����Ϣ���浽����(�յ�������Ϣ)
	//if (rec_info.at(0)==compare[0]&&rec_info.at(1)==compare[1]&& rec_info.at(2) == compare[4])
	//{
	//	
	//	char *rec = rec_info.data() + 5;
	//	QByteArray qba = QByteArray(rec, size);
	//	send_rec(path, QString(qba), "Receive:");
	//	//emit finishedInfo1();
	//}

	//else
	//{
	//	QString str = rec_info.toHex(' ').toUpper();
	//	send_rec(path, str, "Receive:");
	//	if (rec_info.at(0) == compare[0] && rec_info.at(1) == compare[1] && rec_info.at(rec_info.length() - 1) == checkSum)
	//	{
	//		for (int i = 0; i < rowSize; i++)
	//		{
	//			QString cmdStr = ui.tableWidget->item(i, 1)->text();
	//			if (rec_info.at(2) == (char)cmdStr.toInt(nullptr, 16))
	//			{
	//				id = i;
	//			}
	//		}
	//		//Ӧ��д��rec_info.at(2)==0x00,rec_info.at(2)==0x01,rec_info.at(2)==0xff,Ӧ�ø��������ļ��ߣ����ø���id��
	//		if (id == 0 || id == 1 || id == rowSize)
	//		{

	//			//ֻ�е�һ�������Ƿ���һ��id�Ͱ汾��Ϣ���ڶ������һ��Ҳû��result��ֻ���ַ�����Ϣ
	//			if (id == 0)
	//			{
	//				int xinID = rec_info.at(5);
	//				QString str = QString(QLatin1String(rec_info.data() + 6));//////////��ȷת����ʽ�����ԣ������������һλ��У��ͣ���ȥ��
	//				ui.tableWidget->setItem(id, 3, new QTableWidgetItem(QString::number(xinID) + "," + str));
	//				emit finishedInfo1();
	//			}
	//			else
	//			{
	//				QString info(rec_info.data() + 5);
	//				QString str = QString(QLatin1String(rec_info.data() + 5));//////////��ȷת����ʽ�����ԣ������������һλ��У��ͣ���ȥ��
	//				ui.tableWidget->setItem(id, 3, new QTableWidgetItem(info));
	//				emit finishedInfo1();
	//			}
	//		}
	//		//unsigned char Size[2] = { rec_info.at(3),rec_info.at(4) };
	//		//unsigned short size = reverse_uint16(Size);
	//		if (id > 1 && id != rowSize)
	//		{
	//			if (size == 1)   //ֻ��result��û��һЩ��Ϣ
	//			{
	//				if (rec_info.at(5) == compare[1])
	//				{
	//					ui.tableWidget->setItem(id, 2, new QTableWidgetItem(QString::fromLocal8Bit("���Գɹ�")));
	//				}
	//				if (rec_info.at(5) == compare[3])
	//				{
	//					ui.tableWidget->setItem(id, 2, new QTableWidgetItem(QString::fromLocal8Bit("����ʧ��")));
	//				}
	//				emit finishedInfo1(/*1*/);
	//				//return;
	//			}
	//			else
	//			{
	//				if (rec_info.at(5) == compare[1])
	//				{
	//					ui.tableWidget->setItem(id, 2, new QTableWidgetItem(QString::fromLocal8Bit("���Գɹ�")));
	//					QString info(rec_info.data() + 6);
	//					QString str = QString(QLatin1String(rec_info.data() + 6));//////////��ȷת����ʽ�����ԣ������������һλ��У��ͣ���ȥ��
	//					ui.tableWidget->setItem(id, 3, new QTableWidgetItem(info));
	//				}
	//				if (rec_info.at(5) == compare[3])
	//				{
	//					ui.tableWidget->setItem(id, 2, new QTableWidgetItem(QString::fromLocal8Bit("����ʧ��")));
	//					QString info(rec_info.data() + 6);
	//					ui.tableWidget->setItem(id, 3, new QTableWidgetItem(info));
	//				}
	//				emit finishedInfo1(/*1*/);
	//			}
	//		}
	//	}
	//}

	//if (rec_info.at(0) == compare[0] && rec_info.at(1) == compare[1] && rec_info.at(rec_info.length()-1)==checkSum)
	//{
	//	for (int i = 0; i < rowSize; i++)
	//	{
	//		QString cmdStr = ui.tableWidget->item(i, 1)->text();
	//		if (rec_info.at(2) == (char)cmdStr.toInt(nullptr, 16))
	//		{
	//			id = i;
	//		}
	//	}
	//	//unsigned char Size[2] = { rec_info.at(3),rec_info.at(4) };
	//	//unsigned short size = reverse_uint16(Size);
	//	//if (size == 1)   //ֻ��result��û��һЩ��Ϣ
	//	//{
	//	//	if (rec_info.at(5) == compare[1])
	//	//	{
	//	//		ui.tableWidget->setItem(id, 2, new QTableWidgetItem(QString::fromLocal8Bit("���Գɹ�")));
	//	//	}
	//	//	if (rec_info.at(5) == compare[3])
	//	//	{
	//	//		ui.tableWidget->setItem(id, 2, new QTableWidgetItem(QString::fromLocal8Bit("����ʧ��")));
	//	//	}
	//	//	emit finishedInfo1(/*2*/);
	//	//	//return;
	//	//}
	//	//else
	//	//{
	//	//	if (rec_info.at(5) == compare[1])
	//	//	{
	//	//		ui.tableWidget->setItem(id, 2, new QTableWidgetItem(QString::fromLocal8Bit("���Գɹ�")));
	//	//		QString info(rec_info.data() + 6);
	//	//		ui.tableWidget->setItem(id, 3, new QTableWidgetItem(info));
	//	//	}
	//	//	if (rec_info.at(5) == compare[3])
	//	//	{
	//	//		ui.tableWidget->setItem(id, 2, new QTableWidgetItem(QString::fromLocal8Bit("����ʧ��")));
	//	//		QString info(rec_info.data() + 6);
	//	//		ui.tableWidget->setItem(id, 3, new QTableWidgetItem(info));
	//	//	}
	//	//	emit finishedInfo1(/*2*/);
	//	//}


	//	if (id == 0 || id == 1 || id == rowSize)
	//	{
	//		//QString info(rec_info.data() + 5);
	//		//QString str = QString(QLatin1String(rec_info.data() + 5));//////////��ȷת����ʽ�����ԣ������������һλ��У��ͣ���ȥ��
	//		//ui.tableWidget->setItem(id, 3, new QTableWidgetItem(info));
	//		//emit finishedInfo1();

	//		//ֻ�е�һ�������Ƿ���һ��id�Ͱ汾��Ϣ���ڶ������һ��Ҳû��result��ֻ���ַ�����Ϣ
	//		if (id == 0)
	//		{
	//			int xinID = rec_info.at(5);
	//			//ui.tableWidget_4->setItem(id, 3, new QTableWidgetItem(QString::number(xinID)));
	//			//ui.tableWidget_4->setItem(id, 3, new QTableWidgetItem(","));
	//			//QString info(rec_info.data() + 6);
	//			QString str = QString(QLatin1String(rec_info.data() + 6));//////////��ȷת����ʽ�����ԣ������������һλ��У��ͣ���ȥ��
	//			ui.tableWidget->setItem(id, 3, new QTableWidgetItem(QString::number(xinID) + "," + str));
	//			emit finishedInfo1();
	//		}
	//		else
	//		{
	//			QString info(rec_info.data() + 5);
	//			QString str = QString(QLatin1String(rec_info.data() + 5));//////////��ȷת����ʽ�����ԣ������������һλ��У��ͣ���ȥ��
	//			ui.tableWidget->setItem(id, 3, new QTableWidgetItem(info));
	//			emit finishedInfo1();
	//		}
	//	}
	//	unsigned char Size[2] = { rec_info.at(3),rec_info.at(4) };
	//	unsigned short size = reverse_uint16(Size);
	//	if (id > 1 && id != rowSize)
	//	{
	//		if (size == 1)   //ֻ��result��û��һЩ��Ϣ
	//		{
	//			if (rec_info.at(5) == compare[1])
	//			{
	//				ui.tableWidget->setItem(id, 2, new QTableWidgetItem(QString::fromLocal8Bit("���Գɹ�")));
	//			}
	//			if (rec_info.at(5) == compare[3])
	//			{
	//				ui.tableWidget->setItem(id, 2, new QTableWidgetItem(QString::fromLocal8Bit("����ʧ��")));
	//			}
	//			emit finishedInfo1(/*1*/);
	//			//return;
	//		}
	//		else
	//		{
	//			if (rec_info.at(5) == compare[1])
	//			{
	//				ui.tableWidget->setItem(id, 2, new QTableWidgetItem(QString::fromLocal8Bit("���Գɹ�")));
	//				QString info(rec_info.data() + 6);
	//				QString str = QString(QLatin1String(rec_info.data() + 6));//////////��ȷת����ʽ�����ԣ������������һλ��У��ͣ���ȥ��
	//				ui.tableWidget->setItem(id, 3, new QTableWidgetItem(info));
	//			}
	//			if (rec_info.at(5) == compare[3])
	//			{
	//				ui.tableWidget->setItem(id, 2, new QTableWidgetItem(QString::fromLocal8Bit("����ʧ��")));
	//				QString info(rec_info.data() + 6);
	//				ui.tableWidget->setItem(id, 3, new QTableWidgetItem(info));
	//			}
	//			emit finishedInfo1(/*1*/);
	//		}
	//	}
	//}
}
//m_serialPort2�Ľ���
void SLTTestDemo::receiveInfo2()
{
	//QString path = QCoreApplication::applicationDirPath() + "/" + "SerialPort2.txt";
	//QByteArray qArray = m_serialPort2->readAll();
	//QString str = qArray.toHex(' ').toUpper();
	//send_rec(path, str, "Receive_Src:");

	rec_info2.append(m_serialPort2->readAll()/*qArray*/);
	//������־
	//QString path = QCoreApplication::applicationDirPath() + "/" + "SerialPort2.txt";
	char send_data[6] = { 0xef,0xaa,0xff,0x00,0x00,0xff };
	int id;
	int rowSize = ui.tableWidget_2->rowCount();
	char compare[6] = { 0xef,0xaa,0x00,0x55,0xfb,0x33 };

	for (int j = 0; j < rec_info2.length(); j++)
	{
		if (rec_info2.at(j) == compare[0] && j < rec_info2.length() - 5)//����������һ��Ԫ��������0xef����j+1��ֱ��Խ�籨���ˡ����ȼ�5�ǿ��Լ��㵽size
		{
			if (rec_info2.at(j + 1) == compare[1])  //����ֻ�Ƕ�����0xef,0xaa�ˣ�����Ҫ�ж�У����Ƿ���ȷ�����������жϳ��Ƿ�������һ��
			{
				unsigned char Size[2] = { rec_info2.at(j + 3),rec_info2.at(j + 4) };
				unsigned short size = reverse_uint16(Size);
				if (size + j + 5 < rec_info2.length())   //�ӵ�У��ͣ������ڼ���У��͵�ʱ�򳬳��˳��ȷ�Χ//size+5+j��λ����У���
				{
					char checkSum = std::accumulate(rec_info2.data() + j + 2, rec_info2.data() + j + 5 + size, 0);//У��ʹ�CMD��ʼ��size�����ĳ��ȣ���4��û��У��ͣ���5����У���
					if (rec_info2.at(j + 5 + size) == checkSum)  //����ȷ��Ϊһ������//size+5+j��λ����У���
					{
						static int timeoutCount2 = 0;
						static int IDnumber;
						if (rec_info2.at(j + 2) == compare[4])   //�յ�������Ϣ��
						{
							//char *rec = rec_info2.data() + j + 5;
							//QByteArray qba = QByteArray(rec, size);
							//send_rec(path, QString(qba), "Receive:");
							rec_info2.remove(j, 5 + size + 1);   //��j��λ�ÿ�ʼ����5+size+1��У��͵ĳ���

						}
						else
						{
							//Sleep(1000);
							//QString str = rec_info2.toHex(' ').toUpper();
							//send_rec(path, str, "Receive:");
							for (int i = 0; i < rowSize; i++)
							{
								QString cmdStr = ui.tableWidget->item(i, 1)->text();
								if (rec_info2.at(j + 2) == (char)cmdStr.toInt(nullptr, 16))
								{
									id = i;
								}
							}
							if (id == 0 || id == 1 || id == rowSize)
							{
								if (id == 0)
								{
									int xinID = rec_info2.at(j + 5);  //size�����һ��λ��//��Ϣ����int���͵�оƬλ��id ��0,1,2,3�ĸ�
									IDnumber = xinID;
									chipID2 = xinID;
									QByteArray information = QByteArray(rec_info2.data() + j + 6, size-1);
									//QString str = QString(QLatin1String(rec_info.data() + j + 6));//////////��ȷת����ʽ�����ԣ������������һλ��У��ͣ���ȥ��
									ui.tableWidget_2->setItem(id, 3, new QTableWidgetItem(QString::number(xinID) + "," + QString(information)));
									rec_info2.remove(j, 5 + size + 1);
									m_timer2->stop();
									emit finishedInfo2();
									//send_rec(path, "Send signal to quit", "Receive:");
								}
								else
								{
									if (rec_info2.at(j + 5) == compare[5])   //0x33�ǳ�ʱ���᲻��������������԰��ĵ�6��Ԫ��Ҳ������0x33,�����͵��ɳ�ʱȥ��ʾ�ˣ�����ʾ����
									{
										//bin_good_2 = true;
										//QByteArray info = QByteArray(rec_info2.data() + j + 6, size - 1);
										//QTableWidgetItem *item = new QTableWidgetItem(QString(info));
										//item->setBackgroundColor(QColor(255, 0, 0));
										//ui.tableWidget_2->setItem(id, 3, item);
										//QDateTime time;
										//QString currentTime = time.currentDateTime().toString("yyyy/MM/dd_HH:mm:ss.zzz");
										//QString errCase = ui.tableWidget_2->item(id, 0)->text();
										//saveConnent(NULL, errCase, QString(info), QString::number(IDnumber), currentTime);
										//timeoutCount2++;
										//if (timeoutCount2 == 3)
										//{
										//	//bin_good_2 = true;
										//	QDateTime time;
										//	QString now = time.currentDateTime().toString("yyyy/MM/dd_HH:mm:ss");
										//	ui.textEdit->append(now + ":" + QString::fromLocal8Bit("510��ʱ3�Σ�ִ�жϵ磡"));
										//	timeoutCount2 = 0;
										//	m_serialPort2->write(send_data, 6);                 //�յ�3�γ�ʱ���ͷ��Ͷϵ����ͬʱ�����߳��˳�ѭ������ȴ�
										//	m_serialPort2->waitForBytesWritten(10000);
										//	stopThread2 = true;
										//	//failedChipCount++;
										//}
										//rec_info2.remove(j, 5 + size + 1);
										//m_timer2->stop();
										//emit finishedInfo2();
										////send_rec(path, "Send signal to quit", "Receive:");





										bin_good_2 = true;
										QByteArray info = QByteArray(rec_info2.data() + j + 6, size - 1);
										QTableWidgetItem *item = new QTableWidgetItem(QString(info));
										item->setBackgroundColor(QColor(255, 0, 0));
										ui.tableWidget_2->setItem(id, 3, item);
										QDateTime time;
										QString currentTime = time.currentDateTime().toString("yyyy/MM/dd_HH:mm:ss.zzz");
										QString errCase = ui.tableWidget_2->item(id, 0)->text();
										saveConnent(NULL, errCase, QString(info), QString::number(IDnumber), currentTime);
										ui.textEdit->append(currentTime + ":" + QString::fromLocal8Bit("510��ʱ��ִ�жϵ磡"));
										m_serialPort2->write(send_data, 6);                 //�յ�3�γ�ʱ���ͷ��Ͷϵ����ͬʱ�����߳��˳�ѭ������ȴ�
										m_serialPort2->waitForBytesWritten(10000);
										stopThread2 = true;
										rec_info2.remove(j, 5 + size + 1);
										m_timer2->stop();
										emit finishedInfo2();
									}
									else
									{
										QByteArray info = QByteArray(rec_info2.data() + j + 5, size);
										ui.tableWidget_2->setItem(id, 3, new QTableWidgetItem(QString(info)));
										rec_info2.remove(j, 5 + size + 1);
										m_timer2->stop();
										emit finishedInfo2();
										//send_rec(path, "Send signal to quit", "Receive:");
									}
								}
							}
							if (id > 1 && id != rowSize)
							{
								if (size == 1)   //ֻ��result��û��һЩ��Ϣ
								{
									if (rec_info2.at(j + 5) == compare[1])
									{
										ui.tableWidget_2->setItem(id, 2, new QTableWidgetItem(QString::fromLocal8Bit("���Գɹ�")));
										//rec_info1.remove(j, 5 + size + 1);
									}
									if (rec_info2.at(j + 5) == compare[3])
									{
										bin_good_2 = true;
										QTableWidgetItem *item = new QTableWidgetItem(QString::fromLocal8Bit("����ʧ��"));
										item->setBackgroundColor(QColor(255, 0, 0));
										ui.tableWidget_2->setItem(id, 2, item);
										//rec_info1.remove(j, 5 + size + 1);
										//failedChipCount++;
									}
									rec_info2.remove(j, 5 + size + 1);
									m_timer2->stop();
									emit finishedInfo2(/*1*/);
									//send_rec(path, "Send signal to quit", "Receive:");
									//return;
								}
								else
								{
									if (rec_info2.at(j + 5) == compare[1])
									{
										ui.tableWidget_2->setItem(id, 2, new QTableWidgetItem(QString::fromLocal8Bit("���Գɹ�")));
										//QString info(rec_info.data() + 6);
										//QString str = QString(QLatin1String(rec_info.data() + 6));//////////��ȷת����ʽ�����ԣ������������һλ��У��ͣ���ȥ��
										QByteArray info = QByteArray(rec_info2.data() + j + 6, size-1);
										ui.tableWidget_2->setItem(id, 3, new QTableWidgetItem(QString(info)));
										//rec_info1.remove(j, 5 + size + 1);
									}
									if (rec_info2.at(j + 5) == compare[3])
									{
										bin_good_2 = true;
										ui.tableWidget_2->setItem(id, 2, new QTableWidgetItem(QString::fromLocal8Bit("����ʧ��")));
										//QString info(rec_info.data() + 6);
										QByteArray info = QByteArray(rec_info2.data() + j + 6, size-1);
										QTableWidgetItem *item = new QTableWidgetItem(QString(info));
										item->setBackgroundColor(QColor(255, 0, 0));
										ui.tableWidget_2->setItem(id, 3, item);
										//rec_info1.remove(j, 5 + size + 1);
										//failedChipCount++;
										QDateTime time;
										QString currentTime = time.currentDateTime().toString("yyyy/MM/dd_HH:mm:ss.zzz");
										QString errCase = ui.tableWidget->item(id, 0)->text();
										saveConnent(NULL, errCase, QString(info), QString::number(IDnumber), currentTime);

									}
									if (rec_info2.at(j + 5) == compare[5])   //0x33�ǳ�ʱ
									{
										//bin_good_2 = true;
										//QByteArray info = QByteArray(rec_info2.data() + j + 6, size - 1);
										//QTableWidgetItem *item = new QTableWidgetItem(QString(info));
										//item->setBackgroundColor(QColor(255, 0, 0));
										//ui.tableWidget_2->setItem(id, 3, item);
										//timeoutCount2++;
										//QDateTime time;
										//QString currentTime = time.currentDateTime().toString("yyyy/MM/dd_HH:mm:ss.zzz");
										//QString errCase = ui.tableWidget_2->item(id, 0)->text();
										//saveConnent(NULL, errCase, QString(info), QString::number(IDnumber), currentTime);
										//if (timeoutCount2 == 3)
										//{
										//	//bin_good_2 = true;
										//	QDateTime time;
										//	QString now = time.currentDateTime().toString("yyyy/MM/dd_HH:mm:ss");
										//	ui.textEdit->append(now + ":" + QString::fromLocal8Bit("510��ʱ3�Σ�ִ�жϵ磡"));
										//	timeoutCount2 = 0;
										//	m_serialPort2->write(send_data, 6);                 //�յ�3�γ�ʱ���ͷ��Ͷϵ����ͬʱ�����߳��˳�ѭ������ȴ�
										//	m_serialPort2->waitForBytesWritten(10000);
										//	stopThread2 = true;
										//	//emit finishedInfo1();
										//	//failedChipCount++;
										//}



										bin_good_2 = true;
										QByteArray info = QByteArray(rec_info2.data() + j + 6, size - 1);
										QTableWidgetItem *item = new QTableWidgetItem(QString(info));
										item->setBackgroundColor(QColor(255, 0, 0));
										ui.tableWidget_2->setItem(id, 3, item);
										QDateTime time;
										QString currentTime = time.currentDateTime().toString("yyyy/MM/dd_HH:mm:ss.zzz");
										QString errCase = ui.tableWidget_2->item(id, 0)->text();
										saveConnent(NULL, errCase, QString(info), QString::number(IDnumber), currentTime);
										ui.textEdit->append(currentTime + ":" + QString::fromLocal8Bit("510��ʱ��ִ�жϵ磡"));
										m_serialPort2->write(send_data, 6);                 //�յ�3�γ�ʱ���ͷ��Ͷϵ����ͬʱ�����߳��˳�ѭ������ȴ�
										m_serialPort2->waitForBytesWritten(10000);
										stopThread2 = true;
										
									}
									rec_info2.remove(j, 5 + size + 1);
									m_timer2->stop();
									emit finishedInfo2(/*1*/);
									//send_rec(path, "Send signal to quit", "Receive:");
								}
							}
						}
						//�������һ���Ľ����������´�ѭ��Ӧ��ֱ��������һ�������������j��һ��һ�������ӣ���һ���������д���0xef,���ֽ����ˡ�
						//if (j + 6 + size < rec_info.length())//���size��0����ôһ����������6�Ĺ̶�����,���Ǽ�5������Ϊ���е�forѭ�����ֽ�����һ��j++��
						//{
						//	j = j + 5 + size;
						//}
						if (rec_info2.length() > 0)//�����ǽ�����һ����ɾһ��
							j = -1;
					}
				}
			}
		}
	}
}


void SLTTestDemo::receiveInfo3()
{
	//QString path = QCoreApplication::applicationDirPath() + "/" + "SerialPort3.txt";
	//QByteArray qArray = m_serialPort3->readAll();
	//QString str = qArray.toHex(' ').toUpper();
	//send_rec(path, str, "Receive_Src:");

	rec_info3.append(m_serialPort3->readAll()/*qArray*/);
	//������־
	//QString path = QCoreApplication::applicationDirPath() + "/" + "SerialPort3.txt";
	char send_data[6] = { 0xef,0xaa,0xff,0x00,0x00,0xff };
	int id;
	int rowSize = ui.tableWidget_3->rowCount();
	char compare[6] = { 0xef,0xaa,0x00,0x55,0xfb,0x33 };
	for (int j = 0; j < rec_info3.length(); j++)
	{
		if (rec_info3.at(j) == compare[0] && j < rec_info3.length() - 5)//����������һ��Ԫ��������0xef����j+1��ֱ��Խ�籨���ˡ����ȼ�5�ǿ��Լ��㵽size
		{
			if (rec_info3.at(j + 1) == compare[1])  //����ֻ�Ƕ�����0xef,0xaa�ˣ�����Ҫ�ж�У����Ƿ���ȷ�����������жϳ��Ƿ�������һ��
			{
				unsigned char Size[2] = { rec_info3.at(j + 3),rec_info3.at(j + 4) };
				unsigned short size = reverse_uint16(Size);
				if (size + j + 5 < rec_info3.length())   //�ӵ�У��ͣ������ڼ���У��͵�ʱ�򳬳��˳��ȷ�Χ//size+5+j��λ����У���
				{
					char checkSum = std::accumulate(rec_info3.data() + j + 2, rec_info3.data() + j + 5 + size, 0);//У��ʹ�CMD��ʼ��size�����ĳ��ȣ���4��û��У��ͣ���5����У���
					if (rec_info3.at(j + 5 + size) == checkSum)  //����ȷ��Ϊһ������//size+5+j��λ����У���
					{
						static int timeoutCount3 = 0;
						static int IDnumber;
						if (rec_info3.at(j + 2) == compare[4])   //�յ�������Ϣ��
						{
							//char *rec = rec_info3.data() + j + 5;
							//QByteArray qba = QByteArray(rec, size);
							//send_rec(path, QString(qba), "Receive:");
							rec_info3.remove(j, 5 + size + 1);   //��j��λ�ÿ�ʼ����5+size+1��У��͵ĳ���
						
						}
						else
						{
							//QString str = rec_info3.toHex(' ').toUpper();
							//send_rec(path, str, "Receive:");
							for (int i = 0; i < rowSize; i++)
							{
								QString cmdStr = ui.tableWidget->item(i, 1)->text();
								if (rec_info3.at(j + 2) == (char)cmdStr.toInt(nullptr, 16))
								{
									id = i;
								}
							}
							if (id == 0 || id == 1 || id == rowSize)
							{
								if (id == 0)
								{
									int xinID = rec_info3.at(j + 5);  //size�����һ��λ��//��Ϣ����int���͵�оƬλ��id ��0,1,2,3�ĸ�
									IDnumber = xinID;
									chipID3 = xinID;
									QByteArray information = QByteArray(rec_info3.data() + j + 6, size-1);
									//QString str = QString(QLatin1String(rec_info.data() + j + 6));//////////��ȷת����ʽ�����ԣ������������һλ��У��ͣ���ȥ��
									ui.tableWidget_3->setItem(id, 3, new QTableWidgetItem(QString::number(xinID) + "," + QString(information)));
									rec_info3.remove(j, 5 + size + 1);
									m_timer3->stop();
									emit finishedInfo3();
									//send_rec(path, "Send signal to quit", "Receive:");
								}
								else
								{
									if (rec_info3.at(j + 5) == compare[5])   //0x33�ǳ�ʱ���᲻��������������԰��ĵ�6��Ԫ��Ҳ������0x33,�����͵��ɳ�ʱȥ��ʾ�ˣ�����ʾ����
									{
										//bin_good_3 = true;
										//QByteArray info = QByteArray(rec_info3.data() + j + 6, size - 1);
										//QTableWidgetItem *item = new QTableWidgetItem(QString(info));
										//item->setBackgroundColor(QColor(255, 0, 0));
										//ui.tableWidget_3->setItem(id, 3, item);
										//QDateTime time;
										//QString currentTime = time.currentDateTime().toString("yyyy/MM/dd_HH:mm:ss.zzz");
										//QString errCase = ui.tableWidget_3->item(id, 0)->text();
										//saveConnent(NULL, errCase, QString(info), QString::number(IDnumber), currentTime);
										//timeoutCount3++;
										//if (timeoutCount3 == 3)
										//{
										//	//bin_good_3 = true;
										//	QDateTime time;
										//	QString now = time.currentDateTime().toString("yyyy/MM/dd_HH:mm:ss");
										//	ui.textEdit->append(now + ":" + QString::fromLocal8Bit("510��ʱ3�Σ�ִ�жϵ磡"));
										//	timeoutCount3 = 0;
										//	m_serialPort3->write(send_data, 6);                 //�յ�3�γ�ʱ���ͷ��Ͷϵ����ͬʱ�����߳��˳�ѭ������ȴ�
										//	m_serialPort3->waitForBytesWritten(10000);
										//	stopThread3 = true;
										//	//failedChipCount++;
										//}
										//rec_info3.remove(j, 5 + size + 1);
										//m_timer3->stop();
										//emit finishedInfo3();
										////send_rec(path, "Send signal to quit", "Receive:");


										bin_good_3 = true;
										QByteArray info = QByteArray(rec_info3.data() + j + 6, size - 1);
										QTableWidgetItem *item = new QTableWidgetItem(QString(info));
										item->setBackgroundColor(QColor(255, 0, 0));
										ui.tableWidget_3->setItem(id, 3, item);
										QDateTime time;
										QString currentTime = time.currentDateTime().toString("yyyy/MM/dd_HH:mm:ss.zzz");
										QString errCase = ui.tableWidget_3->item(id, 0)->text();
										saveConnent(NULL, errCase, QString(info), QString::number(IDnumber), currentTime);
										ui.textEdit->append(currentTime + ":" + QString::fromLocal8Bit("510��ʱ��ִ�жϵ磡"));
										m_serialPort3->write(send_data, 6);                 //�յ�3�γ�ʱ���ͷ��Ͷϵ����ͬʱ�����߳��˳�ѭ������ȴ�
										m_serialPort3->waitForBytesWritten(10000);
										stopThread3 = true;
										rec_info3.remove(j, 5 + size + 1);
										m_timer3->stop();
										emit finishedInfo3();

									}
									else
									{
										QByteArray info = QByteArray(rec_info3.data() + j + 5, size);
										ui.tableWidget_3->setItem(id, 3, new QTableWidgetItem(QString(info)));
										rec_info3.remove(j, 5 + size + 1);
										m_timer3->stop();
										emit finishedInfo3();
										//send_rec(path, "Send signal to quit", "Receive:");
									}
								}
							}
							if (id > 1 && id != rowSize)
							{
								if (size == 1)   //ֻ��result��û��һЩ��Ϣ
								{
									if (rec_info3.at(j + 5) == compare[1])
									{
										ui.tableWidget_3->setItem(id, 2, new QTableWidgetItem(QString::fromLocal8Bit("���Գɹ�")));
										//rec_info1.remove(j, 5 + size + 1);
									}
									if (rec_info3.at(j + 5) == compare[3])
									{
										bin_good_3 = true;
										QTableWidgetItem *item = new QTableWidgetItem(QString::fromLocal8Bit("����ʧ��"));
										item->setBackgroundColor(QColor(255, 0, 0));
										ui.tableWidget_3->setItem(id, 2, item);
										//rec_info1.remove(j, 5 + size + 1);
										//failedChipCount++;
									}
									rec_info3.remove(j, 5 + size + 1);
									m_timer3->stop();
									emit finishedInfo3(/*1*/);
									//send_rec(path, "Send signal to quit", "Receive:");
									//return;
								}
								else
								{
									if (rec_info3.at(j + 5) == compare[1])
									{
										ui.tableWidget_3->setItem(id, 2, new QTableWidgetItem(QString::fromLocal8Bit("���Գɹ�")));
										//QString info(rec_info.data() + 6);
										//QString str = QString(QLatin1String(rec_info.data() + 6));//////////��ȷת����ʽ�����ԣ������������һλ��У��ͣ���ȥ��
										QByteArray info = QByteArray(rec_info3.data() + j + 6, size-1);
										ui.tableWidget_3->setItem(id, 3, new QTableWidgetItem(QString(info)));
										//rec_info1.remove(j, 5 + size + 1);
									}
									if (rec_info3.at(j + 5) == compare[3])
									{
										bin_good_3 = true;
										ui.tableWidget_3->setItem(id, 2, new QTableWidgetItem(QString::fromLocal8Bit("����ʧ��")));
										//QString info(rec_info.data() + 6);
										QByteArray info = QByteArray(rec_info3.data() + j + 6, size-1);
										QTableWidgetItem *item = new QTableWidgetItem(QString(info));
										item->setBackgroundColor(QColor(255, 0, 0));
										ui.tableWidget_3->setItem(id, 3, item);
										//rec_info1.remove(j, 5 + size + 1);
										//failedChipCount++;
										QDateTime time;
										QString currentTime = time.currentDateTime().toString("yyyy/MM/dd_HH:mm:ss.zzz");
										QString errCase = ui.tableWidget->item(id, 0)->text();
										saveConnent(NULL, errCase, QString(info), QString::number(IDnumber), currentTime);
									}
									if (rec_info3.at(j + 5) == compare[5])   //0x33�ǳ�ʱ
									{
										//bin_good_3 = true;
										//QByteArray info = QByteArray(rec_info3.data() + j + 6, size - 1);
										//QTableWidgetItem *item = new QTableWidgetItem(QString(info));
										//item->setBackgroundColor(QColor(255, 0, 0));
										//ui.tableWidget_3->setItem(id, 3, item);
										//QDateTime time;
										//QString currentTime = time.currentDateTime().toString("yyyy/MM/dd_HH:mm:ss.zzz");
										//QString errCase = ui.tableWidget_3->item(id, 0)->text();
										//saveConnent(NULL, errCase, QString(info), QString::number(IDnumber), currentTime);
										//timeoutCount3++;
										//if (timeoutCount3 == 3)
										//{
										//	//bin_good_3 = true;
										//	QDateTime time;
										//	QString now = time.currentDateTime().toString("yyyy/MM/dd_HH:mm:ss");
										//	ui.textEdit->append(now + ":" + QString::fromLocal8Bit("510��ʱ3�Σ�ִ�жϵ磡"));
										//	timeoutCount3 = 0;
										//	m_serialPort3->write(send_data, 6);                 //�յ�3�γ�ʱ���ͷ��Ͷϵ����ͬʱ�����߳��˳�ѭ������ȴ�
										//	m_serialPort3->waitForBytesWritten(10000);
										//	stopThread3 = true;
										//	//emit finishedInfo1();
										//	//failedChipCount++;
										//}



										bin_good_3 = true;
										QByteArray info = QByteArray(rec_info3.data() + j + 6, size - 1);
										QTableWidgetItem *item = new QTableWidgetItem(QString(info));
										item->setBackgroundColor(QColor(255, 0, 0));
										ui.tableWidget_3->setItem(id, 3, item);
										QDateTime time;
										QString currentTime = time.currentDateTime().toString("yyyy/MM/dd_HH:mm:ss.zzz");
										QString errCase = ui.tableWidget_3->item(id, 0)->text();
										saveConnent(NULL, errCase, QString(info), QString::number(IDnumber), currentTime);
										ui.textEdit->append(currentTime + ":" + QString::fromLocal8Bit("510��ʱ��ִ�жϵ磡"));
										m_serialPort3->write(send_data, 6);                 //�յ�3�γ�ʱ���ͷ��Ͷϵ����ͬʱ�����߳��˳�ѭ������ȴ�
										m_serialPort3->waitForBytesWritten(10000);
										stopThread3 = true;
										
									}
									rec_info3.remove(j, 5 + size + 1);
									m_timer3->stop();
									emit finishedInfo3(/*1*/);
									//send_rec(path, "Send signal to quit", "Receive:");
								}
							}
						}
						//�������һ���Ľ����������´�ѭ��Ӧ��ֱ��������һ�������������j��һ��һ�������ӣ���һ���������д���0xef,���ֽ����ˡ�
						//if (j + 6 + size < rec_info.length())//���size��0����ôһ����������6�Ĺ̶�����,���Ǽ�5������Ϊ���е�forѭ�����ֽ�����һ��j++��
						//{
						//	j = j + 5 + size;
						//}
						if (rec_info3.length() > 0)//�����ǽ�����һ����ɾһ��
							j = -1;
					}
				}
			}
		}
	}
}


void SLTTestDemo::receiveInfo4()
{
	//QString path = QCoreApplication::applicationDirPath() + "/" + "SerialPort4.txt";
	//QByteArray qArray = m_serialPort4->readAll();
	//QString str = qArray.toHex(' ').toUpper();
	//send_rec(path, str, "Receive_Src:");

	rec_info4.append(m_serialPort4->readAll()/*qArray*/);
	//������־
	//QString path = QCoreApplication::applicationDirPath() + "/" + "SerialPort4.txt";
	char send_data[6] = { 0xef,0xaa,0xff,0x00,0x00,0xff };
	int id;
	int rowSize = ui.tableWidget_4->rowCount();
	char compare[6] = { 0xef,0xaa,0x00,0x55,0xfb,0x33 };  //0xef,0xaa,0xff,0x00,0x05,0x1a,0x23,0x32,0xa1,0x33,0xd0

	for (int j = 0; j < rec_info4.length(); j++)
	{
		if (rec_info4.at(j) == compare[0] && j < rec_info4.length() - 5)//����������һ��Ԫ��������0xef����j+1��ֱ��Խ�籨���ˡ����ȼ�5�ǿ��Լ��㵽size
		{
			if (rec_info4.at(j + 1) == compare[1])  //����ֻ�Ƕ�����0xef,0xaa�ˣ�����Ҫ�ж�У����Ƿ���ȷ�����������жϳ��Ƿ�������һ��
			{
				unsigned char Size[2] = { rec_info4.at(j + 3),rec_info4.at(j + 4) };
				unsigned short size = reverse_uint16(Size);
				if (size + j + 5 < rec_info4.length())   //�ӵ�У��ͣ������ڼ���У��͵�ʱ�򳬳��˳��ȷ�Χ//size+5+j��λ����У���
				{
					char checkSum = std::accumulate(rec_info4.data() + j + 2, rec_info4.data() + j + 5 + size, 0);//У��ʹ�CMD��ʼ��size�����ĳ��ȣ���4��û��У��ͣ���5����У���
					if (rec_info4.at(j + 5 + size) == checkSum)  //����ȷ��Ϊһ������//size+5+j��λ����У���
					{
						static int timeoutCount4 = 0;
						static int IDnumber;
						if (rec_info4.at(j + 2) == compare[4])   //�յ�������Ϣ��
						{
							//char *rec = rec_info4.data() + j + 5;
							//QByteArray qba = QByteArray(rec, size);
							//send_rec(path, QString(qba), "Receive:");
							rec_info4.remove(j, 5 + size + 1);   //��j��λ�ÿ�ʼ����5+size+1��У��͵ĳ���
						
						}
						else
						{
							//QString str = rec_info4.toHex(' ').toUpper();
							//send_rec(path, str, "Receive:");
							for (int i = 0; i < rowSize; i++)
							{
								QString cmdStr = ui.tableWidget->item(i, 1)->text();
								if (rec_info4.at(j + 2) == (char)cmdStr.toInt(nullptr, 16))
								{
									id = i;
								}
							}
							if (id == 0 || id == 1 || id == rowSize)
							{
								if (id == 0)
								{
									int xinID = rec_info4.at(j + 5);  //size�����һ��λ��//��Ϣ����int���͵�оƬλ��id ��0,1,2,3�ĸ�
									IDnumber = xinID;
									chipID4 = xinID;
									QByteArray information = QByteArray(rec_info4.data() + j + 6, size-1);
									//QString str = QString(QLatin1String(rec_info.data() + j + 6));//////////��ȷת����ʽ�����ԣ������������һλ��У��ͣ���ȥ��
									ui.tableWidget_4->setItem(id, 3, new QTableWidgetItem(QString::number(xinID) + "," + QString(information)));
									rec_info4.remove(j, 5 + size + 1);
									m_timer4->stop();
									emit finishedInfo4();
									//send_rec(path, "Send signal to quit", "Receive:");
								}
								else
								{
									if (rec_info4.at(j + 5) == compare[5])   //0x33�ǳ�ʱ���᲻��������������԰��ĵ�6��Ԫ��Ҳ������0x33,�����͵��ɳ�ʱȥ��ʾ�ˣ�����ʾ����
									{
										//bin_good_4 = true;
										//QByteArray info = QByteArray(rec_info4.data() + j + 6, size - 1);
										//QTableWidgetItem *item = new QTableWidgetItem(QString(info));
										//item->setBackgroundColor(QColor(255, 0, 0));
										//ui.tableWidget_4->setItem(id, 3, item);
										//QDateTime time;
										//QString currentTime = time.currentDateTime().toString("yyyy/MM/dd_HH:mm:ss.zzz");
										//QString errCase = ui.tableWidget_4->item(id, 0)->text();
										//saveConnent(NULL, errCase, QString(info), QString::number(IDnumber), currentTime);
										//timeoutCount4++;
										//if (timeoutCount4 == 3)
										//{
										//	//bin_good_4 = true;
										//	QDateTime time;
										//	QString now = time.currentDateTime().toString("yyyy/MM/dd_HH:mm:ss");
										//	ui.textEdit->append(now + ":" + QString::fromLocal8Bit("510��ʱ3�Σ�ִ�жϵ磡"));
										//	timeoutCount4 = 0;
										//	m_serialPort4->write(send_data, 6);                 //�յ�3�γ�ʱ���ͷ��Ͷϵ����ͬʱ�����߳��˳�ѭ������ȴ�
										//	m_serialPort4->waitForBytesWritten(10000);
										//	stopThread4 = true;
										//	//failedChipCount++;
										//}
										//rec_info4.remove(j, 5 + size + 1);
										//m_timer4->stop();
										//emit finishedInfo4();
										////send_rec(path, "Send signal to quit", "Receive:");


										bin_good_4 = true;
										QByteArray info = QByteArray(rec_info4.data() + j + 6, size - 1);
										QTableWidgetItem *item = new QTableWidgetItem(QString(info));
										item->setBackgroundColor(QColor(255, 0, 0));
										ui.tableWidget_4->setItem(id, 3, item);
										QDateTime time;
										QString currentTime = time.currentDateTime().toString("yyyy/MM/dd_HH:mm:ss.zzz");
										QString errCase = ui.tableWidget_4->item(id, 0)->text();
										saveConnent(NULL, errCase, QString(info), QString::number(IDnumber), currentTime);
										ui.textEdit->append(currentTime + ":" + QString::fromLocal8Bit("510��ʱ��ִ�жϵ磡"));
										m_serialPort4->write(send_data, 6);                 //�յ�3�γ�ʱ���ͷ��Ͷϵ����ͬʱ�����߳��˳�ѭ������ȴ�
										m_serialPort4->waitForBytesWritten(10000);
										stopThread4 = true;
										rec_info4.remove(j, 5 + size + 1);
										m_timer4->stop();
										emit finishedInfo4();
									}
									else
									{
										QByteArray info = QByteArray(rec_info4.data() + j + 5, size);
										ui.tableWidget_4->setItem(id, 3, new QTableWidgetItem(QString(info)));
										rec_info4.remove(j, 5 + size + 1);
										m_timer4->stop();
										emit finishedInfo4();
										//send_rec(path, "Send signal to quit", "Receive:");
									}
								}
							}
							if (id > 1 && id != rowSize)
							{
								if (size == 1)   //ֻ��result��û��һЩ��Ϣ
								{
									if (rec_info4.at(j + 5) == compare[1])
									{
										ui.tableWidget_4->setItem(id, 2, new QTableWidgetItem(QString::fromLocal8Bit("���Գɹ�")));
										//rec_info1.remove(j, 5 + size + 1);
									}
									if (rec_info4.at(j + 5) == compare[3])
									{
										bin_good_4 = true;
										QTableWidgetItem *item = new QTableWidgetItem(QString::fromLocal8Bit("����ʧ��"));
										item->setBackgroundColor(QColor(255, 0, 0));
										ui.tableWidget_4->setItem(id, 2, item);
										//rec_info1.remove(j, 5 + size + 1);
										//failedChipCount++;
									}
									rec_info4.remove(j, 5 + size + 1);
									m_timer4->stop();
									emit finishedInfo4(/*1*/);
									//send_rec(path, "Send signal to quit", "Receive:");
									//return;
								}
								else
								{
									if (rec_info4.at(j + 5) == compare[1])
									{
										ui.tableWidget_4->setItem(id, 2, new QTableWidgetItem(QString::fromLocal8Bit("���Գɹ�")));
										//QString info(rec_info.data() + 6);
										//QString str = QString(QLatin1String(rec_info.data() + 6));//////////��ȷת����ʽ�����ԣ������������һλ��У��ͣ���ȥ��
										QByteArray info = QByteArray(rec_info4.data() + j + 6, size-1);
										ui.tableWidget_4->setItem(id, 3, new QTableWidgetItem(QString(info)));
										//rec_info1.remove(j, 5 + size + 1);
									}
									if (rec_info4.at(j + 5) == compare[3])
									{
										bin_good_4 = true;
										ui.tableWidget_4->setItem(id, 2, new QTableWidgetItem(QString::fromLocal8Bit("����ʧ��")));
										//QString info(rec_info.data() + 6);
										QByteArray info = QByteArray(rec_info4.data() + j + 6, size-1);
										QTableWidgetItem *item = new QTableWidgetItem(QString(info));
										item->setBackgroundColor(QColor(255, 0, 0));
										ui.tableWidget_4->setItem(id, 3, item);
										//rec_info1.remove(j, 5 + size + 1);
										//failedChipCount++;
										QDateTime time;
										QString currentTime = time.currentDateTime().toString("yyyy/MM/dd_HH:mm:ss.zzz");
										QString errCase = ui.tableWidget->item(id, 0)->text();
										saveConnent(NULL, errCase, QString(info), QString::number(IDnumber), currentTime);
									}
									if (rec_info4.at(j + 5) == compare[5])   //0x33�ǳ�ʱ
									{
										//bin_good_4 = true;
										//QByteArray info = QByteArray(rec_info4.data() + j + 6, size - 1);
										//QTableWidgetItem *item = new QTableWidgetItem(QString(info));
										//item->setBackgroundColor(QColor(255, 0, 0));
										//ui.tableWidget_4->setItem(id, 3, item);
										//QDateTime time;
										//QString currentTime = time.currentDateTime().toString("yyyy/MM/dd_HH:mm:ss.zzz");
										//QString errCase = ui.tableWidget_4->item(id, 0)->text();
										//saveConnent(NULL, errCase, QString(info), QString::number(IDnumber), currentTime);
										//timeoutCount4++;
										//if (timeoutCount4 == 3)
										//{
										//	//bin_good_4 = true;
										//	QDateTime time;
										//	QString now = time.currentDateTime().toString("yyyy/MM/dd_HH:mm:ss");
										//	ui.textEdit->append(now + ":" + QString::fromLocal8Bit("510��ʱ3�Σ�ִ�жϵ磡"));
										//	timeoutCount4 = 0;
										//	m_serialPort4->write(send_data, 6);                 //�յ�3�γ�ʱ���ͷ��Ͷϵ����ͬʱ�����߳��˳�ѭ������ȴ�
										//	m_serialPort4->waitForBytesWritten(10000);
										//	stopThread4 = true;
										//	//emit finishedInfo1();
										//	//failedChipCount++;
										//}


										bin_good_4 = true;
										QByteArray info = QByteArray(rec_info4.data() + j + 6, size - 1);
										QTableWidgetItem *item = new QTableWidgetItem(QString(info));
										item->setBackgroundColor(QColor(255, 0, 0));
										ui.tableWidget_4->setItem(id, 3, item);
										QDateTime time;
										QString currentTime = time.currentDateTime().toString("yyyy/MM/dd_HH:mm:ss.zzz");
										QString errCase = ui.tableWidget_4->item(id, 0)->text();
										saveConnent(NULL, errCase, QString(info), QString::number(IDnumber), currentTime);
										ui.textEdit->append(currentTime + ":" + QString::fromLocal8Bit("510��ʱ��ִ�жϵ磡"));
										m_serialPort4->write(send_data, 6);                 //�յ�3�γ�ʱ���ͷ��Ͷϵ����ͬʱ�����߳��˳�ѭ������ȴ�
										m_serialPort4->waitForBytesWritten(10000);
										stopThread4 = true;

									}
									rec_info4.remove(j, 5 + size + 1);
									m_timer4->stop();
									emit finishedInfo4(/*1*/);
									//send_rec(path, "Send signal to quit", "Receive:");
								}
							}
						}
						//�������һ���Ľ����������´�ѭ��Ӧ��ֱ��������һ�������������j��һ��һ�������ӣ���һ���������д���0xef,���ֽ����ˡ�
						//if (j + 6 + size < rec_info.length())//���size��0����ôһ����������6�Ĺ̶�����,���Ǽ�5������Ϊ���е�forѭ�����ֽ�����һ��j++��
						//{
						//	j = j + 5 + size;
						//}
						if (rec_info4.length() > 0)//�����ǽ�����һ����ɾһ��
							j = -1;
					}
				}
			}
		}
	}













	//QByteArray rec_info = m_serialPort4->readAll();

	////������־
	//QString path = QCoreApplication::applicationDirPath() + "/" + "SerialPort4.txt";

	//int id;
	//int rowSize = ui.tableWidget_4->rowCount();
	//char compare[5] = { 0xef,0xaa,0x00,0x55,0xfb };
	////char checkSum = std::accumulate(rec_info.data() + 2, rec_info.data() + rec_info.length() - 1, 0);
	////unsigned char Size[2] = { rec_info.at(3),rec_info.at(4) };
	////unsigned short size = reverse_uint16(Size);
	//


	//for (int j = 0; j < rec_info.length(); j++)
	//{
	//	if (rec_info.at(j) == compare[0] && j<rec_info.length()-5)//����������һ��Ԫ��������0xef����j+1��ֱ��Խ�籨���ˡ����ȼ�5�ǿ��Լ��㵽size
	//	{
	//		if (rec_info.at(j + 1) == compare[1])  //����ֻ�Ƕ�����0xef,0xaa�ˣ�����Ҫ�ж�У����Ƿ���ȷ�����������жϳ��Ƿ�������һ��
	//		{
	//			unsigned char Size[2] = { rec_info.at(j + 3),rec_info.at(j + 4) };
	//			unsigned short size = reverse_uint16(Size);
	//			if (size + j + 5 < rec_info.length())   //�ӵ�У��ͣ������ڼ���У��͵�ʱ�򳬳��˳��ȷ�Χ//size+5+j��λ����У���
	//			{
	//				char checkSum = std::accumulate(rec_info.data() + j + 2, rec_info.data() + j + 5 + size, 0);//У��ʹ�CMD��ʼ��size�����ĳ��ȣ���4��û��У��ͣ���5����У���
	//				if (rec_info.at(j + 5 + size) == checkSum)  //����ȷ��Ϊһ������//size+5+j��λ����У���
	//				{
	//					if (rec_info.at(j + 2) == compare[4])   //�յ�������Ϣ��
	//					{
	//						char *rec = rec_info.data() + j + 5;
	//						QByteArray qba = QByteArray(rec, size);
	//						send_rec(path, QString(qba), "Receive:");
	//					}
	//					else
	//					{
	//						QString str = rec_info.toHex(' ').toUpper();
	//						send_rec(path, str, "Receive:");
	//						for (int i = 0; i < rowSize; i++)
	//						{
	//							QString cmdStr = ui.tableWidget->item(i, 1)->text();
	//							if (rec_info.at(j+2) == (char)cmdStr.toInt(nullptr, 16))
	//							{
	//								id = i;
	//							}
	//						}
	//						if (id == 0 || id == 1 || id == rowSize)
	//						{
	//							if (id == 0)
	//							{
	//								int xinID = rec_info.at(j + 5);  //size�����һ��λ��//��Ϣ����int���͵�оƬλ��id ��0,1,2,3�ĸ�
	//								QByteArray information = QByteArray(rec_info.data() + j + 6, size);
	//								//QString str = QString(QLatin1String(rec_info.data() + j + 6));//////////��ȷת����ʽ�����ԣ������������һλ��У��ͣ���ȥ��
	//								ui.tableWidget_4->setItem(id, 3, new QTableWidgetItem(QString::number(xinID) + "," + QString(information)));
	//								emit finishedInfo4();
	//							}
	//							else
	//							{
	//								//QString info(rec_info.data() + 5);
	//								//QString str = QString(QLatin1String(rec_info.data() + 5));//////////��ȷת����ʽ�����ԣ������������һλ��У��ͣ���ȥ��
	//								QByteArray info = QByteArray(rec_info.data() + j + 5, size);
	//								ui.tableWidget_4->setItem(id, 3, new QTableWidgetItem(QString(info)));
	//								emit finishedInfo4();
	//							}
	//						}
	//						if (id > 1 && id != rowSize)
	//						{
	//							if (size == 1)   //ֻ��result��û��һЩ��Ϣ
	//							{
	//								if (rec_info.at(j+5) == compare[1])
	//								{
	//									ui.tableWidget_4->setItem(id, 2, new QTableWidgetItem(QString::fromLocal8Bit("���Գɹ�")));
	//								}
	//								if (rec_info.at(j+5) == compare[3])
	//								{
	//									ui.tableWidget_4->setItem(id, 2, new QTableWidgetItem(QString::fromLocal8Bit("����ʧ��")));
	//								}
	//								emit finishedInfo4(/*1*/);
	//								//return;
	//							}
	//							else
	//							{
	//								if (rec_info.at(j+5) == compare[1])
	//								{
	//									ui.tableWidget_4->setItem(id, 2, new QTableWidgetItem(QString::fromLocal8Bit("���Գɹ�")));
	//									//QString info(rec_info.data() + 6);
	//									//QString str = QString(QLatin1String(rec_info.data() + 6));//////////��ȷת����ʽ�����ԣ������������һλ��У��ͣ���ȥ��
	//									QByteArray info = QByteArray(rec_info.data() + j + 6, size);
	//									ui.tableWidget_4->setItem(id, 3, new QTableWidgetItem(QString(info)));
	//								}
	//								if (rec_info.at(j+5) == compare[3])
	//								{
	//									ui.tableWidget_4->setItem(id, 2, new QTableWidgetItem(QString::fromLocal8Bit("����ʧ��")));
	//									//QString info(rec_info.data() + 6);
	//									QByteArray info = QByteArray(rec_info.data() + j + 6, size);
	//									ui.tableWidget_4->setItem(id, 3, new QTableWidgetItem(QString(info)));
	//								}
	//								emit finishedInfo4(/*1*/);
	//							}
	//						}
	//					}
	//					//�������һ���Ľ����������´�ѭ��Ӧ��ֱ��������һ�������������j��һ��һ�������ӣ���һ���������д���0xef,���ֽ����ˡ�
	//					if (j + 6 + size < rec_info.length())//���size��0����ôһ����������6�Ĺ̶�����
	//					{
	//						j = j + 5 + size;
	//					}
	//				}
	//			}
	//		}
	//	}
	//}







	//�յ�MCU��PC�ĵ�����Ϣ���浽����(�յ�������Ϣ)
	//if (rec_info.at(0) == compare[0] && rec_info.at(1) == compare[1] && rec_info.at(2) == compare[4])
	//{
	//	//char *rec = rec_info.data() + 5;
	//	//send_rec(path, QString(QLatin1String(rec)), "Receive:");
	//	char *rec = rec_info.data() + 5;
	//	QByteArray qba = QByteArray(rec, size);
	//	send_rec(path, QString(qba), "Receive:");
	//}
	//else
	//{
	//	QString str = rec_info.toHex(' ').toUpper();
	//	send_rec(path, str, "Receive:");
	//	if (rec_info.at(0) == compare[0] && rec_info.at(1) == compare[1] && rec_info.at(rec_info.length() - 1) == checkSum)
	//	{
	//		for (int i = 0; i < rowSize; i++)
	//		{
	//			QString cmdStr = ui.tableWidget->item(i, 1)->text();
	//			if (rec_info.at(2) == (char)cmdStr.toInt(nullptr, 16))
	//			{
	//				id = i;
	//			}
	//		}
	//		if (id == 0 || id == 1 || id == rowSize)
	//		{
	//			if (id == 0)
	//			{
	//				int xinID = rec_info.at(5);
	//				//ui.tableWidget_4->setItem(id, 3, new QTableWidgetItem(QString::number(xinID)));
	//				//ui.tableWidget_4->setItem(id, 3, new QTableWidgetItem(","));
	//				//QString info(rec_info.data() + 6);
	//				QString str = QString(QLatin1String(rec_info.data() + 6));//////////��ȷת����ʽ�����ԣ������������һλ��У��ͣ���ȥ��
	//				ui.tableWidget_4->setItem(id, 3, new QTableWidgetItem(QString::number(xinID) + "," + str));
	//				emit finishedInfo4();
	//			}
	//			else
	//			{
	//				QString info(rec_info.data() + 5);
	//				QString str = QString(QLatin1String(rec_info.data() + 5));//////////��ȷת����ʽ�����ԣ������������һλ��У��ͣ���ȥ��
	//				ui.tableWidget_4->setItem(id, 3, new QTableWidgetItem(info));
	//				emit finishedInfo4();
	//			}
	//		}
	//		//unsigned char Size[2] = { rec_info.at(3),rec_info.at(4) };
	//		//unsigned short size = reverse_uint16(Size);
	//		if (id > 1 && id != rowSize)
	//		{
	//			if (size == 1)   //ֻ��result��û��һЩ��Ϣ
	//			{
	//				if (rec_info.at(5) == compare[1])
	//				{
	//					ui.tableWidget_4->setItem(id, 2, new QTableWidgetItem(QString::fromLocal8Bit("���Գɹ�")));
	//				}
	//				if (rec_info.at(5) == compare[3])
	//				{
	//					ui.tableWidget_4->setItem(id, 2, new QTableWidgetItem(QString::fromLocal8Bit("����ʧ��")));
	//				}
	//				emit finishedInfo4(/*1*/);
	//				//return;
	//			}
	//			else
	//			{
	//				if (rec_info.at(5) == compare[1])
	//				{
	//					ui.tableWidget_4->setItem(id, 2, new QTableWidgetItem(QString::fromLocal8Bit("���Գɹ�")));
	//					QString info(rec_info.data() + 6);
	//					QString str = QString(QLatin1String(rec_info.data() + 6));//////////��ȷת����ʽ�����ԣ������������һλ��У��ͣ���ȥ��
	//					ui.tableWidget_4->setItem(id, 3, new QTableWidgetItem(info));
	//				}
	//				if (rec_info.at(5) == compare[3])
	//				{
	//					ui.tableWidget_4->setItem(id, 2, new QTableWidgetItem(QString::fromLocal8Bit("����ʧ��")));
	//					QString info(rec_info.data() + 6);
	//					ui.tableWidget_4->setItem(id, 3, new QTableWidgetItem(info));
	//				}
	//				emit finishedInfo4(/*1*/);
	//			}
	//		}
	//	}
	//}

	
}