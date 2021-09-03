#include "Programer.h"
#include "def.h"
#include "packet.h"
#include <qmessagebox.h>
#include <qfiledialog.h>
#include <qfile.h>
#include <Windows.h>
#include <qdatetime.h>
#include <qtextstream.h>
#define FUN_1
Programer::Programer(QWidget *parent)
    : QMainWindow(parent), cmd_first("TX21")
{
    ui.setupUi(this);
	this->setWindowIcon(QIcon("./Logo.png"));
	this->setWindowTitle("Programmer_V1.0");
	m_serialPort_1 = new QSerialPort();
	m_serialPort_2 = new QSerialPort();
	m_serialPort_3 = new QSerialPort();
	m_serialPort_4 = new QSerialPort();
	m_serialPort_5 = new QSerialPort();
	m_serialPort_6 = new QSerialPort();
	m_serialPort_7 = new QSerialPort();
	m_serialPort_8 = new QSerialPort();
	//initSerialPort();
	//connectFun();
	//writeData();
	isEraseOver = false;
	connect(this, SIGNAL(run_erase()), this, SLOT(erase()));
}
QString log_path = "./m_serialport_1_log.txt";
Programer::~Programer()
{
	if (m_serialPort_1->isOpen())
	{
		m_serialPort_1->close();
		delete m_serialPort_1;
	}
		
	
	delete m_serialPort_2;
	delete m_serialPort_3;
	delete m_serialPort_4;
	delete m_serialPort_5;
	delete m_serialPort_6;
	delete m_serialPort_7;
	delete m_serialPort_8;
}

//�����б�
QStringList Programer::getPortNameList()//��ȡ���п��õĴ����б�
{
	QStringList m_serialPortName;
	foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
	{
		//TX210
		//if (info.description() == "USB-SERIAL CH340")
		//{
		//	m_serialPortName << info.portName();
		//}
		//TX231
		if (info.description() == "Silicon Labs CP210x USB to UART Bridge")
		{
			m_serialPortName << info.portName();
		}
	}
	return m_serialPortName;
}
//���ڳ�ʼ��
void Programer::initSerialPort()
{
	QSerialPort *sp;
	QStringList portList = getPortNameList();
	if (!portList.empty())
	{
		for (int i = 0; i < portList.length(); i++)
		{
			if (i == 0)
				sp = m_serialPort_1;
			if (i == 1)
				sp = m_serialPort_2;
			if (i == 2)
				sp = m_serialPort_3;
			if (i == 3)
				sp = m_serialPort_4;
			if (i == 4)
				sp = m_serialPort_5;
			if (i == 5)
				sp = m_serialPort_6;
			if (i == 6)
				sp = m_serialPort_7;
			if (i == 7)
				sp = m_serialPort_8;
			if (sp->isOpen())
			{
				sp->clear();
				sp->close();
			}
			QString serialName = portList.at(i);
			sp->setPortName(serialName);
			if (!sp->open(QIODevice::ReadWrite))
			{
				QMessageBox::warning(0, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("���ڴ�ʧ�ܻ򴮿��ѱ�ռ��!"), QMessageBox::Ok);
				return;
			}
			//sp->setBaudRate(1000000/*QSerialPort::Baud115200*/, QSerialPort::AllDirections);//���ò����ʺͶ�д����  210�Ĳ�������1000000 
			sp->setBaudRate(500000/*QSerialPort::Baud115200*/, QSerialPort::AllDirections);//���ò����ʺͶ�д����  231�Ĳ�������500000 
			sp->setDataBits(QSerialPort::Data8);		//����λΪ8λ
			sp->setFlowControl(QSerialPort::NoFlowControl);//��������
			sp->setParity(QSerialPort::NoParity);	//��У��λ
			sp->setStopBits(QSerialPort::OneStop); //һλֹͣλ
		}
	}
	else
	{
		QMessageBox::warning(0, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("δ��⵽����!"), QMessageBox::Ok);
	}
}

void Programer::connectFun()
{
	connect(m_serialPort_1, SIGNAL(readyRead()), this, SLOT(recData()));
}

