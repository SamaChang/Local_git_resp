#include "FlashSoft.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QDateTime>
#include <QSerialPortInfo>
#include "CheckAvailablePort.h"

//#include "def.h"
#include "Packet.h"

const qint32 SERIAL_BAUD_RATE = 500000;


FlashSoft::FlashSoft(QWidget *parent)
    : QMainWindow(parent)
	, m_bLog(false)
{
    ui.setupUi(this);
	setWindowIcon(QIcon(":/Img/Resources/logo.ico"));
	//��ʼ��״̬����
	m_bHandShake[0] = false;

    m_serialPort_1 = new QSerialPort();
    m_serialPort_2 = new QSerialPort();
    m_serialPort_3 = new QSerialPort();
    m_serialPort_4 = new QSerialPort();
    m_serialPort_5 = new QSerialPort();
    m_serialPort_6 = new QSerialPort();
    m_serialPort_7 = new QSerialPort();
    m_serialPort_8 = new QSerialPort();

    isEraseOver = false;
    connect(this, &FlashSoft::run_erase, this, &FlashSoft::erase);
	m_bLog = initLog();
	if (m_bLog)
	{
		ui.textEdit->append(QStringLiteral("��־ϵͳ������������"));
	}
	else
	{
		ui.textEdit->append(QStringLiteral("��־ϵͳ����ʧ�ܡ�����"));
	}
}

FlashSoft::~FlashSoft()
{
	uintLog();
    if (m_serialPort_1->isOpen())
    {
        m_serialPort_1->close();
        delete m_serialPort_1;
        m_serialPort_1 = nullptr;
    }

    delete m_serialPort_2;
    delete m_serialPort_3;
    delete m_serialPort_4;
    delete m_serialPort_5;
    delete m_serialPort_6;
    delete m_serialPort_7;
    delete m_serialPort_8;

}

