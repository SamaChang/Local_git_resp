#include "SendJpgDemo.h"
#include <opencv2\opencv.hpp>
#include <highgui.hpp>
#include <qstring.h>
#include "protocol.h"
#include <QDebug>
#include "MyComboBox.h"
#include <numeric>
#include <qthread.h>
#include <Windows.h>
#include <qeventloop.h>
//#include <synchapi.h>
//#include <algorithm>

SendJpgDemo::SendJpgDemo(QWidget *parent)
    : QWidget(parent), m_serialPort(nullptr),timer(nullptr), sen_pic_or_feature(false)
{
    ui.setupUi(this);
	this->setWindowIcon(QIcon("./Logo.png"));
	this->setWindowTitle("Feature_Pic_Recognition_V2.0");
	m_serialPort = new QSerialPort();//实例化串口类一个对象
	//combox = new QComboBox();
	m_portNameList = getPortNameList();
	ui.comboBox->addItems(m_portNameList);
	connect(ui.checkBox, SIGNAL(toggled(bool)), this, SLOT(selectFile()));
	connect(ui.comboBox, SIGNAL(clicked()), this, SLOT(serialPortList()));

	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(serialReads()));


	connect(m_serialPort, SIGNAL(readyRead()), this, SLOT(parse_rec()));
}

SendJpgDemo::~SendJpgDemo()
{
	if (m_serialPort->isOpen())
	{
		m_serialPort->close();
	}
	delete m_serialPort;
	m_serialPort = nullptr;
	
	
	if (timer->isActive())
	{
		timer->stop();
	}
	delete timer;
	timer = nullptr;
}
void saveLog(/*const QString &SN,*/ const QString &item, /*const QString &isPass*/int ID);
uint32_t reverse_uint32(uint8_t *uint32_value);


void SendJpgDemo::initSeri()
{
	if (m_serialPort->isOpen())//如果串口已经打开了 先给他关闭了
	{
		m_serialPort->clear();
		m_serialPort->close();
	}
	//设置串口名字 假设我们上面已经成功获取到了 并且使用第一个
	m_serialPort->setPortName(ui.comboBox->currentText());
	if (!m_serialPort->open(QIODevice::ReadWrite))//用ReadWrite 的模式尝试打开串口
	{
		QMessageBox::warning(nullptr, QString::fromLocal8Bit("串口"), QString::fromLocal8Bit("串口打开失败！"), QMessageBox::Ok);
		return;
	}
	//打开成功
	//m_serialPort->setBaudRate(921600, QSerialPort::AllDirections);
	m_serialPort->setBaudRate(QSerialPort::Baud115200, QSerialPort::AllDirections);//设置波特率和读写方向
	m_serialPort->setDataBits(QSerialPort::Data8);		//数据位为8位
	m_serialPort->setFlowControl(QSerialPort::NoFlowControl);//无流控制
	m_serialPort->setParity(QSerialPort::NoParity);	//无校验位
	m_serialPort->setStopBits(QSerialPort::OneStop); //一位停止位
}

void SendJpgDemo::serialReads()
{
	uint8_t rec_buf[4] = { 0 };
	if (timer->isActive())
	{
		timer->stop();
	}
	int len = info.length();
	if (info.length() == 11)
	{
		if (info.at(2) == 0x14)
		{
			rec_buf[0] = info.at(6);
			rec_buf[1] = info.at(7);
			rec_buf[2] = info.at(8);
			rec_buf[3] = info.at(9);
			int ID = reverse_uint32(rec_buf);
			if (ID >= 0)
			{
				saveLog(currentFileName, ID);
			}
			else
			{
				saveLog(currentFileName, -1);
			}
			ui.textEdit->append(QString::fromLocal8Bit("收到ACK:"));
			emit finishedInfo();
			info.clear();
		}
	}
	else
	{
		emit finishedInfo();
	}

	//m_port->write（函数QIODevice::write）用来发送串口数据，不过它也是异步的。也就是说：代码m_port->write("123");会立即返回，至于数据"123"何时会发送给对方，那是操作系统的事情。操作系统不忙的时候，才会做此项工作。
	//m_serialPort->waitForBytesWritten(3000);其含义为：操作系统把串口数据发送出去后，m_port->waitForBytesWritten才会返回。不过，总不能无限制等下去吧？10000就是等待时间的最大值.
	//m_port->readAll（函数QIODevice::readAll）用来读取串口数据。不过，它是异步执行的.什么是异步呢？那就是即使对方还没有发送串口数据，m_port->readAll也会立即返回，而不是傻傻的等着对方发送数据过来后再返回。
	//waitForReadyRead(3000)等待3s，如果3s内有数据进来，返回true,否则返回false
	//while (m_serialPort->waitForReadyRead(3000))
	//{
	//	info = m_serialPort->readAll(); //读取串口数据

	//	if (info.length() == 11)
	//	{
	//		if (info.at(2) == 0x14)
	//		{
	//			rec_buf[0] = info.at(6);
	//			rec_buf[1] = info.at(7);
	//			rec_buf[2] = info.at(8);
	//			rec_buf[3] = info.at(9);
	//			int ID = reverse_uint32(rec_buf);
	//			if (ID >= 0)
	//			{
	//				saveLog(currentFileName, ID);
	//			}
	//			else
	//			{
	//				saveLog(currentFileName, -1);
	//			}
	//			ui.textEdit->append(QString::fromLocal8Bit("收到ACK:"));
	//			emit finishedInfo();
	//		}
	//		break;
	//	}
	//}
}

