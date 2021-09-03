#include "SLTTestDemo.h"
#include <QtCore/QtCore>
#include <qmessagebox.h>
#include <qfiledialog.h>
#include "packet.h"
#include <Windows.h>
#define REQUEST_SRQ -1   //等待GPIB事件超时,死等

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
	set_gpib = new GPIBSet();   //先不开此功能

	m_timer1 = new QTimer(/*this*/);   //在这里创建对象，isActive就不会乱改变了
	m_timer2 = new QTimer(/*this*/);
	m_timer3 = new QTimer(/*this*/);
	m_timer4 = new QTimer(/*this*/);
	connect(m_timer1, SIGNAL(timeout()), this, SLOT(timeRun1(/*QSerialPort **/))/*, Qt::DirectConnection*/);   //放到这里就不需要多次绑定，多次触发槽函数了(测试一个信号会不会触发其他函数)
	connect(m_timer2, SIGNAL(timeout()), this, SLOT(timeRun2(/*QSerialPort **/)));  
	connect(m_timer3, SIGNAL(timeout()), this, SLOT(timeRun3(/*QSerialPort **/))/*, Qt::DirectConnection*/);
	connect(m_timer4, SIGNAL(timeout()), this, SLOT(timeRun4(/*QSerialPort **/))); 

	m_serialPort1 = new QSerialPort();//实例化串口类一个对象
	m_serialPort2 = new QSerialPort();//实例化串口类一个对象
	m_serialPort3 = new QSerialPort();//实例化串口类一个对象
	m_serialPort4 = new QSerialPort();//实例化串口类一个对象
	initSerialPort(/*m_serialPort1*/);
	//initSerialPort(/*m_serialPort2*/);
	//initSerialPort(/*m_serialPort3*/);
	//initSerialPort(/*m_serialPort4*/);
	//加载默认配置文件
	setTableWidget(ui.tableWidget);
	setTableWidget(ui.tableWidget_2);
	setTableWidget(ui.tableWidget_3);
	setTableWidget(ui.tableWidget_4);

	ui.tableWidget->horizontalHeader()->setStretchLastSection(true);   //设置最后一列自动填满表格
	ui.tableWidget_2->horizontalHeader()->setStretchLastSection(true);
	ui.tableWidget_3->horizontalHeader()->setStretchLastSection(true);
	ui.tableWidget_4->horizontalHeader()->setStretchLastSection(true);
	

	QDateTime q_date_time;
	time_creatFile = q_date_time.currentDateTime().toString("yyyyMMdd_HHmmss");
	recordLog("SerialPort1");
	recordLog("SerialPort2");
	recordLog("SerialPort3");
	recordLog("SerialPort4");

	saveCSVFlie();  //保存excel结果
	creatPassRate();  //创建良率文件

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

	//connect(set_gpib, SIGNAL(send_gpib(QString)), this, SLOT(getGPIB_name(QString)));   //先不开此功能
}

static int serial1_cmd;
static int serial2_cmd;
static int serial3_cmd;
static int serial4_cmd;

static int chipID1;
static int chipID2;
static int chipID3;
static int chipID4;

static float allChipCount = 0;  //测试芯片总数
static float failedChipCount = 0;  //失败芯片数

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

//查找GPIB设备
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
//打开GPIB设备
void SLTTestDemo::openGpib()
{
	char *name = "GPIB0::7::INSTR";  //默认是这个
	//选了别的后可以重新赋值
	//QByteArray ba = gpib_name.toLatin1();
	//name = ba.data();

	char buffer_open[255] = { 0 };
	status = 0;                         // 保存返回数值
	defaultRM = 0;
	numInstrs = 0;
	//ViByte wrtBuf[MAX_SCPI_LENGTH];                     // 写缓冲区
	ViByte rdBuf[255];                      // 读缓冲区
	//char buffer[255] = { 0 };

	status = viOpenDefaultRM(&defaultRM);
	//nReturnStatus = viOpen(rmSession, "USB::0xFFFF::0x6300::802060092746810025::INSTR", VI_NULL, VI_NULL, &pnInstrHandle);  //工厂寄家设备
	status = viOpen(defaultRM, /*instrDescriptor*//*"GPIB0::7::INSTR"*/name, VI_NULL, VI_NULL, &instr);  //工厂设备
	status = viQueryf(instr, "FR?\n", "%s", /*buffer*/buffer_open);    //查询Handler状态
	status = viEnableEvent(instr, VI_EVENT_SERVICE_REQ, VI_QUEUE, VI_NULL);
}

//打开GPIB设备，查询状态
void SLTTestDemo::connectGpib()
{
	char buffer_fullsites[255] = { 0 };

	status = viWaitOnEvent(instr, VI_EVENT_SERVICE_REQ, REQUEST_SRQ, &etype, &ehandle);   //等待SRQ,需不需要加？
			//0x41是存在viReadSTB的statusByte还是viRead的data里
	if (status >= VI_SUCCESS)
	{
		status = viReadSTB(instr, &statusByte);   //是viWaitOnEvent可以延时确保收到无误还是读取SRQ的时候需要加循环去接收？
		//status = viRead(instr, data, 3000, &rcount);   //读数据？0x41?
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
	status = viQueryf(instr, "FULLSITES?\r\n", "%[^\n]", /*buffer*/buffer_fullsites);     //%s会在字符串遇到空格时停止导致后面的内容无法显示，%[^\n]这个可以在遇到\n回车的时候停止
	//if (memcmp(buffer_fullsites, "Fullsites 0000000F", strlen("Fullsites 0000000F")) != 0)
	//{
	//	//QMessageBox::warning(nullptr, "Fullsites Error!", "Please Check Sites!", QMessageBox::Ok);
	//	//viClose(instr);
	//	//viClose(defaultRM);
	//	return;
	//}
	if (buffer_fullsites[1]!='u')   //通信出错，只收到一个'F'
	{
		//分bin将通信错误修正
		char buffer[255] = { 0 };
		status = viQueryf(instr, "BINON:00000000,00000000,00000000,00002222;\r\n", "%s", buffer);
		//如果分bin命令错误，则继续发分bin命令
		while (status < VI_SUCCESS)
		{
			Sleep(1000);   //延时一秒发送，不然发送太快导致机台通信收错
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


	//GPIB模拟测试流程可查看HandlerControl_201211文件工程
	//status = 0;                         // 保存返回数值
	//defaultRM = 0;
	//numInstrs = 0;
	////ViByte wrtBuf[MAX_SCPI_LENGTH];                     // 写缓冲区
	//ViByte rdBuf[255];                      // 读缓冲区
	//char buffer[255] = { 0 };

	//status = viOpenDefaultRM(&defaultRM);
	////nReturnStatus = viOpen(rmSession, "USB::0xFFFF::0x6300::802060092746810025::INSTR", VI_NULL, VI_NULL, &pnInstrHandle);  //工厂寄家设备
	//status = viOpen(defaultRM, /*instrDescriptor*/"GPIB0::7::INSTR", VI_NULL, VI_NULL, &instr);  //工厂设备
	//status = viQueryf(instr, "FR?\n", "%s", buffer);    //查询Handler状态
	//status = viEnableEvent(instr, VI_EVENT_SERVICE_REQ, VI_QUEUE, VI_NULL);
	//while (true)
	//{
	//	//status = viEnableEvent(instr, VI_EVENT_SERVICE_REQ, VI_QUEUE, VI_NULL);
	//	status = viWaitOnEvent(instr, VI_EVENT_SERVICE_REQ, REQUEST_SRQ, &etype, &ehandle);   //等待SRQ,需不需要加？
	//	//0x41是存在viReadSTB的statusByte还是viRead的data里
	//	if (status >= VI_SUCCESS)
	//	{
	//		status = viReadSTB(instr, &statusByte);   //是viWaitOnEvent可以延时确保收到无误还是读取SRQ的时候需要加循环去接收？
	//		//status = viRead(instr, data, 3000, &rcount);   //读数据？0x41?
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
	//	Sleep(10000);  //芯片测试时间
	//	status = viQueryf(instr, "BINON:00000000,00000000,00000000,00001111;\r\n", "%s", buffer);
	//	if (status < VI_SUCCESS)
	//	{
	//		viClose(instr);
	//		viClose(defaultRM);
	//		return;
	//	}
	//	//用写和读的方式去判断一下试试与viQueryf问询方式的区别
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

//测试完成，进行分bin
void SLTTestDemo::binON(/*bool bin1,bool bin2,bool bin3,bool bin4*/)
{
	//char buffer[255] = { 0 };
	//status = viOpenDefaultRM(&defaultRM);
	//status = viOpen(defaultRM, instrDescriptor, VI_NULL, VI_NULL, &instr);  //工厂设备
	//status = viQueryf(instr, "BINON:00000000,00000000,00000000,00000015", "%s", buffer);   //分bin,上面是两个site(socket),发送15，所以1site分到5BIN,3分到1BIN.
	////_sleep(100);//模拟测试用
	//Sleep(100);  //模拟测试用
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
	//到此，idJudge数组就是分bin完成后的结果，将这个数组传入bin命令就ok了


	//这里做替换
	char input_buffer[255] = "BINON:00000000,00000000,00000000,00001111;\r\n";
	input_buffer[37] = idJudge[3];
	input_buffer[38] = idJudge[2];
	input_buffer[39] = idJudge[1];
	input_buffer[40] = idJudge[0];



	char buffer_bin[255] = { 0 };
	//status = viQueryf(instr, "BINON:00000000,00000000,00000000,00001111;\r\n", "%s", /*buffer*/buffer_bin); //1代表成功的bin,2代表失败的bin
	status = viQueryf(instr, /*"s%",*/input_buffer, "%s", /*buffer*/buffer_bin);
	if (status < VI_SUCCESS)
	{
		//QMessageBox::warning(nullptr, "BINON Error!", "Can't Receive BINON!", QMessageBox::Ok);
		//viClose(instr);
		//viClose(defaultRM);
		return;
	}
	//用写和读的方式去判断一下试试与viQueryf问询方式的区别
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
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))    //不加QIODevice::Append就擦除之前的内容，覆盖掉，如果加上就继续往下写（固定不变的格式，应该不用Append了吧，如果误点两次就创建两个表头了）
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
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))   //不加QIODevice::Append就擦除之前的内容，覆盖掉，如果加上就继续往下写
	{
		QMessageBox::warning(nullptr, "sdf", "can't open", QMessageBox::Ok);
	}
	QTextStream stream(&file);
	stream << chipID << "," << err << "," << errInfo << "," << socket << "," << time << "\n";
	file.close();
}
//保存良率
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
			QMessageBox::warning(0, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("打开文件失败!"), QMessageBox::Ok);
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
			QMessageBox::warning(0, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("打开文件失败!"), QMessageBox::Ok);
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
		//如果有线程的函数在QEvnetLoop等待，需要先发射退出等待信号，然后break跳出循环等待，这样才能让线程正常退出
		
		stopAutoTest = false;
		stopThread1 = true;
		stopThread2 = true;
		stopThread3 = true;
		stopThread4 = true;

		//closeControl = false;

		isComplete1 = true;   //让线程不进入同步等待。
		isComplete2 = true;
		isComplete3 = true;
		isComplete4 = true;
		//关闭串口
		if (qsp->isOpen())
		{
			qsp->close();
		}
		delete qsp;
		qsp = nullptr;

		emit finishedInfo1();  //这里是否要发两个解除等待信号呢？因为解除第一项等待是跳出了for循环，还可能卡在等待同步结束的等待线程。如果再加一个解除等待需要加延时才能保证释放解除等待信号时，正好线程处于等待状态。也可以不让线程等待，直接同步flag都为true就ok了。
		
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

