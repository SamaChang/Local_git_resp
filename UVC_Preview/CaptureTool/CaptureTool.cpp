#include "CaptureTool.h"
#include <dshow.h>
#include "packet.h"
#include <qmessagebox.h>
#include <fstream>
#include "FilePath.h"
#include <mutex>
#include <qdatetime.h>
#include <qtextstream.h>
//#include "HCNetSDK.h"
//#include "CaptureSet.h"
//获取usb设备

#define IPADDRESS	"192.168.163.247"       //海康ip
#define PORT		8000					//海康端口号
//#define RGB_CAPTURE
//#define IR_SPK_CAPTURE

#pragma comment(lib, "strmiids.lib")
#pragma comment(lib, "quartz.lib")
using namespace std;
using namespace cv;
const char *g_szTitle = "Camera";
CaptureTool::CaptureTool(QWidget *parent)
    : QMainWindow(parent),rgb1_thread(nullptr), ir1_thread(nullptr),stopPlay(true), depth1_thread(nullptr)
	,spk1_thread(nullptr), isCircleShoot(false), all_stream_thread(nullptr), isCut(false),multiple(1)
{
    ui.setupUi(this);
	this->setWindowIcon(QIcon("./Logo.png"));
	this->setWindowTitle("Capture/Preview_Tool_V1.3");
	delay_time_to_shoot = 0;
	shot_times = 0;
	/*CaptureSet **/capset = new CaptureSet(this);
	initForm();
	status = new QLabel();
	ui.statusBar->addWidget(status);
	show_video_all();
	connect(ui.actionStart, SIGNAL(triggered()), this, SLOT(playAllVideo()));
	connect(ui.actionSave_File, SIGNAL(triggered()), this, SLOT(showFileDialog()));
	connect(ui.actionIR_SPK_Depth, SIGNAL(triggered()), this, SLOT(cap_ir_spk_dep()));
	connect(ui.actionIR_Stream, SIGNAL(triggered()), this, SLOT(start_ir1_video_thread()));
	connect(ui.actionSpk_Stream, SIGNAL(triggered()), this, SLOT(start_spk1_video_thread()));
	connect(ui.actionDepth_Stream, SIGNAL(triggered()), this, SLOT(start_depth1_video_thread()));
	connect(ui.actionStop, SIGNAL(triggered()), this, SLOT(stop_stream()));
	connect(ui.actionCapture_Set, SIGNAL(triggered()), this, SLOT(open_capture_set_form()));
	connect(ui.actionRGB_IR_Depth, SIGNAL(triggered()), this, SLOT(cap_rgb_ir_dep()));
	connect(ui.actionrotate, SIGNAL(triggered()), this, SLOT(cutVideo()));
	connect(ui.actionRgb_Stream, SIGNAL(triggered()), this, SLOT(start_rgb1_video_thread()));
	connect(ui.actionbigger, SIGNAL(triggered()), this, SLOT(biggerVideo()));
	connect(ui.actionsmaller, SIGNAL(triggered()), this, SLOT(smallerVideo()));
	connect(ui.actionRGB_IR_SPK, SIGNAL(triggered()), this, SLOT(cap_rgb_ir_spk()));
	//connect(timer,SIGNAL(timeout()),this,SLOT())
	getUsbDev();
	//海康
	//initCamera();
	//connectCamera();
	//registerCamera();
}

CaptureTool::~CaptureTool()
{
	if(rgb1_thread != nullptr)
	{
		stopPlay = false;
		rgb1_thread->join();
		rgb1_thread = nullptr;
	}
	cap_rgb1.release();

	if (ir1_thread != nullptr)
	{
		stopPlay = false;
		ir1_thread->join();
		ir1_thread = nullptr;
	}
	cap_ir1.release();

	if (spk1_thread != nullptr)
	{
		stopPlay = false;
		spk1_thread->join();
		spk1_thread = nullptr;
	}
	cap_spk1.release();

	if (depth1_thread != nullptr)
	{
		stopPlay = false;
		depth1_thread->join();
		depth1_thread = nullptr;
		usb_release();
	}

	if (all_stream_thread != nullptr)
	{
		stopPlay = false;
		all_stream_thread->join();
		all_stream_thread = nullptr;
		cameraDs.CloseCamera();   //关闭direcshow摄像头
	}

	if (all_stream_thread_2 != nullptr)
	{
		stopPlay = false;
		all_stream_thread_2->join();
		all_stream_thread_2 = nullptr;
		cameraDs_2.CloseCamera();   //关闭direcshow摄像头
	}


	//if (ir_video_thread != nullptr)
	//{
	//	stopPlay = false;
	//	ir_video_thread->join();
	//	ir_video_thread = nullptr;
	//}
	
	//if (depth_video_thread != nullptr)
	//{
	//	stopPlay = false;
	//	depth_video_thread->join();
	//	depth_video_thread = nullptr;
	//}
}
//获取usb设备
int listDevices(vector<QString>& list) {

	//COM Library Initialization
	//comInit();

	//if (!silent) DebugPrintOut("\nVIDEOINPUT SPY MODE!\n\n");

	ICreateDevEnum *pDevEnum = NULL;
	IEnumMoniker *pEnum = NULL;
	int deviceCounter = 0;
	CoInitialize(NULL);

	HRESULT hr = CoCreateInstance(CLSID_SystemDeviceEnum, NULL,
		CLSCTX_INPROC_SERVER, IID_ICreateDevEnum,
		reinterpret_cast<void**>(&pDevEnum));


	if (SUCCEEDED(hr))
	{
		// Create an enumerator for the video capture category.
		hr = pDevEnum->CreateClassEnumerator(
			CLSID_VideoInputDeviceCategory,
			&pEnum, 0);

		if (hr == S_OK) {

			printf("SETUP: Looking For Capture Devices\n");
			IMoniker *pMoniker = NULL;

			while (pEnum->Next(1, &pMoniker, NULL) == S_OK) {

				IPropertyBag *pPropBag;
				hr = pMoniker->BindToStorage(0, 0, IID_IPropertyBag,
					(void**)(&pPropBag));

				if (FAILED(hr)) {
					pMoniker->Release();
					continue;  // Skip this one, maybe the next one will work.
				}


				// Find the description or friendly name.
				VARIANT varName;
				VariantInit(&varName);
				hr = pPropBag->Read(L"Description", &varName, 0);

				if (FAILED(hr)) hr = pPropBag->Read(L"FriendlyName", &varName, 0);

				if (SUCCEEDED(hr))
				{

					hr = pPropBag->Read(L"FriendlyName", &varName, 0);

					int count = 0;
					char tmp[255] = { 0 };
					//int maxLen = sizeof(deviceNames[0]) / sizeof(deviceNames[0][0]) - 2;
					while (varName.bstrVal[count] != 0x00 && count < 255)
					{
						tmp[count] = (char)varName.bstrVal[count];
						count++;
					}
					list.push_back(tmp);
					//deviceNames[deviceCounter][count] = 0;

					//if (!silent) DebugPrintOut("SETUP: %i) %s\n", deviceCounter, deviceNames[deviceCounter]);
				}

				pPropBag->Release();
				pPropBag = NULL;

				pMoniker->Release();
				pMoniker = NULL;

				deviceCounter++;
			}

			pDevEnum->Release();
			pDevEnum = NULL;

			pEnum->Release();
			pEnum = NULL;
		}

		//if (!silent) DebugPrintOut("SETUP: %i Device(s) found\n\n", deviceCounter);
	}

	//comUnInit();
	
	return deviceCounter;
}
//获取usb设备
void CaptureTool::getUsbDev()
{
	vector<QString> list;
	//QStringList qList;
	listDevices(list);
	for (int i = 0; i < list.size(); i++)
	{
		//qList << list[i];
		ui.menuUSB_Device->addAction(list[i]);
	}
	//if(ui.menuUSB_Device->activeAction())
}

//#ifdef DEBUG
//bool CaptureTool::eventFilter(QObject *watched, QEvent *event)
//{
//	if (event->type() == QEvent::MouseButtonDblClick) {
//		QLabel *widget = (QLabel *)watched;
//		if (!videoMax) {
//			videoMax = true;
//			hide_video_all();
//			ui.gridLayout->addWidget(widget, 0, 0);
//			widget->setVisible(true);
//		}
//		else {
//			videoMax = false;
//			show_video_all();
//		}
//	}
//	else if (event->type() == QEvent::MouseButtonPress) {
//		if (qApp->mouseButtons() == Qt::RightButton) {
//			videoMenu->exec(QCursor::pos());
//		}
//	}
//
//	return QWidget::eventFilter(watched, event);
//}
//#endif // DEBUG
//初始化窗口
void CaptureTool::initForm()
{
	//设置样式表
	QStringList qss;
	qss.append("QFrame{border:2px solid #000000;}");
	qss.append("QLabel{font:75 25px;color:#F0F0F0;border:2px solid #AAAAAA;background:#000000;}");
	qss.append("QLabel:focus{border:2px solid #00BB9E;background:#555555;}");
	ui.frame->setStyleSheet(qss.join(""));

	videoMax = false; 
	videoType = "1_16";  

	for (int i = 0; i < VIDEOCOUNT; i++) {
		QLabel *widget = new QLabel;
		widget->setObjectName(QString("video%1").arg(i + 1));
		widget->setAlignment(Qt::AlignCenter);  //widget的对齐方式居中对齐,如果视频比组件小，那么就位于组件的中间
		//widget->setFixedSize(QSize(/*UVC_IMG_WIDTH*/180, /*UVC_IMG_HEIGHT*/320));   //设置组件固定大小

	
		widgets.append(widget);
	}
}
#ifdef DEBUG
void CaptureTool::initMenu()
{
	videoMenu = new QMenu(this);
	videoMenu->addAction("截图当前视频", this, SLOT(snapshot_video_one()));
	videoMenu->addAction("截图所有视频", this, SLOT(snapshot_video_all()));
	videoMenu->addSeparator();

	QMenu *menu4 = videoMenu->addMenu(QString::fromLocal8Bit("切换到4画面"));
	menu4->addAction(QString::fromLocal8Bit("通道1-通道4"), this, SLOT(show_video_4()));
	menu4->addAction(QString::fromLocal8Bit("通道5-通道8"), this, SLOT(show_video_4()));
	menu4->addAction(QString::fromLocal8Bit("通道9-通道12"), this, SLOT(show_video_4()));
	menu4->addAction(QString::fromLocal8Bit("通道13-通道16"), this, SLOT(show_video_4()));

	QMenu *menu6 = videoMenu->addMenu("切换到6画面");
	menu6->addAction("通道1-通道6", this, SLOT(show_video_6()));
	menu6->addAction("通道6-通道11", this, SLOT(show_video_6()));
	menu6->addAction("通道11-通道16", this, SLOT(show_video_6()));

	QMenu *menu8 = videoMenu->addMenu("切换到8画面");
	menu8->addAction("通道1-通道8", this, SLOT(show_video_8()));
	menu8->addAction("通道9-通道16", this, SLOT(show_video_8()));

	QMenu *menu9 = videoMenu->addMenu("切换到9画面");
	menu9->addAction("通道1-通道9", this, SLOT(show_video_9()));
	menu9->addAction("通道8-通道16", this, SLOT(show_video_9()));

	videoMenu->addAction("切换到16画面", this, SLOT(show_video_16()));
}
#endif // DEBUG

void CaptureTool::snapshot_video_one()
{

}

void CaptureTool::show_video_4()
{
	videoMax = false;
	QString videoType;
	int index = 0;

	QAction *action = (QAction *)sender();
	QString name = action->text();

	if (name == "通道1-通道4") {
		index = 0;
		videoType = "1_4";
	}
	else if (name == "通道5-通道8") {
		index = 4;
		videoType = "5_8";
	}
	else if (name == "通道9-通道12") {
		index = 8;
		videoType = "9_12";
	}
	else if (name == "通道13-通道16") {
		index = 12;
		videoType = "13_16";
	}

	if (this->videoType != videoType) {
		this->videoType = videoType;
		change_video_4(index);
	}
}

void CaptureTool::show_video_6()
{
	videoMax = false;
	QString videoType;
	int index = 0;

	QAction *action = (QAction *)sender();
	QString name = action->text();

	if (name == "通道1-通道6") {
		index = 0;
		videoType = "1_6";
	}
	else if (name == "通道6-通道11") {
		index = 5;
		videoType = "6_11";
	}
	else if (name == "通道11-通道16") {
		index = 10;
		videoType = "11_16";
	}

	if (this->videoType != videoType) {
		this->videoType = videoType;
		change_video_6(index);
	}
}

void CaptureTool::show_video_8()
{
	videoMax = false;
	QString videoType;
	int index = 0;

	QAction *action = (QAction *)sender();
	QString name = action->text();

	if (name == "通道1-通道8") {
		index = 0;
		videoType = "1_8";
	}
	else if (name == "通道9-通道16") {
		index = 8;
		videoType = "9_16";
	}

	if (this->videoType != videoType) {
		this->videoType = videoType;
		change_video_8(index);
	}
}

