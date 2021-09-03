#include "SerialPortDlg.h"
#include "HandleCom.h"

//#include "Config.h"
#include <QDebug>
#include <QTime>
#include <string>
#include <math.h>

SerialPortDlg::SerialPortDlg(QWidget *parent, int nPowerOfTwo)
	: QDialog(parent)
	, m_pHandleCom(new HandleCom(this))
	, m_bRecvASCII(true)
	, m_bSendASCII(true)
	, m_bAutoWrap(true)
	, m_bShowSended(true)
	, m_bShowTm(true)
	, m_nPowerOfTwo(nPowerOfTwo)
{
	ui.setupUi(this);
	initUI();
	initComParam();
	setCtrlStatus(true);
	//m_nPowerOfTwo = Config::getIns()->m_nPowerOfTwo;
}

SerialPortDlg::~SerialPortDlg()
{
}

void SerialPortDlg::setData(const QVector<IIR_INFO> & vec)
{
	m_nType = EQ_APP;
	m_vec_data = vec;
	memset(m_cData, 0, 5000);
	m_nLen = 0;
	int nSize = vec.size();
	qDebug() << "---------------write data start-----------------";
	for (int i = 0; i < nSize; ++i)
	{
		memcpy(m_cData + i * sizeof(IIR_INFO), (char*)(&vec.at(i)), sizeof(IIR_INFO));
		qDebug() << "b0:" << vec.at(i).b0 << " b1:" << vec.at(i).b1 << " b2:" << vec.at(i).b2 << " a0:" << vec.at(i).a0 << " a1:" << vec.at(i).a1 << " a2:" << vec.at(i).a2;
	}
	qDebug() << "---------------write data end-----------------";
	m_nLen = sizeof(IIR_INFO)*nSize;

	//都除以a0操作
	for (int i = 0; i < m_vec_data.count(); ++i)
	{
		IIR_INFO & temp = m_vec_data[i];
		if (abs(temp.a0) > 0.00001)			//认为a0不是零时
		{
			temp.b0 = temp.b0 / temp.a0;
			temp.b1 = temp.b1 / temp.a0;
			temp.b2 = temp.b2 / temp.a0;
			temp.a1 = temp.a1 / temp.a0;
			temp.a2 = temp.a2 / temp.a0;
			temp.a0 = 1;	
		}
	}
}

void SerialPortDlg::setData(const QVector<IIR_INFO> & vec_iir_ff, const QVector<IIR_INFO> & vec_iir_fb)
{
	m_nType = ANC_APP;
	memset(m_cData, 0, 5000);
	m_nLen = 0;
	int nSize = vec_iir_ff.size();
	qDebug() << "---------------write data start FF-----------------";
	for (int i = 0; i < nSize; ++i)
	{
		IIR_INFO temp = vec_iir_ff.at(i);
		memcpy(m_cData + i * sizeof(IIR_INFO), (char*)(&temp), sizeof(IIR_INFO));
		qDebug() << "b0:" << temp.b0 << " b1:" << temp.b1 << " b2:" << temp.b2 << " a0:" << temp.a0 << " a1:" << temp.a1 << " a2:" << temp.a2;
	}
	qDebug() << "---------------write data end FF-----------------";

	int nSize_FB = vec_iir_fb.size();
	qDebug() << "---------------write data start FB-----------------";
	for (int i = 0; i < nSize_FB; ++i)
	{
		IIR_INFO temp = vec_iir_fb.at(i);
		memcpy(m_cData + i * sizeof(IIR_INFO), (char*)(&temp), sizeof(IIR_INFO));
		qDebug() << "b0:" << temp.b0 << " b1:" << temp.b1 << " b2:" << temp.b2 << " a0:" << temp.a0 << " a1:" << temp.a1 << " a2:" << temp.a2;
	}
	qDebug() << "---------------write data end FB-----------------";

	m_nLen += sizeof(IIR_INFO)*nSize_FB;
	m_vec_data_FF = vec_iir_ff;
	m_vec_data_FB = vec_iir_fb;

	//都除以a0操作
	for (int i=0; i<m_vec_data_FF.count(); ++i)
	{
		IIR_INFO & temp = m_vec_data_FF[i];
		if (abs(temp.a0) > 0.00001)			//认为a0不是零时
		{
			temp.b0 = temp.b0 / temp.a0;
			temp.b1 = temp.b1 / temp.a0;
			temp.b2 = temp.b2 / temp.a0;
			temp.a1 = temp.a1 / temp.a0;
			temp.a2 = temp.a2 / temp.a0;
			temp.a0 = 1;
			
		}
	}

	for (int i = 0; i < m_vec_data_FB.count(); ++i)
	{
		IIR_INFO & temp = m_vec_data_FB[i];
		if (abs(temp.a0) > 0.00001)			//认为a0不是零时
		{
			temp.b0 = temp.b0 / temp.a0;
			temp.b1 = temp.b1 / temp.a0;
			temp.b2 = temp.b2 / temp.a0;
			temp.a1 = temp.a1 / temp.a0;
			temp.a2 = temp.a2 / temp.a0;
			temp.a0 = 1;
			
		}
	}
}

