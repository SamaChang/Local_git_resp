#pragma once
/**
 * @class	�����ô��ڣ�������ڿ��ã��ͼ��뵽���ô����б���
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

	//�����ô���
	void checkPort();
	//���ؿ��ô���
	QVector<QString> getAvailablePort();

signals:
	void sig_available_port(QString strCom);	//����淢�Ϳ��ô���

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