void SendJpgDemo::timerDelay()
{
	timer->start(100);
	info.append(m_serialPort->readAll());
}

uint32_t reverse_uint32(uint8_t *uint32_value)          /* big endian */
{
	return  uint32_value[0] << 24 |
		uint32_value[1] << 16 |
		uint32_value[2] << 8 |
		uint32_value[3];
}

void saveLog(/*const QString &SN,*/ const QString &item, /*const QString &isPass*/int ID)
{
	//QDateTime da_time;
	//QString time_str = da_time.currentDateTime().toString("yyyy-MM-dd HH-mm-ss");
	QDir *DataFile = new QDir;    //创建文件路径（创建一个文件夹）
	bool exist = DataFile->exists("D:/PicLog");
	if (!exist)
	{
		bool isok = DataFile->mkdir("D:/PicLog"); // 新建文件夹
		if (!isok)
			QMessageBox::warning(nullptr, "sdf", "can't mkdir", QMessageBox::Ok);
	}
	//QString fileName = "D:/LogFile/"/* + time_str + */"log.txt";
	QString fileName = "D:/PicLog/piclog.txt";
	QFile file(fileName);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
	{
		QMessageBox::warning(nullptr, "sdf", "can't open", QMessageBox::Ok);
	}
	QTextStream stream(&file);
	stream << /*time_str + "\t\t\t" + */item + "\t\t\t\t" + QString::number(ID) << "\n";
	file.close();
}

