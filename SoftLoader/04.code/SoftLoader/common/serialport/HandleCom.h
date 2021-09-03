#pragma once

#include "../datastruct/DataStruct_anc_eq.h"

#include <QObject>
#include <QtSerialPort/QSerialPort>
//class QSerialPort;

struct COM_INFO   //串口结构体
{
	COM_INFO()
	{
		baudRate = static_cast<QSerialPort::BaudRate>(500000);
		dataBits = QSerialPort::Data8;
		stopBits = QSerialPort::OneStop;
		parity = QSerialPort::NoParity;
		direction = QSerialPort::AllDirections;
		flowCtrl = QSerialPort::NoFlowControl;
	}
	COM_INFO& operator=(const COM_INFO& temp)
	{
		this->strComName = temp.strComName;
		this->baudRate = temp.baudRate;
		this->dataBits = temp.dataBits;
		this->direction = temp.direction;
		this->flowCtrl = temp.flowCtrl;
		this->parity = temp.parity;
		this->stopBits = temp.stopBits;
		return *this;
	}
	QString strComName;						//串口名称
	QSerialPort::BaudRate baudRate;			//波特率
	QSerialPort::DataBits dataBits;			//数据位
	QSerialPort::Direction direction;		//数据方向
	QSerialPort::FlowControl flowCtrl;		//流控制
	QSerialPort::Parity parity;				//奇偶校验位
	QSerialPort::StopBits stopBits;			//停止位
};

class HandleCom : public QObject
{
	Q_OBJECT

public:
	HandleCom(QObject *parent = nullptr, int nPowerOfTwo = 27);
	~HandleCom();
	QStringList getAvailablePorts();		//获取可用串口列表
	bool initPort();	//初始化串口
	bool writeData(unsigned char* pData, int nSize);	//将数据写入串口
	void setComParam(const COM_INFO & temp);
	//打开串口
	bool openCom();
	//关闭串口
	void closeCom();

	int sendData(const QByteArray & sendData);
	int sendData(const QVector<IIR_INFO> & vec);
	int sendData(const QVector<IIR_INFO> &vec, unsigned char nMsgID);
	int sendData(const QVector<IIR_INFO> & vec_ff, const QVector<IIR_INFO> & vec_fb);

public slots:
	void slot_recv_data();		//接收串口的消息

signals:
	void sig_send_data(QByteArray strData);
private:
	//计算奇偶校验位
	unsigned short calcCheckSum(unsigned char *pData, int nSize);
	unsigned short calcCheckSum(unsigned short *pData, int nSize);

private:
	QSerialPort* m_pSerialPort;
	bool m_bRecvHex;			//接收的数据是否是16进制数
	COM_INFO m_com_param;
	int m_nPowerOfTwo;
};
