#include "WriteLog.h"
#include <QThread>
#include <QFile>
#include <QDebug>
#include <QDir>
#include <QDateTime>
#include <QApplication>

QMutex WriteLog::m_mutex;
WriteLog* WriteLog::m_pIns = nullptr;

constexpr auto LOG_NAME = "/log.txt";

WriteLog::WriteLog(QObject *parent)
	: QObject(parent)
	, m_pThread(new QThread)
{
	//创建或者打开日志
	openLogFile();
	this->moveToThread(m_pThread);
	connect(m_pThread, &QThread::started, this, &WriteLog::slot_thread_started);
	connect(m_pThread, &QThread::finished, this, &WriteLog::deleteLater);
	m_pThread->start();
	qDebug() << __FUNCTION__ << QThread::currentThreadId();
}

bool WriteLog::openLogFile()
{
	bool bFlag = false;
	QString logDir = qApp->applicationDirPath() + "/Log/" + QDateTime::currentDateTime().toString("yyyy-MM-dd");
	QDir dir(logDir);
	if (!dir.exists())
	{
		dir.mkdir(logDir);
	}
	logDir += LOG_NAME;
	m_pFile = new QFile(logDir);
	if (m_pFile->open(QFile::WriteOnly | QFile::Text | QFile::Append))
	{
		bFlag = true;
	}
	return bFlag;
}

void WriteLog::writeLogInfo()
{
	if (m_queue.isEmpty())
	{
		return;
	}
	QString strMsg = m_queue.front();
	m_queue.pop_front();
	QTextStream textSream(m_pFile);
	textSream << strMsg << "\r\n";
	m_pFile->flush();		//将缓冲区数据刷新到文件中
}

void WriteLog::slot_recv_msg(QString strLog)
{
	m_queue.push_back(strLog);
	writeLogInfo();
}

void WriteLog::slot_thread_started()
{
	QString preStr1("============================begin：");
	QString strTm = QDateTime::currentDateTime().toString("yyyy-MM-dd");
	QString preStr2("================================");
	preStr1 += strTm + preStr2 + "\r\n";
	QString strLog = QString("--%1<<<%2(%3)>>>").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__);
	QString strDtm = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
	QString strInfo(QStringLiteral("日志线程%1启动").arg(QString::number(quintptr(QThread::currentThreadId()))));
	strDtm += strLog;
	strInfo.prepend(strDtm);
	strInfo.prepend(preStr1);
	m_queue.push_back(strInfo);
	writeLogInfo();
}

WriteLog* WriteLog::getIns()
{
	if (m_pIns == nullptr)
	{
		QMutexLocker locker(&m_mutex);
		m_pIns = new WriteLog;
	}
	return m_pIns;
}

WriteLog::~WriteLog()
{
}