void CaptureTool::show_video_9()
{
	videoMax = false;
	QString videoType;
	int index = 0;

	QAction *action = (QAction *)sender();
	QString name = action->text();

	if (name == "通道1-通道9") {
		index = 0;
		videoType = "1_9";
	}
	else if (name == "通道8-通道16") {
		index = 7;
		videoType = "8_16";
	}

	if (this->videoType != videoType) {
		this->videoType = videoType;
		change_video_9(index);
	}
}

void CaptureTool::show_video_16()
{
	videoMax = false;
	QString videoType;
	int index = 0;
	videoType = "1_16";

	if (this->videoType != videoType) {
		this->videoType = videoType;
		change_video_16(index);
	}
}

void CaptureTool::hide_video_all()
{
	for (int i = 0; i < VIDEOCOUNT; i++) {
		ui.gridLayout->removeWidget(widgets.at(i));
		widgets.at(i)->setVisible(false);
	}
}

void CaptureTool::change_video(int index, int flag)
{

	for (int i = 0; i < VIDEOCOUNT; i++) {
		int m_row = 3;
		int m_col = 2;
		int column = i % m_row;
		int row = i / m_row;
		ui.gridLayout->addWidget(widgets.at(i), row, column);
		widgets.at(i)->setVisible(true);
	}
}

void CaptureTool::change_video_4(int index)
{
	hide_video_all();
	change_video(index, 2);
}

void CaptureTool::change_video_6(int index)
{
	hide_video_all();
	if (index == 0) {
		ui.gridLayout->addWidget(widgets.at(0), 0, 0, 2, 2);
		ui.gridLayout->addWidget(widgets.at(1), 0, 2, 1, 1);
		ui.gridLayout->addWidget(widgets.at(2), 1, 2, 1, 1);
		ui.gridLayout->addWidget(widgets.at(3), 2, 2, 1, 1);
		ui.gridLayout->addWidget(widgets.at(4), 2, 1, 1, 1);
		ui.gridLayout->addWidget(widgets.at(5), 2, 0, 1, 1);

		for (int i = 0; i < 6; i++) {
			widgets.at(i)->setVisible(true);
		}
	}
	else if (index == 5) {
		ui.gridLayout->addWidget(widgets.at(5), 0, 0, 2, 2);
		ui.gridLayout->addWidget(widgets.at(6), 0, 2, 1, 1);
		ui.gridLayout->addWidget(widgets.at(7), 1, 2, 1, 1);
		ui.gridLayout->addWidget(widgets.at(8), 2, 2, 1, 1);
		ui.gridLayout->addWidget(widgets.at(9), 2, 1, 1, 1);
		ui.gridLayout->addWidget(widgets.at(10), 2, 0, 1, 1);

		for (int i = 5; i < 11; i++) {
			widgets.at(i)->setVisible(true);
		}
	}
	else if (index == 10) {
		ui.gridLayout->addWidget(widgets.at(10), 0, 0, 2, 2);
		ui.gridLayout->addWidget(widgets.at(11), 0, 2, 1, 1);
		ui.gridLayout->addWidget(widgets.at(12), 1, 2, 1, 1);
		ui.gridLayout->addWidget(widgets.at(13), 2, 2, 1, 1);
		ui.gridLayout->addWidget(widgets.at(14), 2, 1, 1, 1);
		ui.gridLayout->addWidget(widgets.at(15), 2, 0, 1, 1);

		for (int i = 10; i < 16; i++) {
			widgets.at(i)->setVisible(true);
		}
	}
}

void CaptureTool::change_video_8(int index)
{
	hide_video_all();
	if (index == 0) {
		ui.gridLayout->addWidget(widgets.at(0), 0, 0, 3, 3);
		ui.gridLayout->addWidget(widgets.at(1), 0, 3, 1, 1);
		ui.gridLayout->addWidget(widgets.at(2), 1, 3, 1, 1);
		ui.gridLayout->addWidget(widgets.at(3), 2, 3, 1, 1);
		ui.gridLayout->addWidget(widgets.at(4), 3, 3, 1, 1);
		ui.gridLayout->addWidget(widgets.at(5), 3, 2, 1, 1);
		ui.gridLayout->addWidget(widgets.at(6), 3, 1, 1, 1);
		ui.gridLayout->addWidget(widgets.at(7), 3, 0, 1, 1);

		for (int i = 0; i < 8; i++) {
			widgets.at(i)->setVisible(true);
		}
	}
	else if (index == 8) {
		ui.gridLayout->addWidget(widgets.at(8), 0, 0, 3, 3);
		ui.gridLayout->addWidget(widgets.at(9), 0, 3, 1, 1);
		ui.gridLayout->addWidget(widgets.at(10), 1, 3, 1, 1);
		ui.gridLayout->addWidget(widgets.at(11), 2, 3, 1, 1);
		ui.gridLayout->addWidget(widgets.at(12), 3, 3, 1, 1);
		ui.gridLayout->addWidget(widgets.at(13), 3, 2, 1, 1);
		ui.gridLayout->addWidget(widgets.at(14), 3, 1, 1, 1);
		ui.gridLayout->addWidget(widgets.at(15), 3, 0, 1, 1);

		for (int i = 8; i < 16; i++) {
			widgets.at(i)->setVisible(true);
		}
	}
}

void CaptureTool::change_video_9(int index)
{
	hide_video_all();
	change_video(index, 3);
}

void CaptureTool::change_video_16(int index)
{
	hide_video_all();
	change_video(index, 4);
}

void CaptureTool::show_video_all()
{
	if (videoType == "1_4") {
		change_video_4(0);
	}
	else if (videoType == "5_8") {
		change_video_4(4);
	}
	else if (videoType == "9_12") {
		change_video_4(8);
	}
	else if (videoType == "13_16") {
		change_video_4(12);
	}
	else if (videoType == "1_6") {
		change_video_6(0);
	}
	else if (videoType == "6_11") {
		change_video_6(5);
	}
	else if (videoType == "11_16") {
		change_video_6(10);
	}
	else if (videoType == "1_8") {
		change_video_8(0);
	}
	else if (videoType == "9_16") {
		change_video_8(8);
	}
	else if (videoType == "1_9") {
		change_video_9(0);
	}
	else if (videoType == "8_16") {
		change_video_9(7);
	}
	else if (videoType == "1_16") {
		change_video_16(0);
	}
}

/****************************************************************/
//海康SDK
//设备初始化
void CaptureTool::initCamera()
{
	if (!NET_DVR_Init())   //初始化SDK
	{
		QMessageBox::warning(this, "error", "NET_DVR_Init error;error number is " + QString::number(NET_DVR_GetLastError()));//返回错误码
		NET_DVR_Cleanup();
		return;
	}
}
//连接设备
void CaptureTool::connectCamera()
{
	DWORD dwWaitTime = 3000;   //网络连接超时时间
	DWORD dwTryTime = 1;	//连接尝试次数
	DWORD dwInterval = 2000;    //重连间隔
	BOOL enableRecon = true;    //是否重连
	if (!NET_DVR_SetConnectTime(dwWaitTime, dwTryTime))    //设置网络连接超时时间和连接尝试次数
	{
		//NET_DVR_GetLastError();
		if (!NET_DVR_SetReconnect(dwInterval, enableRecon))    //重连
		{
			QMessageBox::critical(nullptr, QString::fromLocal8Bit("Error"), QString::fromLocal8Bit("Reconnect Fail!"), QMessageBox::Ok);
			NET_DVR_Cleanup();
			return;
		}
	}
}
//注册设备
void CaptureTool::registerCamera()
{
	NET_DVR_DEVICEINFO_V30 lpDeviceinfo;   //获得硬件信息
	IUserID = NET_DVR_Login_V30(IPADDRESS, PORT, "admin", "megvii123", &lpDeviceinfo);
	if (IUserID < 0)
	{
		//QMessageBox::critical(nullptr, QString::fromLocal8Bit("Error"), QString::fromLocal8Bit("Register Fail!"), QMessageBox::Ok);
		QMessageBox::warning(this, "error", "NET_DVR_Login_V30 error;error number " + QString::number(NET_DVR_GetLastError()));
		NET_DVR_Cleanup();
		return;
	}
}
//预览函数需要获得窗体句柄，并且是Windows api中定义的句柄，本质上来讲，QT写出的窗体也是windows窗体，我们这里直接定义一个label控件，控件中有个成员函数是专门获得windows下的窗体句柄的，传入该句柄后，
//函数就会自动向窗体传递图像信息并显示，不需我们的任何操作，同时也不会阻塞在这个函数，应该是直接利用了windows api的消息机制
//预览
void CaptureTool::startPreview()
{
	HWND hwnd = (HWND)(widgets.at(0))->winId();     //获取控件的windows窗口句柄
	NET_DVR_PREVIEWINFO struPlayInfo = { 0 };
	struPlayInfo.hPlayWnd = hwnd;
	struPlayInfo.lChannel = 1;      //预览通道号
	struPlayInfo.dwStreamType = 0;		//0-主码流，1-子码流，2-码流 3，3-码流 4，以此类推
	struPlayInfo.dwLinkMode = 0;    //0- TCP 方式，1- UDP 方式，2- 多播方式，3- RTP 方式，4-RTP/RTSP，5-RSTP/HTTP
	struPlayInfo.bBlocked = 1;      //0- 非阻塞取流，1- 阻塞取流
	IRealPlayHandle = NET_DVR_RealPlay_V40(IUserID, &struPlayInfo, nullptr, nullptr);
	if (IRealPlayHandle < 0)
	{
		QMessageBox::warning(this, "error", "NET_DVR_RealPlay_V40 error;error number " + QString::number(NET_DVR_GetLastError()));
		NET_DVR_Cleanup();
		return;
	}
}
//停止预览
void CaptureTool::stopPreview()
{
	Sleep(1500);
	NET_DVR_StopRealPlay(IRealPlayHandle);  //关闭预览
	NET_DVR_Logout(IUserID);   //用户注销
	NET_DVR_Cleanup();    //释放SDK资源
}
//预览时抓图
void CaptureTool::hkCapture()
{
	if (!NET_DVR_SetCapturePictureMode(BMP_MODE))    //设置抓图模式，BMP模式，JPEG_MODE为JPEG模式
	{
		QMessageBox::warning(this, "error", "NET_DVR_SetCapturePictureMode error;error number " + QString::number(NET_DVR_GetLastError()));
	}
	if (!NET_DVR_CapturePicture(IRealPlayHandle, "D:\\ARGB\\4\\C_1.bmp"))
	{
		QMessageBox::warning(this, "error", "NET_DVR_CapturePicture error;error number " + QString::number(NET_DVR_GetLastError()));
	}
}
/****************************************************************/
//日志保存
void CaptureTool::send_rec(QString path, QString send_info, QString sendOrRec)
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

void CaptureTool::cutVideo()
{
	if (isCut)
		isCut = false;
	else
	{
		isCut = true;
	}
}