void Programer::record_log(QString path, QString send_info, QString sendOrRec)
{
	QDateTime time;
	QString date_time = time.currentDateTime().toString("yyyy/MM/dd_HH:mm:ss.zzz");
	if (!path.isEmpty())
	{
		QFile file(path);
		if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
		{
			QMessageBox::warning(0, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("���ļ�ʧ��!"), QMessageBox::Ok);
		}
		QTextStream tStream(&file);
		tStream << date_time << "\t" << sendOrRec << send_info << "\n";
		file.close();
	}
}

//1.�˺�����loop.exec(),�յ�ERASE_OK����quit()�źţ�������һ��64k;2.��дһ��ֻ����64kһ�εĺ������ڽ������ݺ���ÿ�յ�һ��ERASE_OK����һ�η���.
bool Programer::erase()
{
	ui.textEdit->append(QString::fromLocal8Bit("��ʼ����..."));
	//����1��������
	//QString log_path = "./m_serialport_1_log.txt";
	QEventLoop loop;
	connect(this, SIGNAL(next_erase()), &loop, SLOT(quit()));
	char erase_data[sizeof(dataProtorl) + 7] = { 0 };	
	erase_data[11] = 1;		//MSG_Body�����һλblock numĬ����1��������λ��У���
	file_len = readProgrammerBl();
	if (file_len <= 0)
	{
		isEraseOver = false;
		return false;
	}
	data2protorl(erase_data, 5, MSG_SEDN_ERASE);
	int times = ERASE_MEM(file_len);
	if (file_len%ERASE_LEN)
	{
		for (int i = 0; i < times + 1; i++)    //���һ��С��64k,Ҳ����64kȥ����
		{
			store_le_uint32((unsigned char *)(erase_data + sizeof(dataProtorl)), i*ERASE_LEN);
			//unsigned char value = 0;
			//unsigned short m_checksum = std::accumulate(erase_data + 4, erase_data + 4 + 2 + 1 + 5, value);
			uint16_t m_checksum = computeCheckSum((unsigned char *)erase_data + 4, 2 + 1 + 5);
			short2char(erase_data + sizeof(dataProtorl) + 5, m_checksum);
			m_serialPort_1->write(erase_data, sizeof(dataProtorl) + 7);
			loop.exec();
			record_log(log_path, "erase loop over" + QString::number(i), "Send:");
		}
		isEraseOver = true;
		ui.textEdit->append(QString::fromLocal8Bit("�������..."));
		writeProgrammer();
		return true;
	}
	else
	{
		for (int i = 0; i < times; i++)
		{
			store_le_uint32((unsigned char *)(erase_data + sizeof(dataProtorl)), i*ERASE_LEN);
			//unsigned char value = 0;
			//unsigned short m_checksum = std::accumulate(erase_data + 4, erase_data + 4 + 2 + 1 + 5, value);
			uint16_t m_checksum = computeCheckSum((unsigned char *)erase_data + 4, 2 + 1 + 5);
			short2char(erase_data + sizeof(dataProtorl) + 5, m_checksum);
			//char aa [14]= { 0x55, 0xaa, 0x5a, 0x5a, 0x00 ,0x05 ,0x81 ,0x00 ,0x00 ,0x00 ,0x00 ,0x01 ,0x00 ,0x87 };
			m_serialPort_1->write(erase_data/*aa*/, sizeof(dataProtorl) + 7);
			loop.exec();
			record_log(log_path, "erase loop over" + QString::number(i), "Send:");
		}
		isEraseOver = true;
		ui.textEdit->append(QString::fromLocal8Bit("�������..."));
		writeProgrammer();
		return true;
	}
	return false;
}
//����2
void Programer::erase_once(int count)
{
	char erase_data[sizeof(dataProtorl) + 5] = { 1 };	//���һλblock numĬ����1
	file_len = readProgrammerBl();
	if (file_len <= 0)
		return;
	data2protorl(erase_data, 5, MSG_SEDN_ERASE);
	store_le_uint32((unsigned char *)(erase_data + sizeof(dataProtorl)), count*ERASE_LEN);
	m_serialPort_1->write(erase_data, sizeof(dataProtorl) + 5);
}