//串口列表
QStringList SLTTestDemo::getPortNameList()//获取所有可用的串口列表
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

//初始化串口
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
			if (sp->isOpen())//如果串口已经打开了 先给他关闭了
			{
				sp->clear();
				sp->close();
			}
			//设置串口名字 假设我们上面已经成功获取到了 并且使用第一个
			QString serportName = serialList.at(i);
			sp->setPortName(serportName);
			//sp->setPortName(/*ui.comboBox->currentText()*/"COM21");
			if (!sp->open(QIODevice::ReadWrite))//用ReadWrite 的模式尝试打开串口
			{
				QMessageBox::warning(0, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("串口打开失败或串口已被占用!"), QMessageBox::Ok);
				return;
			}
			//打开成功
			//sp->setBaudRate(921600, QSerialPort::AllDirections);
			sp->setBaudRate(QSerialPort::Baud115200, QSerialPort::AllDirections);//设置波特率和读写方向
			sp->setDataBits(QSerialPort::Data8);		//数据位为8位
			sp->setFlowControl(QSerialPort::NoFlowControl);//无流控制
			sp->setParity(QSerialPort::NoParity);	//无校验位
			sp->setStopBits(QSerialPort::OneStop); //一位停止位
			//i++;
		}
		
	}
	else
	{
		QMessageBox::warning(0, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("未检测到串口!"), QMessageBox::Ok);
	}
	
}
//读取配置文件
void SLTTestDemo::setTableWidget(QTableWidget *tb)
{
	fileName = QCoreApplication::applicationDirPath() + "/" + QString::fromLocal8Bit("配置测试项.xls");
	if (!fileName.isEmpty())
	{
		QFile file;
		file.setFileName(fileName);
		//打开文件
		if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		{
			QMessageBox msg;
			msg.setText(QString::fromLocal8Bit("打开文件失败!"));
			msg.exec();
		}
		else
		{
			if (!file.size())
			{
				QMessageBox::warning(0, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("文件大小为空!"), QMessageBox::Ok);
			}
			else
			{
				//将文件数据导入表格
				int r_count = 0;        //统计文件的行数
				QStringList textList;   //记录文件中每一行的数据
				QTextStream in(&file);
				while (!in.atEnd())
				{
					QString line = in.readLine();
					textList.append(line);          //保存文件的数据
					r_count++;                      //记录文件的行数 前两行为表头
				}
				file.close();       //关闭文件
				if (!textList.isEmpty())
				{
					//QStringList listColHeader = textList.at(1).split("\t");
					QStringList listRowHeader = textList.at(0).split("\t");
					int c_count = listRowHeader.count();
					tb->clear();
					tb->setRowCount(r_count - 1);      //前两行是行列表头
					tb->setColumnCount(c_count/* - 1*/);   //最后一行是“\t"   如果代码写入文件的话会有\t,需要-1，手动创建文件写的话不需要-1.详见TestTry项目解释  
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
					//QMessageBox::information(0, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("导入成功!"));
				}
			}
		}
	}
	else
	{
		QMessageBox::warning(0, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("文件名未指定!"), QMessageBox::Ok);
	}
}

//保存表格结果到本地表格
void SLTTestDemo::saveTableToFile(QTableWidget *tb)
{
	QString path = QCoreApplication::applicationDirPath();
	if (!path.isEmpty())
	{
		//将表格数据写入文件
		if (QFileInfo(path).suffix().isEmpty())
		{
			path.append(".xls");
		}
		QFile file;
		file.setFileName(path);
		//打开文件
		if (!file.open(QIODevice::WriteOnly | QIODevice::Text))      //用此方法创建的excel跟普通的excel不一样，这种是内存很少的，测试发现此方法新建的excel其实就是创建一个文本文档，将.txt改为.xls。普通创建的需要用到QAxObject库，但是速度很慢，所以想要用下面方法读取文件到表格，必须先用这种方法创建excel表格，否则普通创建的excel无法用下面读取的方法读取到内容。
		{
			QMessageBox msg;
			msg.setText(QString::fromLocal8Bit("打开文件失败!"));
			msg.exec();
		}
		else
		{
			QTextStream out(&file);
			int rowCount = ui.tableWidget->rowCount();
			int colCount = ui.tableWidget->columnCount();
			//将表头写入文件
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
			//读取单元格的数据并写入文件
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
				out << "\n";       //linux下换行符是'\n'
			}
			out.flush();
			file.close();       //关闭文件
			QMessageBox::information(0, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("导出成功!"));
		}
	}
	else
	{
		QMessageBox::warning(0, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("文件名未指定!"), QMessageBox::Ok);
	}
}

//GPIB配置
void SLTTestDemo::on_pushButton_clicked()
{
	set_gpib->show();
}

//加载配置文件
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

//串口数据发送
//原先思路是用一个发送函数，四个线程去调用可以实现同时发送，但是由于connect(/*m_serialPort*/this  /*t3*/, SIGNAL(finishedInfo(/*int*//* num*/)), &loop, SLOT(quit()));
//的信号是一个，担心其他线程会解除当前线程的等待，因此用了4个此函数,发射4种不同信号
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
//		//当前线程等待，如果其他线程发出了finishedInfo()信号，此线程就会继续，出问题了
//		//可以自定义4个不同信号，一个线程对应一个信号，每个线程发射不同的信号
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
//	//	sp->waitForBytesWritten(10000);    //如果在新线程使用write发送数据，不加waitForBytesWritten无法发送。
//
//	//	QEventLoop loop;
//	//	connect(/*m_serialPort*/this, SIGNAL(finishedInfo()), &loop, SLOT(quit()));
//	//	loop.exec();
//	//}
//}

//20s后触发此函数，每20s触发一次，所以不用自己for循环发3次
void SLTTestDemo::timeRun1(/*QSerialPort *m_serial*/)
{
	//3次超时重传不行后进行断电处理
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
	//	ui.textEdit->append(now + ":" + QString::fromLocal8Bit("超时重传3次，重新串口初始化并断电！"));
	//	//if (!m_serialPort1->open(QIODevice::ReadWrite))
	//	//{
	//	//	QMessageBox::warning(0, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("串口打开失败或串口已被占用!"), QMessageBox::Ok);
	//	//	return;
	//	//}
	//	initSerialPort();  //防止通信中断，需要重新初始化串口
	//	m_timer1->stop();   //不进入此函数了
	//	char send_data[6] = { 0xef,0xaa,0xff,0x00,0x00,0xff };   //超过3次，那么就断电此芯片，进入等待
	//	m_serialPort1->write(send_data, 6);
	//	m_serialPort1->waitForBytesWritten(10000);
	//	stopThread1 = true;
	//	emit finishedInfo1();
	//	count = 0;
	//}

	//count++;



	//超时17s一次就直接进行断电处理
	QDateTime time;
	QString now = time.currentDateTime().toString("yyyy/MM/dd_HH:mm:ss");
	ui.textEdit->append(now + ":" + QString::fromLocal8Bit("超时重传，重新串口初始化并断电！"));
	saveConnent(NULL, QString::number(serial1_cmd), QString("Can not receive ACK time out"), QString::number(chipID1), now);
	//if (!m_serialPort1->open(QIODevice::ReadWrite))
	//{
	//	QMessageBox::warning(0, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("串口打开失败或串口已被占用!"), QMessageBox::Ok);
	//	return;
	//}
	initSerialPort();  //防止通信中断，需要重新初始化串口
	//m_timer1->stop();   //不进入此函数了，//其实这句也不用加，发了0xff断电后，自然会收到回复的ack，因此会有这个关闭的
	char send_data[6] = { 0xef,0xaa,0xff,0x00,0x00,0xff };   //超过3次，那么就断电此芯片，进入等待
	m_serialPort1->write(send_data, 6);
	m_serialPort1->waitForBytesWritten(10000);
	stopThread1 = true;
	bin_good_1 = true;   //断电重传后，分的bin当错误处理
	//emit finishedInfo1();  //其实这句也不用加，发了0xff断电后，自然会收到回复的ack，因此会发送这个信号的
	
}