void CaptureTool::mainThread_show(QLabel *label, QPixmap pix)
{
	label->setPixmap(pix);
	label->show();
}
//3图全显示
void CaptureTool::showAllStream()
{
	/********************************************/
	////Amcap显示yuv视频
	//yuyv.resize(UVC_IMG_WIDTH * UVC_IMG_HEIGHT * 2);   //yuv422都是一个像素2个字节
	//	IplImage *pFrame = NULL;
	//	
	//	cvNamedWindow(g_szTitle);
	//	//显示
	//	cvShowImage(g_szTitle, pFrame);

	//	while (1)
	//	{
	//		//获取一帧
	//		pFrame = cameraDs.QueryFrame((void*)&yuyv[0], UVC_IMG_WIDTH * UVC_IMG_HEIGHT * 2);

	//		//显示
	//		cvShowImage(g_szTitle, pFrame); /*imshow("daf", pFrame);*/

	//		if (cvWaitKey(20) == 'q')
	//		{
	//			break;
	//		}
	//	}
	/*************************************************/

	static int l = 0;
	stopPlay = true;
	//std::vector<unsigned char> yuyv;
	yuyv.resize(UVC_IMG_WIDTH * UVC_IMG_HEIGHT * 2);   //yuv422都是一个像素2个字节
	int type = 0x00;
	int type_prev = 0x01;
	//ir_video_thread = new std::thread(&CaptureTool::irVideo, this);
	//rgb_video_thread = new std::thread(&CaptureTool::rgbVideo, this);
	//depth_video_thread = new std::thread(&CaptureTool::depthVideo, this);
	QString current_time = "1";
	while (stopPlay) {
		//if (pDlg->b_closeCam)//退出循环
		//	break;

		void* p = &yuyv[0];
		/*bool haveFrame= */cameraDs.QueryFrame((void*)&yuyv[0], UVC_IMG_WIDTH * UVC_IMG_HEIGHT * 2);   //取uvc的原始数据  //这里必须是1280*721*2的长度，因为这才是一帧的数据，如果只需640*400*2，则数据不对。
		//send_rec("./log.txt", "...", "Receive One Frame");
		/*type = yuyv[0];
		if (type == type_prev)
			continue;
		type_prev = yuyv[0];*/																							//memcpy(&all_stream[0], &yuyv[0], UVC_IMG_HEIGHT*UVC_IMG_WIDTH);


		//if (!haveFrame)
		//{
		//	break;
		//}

		////抓取ir图
		//ostringstream  cur;
		//cur << "./aa" << l << ".raw";
		//string dd = cur.str();
		////std::ofstream cc("./aa.raw", std::ios::binary);//app表示每次操作前均定位到文件末尾
		//std::ofstream cc(dd, std::ios::binary);//app表示每次操作前均定位到文件末尾
		//if (cc.fail()) {
		//	cout << "error\n";
		//}
		////cc.write((char*)/*&yuyv[0]*/(&yuyv[0]/* + 640 * 400 * 2*/), UVC_IMG_WIDTH * UVC_IMG_HEIGHT);
		//
		//if (yuyv[0]==0x0a)   //ir
		//{
		//	cc.write((char*)/*&yuyv[0]*/(&yuyv[0]/* + 640 * 400 * 2*/), UVC_IMG_WIDTH * UVC_IMG_HEIGHT);
		//}
		//else    //depth
		//{
		//	cc.write((char*)/*&yuyv[0]*/(&yuyv[0]/* + 640 * 400 * 2*/), UVC_IMG_WIDTH * UVC_IMG_HEIGHT * 2);
		//}
		//
		//cc.close();
		//l++;

		//预览
		//通用把ir和spk一起发，都是0a.然后0-640*360ir,后面是spk,一帧总长度还是640*360*2
		if (yuyv[0] == 0x0a)   //ir_stream  raw数据
		{
			//send_rec("./log.txt", "...", "Receive 0xa");
			static int fps = 0;
			//memcpy(&all_stream[0], &yuyv[0], UVC_IMG_HEIGHT*UVC_IMG_WIDTH);   //ir
			//memcpy(&all_stream_2[0], &yuyv[0] + UVC_IMG_HEIGHT * UVC_IMG_WIDTH, UVC_IMG_HEIGHT*UVC_IMG_WIDTH);   //spk

#ifdef IR_SPK_CAPTURE
			ostringstream  cur;
			cur << "./aa" << l << ".raw";
			string dd = cur.str();
			//std::ofstream cc("./aa.raw", std::ios::binary);//app表示每次操作前均定位到文件末尾
			std::ofstream cc(dd, std::ios::binary);//app表示每次操作前均定位到文件末尾
			if (cc.fail()) {
				cout << "error\n";
			}
			cc.write((char*)/*&yuyv[0]*/(/*&all_stream[0]*/&yuyv[0]), UVC_IMG_WIDTH * UVC_IMG_HEIGHT);
			cc.close();
			
			ostringstream  curs;
			curs << "./bb" << l << ".raw";
			string ee = curs.str();
			std::ofstream ff(ee, std::ios::binary);//app表示每次操作前均定位到文件末尾
			if (ff.fail()) {
				cout << "error\n";
			}
			ff.write((char*)/*&yuyv[0]*/(/*&all_stream_2[0]*/&yuyv[0] + UVC_IMG_WIDTH * UVC_IMG_HEIGHT), UVC_IMG_WIDTH * UVC_IMG_HEIGHT);
			ff.close();
			l++;
#else
			Sleep(50);
			//ir
			Mat ir_src(UVC_IMG_HEIGHT, UVC_IMG_WIDTH, CV_8UC1, /*&all_stream[0]*/&yuyv[0]);
			//imshow("ir", ir_src);
			//waitKey(0);
			QImage img_ir = QImage((unsigned char*)ir_src.data, ir_src.cols, ir_src.rows, ir_src.step, QImage::Format_Indexed8);  //ir原图转QImage
			QPixmap pixmap_ir = QPixmap::fromImage(img_ir);
			mainThread_show(widgets.at(1), pixmap_ir);
			//widgets.at(1)->setPixmap(pixmap_ir);
			//widgets.at(1)->show();
			//send_rec("./log.txt", "...", "IR Completed");
			
			Mat spk_src(UVC_IMG_HEIGHT, UVC_IMG_WIDTH, CV_8UC1, /*&all_stream_2[0]*/&yuyv[0] + UVC_IMG_HEIGHT * UVC_IMG_WIDTH);
			//imshow("spk", spk_src);
			//waitKey(0);
			QImage img_spk = QImage((unsigned char*)spk_src.data, spk_src.cols, spk_src.rows, spk_src.step, QImage::Format_Indexed8);  //ir原图转QImage
			QPixmap pixmap_spk = QPixmap::fromImage(img_spk);
			mainThread_show(widgets.at(2), pixmap_spk);
			//widgets.at(2)->setPixmap(pixmap_spk);
			//widgets.at(2)->show();
			//send_rec("./log.txt", "...", "SPK Completed");

			QString timestamp = QString::number(QDateTime::currentMSecsSinceEpoch() / 1000);
			
			if (current_time.toInt() != timestamp.toInt())
			{
				status->setText("fps:" + QString::number(fps));
				fps = 0;
			}
			current_time = timestamp;
			fps++;
#endif
		}
		//图漾有0b，通用都是0a
		//if(yuyv[0]==0x0b)  //图漾是depth_stream   //   raw数据
		//{
		//	memcpy(&all_stream_2[0], &yuyv[0], UVC_IMG_HEIGHT*UVC_IMG_WIDTH*2);

		//	Mat src_depth(UVC_IMG_HEIGHT, UVC_IMG_WIDTH, CV_16UC1, &all_stream_2[0]);
		//	//imshow("depth", src_depth);
		//	//waitKey(0);
		//	QImage Qtemp = QImage((const unsigned char*)(src_depth.data), src_depth.cols, src_depth.rows, src_depth.step, QImage::Format_Grayscale16);
		//	widgets.at(1)->setPixmap(QPixmap::fromImage(Qtemp));
		//	widgets.at(1)->resize(Qtemp.size());
		//	widgets.at(1)->show();
		//}

		if(yuyv[0]==0x0c)   //yuv422数据
		{
			//send_rec("./log.txt", "...", "Receive 0xc");
			//memcpy(&all_stream_1[0], &yuyv[0], UVC_IMG_HEIGHT*UVC_IMG_WIDTH * 2);
			
#ifdef RGB_CAPTURE
			ostringstream  cur;
			cur << "./rgb" << l << ".raw";
			string dd = cur.str();
			//std::ofstream cc("./aa.raw", std::ios::binary);//app表示每次操作前均定位到文件末尾
			std::ofstream cc(dd, std::ios::binary);//app表示每次操作前均定位到文件末尾
			if (cc.fail()) {
				cout << "error\n";
			}
			cc.write((char*)/*&yuyv[0]*/(&yuyv[0]/* + 640 * 400 * 2*/), UVC_IMG_WIDTH * UVC_IMG_HEIGHT * 2);

			cc.close();
			l++;

#ifdef
			for (int i = 0; i < UVC_IMG_HEIGHT; i++) {
				for (int j = 0; j < UVC_IMG_WIDTH; j++) {
					//偶数提v
					if (j % 2 == 0)
					{
						//两种不同转换方式1，有溢出
						//all_stream_1[3 * i * UVC_IMG_WIDTH + 3 * j + 2] = 1.164*(yuyv[2 * i*UVC_IMG_WIDTH + 2 * j] - 16) + 1.596*(yuyv[2 * i*UVC_IMG_WIDTH + 2 * j + 3] - 128); //1.164*(Y’-16) + 1.596*(Cr'-128)
						//all_stream_1[3 * i * UVC_IMG_WIDTH + 3 * j + 1] = 1.164*(yuyv[2 * i*UVC_IMG_WIDTH + 2 * j] - 16) - 0.813*(yuyv[2 * i*UVC_IMG_WIDTH + 2 * j + 3] - 128) - 0.391* (yuyv[2 * i*UVC_IMG_WIDTH + 2 * j + 1] - 128);
						//all_stream_1[3 * i * UVC_IMG_WIDTH + 3 * j + 0] = 1.164*(yuyv[2 * i*UVC_IMG_WIDTH + 2 * j] - 16) + 2.018* (yuyv[2 * i*UVC_IMG_WIDTH + 2 * j + 1] - 128);
						
						//两种不同转换方式2，无溢出，完美显示，RGB格式
						all_stream_1[3 * i * UVC_IMG_WIDTH + 3 * j + 0] = (yuyv[2 * i*UVC_IMG_WIDTH + 2 * j]) + 1.4075*(yuyv[2 * i*UVC_IMG_WIDTH + 2 * j + 3] - 128);  //R
						all_stream_1[3 * i * UVC_IMG_WIDTH + 3 * j + 1] = (yuyv[2 * i*UVC_IMG_WIDTH + 2 * j]) - 0.7169*(yuyv[2 * i*UVC_IMG_WIDTH + 2 * j + 3] - 128) - 0.3455* (yuyv[2 * i*UVC_IMG_WIDTH + 2 * j + 1] - 128);   //G
						all_stream_1[3 * i * UVC_IMG_WIDTH + 3 * j + 2] = (yuyv[2 * i*UVC_IMG_WIDTH + 2 * j]) + 1.779* (yuyv[2 * i*UVC_IMG_WIDTH + 2 * j + 1] - 128);  //B
					}
					//奇数提u
					else
					{
						all_stream_1[3 * i * UVC_IMG_WIDTH + 3 * j + 0] = (yuyv[2 * i*UVC_IMG_WIDTH + 2 * j]) + 1.4075*(yuyv[2 * i*UVC_IMG_WIDTH + 2 * j + 1] - 128);   //R
						all_stream_1[3 * i * UVC_IMG_WIDTH + 3 * j + 1] = (yuyv[2 * i*UVC_IMG_WIDTH + 2 * j]) - 0.7169*(yuyv[2 * i*UVC_IMG_WIDTH + 2 * j + 1] - 128) - 0.3455* (yuyv[2 * i*UVC_IMG_WIDTH + 2 * j - 1] - 128);   //G
						all_stream_1[3 * i * UVC_IMG_WIDTH + 3 * j + 2] = (yuyv[2 * i*UVC_IMG_WIDTH + 2 * j]) + 1.779* (yuyv[2 * i*UVC_IMG_WIDTH + 2 * j - 1] - 128);   //B
					}
				}
			}
			Mat srcCopy(UVC_IMG_WIDTH, UVC_IMG_HEIGHT/*cv::Size(400, 640)*/, CV_8UC3, &all_stream_1[0]);
			//cvtColor(srcCopy, srcCopy, COLOR_YUV2RGB_UYNV);
			transpose(srcCopy, srcCopy);
			flip(srcCopy, srcCopy, 0);//flip(srcCopy, srcCopy, 1);  //rotate 270 
			//cvtColor(srcCopy, srcCopy, CV_BGR2RGB);//输入源格式转换（转换后色调正常）   BGR格式的话颜色不对，需转换成RGB

			//裁剪
			if(isCut)
				srcCopy = srcCopy(Range(320, 960),Range(180, 540));   //裁成360*640
			

			QImage img = QImage((unsigned char*)srcCopy.data, srcCopy.cols, srcCopy.rows, srcCopy.step, QImage::Format_RGB888);
			
			//原始分辨率显示
			//widgets.at(0)->setPixmap(QPixmap::fromImage(img));
			//widgets.at(0)->show();


			////按照360，640等比例缩放，以180,320为窗口比例进行等比缩放
			QPixmap pixmap = QPixmap::fromImage(img);
			QPixmap fitpixmap = pixmap.scaled(/*UVC_IMG_WIDTH*//*180*/360, /*UVC_IMG_HEIGHT*//*320*/640, Qt::KeepAspectRatio, Qt::SmoothTransformation); //按比例缩放  
			//widgets.at(0)->setPixmap(fitpixmap);
			//widgets.at(0)->show();
			mainThread_show(widgets.at(0), fitpixmap);
#endif // !

#else
			Mat yuv_img(UVC_IMG_WIDTH, UVC_IMG_HEIGHT, CV_8UC2, &yuyv[0]);
			Mat rgb;
			cvtColor(yuv_img, rgb, CV_YUV2RGB_YUY2); //CV_YUV2BGR_YUY2
			transpose(rgb, rgb);
			flip(rgb, rgb, 0);//flip(srcCopy, srcCopy, 1);  //rotate 270 
			QImage img = QImage((unsigned char*)rgb.data, rgb.cols, rgb.rows, rgb.step, QImage::Format_RGB888);
			QPixmap pixmap = QPixmap::fromImage(img);
			QPixmap fitpixmap = pixmap.scaled(/*UVC_IMG_WIDTH*//*180*/360* multiple, /*UVC_IMG_HEIGHT*//*320*/640* multiple, Qt::KeepAspectRatio, Qt::SmoothTransformation); //按比例缩放  
			mainThread_show(widgets.at(0), fitpixmap);
			//imshow("rgb", rgb);
			//waitKey(0);
#endif // DEBUG
		}


		//////由于IR是8bit单通道的yuv422，只需要在SPK的基础上，后移640*400*2长度就好了
		//for (int i = 0; i < UVC_IMG_HEIGHT; i++) {
		//	for (int j = 0; j < UVC_IMG_WIDTH; j++) {
		//		all_stream[3 * i * UVC_IMG_WIDTH + 3 * j + 0] = yuyv[2 * i*UVC_IMG_WIDTH + 2 * j + 640 * 400 * 2];
		//		all_stream[3 * i * UVC_IMG_WIDTH + 3 * j + 1] = yuyv[2 * i*UVC_IMG_WIDTH + 2 * j + 640 * 400 * 2];
		//		all_stream[3 * i * UVC_IMG_WIDTH + 3 * j + 2] = yuyv[2 * i*UVC_IMG_WIDTH + 2 * j + 640 * 400 * 2];
		//	}
		//}

		//for (int i = 0; i < UVC_IMG_HEIGHT; i++) {
		//	for (int j = 0; j < UVC_IMG_WIDTH; j++) {
		//		all_stream_1[3 * i * UVC_IMG_WIDTH + 3 * j + 0] = yuyv[2 * i*UVC_IMG_WIDTH + 2 * j /*+ 640 * 400 * 2*/];
		//		all_stream_1[3 * i * UVC_IMG_WIDTH + 3 * j + 1] = yuyv[2 * i*UVC_IMG_WIDTH + 2 * j /*+ 640 * 400 * 2*/];
		//		all_stream_1[3 * i * UVC_IMG_WIDTH + 3 * j + 2] = yuyv[2 * i*UVC_IMG_WIDTH + 2 * j /*+ 640 * 400 * 2*/];
		//	}
		//}


		////cv::Mat img1(cv::Size(400, /*360*/640), CV_16UC1, resp);
		////做了图像90°旋转，将ir_stream旋转90°到srcCopy
		//Mat srcCopy(UVC_IMG_HEIGHT, UVC_IMG_WIDTH/*cv::Size(400, 640)*/, CV_8UC3, &all_stream[0]);
		////cvtColor(srcCopy, srcCopy, COLOR_YUV2RGB_UYNV);
		////imshow("show", srcCopy);
		////waitKey(0);
		//transpose(srcCopy, srcCopy);
		//flip(srcCopy, srcCopy, 0);//flip(srcCopy, srcCopy, 1);  //rotate 270 


		////cvtColor(srcCopy, srcCopy, CV_BGR2RGB);//输入源格式转换（转换后色调正常）
		//QImage img = QImage((unsigned char*)srcCopy.data, srcCopy.cols, srcCopy.rows, srcCopy.step, QImage::Format_RGB888);

		////窗口大小可自适应不同分辨率，
		//QPixmap pixmap = QPixmap::fromImage(img);
		////QPixmap fitpixmap = pixmap.scaled(UVC_IMG_WIDTH, UVC_IMG_HEIGHT, Qt::KeepAspectRatio, Qt::SmoothTransformation); //按比例缩放  
		//widgets.at(0)->setPixmap(pixmap);

		////ui.label->resize(img.size());
		//widgets.at(0)->show();



		//Mat srcCopy_1(UVC_IMG_HEIGHT, UVC_IMG_WIDTH/*cv::Size(400, 640)*/, CV_8UC3, &all_stream_1[0]);
		////cvtColor(srcCopy, srcCopy, COLOR_YUV2RGB_UYNV);
		////imshow("show", srcCopy);
		////waitKey(0);
		//transpose(srcCopy_1, srcCopy_1);
		//flip(srcCopy_1, srcCopy_1, 0);//flip(srcCopy, srcCopy, 1);  //rotate 270 


		////cvtColor(srcCopy, srcCopy, CV_BGR2RGB);//输入源格式转换（转换后色调正常）
		//QImage img_1 = QImage((unsigned char*)srcCopy_1.data, srcCopy_1.cols, srcCopy_1.rows, srcCopy_1.step, QImage::Format_RGB888);

		////窗口大小可自适应不同分辨率，
		//QPixmap pixmap_1 = QPixmap::fromImage(img_1);
		////QPixmap fitpixmap = pixmap.scaled(UVC_IMG_WIDTH, UVC_IMG_HEIGHT, Qt::KeepAspectRatio, Qt::SmoothTransformation); //按比例缩放  
		//widgets.at(1)->setPixmap(pixmap_1);

		////ui.label->resize(img.size());
		//widgets.at(1)->show();

	}


	//while (true)
	//{
	//	//void* p = &yuyv[0];
	//	int i = 0;
	//	for (i; i < 3; i++)
	//	{
	//		if (i == 0)
	//		{
	//			bool haveFrame = cameraDs.QueryFrame((void*)&yuyv[0], UVC_IMG_WIDTH * UVC_IMG_HEIGHT);    //ir原图是640*400*1
	//			con_ir.notify_one();
	//		}
	//		else if (i == 1)
	//		{
	//			cameraDs.QueryFrame((void *)&yuyv[0], UVC_IMG_WIDTH*UVC_IMG_HEIGHT);   //spk
	//			
	//		}
	//		else
	//		{
	//			cameraDs.QueryFrame((void *)&yuyv[0], UVC_IMG_WIDTH*UVC_IMG_HEIGHT * 2);   //depth
	//			con_depth.notify_one();
	//		}
	//	}
	//}
}