void SerialPortDlg::initUI()
{
	connect(m_pHandleCom, &HandleCom::sig_send_data, this, &SerialPortDlg::slot_recv_data);
	connect(ui.btn_start, &QPushButton::clicked, this, &SerialPortDlg::slot_btn_start);
	connect(ui.btn_stop, &QPushButton::clicked, this, &SerialPortDlg::slot_btn_stop);
	connect(ui.btn_send, &QPushButton::clicked, this, &SerialPortDlg::slot_btn_send);
	connect(ui.btn_send_IIR, &QPushButton::clicked, this, &SerialPortDlg::slot_btn_send_IIR);
	//connect(ui.btn_send_IIR, &QPushButton::clicked, this, &SerialPortDlg::slot_bin_send_IIR_ANC);
	connect(ui.btn_clear, &QPushButton::clicked, this, &SerialPortDlg::slot_btn_clear);

	connect(ui.rbtn_recv_ascii, &QRadioButton::clicked, this, &SerialPortDlg::slot_recv_radio_clicked);
	connect(ui.rbtn_recv_hex, &QRadioButton::clicked, this, &SerialPortDlg::slot_recv_radio_clicked);

	connect(ui.ckb_autoWrap, &QCheckBox::stateChanged, this, &SerialPortDlg::slot_checkbox_stateChanged);
	connect(ui.ckb_showSend, &QCheckBox::stateChanged, this, &SerialPortDlg::slot_checkbox_stateChanged);
	connect(ui.ckb_showTm, &QCheckBox::stateChanged, this, &SerialPortDlg::slot_checkbox_stateChanged);

	//connect(ui.rbtn_send_ascii, &QRadioButton::clicked, this, &SerialPortDlg::slot_send_radio_clicked);
	//connect(ui.rbtn_send_hex, &QRadioButton::clicked, this, &SerialPortDlg::slot_send_radio_clicked);
}

void SerialPortDlg::initComParam()
{
	ui.cmb_port->clear();
	QStringList strList = m_pHandleCom->getAvailablePorts();
    foreach (QString var, strList)
	{
		ui.cmb_port->addItem(var);
	}
}

void SerialPortDlg::setCtrlStatus(bool bFlag)
{
	ui.btn_start->setEnabled(bFlag);
	ui.cmb_port->setEnabled(bFlag);
	ui.cmb_baudRate->setEnabled(bFlag);
	ui.cmb_dataBits->setEnabled(bFlag);
	ui.cmb_flowCtrl->setEnabled(bFlag);
	ui.cmb_parity->setEnabled(bFlag);
	ui.cmb_stopBits->setEnabled(bFlag);

	ui.btn_stop->setEnabled(!bFlag);
	ui.btn_send->setEnabled(!bFlag);
	ui.btn_send_IIR->setEnabled(!bFlag);
	ui.btn_clear->setEnabled(!bFlag);
}