//20s后触发此函数，每20s触发一次，所以不用自己for循环发3次
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
	//	ui.textEdit->append(now + ":" + QString::fromLocal8Bit("超时重传3次，重新串口初始化并断电！"));
	//	initSerialPort(); //防止通信中断，需要重新初始化串口
	//	m_timer2->stop();   //不进入此函数了
	//	char send_data[6] = { 0xef,0xaa,0xff,0x00,0x00,0xff };   //超过3次，那么就断电此芯片，进入等待
	//	m_serialPort2->write(send_data, 6);
	//	m_serialPort2->waitForBytesWritten(10000);
	//	stopThread2 = true;
	//	emit finishedInfo2();
	//	count = 0;
	//}

	//count++;



	QDateTime time;
	QString now = time.currentDateTime().toString("yyyy/MM/dd_HH:mm:ss");
	ui.textEdit->append(now + ":" + QString::fromLocal8Bit("超时重传，重新串口初始化并断电！"));
	saveConnent(NULL, QString::number(serial2_cmd), QString("Can not receive ACK time out"), QString::number(chipID2), now);
	initSerialPort(); //防止通信中断，需要重新初始化串口
	//m_timer2->stop();   //不进入此函数了
	char send_data[6] = { 0xef,0xaa,0xff,0x00,0x00,0xff };   //超过3次，那么就断电此芯片，进入等待
	m_serialPort2->write(send_data, 6);
	m_serialPort2->waitForBytesWritten(10000);
	stopThread2 = true;
	bin_good_2 = true;//断电重传后，分的bin当错误处理
	//emit finishedInfo2();
}

//20s后触发此函数，每20s触发一次，所以不用自己for循环发3次
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
	//	ui.textEdit->append(now + ":" + QString::fromLocal8Bit("超时重传3次，重新串口初始化并断电！"));
	//	initSerialPort(); //防止通信中断，需要重新初始化串口
	//	m_timer3->stop();   //不进入此函数了
	//	char send_data[6] = { 0xef,0xaa,0xff,0x00,0x00,0xff };   //超过3次，那么就断电此芯片，进入等待
	//	m_serialPort3->write(send_data, 6);
	//	m_serialPort3->waitForBytesWritten(10000);
	//	stopThread3 = true;
	//	emit finishedInfo3();
	//	count = 0;
	//}

	//count++;


	QDateTime time;
	QString now = time.currentDateTime().toString("yyyy/MM/dd_HH:mm:ss");
	ui.textEdit->append(now + ":" + QString::fromLocal8Bit("超时重传，重新串口初始化并断电！"));
	saveConnent(NULL, QString::number(serial3_cmd), QString("Can not receive ACK time out"), QString::number(chipID3), now);
	initSerialPort(); //防止通信中断，需要重新初始化串口
	//m_timer3->stop();   //不进入此函数了
	char send_data[6] = { 0xef,0xaa,0xff,0x00,0x00,0xff };   //超过3次，那么就断电此芯片，进入等待
	m_serialPort3->write(send_data, 6);
	m_serialPort3->waitForBytesWritten(10000);
	stopThread3 = true;
	bin_good_3 = true;//断电重传后，分的bin当错误处理
	//emit finishedInfo3();

}

//20s后触发此函数，每20s触发一次，所以不用自己for循环发3次
void SLTTestDemo::timeRun4(/*QSerialPort *m_serial*/)
{
	//加个发3次的逻辑，发一次，如果有回复，就会释放解除等待信号，如果没有回复，则如何触发此函数再次发送
	//3次重发
	//for (int i = 0; i < 3; i++)
	//{
	//	
	//	if (m_timer->isActive())  //如果接收那边没有收到ack，那么m_timer就没有stop()，那么isActive()是true
	//	{
	//		char send_data[6] = { 0 };
	//		send_info(send_data, serial4_cmd, 0, serial4_cmd);
	//		m_serialPort4->write(send_data, 6);
	//		m_serialPort4->waitForBytesWritten(10000);
	//	}
	//	Sleep(20000);  //每20s发一次超时函数，可以使用qtimer进行不阻塞主线程的延时
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
	//	ui.textEdit->append(now + ":" + QString::fromLocal8Bit("超时重传3次，重新串口初始化并断电！"));
	//	initSerialPort(); //防止通信中断，需要重新初始化串口
	//	m_timer4->stop();   //不进入此函数了
	//	char send_data[6] = { 0xef,0xaa,0xff,0x00,0x00,0xff };   //超过3次，那么就断电此芯片，进入等待
	//	m_serialPort4->write(send_data, 6);
	//	m_serialPort4->waitForBytesWritten(10000);
	//	stopThread4 = true;
	//	emit finishedInfo4();
	//	count = 0;
	//}
	//
	//count++;



	//这里将m_timer4->stop();和emit finishedInfo4();注释掉了。1.m_timer4->stop()如果不去掉，那么如果通信断了，17s后触发一次就停了，会造成死等，应该是一直17s触发一次，
	//直到通信修好了，再次触发定时器发送0xff断电命令的时候，会回复ACK，并执行m_timer4->stop();和emit finishedInfo4();
	QDateTime time;
	QString now = time.currentDateTime().toString("yyyy/MM/dd_HH:mm:ss");
	ui.textEdit->append(now + ":" + QString::fromLocal8Bit("超时重传，重新串口初始化并断电！"));
	saveConnent(NULL, QString::number(serial4_cmd), QString("Can not receive ACK time out"), QString::number(chipID4), now);
	initSerialPort(); //防止通信中断，需要重新初始化串口
	//m_timer4->stop();   //不进入此函数了
	char send_data[6] = { 0xef,0xaa,0xff,0x00,0x00,0xff };   //超过3次，那么就断电此芯片，进入等待
	m_serialPort4->write(send_data, 6);
	m_serialPort4->waitForBytesWritten(10000);
	stopThread4 = true;
	bin_good_4 = true;//断电重传后，分的bin当错误处理
	//emit finishedInfo4();
}


void SLTTestDemo::serialPortSend1()
{
	int len = ui.tableWidget->rowCount();
	while (stopAutoTest)
	{
		//connectGpib();
		bin_good_1 = false;    //芯片测试前改为false，有错误会置为true
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
			//FD测功耗的命令需要在测试项之前发一次，测试项结束发一次0xfd(已经在配置文件里改了)
			char send_data[6] = { 0 };
			QString cmdStr = ui.tableWidget->item(i, 1)->text();
			int cmd = cmdStr.toInt(nullptr, 16);
			send_info(send_data, cmd, 0, cmd);
			Sleep(10);   //给mcu时间去等待接收pc信息
			m_serialPort1->write(send_data, 6);
			m_serialPort1->waitForBytesWritten(10000);

			serial1_cmd = cmd;
			emit runT1();
			//m_timer1 = new QTimer(this);
			//m_timer1->setInterval(20000);//在这加了就不用在start参数加了。
			//connect(m_timer1, SIGNAL(timeout()), this, SLOT(timeRun1(/*QSerialPort **/)), Qt::DirectConnection); //规定：槽的参数不能多于信号的参数，无法实现一个槽去发4个串口了//定时器在isActive()=true的状态下（start()打开一次后），如果再次绑定信号槽函数，那么会同时触发两次，或者多次（看绑定几次）
			//if (!m_timer1->isActive())   //stop()之后，isActive返回false.
			//	m_timer1->start();
			
			//emit fini1();
			//recordLog("SerialPort1");

			//保存发送数据到本地（以下这种转换方式可以把“0xef,0xaa”转换成0xef 0xaa，这样的值显示，如果用QString(QLatin1String(send_data))）,是将数据转为字符串，比如“0x32,0xa1”是"success"的显示。
			//QString path = QCoreApplication::applicationDirPath() + "/" + "SerialPort1.txt";
			//QByteArray SEN = QByteArray(send_data, 6);
			//QString str = SEN.toHex(' ').toUpper();
			//send_rec(path, str, "Send:");

			//当前线程等待，如果其他线程发出了finishedInfo()信号，此线程就会继续，出问题了
			//可以自定义4个不同信号，一个线程对应一个信号，每个线程发射不同的信号
			//QEventLoop loop;
			//connect(this, SIGNAL(finishedInfo1(/*int value*/)), &loop, SLOT(quit()));
			//send_rec(path, "Connect loop", "Send:");
			loop.exec();
			//if (value == len-1)   //断电操作
			//{
			//	QString cmdStr = "0xff";
			//	int cmd = cmdStr.toInt(nullptr, 16);
			//	send_info(send_data, cmd, 0, cmd);
			//	m_serialPort1->write(send_data, 6);
			//	m_serialPort1->waitForBytesWritten(10000);
			//}
			//测试！
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
		m_condition.wait(lock);//释放锁lock，使其他线程可以执行从std::unique_lock<std::mutex>lock(m_mutex)开始的代码
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
		bin_good_2 = false;    //芯片测试前改为false，有错误会置为true
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
			Sleep(10);   //给mcu时间去等待接收pc信息
			m_serialPort2->write(send_data, 6);
			m_serialPort2->waitForBytesWritten(10000);

			serial2_cmd = cmd;
			emit runT2();
			//emit fini2();

			//QString path = QCoreApplication::applicationDirPath() + "/" + "SerialPort2.txt";
			//QByteArray SEN = QByteArray(send_data, 6);
			//QString str = SEN.toHex(' ').toUpper();
			//send_rec(path, str, "Send:");

			//当前线程等待，如果其他线程发出了finishedInfo()信号，此线程就会继续，出问题了
			//可以自定义4个不同信号，一个线程对应一个信号，每个线程发射不同的信号
			//QEventLoop loop;
			//connect(this, SIGNAL(finishedInfo2()), &loop, SLOT(quit()));
			//send_rec(path, "Connect loop", "Send:");
			loop.exec();

			//send_rec(path, "loop quit", "Send:");
		}
		//isComplete2 = true;

		//if (isComplete1&&isComplete3&&isComplete4)   //说明都跑完了，当前的线程是最后一个跑完的，要唤醒其他等待的线程
		//{
		//	//m_condition.notify_all();

		//	emit finishedInfoControl();
		//}
		////else   //到这里说明还有没有跑完的，那么当前的线程要进入等待，等其他线程跑完
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
		bin_good_3 = false;    //芯片测试前改为false，有错误会置为true
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
			Sleep(10);   //给mcu时间去等待接收pc信息
			m_serialPort3->write(send_data, 6);
			m_serialPort3->waitForBytesWritten(10000);

			serial3_cmd = cmd;
			emit runT3();
			//emit fini3();

			//QString path = QCoreApplication::applicationDirPath() + "/" + "SerialPort3.txt";
			//QByteArray SEN = QByteArray(send_data, 6);
			//QString str = SEN.toHex(' ').toUpper();
			//send_rec(path, str, "Send:");

			//当前线程等待，如果其他线程发出了finishedInfo()信号，此线程就会继续，出问题了
			//可以自定义4个不同信号，一个线程对应一个信号，每个线程发射不同的信号
			//QEventLoop loop;
			//connect(this, SIGNAL(finishedInfo3()), &loop, SLOT(quit()));
			//send_rec(path, "Connect loop", "Send:");
			loop.exec();

			//send_rec(path, "loop quit", "Send:");
		}
		//isComplete3 = true;

		//if (isComplete1&&isComplete2&&isComplete4)   //说明都跑完了，当前的线程是最后一个跑完的，要唤醒其他等待的线程
		//{
		//	//m_condition.notify_all();

		//	emit finishedInfoControl();
		//}
		////else   //到这里说明还有没有跑完的，那么当前的线程等待其他线程跑完
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
		bin_good_4 = false;    //芯片测试前改为false，有错误会置为true
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
			int cmd = cmdStr.toInt(nullptr, 16);  //16进制输出
			send_info(send_data, cmd, 0, cmd);
			Sleep(10);   //给mcu时间去等待接收pc信息
			m_serialPort4->write(send_data, 6);
			m_serialPort4->waitForBytesWritten(10000);

			serial4_cmd = cmd;
			emit runT4();
			//emit fini4();

			//QString path = QCoreApplication::applicationDirPath() + "/" + "SerialPort4.txt";
			//QByteArray SEN = QByteArray(send_data, 6);
			//QString str = SEN.toHex(' ').toUpper();
			//send_rec(path, str, "Send:");

			//当前线程等待，如果其他线程发出了finishedInfo()信号，此线程就会继续，出问题了
			//可以自定义4个不同信号，一个线程对应一个信号，每个线程发射不同的信号
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
		m_condition.wait(lock);   //释放锁lock
		//send_rec(path, "wait to be awake", "over aft:");
	}
}

