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

	void slot_btn_1();		//音量配置
	void slot_btn_2();		//充电配置
	void slot_btn_3();		//充电配置恢复默认值
	void slot_btn_4();		//蓝牙配置
	void slot_btn_5();		//蓝牙配置恢复默认值
	void slot_btn_6();		//按键配置
	void slot_btn_7();		//连接
	void slot_btn_8();		//关闭
	void slot_btn_9();		//保存当前配置

	void slot_port_recv();

private:
	void initCmbPort();
	bool readConfig();		//读取配置

private:
	Ui::ConfItemWgt ui;
	QSerialPort* m_pSerialPort;
	///音量配置
	int m_volume_default;				//系统默认音量
	int m_volume_tips;					//提示音音量
	///充电配置
	double m_charge_full_voltage;		//充电满电压
	int m_charge_full_current;				//充电满电流
	int m_charge_current;						//充电电流
	double m_low_voltage_tips;			//低电压提醒电压配置
	double m_low_shut_down;				//低电关机电压设置
	///蓝牙配置
	QString m_bluetooth_name;			//蓝牙名称
	unsigned char m_bluetooth_mac_addr[6];	//蓝牙mac地址
	int m_bluetooth_send_freq;				//发射频率
	int m_bluetooth_tm;							//未连接自动关机配置
	//按键配置
	int m_nKeySum;
	unsigned char m_nKeyFun[10];

	QVector<QComboBox*> m_cmb_group;
};