QString SerialPortDlg::strASCIIToHex(const QString & strAscii)
{
	QString strHex;
	QByteArray byteArray = strAscii.toLocal8Bit();
	strHex = byteArray.toHex(' ').toUpper();
	return strHex;
}

QString SerialPortDlg::strHexToASCII(const QString & strHex)
{
	QString strReturn;
	bool bOk = false;
	QByteArray byteArray;
	QStringList strList = strHex.split(" ");
    foreach (QString var, strList)
	{
		if (!var.isEmpty())
		{
			int nVak = var.toInt(&bOk, 16);
			char c = nVak;
			if (bOk)
			{
				byteArray.append(c);
			}
		}
	}
	strReturn = QString::fromLocal8Bit(byteArray);
	return strReturn;
}

void SerialPortDlg::sendEQMsg()
{
	sendMsg(m_vec_data, MSG_SEND_EQ_TX);
}

void SerialPortDlg::sendANCMsg()
{
	sendMsg(m_vec_data_FB, MSG_SEND_ANC_TX_FB);
	sendMsg(m_vec_data_FF, MSG_SEND_ANC_TX_FF);
}

int SerialPortDlg::sendMsg(const QVector<IIR_INFO> &vec, unsigned char nMsgID)
{
	int nLen = m_pHandleCom->sendData(vec, nMsgID);
	QString strLog;
	strLog = QStringLiteral("send>>>>>>发送失败！！！！！！！");
	if (nLen > -1)
	{
		strLog = QStringLiteral("send>>>>>>发送成功，长度为：%1，报文如下：").arg(nLen);
		ui.lab_info->setText(strLog);
		strLog += "\n";
		QString strTemp;
		SEND_INFO_MSG tempMsg;
		tempMsg.header.msgID = nMsgID;

		QString strMsgName;

		switch (nMsgID)
		{
		case MSG_SEND_EQ_TX:
		{
			strMsgName = "EQ->TX";
			break;
		}
		case MSG_SEND_ANC_TX_FB:
		{
			strMsgName = "ANC.FB->TX";
			break;
		}
		case MSG_SEND_ANC_TX_FF:
		{
			strMsgName = "ANC.FF->TX";
			break;
		}
		default:
			break;
		}

		strTemp = QStringLiteral("报文头 sybcWord:0x%1  msgID:%2 %3\n").arg(QString::number(tempMsg.header.syncWord, 16)).arg(QString::number(tempMsg.header.msgID, 16)).arg(strMsgName);
		strLog += strTemp;

		for (int i = 0; i < vec.size(); i++)
		{
			IIR_INFO temp = vec.at(i);
            strTemp = QString("b0=%1, b1=%2, b2=%3, a0=%4, a1=%5, a2=%6\n").arg(long(temp.b0*pow(2, m_nPowerOfTwo))).arg(long(temp.b1*pow(2, m_nPowerOfTwo))).arg(long(temp.b2*pow(2, m_nPowerOfTwo))).arg(long(temp.a0*pow(2, m_nPowerOfTwo))).arg(long(temp.a1*pow(2, m_nPowerOfTwo))).arg(long(temp.a2*pow(2, m_nPowerOfTwo)));
			strLog += strTemp;
		}
	}
	else
	{
		ui.lab_info->setText(strLog);
	}

	if (m_bShowSended)
	{
		ui.plainTextEdit_recv->appendPlainText(strLog);
	}
	return nLen;
}

