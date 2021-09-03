#include "SerialThread.h"

#include <QSerialPort>
#include <QTimer>
#include <QDateTime>
#include <QDebug>
#include <QApplication>
#include <QFile>
#include "Packet.h"
#include "WriteLog.h"

SerialThread::SerialThread(QObject *parent)
	: QObject(parent)
	, m_serial_baud_rate(500000)
	, m_bStartTm(false)
	, m_secondBin_length(0)
	, m_burn_state(BURN_NONE)
{
	m_thread = new QThread;
	m_port = new QSerialPort;
	//m_timer = new QTimer;
	//m_strPortName = new QString;
	///QString strss = "COM1";
	//init_port(strss);

	this->moveToThread(m_thread);
	m_port->moveToThread(m_thread);
	//m_timer->moveToThread(m_thread);
	//m_timer->setInterval(2000);
	//connect(m_timer, &QTimer::timeout, this, &SerialThread::slot_timeout);
	//connect(m_thread, &QThread::started, m_timer, QOverload<void>::of(&QTimer::start));
	connect(this, &SerialThread::run_erase, this, &SerialThread::erase_process);
	//m_timer->start(2000);
	m_thread->start();	//�������߳�

	connect(this, &SerialThread::sig_log, WriteLog::getIns(), &WriteLog::slot_recv_msg);
}

SerialThread::~SerialThread()
{
	reset();
}

void SerialThread::reset()
{
	//m_port->disconnect();
	//m_thread->disconnect();
	m_thread->quit();
	m_thread->wait();

	//m_port->close();
	QString strInfo = LOG_HEAD;
	strInfo += QStringLiteral("���̣߳�BBBBBBBBBBBBBB");
	emit sig_log(strInfo);
	delete m_port;
	delete m_thread;
	m_port = nullptr;
	m_thread = nullptr;
	m_strPortName = "";
}

bool SerialThread::init_port()
{
	bool bFlag = false;
	//���ô��ڲ�����Ϣ
	m_port->setPortName(m_strPortName);		//��������
	m_port->setBaudRate(m_serial_baud_rate, QSerialPort::AllDirections);	//������
	m_port->setDataBits(QSerialPort::Data8);	//����λ
	m_port->setFlowControl(QSerialPort::NoFlowControl);	//����������
	m_port->setParity(QSerialPort::NoParity);	//��У��λ
	m_port->setStopBits(QSerialPort::OneStop);	//һλֹͣλ

	if (m_port->open(QIODevice::ReadWrite))
	{
		bFlag = true;
		connect(m_port, &QSerialPort::readyRead, this, &SerialThread::slot_handle_data, Qt::DirectConnection);
		//QString strLog = QStringLiteral("--%1<<<%2(%3)>>>").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__);
		QString strInfo = LOG_HEAD;
		strInfo += QStringLiteral("�����߳�%1��������ֺ����߳������°󶨴���%2").arg(THREAD_NAME).arg(m_strPortName);
		emit sig_log(strInfo);
	}
	return bFlag;
}

void SerialThread::setPortName(QString strSrialName)
{
	m_strPortName = strSrialName;
}

void SerialThread::setFristBin(QByteArray &firstBin)
{
	m_array_first_bin = firstBin;
}

void SerialThread::setSecondBin(QByteArray &secondBin, int nLen)
{
	m_array_second_bin = secondBin;
	m_secondBin_length = nLen;
}

