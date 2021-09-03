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
	QByteArray rec_data_connect;   //��������
	QByteArray rec_data;
	int file_len;
	QByteArray file_data;
	void initSerialPort();
	QStringList getPortNameList();
	void connectFun();
	void record_log(QString path, QString send_info, QString sendOrRec);
	bool communicate();   //����
	int readProgrammerBl(/*QByteArray &read_data*/);  //��ȡ512K����
	//bool erase();     //��������
	void erase_once(int count);		//����һ��64k
	bool writeProgrammer();		//дҳ
	uint16_t computeCheckSum(uint8_t *data, uint16_t size);
	QString filePath;  //ѡ���ļ�·��

	bool isEraseOver;

private slots:
	void recData();
	void on_pushButton_clicked();
	void on_pushButton_2_clicked();
	bool erase();     //��������
signals:
	void run_erase();
	void next_erase();
	void next_write();

};
