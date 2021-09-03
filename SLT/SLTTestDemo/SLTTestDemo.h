#pragma once

#include <QtWidgets/QWidget>
#include "ui_SLTTestDemo.h"
#include <QtSerialPort/qserialport.h>
#include <QtSerialPort/qserialportinfo.h>
#include <thread>
//#include "GPIBConnect.h"
//#include <qsettings.h>
//#include <qvariant.h>
#include <visa.h>
#include <visatype.h>
#include <mutex>
#include <condition_variable>
#include <qtimer.h>
#include <qdatetime.h>
#include "GPIBSet.h"
class SLTTestDemo : public QWidget
{
    Q_OBJECT

public:
    SLTTestDemo(QWidget *parent = Q_NULLPTR);
	SLTTestDemo(int a);
	~SLTTestDemo();

private:
    Ui::SLTTestDemoClass ui;
	QTimer *m_timer1;
	QTimer *m_timer2;
	QTimer *m_timer3;
	QTimer *m_timer4;
	QSerialPort *m_serialPort1;
	QSerialPort *m_serialPort2;
	QSerialPort *m_serialPort3;
	QSerialPort *m_serialPort4;
	//QByteArray rec_info;
	QString fileName;
	void initSerialPort(/*QSerialPort *sp*/);
	void recDataParse(char *packet, QTableWidget *tb/*,int id*/);
	//void serialPortSend(QSerialPort *sp/*,int num*/);
	void serialPortSend1();
	void serialPortSend2();
	void serialPortSend3();
	void serialPortSend4();
	QStringList getPortNameList();
	void setTableWidget(QTableWidget *tb);   //��ȡ�����ļ�
	void saveTableToFile(QTableWidget *tb);  //����������ļ�
	std::thread *t1;
	std::thread *t2;
	std::thread *t3;
	std::thread *t4;

	std::thread *tControl;

	void stopSerialPort(QSerialPort *qsp, std::thread *t);
	bool stopThread1;
	bool stopThread2;
	bool stopThread3;
	bool stopThread4;
	bool stopAutoTest;
	void recordLog(QString saveLogName/*, QString send_info, QString rec_info*/);//���������Ϣ
	void send_rec(QString path, QString send_info, QString sendOrRec);
	QString filePath;
	QByteArray rec_info1;
	QByteArray rec_info2;
	QByteArray rec_info3;
	QByteArray rec_info4;

	void clearConnent(QTableWidget *table);  //ÿ�β���������֮ǰ�Ľ��

	//QSettings *setting;
	//QVariant getSetting(QString qstrnodename, QString qstrkeyname);
	//GPIBConnect gpibConnect;
	
	//static char instrDescriptor[VI_FIND_BUFLEN];
	//static ViUInt32 numInstrs;
	//static ViFindList findList;
	//static ViSession defaultRM, instr;
	//static ViStatus status;
	int findRsrc();
	void connectGpib();
	void binON(/*bool bin1, bool bin2, bool bin3, bool bin4*/);
	void control();
	void openGpib();

	bool isComplete1;
	bool isComplete2;
	bool isComplete3;
	bool isComplete4;

	bool closeControl;

	QString time_creatFile;
	GPIBSet *set_gpib;
	//QString gpib_name;

	void saveCSVFlie();
	void saveConnent(QString chipID, QString err, QString errInfo, QString socket, QString time);
	void creatPassRate();  //������������.csvFile Chip" << "," << "All Chip" << "," << "Pass Rate"
	void savePassRate(QString fail,QString all,QString passRate);  //��������
	//void saveFail(QString fail);  //���������
	//void saveFail(QString all);  //��������
	//void saveFail(QString passRate);  //��������

	std::condition_variable m_condition;
	std::mutex m_mutex;
	std::condition_variable cond;
	std::mutex mut;

	//QEventLoop loop1;
	//QEventLoop loop2;
	//QEventLoop loop3;
	//QEventLoop loop4;

	//static int serial1_cmd;
	//static int serial2_cmd;
	//static int serial3_cmd;
	//static int serial4_cmd;

	//static int chipID1;
	//static int chipID2;
	//static int chipID3;
	//static int chipID4;

	void stopQtimer(QTimer *timer);

	//bool timerFlag;

	bool bin_good_1;
	bool bin_good_2;
	bool bin_good_3;
	bool bin_good_4;


	//MSG msg1;
	//MSG msg2;
	//MSG msg3;
	//MSG msg4;
	//int iId;
	
private slots:
	void on_pushButton_clicked();
	void on_pushButton_2_clicked();
	void on_pushButton_3_clicked();
	void on_pushButton_4_clicked();
	void receiveInfo1(/*int i*/);
	void receiveInfo2(/*int i*/);
	void receiveInfo3(/*int i*/);
	void receiveInfo4(/*int i*/);
	void timeRun1(/*QSerialPort *m_serial*/);   //�涨���۵Ĳ������ܶ����źŵĲ���
	void timeRun2(/*QSerialPort *m_serial*/);   //�涨���۵Ĳ������ܶ����źŵĲ���
	void timeRun3(/*QSerialPort *m_serial*/);   //�涨���۵Ĳ������ܶ����źŵĲ���
	void timeRun4(/*QSerialPort *m_serial*/);   //�涨���۵Ĳ������ܶ����źŵĲ���

	void qtimerRun1();
	void qtimerRun2();
	void qtimerRun3();
	void qtimerRun4();

	void lcdCount();   //ˢ��LCDcount

	void pushbutton3disable();
	//void getGPIB_name(QString name);
signals:
	//void finishedInfo(/*int*//* num*/);
	void finishedInfo1();
	void finishedInfo2();
	void finishedInfo3();
	void finishedInfo4();
	//void finishedInfoControl();
	//void fini1();
	//void fini2();
	//void fini3();
	//void fini4();
	void runT1();
	void runT2();
	void runT3();
	void runT4();

	void updateUI();    //���̵߳Ľ������ͨ���źŲ������߳��и���

	void pushButton_3_disable();
};