int Programer::readProgrammerBl(/*QByteArray &read_data*/)
{
	int file_len = 0;
	QString filename = /*"C:/Users/EDZ/Desktop/Test_bin/bootloader_bin_emmc_ddr800_cpu400_aie360_71c2e1c (2).bin"*/filePath;
	QFile file(filename);
	if (!file.open(QIODevice::ReadOnly))
	{
		QMessageBox::question(0, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("��Programmer�ļ�ʧ��!"), QMessageBox::Ok);
		return FILE_LEN_ERROR;
	}
	else
	{
		file_data = file.readAll();
		file_len = file_data.length();
		file.close();
		ui.textEdit->append(QString::fromLocal8Bit("bin�ļ���ȡ�ɹ�������Ϊ��") + QString::number(file_len));
		return file_len;
	}
	return file_len;
}

uint16_t Programer::computeCheckSum(uint8_t *data, uint16_t size)
{
	uint16_t checksum = 0;
	for (uint16_t i = 0; i < size; i++)
	{
		checksum += data[i];
	}
	return checksum;
}

//�����һ�������Ƿ���һ��packet�ͻظ�һ��
bool Programer::writeProgrammer()
{
	ui.textEdit->append(QString::fromLocal8Bit("��ʼ��¼�ļ�:")+ filePath);
	//char *page_data = (char *)malloc(file_len);
	char page_data[261 + sizeof(dataProtorl) + 2] = { 0 };   //7B(4B_ͷ+2B_size+1B_Msgid)+261B_MsgBody(4B_pageaddr+1B_flag+256B_data)+2B_checksum
	QEventLoop loop;
	connect(this, SIGNAL(next_write()), &loop, SLOT(quit()));
	int times = 0;
	//QByteArray read_data;
	//file_len = readProgrammerBl(read_data);
	//if (file_len <= 0)
	//{
	//	QMessageBox::question(0, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("Programmer�ļ���ȡʧ��!"), QMessageBox::Ok);
	//	return false;
	//}
	//else
	//{
		times = CHANGE_PACKET(file_len);
		data2protorl(page_data, 261, MSG_SEND_WRITE_PAGE);
		//fun1��
		if (file_len%DATA_LEN)    //���һ������256�Ĳ�0�չ�256
		{
			for (int i = 0; i < CHANGE_PACKET(file_len); i++)
			{
				store_le_uint32((unsigned char *)(page_data + sizeof(dataProtorl)), i*DATA_LEN);
				memcpy(page_data + sizeof(dataProtorl) + 5, file_data.data() + i * DATA_LEN, DATA_LEN);    //msgbody=4B��page_add��1B��flag(���͵����һ��packetΪ1��������Ϊ0)��256B��data,һ��261B.
				//short value = 0;
				//unsigned short m_checksum = std::accumulate(page_data + 4, page_data + 4 + 2 + 1 + 261, value/*0*/);
				uint16_t m_checksum = computeCheckSum((unsigned char *)page_data + 4, 264);
				short2char(page_data + sizeof(dataProtorl) + 261, m_checksum);
				//m_serialPort_1->write(file_data.data() + i * DATA_LEN, DATA_LEN);   //��Ϊ�����ݰ����ͣ�û��Э��
				m_serialPort_1->write(page_data, 261 + sizeof(dataProtorl) + 2);
				loop.exec();
				record_log(log_path, "writeProgrammer loop over...." + QString::number(i), "Send:");
			}
			//���һ��
			page_data[sizeof(dataProtorl) + 4] = 1;  //���һ����block_numΪ1
			store_le_uint32((unsigned char *)(page_data + sizeof(dataProtorl)), times*DATA_LEN);   //д���ַ��λ�����һ���׵�ַ
			memcpy(page_data + sizeof(dataProtorl) + 5, file_data.data() + times * DATA_LEN, file_len%DATA_LEN);
			memset(page_data + file_len % DATA_LEN + sizeof(dataProtorl) + 5, 0, sizeof(char)*(256 - file_len % DATA_LEN));    //������256��Ԫ�ز�0
			//short value = 0;
			//unsigned short m_checksum = std::accumulate(page_data + 4, page_data + 4 + 2 + 1 + 261, value/*0*/);
			uint16_t m_checksum = computeCheckSum((unsigned char *)page_data + 4, 264);
			short2char(page_data + sizeof(dataProtorl) + 261, m_checksum);
			m_serialPort_1->write(page_data, 261 + sizeof(dataProtorl) + 2);
			loop.exec();
			record_log(log_path, "writeProgrammer Completed!!....", "Send:");
			////if (file_len - (times*DATA_LEN) > 0)   //���һ������ʵ�ʳ��ȷ���
			////{
			////	m_serialPort_1->write(file_data.data() + (times*DATA_LEN), file_len - (times*DATA_LEN));
			////}
		}
		else
		{
			for (int i = 0; i < CHANGE_PACKET(file_len); i++)
			{
				store_le_uint32((unsigned char *)(page_data + sizeof(dataProtorl)), i*DATA_LEN);
				memcpy(page_data + sizeof(dataProtorl) + 5, file_data.data() + i * DATA_LEN, DATA_LEN);    //msgbody=4B��page_add��1B��flag(���͵����һ��packetΪ1��������Ϊ0)��256B��data,һ��261B.
				uint16_t m_checksum = computeCheckSum((unsigned char *)page_data + 4, 264);
				//ushort value = 0;
				//unsigned short m_checksum = std::accumulate(page_data + 4, page_data + 4 + 2 + 1 + 261, value/*0*/);
				short2char(page_data + sizeof(dataProtorl) + 261, m_checksum);
				if (i == times - 1)//���һ��
				{
					page_data[sizeof(dataProtorl) + 4] = 1;
					m_checksum += 1;
					short2char(page_data + sizeof(dataProtorl) + 261, m_checksum);
				}
				//m_serialPort_1->write(file_data.data() + i * DATA_LEN, DATA_LEN);   //��Ϊ�����ݰ����ͣ�û��Э��
				m_serialPort_1->write(page_data, 261 + sizeof(dataProtorl) + 2);
				loop.exec();
				record_log(log_path, "writeProgrammer loop over...." + QString::number(i), "Send:");
			}
		}
		//fun2��
		//for (int i = 0; i < CHANGE_PACKET(file_len); i++)
		//{
		//	store_le_uint32((unsigned char *)(page_data + sizeof(dataProtorl)), i*DATA_LEN);
		//	memcpy(page_data + sizeof(dataProtorl) + 5, file_data.data() + i * DATA_LEN, DATA_LEN);    //msgbody=4B��page_add��1B��flag(���͵����һ��packetΪ1��������Ϊ0)��256B��data,һ��261B.
		//	//unsigned char value = 0;
		//	short value = 0;
		//	unsigned short m_checksum = std::accumulate(page_data + 4, page_data + 4 + 2 + 1 + 261, value/*0*/);
		//	short2char(page_data + sizeof(dataProtorl) + 261, m_checksum);
		//	//m_serialPort_1->write(file_data.data() + i * DATA_LEN, DATA_LEN);   //��Ϊ�����ݰ����ͣ�û��Э��
		//	m_serialPort_1->write(page_data, 261 + sizeof(dataProtorl) + 2);
		//	loop.exec();
		//	record_log(log_path, "writeProgrammer loop over....", "Send:");
		//}
		//if (file_len - (times*DATA_LEN) > 0)
		//{
		//	m_serialPort_1->write(file_data.data() + (times*DATA_LEN), file_len - (times*DATA_LEN));
		//}
		ui.textEdit->append(QString::fromLocal8Bit("��¼���..."));
		QMessageBox::information(0, QString::fromLocal8Bit("��¼"), QString::fromLocal8Bit("��¼���!"), QMessageBox::Ok);
		return true;
}