//裁剪图片
void SendJpgDemo::on_pushButton_clicked()
{
	//通过ROI方式裁剪
	//std::string path = "D:/timg.jpg";
	//std::string dstPath = "D:/dst.jpg";
	//cv::Mat src = cv::imread(path);
	//cv::imshow("Source", src);
	//IplImage* pSrc = cvLoadImage(path.c_str(), 1);

	//CvSize size = cvSize(640, 640);//区域大小
	//cvSetImageROI(pSrc, cvRect(0, 0, /*0.5*pSrc->width*/1080, /*0.5*pSrc->height*/360));//设置源图像ROI
	//IplImage* pDest = cvCreateImage(cvSize(/*0.5*pSrc->width*/1080, /*0.5*pSrc->height*/360), pSrc->depth, pSrc->nChannels);//创建目标图像
	//cvCopy(pSrc, pDest, 0); //复制图像
	//cvResetImageROI(pSrc);//源图像用完后，清空ROI
	//cvShowImage("操作后的图像", pDest);  //显示图片
	//cvSaveImage(dstPath.c_str(), pDest);//保存目标图像
	////IplImage* resize;
	////cvResize(pDest, resize,1);


	////通过Range方式裁剪(先剪后缩)
	//cv::Mat img;
	//cv::Mat out;
	//cv::Mat dst;
	//img = cv::imread("D:\\ARGB\\170511.jpg");
	//cv::imshow("源图像", img);
	//out = img(cv::Range(0, img.rows), cv::Range(100, img.cols));
	//cv::imshow("裁剪后图像", out);
	////imwrite("D:\\Picture2.jpg", out);
	////缩放
	//cv::resize(out, dst, cv::Size(360, 640)/*src.size() / 2*/, (0, 0), (0, 0), cv::INTER_LINEAR);
	//cv::imshow("Resize", dst);

	//先放大再裁剪
	//cv::Mat img;
	//cv::Mat out;
	//cv::Mat dst;
	//img = cv::imread("D:\\ARGB\\000029.jpg"); /*int a = img.rows; int b = img.cols;*/
	//cv::resize(img, out, cv::Size(590, 826)/*src.size() / 2*/, (0, 0), (0, 0), cv::INTER_LINEAR);
	//cv::imshow("Resize", out);
	//dst = out(cv::Range(/*39*/30, /*1000*/670), cv::Range(/*54*/120, /*845*/480));
	//cv::imshow("裁剪后图像", dst);
	//cv::imwrite("D:\\Picture1.jpg", dst);

	//////CopyTo
	//cv::Mat signal = cv::imread("D:\\ARGB\\000029.jpg", 0);
	//cv::Mat imageROI;
	//int width, height;
	//cv::Mat srcImage(640, 360, signal.type()/*CV_8UC1*//*, cv::Scalar(255, 255, 255)*/);//创建一个高64，宽64的灰度图的Mat对象
	////cv::Mat srcImage = cv::imread("D:\\TX510_picture\\picture\\girl.jpg");
	////cv::imshow("源图像", srcImage);
	//
	//if (signal.rows <= 640 && signal.cols <= 360)
	//{
	//	imageROI = srcImage(cv::Rect(0, 0, signal.cols, signal.rows));
	//}
	////cv::Mat mask = cv::imread("D:\\ARGB\\000029.jpg", 0);
	//////cv::threshold(mask, mask, 200, 255, CV_THRESH_BINARY_INV);
	////signal.copyTo(imageROI, signal);
	//signal.copyTo(imageROI);
	//cv::namedWindow("result");
	//cv::imshow("result", srcImage);
	//cv::imwrite("D:\\Picture1.jpg", srcImage);


	//std::string path = "D:\\ARGB\\000029.jpg";
	//IplImage* pSrc = cvLoadImage(path.c_str(), 1);
	////cvSetImageROI(pSrc, cvRect(0, 0, 360, 640));//设置源图像ROI
	//IplImage* pDest = cvCreateImage(cvSize(640, 360), pSrc->depth, pSrc->nChannels);
	//IplImage* pMask = cvCreateImage(cvSize(pSrc->width, pSrc->height), pSrc->depth, pSrc->nChannels);
	//cvShowImage("空图片", pDest);  //显示图片
	//cvCopy(pSrc, pDest, 0); //复制图像
	//cvResetImageROI(pSrc);//源图像用完后，清空ROI
	//cvShowImage("操作后的图像", pDest);  //显示图片
	


	
	//cv::Mat image = cv::imread("D:/TX510_picture/picture/girl.jpg");
	/******************************************************************************/
	//cv::Mat logo = cv::imread("D:/ARGB/170511.jpg");
	//cv::Mat image(640, 360, logo.type()/*CV_8UC1*//*, cv::Scalar(255, 255, 255)*/);//创建一个高64，宽64的灰度图的Mat对象
	//cv::Mat imageROI;
	//cv::Mat cutImg;
	//cv::Mat cutImg_dst;
	//if (logo.rows <= 640 && logo.cols <= 360)
	//{
	//	imageROI = image(cv::Rect(0, 0, logo.cols, logo.rows));
	//	logo.copyTo(imageROI);
	//	cv::namedWindow("result");
	//	cv::imshow("result", image);
	//	cv::imwrite("D:\\Picture1.jpg", image);
	//}
	////if (logo.rows > 640 || logo.cols > 360)
	////{
	////	if ((logo.rows) / (logo.cols) > (16 / 9))
	////	{
	////		out = img(cv::Range(0, 320), cv::Range(60, 180 + 60));
	////	}
	////}
	//if (logo.cols > 360)
	//{
	//	//logo.cols-360  
	//	cutImg = logo(cv::Range(0, logo.rows), cv::Range((logo.cols - 360) / 2, logo.cols));
	//	cutImg_dst = cutImg(cv::Range(0, cutImg.rows), cv::Range((cutImg.cols - 360), cutImg.cols));
	//	//cv::imshow("cutImg_dst", cutImg_dst);
	//	imageROI = image(cv::Rect(0, 0, cutImg_dst.cols, cutImg_dst.rows));
	//	cutImg_dst.copyTo(imageROI);
	//	cv::namedWindow("result");
	//	cv::imshow("result", image);
	//	cv::imwrite("D:\\Picture1.jpg", image);
	//}
	////logo.copyTo(imageROI);
	////cv::namedWindow("result");
	////cv::imshow("result", image);
	////cv::imwrite("D:\\Picture1.jpg", image);
	/*****************************************************************************************************/
	


//QFileDialog类打开文件
	fileName = QFileDialog::getExistingDirectory(this, "choose src Directory",
		"/");
	QDir dir(fileName);
	ui.textEdit_2->append(QString::fromLocal8Bit("打开路径：") + fileName);
	//QList<QFileInfo> *fileInfo = new QList<QFileInfo>(dir->entryInfoList(filter));
	qint32 count = dir.count();
	//for (int i = 0; i < count; i++)
	//{
	//	QString file_name = dir[i];  //文件名称
	//	filter.append(file_name); 
	//}
	ui.textEdit_2->append(QString::fromLocal8Bit("文件数：") + count);
	for (int i = 0; i < count; i++)
	{
		QString file_name = dir[i];
		files.push_back(file_name);
		ui.textEdit_2->append(QString::fromLocal8Bit("文件名:") + file_name);
	}

}
//读取并裁剪图片
void SendJpgDemo::on_pushButton_3_clicked()
{

	QString cutFilePath = "D:/CutPic";
	QDir* dir = new QDir();
	if (!dir->exists(cutFilePath)) {
		dir->mkpath(cutFilePath);
	}
	ui.textEdit_2->append(QString::fromLocal8Bit("保存路径：") + cutFilePath);
	if (files.count() > 2)
	{
		for (int i = 2; i < files.count(); i++)
		{
			std::string b = files[i].toStdString();
			std::string c = fileName.toStdString();
			std::string a = fileName.toStdString() + "/" + files[i].toStdString();
			cv::Mat logo = cv::imread(fileName.toStdString() + "/" + files[i].toStdString());
			//cv::imshow("32", logo);
			cv::Mat image(640, 360, logo.type()/*CV_8UC1*//*, cv::Scalar(255, 255, 255)*/);//创建一个高64，宽64的灰度图的Mat对象
			cv::Mat imageROI;
			cv::Mat cutImg;
			cv::Mat cutImg_dst;
			if (logo.rows <= 640 && logo.cols <= 360)
			{
				imageROI = image(cv::Rect(0, 0, logo.cols, logo.rows));
				logo.copyTo(imageROI);
				//cv::namedWindow("result");
				//cv::imshow("result", image);
				std::string d = cutFilePath.toStdString() + "/" + files[i].toStdString();
				cv::imwrite(cutFilePath.toStdString() + "/" + files[i].toStdString(), image);
				ui.textEdit_2->append(QString::fromLocal8Bit("写入文件路径：") + cutFilePath + files[i]);
				
			}
			if (logo.cols > 360)
			{
				//logo.cols-360  
				cutImg = logo(cv::Range(0, logo.rows), cv::Range((logo.cols - 360) / 2, logo.cols));
				cutImg_dst = cutImg(cv::Range(0, cutImg.rows), cv::Range((cutImg.cols - 360), cutImg.cols));
				//cv::imshow("cutImg_dst", cutImg_dst);
				imageROI = image(cv::Rect(0, 0, cutImg_dst.cols, cutImg_dst.rows));
				cutImg_dst.copyTo(imageROI);
				//cv::namedWindow("result");
				//cv::imshow("result", image);
				cv::imwrite(cutFilePath.toStdString() + "/" + files[i].toStdString(), image);
				ui.textEdit_2->append(QString::fromLocal8Bit("写入文件路径：") + cutFilePath + files[i]);
			}
		}
	}
	QMessageBox::information(nullptr, QString::fromLocal8Bit("裁剪"), QString::fromLocal8Bit("裁剪完成！"), QMessageBox::Ok);
}
//串口通信
void SendJpgDemo::on_pushButton_2_clicked()
{
	//QStringList m_serialPortName;
	//foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
	//{
	//	m_serialPortName << info.portName();
	//	//ui.lineEdit->setText("serialPortName:" + info.portName()); 
	//}
	//m_serialPort = new QSerialPort();//实例化串口类一个对象
	initSeri();

	//连接信号槽 当下位机发送数据QSerialPortInfo 会发送个 readyRead 信号,我们定义个槽void receiveInfo()解析数据
	//connect(m_serialPort, SIGNAL(readyRead()), this, SLOT(receiveInfo()));
	//connect(m_serialPort, SIGNAL(readyRead()), this, SLOT(timerDelay()));
	
	//sendInfo(send_buf, 10);
	//sendInfo(/*send_buf, 10*/);
	if (ui.checkBox->isChecked())
	{
		//sendInfo();
		newSendInfo();
		QMessageBox::information(nullptr, QString::fromLocal8Bit("发送"), QString::fromLocal8Bit("发送完成！"), QMessageBox::Ok);
	}
	else
	{
		sendInfo(ui.lineEdit->text());
	}
}