bool FlashSoft::initLog()
{
	bool bFlag = false;
	QString fileName = qApp->applicationDirPath();
	fileName += "/Log/log.txt";		//�����231���ӵ�bootroom
	m_logFile.close();
	m_logFile.setFileName(fileName);
	if (m_logFile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
	{
		m_logStream.setDevice(&m_logFile);
		bFlag = true;
	}
	return bFlag;
}

void FlashSoft::uintLog()
{
	m_logFile.close();
}

void FlashSoft::initSerialPort()
{
    QSerialPort* pSerialPort;
    QStringList strPortNameLst = getPortNameList();
    int nCount = strPortNameLst.count();

    if (nCount < 1)
    {
        QMessageBox::information(nullptr, QStringLiteral("����"), QStringLiteral("δ��⵽���ӵĴ���..."), QMessageBox::Yes);
    }
    else
    {
        for (int i = 0; i < nCount; ++i)
        {
            QString serialName = strPortNameLst.at(i);
            //�жϵ�ǰ���ĸ�serialPort
            if (i == 0)
            {
                pSerialPort = m_serialPort_1;
            }
            else if (i == 1)
            {
                pSerialPort = m_serialPort_2;
            }
            else if (i == 2)
            {
                pSerialPort = m_serialPort_3;
            }
            else if (i == 3)
            {
                pSerialPort = m_serialPort_4;
            }
            else if (i == 4)
            {
                pSerialPort = m_serialPort_5;
            }
            else if (i == 5)
            {
                pSerialPort = m_serialPort_6;
            }
            else if (i == 6)
            {
                pSerialPort = m_serialPort_7;
            }
            else if (i == 7)
            {
                pSerialPort = m_serialPort_8;
            }

            if (pSerialPort->isOpen())
            {
                pSerialPort->clear();
                pSerialPort->close();
            }
            //���ô��ڲ�����Ϣ
            pSerialPort->setPortName(serialName);		//��������
            pSerialPort->setBaudRate(SERIAL_BAUD_RATE, QSerialPort::AllDirections);	//������
            pSerialPort->setDataBits(QSerialPort::Data8);	//����λ
            pSerialPort->setFlowControl(QSerialPort::NoFlowControl);	//����������
            pSerialPort->setParity(QSerialPort::NoParity);	//��У��λ
            pSerialPort->setStopBits(QSerialPort::OneStop);	//һλֹͣλ

            if (!pSerialPort->open(QIODevice::ReadWrite))
            {
                //QMessageBox::information(nullptr, QStringLiteral("����"), QStringLiteral("����(%1)��ʧ�ܻ����ѱ�ռ��").arg(serialName), QMessageBox::Yes);
                break;
            }
            else
            {
                ui.textEdit->append(QStringLiteral("����%1�����ӣ�����").arg(serialName));
				connect(m_serialPort_1, &QSerialPort::readyRead, this, &FlashSoft::recData);
            }
        }
    }
}

QStringList FlashSoft::getPortNameList()
{
	QStringList serialPortNameLst;

	foreach(const QSerialPortInfo var, QSerialPortInfo::availablePorts())
	{
		if (var.description() == SERIAL_STRING)
		{
			serialPortNameLst << var.portName();
		}
	}
	return serialPortNameLst;
}

void FlashSoft::connectFun()
{
    connect(m_serialPort_1, &QSerialPort::readyRead, this, &FlashSoft::recData);
}

void FlashSoft::record_log(QString path, QString send_info, QString sendOrRec)
{
    QString dateTmStr = QDateTime::currentDateTime().toString("yyyy-MM-dd_hh:mm:ss.zzz��");
    if (!path.isEmpty())
    {
        QFile file(path);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
        {
            QTextStream tStream(&file);
            tStream << dateTmStr << sendOrRec << send_info << "\n";
            file.close();
        }
    }
}

void FlashSoft::record_log(LOG_STATUS status, QString send_info)
{
	if (m_bLog)
	{
		QString strLog;
		QString dateTmStr = QDateTime::currentDateTime().toString("yyyy-MM-dd_hh:mm:ss.zzz");
		if (status == LOG_SEND)
		{
			strLog = dateTmStr + QStringLiteral("������\t") + send_info + "\n";
			m_logFile.write(strLog.toLocal8Bit().data());
		}
		else
		{
			strLog = dateTmStr + QStringLiteral("������\t") + send_info + "\n";
			m_logFile.write(strLog.toLocal8Bit().data());
		}
		m_logFile.flush();
	}
}

bool FlashSoft::communicate()
{
    bool bFlag = true;
    QByteArray recv_data;
    qint64 nRet = m_serialPort_1->write(PC_ASK);		//��������ָ��

	/*
    //m_serialPort_1->waitForReadyRead(10);
    if (m_serialPort_1->waitForReadyRead(10))
    {
        qApp->processEvents();	//���ô˺������߳�ִ������Ϣ�����е��¼���ֱ��û���¼�����ִ��Ϊֹ
        recv_data = m_serialPort_1->readAll();
        if (recv_data.contains(TX_REPLY))
        {
            connect(m_serialPort_1, &QSerialPort::readyRead, this, &FlashSoft::recData);
            bFlag = true;
        }
    }
	*/
    return bFlag;
}

int FlashSoft::readProgrammerBl(/*QByteArray &read_data*/)
{
    int file_len = -1;
    QString filename = filePath;
    QFile file(filename);
    if (file.open(QIODevice::ReadOnly))
    {
        file_data = file.readAll();
        file_len = file_data.length();
        file.close();
        ui.textEdit->append(QStringLiteral("bin�ļ���ȡ�ɹ�������Ϊ��%1").arg(file_len));
    }
    else
    {
        file_len = FILE_LEN_ERROR;
    }

    return file_len;
}

void FlashSoft::erase_once(int count)
{
	/*
    char erase_data[sizeof(DataProtorl) + 5] = { 1 };			//���һλblock_numĬ����1
    file_len = readProgrammerBl();
    if (file_len <= 0)
    {
        return;
    }
    data2protorl(erase_data, 5, MSG_SEND_ERASE);
    store_le_uint32((unsigned char*)(erase_data + sizeof(DataProtorl)), count*ERASE_LEN);
    qint64 nRet = m_serialPort_1->write(erase_data, sizeof(DataProtorl) + 5);
	*/
	PC_TX_ERASE_CMD stuEraseCmd;
	file_len = readProgrammerBl();
	if (file_len <= 0)
	{
		return;
	}
	stuEraseCmd.block_num = 1;
	stuEraseCmd.block_addr = count * ERASE_LEN;
	stuEraseCmd.readyData();
	qint64 nRet = m_serialPort_1->write((char*)&stuEraseCmd, PC_TX_ERASE_CMD_LEN);
}

bool FlashSoft::writeProgrammer()
{
    ui.textEdit->append(QStringLiteral("��ʼ��¼�ļ���%1").arg(filePath));

	
    QEventLoop loop;
    connect(this, &FlashSoft::next_write, &loop, &QEventLoop::quit);
	
    //Ҫ��д�Ĵ��������һ������256�Ĳ�0�չ�256
    int nRemain = file_len%DATA_LEN;	//ʣ��
    int nTimes = nRemain>1 ? CHANGE_PACKET(file_len)+1 : CHANGE_PACKET(file_len);
    for (int i=0; i<nTimes; ++i)
    {
		PC_TX_WRITE_PAGE stuWritePage;
		stuWritePage.page_addr = i * DATA_LEN;
        
        //��дfirmware_data
        if (i == nTimes - 1)	//���һ��
        {
			stuWritePage.last_page_flag = 1;
			memcpy(stuWritePage.firmware_data, file_data.data() + i * DATA_LEN, nRemain);
            //memcpy(page_data + sizeof(DataProtorl) + 5, file_data.data() + i*DATA_LEN, nRemain);
            //�����ı���������
            //memset(page_data + nRemain + sizeof(DataProtorl) + 5, 0, sizeof(char)*(256 - nRemain));
        }
        else
        {
			memcpy(stuWritePage.firmware_data, file_data.data() + i * DATA_LEN, DATA_LEN);
            //memcpy(page_data + sizeof(DataProtorl) + 5, file_data.data() + i*DATA_LEN, DATA_LEN);
        }
        //��дУ��λ 6= SyncWord+checksum�ĳ���
        uint16_t nCheckSum = computeCheckSum((unsigned char*)&stuWritePage + 4, PC_TX_WRITE_PAGE_LEN-6);
		stuWritePage.checksum = nCheckSum;
        //short2char(page_data + sizeof(DataProtorl) + 261, nCheckSum);
		stuWritePage.readyData();
        //���ڷ���
        m_serialPort_1->write((char*)&stuWritePage, PC_TX_WRITE_PAGE_LEN);
        loop.exec();
        //record_log(log_path, QString("writeProgrammer loop over...%1/%2").arg(i).arg(nTimes), "Send��");
		record_log(LOG_SEND, QStringLiteral("����д���У�%1/%2��").arg(i+1).arg(nTimes));
    }

    ui.textEdit->append(QStringLiteral("��¼���..."));
    QMessageBox::information(nullptr, QStringLiteral("��ʾ"), QStringLiteral("��¼���..."), QMessageBox::Yes);
    return false;
}

uint16_t FlashSoft::computeCheckSum(uint8_t *data, uint16_t size)
{
    uint16_t nCheckSum = 0;
    for (int i=0; i<size; ++i)
    {
        nCheckSum += data[i];
    }
    return nCheckSum;
}

bool FlashSoft::loadInitBin()
{
	bool bLoad = false;
	QString fileName = qApp->applicationDirPath();
	fileName += "/data/appotf_download_normal.bin";		//�����231���ӵ�bootroom
	QFile file(fileName);
	if (file.open(QIODevice::ReadOnly))
	{
		m_init_bin = file.readAll();
		file.close();
		bLoad = true;
		//qint64 nRet = m_serialPort_1->write(data_bin);
	}
	return bLoad;
}

void FlashSoft::recData()
{
	//TX231Ӧ��PC��Ϣ����
	TX_PC_REPLY txReply;
    //QByteArray recv_data;
	//QByteArray m_recv_data;
	m_recv_data.append(m_serialPort_1->readAll());
	ui.textEdit->append(m_recv_data);

	if (/*m_recv_data.contains(TX_REPLY) &&*/ m_burn_state== BURN_NONE)
	{
		if (m_recv_data.contains(TX_REPLY))
		{
			QByteArray().swap(m_recv_data);
			m_burn_state = BURN_HANDSHAKE;
			qApp->processEvents();	//���ô˺������߳�ִ������Ϣ�����е��¼���ֱ��û���¼�����ִ��Ϊֹ
			ui.textEdit->append(QStringLiteral("���ֳɹ�����"));
			qint64 nRet = m_serialPort_1->write(m_init_bin);
			m_burn_state = BURN_FIRST_BIN;
			m_bHandShake[0] = true;
		}
	}
	else
	{
		for (int i = 0; i < m_recv_data.length(); ++i)
		{
			if (i == 62)
			{
				int mmm = 0;
			}
			int nLen = m_recv_data.length();
			if (i <= nLen - TX_PC_REPLY_LEN && nLen>= TX_PC_REPLY_LEN)
			{
				unsigned char cMsgData[TX_PC_REPLY_LEN] = { 0 };
				memcpy(cMsgData, m_recv_data.constData() + i, TX_PC_REPLY_LEN);
				memcpy(&txReply, m_recv_data.constData() + i, TX_PC_REPLY_LEN);
				txReply.readyData();
				if (txReply.head.SyncWord == MSG_UNIFIED_MSGID)
				{
					unsigned short nCheckSum = std::accumulate(cMsgData+4, cMsgData+ TX_PC_REPLY_LEN-2, 0);
					if (txReply.checksum == nCheckSum)
					{
						if (txReply.ack_status == MSG_ACK_BL_START)
						{
							//record_log(log_path, "ready emit run_erase fun", "Receive��");
							record_log(LOG_RECV, QStringLiteral("���յ�ACK_BLָ��"));
							m_recv_data.clear();
							emit run_erase();
							break;
						}

						if (txReply.ack_status == MSG_ACK_ERASE_OK)		//����һ��64K�ظ�һ��
						{
							//record_log(log_path, "ready emit next_erase", "Receive��");
							record_log(LOG_RECV, QStringLiteral("���յ�ACK_ERASEָ��"));
							m_recv_data.clear();
							emit next_erase();
							break;
						}

						if (txReply.ack_status == MSG_ACK_PAGE_PROGRAM_OK)
						{
							//record_log(log_path, "ready emit next write", "Receive��");
							record_log(LOG_RECV, QStringLiteral("���յ�ACK_PAGE_PROGRAMָ��"));
							m_recv_data.clear();
							emit next_write();
							break;
						}

						if (txReply.ack_status == MSG_ACK_CHECKSUM_ERROR)
						{
							m_recv_data.clear();
							QMessageBox::information(nullptr, QStringLiteral("��ʾ"), QStringLiteral("���յ��ı���У��Ͳ���ȷ"), QMessageBox::Yes);
						}
					}
				}
			}
		}
	}
}

void FlashSoft::on_pushButton_clicked()
{
	qint64 nRet = m_serialPort_1->write(PC_ASK);		//��������ָ��
	ui.textEdit->append(QStringLiteral("��������ָ��"));
}

void FlashSoft::on_pushButton_2_clicked()
{
	//bool bLoad = loadInitBin();
    QString fileNamePath = qApp->applicationDirPath();
    fileNamePath += "/data";		//�ļ�·��
    filePath = QFileDialog::getOpenFileName(this, QStringLiteral("ѡ���ļ�"), fileNamePath, "(*.bin);;All Files(*.*)");
	//file_len = readProgrammerBl();

}

void FlashSoft::on_pushButton_3_clicked()
{
	bool bLoad = loadInitBin();
	initSerialPort();
	m_burn_state = BURN_NONE;
}

bool FlashSoft::erase()
{
    ui.textEdit->append(QStringLiteral("��ʼ����..."));
    QEventLoop loop;
    connect(this, &FlashSoft::next_erase, &loop, &QEventLoop::quit);
    
    file_len = readProgrammerBl();
    if (file_len < 0)
    {
        isEraseOver = false;
        return false;
    }

    //Ҫ��д�Ĵ��������һ��С��64k��Ҳ��64k����
    int nFreq = file_len%ERASE_LEN>1 ? ERASE_MEM(file_len)+1 :  ERASE_MEM(file_len);
    for (int i=0; i<nFreq; ++i)
    {
		PC_TX_ERASE_CMD stuEraseCmd;
		stuEraseCmd.block_num = 1;
		stuEraseCmd.block_addr = i * ERASE_LEN;
		//6= SyncWord+checksum�ĳ���
		uint16_t nCheckSum = computeCheckSum((unsigned char*)&stuEraseCmd + 4, PC_TX_ERASE_CMD_LEN-6);
		stuEraseCmd.checksum = nCheckSum;
		stuEraseCmd.readyData();
		//���ڷ���
		qint64 nRet = m_serialPort_1->write((char*)&stuEraseCmd, PC_TX_ERASE_CMD_LEN);
        loop.exec();
        //record_log(log_path, QString("erase loop over--%1/%2").arg(i).arg(nFreq), QString("Send��"));
		record_log(LOG_SEND, QStringLiteral("���Ͳ���ָ�%1/%2��").arg(i+1).arg(nFreq));
    }
    isEraseOver = true;
    ui.textEdit->append(QStringLiteral("�������..."));
    writeProgrammer();
    return true;
}
