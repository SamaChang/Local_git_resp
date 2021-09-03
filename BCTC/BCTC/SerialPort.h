#pragma once
#include <qobject.h>
#include <qserialport.h>
#define REC_PACEKT   1024*1024
class SerialPort :
	public QObject
{
	Q_OBJECT
public:
	SerialPort();
	~SerialPort();
	void send_serial_data(unsigned char *packet, unsigned int size, QSerialPort *ser);
	QSerialPort *serial_port;    //下位机通信串口
	QSerialPort *another_pc;     //与另一台机器通信串口
	bool sendPicOrCmd;
	void connectSig();
	
	QStringList getPortNameList();
	void initSerialPort(QSerialPort *serial, QString name);
private:
	//QSerialPort *serial_port;
	//void initSerialPort(QString name);
	QStringList m_serialPortName;
	void rec_cmd_data(/*QByteArray rec*/);
	void rec_pic_result_data(/*QByteArray rec*/);
	void rec_pc_serial_cmd(QByteArray rec);
	void closeSerialPort(QSerialPort *ser);
	QByteArray rec;
	QByteArray rec_anther_pc;
private slots:
	void read_serial_data();
	void rec_test_pc();
signals:
	void finished();
	void usb_send(bool);
	void finished_pic_send();
	void toSavePic(int);
	void toSendUsbCmd();
	void send_pc_result(bool);
};