void SendJpgDemo::on_pushButton_4_clicked()
{
	ui.textEdit->clear();
}

void SendJpgDemo::on_pushButton_5_clicked()
{
	ui.lineEdit->clear();
}

QStringList SendJpgDemo::getPortNameList()//获取所有可用的串口列表
{
	QStringList m_serialPortName;
	foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
	{
		m_serialPortName << info.portName();
	}
	return m_serialPortName;
}

//接收单片机的数据
void SendJpgDemo::receiveInfo()
{

	//timer->start(100);
	//info = m_serialPort->readAll();






	static int num;
	//QByteArray info;
	uint8_t rec_buf[4] = { 0 };
	Sleep(150);
	//m_serialPort->clear();
	//m_serialPort->waitForReadyRead(30);
	info = m_serialPort->readAll();
	QByteArray hexData = info.toHex();
	//while (info.length() != 7)
	//{
	//	info = m_serialPort->readAll();
	//}
	//int n = m_serialPort->bytesAvailable();
	//由于有时候收到数据的时候，readAll()收取数据不完整，以下循环为了把所有数据都收到后再进行处理
	while (1)
	{
		bool bsucc = m_serialPort->waitForReadyRead(10);
		if (!bsucc)
		{
			break;
		}
		//n += m_serialPort->bytesAvailable();
		info += m_serialPort->readAll();
	}
	//QByteArray hexData = info.toHex();

	if (info.length() == 10)
	{
		rec_buf[0] = info.at(5);
		rec_buf[1] = info.at(6);
		rec_buf[2] = info.at(7);
		rec_buf[3] = info.at(8);
		int ID = reverse_uint32(rec_buf);
		if (ID >= 0 && num % 2 == 0)
		{
			saveLog(currentFileName, ID);
		}
		if (ID < 0 && num % 2 == 0)
		{
			saveLog(currentFileName, -1);
		}

		if (info.at(1) == 0x14 && num % 2 == 0)
		{
			emit finishedInfo();
			ui.textEdit->append(QString::fromLocal8Bit("收到ACK:"));
		}
		QString str = QString::fromLatin1(hexData);

		ui.textEdit->append(str);
	}
	else
	{
		emit finishedInfo();
	}
	num++;

}
//另一个 函数 char 转为 16进制
char SendJpgDemo::convertCharToHex(char ch)
{
	/*
	0x30等于十进制的48，48也是0的ASCII值，，
	1-9的ASCII值是49-57，，所以某一个值－0x30，，
	就是将字符0-9转换为0-9

	*/
	if ((ch >= '0') && (ch <= '9'))
		return ch - 0x30;
	else if ((ch >= 'A') && (ch <= 'F'))
		return ch - 'A' + 10;
	else if ((ch >= 'a') && (ch <= 'f'))
		return ch - 'a' + 10;
	else return (-1);
}

void toHex(const QString &str, QByteArray &byteData)
{
	QByteArray byte = str.toLatin1();
	//byte.toHex();
	byteData = byte.toHex();
}


//向单片机发送数据

//基本和单片机交互 数据 都是16进制的 我们这里自己写一个 Qstring 转为 16进制的函数	
void SendJpgDemo::convertStringToHex(const QString &str, QByteArray &byteData)
{
	int hexdata, lowhexdata;
	int hexdatalen = 0;
	int len = str.length();
	byteData.resize(len / 2);
	char lstr, hstr;
	for (int i = 0; i < len; )
	{
		//char lstr,
		hstr = str[i].toLatin1();
		if (hstr == ' ')
		{
			i++;
			continue;
		}
		i++;
		if (i >= len)
			break;
		lstr = str[i].toLatin1();
		hexdata = convertCharToHex(hstr);
		lowhexdata = convertCharToHex(lstr);
		if ((hexdata == 16) || (lowhexdata == 16))
			break;
		else
			hexdata = hexdata * 16 + lowhexdata;
		i++;
		byteData[hexdatalen] = (char)hexdata;
		hexdatalen++;
	}
	byteData.resize(hexdatalen);
}