//每测试完成一次清除一次
void SLTTestDemo::clearConnent(QTableWidget *table)
{
	table->removeColumn(2);
	table->removeColumn(2);
	table->setColumnCount(4);
	QStringList header;
	header << QString::fromLocal8Bit("测试项") << QString::fromLocal8Bit("命令字") << QString::fromLocal8Bit("结果") << QString::fromLocal8Bit("信息");
	table->setHorizontalHeaderLabels(header);
}

void SLTTestDemo::control()
{
	while (closeControl)
	{
		//20ms延时，使每个串口下一轮测试先将isComplete1..等置为false了，再进入下面的判断，
		//不然如果唤醒第5个线程后，第5个线程先进入true的话，那就又发了一次分bin的命令，导致一轮芯片刚放上一小会就拿去分bin去了，（实际没有测试）
		Sleep(20);   
		if (isComplete1&&isComplete2&&isComplete3&&isComplete4)  //所有芯片一轮测试完成，换芯片
		{
			//Sleep(500);  //保证所有串口发送都进入等待状态

			Sleep(1000);   //测试芯片断电后充分放电

			binON(); 
			connectGpib();
			//ui.textEdit->append(QString::fromLocal8Bit("测试芯片总数：") + QString::number(allChipCount));
			m_condition.notify_all();
			
			//emit finishedInfo1();
			//emit finishedInfo2();
			//emit finishedInfo3();
			//emit finishedInfo4();
		}
		else   //先进入等待，等4个芯片都跑完一轮后唤醒
		{
			//QEventLoop loop;
			//connect(this, SIGNAL(finishedInfoControl()), &loop, SLOT(quit()));
			//loop.exec();
			std::unique_lock<std::mutex>lock(mut);
			cond.wait(lock);
		}
	}
}

//开始测试
void SLTTestDemo::on_pushButton_3_clicked()
{
	//ui.pushButton_3->setEnabled(false);
	emit pushButton_3_disable();
	QDateTime time;
	QString now = time.currentDateTime().toString("yyyy/MM/dd_HH:mm:ss");
	ui.textEdit->append(now + ":" + QString::fromLocal8Bit("开始测试."));
	//findRsrc();
	openGpib();
	connectGpib();
	t1 = new std::thread(&SLTTestDemo::serialPortSend1, this/*, m_serialPort1*//*, 1*/);
	t2 = new std::thread(&SLTTestDemo::serialPortSend2, this/*, m_serialPort2*//*, 2*/);
	t3 = new std::thread(&SLTTestDemo::serialPortSend3, this/*, m_serialPort3*//*, 3*/);
	t4 = new std::thread(&SLTTestDemo::serialPortSend4, this/*, m_serialPort4*//*, 4*/);

	tControl = new std::thread(&SLTTestDemo::control, this);

}
//测试暂停/继续
void SLTTestDemo::on_pushButton_4_clicked()
{
	//QEventLoop loop;
	//connect(/*m_serialPort*/this, SIGNAL(finishedInfo()), &loop, SLOT(quit()));
	//loop.exec();

	//继续
	emit finishedInfo1(/*5*/);   //信号传递参数到槽，信号emit时是什么，那就是什么，所以如果发射是5，那connect(/*m_serialPort*/this  /*t3*/, SIGNAL(finishedInfo(int/* num*/)), &loop, SLOT(quit()));这个触发的所有都是5。所以加不加参数没用
	//emit finishedInfo(2);
	//emit finishedInfo(3);
	//emit finishedInfo(4);

}


//解析收到数据
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
	//		tb->setItem(id, 2, new QTableWidgetItem(QString::fromLocal8Bit("测试成功")));
	//	}
	//	else
	//	{
	//		tb->setItem(id, 2, new QTableWidgetItem(QString::fromLocal8Bit("测试失败")));
	//	}
	//	emit finishedInfo();
	//	id++;
	//}
}

