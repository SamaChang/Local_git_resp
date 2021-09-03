#include "SerialPort.h"
#include <qmessagebox.h>
#include <qserialportinfo.h>
#include "packet.h"
#include <qdebug.h>

SerialPort::SerialPort()
	:serial_port(new QSerialPort),another_pc(new QSerialPort)
{
	//if (getPortNameList().isEmpty())
	//	return;
	//initSerialPort(getPortNameList().at(0));
	//initSerialPort("COM3");   //常浩
	//initSerialPort("COM42");   //李一
}

SerialPort::~SerialPort()
{
	if (!m_serialPortName.isEmpty())
	{
		closeSerialPort(serial_port);
		closeSerialPort(another_pc);
	}
}


void SerialPort::closeSerialPort(QSerialPort *ser)
{
	if (ser->isOpen())
	{
		ser->clear();
		ser->close();
	}
	delete ser;
	ser = nullptr;
}

QStringList SerialPort::getPortNameList()
{
	foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
	{
		//if (info.description() == "Silicon Labs CP210x USB to UART Bridge")
		//{
		//	m_serialPortName << info.portName();
		//}
		m_serialPortName << info.portName();
	}
	return m_serialPortName;
}

void SerialPort::send_serial_data(unsigned char *packet,unsigned int size,QSerialPort *ser)
{
	//unsigned char sendCmd[8] = { 0x31,0x30,0x31,0x30,0x39,0x39,0x0a,0x0a };
	//unsigned char send_buf[1024 * 500] = { 0 };
	//port_send_msg(send_buf, 10);
	//memcpy(send_buf + sizeof(PortDataProtorl), sendCmd, 6);
	//char checkSum = std::accumulate(send_buf + 2, send_buf + sizeof(PortDataProtorl) + 8, 0);
	ser->write((char *)packet, size);
	//serial_port->waitForBytesWritten(30000);
}

//测试机与当前电脑的串口通信
void SerialPort::rec_pc_serial_cmd(QByteArray rec)
{
	int len = rec.size();
	char compare[8] = { 0x31, 0x30 ,0x31 ,0x30 ,0x39 ,0x39 ,0x30 ,0x31 };
	for (int i = 0; i < len; i++)
	{
		if (rec.at(i) == compare[0] && i < len - 7)
		{
			
			if (rec.at(i + 1) == compare[1]&& rec.at(i + 2) == compare[2] && rec.at(i + 3) == compare[3] && rec.at(i + 4) == compare[4] && rec.at(i + 5) == compare[5] && rec.at(i + 6) == compare[6] && rec.at(i + 7) == compare[7])
			{
				emit toSendUsbCmd();
				rec_anther_pc.clear();
			}
		}
	}
}

//抓图串口回复
void SerialPort::rec_cmd_data(/*QByteArray rec*/)
{
	int len = rec.size();
	char compare[5] = { 0xef,0xaa,0xa0,0x41,0x43 };
	for (int i = 0; i < len; i++)
	{
		if (rec.at(i) == compare[0] && i < len - 11)
		{
			if (rec.at(i + 1) == compare[1])
			{
				unsigned char rec_size[4] = { rec.at(i + 3),rec.at(i + 4),rec.at(i + 5),rec.at(i + 6) };
				unsigned short length = reverse_uint32(rec_size);
				if (i + 7 + length < len)
				{
					char checkSum = std::accumulate(rec.data() + i + 2, rec.data() + i + 7 + length, 0);
					if (rec.at(i + 6 + length + 1) == checkSum)
					{
						if (rec.at(i + 7) == compare[3] && rec.at(i + 8) == compare[3] && rec.at(i + 9) == compare[3] && rec.at(i + 10) == compare[3])  //'A'活体
						{
							rec.clear();
							//disconnect(serial_port, SIGNAL(readyRead()), this, SLOT(read_serial_data()));
							emit usb_send(true);
							//emit send_pc_result(true);
							qDebug() << "serial_to_usbconnect";
							
							
							break;
							//serial_port->close();
							//delete(serial_port);
							//serial_port = nullptr;
						}
						if (rec.at(i + 7) == compare[4] && rec.at(i + 8) == compare[4] && rec.at(i + 9) == compare[4] && rec.at(i + 10) == compare[4])   //'C'假体
						{
							rec.clear();
							//disconnect(serial_port, SIGNAL(readyRead()), this, SLOT(read_serial_data()));
							emit usb_send(false);
							//emit send_pc_result(false);
							qDebug() << "serial_to_usbconnect";
							
							
							break;
							//serial_port->close();
							//delete(serial_port);
							//serial_port = nullptr;
						}
					}
				}
			}
		}
	}
}
//串口传图检测结果
void SerialPort::rec_pic_result_data(/*QByteArray rec*/)
{
	int len = rec.size();
	char compare[5] = { 0xef,0xaa,0xa0,0x41,0x43 }; //{0xef,0xaa,0x14,0x00,0x00,0x00,0x05,0x01,0x00,0x00,0x00,0x01,0x23}
	for (int i = 0; i < len; i++)
	{
		if (rec.at(i) == compare[0] && i < len - 12)
		{
			if (rec.at(i + 1) == compare[1])
			{
				unsigned char rec_size[4] = { rec.at(i + 3),rec.at(i + 4),rec.at(i + 5),rec.at(i + 6) };
				unsigned short length = reverse_uint32(rec_size);
				if (i + 7 + length < len)
				{
					char checkSum = std::accumulate(rec.data() + i + 2, rec.data() + i + 7 + length, 0);//6?7?
					if (rec.at(i + 6 + length + 1) == checkSum)
					{
						int id = reverse_uint32((uint8_t *)rec.data() + i + 8);
						qDebug() << "Received One Picture";
						qDebug() << "ID Is" + QString::number(id);
						emit toSavePic(id);
						emit finished_pic_send();
						rec.clear();     //应该写在上面
						break;
					}
				}
			}
		}
	}
}

void SerialPort::read_serial_data()
{
	//QByteArray rec;
	rec.append(serial_port->readAll());
	if (sendPicOrCmd)
	{
		rec_cmd_data(/*rec*/);
		//rec.clear();
	}	
	else
	{
		rec_pic_result_data(/*rec*/);
	}
}

void SerialPort::rec_test_pc()
{
	rec_anther_pc.append(another_pc->readAll());
	rec_pc_serial_cmd(rec_anther_pc);
}

void SerialPort::initSerialPort(QSerialPort *serial,QString name)
{
	//serial_port = new QSerialPort();
	if (serial->isOpen())
	{
		serial->clear();
		serial->close();
	}
	serial->setPortName(name);
	if (!serial->open(QIODevice::ReadWrite))
	{
		QMessageBox::warning(nullptr, "Warning", "Can not open serial port or is occupied");
		return;
	}
	serial->setBaudRate(QSerialPort::Baud115200,QSerialPort::AllDirections);
	serial->setDataBits(QSerialPort::Data8);
	serial->setFlowControl(QSerialPort::NoFlowControl);
	serial->setParity(QSerialPort::NoParity);
	serial->setStopBits(QSerialPort::OneStop);
	//connect(serial_port, SIGNAL(readyRead()), this, SLOT(read_serial_data()));
}

void SerialPort::connectSig()
{
	connect(serial_port, SIGNAL(readyRead()), this, SLOT(read_serial_data()));
	connect(another_pc, SIGNAL(readyRead()), this, SLOT(rec_test_pc()));
}