void SendJpgDemo::selectFile()
{
	if (ui.checkBox->isChecked())
	{
		fileName = QFileDialog::getExistingDirectory(this, "choose src Directory",
			"/");
	}
}


void SendJpgDemo::parse_rec()
{
	char compareArray[5] = { 0xef, 0xaa, 0x14 ,0x15 ,0x00};
	//0xef  0xaa  0x14  0x00  0x00  0x00  0x05  0x01  0x00  0x00  0x00  0x01  0x15
	newParseRec.append(m_serialPort->readAll());
	//uint8_t tmp[4] = { 0 };
	uint8_t id_vec[4] = { 0 };
	//uint8_t id_fea[2] = { 0 };
	if (newParseRec.length() < 13)
		return;
	for (int i = 0; i < newParseRec.length(); i++)
	{
		if (sen_pic_or_feature)  //收照片下发返回id
		{
			if (newParseRec.at(i) == compareArray[0] && newParseRec.at(i + 1) == compareArray[1] && newParseRec.at(i + 2) == compareArray[2])
			{
				char cal_check_sum = std::accumulate(/*newParseRec.at(i + 7)*/newParseRec.data() + i + 2, newParseRec.data() + i + 12, 0);
				if (newParseRec.at(i + 12) == cal_check_sum)
				{
					id_vec[0] = newParseRec.at(i + 8);
					id_vec[1] = newParseRec.at(i + 9);
					id_vec[2] = newParseRec.at(i + 10);
					id_vec[3] = newParseRec.at(i + 11);
					int cur_id = reverse_uint32(id_vec);
					if (cur_id >= 0)
					{
						saveLog(currentFileName, cur_id);
						ui.textEdit->append(QString::fromLocal8Bit("注册成功，注册ID为：") + QString::number(cur_id));
						newParseRec.clear();
						emit finished();
						break;
					}
					if (cur_id == -1)
					{
						saveLog(currentFileName, cur_id);
						ui.textEdit->append(QString::fromLocal8Bit("注册失败，注册ID为：") + QString::number(cur_id));
						newParseRec.clear();
						emit finished();
						break;
					}
					if (cur_id == -2)
					{
						saveLog(currentFileName, cur_id);
						ui.textEdit->append(QString::fromLocal8Bit("注册失败，注册ID为：") + QString::number(cur_id));
						newParseRec.clear();
						emit finished();
						break;
					}
				}
			}
		}
		else//收特征文件返回id  
		{
			//sync(2B)  msgid(1B)       len(4B)       cmd(1B)result(1B)         id(4B)   checksum(1B)
			//0xef  0xaa  0x00  0x00  0x00  0x00  0x06  0x15  0x00  0x00  0x00  0x00  0x01  0x1a
			if (newParseRec.at(i) == compareArray[0] && newParseRec.at(i + 1) == compareArray[1] && newParseRec.at(i + 2) == compareArray[4])
			{
				char cal_check_sum = std::accumulate(/*newParseRec.at(i + 7)*/newParseRec.data() + i + 2, newParseRec.data() + i + 13, 0);
				if (newParseRec.at(i + 13) == cal_check_sum)
				{
					if (newParseRec.at(i + 8) == compareArray[4])   //注册成功
					{
						id_vec[0] = newParseRec.at(i + 9);
						id_vec[1] = newParseRec.at(i + 10);
						id_vec[2] = newParseRec.at(i + 11);
						id_vec[3] = newParseRec.at(i + 12);
						int fea_id = reverse_uint32(id_vec);
						saveLog(currentFileName, fea_id);
						ui.textEdit->append(QString::fromLocal8Bit("注册成功，注册ID为：") + QString::number(fea_id));
						newParseRec.clear();
						emit feature_fini();
						break;
					}
					else
					{
						id_vec[0] = newParseRec.at(i + 9);
						id_vec[1] = newParseRec.at(i + 10);
						id_vec[2] = newParseRec.at(i + 11);
						id_vec[3] = newParseRec.at(i + 12);
						int fea_id = reverse_uint32(id_vec);
						saveLog(currentFileName, fea_id);
						ui.textEdit->append(QString::fromLocal8Bit("注册失败，注册ID为：") + QString::number(fea_id));
						newParseRec.clear();
						emit feature_fini();
						break;
					}
				}
			}
		}
		
	}
	
}


