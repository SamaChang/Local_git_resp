#pragma once
/**
 * @class	检查可用串口，如果串口可用，就加入到可用串口列表中
 * @date   2021/06/16
 */

#include <QObject>
#include <QSerialPort>
#include <QTimer>

class CheckAvailablePort : public QObject
{
	Q_OBJECT

public:
	CheckAvailablePort(QObject *parent = nullptr);
	~CheckAvailablePort();

	//检测可用串口
	void checkPort();
	//返回可用串口
	QVector<QString> getAvailablePort();

signals:
	void sig_available_port(QString strCom);	//向界面发送可用串口

public slots:
	void handle_recv();
	void slot_link();

private:
	//QSerialPort* m_pSerialPort;
	QVector<QSerialPort*> m_vec_p_serial_port;
	QTimer m_timer;
	bool m_bAvailableLink;
	QVector<QString> m_vecAvailablePort;
};