void SerialPortDlg::slot_recv_data(QByteArray strData)
{
	QByteArray byteArray = strData;
	QString strArray;
	if (m_bShowTm)
	{
		QString strTm = QTime::currentTime().toString("hh:mm:ss");
		strArray += strTm;
		strArray += " : ";
	}
	if (byteArray.length() == TX_PC_REPLY_LEN)
	{
		//TX231应答PC消息报文
		TX_PC_REPLY txReply;
		memcpy(&txReply, byteArray.constData(), TX_PC_REPLY_LEN);
		txReply.reset();
		unsigned char cMsgData[TX_PC_REPLY_LEN] = { 0 };
		memcpy(cMsgData, byteArray.constData(), TX_PC_REPLY_LEN);

		unsigned short nCheckSum = std::accumulate(cMsgData + 4, cMsgData + TX_PC_REPLY_LEN - 2, 0);
		if (txReply.head.syncWord == MSG_UNIFIED_MSGID && nCheckSum == txReply.checksum)
		{
			if (txReply.ack_status == MSG_ACK_TX_EQ_OK)
			{
				ui.plainTextEdit_recv->appendPlainText(QStringLiteral("EQ配置传输成功"));
			}
			else if(txReply.ack_status == MSG_ACK_TX_ANC_FB_OK)
			{
				ui.plainTextEdit_recv->appendPlainText(QStringLiteral("ANC.FB配置传输成功"));
			}
			else if (txReply.ack_status == MSG_ACK_TX_ANC_FF_OK)
			{
				ui.plainTextEdit_recv->appendPlainText(QStringLiteral("ANC.FF配置传输成功"));
			}
			else if (txReply.ack_status == MSG_ACK_TX_CHECKSUM_ERROR)
			{
				ui.plainTextEdit_recv->appendPlainText(QStringLiteral("校验失败"));
			}
			else
			{
				ui.plainTextEdit_recv->appendPlainText(QStringLiteral("无效报文"));
			}
		}
	}
	else
	{
		QString strOut = QString::fromLocal8Bit(byteArray);
		if (!m_bRecvASCII)
		{
			strOut = strASCIIToHex(byteArray);
		}
		else
		{
			strOut = byteArray.left(byteArray.length() - 1);	//删除换行符
		}
		strArray += strOut;
		ui.plainTextEdit_recv->appendPlainText(strArray);
	}
}

void SerialPortDlg::slot_btn_start()
{
	COM_INFO tempStu;
	QString strName = ui.cmb_port->currentText();
	strName = strName.section(":", 0, 0);
	tempStu.strComName = strName;
	//设置串口波特率
	tempStu.baudRate = static_cast<QSerialPort::BaudRate>(ui.cmb_baudRate->currentText().toInt());
	//设置串口数据位
	tempStu.dataBits = static_cast<QSerialPort::DataBits>(ui.cmb_dataBits->currentText().toInt());
	//设置串口停止位
	if (ui.cmb_stopBits->currentText() == "1")
	{
		tempStu.stopBits = QSerialPort::OneStop;
	}
	else if (ui.cmb_stopBits->currentText() == "1.5")
	{
		tempStu.stopBits = QSerialPort::OneAndHalfStop;
	}
	else if (ui.cmb_stopBits->currentText() == "2")
	{
		tempStu.stopBits = QSerialPort::TwoStop;
	}

	//设置串口奇偶校验位
	tempStu.parity = static_cast<QSerialPort::Parity>(ui.cmb_parity->currentIndex() == 0 ? 0 : ui.cmb_parity->currentIndex() + 1);

	//设置流控制
	if (ui.cmb_flowCtrl->currentIndex() == 0)
	{
		tempStu.flowCtrl = QSerialPort::NoFlowControl;
	}
	else if (ui.cmb_flowCtrl->currentIndex() == 1)
	{
		tempStu.flowCtrl = QSerialPort::HardwareControl;
	}
	else if (ui.cmb_flowCtrl->currentIndex() == 2)
	{
		tempStu.flowCtrl = QSerialPort::SoftwareControl;
	}

	// 初始化串口属性，设置 端口号、波特率、数据位、停止位、奇偶校验位数
	m_pHandleCom->setComParam(tempStu);
	//打开串口
	QString strLog;
	bool bRet = m_pHandleCom->openCom();
	if (bRet)
	{
		setCtrlStatus(!bRet);
		strLog = QStringLiteral("串口%1打开成功！！！").arg(strName);
	}
	else
	{
		strLog = QStringLiteral("串口%1打开成功！！！").arg(strName);
	}
	ui.lab_info->setText(strLog);
}

