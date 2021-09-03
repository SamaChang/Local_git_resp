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
	m_serialPort = new QSerialPort();//ʵ����������һ������
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
	if (m_serialPort->isOpen())//��������Ѿ����� �ȸ����ر���
	{
		m_serialPort->clear();
		m_serialPort->close();
	}
	//���ô������� �������������Ѿ��ɹ���ȡ���� ����ʹ�õ�һ��
	m_serialPort->setPortName(ui.comboBox->currentText());
	if (!m_serialPort->open(QIODevice::ReadWrite))//��ReadWrite ��ģʽ���Դ򿪴���
	{
		QMessageBox::warning(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("���ڴ�ʧ�ܣ�"), QMessageBox::Ok);
		return;
	}
	//�򿪳ɹ�
	//m_serialPort->setBaudRate(921600, QSerialPort::AllDirections);
	m_serialPort->setBaudRate(QSerialPort::Baud115200, QSerialPort::AllDirections);//���ò����ʺͶ�д����
	m_serialPort->setDataBits(QSerialPort::Data8);		//����λΪ8λ
	m_serialPort->setFlowControl(QSerialPort::NoFlowControl);//��������
	m_serialPort->setParity(QSerialPort::NoParity);	//��У��λ
	m_serialPort->setStopBits(QSerialPort::OneStop); //һλֹͣλ
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
			ui.textEdit->append(QString::fromLocal8Bit("�յ�ACK:"));
			emit finishedInfo();
			info.clear();
		}
	}
	else
	{
		emit finishedInfo();
	}

	//m_port->write������QIODevice::write���������ʹ������ݣ�������Ҳ���첽�ġ�Ҳ����˵������m_port->write("123");���������أ���������"123"��ʱ�ᷢ�͸��Է������ǲ���ϵͳ�����顣����ϵͳ��æ��ʱ�򣬲Ż����������
	//m_serialPort->waitForBytesWritten(3000);�京��Ϊ������ϵͳ�Ѵ������ݷ��ͳ�ȥ��m_port->waitForBytesWritten�Ż᷵�ء��������ܲ��������Ƶ���ȥ�ɣ�10000���ǵȴ�ʱ������ֵ.
	//m_port->readAll������QIODevice::readAll��������ȡ�������ݡ������������첽ִ�е�.ʲô���첽�أ��Ǿ��Ǽ�ʹ�Է���û�з��ʹ������ݣ�m_port->readAllҲ���������أ�������ɵɵ�ĵ��ŶԷ��������ݹ������ٷ��ء�
	//waitForReadyRead(3000)�ȴ�3s�����3s�������ݽ���������true,���򷵻�false
	//while (m_serialPort->waitForReadyRead(3000))
	//{
	//	info = m_serialPort->readAll(); //��ȡ��������

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
	//			ui.textEdit->append(QString::fromLocal8Bit("�յ�ACK:"));
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
	QDir *DataFile = new QDir;    //�����ļ�·��������һ���ļ��У�
	bool exist = DataFile->exists("D:/PicLog");
	if (!exist)
	{
		bool isok = DataFile->mkdir("D:/PicLog"); // �½��ļ���
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

//�ü�ͼƬ
void SendJpgDemo::on_pushButton_clicked()
{
	//ͨ��ROI��ʽ�ü�
	//std::string path = "D:/timg.jpg";
	//std::string dstPath = "D:/dst.jpg";
	//cv::Mat src = cv::imread(path);
	//cv::imshow("Source", src);
	//IplImage* pSrc = cvLoadImage(path.c_str(), 1);

	//CvSize size = cvSize(640, 640);//�����С
	//cvSetImageROI(pSrc, cvRect(0, 0, /*0.5*pSrc->width*/1080, /*0.5*pSrc->height*/360));//����Դͼ��ROI
	//IplImage* pDest = cvCreateImage(cvSize(/*0.5*pSrc->width*/1080, /*0.5*pSrc->height*/360), pSrc->depth, pSrc->nChannels);//����Ŀ��ͼ��
	//cvCopy(pSrc, pDest, 0); //����ͼ��
	//cvResetImageROI(pSrc);//Դͼ����������ROI
	//cvShowImage("�������ͼ��", pDest);  //��ʾͼƬ
	//cvSaveImage(dstPath.c_str(), pDest);//����Ŀ��ͼ��
	////IplImage* resize;
	////cvResize(pDest, resize,1);


	////ͨ��Range��ʽ�ü�(�ȼ�����)
	//cv::Mat img;
	//cv::Mat out;
	//cv::Mat dst;
	//img = cv::imread("D:\\ARGB\\170511.jpg");
	//cv::imshow("Դͼ��", img);
	//out = img(cv::Range(0, img.rows), cv::Range(100, img.cols));
	//cv::imshow("�ü���ͼ��", out);
	////imwrite("D:\\Picture2.jpg", out);
	////����
	//cv::resize(out, dst, cv::Size(360, 640)/*src.size() / 2*/, (0, 0), (0, 0), cv::INTER_LINEAR);
	//cv::imshow("Resize", dst);

	//�ȷŴ��ٲü�
	//cv::Mat img;
	//cv::Mat out;
	//cv::Mat dst;
	//img = cv::imread("D:\\ARGB\\000029.jpg"); /*int a = img.rows; int b = img.cols;*/
	//cv::resize(img, out, cv::Size(590, 826)/*src.size() / 2*/, (0, 0), (0, 0), cv::INTER_LINEAR);
	//cv::imshow("Resize", out);
	//dst = out(cv::Range(/*39*/30, /*1000*/670), cv::Range(/*54*/120, /*845*/480));
	//cv::imshow("�ü���ͼ��", dst);
	//cv::imwrite("D:\\Picture1.jpg", dst);

	//////CopyTo
	//cv::Mat signal = cv::imread("D:\\ARGB\\000029.jpg", 0);
	//cv::Mat imageROI;
	//int width, height;
	//cv::Mat srcImage(640, 360, signal.type()/*CV_8UC1*//*, cv::Scalar(255, 255, 255)*/);//����һ����64����64�ĻҶ�ͼ��Mat����
	////cv::Mat srcImage = cv::imread("D:\\TX510_picture\\picture\\girl.jpg");
	////cv::imshow("Դͼ��", srcImage);
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
	////cvSetImageROI(pSrc, cvRect(0, 0, 360, 640));//����Դͼ��ROI
	//IplImage* pDest = cvCreateImage(cvSize(640, 360), pSrc->depth, pSrc->nChannels);
	//IplImage* pMask = cvCreateImage(cvSize(pSrc->width, pSrc->height), pSrc->depth, pSrc->nChannels);
	//cvShowImage("��ͼƬ", pDest);  //��ʾͼƬ
	//cvCopy(pSrc, pDest, 0); //����ͼ��
	//cvResetImageROI(pSrc);//Դͼ����������ROI
	//cvShowImage("�������ͼ��", pDest);  //��ʾͼƬ
	


	
	//cv::Mat image = cv::imread("D:/TX510_picture/picture/girl.jpg");
	/******************************************************************************/
	//cv::Mat logo = cv::imread("D:/ARGB/170511.jpg");
	//cv::Mat image(640, 360, logo.type()/*CV_8UC1*//*, cv::Scalar(255, 255, 255)*/);//����һ����64����64�ĻҶ�ͼ��Mat����
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
	


//QFileDialog����ļ�
	fileName = QFileDialog::getExistingDirectory(this, "choose src Directory",
		"/");
	QDir dir(fileName);
	ui.textEdit_2->append(QString::fromLocal8Bit("��·����") + fileName);
	//QList<QFileInfo> *fileInfo = new QList<QFileInfo>(dir->entryInfoList(filter));
	qint32 count = dir.count();
	//for (int i = 0; i < count; i++)
	//{
	//	QString file_name = dir[i];  //�ļ�����
	//	filter.append(file_name); 
	//}
	ui.textEdit_2->append(QString::fromLocal8Bit("�ļ�����") + count);
	for (int i = 0; i < count; i++)
	{
		QString file_name = dir[i];
		files.push_back(file_name);
		ui.textEdit_2->append(QString::fromLocal8Bit("�ļ���:") + file_name);
	}

}
//��ȡ���ü�ͼƬ
void SendJpgDemo::on_pushButton_3_clicked()
{

	QString cutFilePath = "D:/CutPic";
	QDir* dir = new QDir();
	if (!dir->exists(cutFilePath)) {
		dir->mkpath(cutFilePath);
	}
	ui.textEdit_2->append(QString::fromLocal8Bit("����·����") + cutFilePath);
	if (files.count() > 2)
	{
		for (int i = 2; i < files.count(); i++)
		{
			std::string b = files[i].toStdString();
			std::string c = fileName.toStdString();
			std::string a = fileName.toStdString() + "/" + files[i].toStdString();
			cv::Mat logo = cv::imread(fileName.toStdString() + "/" + files[i].toStdString());
			//cv::imshow("32", logo);
			cv::Mat image(640, 360, logo.type()/*CV_8UC1*//*, cv::Scalar(255, 255, 255)*/);//����һ����64����64�ĻҶ�ͼ��Mat����
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
				ui.textEdit_2->append(QString::fromLocal8Bit("д���ļ�·����") + cutFilePath + files[i]);
				
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
				ui.textEdit_2->append(QString::fromLocal8Bit("д���ļ�·����") + cutFilePath + files[i]);
			}
		}
	}
	QMessageBox::information(nullptr, QString::fromLocal8Bit("�ü�"), QString::fromLocal8Bit("�ü���ɣ�"), QMessageBox::Ok);
}
//����ͨ��
void SendJpgDemo::on_pushButton_2_clicked()
{
	//QStringList m_serialPortName;
	//foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
	//{
	//	m_serialPortName << info.portName();
	//	//ui.lineEdit->setText("serialPortName:" + info.portName()); 
	//}
	//m_serialPort = new QSerialPort();//ʵ����������һ������
	initSeri();

	//�����źŲ� ����λ����������QSerialPortInfo �ᷢ�͸� readyRead �ź�,���Ƕ������void receiveInfo()��������
	//connect(m_serialPort, SIGNAL(readyRead()), this, SLOT(receiveInfo()));
	//connect(m_serialPort, SIGNAL(readyRead()), this, SLOT(timerDelay()));
	
	//sendInfo(send_buf, 10);
	//sendInfo(/*send_buf, 10*/);
	if (ui.checkBox->isChecked())
	{
		//sendInfo();
		newSendInfo();
		QMessageBox::information(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("������ɣ�"), QMessageBox::Ok);
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

QStringList SendJpgDemo::getPortNameList()//��ȡ���п��õĴ����б�
{
	QStringList m_serialPortName;
	foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
	{
		m_serialPortName << info.portName();
	}
	return m_serialPortName;
}

//���յ�Ƭ��������
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
	//������ʱ���յ����ݵ�ʱ��readAll()��ȡ���ݲ�����������ѭ��Ϊ�˰��������ݶ��յ����ٽ��д���
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
			ui.textEdit->append(QString::fromLocal8Bit("�յ�ACK:"));
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
//��һ�� ���� char תΪ 16����
char SendJpgDemo::convertCharToHex(char ch)
{
	/*
	0x30����ʮ���Ƶ�48��48Ҳ��0��ASCIIֵ����
	1-9��ASCIIֵ��49-57��������ĳһ��ֵ��0x30����
	���ǽ��ַ�0-9ת��Ϊ0-9

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


//��Ƭ����������

//�����͵�Ƭ������ ���� ����16���Ƶ� ���������Լ�дһ�� Qstring תΪ 16���Ƶĺ���	
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
		if (sen_pic_or_feature)  //����Ƭ�·�����id
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
						ui.textEdit->append(QString::fromLocal8Bit("ע��ɹ���ע��IDΪ��") + QString::number(cur_id));
						newParseRec.clear();
						emit finished();
						break;
					}
					if (cur_id == -1)
					{
						saveLog(currentFileName, cur_id);
						ui.textEdit->append(QString::fromLocal8Bit("ע��ʧ�ܣ�ע��IDΪ��") + QString::number(cur_id));
						newParseRec.clear();
						emit finished();
						break;
					}
					if (cur_id == -2)
					{
						saveLog(currentFileName, cur_id);
						ui.textEdit->append(QString::fromLocal8Bit("ע��ʧ�ܣ�ע��IDΪ��") + QString::number(cur_id));
						newParseRec.clear();
						emit finished();
						break;
					}
				}
			}
		}
		else//�������ļ�����id  
		{
			//sync(2B)  msgid(1B)       len(4B)       cmd(1B)result(1B)         id(4B)   checksum(1B)
			//0xef  0xaa  0x00  0x00  0x00  0x00  0x06  0x15  0x00  0x00  0x00  0x00  0x01  0x1a
			if (newParseRec.at(i) == compareArray[0] && newParseRec.at(i + 1) == compareArray[1] && newParseRec.at(i + 2) == compareArray[4])
			{
				char cal_check_sum = std::accumulate(/*newParseRec.at(i + 7)*/newParseRec.data() + i + 2, newParseRec.data() + i + 13, 0);
				if (newParseRec.at(i + 13) == cal_check_sum)
				{
					if (newParseRec.at(i + 8) == compareArray[4])   //ע��ɹ�
					{
						id_vec[0] = newParseRec.at(i + 9);
						id_vec[1] = newParseRec.at(i + 10);
						id_vec[2] = newParseRec.at(i + 11);
						id_vec[3] = newParseRec.at(i + 12);
						int fea_id = reverse_uint32(id_vec);
						saveLog(currentFileName, fea_id);
						ui.textEdit->append(QString::fromLocal8Bit("ע��ɹ���ע��IDΪ��") + QString::number(fea_id));
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
						ui.textEdit->append(QString::fromLocal8Bit("ע��ʧ�ܣ�ע��IDΪ��") + QString::number(fea_id));
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
	sen_pic_or_feature = true;   //����ͼƬ��true������������false
	char compareArray[3] = { 0xef, 0xaa, 0xb1 };
	char sed_check[12] = { 0 };
	int pic = 1;
	files.clear();
	QDir dir(fileName);
	ui.textEdit_2->append(QString::fromLocal8Bit("��·����") + fileName);
	qint32 count = dir.count();
	for (int i = 0; i < count; i++)
	{
		QString file_name = dir[i];
		files.push_back(file_name);
		ui.textEdit_2->append(QString::fromLocal8Bit("�ļ���") + file_name);
	}
	uint8_t rec_buf[4] = { 0 };
	if (files.count() > 2)
	{
		QEventLoop loop;
		connect(this, SIGNAL(finished()), &loop, SLOT(quit()));
		for (int i = 2; i < files.count(); i++)
		{
			flag = true;
			//qt���ļ�����
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
			
			//m_serialPort->waitForBytesWritten(10000);    //ȷ���������

			currentFileName = files[i];

			ui.textEdit->append(QString::fromLocal8Bit("����ͼƬ����")+ QString::number(pic));
			pic++;
			loop.exec();
		}
	}
}

//д�������� ��Ƭ���������� 
void SendJpgDemo::sendInfo(/*QString path*/)
{
	char compareArray[3] = { 0xef, 0xaa, 0xb1 };
	char sed_check[12] = { 0 };
	int pic = 1;
	files.clear();
	QDir dir(fileName);
	ui.textEdit_2->append(QString::fromLocal8Bit("��·����") + fileName);
	qint32 count = dir.count();
	for (int i = 0; i < count; i++)
	{
		QString file_name = dir[i];
		files.push_back(file_name);
		ui.textEdit_2->append(QString::fromLocal8Bit("�ļ���") + file_name);
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
			//qt���ļ�����
			char send_buf[1024 * 200] = { 0 };
			//char *send_buf = (char *)malloc(1024 * 1024 * 2);//2M
			QFile file(fileName + "/" + files[i]);
			file.open(QIODevice::ReadOnly/* | QIODevice::Text*/);
			QByteArray t = file.readAll();
			file.close();
			info.clear();
			//qtд�ļ�����
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



			//�¼�ͬ��/*******************/
			m_serialPort->waitForBytesWritten(10000);    //ȷ���������


			currentFileName = files[i];   

			/*******************************/
			ui.textEdit->append(QString::fromLocal8Bit("����ͼƬ����"));
			ui.textEdit->append(QString::number(pic));
			pic++;

			
			/**********************************/
			//m_port->waitForReadyRead(10000)���京��Ϊ�ȴ��Է����ʹ������ݹ���������Է����ʹ������ݹ����ˣ�������true��Ȼ��ʹ��m_port->readAll��ȡ�������ݣ�����Է���3���ڶ�û�з��ʹ������ݹ�����������false���˳�ѭ����
			while (m_serialPort->waitForReadyRead(10000))
			{
				
				//info = m_serialPort->readAll(); //��ȡ��������
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
							//У��Ͳ��Ի�����λ�����յ����ݲ�����������3��ͼƬ�����ش�
							if (ID == -1)   //-1Ϊ0xff,0xff,0xff,0xffУ���ʧ�ܣ�˵��ͼƬ����������
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
													//ID = newID;    //����ID
													record = 0;  //�����ش�
													break;
												}
												else
												{
													if (newID == -1 && record != 0)     //�յ�-1ʱ������У���ʧ�ܣ���Ҫ�ش�����recordΪ���һ���ش���ʱ���������-1���ͽ������¼ΪУ���ʧ��
													{
														//saveLog(currentFileName, -1);
														break;
													}
													if (newID == -1 && record == 0)
													{
														saveLog(currentFileName, -1);
														break;
													}
													if (newID == -2)    //-2Ϊ0xff,0xff,0xff,0xfeע��ʧ�ܣ�˵��ͼƬ����û����
													{
														saveLog(currentFileName, -2);
														record = 0;		//�����ش�
														break;
													}
												}
												
											}
										}
										else    //����ش�3�ζ�û���յ����ͼ�¼Ϊ-1
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
							if (ID == -2)   //-2Ϊ0xff,0xff,0xff,0xfeע��ʧ��
							{
								saveLog(currentFileName, -2);
								break;
							}
							//saveLog(currentFileName, -1);
						}
						ui.textEdit->append(QString::fromLocal8Bit("�յ�ACK"));
						//break;
					}
				}
				//���ڶ�ȡ�������ˣ���������û��ȫ����ʧ�˼����ֽڵ����
				//else
				//{
				//	checkID(sed_check);
				//	m_serialPort->write(sed_check, 4);   //�·���ѯ����
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
				//				ui.textEdit->append(QString::fromLocal8Bit("�յ���ѯ�ظ�"));
				//				break;
				//			}
				//		}
				//	}
				//}
			}

			//һ�����ݶ�û�յ�����������ȫ����ʧ��������յ����ݲ���������ʧ�������ݲ���11�ֽ����
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
					m_serialPort->write(sed_check, 8);   //�·���ѯ����
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
						//		int checkID = reverse_uint32(rec_checkBuf);  //checkIDΪ��λ�����һ�γɹ���ID
						//		if (checkID >= 0 && checkID > ID)  
						//		{
						//			saveLog(currentFileName, checkID);
						//		}
						//		if (checkID >= 0 && checkID == ID)   //ע��ʧ��
						//		{
						//			saveLog(currentFileName, -2);
						//		}
						//		if (checkID == -1)   //У���ʧ��
						//		{
						//			saveLog(currentFileName, -1);
						//		}
						//		if (checkID == -2)		//ע��ʧ��
						//		{
						//			saveLog(currentFileName, -2);
						//		}
						//		
						//		ui.textEdit->append(QString::fromLocal8Bit("�յ���ѯ�ظ�"));
						//		count = 0;
						//		break;
						//	}
						//}
						//else
						//{
						//	saveLog(currentFileName, 65565);   //��ѯ��Ч
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
							int checkID = reverse_uint32(rec_checkBuf);  //checkIDΪ��ǰ��ID
							if (checkID >= 0/* && checkID > ID*/)
							{
								saveLog(currentFileName, checkID);
							}
							//if (checkID >= 0 && checkID == ID)   //ע��ʧ��
							//{
							//	saveLog(currentFileName, -2);
							//}
							if (checkID == -1)   //У���ʧ��
							{
								saveLog(currentFileName, -1);
							}
							if (checkID == -2)		//ע��ʧ��
							{
								saveLog(currentFileName, -2);
							}

							ui.textEdit->append(QString::fromLocal8Bit("�յ���ѯ�ظ�"));
							count = 0;
							break;
						}
					}
					else
					{
						saveLog(currentFileName, 65565);   //��ѯ��Ч
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
					//		ui.textEdit->append(QString::fromLocal8Bit("�յ���ѯ�ظ�"));
					//		break;
					//	}
					//}
				} while (count--);
			}
			

			
			//���3s��û�յ��Ļ������Կ�����λ��Ҳ����ACK�ˣ������ڷ��͵�ʱ��ʧ�ˡ������ղ�����Ҫ�ش���
			/**********************************************/



			//������֮ǰ����
			//QEventLoop loop;
			//connect(/*m_serialPort*/this, SIGNAL(finishedInfo()), &loop, SLOT(quit()));
			//loop.exec();
			

			//ui.textEdit->append(QString::fromLocal8Bit("����ͼƬ����"));
			//ui.textEdit->append(QString::number(pic));
			//pic++;
		}
	}
}
//������д����
void SendJpgDemo::sendInfo(const QString &info)
{

	QByteArray sendBuf;
	if (info.contains(" "))
	{
		return;
		//info.replace()
		//info.replace(QString(""), QString(""));//�������ǰѿո�ȥ�����������Ƕ���Э����
	}
	//convertStringToHex(info, sendBuf); //��QString ת�� Ϊ hex 
	sendBuf = info.toLatin1();
	m_serialPort->write(sendBuf); //����������ĸ���Ƭ�������� �õ�����QIODevice::write ������Կ��ĵ�

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
//ѡ�������ļ���
void SendJpgDemo::on_pushButton_7_clicked()
{
	feature_dir = QFileDialog::getExistingDirectory(this, "Choose Feature Directory",
		"/");
	ui.lineEdit_2->setText(feature_dir);
}
//�·������ļ�
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
		ui.textEdit_2->append(QString::fromLocal8Bit("�ļ���:") + file_name);
	}
	if (files.count() > 2)
	{
		QEventLoop loop;
		connect(this, SIGNAL(feature_fini()), &loop, SLOT(quit()));
		for (int i = 2; i < files.count(); i++)
		{
			//flag = true;
			//qt���ļ�����
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

			ui.textEdit->append(QString::fromLocal8Bit("���������ļ�����") + QString::number(pic));
			pic++;
			loop.exec();
		}
	}
}