//另一台设备(门禁)新加
void CaptureTool::showAllStream_2()
{
	/********************************************/
	////Amcap显示yuv视频
	//yuyv.resize(UVC_IMG_WIDTH * UVC_IMG_HEIGHT * 2);   //yuv422都是一个像素2个字节
	//	IplImage *pFrame = NULL;
	//	
	//	cvNamedWindow(g_szTitle);
	//	//显示
	//	cvShowImage(g_szTitle, pFrame);

	//	while (1)
	//	{
	//		//获取一帧
	//		pFrame = cameraDs.QueryFrame((void*)&yuyv[0], UVC_IMG_WIDTH * UVC_IMG_HEIGHT * 2);

	//		//显示
	//		cvShowImage(g_szTitle, pFrame); /*imshow("daf", pFrame);*/

	//		if (cvWaitKey(20) == 'q')
	//		{
	//			break;
	//		}
	//	}
	/*************************************************/

	static int l = 0;
	stopPlay = true;
	//std::vector<unsigned char> yuyv;
	yuyv_2.resize(UVC_IMG_WIDTH * UVC_IMG_HEIGHT * 2);   //yuv422都是一个像素2个字节
	int type = 0x00;
	int type_prev = 0x01;
	//ir_video_thread = new std::thread(&CaptureTool::irVideo, this);
	//rgb_video_thread = new std::thread(&CaptureTool::rgbVideo, this);
	//depth_video_thread = new std::thread(&CaptureTool::depthVideo, this);
	QString current_time = "1";
	while (stopPlay) {
		//if (pDlg->b_closeCam)//退出循环
		//	break;

		void* p = &yuyv_2[0];
		/*bool haveFrame= */cameraDs_2.QueryFrame((void*)&yuyv_2[0], UVC_IMG_WIDTH * UVC_IMG_HEIGHT * 2);   //取uvc的原始数据  //这里必须是1280*721*2的长度，因为这才是一帧的数据，如果只需640*400*2，则数据不对。
		//send_rec("./log.txt", "...", "Receive One Frame");
		/*type = yuyv[0];
		if (type == type_prev)
			continue;
		type_prev = yuyv[0];*/																							//memcpy(&all_stream[0], &yuyv[0], UVC_IMG_HEIGHT*UVC_IMG_WIDTH);


		//if (!haveFrame)
		//{
		//	break;
		//}

		////抓取ir图
		//ostringstream  cur;
		//cur << "./aa" << l << ".raw";
		//string dd = cur.str();
		////std::ofstream cc("./aa.raw", std::ios::binary);//app表示每次操作前均定位到文件末尾
		//std::ofstream cc(dd, std::ios::binary);//app表示每次操作前均定位到文件末尾
		//if (cc.fail()) {
		//	cout << "error\n";
		//}
		////cc.write((char*)/*&yuyv[0]*/(&yuyv[0]/* + 640 * 400 * 2*/), UVC_IMG_WIDTH * UVC_IMG_HEIGHT);
		//
		//if (yuyv[0]==0x0a)   //ir
		//{
		//	cc.write((char*)/*&yuyv[0]*/(&yuyv[0]/* + 640 * 400 * 2*/), UVC_IMG_WIDTH * UVC_IMG_HEIGHT);
		//}
		//else    //depth
		//{
		//	cc.write((char*)/*&yuyv[0]*/(&yuyv[0]/* + 640 * 400 * 2*/), UVC_IMG_WIDTH * UVC_IMG_HEIGHT * 2);
		//}
		//
		//cc.close();
		//l++;

		//预览
		//通用把ir和spk一起发，都是0a.然后0-640*360ir,后面是spk,一帧总长度还是640*360*2
		if (yuyv_2[0] == 0x0a)   //ir_stream  raw数据
		{
			//send_rec("./log.txt", "...", "Receive 0xa");
			static int fps = 0;
			//memcpy(&all_stream[0], &yuyv[0], UVC_IMG_HEIGHT*UVC_IMG_WIDTH);   //ir
			//memcpy(&all_stream_2[0], &yuyv[0] + UVC_IMG_HEIGHT * UVC_IMG_WIDTH, UVC_IMG_HEIGHT*UVC_IMG_WIDTH);   //spk

#ifdef IR_SPK_CAPTURE
			ostringstream  cur;
			cur << "./aa" << l << ".raw";
			string dd = cur.str();
			//std::ofstream cc("./aa.raw", std::ios::binary);//app表示每次操作前均定位到文件末尾
			std::ofstream cc(dd, std::ios::binary);//app表示每次操作前均定位到文件末尾
			if (cc.fail()) {
				cout << "error\n";
			}
			cc.write((char*)/*&yuyv[0]*/(/*&all_stream[0]*/&yuyv[0]), UVC_IMG_WIDTH * UVC_IMG_HEIGHT);
			cc.close();

			ostringstream  curs;
			curs << "./bb" << l << ".raw";
			string ee = curs.str();
			std::ofstream ff(ee, std::ios::binary);//app表示每次操作前均定位到文件末尾
			if (ff.fail()) {
				cout << "error\n";
			}
			ff.write((char*)/*&yuyv[0]*/(/*&all_stream_2[0]*/&yuyv[0] + UVC_IMG_WIDTH * UVC_IMG_HEIGHT), UVC_IMG_WIDTH * UVC_IMG_HEIGHT);
			ff.close();
			l++;
#else
			Sleep(50);
			//ir
			Mat ir_src(UVC_IMG_HEIGHT, UVC_IMG_WIDTH, CV_8UC1, /*&all_stream[0]*/&yuyv_2[0]);
			//imshow("ir", ir_src);
			//waitKey(0);
			QImage img_ir = QImage((unsigned char*)ir_src.data, ir_src.cols, ir_src.rows, ir_src.step, QImage::Format_Indexed8);  //ir原图转QImage
			QPixmap pixmap_ir = QPixmap::fromImage(img_ir);
			mainThread_show(widgets.at(4), pixmap_ir);
			//widgets.at(1)->setPixmap(pixmap_ir);
			//widgets.at(1)->show();
			//send_rec("./log.txt", "...", "IR Completed");

			//门禁无散斑
			//Mat spk_src(UVC_IMG_HEIGHT, UVC_IMG_WIDTH, CV_8UC1, /*&all_stream_2[0]*/&yuyv[0] + UVC_IMG_HEIGHT * UVC_IMG_WIDTH);
			////imshow("spk", spk_src);
			////waitKey(0);
			//QImage img_spk = QImage((unsigned char*)spk_src.data, spk_src.cols, spk_src.rows, spk_src.step, QImage::Format_Indexed8);  //ir原图转QImage
			//QPixmap pixmap_spk = QPixmap::fromImage(img_spk);
			//mainThread_show(widgets.at(2), pixmap_spk);
			//widgets.at(2)->setPixmap(pixmap_spk);
			//widgets.at(2)->show();
			//send_rec("./log.txt", "...", "SPK Completed");

			QString timestamp = QString::number(QDateTime::currentMSecsSinceEpoch() / 1000);

			if (current_time.toInt() != timestamp.toInt())
			{
				status->setText("fps:" + QString::number(fps));
				fps = 0;
			}
			current_time = timestamp;
			fps++;
#endif
		}
		//图漾有0b，通用都是0a
		//if(yuyv[0]==0x0b)  //图漾是depth_stream   //   raw数据
		//{
		//	memcpy(&all_stream_2[0], &yuyv[0], UVC_IMG_HEIGHT*UVC_IMG_WIDTH*2);

		//	Mat src_depth(UVC_IMG_HEIGHT, UVC_IMG_WIDTH, CV_16UC1, &all_stream_2[0]);
		//	//imshow("depth", src_depth);
		//	//waitKey(0);
		//	QImage Qtemp = QImage((const unsigned char*)(src_depth.data), src_depth.cols, src_depth.rows, src_depth.step, QImage::Format_Grayscale16);
		//	widgets.at(1)->setPixmap(QPixmap::fromImage(Qtemp));
		//	widgets.at(1)->resize(Qtemp.size());
		//	widgets.at(1)->show();
		//}

		if (yuyv_2[0] == 0x0c)   //yuv422数据
		{
			//send_rec("./log.txt", "...", "Receive 0xc");
			//memcpy(&all_stream_1[0], &yuyv[0], UVC_IMG_HEIGHT*UVC_IMG_WIDTH * 2);

#ifdef RGB_CAPTURE
			ostringstream  cur;
			cur << "./rgb" << l << ".raw";
			string dd = cur.str();
			//std::ofstream cc("./aa.raw", std::ios::binary);//app表示每次操作前均定位到文件末尾
			std::ofstream cc(dd, std::ios::binary);//app表示每次操作前均定位到文件末尾
			if (cc.fail()) {
				cout << "error\n";
			}
			cc.write((char*)/*&yuyv[0]*/(&yuyv[0]/* + 640 * 400 * 2*/), UVC_IMG_WIDTH * UVC_IMG_HEIGHT * 2);

			cc.close();
			l++;

#ifdef
			for (int i = 0; i < UVC_IMG_HEIGHT; i++) {
				for (int j = 0; j < UVC_IMG_WIDTH; j++) {
					//偶数提v
					if (j % 2 == 0)
					{
						//两种不同转换方式1，有溢出
						//all_stream_1[3 * i * UVC_IMG_WIDTH + 3 * j + 2] = 1.164*(yuyv[2 * i*UVC_IMG_WIDTH + 2 * j] - 16) + 1.596*(yuyv[2 * i*UVC_IMG_WIDTH + 2 * j + 3] - 128); //1.164*(Y’-16) + 1.596*(Cr'-128)
						//all_stream_1[3 * i * UVC_IMG_WIDTH + 3 * j + 1] = 1.164*(yuyv[2 * i*UVC_IMG_WIDTH + 2 * j] - 16) - 0.813*(yuyv[2 * i*UVC_IMG_WIDTH + 2 * j + 3] - 128) - 0.391* (yuyv[2 * i*UVC_IMG_WIDTH + 2 * j + 1] - 128);
						//all_stream_1[3 * i * UVC_IMG_WIDTH + 3 * j + 0] = 1.164*(yuyv[2 * i*UVC_IMG_WIDTH + 2 * j] - 16) + 2.018* (yuyv[2 * i*UVC_IMG_WIDTH + 2 * j + 1] - 128);

						//两种不同转换方式2，无溢出，完美显示，RGB格式
						all_stream_1[3 * i * UVC_IMG_WIDTH + 3 * j + 0] = (yuyv[2 * i*UVC_IMG_WIDTH + 2 * j]) + 1.4075*(yuyv[2 * i*UVC_IMG_WIDTH + 2 * j + 3] - 128);  //R
						all_stream_1[3 * i * UVC_IMG_WIDTH + 3 * j + 1] = (yuyv[2 * i*UVC_IMG_WIDTH + 2 * j]) - 0.7169*(yuyv[2 * i*UVC_IMG_WIDTH + 2 * j + 3] - 128) - 0.3455* (yuyv[2 * i*UVC_IMG_WIDTH + 2 * j + 1] - 128);   //G
						all_stream_1[3 * i * UVC_IMG_WIDTH + 3 * j + 2] = (yuyv[2 * i*UVC_IMG_WIDTH + 2 * j]) + 1.779* (yuyv[2 * i*UVC_IMG_WIDTH + 2 * j + 1] - 128);  //B
					}
					//奇数提u
					else
					{
						all_stream_1[3 * i * UVC_IMG_WIDTH + 3 * j + 0] = (yuyv[2 * i*UVC_IMG_WIDTH + 2 * j]) + 1.4075*(yuyv[2 * i*UVC_IMG_WIDTH + 2 * j + 1] - 128);   //R
						all_stream_1[3 * i * UVC_IMG_WIDTH + 3 * j + 1] = (yuyv[2 * i*UVC_IMG_WIDTH + 2 * j]) - 0.7169*(yuyv[2 * i*UVC_IMG_WIDTH + 2 * j + 1] - 128) - 0.3455* (yuyv[2 * i*UVC_IMG_WIDTH + 2 * j - 1] - 128);   //G
						all_stream_1[3 * i * UVC_IMG_WIDTH + 3 * j + 2] = (yuyv[2 * i*UVC_IMG_WIDTH + 2 * j]) + 1.779* (yuyv[2 * i*UVC_IMG_WIDTH + 2 * j - 1] - 128);   //B
					}
				}
			}
			Mat srcCopy(UVC_IMG_WIDTH, UVC_IMG_HEIGHT/*cv::Size(400, 640)*/, CV_8UC3, &all_stream_1[0]);
			//cvtColor(srcCopy, srcCopy, COLOR_YUV2RGB_UYNV);
			transpose(srcCopy, srcCopy);
			flip(srcCopy, srcCopy, 0);//flip(srcCopy, srcCopy, 1);  //rotate 270 
			//cvtColor(srcCopy, srcCopy, CV_BGR2RGB);//输入源格式转换（转换后色调正常）   BGR格式的话颜色不对，需转换成RGB

			//裁剪
			if (isCut)
				srcCopy = srcCopy(Range(320, 960), Range(180, 540));   //裁成360*640


			QImage img = QImage((unsigned char*)srcCopy.data, srcCopy.cols, srcCopy.rows, srcCopy.step, QImage::Format_RGB888);

			//原始分辨率显示
			//widgets.at(0)->setPixmap(QPixmap::fromImage(img));
			//widgets.at(0)->show();


			////按照360，640等比例缩放，以180,320为窗口比例进行等比缩放
			QPixmap pixmap = QPixmap::fromImage(img);
			QPixmap fitpixmap = pixmap.scaled(/*UVC_IMG_WIDTH*//*180*/360, /*UVC_IMG_HEIGHT*//*320*/640, Qt::KeepAspectRatio, Qt::SmoothTransformation); //按比例缩放  
			//widgets.at(0)->setPixmap(fitpixmap);
			//widgets.at(0)->show();
			mainThread_show(widgets.at(0), fitpixmap);
#endif // !

#else
			Mat yuv_img(UVC_IMG_WIDTH, UVC_IMG_HEIGHT, CV_8UC2, &yuyv_2[0]);
			Mat rgb;
			cvtColor(yuv_img, rgb, CV_YUV2RGB_YUY2); //CV_YUV2BGR_YUY2
			transpose(rgb, rgb);
			flip(rgb, rgb, 0);//flip(srcCopy, srcCopy, 1);  //rotate 270 
			QImage img = QImage((unsigned char*)rgb.data, rgb.cols, rgb.rows, rgb.step, QImage::Format_RGB888);
			QPixmap pixmap = QPixmap::fromImage(img);
			QPixmap fitpixmap = pixmap.scaled(/*UVC_IMG_WIDTH*//*180*/360 * multiple, /*UVC_IMG_HEIGHT*//*320*/640 * multiple, Qt::KeepAspectRatio, Qt::SmoothTransformation); //按比例缩放  
			mainThread_show(widgets.at(3), fitpixmap);
			//imshow("rgb", rgb);
			//waitKey(0);
#endif // DEBUG
		}


		//////由于IR是8bit单通道的yuv422，只需要在SPK的基础上，后移640*400*2长度就好了
		//for (int i = 0; i < UVC_IMG_HEIGHT; i++) {
		//	for (int j = 0; j < UVC_IMG_WIDTH; j++) {
		//		all_stream[3 * i * UVC_IMG_WIDTH + 3 * j + 0] = yuyv[2 * i*UVC_IMG_WIDTH + 2 * j + 640 * 400 * 2];
		//		all_stream[3 * i * UVC_IMG_WIDTH + 3 * j + 1] = yuyv[2 * i*UVC_IMG_WIDTH + 2 * j + 640 * 400 * 2];
		//		all_stream[3 * i * UVC_IMG_WIDTH + 3 * j + 2] = yuyv[2 * i*UVC_IMG_WIDTH + 2 * j + 640 * 400 * 2];
		//	}
		//}

		//for (int i = 0; i < UVC_IMG_HEIGHT; i++) {
		//	for (int j = 0; j < UVC_IMG_WIDTH; j++) {
		//		all_stream_1[3 * i * UVC_IMG_WIDTH + 3 * j + 0] = yuyv[2 * i*UVC_IMG_WIDTH + 2 * j /*+ 640 * 400 * 2*/];
		//		all_stream_1[3 * i * UVC_IMG_WIDTH + 3 * j + 1] = yuyv[2 * i*UVC_IMG_WIDTH + 2 * j /*+ 640 * 400 * 2*/];
		//		all_stream_1[3 * i * UVC_IMG_WIDTH + 3 * j + 2] = yuyv[2 * i*UVC_IMG_WIDTH + 2 * j /*+ 640 * 400 * 2*/];
		//	}
		//}


		////cv::Mat img1(cv::Size(400, /*360*/640), CV_16UC1, resp);
		////做了图像90°旋转，将ir_stream旋转90°到srcCopy
		//Mat srcCopy(UVC_IMG_HEIGHT, UVC_IMG_WIDTH/*cv::Size(400, 640)*/, CV_8UC3, &all_stream[0]);
		////cvtColor(srcCopy, srcCopy, COLOR_YUV2RGB_UYNV);
		////imshow("show", srcCopy);
		////waitKey(0);
		//transpose(srcCopy, srcCopy);
		//flip(srcCopy, srcCopy, 0);//flip(srcCopy, srcCopy, 1);  //rotate 270 


		////cvtColor(srcCopy, srcCopy, CV_BGR2RGB);//输入源格式转换（转换后色调正常）
		//QImage img = QImage((unsigned char*)srcCopy.data, srcCopy.cols, srcCopy.rows, srcCopy.step, QImage::Format_RGB888);

		////窗口大小可自适应不同分辨率，
		//QPixmap pixmap = QPixmap::fromImage(img);
		////QPixmap fitpixmap = pixmap.scaled(UVC_IMG_WIDTH, UVC_IMG_HEIGHT, Qt::KeepAspectRatio, Qt::SmoothTransformation); //按比例缩放  
		//widgets.at(0)->setPixmap(pixmap);

		////ui.label->resize(img.size());
		//widgets.at(0)->show();



		//Mat srcCopy_1(UVC_IMG_HEIGHT, UVC_IMG_WIDTH/*cv::Size(400, 640)*/, CV_8UC3, &all_stream_1[0]);
		////cvtColor(srcCopy, srcCopy, COLOR_YUV2RGB_UYNV);
		////imshow("show", srcCopy);
		////waitKey(0);
		//transpose(srcCopy_1, srcCopy_1);
		//flip(srcCopy_1, srcCopy_1, 0);//flip(srcCopy, srcCopy, 1);  //rotate 270 


		////cvtColor(srcCopy, srcCopy, CV_BGR2RGB);//输入源格式转换（转换后色调正常）
		//QImage img_1 = QImage((unsigned char*)srcCopy_1.data, srcCopy_1.cols, srcCopy_1.rows, srcCopy_1.step, QImage::Format_RGB888);

		////窗口大小可自适应不同分辨率，
		//QPixmap pixmap_1 = QPixmap::fromImage(img_1);
		////QPixmap fitpixmap = pixmap.scaled(UVC_IMG_WIDTH, UVC_IMG_HEIGHT, Qt::KeepAspectRatio, Qt::SmoothTransformation); //按比例缩放  
		//widgets.at(1)->setPixmap(pixmap_1);

		////ui.label->resize(img.size());
		//widgets.at(1)->show();

	}


	//while (true)
	//{
	//	//void* p = &yuyv[0];
	//	int i = 0;
	//	for (i; i < 3; i++)
	//	{
	//		if (i == 0)
	//		{
	//			bool haveFrame = cameraDs.QueryFrame((void*)&yuyv[0], UVC_IMG_WIDTH * UVC_IMG_HEIGHT);    //ir原图是640*400*1
	//			con_ir.notify_one();
	//		}
	//		else if (i == 1)
	//		{
	//			cameraDs.QueryFrame((void *)&yuyv[0], UVC_IMG_WIDTH*UVC_IMG_HEIGHT);   //spk
	//			
	//		}
	//		else
	//		{
	//			cameraDs.QueryFrame((void *)&yuyv[0], UVC_IMG_WIDTH*UVC_IMG_HEIGHT * 2);   //depth
	//			con_depth.notify_one();
	//		}
	//	}
	//}
}

