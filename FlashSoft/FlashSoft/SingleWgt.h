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
	//�󶨴���
	bool bindPort(QString strCom);
	//��ʼ��д
	void startProcess();
	//������д״̬
	void setProcessState(int nState);

	void initUI();

private:
	void reset();

signals:
	void sig_loop_quit();		//����ѭ���ȴ�
	void sig_init();		//��ʼ���̴߳���
	void sig_start();	//��ʼ��д�ź�
	void sig_burn_finished();		//��д����ź�
	
public slots:
	//���ý�������״̬��
	void slot_thread_port_status(BURN_STATE nStatus, float nValProcess = 0);
private:
	Ui::SingleWgt ui;
	SerialThread* m_pSerialPort;			//�����߳�
	QByteArray m_array_first_bin;
	QByteArray m_array_second_bin;
	int m_second_bin_length;
	BURN_STATE m_state;			//��д����״̬
};
