#include "HandleCom.h"
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>
#include <math.h>

//#include "Config.h"

HandleCom::HandleCom(QObject *parent, int nPowerOfTwo)
	: QObject(parent)
	, m_pSerialPort(new QSerialPort(this))
	, m_bRecvHex(false)
	, m_nPowerOfTwo(nPowerOfTwo)
{
	//串口接收
	connect(m_pSerialPort, &QSerialPort::readyRead, this, &HandleCom::slot_recv_data);
	//m_nPowerOfTwo = Config::getIns()->m_nPowerOfTwo;
}

HandleCom::~HandleCom()
{

}

QStringList HandleCom::getAvailablePorts()
{
	QStringList tempSerialPortList;
	qDebug() << "*******************************************";
    foreach (const QSerialPortInfo & var, QSerialPortInfo::availablePorts())
	{
		qDebug() << QStringLiteral("串口设备信息：") << var.portName();
		qDebug() << QStringLiteral("芯片/驱动名称：") << var.description();
		qDebug() << QStringLiteral("串口设备制造商：") << var.manufacturer();
		qDebug() << QStringLiteral("串口设备的序列号：") << var.serialNumber();
		qDebug() << QStringLiteral("串口设备的系统位置：") << var.systemLocation();

		//if (var.description() == "USB-SERIAL CH340")
		{
			tempSerialPortList << var.portName();
		}
	}
	return tempSerialPortList;
}

bool HandleCom::writeData(unsigned char* pData, int nSize)
{
	return true;
}

void HandleCom::setComParam(const COM_INFO & temp)
{
	m_com_param = temp;
	m_pSerialPort->setPortName(m_com_param.strComName);
	m_pSerialPort->setBaudRate(m_com_param.baudRate);
	m_pSerialPort->setDataBits(m_com_param.dataBits);
	m_pSerialPort->setStopBits(m_com_param.stopBits);
	m_pSerialPort->setParity(m_com_param.parity);
}

bool HandleCom::openCom()
{
	return m_pSerialPort->open(QIODevice::ReadWrite);
}

void HandleCom::closeCom()
{
	m_pSerialPort->close();
}

int HandleCom::sendData(const QByteArray & sendData)
{
	int nLen = m_pSerialPort->write(sendData);
	return nLen;
}

int HandleCom::sendData(const QVector<IIR_INFO> & vec)
{
	//组织报文
	SEND_INFO_MSG tempMsg;
	int nSubUint = sizeof(IIR_INFO);
	tempMsg.header.nSize = nSubUint*10;
	char tempData[1000];
	memset(tempData, 0, 1000);
	qDebug() << "---------------send data start-----------------";
	for (int i = 0; i < vec.size(); i++)
	{
		memcpy(&(tempMsg.cData[i]), (char*)&(vec.at(i)), sizeof(IIR_INFO));
		memcpy(tempData + i*nSubUint, (char*)&(vec.at(i)), sizeof(IIR_INFO));
		qDebug() << "b0:" << tempMsg.cData[i].b0 << " b1:" << tempMsg.cData[i].b1 << " b2:" << tempMsg.cData[i].b2 << " a0:" << tempMsg.cData[i].a0 << " a1:" << tempMsg.cData[i].a1 << " a2:" << tempMsg.cData[i].a2;
	}
	qDebug() << "---------------send data end-----------------";
	tempMsg.checkSum = calcCheckSum((unsigned char*)tempData, tempMsg.header.nSize);
	int nLen = m_pSerialPort->write((char*)&tempMsg, tempMsg.header.nSize+9);
	return nLen;
}