//发的原图，不是yuv422不需要转换成rgb格式
void CaptureTool::irVideo()
{
	stopPlay = true;
	std::unique_lock<std::mutex> lock_ir(loc);
	connect(this, SIGNAL(ui_show(int, QPixmap)), /*widgets.at(0)*/this, SLOT(updateUI(int, QPixmap)));
	//Sleep(3000);
	while (stopPlay)
	{
		////发的原图，不是yuv422不需要转换成rgb格式
		//for (int i = 0; i < UVC_IMG_HEIGHT; i++) {
		//	for (int j = 0; j < UVC_IMG_WIDTH; j++) {
		//		all_stream[3 * i * UVC_IMG_WIDTH + 3 * j + 0] = yuyv[2 * i*UVC_IMG_WIDTH + 2 * j + 640 * 400 * 2];
		//		all_stream[3 * i * UVC_IMG_WIDTH + 3 * j + 1] = yuyv[2 * i*UVC_IMG_WIDTH + 2 * j + 640 * 400 * 2];
		//		all_stream[3 * i * UVC_IMG_WIDTH + 3 * j + 2] = yuyv[2 * i*UVC_IMG_WIDTH + 2 * j + 640 * 400 * 2];
		//	}
		//}

		//Mat srcCopy(UVC_IMG_HEIGHT, UVC_IMG_WIDTH/*cv::Size(400, 640)*/, CV_8UC3, &all_stream[0]);
		////cvtColor(srcCopy, srcCopy, COLOR_YUV2RGB_UYNV);
		////imshow("show", srcCopy);
		////waitKey(0);
		//transpose(srcCopy, srcCopy);
		//flip(srcCopy, srcCopy, 0);//flip(srcCopy, srcCopy, 1);  //rotate 270 


		////cvtColor(srcCopy, srcCopy, CV_BGR2RGB);//输入源格式转换（转换后色调正常）
		//QImage img = QImage((unsigned char*)srcCopy.data, srcCopy.cols, srcCopy.rows, srcCopy.step, QImage::Format_RGB888);

		////窗口大小可自适应不同分辨率，
		//QPixmap pixmap = QPixmap::fromImage(img);
		////QPixmap fitpixmap = pixmap.scaled(UVC_IMG_WIDTH, UVC_IMG_HEIGHT, Qt::KeepAspectRatio, Qt::SmoothTransformation); //按比例缩放  
		//widgets.at(0)->setPixmap(pixmap);

		////ui.label->resize(img.size());
		//widgets.at(0)->show();

		//std::unique_lock<std::mutex> lock_ir(loc);
		//con_ir.wait(lock_ir);
		
		Mat ir_src(UVC_IMG_HEIGHT, UVC_IMG_WIDTH, CV_8UC1, &all_stream[0]);
		//imshow("ir", ir_src);
		//waitKey(0);
		QImage img = QImage((unsigned char*)ir_src.data, ir_src.cols, ir_src.rows, ir_src.step,QImage::Format_Indexed8);  //ir原图转QImage
		QPixmap pixmap = QPixmap::fromImage(img);
		//widgets.at(0)->setPixmap(pixmap);
		//widgets.at(0)->show();

		//emit ab();
		emit ui_show(0, pixmap);

		//widgets.at(0)->update();
		//widgets.at(0)->repaint();
		//QApplication::processEvents();
		
	}
	
}


