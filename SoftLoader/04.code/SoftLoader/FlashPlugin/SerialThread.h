#pragma once

#include <QObject>
#include "def.h"


class QSerialPort;
class QTimer;

class SerialThread : public QObject
{
	Q_OBJECT

public:
	SerialThread(QObject *parent = nullptr);
	~SerialThread();
	bool init_port();		//初始化串口
	void setPortName(QString strSrialName);
	void setFristBin(QByteArray &firstBin);
	void setSecondBin(QByteArray &secondBin, int nLen);

	void reset();

private:
	void handle_process(unsigned char nCmd);		//根据指令处理逻辑
	
	void write_second_bin_process();
	uint16_t computeCheckSum(uint8_t *data, uint16_t size);

	

signals:
	void sig_status(BURN_STATE nState, float nVal = 0);
	void sig_log(QString strLog);
	void thread_sig();
	void run_erase();
	void next_erase();
	void next_write();
	void sig_thread_finished();
	

public slots:
	void slot_init_port();
	void slot_start();
	void slot_handle_data();
	void slot_write_data();
	//void slot_timeout();
	void erase_process();

private:
	QThread *m_thread;
	QSerialPort *m_port;
	QTimer *m_timer;

	int m_serial_baud_rate;
	QString m_strPortName;
	volatile bool m_bStartTm;
	volatile BURN_STATE m_burn_state;
	QByteArray m_array_first_bin;
	QByteArray m_array_second_bin;
	int m_secondBin_length;

	QByteArray m_recv_data;
};