void SerialPortDlg::slot_btn_stop()
{
	ui.lab_info->setText(QStringLiteral("关闭串口！！！"));
	m_pHandleCom->closeCom();
	setCtrlStatus(true);
}

void SerialPortDlg::slot_btn_send()
{
	QString strSend = ui.tedt_send->toPlainText();
	int nLen = m_pHandleCom->sendData(strSend.toLocal8Bit());
	QString strLog;
	strLog = QStringLiteral("send>>>>>>发送失败！！！！！！！");
	if (nLen > -1)
	{
		strLog = QStringLiteral("send>>>>>>发送成功，长度为：%1").arg(nLen);
		ui.lab_info->setText(strLog);
		strLog += "\n";
		strLog += strSend;
	}
	else
	{
		ui.lab_info->setText(strLog);
	}
	if (m_bShowSended)
	{	
		ui.plainTextEdit_recv->appendPlainText(strLog);
	}
	
}

void SerialPortDlg::slot_btn_send_IIR()
{
	if (m_nType == EQ_APP)
	{
		sendEQMsg();
	}
	else if (m_nType == ANC_APP)
	{
		sendANCMsg();
	}
}

void SerialPortDlg::slot_btn_clear()
{
	ui.plainTextEdit_recv->clear();
}

void SerialPortDlg::slot_recv_radio_clicked(bool bChecked)
{
	QRadioButton* pBtn = qobject_cast<QRadioButton*>(sender());
	if (pBtn == ui.rbtn_recv_ascii)
	{
		if (pBtn->isChecked())
		{
			//设置发送显示为ASCII
			m_bRecvASCII = true;
		}
		else
		{
			m_bRecvASCII = false;
		}
	}
	else
	{
		if (pBtn->isChecked())
		{
			//设置发送显示为ASCII
			m_bRecvASCII = false;
		}
		else
		{
			m_bRecvASCII = true;
		}
	}
}

void SerialPortDlg::slot_send_radio_clicked(bool bChecked)
{
	/*
	QRadioButton* pBtn = qobject_cast<QRadioButton*>(sender());
	if (pBtn == ui.rbtn_send_ascii)
	{
		if (pBtn->isChecked())
		{
			//设置发送显示为ASCII
			m_bSendASCII = true;
		}
		else
		{
			m_bSendASCII = false;
		}
	}
	else
	{
		if (pBtn->isChecked())
		{
			//设置发送显示为ASCII
			m_bSendASCII = false;
		}
		else
		{
			m_bSendASCII = true;
		}
	}
	*/
}

void SerialPortDlg::slot_checkbox_stateChanged(int state)
{
	QCheckBox* pCheckBtn = qobject_cast<QCheckBox*>(sender());
	if (pCheckBtn == ui.ckb_autoWrap)	//自动换行
	{
		if (state == Qt::Checked)
		{
			//设置自动换行
			m_bAutoWrap = true;
		}
		else
		{
			m_bAutoWrap = false;
		}

	}
	else if(pCheckBtn == ui.ckb_showSend)	//显示发送
	{
		if (state == Qt::Checked)
		{
			//设置显示发送
			m_bShowSended = true;
		}
		else
		{
			m_bShowSended = false;
		}
	}
	else if (pCheckBtn == ui.ckb_showTm)	//显示时间
	{
		if (state == Qt::Checked)
		{
			//设置显示时间
			m_bShowTm = true;
		}
		else
		{
			m_bShowTm = false;
		}
	}
}
