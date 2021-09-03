#include "TCP.h"
#include <qmessagebox.h>
#include "packet.h"

TCP::TCP(QObject *parent)
	: QObject(parent)
{
}

TCP::~TCP()
{
	//if (tcpSocket->isOpen())
	//{
	//	tcpSocket->flush();
	//	tcpSocket->close();
	//}

	//delete tcpSocket;
	//if (tcpSocket != nullptr)
	//	tcpSocket = nullptr;
}

void TCP::initSocket()
{
	tcpSocket = new QTcpSocket();
	//connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(socket_read_data()));
}

int TCP::connectSocket()
{
	tcpSocket->abort();   //ȡ����������
	tcpSocket->connectToHost(IP_360, PORT);   //���ӷ�����
	if (!tcpSocket->waitForConnected(3000))   //�ȴ����ӳɹ�
	{
		//tcpSocket->flush();
		//tcpSocket->close();   //�ر�socket
		//QMessageBox::critical(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("TCP���ӳ�ʱ��"), QMessageBox::Ok);
		return -1;
	}
	return 0;
}

void TCP::send_data(char *data, int len)
{
	tcpSocket->write(data, len);
	tcpSocket->flush();
	//socket_read_data();
}

//int TCP::socket_read_data(uint8_t *send, char *rec)
//{
//	//QByteArray buffer;
//	////��ȡ����������
//	//buffer = tcpSocket->readAll();
//	//if (buffer.isEmpty())
//	//{
//	//	QMessageBox::critical(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("TCP��ȡ���ݴ���"), QMessageBox::Ok);
//	//}
//
//	pack360_head(CMD_GET_RESULT, 0, send);
//	send_data((char *)send, GET_360_SEND_LEN(send));
//	
//	QByteArray buffer;
//	if (tcpSocket->waitForReadyRead(3000))
//	{
//		
//		buffer = tcpSocket->readAll();
//		rec = buffer.data();
//	}
//	else
//	{
//		tcpSocket->flush();
//		tcpSocket->close();
//		delete tcpSocket;
//		if (tcpSocket != nullptr)
//			tcpSocket = nullptr;
//		//QMessageBox::critical(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("TCP��ȡ���ݴ���"), QMessageBox::Ok);
//		return -1;
//	}
//	tcpSocket->flush();
//	tcpSocket->close();
//	delete tcpSocket;
//	if (tcpSocket != nullptr)
//		tcpSocket = nullptr;
//	return 0;
//}

QByteArray TCP::socket_read_data(uint8_t *send, char *rec)
{
	pack360_head(CMD_GET_RESULT, 0, send);
	send_data((char *)send, GET_360_SEND_LEN(send));

	QByteArray buffer;
	if (tcpSocket->waitForReadyRead(20000))
	{
		//QByteArray buffer;
		buffer = tcpSocket->readAll();
		rec = buffer.data();
	}
	else
	{
		tcpSocket->flush();
		tcpSocket->close();
		delete tcpSocket;
		if (tcpSocket != nullptr)
			tcpSocket = nullptr;
		//QMessageBox::critical(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("TCP��ȡ���ݴ���"), QMessageBox::Ok);
		return nullptr;
	}
	tcpSocket->flush();
	tcpSocket->close();
	delete tcpSocket;
	if (tcpSocket != nullptr)
		tcpSocket = nullptr;
	return buffer;
}
