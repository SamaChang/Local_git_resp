#include "CheckAvailablePort.h"
#include <QSerialPortInfo>
#include <QSerialPort>
#include <QEventLoop>

#include <QDebug>
#include "def.h"

CheckAvailablePort::CheckAvailablePort(QObject *parent)
	: QObject(parent)
	, m_bAvailableLink(false)
{
	connect(&m_timer, &QTimer::timeout, this, &CheckAvailablePort::slot_link);
	m_timer.start(40);
}

CheckAvailablePort::~CheckAvailablePort()
{
}

void CheckAvailablePort::checkPort()
{
	QVector<QString>().swap(m_vecAvailablePort);
	//QEventLoop loop;
	//connect(this, &CheckAvailablePort::sig_result, &loop, &QEventLoop::quit);
	//QTimer::singleShot(30000, &loop, &QEventLoop::quit);
	foreach(const QSerialPortInfo var, QSerialPortInfo::availablePorts())
	{
		if (var.description() == SERIAL_STRING)
		{
			//serialPortNameLst << var.portName();
			QSerialPort* m_pSerialPort = new QSerialPort;
			qDebug() << QStringLiteral("正在检查串口%1").arg(var.portName());
			m_pSerialPort->setPortName(var.portName());		//串口名称
			m_pSerialPort->setBaudRate(PORT_BAUD_RATE, QSerialPort::AllDirections);	//波特率
			m_pSerialPort->setDataBits(QSerialPort::Data8);	//数据位
			m_pSerialPort->setFlowControl(QSerialPort::NoFlowControl);	//流控制类型
			m_pSerialPort->setParity(QSerialPort::NoParity);	//无校验位
			m_pSerialPort->setStopBits(QSerialPort::OneStop);	//一位停止位
			if (m_pSerialPort->open(QIODevice::ReadWrite))
			{
				connect(m_pSerialPort, &QSerialPort::readyRead, this, &CheckAvailablePort::handle_recv);
				
				qDebug() << QStringLiteral("检查。。。。。");
				m_vec_p_serial_port.push_back(m_pSerialPort);
				/*
				if (m_bAvailableLink)
				{
					emit sig_available_port(var.portName());
					m_vecAvailablePort.push_back(var.portName());
					qDebug() << "available port " << var.portName();
				}
				else
				{
					qDebug() << QStringLiteral("串口检测超时。。。");
					break;
				}
				*/
			}
			else
			{
				delete m_pSerialPort;
				m_pSerialPort = nullptr;
			}
		}
		m_bAvailableLink = false;
	}
}

QVector<QString> CheckAvailablePort::getAvailablePort()
{
	return m_vecAvailablePort;
}

void CheckAvailablePort::handle_recv()
{
	QSerialPort* pPort = qobject_cast<QSerialPort*>(sender());
	QByteArray byteArray = pPort->readAll();
	//QByteArray byteArray = m_pSerialPort->readAll();
	qDebug() << byteArray;
	if (byteArray.contains(TX_REPLY))
	{
		//m_timer.stop();
		//m_bAvailableLink = true;
		QString strPort = pPort->portName();
		pPort->disconnect();
		pPort->close();
		m_vec_p_serial_port.removeOne(pPort);
		delete pPort;
		pPort = nullptr;
		
		m_vecAvailablePort.push_back(strPort);
		qDebug() << "available port " << strPort;
		emit sig_available_port(strPort);
	}
}

void CheckAvailablePort::slot_link()
{
	/*
	if (m_pSerialPort)
	{
		m_pSerialPort->write(PC_ASK);
		qDebug() << QStringLiteral("开始握手。。。");
	}
	*/

	for (int i=0; i<m_vec_p_serial_port.size(); ++i)
	{
		m_vec_p_serial_port[i]->write(PC_ASK);
		qDebug() << m_vec_p_serial_port[i]->portName() << QStringLiteral("--开始握手。。。。");
	}
}