void Programer::recData()
{
	const char compare[3] = { 0x55,0xaa,0x5a };
	//QByteArray rec_data;
	//bool isEraseOver = false;
	rec_data.append(m_serialPort_1->readAll());
	for (int i = 0; i < rec_data.length(); i++)
	{
		int len = rec_data.length();
		if (rec_data.at(i)== compare[0] && i< len -6)   //�˴���֤���ȿ��Լ��㵽size
		{
			if (rec_data.at(i+1) == compare[1] && rec_data.at(i+2) == compare[2] && rec_data.at(i+3) == compare[2])
			{
				unsigned char size[2] = { rec_data.at(i + 4),rec_data.at(i + 5) };
				unsigned short m_size = reverse_uint16(size);
				if (m_size + i + 8 < rec_data.length())    //�˴���֤���ȿ��Լ��㵽У��͡�m_size+i+7<rec_data.length()����ж��ǳ��ȹ�1BУ��ͣ��������ڵ�У��Ͷ���2B,���Լ�8����֤���ȹ�2B��У���
				{
					unsigned short m_checksum = std::accumulate(rec_data.data() + i + 4, rec_data.data() + i + 4 + 2 + 1 + m_size, 0);
					unsigned char checksum[2] = { rec_data.at(i + 4 + 2 + 1 + m_size),rec_data.at(i + 4 + 2 + 1 + m_size + 1) };
					if (reverse_uint16(checksum) == m_checksum)
					{
						if (rec_data.at(i + 8) == MSG_ACK_BL_START)
						{
							//isEraseOver = erase();   //��Ҫ���͸��ź�ִ�д˺�������Ȼ����������?
							//erase_once(0);  //����2
							rec_data.clear();
							record_log(log_path, "ready emit run_erase fun", "Receive:");
							emit run_erase();
							break;
						}
						if (rec_data.at(i + 8) == MSG_ACK_ERASE_OK)    //����һ��64k�ظ�һ��
						{
#ifdef FUN_2
							//����2��������
							static int count = 1;		//�������һ����
							if (count < ERASE_MEM(file_len))   
							{
								erase_once(count);
								count++;
							}
							else
							{
								count = 0;
								writeProgrammer();
							}
#else						rec_data.clear();
							record_log(log_path, "ready emit next_erase", "Receive:");
							emit next_erase();

							//if (isEraseOver)
							//	writeProgrammer();
							break;
#endif // FUN_2
						}
						//if (isEraseOver)
						//	writeProgrammer();
						if (rec_data.at(i + 8) == MSG_ACK_PAGE_PROGRAM_OK)
						{
							rec_data.clear();
							record_log(log_path, "ready emit next_write.....", "Receive:");
							emit next_write();
							break;
						}
						if (rec_data.at(i + 8) == MSG_ACK_CHECKSUM_ERROR)
						{
							QMessageBox::question(0, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("����У��ͳ�������!"), QMessageBox::Ok);
						}
					}
				}
			}
		}
	}
}

