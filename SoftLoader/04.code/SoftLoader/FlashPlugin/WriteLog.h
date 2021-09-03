#pragma once

#include <QObject>
#include <QMutex>
#include <QQueue>

class QThread;
class QFile;

class WriteLog : public QObject
{
	Q_OBJECT

public:
	static WriteLog* getIns();
	~WriteLog();

private:
	WriteLog(QObject *parent = nullptr);
	bool openLogFile();
	void writeLogInfo();

public slots:
	void slot_recv_msg(QString strLog);
	void slot_thread_started();
	
private:
	static QMutex m_mutex;
	static WriteLog* m_pIns;
	QThread* m_pThread;
	QQueue<QString> m_queue;
	QFile* m_pFile;

};