void SerialThread::handle_process(unsigned char nCmd)
{
	switch (nCmd)
	{
	case MSG_ACK_BL_START:
	{
		QString strInfo = LOG_HEAD;
		strInfo += QStringLiteral("�߳�%1�����յ�BLָ��").arg(THREAD_NAME);
		emit sig_log(strInfo);
		emit sig_status(BURN_REPLY_BL);
		emit run_erase();
		int mm = 0;
		break;
	}
	case MSG_ACK_ERASE_OK:		////����һ��64K�ظ�һ��
	{
		QString strInfo = LOG_HEAD;
		strInfo += QStringLiteral("�߳�%1�����յ�����һ��64K�ظ�ָ��").arg(THREAD_NAME);
		emit sig_log(strInfo);
		emit next_erase();
		break;
	}
	case MSG_ACK_PAGE_PROGRAM_OK:			//��д�ڶ���bin���
	{
		QString strInfo = LOG_HEAD;
		strInfo += QStringLiteral("�߳�%1�����յ���д�ڶ���bin�ظ�ָ��").arg(THREAD_NAME);
		emit sig_log(strInfo);
		emit next_write();
		break;
	}
	case MSG_ACK_CHECKSUM_ERROR:
	{
		int mm = 0;
		break;
	}
	default:
		break;
	}
}

void SerialThread::erase_process()
{
	QEventLoop loop;
	connect(this, &SerialThread::next_erase, &loop, &QEventLoop::quit);
	//Ҫ��д�Ĵ��������һ��С��64k��Ҳ��64k����
	int nFreq = m_secondBin_length % ERASE_LEN > 1 ? ERASE_MEM(m_secondBin_length) + 1 : ERASE_MEM(m_secondBin_length);
	for (int i = 0; i < nFreq; ++i)
	{
		PC_TX_ERASE_CMD stuEraseCmd;
		stuEraseCmd.block_num = 1;
		stuEraseCmd.block_addr = i * ERASE_LEN;
		//6= SyncWord+checksum�ĳ���
		uint16_t nCheckSum = computeCheckSum((unsigned char*)&stuEraseCmd + 4, PC_TX_ERASE_CMD_LEN - 6);
		stuEraseCmd.checksum = nCheckSum;
		stuEraseCmd.readyData();
		//���ڷ���
		qint64 nRet = m_port->write((char*)&stuEraseCmd, PC_TX_ERASE_CMD_LEN);
		QString strInfo = LOG_HEAD;
		strInfo += QStringLiteral("�߳�%1�����Ͳ���ָ�%2/%3��").arg(THREAD_NAME).arg(i + 1).arg(nFreq);
		emit sig_log(strInfo);
		emit sig_status(BURN_REPLY_ERASE, (i+1)/(nFreq*0.01));
		loop.exec();
	}
	m_burn_state = BRUN_PROGRAM;
	write_second_bin_process();
	//isEraseOver = true;
	//ui.textEdit->append(QStringLiteral("�������..."));
	//writeProgrammer();
	
}

void SerialThread::write_second_bin_process()
{
	qDebug() << QStringLiteral("��ʼ��¼�ڶ���bin������Ϊ%2").arg(m_secondBin_length);
	QString strInfo = LOG_HEAD;
	strInfo += QStringLiteral("�߳�%1����ʼ��¼�ڶ���bin������Ϊ%2").arg(THREAD_NAME).arg(m_secondBin_length);
	emit sig_log(strInfo);
	QEventLoop loop;
	connect(this, &SerialThread::next_write, &loop, &QEventLoop::quit);

	//Ҫ��д�Ĵ��������һ������256�Ĳ�0�չ�256
	int nRemain = m_secondBin_length % DATA_LEN;	//ʣ��
	int nTimes = nRemain > 1 ? CHANGE_PACKET(m_secondBin_length) + 1 : CHANGE_PACKET(m_secondBin_length);
	for (int i = 0; i < nTimes; ++i)
	{
		PC_TX_WRITE_PAGE stuWritePage;
		stuWritePage.page_addr = i * DATA_LEN;

		//��дfirmware_data
		if (i == nTimes - 1)	//���һ��
		{
			stuWritePage.last_page_flag = 1;
			memcpy(stuWritePage.firmware_data, m_array_second_bin.data() + i * DATA_LEN, nRemain);
		}
		else
		{
			memcpy(stuWritePage.firmware_data, m_array_second_bin.data() + i * DATA_LEN, DATA_LEN);
		}
		//��дУ��λ 6= SyncWord+checksum�ĳ���
		uint16_t nCheckSum = computeCheckSum((unsigned char*)&stuWritePage + 4, PC_TX_WRITE_PAGE_LEN - 6);
		stuWritePage.checksum = nCheckSum;
		stuWritePage.readyData();
		//���ڷ���
		m_port->write((char*)&stuWritePage, PC_TX_WRITE_PAGE_LEN);
		qDebug() << QStringLiteral("����д���У�%1/%2��").arg(i + 1).arg(nTimes);
		QString strInfo = LOG_HEAD;
		strInfo += QStringLiteral("�߳�%1������д���У�%2/%3��").arg(THREAD_NAME).arg(i + 1).arg(nTimes);
		emit sig_log(strInfo);
		emit sig_status(BRUN_PROGRAM, (i + 1) / (nTimes*0.01));
		loop.exec();
	}
	qDebug() << QStringLiteral("��¼���...");

	QString strInfo_2 = LOG_HEAD;
	strInfo_2 += QStringLiteral("�߳�%1����¼���").arg(THREAD_NAME);
	emit sig_log(strInfo_2);
	
	m_port->close();

	emit sig_status(BURN_REPLY_PROGRAM);

	//emit sig_thread_finished();
}

