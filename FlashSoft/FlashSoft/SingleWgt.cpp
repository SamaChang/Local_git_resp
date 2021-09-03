#include "SingleWgt.h"
#include "SerialThread.h"
#include <QThread>
#include <QFile>
#include <QDebug>
#include <QSerialPortInfo>
#include "def.h"

SingleWgt::SingleWgt(QWidget *parent)
	: QWidget(parent)
	, m_state(BURN_NONE)
{
	ui.setupUi(this);
}

SingleWgt::~SingleWgt()
{
}

void SingleWgt::setFirstBin(QByteArray & firstBin)
{
	m_pSerialPort->setFristBin(firstBin);
}

void SingleWgt::setSecondBin(QByteArray & secondBin, int nLen)
{
	m_pSerialPort->setSecondBin(secondBin, nLen);
}

bool SingleWgt::bindPort(QString strCom)
{
	bool bFlag = false;
	QEventLoop loop;
	m_pSerialPort = new SerialThread;
	m_pSerialPort->setPortName(strCom);
	connect(this, &SingleWgt::sig_loop_quit, &loop, &QEventLoop::quit);
	connect(m_pSerialPort, &SerialThread::sig_status, this, &SingleWgt::slot_thread_port_status);
	connect(this, &SingleWgt::sig_init, m_pSerialPort, &SerialThread::slot_init_port);
	connect(this, &SingleWgt::sig_start, m_pSerialPort, &SerialThread::slot_start);
	emit sig_init();
	loop.exec();
	if (m_state == BURN_HANDSHAKE)
	{
		bFlag = true;
	}
	return bFlag;
}

void SingleWgt::startProcess()
{
	emit sig_start();
}

void SingleWgt::setProcessState(int nState)
{
	if (nState == 1)
	{
		//ui.tbtn_ws->setChecked(true);
		ui.tbtn_ws->setStyleSheet("QToolButton{ background-color:#00FF00;}");
	}
}

void SingleWgt::initUI()
{
	ui.tbtn_ws->setStyleSheet("QToolButton{ background-color:none;}");
	ui.tbtn_bl->setStyleSheet("QToolButton{ background-color:none;}");
	ui.tbtn_erase->setStyleSheet("QToolButton{ background-color:none;}");
	ui.tbtn_prag->setStyleSheet("QToolButton{ background-color:none;}");
	ui.tbtn_finish->setStyleSheet("QToolButton{ background-color:none;}");
	ui.progressBar->setValue(0);
}

void SingleWgt::reset()
{
	m_pSerialPort->reset();
	m_pSerialPort->disconnect();
	delete m_pSerialPort;
	m_pSerialPort = nullptr;
	m_state = BURN_NONE;
	emit sig_burn_finished();
}

void SingleWgt::slot_thread_port_status(BURN_STATE nStatus, float nValProcess)
{
	m_state = nStatus;

	switch (nStatus)
	{
	case BURN_HANDSHAKE:
	{
		emit sig_loop_quit();
		break;
	}
	case BURN_REPLY_BL:
	{
		ui.tbtn_bl->setStyleSheet("QToolButton{ background-color:#00FF00;}");
		break;
	}
	case BURN_ERASE:
	{
		ui.tbtn_bl->setStyleSheet("QToolButton{ background-color:#00FF00;}");
		break;
	}
	case BURN_REPLY_ERASE:
	{
		ui.tbtn_erase->setStyleSheet("QToolButton{ background-color:#00FF00;}");
		ui.progressBar->setValue(nValProcess);
		break;
	}
	case BRUN_PROGRAM:
	{
		ui.tbtn_prag->setStyleSheet("QToolButton{ background-color:#00FF00;}");
		ui.progressBar->setValue(nValProcess);
		break;
	}
	case BURN_REPLY_PROGRAM:
	{
		ui.tbtn_finish->setStyleSheet("QToolButton{ background-color:#00FF00;}");
		//线程执行完毕，重新释放线程
		reset();
		break;
	}
	default:
		break;
	}
}
