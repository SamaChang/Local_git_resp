#pragma once

#include <QObject>
#include <qtcpsocket.h>
#define IP_360 "192.168.100.101"   //·þÎñÆ÷µØÖ·
#define PORT	1234

class TCP : public QObject
{
	Q_OBJECT

public:
	TCP(QObject *parent);
	~TCP();
	void initSocket();
	int connectSocket();
	void send_data(char *data, int len);
	//int socket_read_data(uint8_t *send, char *rec);
	QByteArray socket_read_data(uint8_t *send, char *rec);
private:
	QTcpSocket *tcpSocket;


};
