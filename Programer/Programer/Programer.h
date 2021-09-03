#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Programer.h"
#include <qserialport.h>
#include <qserialportinfo.h>
class Programer : public QMainWindow
{
    Q_OBJECT

public:
    Programer(QWidget *parent = Q_NULLPTR);
	~Programer();

private:
    Ui::ProgramerClass ui;
	const char *cmd_first;
	QSerialPort *m_serialPort_1;
	QSerialPort *m_serialPort_2;
	QSerialPort *m_serialPort_3;
	QSerialPort *m_serialPort_4;
	QSerialPort *m_serialPort_5;
	QSerialPort *m_serialPort_6;
	QSerialPort *m_serialPort_7;
	QSerialPort *m_serialPort_8;
	QByteArray rec_port1;
	QByteArray rec_data_connect;   //串口握手
	QByteArray rec_data;
	int file_len;
	QByteArray file_data;
	void initSerialPort();
	QStringList getPortNameList();
	void connectFun();
	void record_log(QString path, QString send_info, QString sendOrRec);
	bool communicate();   //握手
	int readProgrammerBl(/*QByteArray &read_data*/);  //读取512K程序
	//bool erase();     //擦除程序
	void erase_once(int count);		//擦除一次64k
	bool writeProgrammer();		//写页
	uint16_t computeCheckSum(uint8_t *data, uint16_t size);
	QString filePath;  //选择文件路径

	bool isEraseOver;

private slots:
	void recData();
	void on_pushButton_clicked();
	void on_pushButton_2_clicked();
	bool erase();     //擦除程序
signals:
	void run_erase();
	void next_erase();
	void next_write();

};