void CaptureTool::updateUI(int screen_index,QPixmap pixmap)
{
	widgets.at(screen_index)->setPixmap(pixmap);
	widgets.at(screen_index)->show();
}

//rgb
void CaptureTool::rgbVideo()
{
	stopPlay = true;
	while (stopPlay)
	{
		for (int i = 0; i < UVC_IMG_HEIGHT; i++) {
			for (int j = 0; j < UVC_IMG_WIDTH; j++) {
				all_stream_1[3 * i * UVC_IMG_WIDTH + 3 * j + 0] = yuyv[2 * i*UVC_IMG_WIDTH + 2 * j /*+ 640 * 400 * 2*/];
				all_stream_1[3 * i * UVC_IMG_WIDTH + 3 * j + 1] = yuyv[2 * i*UVC_IMG_WIDTH + 2 * j /*+ 640 * 400 * 2*/];
				all_stream_1[3 * i * UVC_IMG_WIDTH + 3 * j + 2] = yuyv[2 * i*UVC_IMG_WIDTH + 2 * j /*+ 640 * 400 * 2*/];
			}
		}

		Mat srcCopy(UVC_IMG_HEIGHT, UVC_IMG_WIDTH/*cv::Size(400, 640)*/, CV_8UC3, &all_stream[0]);
		//cvtColor(srcCopy, srcCopy, COLOR_YUV2RGB_UYNV);
		//imshow("show", srcCopy);
		//waitKey(0);
		transpose(srcCopy, srcCopy);
		flip(srcCopy, srcCopy, 0);//flip(srcCopy, srcCopy, 1);  //rotate 270 


		//cvtColor(srcCopy, srcCopy, CV_BGR2RGB);//输入源格式转换（转换后色调正常）
		QImage img = QImage((unsigned char*)srcCopy.data, srcCopy.cols, srcCopy.rows, srcCopy.step, QImage::Format_RGB888);

		//窗口大小可自适应不同分辨率，
		QPixmap pixmap = QPixmap::fromImage(img);
		//QPixmap fitpixmap = pixmap.scaled(UVC_IMG_WIDTH, UVC_IMG_HEIGHT, Qt::KeepAspectRatio, Qt::SmoothTransformation); //按比例缩放  
		widgets.at(1)->setPixmap(pixmap);

		//ui.label->resize(img.size());
		widgets.at(1)->show();
	}
	
}

void CaptureTool::depthVideo()
{
	stopPlay = true;
	//unique_lock<std::mutex> lock_dep;
	//Sleep(3000);
	while (stopPlay)
	{
		//con_depth.wait(lock_dep);
		//Sleep(3000);
		Mat src_depth(UVC_IMG_HEIGHT, UVC_IMG_WIDTH, CV_16UC1, &all_stream_2[0]);
		//imshow("depth", src_depth);
		//waitKey(0);
		QImage Qtemp = QImage((const unsigned char*)(src_depth.data), src_depth.cols, src_depth.rows, src_depth.step, QImage::Format_Grayscale16);
		widgets.at(1)->setPixmap(QPixmap::fromImage(Qtemp));
		widgets.at(1)->resize(Qtemp.size());
		widgets.at(1)->show();
	}
}

//void CaptureTool::test()
//{
//	//做了图像90°旋转，将ir_stream旋转90°到srcCopy
//	Mat srcCopy(UVC_IMG_HEIGHT, UVC_IMG_WIDTH/*cv::Size(400, 640)*/, CV_8UC3, &all_stream[0]);
//	//cvtColor(srcCopy, srcCopy, COLOR_YUV2RGB_UYNV);
//	//imshow("show", srcCopy);
//	//waitKey(0);
//	transpose(srcCopy, srcCopy);
//	flip(srcCopy, srcCopy, 0);//flip(srcCopy, srcCopy, 1);  //rotate 270 
//
//
//	//cvtColor(srcCopy, srcCopy, CV_BGR2RGB);//输入源格式转换（转换后色调正常）
//	QImage img = QImage((unsigned char*)srcCopy.data, srcCopy.cols, srcCopy.rows, srcCopy.step, QImage::Format_RGB888);
//
//	//窗口大小可自适应不同分辨率，
//	QPixmap pixmap = QPixmap::fromImage(img);
//	//QPixmap fitpixmap = pixmap.scaled(UVC_IMG_WIDTH, UVC_IMG_HEIGHT, Qt::KeepAspectRatio, Qt::SmoothTransformation); //按比例缩放  
//	widgets.at(0)->setPixmap(pixmap);
//
//	//ui.label->resize(img.size());
//	widgets.at(0)->show();
//}

void CaptureTool::biggerVideo()
{
	multiple += 1;
}

void CaptureTool::smallerVideo()
{
	if(multiple > 1)
		multiple -= 1;
}

void CaptureTool::show_rgb1_video()
{
	stopPlay = true;
	cap_rgb1.set(CAP_PROP_FRAME_WIDTH, 1280);
	cap_rgb1.set(CAP_PROP_FRAME_HEIGHT, 720);
	while (stopPlay)
	{
		cap_rgb1 >> rgb_stream;
		cvtColor(rgb_stream, rgb_stream, CV_BGR2RGB);//输入源格式转换（转换后色调正常）
		transpose(rgb_stream, rgb_stream);
		flip(rgb_stream, rgb_stream, 0);//flip(srcCopy, srcCopy, 1);  //rotate 270 
		//if (isCut)
		//	rgb_stream = rgb_stream(Range(320, 960), Range(180, 540));   //裁成360*640
		QImage img = QImage((unsigned char*)rgb_stream.data, rgb_stream.cols, rgb_stream.rows, rgb_stream.step, QImage::Format_RGB888);
		//widgets.at(0)->setPixmap(QPixmap::fromImage(img));
		//widgets.at(0)->show();
		//等比例缩放
		QPixmap pixmap = QPixmap::fromImage(img);
		QPixmap fitpixmap = pixmap.scaled(/*UVC_IMG_WIDTH*//*180*/180 * multiple, /*UVC_IMG_HEIGHT*//*320*/320 * multiple, Qt::KeepAspectRatio, Qt::SmoothTransformation); //按比例缩放  
		widgets.at(0)->setPixmap(fitpixmap);
		widgets.at(0)->show();
	}
	cap_rgb1.release();
}
//IR流显示
void CaptureTool::show_ir1_video()
{
	stopPlay = true;
	cap_ir1.set(CAP_PROP_FRAME_WIDTH, 1280);
	cap_ir1.set(CAP_PROP_FRAME_HEIGHT, 720);
	//固定的窗口，图像分辨率自适应缩放
	int width = /*640*/widgets.at(0)->width();
	int height = /*360*/widgets.at(0)->height();
	

	while (stopPlay)
	{
		cap_ir1 >> ir_stream; 

		//做了图像90°旋转，将ir_stream旋转90°到srcCopy
		Mat srcCopy = Mat(ir_stream.rows, ir_stream.cols, ir_stream.depth());
		transpose(ir_stream, srcCopy);
		flip(srcCopy, srcCopy, 0);//flip(srcCopy, srcCopy, 1);  //rotate 270 


		cvtColor(srcCopy, srcCopy, CV_BGR2RGB);//输入源格式转换（转换后色调正常）
		QImage img = QImage((unsigned char*)srcCopy.data, srcCopy.cols, srcCopy.rows, srcCopy.step, QImage::Format_RGB888);

		//窗口大小可自适应不同分辨率，
		//int width = /*640*/widgets.at(0)->width();
		//int height = /*360*/widgets.at(0)->height();
		QPixmap pixmap = QPixmap::fromImage(img);
		QPixmap fitpixmap = pixmap.scaled(width, height, Qt::KeepAspectRatio, Qt::SmoothTransformation); //按比例缩放  
		widgets.at(0)->setPixmap(fitpixmap);
		
		widgets.at(0)->show();
	}
	cap_ir1.release();
}
//UVC显示深度
void CaptureTool::show_depth1_video()
{
	stopPlay = true;
	while (stopPlay)
	{
		cap_depth1 >> depth_stream;
		cvtColor(depth_stream, depth_stream, CV_BGR2RGB);//输入源格式转换（转换后色调正常）
		QImage img = QImage((unsigned char*)depth_stream.data, depth_stream.cols, depth_stream.rows, depth_stream.step, QImage::Format_RGB888);
		widgets.at(2)->setPixmap(QPixmap::fromImage(img));

		widgets.at(2)->show();
	}
	cap_depth1.release();
}
//SPK流显示
void CaptureTool::show_spk1_video()
{
	stopPlay = true;
	cap_spk1.set(CAP_PROP_FRAME_WIDTH, 1280);
	cap_spk1.set(CAP_PROP_FRAME_HEIGHT, 721);
	//固定的窗口，图像分辨率自适应缩放
	int width = widgets.at(0)->width();
	int height = widgets.at(0)->height();
	while (stopPlay)
	{
		cap_spk1 >> spk_stream;

		//做了图像90°旋转，将ir_stream旋转90°到srcCopy
		Mat srcCopy = Mat(spk_stream.rows, spk_stream.cols, spk_stream.depth());
		transpose(spk_stream, srcCopy);
		flip(srcCopy, srcCopy, 0);//flip(srcCopy, srcCopy, 1);  //rotate 270 


		cvtColor(srcCopy, srcCopy, CV_BGR2RGB);//输入源格式转换（转换后色调正常）
		QImage img = QImage((unsigned char*)srcCopy.data, srcCopy.cols, srcCopy.rows, srcCopy.step, QImage::Format_RGB888);

		//窗口大小可自适应不同分辨率，
		QPixmap pixmap = QPixmap::fromImage(img);
		QPixmap fitpixmap = pixmap.scaled(width, height, Qt::KeepAspectRatio, Qt::SmoothTransformation); //按比例缩放  
		widgets.at(0)->setPixmap(fitpixmap);

		//ui.label->resize(img.size());
		widgets.at(0)->show();
	}
	cap_spk1.release();
}

static uint32_t histBin[32] = { 0 };
void CaptureTool::runHist(uint16_t* src, int h, int w, int step)
{
	for (int i = 0; i < 32; i++)
	{
		histBin[i] = 0;
	}

	for (int y = 0; y < h; y += step)
	{
		for (int x = 0; x < w; x += step)
		{
			int h_idx = src[y * w + x] >> 3;
			histBin[h_idx]++;
		}
	}
}

void CaptureTool::scaleGray(uint16_t* gray, int num, int min, int max)
{

	float scale = 230.0f / (max - min);
	for (int i = 0; i < num; i++)
	{
		gray[i] = (ushort)(gray[i] <= min ? min : gray[i]);
		gray[i] = (ushort)(gray[i] >= max ? max : gray[i]);
		gray[i] = (ushort)(gray[i] - min);
		gray[i] = (ushort)(gray[i] * scale);
	}
}