bool Programer::communicate()
{
	//Sleep(1000);
	//QByteArray rec_data_connect;
	m_serialPort_1->write(cmd_first);
	//m_serialPort_1->waitForBytesWritten(30000);

	m_serialPort_1->waitForReadyRead(10);
	//rec_data.append(m_serialPort_1->readAll());
	rec_data_connect = m_serialPort_1->readAll();
	if (!rec_data_connect.contains("ZZ"))
	{
		rec_data_connect.clear();
		QMessageBox::question(0, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("����1δ�յ������ź�!"), QMessageBox::Ok);
		return false;
	}
	rec_data_connect.clear();
	return true;
}

void Programer::on_pushButton_clicked()
{
	initSerialPort();
	if (!communicate())
		return;
	ui.textEdit->append(QString::fromLocal8Bit("���ֳɹ�..."));
	connectFun();

	//QString filename = "C:/Users/EDZ/Desktop/Test_bin/app_download(3).bin"/*filePath*/;
	//QString filename = "./app_download(3).bin"/*filePath*/;    //�����210���ӵ�bootroom
	//QString filename = "./appotf_download_normal.bin"/*filePath*/;    //�����231���ӵ�bootroom
	QString filename = "./appmd5otf_download_programmer.bin"/*filePath*/;   
	QFile file(filename);
	if (!file.open(QIODevice::ReadOnly))
	{
		QMessageBox::question(0, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("��appotf_download�ļ�ʧ��!"), QMessageBox::Ok);
		return;
	}
	else
	{
		QByteArray data_bin = file.readAll();
		file.close();
		m_serialPort_1->write(data_bin);
		//m_serialPort_1->waitForBytesWritten(10);
	}


	//connect(this, SIGNAL(run_erase()), this, SLOT(erase()));
}

void Programer::on_pushButton_2_clicked()
{
	filePath = QFileDialog::getOpenFileName(this, tr("Choose File"), "", "(*.bin);;All files(*.*)");
}