#pragma once

#include <QWidget>
#include "ui_SingleWgt.h"
#include "def.h"

class SerialThread;

class SingleWgt : public QWidget
{
	Q_OBJECT

public:
	SingleWgt(QWidget *parent = Q_NULLPTR);
	~SingleWgt();
	void setFirstBin(QByteArray & firstBin);
	void setSecondBin(QByteArray & secondBin, int nLen);
	//绑定串口
	bool bindPort(QString strCom);
	//开始烧写
	void startProcess();
	//设置烧写状态
	void setProcessState(int nState);

	void initUI();

private:
	void reset();

signals:
	void sig_loop_quit();		//自我循环等待
	void sig_init();		//初始化线程串口
	void sig_start();	//开始烧写信号
	void sig_burn_finished();		//烧写完成信号
	
public slots:
	//设置界面流程状态灯
	void slot_thread_port_status(BURN_STATE nStatus, float nValProcess = 0);
private:
	Ui::SingleWgt ui;
	SerialThread* m_pSerialPort;			//串口线程
	QByteArray m_array_first_bin;
	QByteArray m_array_second_bin;
	int m_second_bin_length;
	BURN_STATE m_state;			//烧写流程状态
};