void SendJpgDemo::newSendInfo()
{
	sen_pic_or_feature = true;   //发送图片是true，发送特征是false
	char compareArray[3] = { 0xef, 0xaa, 0xb1 };
	char sed_check[12] = { 0 };
	int pic = 1;
	files.clear();
	QDir dir(fileName);
	ui.textEdit_2->append(QString::fromLocal8Bit("打开路径：") + fileName);
	qint32 count = dir.count();
	for (int i = 0; i < count; i++)
	{
		QString file_name = dir[i];
		files.push_back(file_name);
		ui.textEdit_2->append(QString::fromLocal8Bit("文件名") + file_name);
	}
	uint8_t rec_buf[4] = { 0 };
	if (files.count() > 2)
	{
		QEventLoop loop;
		connect(this, SIGNAL(finished()), &loop, SLOT(quit()));
		for (int i = 2; i < files.count(); i++)
		{
			flag = true;
			//qt读文件数据
			char send_buf[1024 * 200] = { 0 };
			QFile file(fileName + "/" + files[i]);
			file.open(QIODevice::ReadOnly/* | QIODevice::Text*/);
			QByteArray t = file.readAll();
			file.close();
			info.clear();
			int len = t.length();

			progresPortocol(send_buf, len);
			memcpy(send_buf + sizeof(ProgressPro), t.data(), len);
			char sumCheck = std::accumulate(send_buf + 2, send_buf + sizeof(ProgressPro) + len, 0);
			insertCheck(send_buf + sizeof(ProgressPro) + len, sumCheck);

			m_serialPort->write(send_buf, len + sizeof(ProgressPro) + 1);
			
			//m_serialPort->waitForBytesWritten(10000);    //确保发送完毕

			currentFileName = files[i];

			ui.textEdit->append(QString::fromLocal8Bit("发送图片数：")+ QString::number(pic));
			pic++;
			loop.exec();
		}
	}
}

