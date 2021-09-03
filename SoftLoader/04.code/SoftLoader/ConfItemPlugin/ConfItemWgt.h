#pragma once

#include <QWidget>
#include <QVector>
#include "ui_ConfItemWgt.h"

class QSerialPort;

class ConfItemWgt : public QWidget
{
	Q_OBJECT

public:
	ConfItemWgt(QWidget *parent = Q_NULLPTR);
	~ConfItemWgt();

public slots:
	void slot_cmb_port_init();

	void slot_btn_1();		//��������
	void slot_btn_2();		//�������
	void slot_btn_3();		//������ûָ�Ĭ��ֵ
	void slot_btn_4();		//��������
	void slot_btn_5();		//�������ûָ�Ĭ��ֵ
	void slot_btn_6();		//��������
	void slot_btn_7();		//����
	void slot_btn_8();		//�ر�
	void slot_btn_9();		//���浱ǰ����

	void slot_port_recv();

private:
	void initCmbPort();
	bool readConfig();		//��ȡ����

private:
	Ui::ConfItemWgt ui;
	QSerialPort* m_pSerialPort;
	///��������
	int m_volume_default;				//ϵͳĬ������
	int m_volume_tips;					//��ʾ������
	///�������
	double m_charge_full_voltage;		//�������ѹ
	int m_charge_full_current;				//���������
	int m_charge_current;						//������
	double m_low_voltage_tips;			//�͵�ѹ���ѵ�ѹ����
	double m_low_shut_down;				//�͵�ػ���ѹ����
	///��������
	QString m_bluetooth_name;			//��������
	unsigned char m_bluetooth_mac_addr[6];	//����mac��ַ
	int m_bluetooth_send_freq;				//����Ƶ��
	int m_bluetooth_tm;							//δ�����Զ��ػ�����
	//��������
	int m_nKeySum;
	unsigned char m_nKeyFun[10];

	QVector<QComboBox*> m_cmb_group;
};