//m_serialPort1的接收
void SLTTestDemo::receiveInfo1()
{
	//QString path = QCoreApplication::applicationDirPath() + "/" + "SerialPort1.txt";
	//QByteArray qArray = m_serialPort1->readAll();
	//QString str = qArray.toHex(' ').toUpper();
	//send_rec(path, str, "Receive_Src:");

	//QByteArray rec_info = m_serialPort1->readAll();    //这种方法最好，但是会出现沾包的情况。就是分两次接收了，上一包一半下一包一半，导致收到的不是整包无法判断为整包
	//QByteArray rec_info;
	rec_info1.append(m_serialPort1->readAll()/*qArray*/);
	//接收日志
	//QString path = QCoreApplication::applicationDirPath() + "/" + "SerialPort1.txt";
	char send_data[6] = { 0xef,0xaa,0xff,0x00,0x00,0xff };
	int id;
	int rowSize = ui.tableWidget->rowCount();
	char compare[6] = { 0xef,0xaa,0x00,0x55,0xfb,0x33 };

	for (int j = 0; j < rec_info1.length(); j++)
	{
		if (rec_info1.at(j) == compare[0] && j < rec_info1.length() - 5)//担心如果最后一个元素正好是0xef，那j+1就直接越界报错了。长度减5是可以计算到size
		{
			if (rec_info1.at(j + 1) == compare[1])  //到这只是读出来0xef,0xaa了，还需要判断校验和是否正确，这样才能判断出是否是完整一包
			{
				unsigned char Size[2] = { rec_info1.at(j + 3),rec_info1.at(j + 4) };
				unsigned short size = reverse_uint16(Size);
				if (size + j + 5 < rec_info1.length())   //加到校验和，不能在计算校验和的时候超出了长度范围//size+5+j的位置是校验和，如果进到这个if里，说明收的数据长度够了
				{
					char checkSum = std::accumulate(rec_info1.data() + j + 2, rec_info1.data() + j + 5 + size, 0);//校验和从CMD开始到size结束的长度，加4是没算校验和，加5算上校验和
					if (rec_info1.at(j + 5 + size) == checkSum)  //到此确认为一个整包//size+5+j的位置是校验和
					{
						static int timeoutCount1 = 0;
						static int IDnumber;
						if (rec_info1.at(j + 2) == compare[4])   //收到调试信息包
						{
							//char *rec = rec_info1.data() + j + 5;
							//QByteArray qba = QByteArray(rec, size);
							//send_rec(path, QString(qba), "Receive:");
							rec_info1.remove(j, 5 + size + 1);   //从j的位置开始，到5+size+1的校验和的长度

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
							//应该写成rec_info.at(2)==0x00,rec_info.at(2)==0x01,rec_info.at(2)==0xff,应该跟着配置文件走，不该跟着id走
							if (id == 0 || id == 1 || id == rowSize)         //char compare[6] = { 0xef,0xaa,0x00,0x55,0xfb,0x33 };
							{
								if (id == 0)
								{
									int xinID = rec_info1.at(j + 5);  //size后面第一个位置//信息会有int类型的芯片位置id ：0,1,2,3四个
									IDnumber = xinID;
									chipID1 = xinID;
									QByteArray information = QByteArray(rec_info1.data() + j + 6, size - 1);   //因为size的长度是算上了1个字节的芯片信息
									//QString str = QString(QLatin1String(rec_info.data() + j + 6));//////////正确转换方式，待试，但是数组最后一位是校验和，得去掉
									ui.tableWidget->setItem(id, 3, new QTableWidgetItem(QString::number(xinID) + "," + QString(information)));
									rec_info1.remove(j, 5 + size + 1);
									m_timer1->stop();
									emit finishedInfo1();
									//send_rec(path, "Send signal to quit", "Receive:");
								}
								else
								{
									if (rec_info1.at(j + 5) == compare[5])   //0x33是超时（会不会下面的正常测试包的第6个元素也正好是0x33,这样就当成超时去显示了，会显示错误）
									{
										////3次超时触发断电操作，改为1次超时就断电
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
										//	ui.textEdit->append(now + ":" + QString::fromLocal8Bit("510超时3次，执行断电！"));
										//	m_serialPort1->write(send_data, 6);                 //收到3次超时，就发送断电命令，同时发送线程退出循环进入等待
										//	m_serialPort1->waitForBytesWritten(10000);
										//	stopThread1 = true;
										//	//failedChipCount++;
										//}
										//rec_info1.remove(j, 5 + size + 1);
										//m_timer1->stop();
										//emit finishedInfo1();
										////send_rec(path, "Send signal to quit", "Receive:");




										//1次超时就执行断电操作
										bin_good_1 = true;
										QByteArray info = QByteArray(rec_info1.data() + j + 6, size - 1);
										QTableWidgetItem *item = new QTableWidgetItem(QString(info));
										item->setBackgroundColor(QColor(255, 0, 0));
										ui.tableWidget->setItem(id, 3, item);
										QDateTime time;
										QString currentTime = time.currentDateTime().toString("yyyy/MM/dd_HH:mm:ss.zzz");
										QString errCase = ui.tableWidget->item(id, 0)->text();
										saveConnent(NULL, errCase, QString(info), QString::number(IDnumber), currentTime);
										ui.textEdit->append(currentTime + ":" + QString::fromLocal8Bit("510超时，执行断电！"));
										m_serialPort1->write(send_data, 6);		              //收到3次超时，就发送断电命令，同时发送线程退出循环进入等待
										m_serialPort1->waitForBytesWritten(10000);
										stopThread1 = true;
										rec_info1.remove(j, 5 + size + 1);
										m_timer1->stop();
										emit finishedInfo1();
									}
									else  //不是超时的时候
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
								if (size == 1)   //只有result，没有一些信息
								{
									if (rec_info1.at(j + 5) == compare[1])
									{
										ui.tableWidget->setItem(id, 2, new QTableWidgetItem(QString::fromLocal8Bit("测试成功")));
										//rec_info1.remove(j, 5 + size + 1);
									}
									if (rec_info1.at(j + 5) == compare[3])
									{
										bin_good_1 = true;
										QTableWidgetItem *item = new QTableWidgetItem(QString::fromLocal8Bit("测试失败"));
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
										ui.tableWidget->setItem(id, 2, new QTableWidgetItem(QString::fromLocal8Bit("测试成功")));
										//QString info(rec_info.data() + 6);
										//QString str = QString(QLatin1String(rec_info.data() + 6));//////////正确转换方式，待试，但是数组最后一位是校验和，得去掉
										QByteArray info = QByteArray(rec_info1.data() + j + 6, size - 1);  //因为size的长度是算上了1个字节的result 0xaa
										ui.tableWidget->setItem(id, 3, new QTableWidgetItem(QString(info)));
										//rec_info1.remove(j, 5 + size + 1);
									}
									if (rec_info1.at(j+5) == compare[3])
									{
										bin_good_1 = true;
										ui.tableWidget->setItem(id, 2, new QTableWidgetItem(QString::fromLocal8Bit("测试失败")));
										//QString info(rec_info.data() + 6);
										QByteArray info = QByteArray(rec_info1.data() + j + 6, size - 1);        //因为size的长度是算上了1个字节的result 0x55
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
									if (rec_info1.at(j + 5) == compare[5])   //0x33是超时
									{
										//超时3次执行断电操作
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
										//	ui.textEdit->append(now + ":" + QString::fromLocal8Bit("510超时3次，执行断电！"));
										//	timeoutCount1 = 0;
										//	m_serialPort1->write(send_data, 6);                 //收到3次超时，就发送断电命令，同时发送线程退出循环进入等待
										//	m_serialPort1->waitForBytesWritten(10000);
										//	stopThread1 = true;
										//	//emit finishedInfo1();
										//	//failedChipCount++;
										//}


										
										//超时1次就执行断电操作
										bin_good_1 = true;
										QByteArray info = QByteArray(rec_info1.data() + j + 6, size - 1);
										QTableWidgetItem *item = new QTableWidgetItem(QString(info));
										item->setBackgroundColor(QColor(255, 0, 0));
										ui.tableWidget->setItem(id, 3, item);
										QDateTime time;
										QString currentTime = time.currentDateTime().toString("yyyy/MM/dd_HH:mm:ss.zzz");
										QString errCase = ui.tableWidget->item(id, 0)->text();
										saveConnent(NULL, errCase, QString(info), QString::number(IDnumber), currentTime);
										ui.textEdit->append(currentTime + ":" + QString::fromLocal8Bit("510超时，执行断电！"));
										m_serialPort1->write(send_data, 6);                 //收到3次超时，就发送断电命令，同时发送线程退出循环进入等待
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
						//上面完成一包的解析，所以下次循环应该直接跳到下一包，如果不跳，j是一个一个的增加，万一包的数据中存在0xef,就又进来了。
						//if (j + 6 + size < rec_info.length())//如果size是0，那么一个包最少是6的固定长度,但是加5的是因为运行的for循环后，又进行了一次j++。
						//{
						//	j = j + 5 + size;
						//}
						if (rec_info1.length() > 0)//现在是解析完一包就删一包
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

	//////接收日志
	//QString path = QCoreApplication::applicationDirPath() + "/" + "SerialPort1.txt";
	////QString str = rec_info.toHex(' ').toUpper();
	////send_rec(path, str, "Receive:");

	////收到MCU到PC的调试信息保存到本地(收到调试信息)
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
	//		//应该写成rec_info.at(2)==0x00,rec_info.at(2)==0x01,rec_info.at(2)==0xff,应该跟着配置文件走，不该跟着id走
	//		if (id == 0 || id == 1 || id == rowSize)
	//		{

	//			//只有第一个命令是返回一个id和版本信息，第二个最后一个也没有result，只有字符串信息
	//			if (id == 0)
	//			{
	//				int xinID = rec_info.at(5);
	//				QString str = QString(QLatin1String(rec_info.data() + 6));//////////正确转换方式，待试，但是数组最后一位是校验和，得去掉
	//				ui.tableWidget->setItem(id, 3, new QTableWidgetItem(QString::number(xinID) + "," + str));
	//				emit finishedInfo1();
	//			}
	//			else
	//			{
	//				QString info(rec_info.data() + 5);
	//				QString str = QString(QLatin1String(rec_info.data() + 5));//////////正确转换方式，待试，但是数组最后一位是校验和，得去掉
	//				ui.tableWidget->setItem(id, 3, new QTableWidgetItem(info));
	//				emit finishedInfo1();
	//			}
	//		}
	//		//unsigned char Size[2] = { rec_info.at(3),rec_info.at(4) };
	//		//unsigned short size = reverse_uint16(Size);
	//		if (id > 1 && id != rowSize)
	//		{
	//			if (size == 1)   //只有result，没有一些信息
	//			{
	//				if (rec_info.at(5) == compare[1])
	//				{
	//					ui.tableWidget->setItem(id, 2, new QTableWidgetItem(QString::fromLocal8Bit("测试成功")));
	//				}
	//				if (rec_info.at(5) == compare[3])
	//				{
	//					ui.tableWidget->setItem(id, 2, new QTableWidgetItem(QString::fromLocal8Bit("测试失败")));
	//				}
	//				emit finishedInfo1(/*1*/);
	//				//return;
	//			}
	//			else
	//			{
	//				if (rec_info.at(5) == compare[1])
	//				{
	//					ui.tableWidget->setItem(id, 2, new QTableWidgetItem(QString::fromLocal8Bit("测试成功")));
	//					QString info(rec_info.data() + 6);
	//					QString str = QString(QLatin1String(rec_info.data() + 6));//////////正确转换方式，待试，但是数组最后一位是校验和，得去掉
	//					ui.tableWidget->setItem(id, 3, new QTableWidgetItem(info));
	//				}
	//				if (rec_info.at(5) == compare[3])
	//				{
	//					ui.tableWidget->setItem(id, 2, new QTableWidgetItem(QString::fromLocal8Bit("测试失败")));
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
	//	//if (size == 1)   //只有result，没有一些信息
	//	//{
	//	//	if (rec_info.at(5) == compare[1])
	//	//	{
	//	//		ui.tableWidget->setItem(id, 2, new QTableWidgetItem(QString::fromLocal8Bit("测试成功")));
	//	//	}
	//	//	if (rec_info.at(5) == compare[3])
	//	//	{
	//	//		ui.tableWidget->setItem(id, 2, new QTableWidgetItem(QString::fromLocal8Bit("测试失败")));
	//	//	}
	//	//	emit finishedInfo1(/*2*/);
	//	//	//return;
	//	//}
	//	//else
	//	//{
	//	//	if (rec_info.at(5) == compare[1])
	//	//	{
	//	//		ui.tableWidget->setItem(id, 2, new QTableWidgetItem(QString::fromLocal8Bit("测试成功")));
	//	//		QString info(rec_info.data() + 6);
	//	//		ui.tableWidget->setItem(id, 3, new QTableWidgetItem(info));
	//	//	}
	//	//	if (rec_info.at(5) == compare[3])
	//	//	{
	//	//		ui.tableWidget->setItem(id, 2, new QTableWidgetItem(QString::fromLocal8Bit("测试失败")));
	//	//		QString info(rec_info.data() + 6);
	//	//		ui.tableWidget->setItem(id, 3, new QTableWidgetItem(info));
	//	//	}
	//	//	emit finishedInfo1(/*2*/);
	//	//}


	//	if (id == 0 || id == 1 || id == rowSize)
	//	{
	//		//QString info(rec_info.data() + 5);
	//		//QString str = QString(QLatin1String(rec_info.data() + 5));//////////正确转换方式，待试，但是数组最后一位是校验和，得去掉
	//		//ui.tableWidget->setItem(id, 3, new QTableWidgetItem(info));
	//		//emit finishedInfo1();

	//		//只有第一个命令是返回一个id和版本信息，第二个最后一个也没有result，只有字符串信息
	//		if (id == 0)
	//		{
	//			int xinID = rec_info.at(5);
	//			//ui.tableWidget_4->setItem(id, 3, new QTableWidgetItem(QString::number(xinID)));
	//			//ui.tableWidget_4->setItem(id, 3, new QTableWidgetItem(","));
	//			//QString info(rec_info.data() + 6);
	//			QString str = QString(QLatin1String(rec_info.data() + 6));//////////正确转换方式，待试，但是数组最后一位是校验和，得去掉
	//			ui.tableWidget->setItem(id, 3, new QTableWidgetItem(QString::number(xinID) + "," + str));
	//			emit finishedInfo1();
	//		}
	//		else
	//		{
	//			QString info(rec_info.data() + 5);
	//			QString str = QString(QLatin1String(rec_info.data() + 5));//////////正确转换方式，待试，但是数组最后一位是校验和，得去掉
	//			ui.tableWidget->setItem(id, 3, new QTableWidgetItem(info));
	//			emit finishedInfo1();
	//		}
	//	}
	//	unsigned char Size[2] = { rec_info.at(3),rec_info.at(4) };
	//	unsigned short size = reverse_uint16(Size);
	//	if (id > 1 && id != rowSize)
	//	{
	//		if (size == 1)   //只有result，没有一些信息
	//		{
	//			if (rec_info.at(5) == compare[1])
	//			{
	//				ui.tableWidget->setItem(id, 2, new QTableWidgetItem(QString::fromLocal8Bit("测试成功")));
	//			}
	//			if (rec_info.at(5) == compare[3])
	//			{
	//				ui.tableWidget->setItem(id, 2, new QTableWidgetItem(QString::fromLocal8Bit("测试失败")));
	//			}
	//			emit finishedInfo1(/*1*/);
	//			//return;
	//		}
	//		else
	//		{
	//			if (rec_info.at(5) == compare[1])
	//			{
	//				ui.tableWidget->setItem(id, 2, new QTableWidgetItem(QString::fromLocal8Bit("测试成功")));
	//				QString info(rec_info.data() + 6);
	//				QString str = QString(QLatin1String(rec_info.data() + 6));//////////正确转换方式，待试，但是数组最后一位是校验和，得去掉
	//				ui.tableWidget->setItem(id, 3, new QTableWidgetItem(info));
	//			}
	//			if (rec_info.at(5) == compare[3])
	//			{
	//				ui.tableWidget->setItem(id, 2, new QTableWidgetItem(QString::fromLocal8Bit("测试失败")));
	//				QString info(rec_info.data() + 6);
	//				ui.tableWidget->setItem(id, 3, new QTableWidgetItem(info));
	//			}
	//			emit finishedInfo1(/*1*/);
	//		}
	//	}
	//}
}
//m_serialPort2的接收
void SLTTestDemo::receiveInfo2()
{
	//QString path = QCoreApplication::applicationDirPath() + "/" + "SerialPort2.txt";
	//QByteArray qArray = m_serialPort2->readAll();
	//QString str = qArray.toHex(' ').toUpper();
	//send_rec(path, str, "Receive_Src:");

	rec_info2.append(m_serialPort2->readAll()/*qArray*/);
	//接收日志
	//QString path = QCoreApplication::applicationDirPath() + "/" + "SerialPort2.txt";
	char send_data[6] = { 0xef,0xaa,0xff,0x00,0x00,0xff };
	int id;
	int rowSize = ui.tableWidget_2->rowCount();
	char compare[6] = { 0xef,0xaa,0x00,0x55,0xfb,0x33 };

	for (int j = 0; j < rec_info2.length(); j++)
	{
		if (rec_info2.at(j) == compare[0] && j < rec_info2.length() - 5)//担心如果最后一个元素正好是0xef，那j+1就直接越界报错了。长度减5是可以计算到size
		{
			if (rec_info2.at(j + 1) == compare[1])  //到这只是读出来0xef,0xaa了，还需要判断校验和是否正确，这样才能判断出是否是完整一包
			{
				unsigned char Size[2] = { rec_info2.at(j + 3),rec_info2.at(j + 4) };
				unsigned short size = reverse_uint16(Size);
				if (size + j + 5 < rec_info2.length())   //加到校验和，不能在计算校验和的时候超出了长度范围//size+5+j的位置是校验和
				{
					char checkSum = std::accumulate(rec_info2.data() + j + 2, rec_info2.data() + j + 5 + size, 0);//校验和从CMD开始到size结束的长度，加4是没算校验和，加5算上校验和
					if (rec_info2.at(j + 5 + size) == checkSum)  //到此确认为一个整包//size+5+j的位置是校验和
					{
						static int timeoutCount2 = 0;
						static int IDnumber;
						if (rec_info2.at(j + 2) == compare[4])   //收到调试信息包
						{
							//char *rec = rec_info2.data() + j + 5;
							//QByteArray qba = QByteArray(rec, size);
							//send_rec(path, QString(qba), "Receive:");
							rec_info2.remove(j, 5 + size + 1);   //从j的位置开始，到5+size+1的校验和的长度

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
									int xinID = rec_info2.at(j + 5);  //size后面第一个位置//信息会有int类型的芯片位置id ：0,1,2,3四个
									IDnumber = xinID;
									chipID2 = xinID;
									QByteArray information = QByteArray(rec_info2.data() + j + 6, size-1);
									//QString str = QString(QLatin1String(rec_info.data() + j + 6));//////////正确转换方式，待试，但是数组最后一位是校验和，得去掉
									ui.tableWidget_2->setItem(id, 3, new QTableWidgetItem(QString::number(xinID) + "," + QString(information)));
									rec_info2.remove(j, 5 + size + 1);
									m_timer2->stop();
									emit finishedInfo2();
									//send_rec(path, "Send signal to quit", "Receive:");
								}
								else
								{
									if (rec_info2.at(j + 5) == compare[5])   //0x33是超时（会不会下面的正常测试包的第6个元素也正好是0x33,这样就当成超时去显示了，会显示错误）
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
										//	ui.textEdit->append(now + ":" + QString::fromLocal8Bit("510超时3次，执行断电！"));
										//	timeoutCount2 = 0;
										//	m_serialPort2->write(send_data, 6);                 //收到3次超时，就发送断电命令，同时发送线程退出循环进入等待
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
										ui.textEdit->append(currentTime + ":" + QString::fromLocal8Bit("510超时，执行断电！"));
										m_serialPort2->write(send_data, 6);                 //收到3次超时，就发送断电命令，同时发送线程退出循环进入等待
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
								if (size == 1)   //只有result，没有一些信息
								{
									if (rec_info2.at(j + 5) == compare[1])
									{
										ui.tableWidget_2->setItem(id, 2, new QTableWidgetItem(QString::fromLocal8Bit("测试成功")));
										//rec_info1.remove(j, 5 + size + 1);
									}
									if (rec_info2.at(j + 5) == compare[3])
									{
										bin_good_2 = true;
										QTableWidgetItem *item = new QTableWidgetItem(QString::fromLocal8Bit("测试失败"));
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
										ui.tableWidget_2->setItem(id, 2, new QTableWidgetItem(QString::fromLocal8Bit("测试成功")));
										//QString info(rec_info.data() + 6);
										//QString str = QString(QLatin1String(rec_info.data() + 6));//////////正确转换方式，待试，但是数组最后一位是校验和，得去掉
										QByteArray info = QByteArray(rec_info2.data() + j + 6, size-1);
										ui.tableWidget_2->setItem(id, 3, new QTableWidgetItem(QString(info)));
										//rec_info1.remove(j, 5 + size + 1);
									}
									if (rec_info2.at(j + 5) == compare[3])
									{
										bin_good_2 = true;
										ui.tableWidget_2->setItem(id, 2, new QTableWidgetItem(QString::fromLocal8Bit("测试失败")));
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
									if (rec_info2.at(j + 5) == compare[5])   //0x33是超时
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
										//	ui.textEdit->append(now + ":" + QString::fromLocal8Bit("510超时3次，执行断电！"));
										//	timeoutCount2 = 0;
										//	m_serialPort2->write(send_data, 6);                 //收到3次超时，就发送断电命令，同时发送线程退出循环进入等待
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
										ui.textEdit->append(currentTime + ":" + QString::fromLocal8Bit("510超时，执行断电！"));
										m_serialPort2->write(send_data, 6);                 //收到3次超时，就发送断电命令，同时发送线程退出循环进入等待
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
						//上面完成一包的解析，所以下次循环应该直接跳到下一包，如果不跳，j是一个一个的增加，万一包的数据中存在0xef,就又进来了。
						//if (j + 6 + size < rec_info.length())//如果size是0，那么一个包最少是6的固定长度,但是加5的是因为运行的for循环后，又进行了一次j++。
						//{
						//	j = j + 5 + size;
						//}
						if (rec_info2.length() > 0)//现在是解析完一包就删一包
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
	//接收日志
	//QString path = QCoreApplication::applicationDirPath() + "/" + "SerialPort3.txt";
	char send_data[6] = { 0xef,0xaa,0xff,0x00,0x00,0xff };
	int id;
	int rowSize = ui.tableWidget_3->rowCount();
	char compare[6] = { 0xef,0xaa,0x00,0x55,0xfb,0x33 };
	for (int j = 0; j < rec_info3.length(); j++)
	{
		if (rec_info3.at(j) == compare[0] && j < rec_info3.length() - 5)//担心如果最后一个元素正好是0xef，那j+1就直接越界报错了。长度减5是可以计算到size
		{
			if (rec_info3.at(j + 1) == compare[1])  //到这只是读出来0xef,0xaa了，还需要判断校验和是否正确，这样才能判断出是否是完整一包
			{
				unsigned char Size[2] = { rec_info3.at(j + 3),rec_info3.at(j + 4) };
				unsigned short size = reverse_uint16(Size);
				if (size + j + 5 < rec_info3.length())   //加到校验和，不能在计算校验和的时候超出了长度范围//size+5+j的位置是校验和
				{
					char checkSum = std::accumulate(rec_info3.data() + j + 2, rec_info3.data() + j + 5 + size, 0);//校验和从CMD开始到size结束的长度，加4是没算校验和，加5算上校验和
					if (rec_info3.at(j + 5 + size) == checkSum)  //到此确认为一个整包//size+5+j的位置是校验和
					{
						static int timeoutCount3 = 0;
						static int IDnumber;
						if (rec_info3.at(j + 2) == compare[4])   //收到调试信息包
						{
							//char *rec = rec_info3.data() + j + 5;
							//QByteArray qba = QByteArray(rec, size);
							//send_rec(path, QString(qba), "Receive:");
							rec_info3.remove(j, 5 + size + 1);   //从j的位置开始，到5+size+1的校验和的长度
						
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
									int xinID = rec_info3.at(j + 5);  //size后面第一个位置//信息会有int类型的芯片位置id ：0,1,2,3四个
									IDnumber = xinID;
									chipID3 = xinID;
									QByteArray information = QByteArray(rec_info3.data() + j + 6, size-1);
									//QString str = QString(QLatin1String(rec_info.data() + j + 6));//////////正确转换方式，待试，但是数组最后一位是校验和，得去掉
									ui.tableWidget_3->setItem(id, 3, new QTableWidgetItem(QString::number(xinID) + "," + QString(information)));
									rec_info3.remove(j, 5 + size + 1);
									m_timer3->stop();
									emit finishedInfo3();
									//send_rec(path, "Send signal to quit", "Receive:");
								}
								else
								{
									if (rec_info3.at(j + 5) == compare[5])   //0x33是超时（会不会下面的正常测试包的第6个元素也正好是0x33,这样就当成超时去显示了，会显示错误）
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
										//	ui.textEdit->append(now + ":" + QString::fromLocal8Bit("510超时3次，执行断电！"));
										//	timeoutCount3 = 0;
										//	m_serialPort3->write(send_data, 6);                 //收到3次超时，就发送断电命令，同时发送线程退出循环进入等待
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
										ui.textEdit->append(currentTime + ":" + QString::fromLocal8Bit("510超时，执行断电！"));
										m_serialPort3->write(send_data, 6);                 //收到3次超时，就发送断电命令，同时发送线程退出循环进入等待
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
								if (size == 1)   //只有result，没有一些信息
								{
									if (rec_info3.at(j + 5) == compare[1])
									{
										ui.tableWidget_3->setItem(id, 2, new QTableWidgetItem(QString::fromLocal8Bit("测试成功")));
										//rec_info1.remove(j, 5 + size + 1);
									}
									if (rec_info3.at(j + 5) == compare[3])
									{
										bin_good_3 = true;
										QTableWidgetItem *item = new QTableWidgetItem(QString::fromLocal8Bit("测试失败"));
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
										ui.tableWidget_3->setItem(id, 2, new QTableWidgetItem(QString::fromLocal8Bit("测试成功")));
										//QString info(rec_info.data() + 6);
										//QString str = QString(QLatin1String(rec_info.data() + 6));//////////正确转换方式，待试，但是数组最后一位是校验和，得去掉
										QByteArray info = QByteArray(rec_info3.data() + j + 6, size-1);
										ui.tableWidget_3->setItem(id, 3, new QTableWidgetItem(QString(info)));
										//rec_info1.remove(j, 5 + size + 1);
									}
									if (rec_info3.at(j + 5) == compare[3])
									{
										bin_good_3 = true;
										ui.tableWidget_3->setItem(id, 2, new QTableWidgetItem(QString::fromLocal8Bit("测试失败")));
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
									if (rec_info3.at(j + 5) == compare[5])   //0x33是超时
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
										//	ui.textEdit->append(now + ":" + QString::fromLocal8Bit("510超时3次，执行断电！"));
										//	timeoutCount3 = 0;
										//	m_serialPort3->write(send_data, 6);                 //收到3次超时，就发送断电命令，同时发送线程退出循环进入等待
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
										ui.textEdit->append(currentTime + ":" + QString::fromLocal8Bit("510超时，执行断电！"));
										m_serialPort3->write(send_data, 6);                 //收到3次超时，就发送断电命令，同时发送线程退出循环进入等待
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
						//上面完成一包的解析，所以下次循环应该直接跳到下一包，如果不跳，j是一个一个的增加，万一包的数据中存在0xef,就又进来了。
						//if (j + 6 + size < rec_info.length())//如果size是0，那么一个包最少是6的固定长度,但是加5的是因为运行的for循环后，又进行了一次j++。
						//{
						//	j = j + 5 + size;
						//}
						if (rec_info3.length() > 0)//现在是解析完一包就删一包
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
	//接收日志
	//QString path = QCoreApplication::applicationDirPath() + "/" + "SerialPort4.txt";
	char send_data[6] = { 0xef,0xaa,0xff,0x00,0x00,0xff };
	int id;
	int rowSize = ui.tableWidget_4->rowCount();
	char compare[6] = { 0xef,0xaa,0x00,0x55,0xfb,0x33 };  //0xef,0xaa,0xff,0x00,0x05,0x1a,0x23,0x32,0xa1,0x33,0xd0

	for (int j = 0; j < rec_info4.length(); j++)
	{
		if (rec_info4.at(j) == compare[0] && j < rec_info4.length() - 5)//担心如果最后一个元素正好是0xef，那j+1就直接越界报错了。长度减5是可以计算到size
		{
			if (rec_info4.at(j + 1) == compare[1])  //到这只是读出来0xef,0xaa了，还需要判断校验和是否正确，这样才能判断出是否是完整一包
			{
				unsigned char Size[2] = { rec_info4.at(j + 3),rec_info4.at(j + 4) };
				unsigned short size = reverse_uint16(Size);
				if (size + j + 5 < rec_info4.length())   //加到校验和，不能在计算校验和的时候超出了长度范围//size+5+j的位置是校验和
				{
					char checkSum = std::accumulate(rec_info4.data() + j + 2, rec_info4.data() + j + 5 + size, 0);//校验和从CMD开始到size结束的长度，加4是没算校验和，加5算上校验和
					if (rec_info4.at(j + 5 + size) == checkSum)  //到此确认为一个整包//size+5+j的位置是校验和
					{
						static int timeoutCount4 = 0;
						static int IDnumber;
						if (rec_info4.at(j + 2) == compare[4])   //收到调试信息包
						{
							//char *rec = rec_info4.data() + j + 5;
							//QByteArray qba = QByteArray(rec, size);
							//send_rec(path, QString(qba), "Receive:");
							rec_info4.remove(j, 5 + size + 1);   //从j的位置开始，到5+size+1的校验和的长度
						
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
									int xinID = rec_info4.at(j + 5);  //size后面第一个位置//信息会有int类型的芯片位置id ：0,1,2,3四个
									IDnumber = xinID;
									chipID4 = xinID;
									QByteArray information = QByteArray(rec_info4.data() + j + 6, size-1);
									//QString str = QString(QLatin1String(rec_info.data() + j + 6));//////////正确转换方式，待试，但是数组最后一位是校验和，得去掉
									ui.tableWidget_4->setItem(id, 3, new QTableWidgetItem(QString::number(xinID) + "," + QString(information)));
									rec_info4.remove(j, 5 + size + 1);
									m_timer4->stop();
									emit finishedInfo4();
									//send_rec(path, "Send signal to quit", "Receive:");
								}
								else
								{
									if (rec_info4.at(j + 5) == compare[5])   //0x33是超时（会不会下面的正常测试包的第6个元素也正好是0x33,这样就当成超时去显示了，会显示错误）
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
										//	ui.textEdit->append(now + ":" + QString::fromLocal8Bit("510超时3次，执行断电！"));
										//	timeoutCount4 = 0;
										//	m_serialPort4->write(send_data, 6);                 //收到3次超时，就发送断电命令，同时发送线程退出循环进入等待
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
										ui.textEdit->append(currentTime + ":" + QString::fromLocal8Bit("510超时，执行断电！"));
										m_serialPort4->write(send_data, 6);                 //收到3次超时，就发送断电命令，同时发送线程退出循环进入等待
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
								if (size == 1)   //只有result，没有一些信息
								{
									if (rec_info4.at(j + 5) == compare[1])
									{
										ui.tableWidget_4->setItem(id, 2, new QTableWidgetItem(QString::fromLocal8Bit("测试成功")));
										//rec_info1.remove(j, 5 + size + 1);
									}
									if (rec_info4.at(j + 5) == compare[3])
									{
										bin_good_4 = true;
										QTableWidgetItem *item = new QTableWidgetItem(QString::fromLocal8Bit("测试失败"));
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
										ui.tableWidget_4->setItem(id, 2, new QTableWidgetItem(QString::fromLocal8Bit("测试成功")));
										//QString info(rec_info.data() + 6);
										//QString str = QString(QLatin1String(rec_info.data() + 6));//////////正确转换方式，待试，但是数组最后一位是校验和，得去掉
										QByteArray info = QByteArray(rec_info4.data() + j + 6, size-1);
										ui.tableWidget_4->setItem(id, 3, new QTableWidgetItem(QString(info)));
										//rec_info1.remove(j, 5 + size + 1);
									}
									if (rec_info4.at(j + 5) == compare[3])
									{
										bin_good_4 = true;
										ui.tableWidget_4->setItem(id, 2, new QTableWidgetItem(QString::fromLocal8Bit("测试失败")));
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
									if (rec_info4.at(j + 5) == compare[5])   //0x33是超时
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
										//	ui.textEdit->append(now + ":" + QString::fromLocal8Bit("510超时3次，执行断电！"));
										//	timeoutCount4 = 0;
										//	m_serialPort4->write(send_data, 6);                 //收到3次超时，就发送断电命令，同时发送线程退出循环进入等待
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
										ui.textEdit->append(currentTime + ":" + QString::fromLocal8Bit("510超时，执行断电！"));
										m_serialPort4->write(send_data, 6);                 //收到3次超时，就发送断电命令，同时发送线程退出循环进入等待
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
						//上面完成一包的解析，所以下次循环应该直接跳到下一包，如果不跳，j是一个一个的增加，万一包的数据中存在0xef,就又进来了。
						//if (j + 6 + size < rec_info.length())//如果size是0，那么一个包最少是6的固定长度,但是加5的是因为运行的for循环后，又进行了一次j++。
						//{
						//	j = j + 5 + size;
						//}
						if (rec_info4.length() > 0)//现在是解析完一包就删一包
							j = -1;
					}
				}
			}
		}
	}













	//QByteArray rec_info = m_serialPort4->readAll();

	////接收日志
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
	//	if (rec_info.at(j) == compare[0] && j<rec_info.length()-5)//担心如果最后一个元素正好是0xef，那j+1就直接越界报错了。长度减5是可以计算到size
	//	{
	//		if (rec_info.at(j + 1) == compare[1])  //到这只是读出来0xef,0xaa了，还需要判断校验和是否正确，这样才能判断出是否是完整一包
	//		{
	//			unsigned char Size[2] = { rec_info.at(j + 3),rec_info.at(j + 4) };
	//			unsigned short size = reverse_uint16(Size);
	//			if (size + j + 5 < rec_info.length())   //加到校验和，不能在计算校验和的时候超出了长度范围//size+5+j的位置是校验和
	//			{
	//				char checkSum = std::accumulate(rec_info.data() + j + 2, rec_info.data() + j + 5 + size, 0);//校验和从CMD开始到size结束的长度，加4是没算校验和，加5算上校验和
	//				if (rec_info.at(j + 5 + size) == checkSum)  //到此确认为一个整包//size+5+j的位置是校验和
	//				{
	//					if (rec_info.at(j + 2) == compare[4])   //收到调试信息包
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
	//								int xinID = rec_info.at(j + 5);  //size后面第一个位置//信息会有int类型的芯片位置id ：0,1,2,3四个
	//								QByteArray information = QByteArray(rec_info.data() + j + 6, size);
	//								//QString str = QString(QLatin1String(rec_info.data() + j + 6));//////////正确转换方式，待试，但是数组最后一位是校验和，得去掉
	//								ui.tableWidget_4->setItem(id, 3, new QTableWidgetItem(QString::number(xinID) + "," + QString(information)));
	//								emit finishedInfo4();
	//							}
	//							else
	//							{
	//								//QString info(rec_info.data() + 5);
	//								//QString str = QString(QLatin1String(rec_info.data() + 5));//////////正确转换方式，待试，但是数组最后一位是校验和，得去掉
	//								QByteArray info = QByteArray(rec_info.data() + j + 5, size);
	//								ui.tableWidget_4->setItem(id, 3, new QTableWidgetItem(QString(info)));
	//								emit finishedInfo4();
	//							}
	//						}
	//						if (id > 1 && id != rowSize)
	//						{
	//							if (size == 1)   //只有result，没有一些信息
	//							{
	//								if (rec_info.at(j+5) == compare[1])
	//								{
	//									ui.tableWidget_4->setItem(id, 2, new QTableWidgetItem(QString::fromLocal8Bit("测试成功")));
	//								}
	//								if (rec_info.at(j+5) == compare[3])
	//								{
	//									ui.tableWidget_4->setItem(id, 2, new QTableWidgetItem(QString::fromLocal8Bit("测试失败")));
	//								}
	//								emit finishedInfo4(/*1*/);
	//								//return;
	//							}
	//							else
	//							{
	//								if (rec_info.at(j+5) == compare[1])
	//								{
	//									ui.tableWidget_4->setItem(id, 2, new QTableWidgetItem(QString::fromLocal8Bit("测试成功")));
	//									//QString info(rec_info.data() + 6);
	//									//QString str = QString(QLatin1String(rec_info.data() + 6));//////////正确转换方式，待试，但是数组最后一位是校验和，得去掉
	//									QByteArray info = QByteArray(rec_info.data() + j + 6, size);
	//									ui.tableWidget_4->setItem(id, 3, new QTableWidgetItem(QString(info)));
	//								}
	//								if (rec_info.at(j+5) == compare[3])
	//								{
	//									ui.tableWidget_4->setItem(id, 2, new QTableWidgetItem(QString::fromLocal8Bit("测试失败")));
	//									//QString info(rec_info.data() + 6);
	//									QByteArray info = QByteArray(rec_info.data() + j + 6, size);
	//									ui.tableWidget_4->setItem(id, 3, new QTableWidgetItem(QString(info)));
	//								}
	//								emit finishedInfo4(/*1*/);
	//							}
	//						}
	//					}
	//					//上面完成一包的解析，所以下次循环应该直接跳到下一包，如果不跳，j是一个一个的增加，万一包的数据中存在0xef,就又进来了。
	//					if (j + 6 + size < rec_info.length())//如果size是0，那么一个包最少是6的固定长度
	//					{
	//						j = j + 5 + size;
	//					}
	//				}
	//			}
	//		}
	//	}
	//}







	//收到MCU到PC的调试信息保存到本地(收到调试信息)
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
	//				QString str = QString(QLatin1String(rec_info.data() + 6));//////////正确转换方式，待试，但是数组最后一位是校验和，得去掉
	//				ui.tableWidget_4->setItem(id, 3, new QTableWidgetItem(QString::number(xinID) + "," + str));
	//				emit finishedInfo4();
	//			}
	//			else
	//			{
	//				QString info(rec_info.data() + 5);
	//				QString str = QString(QLatin1String(rec_info.data() + 5));//////////正确转换方式，待试，但是数组最后一位是校验和，得去掉
	//				ui.tableWidget_4->setItem(id, 3, new QTableWidgetItem(info));
	//				emit finishedInfo4();
	//			}
	//		}
	//		//unsigned char Size[2] = { rec_info.at(3),rec_info.at(4) };
	//		//unsigned short size = reverse_uint16(Size);
	//		if (id > 1 && id != rowSize)
	//		{
	//			if (size == 1)   //只有result，没有一些信息
	//			{
	//				if (rec_info.at(5) == compare[1])
	//				{
	//					ui.tableWidget_4->setItem(id, 2, new QTableWidgetItem(QString::fromLocal8Bit("测试成功")));
	//				}
	//				if (rec_info.at(5) == compare[3])
	//				{
	//					ui.tableWidget_4->setItem(id, 2, new QTableWidgetItem(QString::fromLocal8Bit("测试失败")));
	//				}
	//				emit finishedInfo4(/*1*/);
	//				//return;
	//			}
	//			else
	//			{
	//				if (rec_info.at(5) == compare[1])
	//				{
	//					ui.tableWidget_4->setItem(id, 2, new QTableWidgetItem(QString::fromLocal8Bit("测试成功")));
	//					QString info(rec_info.data() + 6);
	//					QString str = QString(QLatin1String(rec_info.data() + 6));//////////正确转换方式，待试，但是数组最后一位是校验和，得去掉
	//					ui.tableWidget_4->setItem(id, 3, new QTableWidgetItem(info));
	//				}
	//				if (rec_info.at(5) == compare[3])
	//				{
	//					ui.tableWidget_4->setItem(id, 2, new QTableWidgetItem(QString::fromLocal8Bit("测试失败")));
	//					QString info(rec_info.data() + 6);
	//					ui.tableWidget_4->setItem(id, 3, new QTableWidgetItem(info));
	//				}
	//				emit finishedInfo4(/*1*/);
	//			}
	//		}
	//	}
	//}

	
}