//写两个函数 向单片机发送数据 
void SendJpgDemo::sendInfo(/*QString path*/)
{
	char compareArray[3] = { 0xef, 0xaa, 0xb1 };
	char sed_check[12] = { 0 };
	int pic = 1;
	files.clear();
	QDir dir(fileName);
	ui.textEdit_2->append(QString::fromLocal8Bit("打开路径：") + fileName);
	qint32 count = dir.count();
	for (int i = 0; i < count; i++)
	{
		QString file_name = dir[i];
		files.push_back(file_name);
		ui.textEdit_2->append(QString::fromLocal8Bit("文件名") + file_name);
	}
	uint8_t rec_buf[4] = { 0 };
	//static int ID = 0;
	//QString cutFilePath = "D:/CutPic";
	if (files.count() > 2) 
	{
		for (int i = 2; i < files.count(); i++)
		{

			flag = true;
			Sleep(1000);
			//qt读文件数据
			char send_buf[1024 * 200] = { 0 };
			//char *send_buf = (char *)malloc(1024 * 1024 * 2);//2M
			QFile file(fileName + "/" + files[i]);
			file.open(QIODevice::ReadOnly/* | QIODevice::Text*/);
			QByteArray t = file.readAll();
			file.close();
			info.clear();
			//qt写文件数据
			//QFile writeFile("D:/CutPic/test.jpg");
			//writeFile.open(QIODevice::WriteOnly /*| QIODevice::Text*/);
			//writeFile.write(t);
			//writeFile.close();

	/*		buffer_send r;
			memcpy(r.data, t.data(), t.length());*/
			//QFile writeFile("D:/CutPic/test.jpg");
			//writeFile.open(QIODevice::WriteOnly /*| QIODevice::Text*/);
			//writeFile.write(r.data, t.length());
			//writeFile.close();
			int len = t.length();
			
			//Test test;
			//test.data = new char[t.length()];
			//memcpy(test.data, t.data(), t.length());
			
			//testNewProtocol(send_buf, t.length()/*, 8*//*, test*/);
			//memcpy(send_buf + 5, t.data(), t.length());


			progresPortocol(send_buf, t.length());
			memcpy(send_buf + sizeof(ProgressPro), t.data(), t.length());
			char sumCheck = std::accumulate(send_buf + 2, send_buf + sizeof(ProgressPro) + t.length(), 0);
			insertCheck(send_buf + sizeof(ProgressPro) + t.length(), sumCheck);

			

			//syncWord(send_buf, t.length(), r, 1);
			m_serialPort->write(send_buf, t.length() +sizeof(ProgressPro) + 1);



			//新加同步/*******************/
			m_serialPort->waitForBytesWritten(10000);    //确保发送完毕


			currentFileName = files[i];   

			/*******************************/
			ui.textEdit->append(QString::fromLocal8Bit("发送图片数："));
			ui.textEdit->append(QString::number(pic));
			pic++;

			
			/**********************************/
			//m_port->waitForReadyRead(10000)，其含义为等待对方发送串口数据过来。如果对方发送串口数据过来了，它返回true，然后使用m_port->readAll读取串口数据；如果对方在3秒内都没有发送串口数据过来，它返回false，退出循环。
			while (m_serialPort->waitForReadyRead(10000))
			{
				
				//info = m_serialPort->readAll(); //读取串口数据
				info.append(m_serialPort->readAll());
				int b = info.length();
				if (info.length() == 13)
				{
					
					if (info.at(0) == compareArray[0] && info.at(1) == compareArray[1] && info.at(2) == 0x14)
					{
						flag = false;
						rec_buf[0] = info.at(8);
						rec_buf[1] = info.at(9);
						rec_buf[2] = info.at(10);
						rec_buf[3] = info.at(11);
						int ID = reverse_uint32(rec_buf);
						if (ID >= 0)
						{
							saveLog(currentFileName, ID);
							break;
						}
						else
						{
							/******************************************************************/
							//校验和不对或者下位机接收到数据不完整，进行3次图片数据重传
							if (ID == -1)   //-1为0xff,0xff,0xff,0xff校验和失败，说明图片数据有问题
							{
								int record = 2;
								do
								{
									timeoutSend.clear();
									uint8_t timeoutBuf[4] = { 0 };
									m_serialPort->write(send_buf, t.length() + sizeof(ProgressPro) + 1);
									m_serialPort->waitForBytesWritten(10000);
									while (m_serialPort->waitForReadyRead(10000))
									{
										timeoutSend.append(m_serialPort->readAll());
										if (timeoutSend.length() == 13)
										{
											if (timeoutSend.at(0) == compareArray[0] && timeoutSend.at(1) == compareArray[1] && timeoutSend.at(2) == 0x14)
											{
												timeoutBuf[0] = timeoutSend.at(8);
												timeoutBuf[1] = timeoutSend.at(9);
												timeoutBuf[2] = timeoutSend.at(10);
												timeoutBuf[3] = timeoutSend.at(11);
												int newID = reverse_uint32(timeoutBuf);
												if (newID >= 0)
												{
													saveLog(currentFileName, newID);
													//ID = newID;    //更新ID
													record = 0;  //不再重传
													break;
												}
												else
												{
													if (newID == -1 && record != 0)     //收到-1时，还是校验和失败，需要重传，当record为最后一次重传的时候，如果还是-1，就将结果记录为校验和失败
													{
														//saveLog(currentFileName, -1);
														break;
													}
													if (newID == -1 && record == 0)
													{
														saveLog(currentFileName, -1);
														break;
													}
													if (newID == -2)    //-2为0xff,0xff,0xff,0xfe注册失败，说明图片传输没问题
													{
														saveLog(currentFileName, -2);
														record = 0;		//不再重传
														break;
													}
												}
												
											}
										}
										else    //如果重传3次都没有收到，就记录为-1
										{
											if (record == 0)
											{
												saveLog(currentFileName, -1);
												break;
											}
										}
									}
								} 
								while (record--);
							}
							if (ID == -2)   //-2为0xff,0xff,0xff,0xfe注册失败
							{
								saveLog(currentFileName, -2);
								break;
							}
							//saveLog(currentFileName, -1);
						}
						ui.textEdit->append(QString::fromLocal8Bit("收到ACK"));
						//break;
					}
				}
				//串口读取到数据了，但是数据没收全，丢失了几个字节的情况
				//else
				//{
				//	checkID(sed_check);
				//	m_serialPort->write(sed_check, 4);   //下发查询命令
				//	m_serialPort->waitForBytesWritten(5000);   

				//	char rec_checkBuf[4] = { 0 };
				//	while (m_serialPort->waitForReadyRead(3000))
				//	{
				//		
				//		QByteArray recID = m_serialPort->readAll();
				//		if (recID.length() == 8)
				//		{
				//			if (recID.at(0) == 0xEF && recID.at(1) == 0xAA && recID.at(2) == 0xB1 && recID.at(3) == 0xB2)
				//			{
				//				rec_checkBuf[0] = recID.at(4);
				//				rec_checkBuf[1] = recID.at(5);
				//				rec_checkBuf[2] = recID.at(6);
				//				rec_checkBuf[3] = recID.at(7);
				//				int ID = reverse_uint32(rec_buf);
				//				if (ID >= 0)
				//				{
				//					saveLog(currentFileName, ID);
				//				}
				//				else
				//				{
				//					saveLog(currentFileName, -1);
				//				}
				//				ui.textEdit->append(QString::fromLocal8Bit("收到查询回复"));
				//				break;
				//			}
				//		}
				//	}
				//}
			}

			//一个数据都没收到，串口数据全部丢失的情况和收到数据不完整，丢失部分数据不够11字节情况
			if (flag)
			{
				
				int count = 9;
				checkCMD(sed_check, 0);
				char sumCheck = std::accumulate(sed_check + 2, sed_check + sizeof(ProgressPro), 0);
				insertCheck(sed_check + sizeof(ProgressPro), sumCheck);
				//checkID(sed_check);   //


				uint8_t rec_checkBuf[4] = { 0 };
				do /*(m_serialPort->waitForReadyRead(1000))*/
				{
					recID.clear();
					m_serialPort->write(sed_check, 8);   //下发查询命令
					m_serialPort->waitForBytesWritten(5000);
					while (m_serialPort->waitForReadyRead(5000))
					{
						recID.append(m_serialPort->readAll());
						int c = recID.length();
						//if (recID.length() == 10)
						//{
						//	if (recID.at(0) == 0xEF && recID.at(1) == 0xAA && recID.at(2) == 0xB1)
						//	{
						//		rec_checkBuf[0] = recID.at(5);
						//		rec_checkBuf[1] = recID.at(6);
						//		rec_checkBuf[2] = recID.at(7);
						//		rec_checkBuf[3] = recID.at(8);
						//		int checkID = reverse_uint32(rec_checkBuf);  //checkID为下位机最近一次成功的ID
						//		if (checkID >= 0 && checkID > ID)  
						//		{
						//			saveLog(currentFileName, checkID);
						//		}
						//		if (checkID >= 0 && checkID == ID)   //注册失败
						//		{
						//			saveLog(currentFileName, -2);
						//		}
						//		if (checkID == -1)   //校验和失败
						//		{
						//			saveLog(currentFileName, -1);
						//		}
						//		if (checkID == -2)		//注册失败
						//		{
						//			saveLog(currentFileName, -2);
						//		}
						//		
						//		ui.textEdit->append(QString::fromLocal8Bit("收到查询回复"));
						//		count = 0;
						//		break;
						//	}
						//}
						//else
						//{
						//	saveLog(currentFileName, 65565);   //查询无效
						//}
					}
					if (recID.length() == 12)
					{
						if (recID.at(0) == compareArray[0] && recID.at(1) == compareArray[1] && recID.at(2) == compareArray[2])
						{
							rec_checkBuf[0] = recID.at(7);
							rec_checkBuf[1] = recID.at(8);
							rec_checkBuf[2] = recID.at(9);
							rec_checkBuf[3] = recID.at(10);
							int checkID = reverse_uint32(rec_checkBuf);  //checkID为当前的ID
							if (checkID >= 0/* && checkID > ID*/)
							{
								saveLog(currentFileName, checkID);
							}
							//if (checkID >= 0 && checkID == ID)   //注册失败
							//{
							//	saveLog(currentFileName, -2);
							//}
							if (checkID == -1)   //校验和失败
							{
								saveLog(currentFileName, -1);
							}
							if (checkID == -2)		//注册失败
							{
								saveLog(currentFileName, -2);
							}

							ui.textEdit->append(QString::fromLocal8Bit("收到查询回复"));
							count = 0;
							break;
						}
					}
					else
					{
						saveLog(currentFileName, 65565);   //查询无效
					}
					
					
					//if (recID.length() == 8)
					//{
					//	if (recID.at(0) == 0xEF && recID.at(1) == 0xAA && recID.at(2) == 0xB1 && recID.at(3) == 0xB2)
					//	{
					//		rec_checkBuf[0] = recID.at(4);
					//		rec_checkBuf[1] = recID.at(5);
					//		rec_checkBuf[2] = recID.at(6);
					//		rec_checkBuf[3] = recID.at(7);
					//		int ID = reverse_uint32(rec_buf);
					//		if (ID >= 0)
					//		{
					//			saveLog(currentFileName, ID);
					//		}
					//		else
					//		{
					//			saveLog(currentFileName, -1);
					//		}
					//		ui.textEdit->append(QString::fromLocal8Bit("收到查询回复"));
					//		break;
					//	}
					//}
				} while (count--);
			}
			

			
			//如果3s都没收到的话，可以考虑下位机也发了ACK了，但串口发送的时候丢失了。就是收不到，要重传。
			/**********************************************/



			//下面是之前就有
			//QEventLoop loop;
			//connect(/*m_serialPort*/this, SIGNAL(finishedInfo()), &loop, SLOT(quit()));
			//loop.exec();
			

			//ui.textEdit->append(QString::fromLocal8Bit("发送图片数："));
			//ui.textEdit->append(QString::number(pic));
			//pic++;
		}
	}
}
//发送手写数据
void SendJpgDemo::sendInfo(const QString &info)
{

	QByteArray sendBuf;
	if (info.contains(" "))
	{
		return;
		//info.replace()
		//info.replace(QString(""), QString(""));//我这里是把空格去掉，根据你们定的协议来
	}
	//convertStringToHex(info, sendBuf); //把QString 转换 为 hex 
	sendBuf = info.toLatin1();
	m_serialPort->write(sendBuf); //这句是真正的给单片机发数据 用到的是QIODevice::write 具体可以看文档

}

