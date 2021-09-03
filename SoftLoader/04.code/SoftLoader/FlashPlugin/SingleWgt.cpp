#include "SingleWgt.h"
#include "SerialThread.h"
#include <QThread>
#include <QFile>
#include <QDebug>
#include <QSerialPortInfo>
#include <QDateTime>
#include "def.h"
#include "WriteLog.h"

SingleWgt::SingleWgt(QWidget *parent)
	: QWidget(parent)
	, m_state(BURN_NONE)
{
	ui.setupUi(this);
	QStringList strList;
	strList << QStringLiteral("握手") << QStringLiteral("初始化") << QStringLiteral("擦写") << QStringLiteral("烧写") << QStringLiteral("成功");
	ui.arrowWgt->setTitles(strList);
	ui.arrowWgt->initUI();
	connect(this, &SingleWgt::sig_log, WriteLog::getIns(), &WriteLog::slot_recv_msg);
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
		//ui.ringWgt->setTitle(QStringLiteral("握手成功"));
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
		//ui.tbtn_ws->setStyleSheet("QToolButton{ background-color:#00FF00;}");
		ui.arrowWgt->setStepStatus(STATUS_WS, true);
	}
}

void SingleWgt::initUI()
{
	//ui.tbtn_ws->setStyleSheet("QToolButton{ background-color:none;}");
	//ui.tbtn_bl->setStyleSheet("QToolButton{ background-color:none;}");
	//ui.tbtn_erase->setStyleSheet("QToolButton{ background-color:none;}");
	//ui.tbtn_prag->setStyleSheet("QToolButton{ background-color:none;}");
	//ui.tbtn_finish->setStyleSheet("QToolButton{ background-color:none;}");
	//ui.progressBar->setValue(0);
	ui.ringWgt->init();
	ui.arrowWgt->initUI();
}

void SingleWgt::reset()
{
	QString strInfo = LOG_HEAD;
	strInfo += QStringLiteral("主线程，AAAAAAAAAAAAA");
	emit sig_log(strInfo);
	QThread::usleep(1);
	if (m_pSerialPort != nullptr)
	{
		delete m_pSerialPort;
		m_pSerialPort = nullptr;
	}
	QThread::usleep(1);
	strInfo = LOG_HEAD;
	strInfo += QStringLiteral("主线程，CCCCCCCCCCCC");
	emit sig_log(strInfo);

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
		ui.ringWgt->setTitle(QStringLiteral("握手成功"));
		emit sig_loop_quit();
		break;
	}
	case BURN_REPLY_BL:
	{
		//ui.tbtn_bl->setStyleSheet("QToolButton{ background-color:#00FF00;}");
		ui.arrowWgt->setStepStatus(STATUS_FB, true);
		break;
	}
	case BURN_ERASE:
	{
		//ui.tbtn_bl->setStyleSheet("QToolButton{ background-color:#00FF00;}");
		ui.arrowWgt->setStepStatus(STATUS_FB, true);
		break;
	}
	case BURN_REPLY_ERASE:
	{
		ui.ringWgt->setTitle(QStringLiteral("擦除"));
		//ui.tbtn_erase->setStyleSheet("QToolButton{ background-color:#00FF00;}");
		ui.ringWgt->setPersent(nValProcess);
		ui.arrowWgt->setStepStatus(STATUS_CC, true);
		break;
	}
	case BRUN_PROGRAM:
	{
		ui.ringWgt->setTitle(QStringLiteral("烧录中"));
		//ui.tbtn_prag->setStyleSheet("QToolButton{ background-color:#00FF00;}");
		ui.arrowWgt->setStepStatus(STATUS_SB, true);
		ui.ringWgt->setPersent(nValProcess);
		break;
	}
	case BURN_REPLY_PROGRAM:
	{
		//QString strInfo = LOG_HEAD;
		//strInfo += QStringLiteral("主线程，接收到成功信号");
		//emit sig_log(strInfo);
		ui.ringWgt->setTitle(QStringLiteral("成功"));
		ui.arrowWgt->setStepStatus(STATUS_WC, true);
		//ui.tbtn_finish->setStyleSheet("QToolButton{ background-color:#00FF00;}");
		//线程执行完毕，重新释放线程
		reset();
		break;
	}
	default:
		break;
	}
	update();
}
