#pragma once

#include "../datastruct/DataStruct_anc_eq.h"

#include <QObject>
#include <QtSerialPort/QSerialPort>
//class QSerialPort;

struct COM_INFO   //���ڽṹ��
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
	QString strComName;						//��������
	QSerialPort::BaudRate baudRate;			//������
	QSerialPort::DataBits dataBits;			//����λ
	QSerialPort::Direction direction;		//���ݷ���
	QSerialPort::FlowControl flowCtrl;		//������
	QSerialPort::Parity parity;				//��żУ��λ
	QSerialPort::StopBits stopBits;			//ֹͣλ
};

class HandleCom : public QObject
{
	Q_OBJECT

public:
	HandleCom(QObject *parent = nullptr, int nPowerOfTwo = 27);
	~HandleCom();
	QStringList getAvailablePorts();		//��ȡ���ô����б�
	bool initPort();	//��ʼ������
	bool writeData(unsigned char* pData, int nSize);	//������д�봮��
	void setComParam(const COM_INFO & temp);
	//�򿪴���
	bool openCom();
	//�رմ���
	void closeCom();

	int sendData(const QByteArray & sendData);
	int sendData(const QVector<IIR_INFO> & vec);
	int sendData(const QVector<IIR_INFO> &vec, unsigned char nMsgID);
	int sendData(const QVector<IIR_INFO> & vec_ff, const QVector<IIR_INFO> & vec_fb);

public slots:
	void slot_recv_data();		//���մ��ڵ���Ϣ

signals:
	void sig_send_data(QByteArray strData);
private:
	//������żУ��λ
	unsigned short calcCheckSum(unsigned char *pData, int nSize);
	unsigned short calcCheckSum(unsigned short *pData, int nSize);

private:
	QSerialPort* m_pSerialPort;
	bool m_bRecvHex;			//���յ������Ƿ���16������
	COM_INFO m_com_param;
	int m_nPowerOfTwo;
};
