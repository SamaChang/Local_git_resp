#pragma once

#include <QtWidgets/QWidget>
#include "ui_SendJpgDemo.h"
#include <qcombobox.h>
#include <QtSerialPort/qserialport.h>
#include <QtSerialPort/qserialportinfo.h>
#include <thread>
#include <qfiledialog.h>
#include <qtimer.h>

class SendJpgDemo : public QWidget
{
    Q_OBJECT

public:
    SendJpgDemo(QWidget *parent = Q_NULLPTR);
	~SendJpgDemo();

private:
    Ui::SendJpgDemoClass ui;
	QSerialPort *m_serialPort;
	//QComboBox *combox;
	std::thread recData;
	QString fileName;  //打开文件路径
	QStringList filter;  //文件名
	QVector<QString>files;
	QString currentFileName;
	char convertCharToHex(char ch);
	void convertStringToHex(const QString &str, QByteArray &byteData);
	void sendInfo(/*char* info, int len*/);
	void sendInfo(const QString &info);
	QStringList getPortNameList();//获取所有可用的串口列表
	QStringList m_portNameList;
	QByteArray info;  //接受串口数据
	QByteArray recID;
	QByteArray timeoutSend;

	QByteArray newParseRec;
	QTimer *timer;

	QString feature_dir;

	bool sen_pic_or_feature;

	bool flag;
	void newSendInfo();
	void initSeri();
private slots:
	void on_pushButton_clicked();
	void on_pushButton_2_clicked();
	void on_pushButton_3_clicked();
	void on_pushButton_4_clicked();
	void on_pushButton_5_clicked();
	void on_pushButton_6_clicked();
	void on_pushButton_7_clicked();
	void receiveInfo();
	void selectFile();
	void serialPortList();
	void serialReads();
	void timerDelay();
	
	void parse_rec();
signals:
	void finishedInfo();
	void finished();
	void feature_fini();
};
