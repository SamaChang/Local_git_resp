#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_FlashSoft.h"

#include <QStringList>
#include <QFile>
#include <QTextStream>
#include <QSerialPort>
#include "def.h"

constexpr auto SERIAL_PORT_COUNT = 8;

class FlashSoft : public QMainWindow
{
	Q_OBJECT

public:
	FlashSoft(QWidget *parent = Q_NULLPTR);
	~FlashSoft();

private:

	enum LOG_STATUS
	{
		LOG_SEND,
		LOG_RECV
	};

	

	bool initLog();
	void uintLog();
	void initSerialPort();
	QStringList getPortNameList();
	void connectFun();
	void record_log(QString path, QString send_info, QString sendOrRec);
	void record_log(LOG_STATUS status, QString send_info);
    bool communicate();   //握手
    int readProgrammerBl(/*QByteArray &read_data*/);  //读取512K程序,返回文件的长度
    //bool erase();     //擦除程序
    void erase_once(int count);		//擦除一次64k
    bool writeProgrammer();		//写页
	uint16_t computeCheckSum(uint8_t *data, uint16_t size);

	//加载初始化Bin文件
	bool loadInitBin();

private slots:
	void recData();
	void on_pushButton_clicked();
	void on_pushButton_2_clicked();
	void on_pushButton_3_clicked();
    bool erase();     //擦除程序
signals:
	void run_erase();
	void next_erase();
	void next_write();

private:
	Ui::FlashSoftClass ui;
	BURN_STATE m_burn_state;
	//接收串口数据
	QByteArray m_recv_data;

	//日志
	QFile m_logFile;
	QTextStream m_logStream;
	bool m_bLog;

	QSerialPort *m_serialPort_1;
	QSerialPort *m_serialPort_2;
	QSerialPort *m_serialPort_3;
	QSerialPort *m_serialPort_4;
	QSerialPort *m_serialPort_5;
	QSerialPort *m_serialPort_6;
	QSerialPort *m_serialPort_7;
	QSerialPort *m_serialPort_8;

	QByteArray rec_port1;
	int file_len;
	QByteArray file_data;
    QString filePath;  //选择文件路径
	bool isEraseOver;

	bool m_bHandShake[SERIAL_PORT_COUNT];		//标识握手状态
	QSerialPort* m_pSerialPorts[SERIAL_PORT_COUNT];	//串口接口
	QByteArray m_init_bin;
};