void CaptureTool::enhanceDepth(uint16_t* src, uint16_t* dst, int h, int w, int minDist, int maxDist, bool invert_white)
{
	float GRAY_MAX = 230.0f;
	int num = h * w;
	int inv = (int)(invert_white ? GRAY_MAX : 0);

	int real_min = 32768;
	int real_max = 0;

	for (int i = 0; i < num; i++)
	{
		real_min = src[i] < real_min ? src[i] : real_min;
		real_max = src[i] > real_max ? src[i] : real_max;
	}

	real_max = maxDist < real_max ? maxDist : real_max;
	real_min = minDist > real_min ? minDist : real_min;
	float scale = GRAY_MAX / (real_max - real_min);

	for (int i = 0; i < num; i++)
	{
		int data = src[i];
		data = data > real_max ? real_max : data;
		data = data < real_min ? real_min : data;
		data = data - real_min;

		dst[i] = (char)(data * scale);
		dst[i] -= (char)inv;
	}
}
//#ifdef DEBUG
//void CaptureTool::readBufferTo16RawStream(char* buffer)
//{
//	//Buffer.BlockCopy(buffer, 0, pix16, 0, buffer.Length);
//	memcpy(pix16, buffer, /*512 * 900*/640 * 400 * 2);
//
//	//getDepthImg(pix16, newBuffer, 360, 640, 50, 900, 479.870079f, -40);  //数据源是视差图的话，这个函数将视差数据转为深度数据。
//	///////////////////////////////////////////普通的深度把这个注释
//	for (int i = 0; i < 640 * /*360*/400; i++)
//	{
//		newBuffer[i] = (uint16_t)(pix16[i] < 0 ? 0 : pix16[i]);
//		/* 深度图除16 */
//		newBuffer[i] = (uint16_t)(newBuffer[i] >> 4);
//	}
//	/////////////////////////////////////////
//	//if (!flag)              ///把这个取消注释就可以了
//	//{
//	//for (int i = 0; i < 640 * 360; i++)
//	//{
//	//    newBuffer[i] = (ushort)(newBuffer[i] < 0 ? 0 : newBuffer[i]);
//	//    /* 深度图除16 */
//	//    newBuffer[i] = (ushort)(newBuffer[i] >> 4);
//	//}
//	enhanceDepth(newBuffer, dst, /*360*/400, 640, 300, 900, false);
//
//	runHist(dst, /*360*/400, 640, 1);
//	float total = /*360*/400 * 640;
//	int idx = -1;
//	for (int j = 1; j < 32 - 16; j++)
//	{
//		uint sum = 0;
//		for (int i = j; i < j + 16; i++)
//		{
//			sum += histBin[j];
//		}
//		if ((float)sum / total > 0.5)
//		{
//			idx = j; break;
//		}
//	}
//
//	if (idx != -1)
//	{
//		int min = idx * 8;
//		int max = (idx + 16) * 8 - 1;
//		scaleGray(dst, /*360*/400 * 640, min, max);
//	}
//	for (int i = 0; i < 640 * /*360*/400; i++)
//	{
//		//dst[i] = (ushort)((230 - dst[i])*0.75);
//		dst[i] *= 256;
//	}
//
//
//	//Mat gray1_mat(640, 360, CV_16UC1, dst);
//	cv::Mat img1(cv::Size(640, /*360*/400), CV_16UC1, dst);
//	//Mat img2(cv::Size(640, 360), CV_16UC3, Scalar(0));
//	//cvtColor(img1, img2, CV_BayerGB2BGR);
//	//imshow("img", img2);
//	//waitKey(0);
//
//
//	for (int i = 0; i < widgets.length(); i++)
//	{
//		widgets.at(i)->setFixedSize(QSize(640, /*360*/400));
//	}
//
//
//	//深度视频流显示
//	QImage Qtemp = QImage((const unsigned char*)(img1.data), img1.cols, img1.rows, img1.step, QImage::Format_Grayscale16);
//	widgets.at(0)->setPixmap(QPixmap::fromImage(Qtemp));
//	widgets.at(0)->resize(Qtemp.size());
//	widgets.at(0)->show();
//
//
//}
//#endif // DEBUG
//bulk显示深度,分辨率400x640x2
void CaptureTool::bulk_depth()
{
	stopPlay = true;
	if (usb_initial() < 0)
	{
		QMessageBox::critical(nullptr, QString::fromLocal8Bit("Error"), QString::fromLocal8Bit("USB Init Error!"), QMessageBox::Ok);
		usb_release();
		return;
	}
	uint8_t writeBuffer[512] = { 0 };
	char resp[/*512 * 900*/640 * 400 * 2] = { 0 };
	writeBuffer[0] = 0x54;
	writeBuffer[1] = 0x53;
	writeBuffer[2] = 0x4d;
	writeBuffer[3] = 0x21;  //通知下位机准备切图指令   
	writeBuffer[12] = 3;  //1是RGB  2是IR  3是深度图
	if (send_packet(writeBuffer, 512) < 0)
	{
		QMessageBox::warning(this, "Error", "USB Send Error!",QMessageBox::Ok);
		usb_release();
		return;

	}
	Sleep(1000);
	while (stopPlay)
	{
		writeBuffer[3] = 0x20;
		send_packet(writeBuffer, 512);
		int ret = usb_read(resp, /*512 * 900*/640 * 400 * 2, 2000);//分辨率由原来的640*360*2改为640*400*2

		//不加算法
		cv::Mat img1(cv::Size(400, /*360*/640), CV_16UC1, resp);
		//深度视频流显示
		QImage Qtemp = QImage((const unsigned char*)(img1.data), img1.cols, img1.rows, img1.step, QImage::Format_Grayscale16);
		widgets.at(0)->setPixmap(QPixmap::fromImage(Qtemp));
		widgets.at(0)->resize(Qtemp.size());
		widgets.at(0)->show();

		//加算法
		//readBufferTo16RawStream(resp);
	}
	usb_release();
}
//Start流播放
void CaptureTool::playAllVideo()
{
	if (rgb1_thread != nullptr)
	{
		stopPlay = false;
		rgb1_thread->join();
		rgb1_thread = nullptr;
	}
	cap_rgb1.release();
	Sleep(1000);

	all_stream.resize(UVC_IMG_HEIGHT*UVC_IMG_WIDTH);  //ir
	all_stream_1.resize(UVC_IMG_HEIGHT*UVC_IMG_WIDTH * 3);   //rgb  yuv
	all_stream_2.resize(UVC_IMG_HEIGHT*UVC_IMG_WIDTH /** 2*/);  //图漾。。depth   //通用。。spk

	bool bret = cameraDs.OpenCamera(0, false, UVC_IMG_HEIGHT, UVC_IMG_WIDTH);    //当没有摄像头时，参数没有0，会报错。
	if (!bret)
	{
		QMessageBox::critical(nullptr, QString::fromLocal8Bit("Error"), QString::fromLocal8Bit("Camera Open Error!"), QMessageBox::Ok);
		//return;
	}
	else 
	{
		all_stream_thread = new std::thread(&CaptureTool::showAllStream, this);
	}


	//新加门禁
	bool bret_2 = cameraDs_2.OpenCamera(1, false, UVC_IMG_HEIGHT, UVC_IMG_WIDTH);    //当没有摄像头时，参数没有0，会报错。
	if (!bret_2)
	{
		QMessageBox::critical(nullptr, QString::fromLocal8Bit("Error"), QString::fromLocal8Bit("Camera Open Error!"), QMessageBox::Ok);
		//return;
	}
	else
	{
		all_stream_thread_2 = new std::thread(&CaptureTool::showAllStream_2, this);
	}
	
	//海康预览
	//startPreview();

}
//开启uvc_rgb线程（yuv422格式才行，raw不行）
void CaptureTool::start_rgb1_video_thread()
{
	if (all_stream_thread != nullptr)
	{
		stopPlay = false;
		all_stream_thread->join();
		all_stream_thread = nullptr;
		cameraDs.CloseCamera();   //关闭direcshow摄像头
	}


	stopPlay = false;
	Sleep(3000);
	cap_rgb1.open(0);
	if (cap_rgb1.isOpened())
		rgb1_thread = new std::thread(&CaptureTool::show_rgb1_video, this);
}

//开启ucv_ir线程（yuv422格式才行，raw不行）
void CaptureTool::start_ir1_video_thread()
{
	stopPlay = false;
	Sleep(3000);
	cap_ir1.open(0);
	if (cap_ir1.isOpened())
		ir1_thread = new std::thread(&CaptureTool::show_ir1_video, this);
}
//开启ucv_spk线程（yuv422格式才行，raw不行）
void CaptureTool::start_spk1_video_thread()
{
	stopPlay = false;
	Sleep(3000);
	cap_spk1.open(0);
	if (cap_spk1.isOpened())
		spk1_thread = new std::thread(&CaptureTool::show_spk1_video, this);
}
//bulk显示深度流（显示的raw图）
void CaptureTool::start_depth1_video_thread()
{
	stopPlay = false;
	Sleep(3000);
	depth1_thread = new std::thread(&CaptureTool::bulk_depth, this);
}
//Stop流播放
void CaptureTool::stop_stream()
{
	stopPlay = false;
	cap_ir1.release();
	cap_spk1.release();
}
//SaveFile
void CaptureTool::showFileDialog()
{
	filePath = new FilePath(this);
	connect(filePath, SIGNAL(send_path(QString)), this, SLOT(get_save_path(QString)));
	//模态窗口
	if (filePath->exec())
	{

	}
	delete filePath;
	filePath = nullptr;
}

void CaptureTool::get_save_path(QString path)
{
	saveFileName = path;
}

//Capture
void CaptureTool::cap_ir_spk_dep()
{
	stopPlay = false;   //抓图前关闭uvc
	Sleep(3000);
	static uint32_t spk_ir_dep_pic_id = 0;
	uint8_t send_buf[BUF_SEND_LEN] = { 0 };
	uint8_t *recv_buf = (uint8_t *)malloc(20 * 1024 * 1024);   //分配1M内存//ir是640*360=225kB
	uint8_t *recv_ir_buf = recv_buf;   //ir1280*800
	uint8_t *recv_spk_buf = recv_buf + BUF_RECV_IR_SPK_DEPTH/*BUF_RECV_GAP_LEN*/;    //spk1280*800
	uint8_t *recv_depth_buf = recv_spk_buf + BUF_RECV_IR_SPK_DEPTH/*BUF_RECV_GAP_LEN*/;   //深度500k  
	if (recv_buf == nullptr)
	{
		QMessageBox::critical(nullptr, QString::fromLocal8Bit("Error"), QString::fromLocal8Bit("Memory malloc failure!"), QMessageBox::Ok);
	}
	if (usb_initial() < 0)
	{
		QMessageBox::critical(nullptr, QString::fromLocal8Bit("Error"), QString::fromLocal8Bit("USB Init error!"), QMessageBox::Ok);						/* usb init */
		return;
	}
	pack_head(CMD_GET_IR_SPK_DEP_1280x800/*CMD_GET_ALL_IMG*/, spk_ir_dep_pic_id, 0, send_buf);
	if (send_packet(send_buf, GET_REQ_LEN(send_buf)) < 0)
	{
		QMessageBox::critical(nullptr, QString::fromLocal8Bit("Error"), QString::fromLocal8Bit("USB Send error!"), QMessageBox::Ok);
		if (recv_buf != nullptr) {
			free(recv_buf);
			recv_buf = nullptr;
		}
		usb_release();
		return;
	}

	if (get_depth_map(spk_ir_dep_pic_id, send_buf, recv_ir_buf) < 0)
	{
		QMessageBox::critical(nullptr, QString::fromLocal8Bit("Error"), QString::fromLocal8Bit("USB Receive error!"), QMessageBox::Ok);
		if (recv_buf != nullptr) {
			free(recv_buf);
			recv_buf = nullptr;
		}
		usb_release();
		return;
	}

	if (get_ir_image(spk_ir_dep_pic_id, send_buf, recv_spk_buf) < 0)
	{
		QMessageBox::critical(nullptr, QString::fromLocal8Bit("Error"), QString::fromLocal8Bit("USB Receive error!"), QMessageBox::Ok);
		if (recv_buf != nullptr) {
			free(recv_buf);
			recv_buf = nullptr;
		}
		usb_release();
		return;
	}

	if (get_rgb_image(spk_ir_dep_pic_id, send_buf, recv_depth_buf) < 0)
	{
		QMessageBox::critical(nullptr, QString::fromLocal8Bit("Error"), QString::fromLocal8Bit("USB Receive error!"), QMessageBox::Ok);
		if (recv_buf != nullptr) {
			free(recv_buf);
			recv_buf = nullptr;
		}
		usb_release();
		return;
	}
	uint32_t offset = sizeof(resp_pack_head_t) + sizeof(pic_payload_t);
	QString irName = saveFileName + "/" + "IR" + QString::number(spk_ir_dep_pic_id) + "_1280x800.raw";
	QFile fileIR(irName);
	if (!fileIR.open(QIODevice::WriteOnly))
	{
		QMessageBox::critical(nullptr, QString::fromLocal8Bit("Error"), QString::fromLocal8Bit("Open File error!"), QMessageBox::Ok);
		if (recv_buf != nullptr) {
			free(recv_buf);
			recv_buf = nullptr;
		}
		usb_release();
		return;
	}
	fileIR.write((const char *)recv_ir_buf + offset, GET_RESP_LEN(recv_ir_buf) - offset);
	fileIR.close();

	
	Mat ir(IR_HEIGHT, IR_WIDTH, CV_8UC1, recv_ir_buf + offset);
	QString irPng = saveFileName + "/" + "IR" + QString::number(spk_ir_dep_pic_id) + ".png";
	imwrite(irPng.toStdString(), ir);
	

	QString spkName = saveFileName + "/" + "SPK" + QString::number(spk_ir_dep_pic_id) + "_1280x800.raw";
	QFile fileSpk(spkName);
	if (!fileSpk.open(QIODevice::WriteOnly))
	{
		QMessageBox::critical(nullptr, QString::fromLocal8Bit("Error"), QString::fromLocal8Bit("Open File error!"), QMessageBox::Ok);
		if (recv_buf != nullptr) {
			free(recv_buf);
			recv_buf = nullptr;
		}
		usb_release();
		return;
	}
	fileSpk.write((const char *)recv_spk_buf + offset, GET_RESP_LEN(recv_spk_buf) - offset);
	fileSpk.close();

	
	
	Mat spk(SPK_HEIGHT, SPK_WIDTH, CV_8UC1, recv_spk_buf + offset);
	QString spkPng = saveFileName + "/" + "SPK" + QString::number(spk_ir_dep_pic_id) + ".png";
	imwrite(spkPng.toStdString(), spk);
	


	QString depName = saveFileName + "/" + "Depth" + QString::number(spk_ir_dep_pic_id) + "_640x400.raw";
	QFile fileDep(depName);
	if (!fileDep.open(QIODevice::WriteOnly))
	{
		QMessageBox::critical(nullptr, QString::fromLocal8Bit("Error"), QString::fromLocal8Bit("Open File error!"), QMessageBox::Ok);
		if (recv_buf != nullptr) {
			free(recv_buf);
			recv_buf = nullptr;
		}
		usb_release();
		return;
	}
	fileDep.write((const char *)recv_depth_buf + offset, GET_RESP_LEN(recv_depth_buf) - offset);
	fileDep.close();

	
	Mat depth(DEPTH_HEIGHT, DEPTH_WIDTH, CV_16UC1, recv_depth_buf + offset);
	QString depthPng = saveFileName + "/" + "Depth" + QString::number(spk_ir_dep_pic_id) + ".png";
	imwrite(depthPng.toStdString(), depth);
	

	spk_ir_dep_pic_id++;
	QMessageBox::information(nullptr, QString::fromLocal8Bit("Sucessful"), QString::fromLocal8Bit("Completed！"), QMessageBox::Ok);
	if (recv_buf != nullptr) {
		free(recv_buf);
		recv_buf = nullptr;
	}
	usb_release();
}