void readFile(cv::Mat img)
{
	int imgSize = img.cols*img.rows;
}

void SendJpgDemo::serialPortList()
{
	ui.comboBox->clear();
	m_portNameList = getPortNameList();
	ui.comboBox->addItems(m_portNameList);
	
}
//选择特征文件夹
void SendJpgDemo::on_pushButton_7_clicked()
{
	feature_dir = QFileDialog::getExistingDirectory(this, "Choose Feature Directory",
		"/");
	ui.lineEdit_2->setText(feature_dir);
}
//下发特征文件
void SendJpgDemo::on_pushButton_6_clicked()
{
	initSeri();
	sen_pic_or_feature = false;
	int pic = 1;
	files.clear();
	QDir dir(feature_dir);
	qint32 count = dir.count();
	//char *sed_buf = (char *)malloc(2 * 1024 * 1024);
	for (int i = 0; i < count; i++)
	{
		QString file_name = dir[i];
		files.push_back(file_name);
		ui.textEdit_2->append(QString::fromLocal8Bit("文件名:") + file_name);
	}
	if (files.count() > 2)
	{
		QEventLoop loop;
		connect(this, SIGNAL(feature_fini()), &loop, SLOT(quit()));
		for (int i = 2; i < files.count(); i++)
		{
			//flag = true;
			//qt读文件数据
			char sed_buf[1024 * 5] = { 0 };
			QFile file(feature_dir + "/" + files[i]);
			if (!file.open(QIODevice::ReadOnly))
			{
				QMessageBox::warning(nullptr, "sdf", "can't open this file", QMessageBox::Ok);
				return;
			}
			QByteArray feature = file.readAll();
			file.close();
			int len = feature.length();
			featurePortocol(sed_buf, len);
			memcpy(sed_buf + sizeof(ProgressPro), feature.data(), len);
			char sumCheck = std::accumulate(sed_buf + 2, sed_buf + sizeof(ProgressPro) + len, 0);
			insertCheck(sed_buf + sizeof(ProgressPro) + len, sumCheck);
			m_serialPort->write(sed_buf, len + sizeof(ProgressPro) + 1);

			currentFileName = files[i];

			ui.textEdit->append(QString::fromLocal8Bit("发送特征文件数：") + QString::number(pic));
			pic++;
			loop.exec();
		}
	}
}