uint16_t SerialThread::computeCheckSum(uint8_t *data, uint16_t size)
{
	uint16_t nCheckSum = 0;
	for (int i = 0; i < size; ++i)
	{
		nCheckSum += data[i];
	}
	return nCheckSum;
}

void SerialThread::slot_init_port()
{
	qDebug()<< __FUNCTION__ << " thread id-- " << QThread::currentThreadId();
	bool bLink = init_port();
	if (bLink)
	{
		m_bStartTm = true;
		
		emit sig_status(BURN_HANDSHAKE);
	}
}

void SerialThread::slot_start()
{
	qint64 nRet = m_port->write(m_array_first_bin);
	qDebug() << "send first bin size: " << nRet;
	QString strInfo = LOG_HEAD;
	strInfo += QStringLiteral("�߳�%1�����͵�һ��bin����Ϊ��%2").arg(THREAD_NAME).arg(nRet);
	emit sig_log(strInfo);
	m_burn_state = BURN_FIRST_BIN;
	emit sig_status(BURN_FIRST_BIN);
}

void SerialThread::slot_handle_data()
{
	m_recv_data.append(m_port->readAll());
	qDebug() << QThread::currentThreadId()<< QStringLiteral("�߳̽�������--����")<< m_strPortName<<">>>"<< m_recv_data.toHex();
	if (m_burn_state == BURN_NONE)		//�������ֲ���
	{
	}
	else
	{
		int nMsgLen = m_recv_data.length();
		for (int i=0; i< nMsgLen; ++i)
		{
			if (i <= nMsgLen - TX_PC_REPLY_LEN && nMsgLen >= TX_PC_REPLY_LEN)
			{
				//TX231Ӧ��PC��Ϣ����
				TX_PC_REPLY txReply;
				unsigned char cMsgData[TX_PC_REPLY_LEN] = { 0 };
				memcpy(cMsgData, m_recv_data.constData() + i, TX_PC_REPLY_LEN);
				memcpy(&txReply, m_recv_data.constData() + i, TX_PC_REPLY_LEN);
				txReply.readyData();
				if (txReply.head.SyncWord == MSG_UNIFIED_MSGID )
				{
					unsigned short nCheckSum = std::accumulate(cMsgData + 4, cMsgData + TX_PC_REPLY_LEN - 2, 0);
					if (txReply.checksum == nCheckSum)
					{
						QByteArray().swap(m_recv_data);
						handle_process(txReply.ack_status);
						break;
					}
				}
			}
		}
	}
}

void SerialThread::slot_write_data()
{
	qDebug() << m_strPortName << __FUNCTION__ << " thread id-- " << QThread::currentThreadId();
	m_port->write("data", 4);
}