void CaptureTool::open_capture_set_form()
{
	//CaptureSet *capset = new CaptureSet(this);
	connect(capset, SIGNAL(shot_mode(bool, int, int)), this, SLOT(shot_set(bool, int, int)));
	//connect(capset, SIGNAL(delay_time(int)), this, SLOT(delay_time(int)));
	if (capset->exec())   //模态窗口
	{

	}

}

void CaptureTool::shot_set(bool circle_shoot, int delay_time,int shoot_times)
{
	isCircleShoot = circle_shoot;
	delay_time_to_shoot = delay_time;
	shot_times = shoot_times - 1;
	record_times = shoot_times - 1;
}

void CaptureTool::cap_rgb_ir_dep()
{
	static uint32_t rgb_ir_dep_pic_id = 0;
	uint8_t send_buf[BUF_SEND_LEN] = { 0 };
	uint8_t *recv_buf = (uint8_t *)malloc(20 * 1024 * 1024);   //分配1M内存//ir是640*360=225kB
	uint8_t *recv_rgb_buf = recv_buf;   //ir1280*800
	uint8_t *recv_ir_buf = recv_buf + BUF_RECV_IR_SPK_DEPTH/*BUF_RECV_GAP_LEN*/;    //spk1280*800
	uint8_t *recv_depth_buf = recv_ir_buf + BUF_RECV_IR_SPK_DEPTH/*BUF_RECV_GAP_LEN*/;   //深度500k  
	if (recv_buf == nullptr)
	{
		QMessageBox::critical(nullptr, QString::fromLocal8Bit("Error"), QString::fromLocal8Bit("Memory malloc failure!"), QMessageBox::Ok);
	}
	if (usb_initial() < 0)
	{
		QMessageBox::critical(nullptr, QString::fromLocal8Bit("Error"), QString::fromLocal8Bit("USB Init error!"), QMessageBox::Ok);						/* usb init */
		return;
	}
	
	do
	{
		if(delay_time_to_shoot)
			Sleep(delay_time_to_shoot * 1000);

		//if (usb_initial() < 0)
		//{
		//	QMessageBox::critical(nullptr, QString::fromLocal8Bit("Error"), QString::fromLocal8Bit("USB Init error!"), QMessageBox::Ok);						/* usb init */
		//	return;
		//}
		pack_head(CMD_GET_ALL_IMG/*CMD_GET_ALL_IMG*/, rgb_ir_dep_pic_id, 0, send_buf);
		if (send_packet(send_buf, GET_REQ_LEN(send_buf)) < 0)
		{
			QMessageBox::critical(nullptr, QString::fromLocal8Bit("Error"), QString::fromLocal8Bit("USB Send error!"), QMessageBox::Ok);
			if (recv_buf != nullptr) {
				free(recv_buf);
				recv_buf = nullptr;
			}
			usb_release();
			return;
		}
		//Sleep(700);
		if (get_depth_map(rgb_ir_dep_pic_id, send_buf, recv_rgb_buf) < 0)
		{
			QMessageBox::critical(nullptr, QString::fromLocal8Bit("Error"), QString::fromLocal8Bit("USB Receive error!"), QMessageBox::Ok);
			if (recv_buf != nullptr) {
				free(recv_buf);
				recv_buf = nullptr;
			}
			usb_release();
			return;
		}

		if (get_ir_image(rgb_ir_dep_pic_id, send_buf, recv_ir_buf) < 0)
		{
			QMessageBox::critical(nullptr, QString::fromLocal8Bit("Error"), QString::fromLocal8Bit("USB Receive error!"), QMessageBox::Ok);
			if (recv_buf != nullptr) {
				free(recv_buf);
				recv_buf = nullptr;
			}
			usb_release();
			return;
		}

		if (get_rgb_image(rgb_ir_dep_pic_id, send_buf, recv_depth_buf) < 0)
		{
			QMessageBox::critical(nullptr, QString::fromLocal8Bit("Error"), QString::fromLocal8Bit("USB Receive error!"), QMessageBox::Ok);
			if (recv_buf != nullptr) {
				free(recv_buf);
				recv_buf = nullptr;
			}
			usb_release();
			return;
		}
		uint32_t offset = sizeof(resp_pack_head_t) + sizeof(pic_payload_t);
		QString rgbName = saveFileName + "/" + "Depth" + QString::number(rgb_ir_dep_pic_id) + "_360x640.raw";
		QFile fileRGB(rgbName);    //深度与rgb换一下位置
		if (!fileRGB.open(QIODevice::WriteOnly))
		{
			QMessageBox::critical(nullptr, QString::fromLocal8Bit("Error"), QString::fromLocal8Bit("Open File error!"), QMessageBox::Ok);
			if (recv_buf != nullptr) {
				free(recv_buf);
				recv_buf = nullptr;
			}
			usb_release();
			return;
		}
		fileRGB.write((const char *)recv_rgb_buf + offset, GET_RESP_LEN(recv_rgb_buf) - offset);
		fileRGB.close();
		//竖图
		//Mat rgb(640, 360, CV_8UC4, recv_rgb_buf + offset);
		//QString rgbPng = saveFileName + "/" + "RGB" + QString::number(rgb_ir_dep_pic_id) + ".png";
		//imwrite(rgbPng.toStdString(), rgb);

		QString irName = saveFileName + "/" + "IR" + QString::number(rgb_ir_dep_pic_id) + "_360x640.raw";
		QFile fileIR(irName);
		if (!fileIR.open(QIODevice::WriteOnly))
		{
			QMessageBox::critical(nullptr, QString::fromLocal8Bit("Error"), QString::fromLocal8Bit("Open File error!"), QMessageBox::Ok);
			if (recv_buf != nullptr) {
				free(recv_buf);
				recv_buf = nullptr;
			}
			usb_release();
			return;
		}
		fileIR.write((const char *)recv_ir_buf + offset, GET_RESP_LEN(recv_ir_buf) - offset);
		fileIR.close();


		//竖图
		//Mat ir(640, 360, CV_8UC1, recv_ir_buf + offset);
		//QString irPng = saveFileName + "/" + "IR" + QString::number(rgb_ir_dep_pic_id) + ".png";
		//imwrite(irPng.toStdString(), ir);



		QString depName = saveFileName + "/" + "RGB" + QString::number(rgb_ir_dep_pic_id) + "_360x640.raw";
		QFile fileDep(depName);//深度与rgb换一下位置
		if (!fileDep.open(QIODevice::WriteOnly))
		{
			QMessageBox::critical(nullptr, QString::fromLocal8Bit("Error"), QString::fromLocal8Bit("Open File error!"), QMessageBox::Ok);
			if (recv_buf != nullptr) {
				free(recv_buf);
				recv_buf = nullptr;
			}
			usb_release();
			return;
		}
		fileDep.write((const char *)recv_depth_buf + offset, GET_RESP_LEN(recv_depth_buf) - offset);
		fileDep.close();

		//竖图
		//Mat depth(640, 360, CV_16UC1, recv_depth_buf + offset);
		//QString depthPng = saveFileName + "/" + "Depth" + QString::number(rgb_ir_dep_pic_id) + ".png";
		//imwrite(depthPng.toStdString(), depth);

		rgb_ir_dep_pic_id++;

		ui.statusBar->setStatusTip("Completed pictures:" + rgb_ir_dep_pic_id);

		//QMessageBox::information(nullptr, QString::fromLocal8Bit("Sucessful"), QString::fromLocal8Bit("Completed！"), QMessageBox::Ok);
		//if (recv_buf != nullptr) {
		//	free(recv_buf);
		//	recv_buf = nullptr;
		//}
		//usb_release();
	}while (isCircleShoot && shot_times--);

	shot_times = record_times;
	
	QMessageBox::information(nullptr, QString::fromLocal8Bit("Sucessful"), QString::fromLocal8Bit("Completed！"), QMessageBox::Ok);
	if (recv_buf != nullptr) {
		free(recv_buf);
		recv_buf = nullptr;
	}
	usb_release();
}

void CaptureTool::cap_rgb_ir_spk()
{
	static uint32_t rgb_ir_dep_pic_id = 0;
	do
	{
		if (delay_time_to_shoot)
			Sleep(delay_time_to_shoot * 1000);
		
		//rgb
		if (yuyv[0] == 0xc)  
		{
			QString rgbName = saveFileName + "/" + "RGB" + QString::number(rgb_ir_dep_pic_id) + "_640x360.raw";
			QFile fileRGB(rgbName);    
			if (!fileRGB.open(QIODevice::WriteOnly))
			{
				QMessageBox::critical(nullptr, QString::fromLocal8Bit("Error"), QString::fromLocal8Bit("Open File error!"), QMessageBox::Ok);
				return;
			}
			fileRGB.write((const char *)&yuyv[0], UVC_IMG_WIDTH*UVC_IMG_HEIGHT * 2);  //RGB
			fileRGB.close();
			//竖图
			//Mat rgb(640, 360, CV_8UC4, recv_rgb_buf + offset);
			//QString rgbPng = saveFileName + "/" + "RGB" + QString::number(rgb_ir_dep_pic_id) + ".png";
			//imwrite(rgbPng.toStdString(), rgb);
		}
		//ir&spk
		if (yuyv[0] == 0xa)
		{
			QString irName = saveFileName + "/" + "IR" + QString::number(rgb_ir_dep_pic_id) + "_360x640.raw";
			QFile fileIR(irName);
			if (!fileIR.open(QIODevice::WriteOnly))
			{
				QMessageBox::critical(nullptr, QString::fromLocal8Bit("Error"), QString::fromLocal8Bit("Open File error!"), QMessageBox::Ok);
				return;
			}
			fileIR.write((const char *)&yuyv[0], UVC_IMG_WIDTH*UVC_IMG_HEIGHT);
			fileIR.close();


			//竖图
			//Mat ir(640, 360, CV_8UC1, recv_ir_buf + offset);
			//QString irPng = saveFileName + "/" + "IR" + QString::number(rgb_ir_dep_pic_id) + ".png";
			//imwrite(irPng.toStdString(), ir);



			QString spkName = saveFileName + "/" + "SPK" + QString::number(rgb_ir_dep_pic_id) + "_360x640.raw";
			QFile fileSpk(spkName);
			if (!fileSpk.open(QIODevice::WriteOnly))
			{
				QMessageBox::critical(nullptr, QString::fromLocal8Bit("Error"), QString::fromLocal8Bit("Open File error!"), QMessageBox::Ok);
				return;
			}
			fileSpk.write((const char *)&yuyv[0] + UVC_IMG_WIDTH * UVC_IMG_HEIGHT, UVC_IMG_WIDTH*UVC_IMG_HEIGHT);
			fileSpk.close();

			//竖图
			//Mat depth(640, 360, CV_16UC1, recv_depth_buf + offset);
			//QString depthPng = saveFileName + "/" + "Depth" + QString::number(rgb_ir_dep_pic_id) + ".png";
			//imwrite(depthPng.toStdString(), depth);
		}
		
		rgb_ir_dep_pic_id++;

		ui.statusBar->setStatusTip("Completed pictures:" + rgb_ir_dep_pic_id);

	} while (isCircleShoot && shot_times--);

	shot_times = record_times;
}