int HandleCom::sendData(const QVector<IIR_INFO> &vec, unsigned char nMsgID)
{
	//组织报文
	SEND_INFO_MSG tempMsg;
	int nSubUint = sizeof(IIR_INFO_INT);
	tempMsg.header.nSize = nSubUint * 10;
	tempMsg.header.msgID = nMsgID;
	
	if (nMsgID == MSG_SEND_ANC_TX_FB)
	{
		qDebug() << "*******************send msg anc.fb**********************\n";
	}
	else if (nMsgID == MSG_SEND_ANC_TX_FF)
	{
		qDebug() << "*******************send msg anc.ff**********************\n";
	}
	else if (nMsgID == MSG_SEND_EQ_TX)
	{
		qDebug() << "*******************send msg eq**********************\n";
	}
	else
	{
		qDebug() << "*******************unknown**********************\n";
	}

	for (int i = 0; i < vec.size(); i++)
	{
		IIR_INFO temp = vec.at(i);
		IIR_INFO_INT & subIIR = tempMsg.cData[i];
		subIIR.b0 = int(temp.b0*pow(2, m_nPowerOfTwo));
		subIIR.b1 = int(temp.b1*pow(2, m_nPowerOfTwo));
		subIIR.b2 = int(temp.b2*pow(2, m_nPowerOfTwo));
		subIIR.a0 = int(temp.a0*pow(2, m_nPowerOfTwo));
		subIIR.a1 = int(temp.a1*pow(2, m_nPowerOfTwo));
		subIIR.a2 = int(temp.a2*pow(2, m_nPowerOfTwo));
		qDebug() << i + 1 << "\t" << subIIR.b0 << "\t" << subIIR.b1 << "\t" << subIIR.b2 << "\t" << subIIR.a0 << "\t" << subIIR.a1 << "\t" << subIIR.a2 << "\n";
	}
	qDebug() << "*************************************************************\n";

	tempMsg.checkSum = calcCheckSum((unsigned char*)&tempMsg+4, SEND_INFO_MSG_LEN-6);
	tempMsg.reset();
	char tempData[1000];
	memset(tempData, 0, 1000);
	memcpy(tempData, &tempMsg, SEND_INFO_MSG_LEN);
	int nLen = m_pSerialPort->write(tempData, SEND_INFO_MSG_LEN);
	return nLen;
}

int HandleCom::sendData(const QVector<IIR_INFO> & vec_ff, const QVector<IIR_INFO> & vec_fb)
{
	//组织报文
	ANC_INFO_MSG tempMsg;
	int nSubUint = sizeof(IIR_INFO);
	tempMsg.header.nSize = nSubUint * 10;
	char tempData[1000];
	memset(tempData, 0, 1000);
	qDebug() << "---------------send data start FF-----------------";
	for (int i = 0; i < vec_ff.size(); i++)
	{
		memcpy(&(tempMsg.cData_FF[i]), (char*)&(vec_ff.at(i)), sizeof(IIR_INFO));
		memcpy(tempData + i * nSubUint, (char*)&(vec_ff.at(i)), sizeof(IIR_INFO));
		qDebug() << "b0:" << tempMsg.cData_FF[i].b0 << " b1:" << tempMsg.cData_FF[i].b1 << " b2:" << tempMsg.cData_FF[i].b2 << " a0:" << tempMsg.cData_FF[i].a0 << " a1:" << tempMsg.cData_FF[i].a1 << " a2:" << tempMsg.cData_FF[i].a2;
	}
	qDebug() << "---------------send data end FF-----------------";

	qDebug() << "---------------send data start FB-----------------";
	for (int i = 0; i < vec_ff.size(); i++)
	{
		memcpy(&(tempMsg.cData_FB[i]), (char*)&(vec_fb.at(i)), sizeof(IIR_INFO));
		memcpy(tempData + i * nSubUint, (char*)&(vec_fb.at(i)), sizeof(IIR_INFO));
		qDebug() << "b0:" << tempMsg.cData_FB[i].b0 << " b1:" << tempMsg.cData_FB[i].b1 << " b2:" << tempMsg.cData_FB[i].b2 << " a0:" << tempMsg.cData_FB[i].a0 << " a1:" << tempMsg.cData_FB[i].a1 << " a2:" << tempMsg.cData_FB[i].a2;
	}
	qDebug() << "---------------send data end FB-----------------";

	tempMsg.checkSum = calcCheckSum((unsigned char*)tempData, tempMsg.header.nSize);
	int nLen = m_pSerialPort->write((char*)&tempMsg, tempMsg.header.nSize + 9);
	return nLen;
}

void HandleCom::slot_recv_data()
{
	QByteArray recvBuf = m_pSerialPort->readAll();
	emit sig_send_data(recvBuf);
}

unsigned short HandleCom::calcCheckSum(unsigned char *pData, int nSize)
{
	uint16_t checksum = 0;
	for (uint16_t i = 0; i < nSize; i++)
	{
		checksum += pData[i];
	}
	return checksum;
}

unsigned short HandleCom::calcCheckSum(unsigned short *pData, int nSize)
{
	uint16_t checksum = 0;
	for (uint16_t i = 0; i < nSize; i++)
	{
		checksum += pData[i];
	}
	return checksum;
}

