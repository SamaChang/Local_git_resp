#include "ConfItemWgt.h"
#include <QRegExp>
#include <QtSerialPort/QSerialPortInfo>
#include <QtSerialPort/QtSerialPort>
#include"../common/datastruct/DataStruct.h"
#include <QMessageBox>
#include <QRegExpValidator>
#include <QtDebug>

#include <QFile>
#include <QJsonDocument>

ConfItemWgt::ConfItemWgt(QWidget *parent)
	: QWidget(parent)
	, m_pSerialPort(new QSerialPort)
{
	ui.setupUi(this);
	
	//QRegExp regexpMac("([0-9A-Fa-f]{2}:[0-9A-Fa-f]{2}:[0-9A-Fa-f]{2}:[0-9A-Fa-f]{2}:[0-9A-Fa-f]{2}:[0-9A-Fa-f]{2})");
	//ui.edt_mac->setValidator(new QRegExpValidator(regexpMac, this));
	//ui.comboBox->lineEdit()->setAlignment(Qt::AlignCenter);
	initCmbPort();

	connect(ui.pushButton, &QPushButton::clicked, this, &ConfItemWgt::slot_btn_1);
	connect(ui.pushButton_2, &QPushButton::clicked, this, &ConfItemWgt::slot_btn_2);
	connect(ui.pushButton_3, &QPushButton::clicked, this, &ConfItemWgt::slot_btn_3);
	connect(ui.pushButton_4, &QPushButton::clicked, this, &ConfItemWgt::slot_btn_4);
	connect(ui.pushButton_5, &QPushButton::clicked, this, &ConfItemWgt::slot_btn_5);
	connect(ui.pushButton_6, &QPushButton::clicked, this, &ConfItemWgt::slot_btn_6);
	connect(ui.pushButton_7, &QPushButton::clicked, this, &ConfItemWgt::slot_btn_7);
	connect(ui.pushButton_8, &QPushButton::clicked, this, &ConfItemWgt::slot_btn_8);
	connect(ui.pushButton_9, &QPushButton::clicked, this, &ConfItemWgt::slot_btn_9);

	m_cmb_group.push_back(ui.cmb_aj_1);
	m_cmb_group.push_back(ui.cmb_aj_2);
	m_cmb_group.push_back(ui.cmb_aj_3);
	m_cmb_group.push_back(ui.cmb_aj_4);
	m_cmb_group.push_back(ui.cmb_aj_5);
	m_cmb_group.push_back(ui.cmb_aj_6);
	m_cmb_group.push_back(ui.cmb_aj_7);
	m_cmb_group.push_back(ui.cmb_aj_8);
	m_cmb_group.push_back(ui.cmb_aj_9);
	m_cmb_group.push_back(ui.cmb_aj_10);

	slot_btn_3();
	slot_btn_5();
	//音量配置
	ui.spinBox->setValue(m_volume_default);
	ui.spinBox_2->setValue(m_volume_tips);

	QRegExp regexp("^[A-F0-9]{2}$");
	QRegExpValidator* macValidator = new QRegExpValidator(regexp, this);
	ui.edtMac_1->setValidator(macValidator);
	ui.edtMac_2->setValidator(macValidator);
	ui.edtMac_3->setValidator(macValidator);
	ui.edtMac_4->setValidator(macValidator);
	ui.edtMac_5->setValidator(macValidator);
	ui.edtMac_6->setValidator(macValidator);

	for (int i = 0; i < 6; ++i)
	{
		m_bluetooth_mac_addr[i] = 0xFF;
	}

	for (int i = 0; i < 10; ++i)
	{
		m_nKeyFun[i] = 0;
	}

	readConfig();
	
}

ConfItemWgt::~ConfItemWgt()
{
}

void ConfItemWgt::slot_cmb_port_init()
{
	initCmbPort();
}

//音量配置
void ConfItemWgt::slot_btn_1()
{
	VolumeConfStu tempStu;
	tempStu.defaultVal = ui.spinBox->value();
	tempStu.tipsVal = ui.spinBox_2->value();
	tempStu.reset();
	int nRet = m_pSerialPort->write((char*)&tempStu, sizeof(VolumeConfStu));
	if (nRet)
	{
		qDebug() << QStringLiteral("发送音量配置成功");
		ui.lab_info->setText(QStringLiteral("发送音量配置成功"));
	}
}

//充电配置
void ConfItemWgt::slot_btn_2()
{
	ChargeConfStu tempStu;

	tempStu.charge_full_voltage = static_cast<int>(ui.doubleSpinBox->value()*MSG_DIMENSION);
	tempStu.charge_full_current = ui.spinBox_6->value();
	tempStu.charge_current = ui.spinBox_7->value();
	tempStu.low_voltage_tips = static_cast<int>(ui.doubleSpinBox_3->value()*MSG_DIMENSION);
	tempStu.low_shut_down = static_cast<int>(ui.doubleSpinBox_2->value()*MSG_DIMENSION);
	tempStu.reset();
	int nRet = m_pSerialPort->write((char*)&tempStu, sizeof(ChargeConfStu));
	if (nRet)
	{
		qDebug() << QStringLiteral("发送充电配置成功");
		ui.lab_info->setText(QStringLiteral("发送充电配置成功"));
	}
}

//充电配置恢复默认值
void ConfItemWgt::slot_btn_3()
{
	m_charge_full_voltage = 4.202;
	m_charge_full_current = 10;
	m_charge_current = 15;
	m_low_voltage_tips = 3.4;
	m_low_shut_down = 3.4;

	//充电配置
	ui.doubleSpinBox->setValue(m_charge_full_voltage);
	ui.spinBox_6->setValue(m_charge_full_current);
	ui.spinBox_7->setValue(m_charge_current);
	ui.doubleSpinBox_3->setValue(m_low_voltage_tips);
	ui.doubleSpinBox_2->setValue(m_low_shut_down);
}

//蓝牙配置
void ConfItemWgt::slot_btn_4()
{
	BluetoothConfStu tempStu;
	QString strName = ui.lineEdit->text();

	bool bOk;
	tempStu.mac[0] = ui.edtMac_1->text().toInt(&bOk, 16);
	tempStu.mac[1] = ui.edtMac_1->text().toInt(&bOk, 16);
	tempStu.mac[2] = ui.edtMac_1->text().toInt(&bOk, 16);
	tempStu.mac[3] = ui.edtMac_1->text().toInt(&bOk, 16);
	tempStu.mac[4] = ui.edtMac_1->text().toInt(&bOk, 16);
	tempStu.mac[5] = ui.edtMac_1->text().toInt(&bOk, 16);

	memcpy(tempStu.name, strName.toLocal8Bit().data(), strName.toLocal8Bit().size());
	
	tempStu.sendFreq = ui.spinBox_3->value();
	tempStu.tm = ui.spinBox_4->value();
	tempStu.reset();
	int nRet = m_pSerialPort->write((char*)&tempStu, sizeof(BluetoothConfStu));
	if (nRet)
	{
		qDebug() << QStringLiteral("发送蓝牙配置成功");
		ui.lab_info->setText(QStringLiteral("发送蓝牙配置成功"));
	}
}

//蓝牙配置恢复默认值
void ConfItemWgt::slot_btn_5()
{
	m_bluetooth_name = "Tsingmicro";
	m_bluetooth_mac_addr[0] = 0xFF;
	m_bluetooth_mac_addr[1] = 0xFF;
	m_bluetooth_mac_addr[2] = 0xFF;
	m_bluetooth_mac_addr[3] = 0xFF;
	m_bluetooth_mac_addr[4] = 0xFF;
	m_bluetooth_mac_addr[5] = 0xFF;
	m_bluetooth_send_freq = 10;
	m_bluetooth_tm = 3;

	//蓝牙配置
	ui.lineEdit->setText(m_bluetooth_name);
	ui.edtMac_1->setText(QString::number(m_bluetooth_mac_addr[0], 16).toUpper());
	ui.edtMac_2->setText(QString::number(m_bluetooth_mac_addr[1], 16).toUpper());
	ui.edtMac_3->setText(QString::number(m_bluetooth_mac_addr[2], 16).toUpper());
	ui.edtMac_4->setText(QString::number(m_bluetooth_mac_addr[3], 16).toUpper());
	ui.edtMac_5->setText(QString::number(m_bluetooth_mac_addr[4], 16).toUpper());
	ui.edtMac_6->setText(QString::number(m_bluetooth_mac_addr[5], 16).toUpper());

	ui.spinBox_3->setValue(m_bluetooth_send_freq);
	ui.spinBox_4->setValue(m_bluetooth_tm);
}

//按键配置
void ConfItemWgt::slot_btn_6()
{
	KeyConfStu tempStu;
	tempStu.nSum = ui.spinBox_5->value();
	for (int i = 0; i < tempStu.nSum; ++i)
	{
		m_nKeyFun[i] = m_cmb_group.at(i)->currentIndex() + 1;
		tempStu.nKey[i] = m_cmb_group.at(i)->currentIndex()+1;
	}
	tempStu.reset();
	int nRet = m_pSerialPort->write((char*)&tempStu, sizeof(KeyConfStu));
	if (nRet)
	{
		qDebug() << QStringLiteral("发送按键配置成功");
		ui.lab_info->setText(QStringLiteral("发送按键配置成功"));
	}
}

//连接串口
void ConfItemWgt::slot_btn_7()
{
	QString strComName;						//串口名称
	QSerialPort::BaudRate baudRate;			//波特率
	QSerialPort::DataBits dataBits;			//数据位
	//QSerialPort::Direction direction;		//数据方向
	QSerialPort::FlowControl flowCtrl;		//流控制
	QSerialPort::Parity parity;				//奇偶校验位
	QSerialPort::StopBits stopBits;			//停止位

	strComName = ui.cmb_port->currentText();
	baudRate = static_cast<QSerialPort::BaudRate>(ui.cmb_baudRate->currentText().toInt());
	dataBits = static_cast<QSerialPort::DataBits>(ui.cmb_dataBits->currentText().toInt());
	//设置串口停止位
	if (ui.cmb_stopBits->currentText() == "1")
	{
		stopBits = QSerialPort::OneStop;
	}
	else if (ui.cmb_stopBits->currentText() == "1.5")
	{
		stopBits = QSerialPort::OneAndHalfStop;
	}
	else if (ui.cmb_stopBits->currentText() == "2")
	{
		stopBits = QSerialPort::TwoStop;
	}

	//设置串口奇偶校验位
	parity = static_cast<QSerialPort::Parity>(ui.cmb_parity->currentIndex() == 0 ? 0 : ui.cmb_parity->currentIndex() + 1);

	//设置流控制
	if (ui.cmb_flowCtrl->currentIndex() == 0)
	{
		flowCtrl = QSerialPort::NoFlowControl;
	}
	else if (ui.cmb_flowCtrl->currentIndex() == 1)
	{
		flowCtrl = QSerialPort::HardwareControl;
	}
	else if (ui.cmb_flowCtrl->currentIndex() == 2)
	{
		flowCtrl = QSerialPort::SoftwareControl;
	}

	m_pSerialPort->setPortName(strComName);
	m_pSerialPort->setBaudRate(baudRate);
	m_pSerialPort->setDataBits(dataBits);
	m_pSerialPort->setStopBits(stopBits);
	m_pSerialPort->setParity(parity);
	m_pSerialPort->setFlowControl(flowCtrl);

	bool bOpen = m_pSerialPort->open(QIODevice::ReadWrite);
	if (bOpen)
	{
		QString strTip = QStringLiteral("%1 OPENED,%2").arg(strComName).arg(baudRate);
		ui.lab_status->setText(strTip);
		connect(m_pSerialPort, &QSerialPort::readyRead, this, &ConfItemWgt::slot_port_recv);
	}
}

//关闭串口
void ConfItemWgt::slot_btn_8()
{
	m_pSerialPort->disconnect();
	m_pSerialPort->close();
	QString strTip = QStringLiteral("CLOSED");
	ui.lab_status->setText(strTip);
}

void ConfItemWgt::slot_btn_9()
{
	//获取控件值
	//音量配置
	m_volume_default = ui.spinBox->value();
	m_volume_tips = ui.spinBox_2->value();

	//充电配置
	m_charge_full_voltage = ui.doubleSpinBox->value();
	m_charge_full_current = ui.spinBox_6->value();
	m_charge_current = ui.spinBox_7->value();
	m_low_voltage_tips = ui.doubleSpinBox_3->value();
	m_low_shut_down = ui.doubleSpinBox_2->value();

	//蓝牙配置
	m_bluetooth_name = ui.lineEdit->text();
	//m_bluetooth_mac_addr = ui.edt_mac->text();
	bool bOk;
	m_bluetooth_mac_addr[0] = ui.edtMac_1->text().toInt(&bOk, 16);
	m_bluetooth_mac_addr[1] = ui.edtMac_2->text().toInt(&bOk, 16);
	m_bluetooth_mac_addr[2] = ui.edtMac_3->text().toInt(&bOk, 16);
	m_bluetooth_mac_addr[3] = ui.edtMac_4->text().toInt(&bOk, 16);
	m_bluetooth_mac_addr[4] = ui.edtMac_5->text().toInt(&bOk, 16);
	m_bluetooth_mac_addr[5] = ui.edtMac_6->text().toInt(&bOk, 16);

	m_nKeyFun[0] = ui.cmb_aj_1->currentIndex() + 1;
	m_nKeyFun[1] = ui.cmb_aj_2->currentIndex() + 1;
	m_nKeyFun[2] = ui.cmb_aj_3->currentIndex() + 1;
	m_nKeyFun[3] = ui.cmb_aj_4->currentIndex() + 1;
	m_nKeyFun[4] = ui.cmb_aj_5->currentIndex() + 1;
	m_nKeyFun[5] = ui.cmb_aj_6->currentIndex() + 1;
	m_nKeyFun[6] = ui.cmb_aj_7->currentIndex() + 1;
	m_nKeyFun[7] = ui.cmb_aj_8->currentIndex() + 1;
	m_nKeyFun[8] = ui.cmb_aj_9->currentIndex() + 1;
	m_nKeyFun[9] = ui.cmb_aj_10->currentIndex() + 1;

	m_bluetooth_send_freq = ui.spinBox_3->value();
	m_bluetooth_tm = ui.spinBox_4->value();
	//按键配置
	m_nKeySum = ui.spinBox_5->value();

	QString strPathFile = qApp->applicationDirPath();
	strPathFile += "/config/confItem/config.json";
	QFile file(strPathFile);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("保存配置失败，原因为：")+file.errorString(), QMessageBox::Yes);
	}
	else
	{
		file.resize(0);		//清空文件中的原有内容
		QJsonDocument jsonDoc;
		QJsonObject jsonRoot;			//根节点
		QJsonObject jsonVolume;		//音量配置
		QJsonObject jsonCharge;		//充电配置
		QJsonObject jsonBluetooth;	//蓝牙配置
		QJsonObject jsonKey;				//按键配置
		//音量配置
		jsonVolume["volume_default"] = m_volume_default;
		jsonVolume["volume_tips"] = m_volume_tips;
		jsonRoot["volume"] = jsonVolume;
		//充电配置
		jsonCharge["charge_full_voltage"] = m_charge_full_voltage;
		jsonCharge["charge_full_current"] = m_charge_full_current;
		jsonCharge["charge_current"] = m_charge_current;
		jsonCharge["low_voltage_tips"] = m_low_voltage_tips;
		jsonCharge["low_shut_down"] = m_low_shut_down;
		jsonRoot["charge"] = jsonCharge;
		//蓝牙配置
		jsonBluetooth["bluetooth_name"] = m_bluetooth_name;
		jsonBluetooth["bluetooth_mac_addr_1"] = m_bluetooth_mac_addr[0];
		jsonBluetooth["bluetooth_mac_addr_2"] = m_bluetooth_mac_addr[1];
		jsonBluetooth["bluetooth_mac_addr_3"] = m_bluetooth_mac_addr[2];
		jsonBluetooth["bluetooth_mac_addr_4"] = m_bluetooth_mac_addr[3];
		jsonBluetooth["bluetooth_mac_addr_5"] = m_bluetooth_mac_addr[4];
		jsonBluetooth["bluetooth_mac_addr_6"] = m_bluetooth_mac_addr[5];
		jsonBluetooth["bluetooth_send_freq"] = m_bluetooth_send_freq;
		jsonBluetooth["bluetooth_tm"] = m_bluetooth_tm;
		jsonRoot["bluetooth"] = jsonBluetooth;

		//按键配置
		jsonKey["sum"] = m_nKeySum;
		for (int i = 0; i < m_nKeySum; ++i)
		{
			jsonKey[QString("key_fun_id_%1").arg(i + 1)] = m_nKeyFun[i];
		}
		//jsonKey[""]
		//TODO
		jsonRoot["key"] = jsonKey;
		
		jsonDoc.setObject(jsonRoot);
		file.write(jsonDoc.toJson());
		file.close();
		QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("保存配置成功"), QMessageBox::Yes);
	}

	
}

void ConfItemWgt::slot_port_recv()
{
	QByteArray byteData = m_pSerialPort->readAll();
	if (byteData.length() == TX_PC_REPLY_LEN)
	{
		//TX231应答PC消息报文
		TX_PC_REPLY txReply;
		memcpy(&txReply, byteData.constData(), TX_PC_REPLY_LEN);
		txReply.reset();
		unsigned char cMsgData[TX_PC_REPLY_LEN] = { 0 };
		memcpy(cMsgData, byteData.constData(), TX_PC_REPLY_LEN);

		unsigned short nCheckSum = std::accumulate(cMsgData + 4, cMsgData + TX_PC_REPLY_LEN - 2, 0);
		if (txReply.header.syncWord == MSG_UNIFIED_MSGID && txReply.header.nMsgID== MSG_TX_PC_REPLY && nCheckSum == txReply.checksum)
		{
			if (txReply.ack_status == MSG_ACK_TX_YL_OK)
			{
				QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("音量配置成功"), QMessageBox::Yes);
			}
			else if (txReply.ack_status == MSG_ACK_TX_CD_OK)
			{
				QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("充电配置成功"), QMessageBox::Yes);
			}
			else if (txReply.ack_status == MSG_ACK_TX_LY_OK)
			{
				QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("蓝牙配置成功"), QMessageBox::Yes);
			}
			else if (txReply.ack_status == MSG_ACK_TX_AJ_OK)
			{
				QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("按键配置成功"), QMessageBox::Yes);
			}
			else if (txReply.ack_status == MSG_ACK_TX_CHECKSUM_ERROR)
			{
				QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("校验位失败"), QMessageBox::Yes);
			}
			else
			{
				QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("无效报文"), QMessageBox::Yes);
			}
		}
	}
}

void ConfItemWgt::initCmbPort()
{
	ui.cmb_port->clear();
	QList<QSerialPortInfo> lstSerials =  QSerialPortInfo::availablePorts();
    foreach (QSerialPortInfo var, lstSerials)
    {
        QString strCom = var.portName();
        if (ui.cmb_port)
        {
            ui.cmb_port->addItem(strCom);
        }
    }
	//connect(ui.cmb_port, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &ConfItemWgt::slot_cmb_port_init);
}

bool ConfItemWgt::readConfig()
{
	bool bFlag = false;
	QString strPathFile = qApp->applicationDirPath();
	strPathFile += "/config/confItem/config.json";
	qDebug() << strPathFile;
	QFile file(strPathFile);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("打开配置文件失败，原因为：") + file.errorString(), QMessageBox::Yes);
	}
	else
	{
		QByteArray allData = file.readAll();
		file.close();

		QJsonParseError jsonError;
		QJsonDocument jsonDoc(QJsonDocument::fromJson(allData, &jsonError));
		if (jsonError.error != QJsonParseError::NoError)
		{
			QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("读取配置文件失败，原因为：") + jsonError.errorString(), QMessageBox::Yes);
		}
		else
		{
			QJsonObject jsonRoot = jsonDoc.object();
			//音量配置
			QJsonObject jsonVolume = jsonRoot["volume"].toObject();
			m_volume_default = jsonVolume["volume_default"].toInt();
			m_volume_tips = jsonVolume["volume_tips"].toInt();
			//充电配置
			QJsonObject jsonCharge = jsonRoot["charge"].toObject();
			m_charge_full_voltage = jsonCharge["charge_full_voltage"].toDouble();
			m_charge_full_current = jsonCharge["charge_full_current"].toInt();
			m_charge_current = jsonCharge["charge_current"].toInt();
			m_low_voltage_tips = jsonCharge["low_voltage_tips"].toDouble();
			m_low_shut_down = jsonCharge["low_shut_down"].toDouble();
			//蓝牙配置
			QJsonObject jsonBluetooth = jsonRoot["bluetooth"].toObject();
			m_bluetooth_name = jsonBluetooth["bluetooth_name"].toString();
			m_bluetooth_mac_addr[0] = jsonBluetooth["bluetooth_mac_addr_1"].toInt();
			m_bluetooth_mac_addr[1] = jsonBluetooth["bluetooth_mac_addr_2"].toInt();
			m_bluetooth_mac_addr[2] = jsonBluetooth["bluetooth_mac_addr_3"].toInt();
			m_bluetooth_mac_addr[3] = jsonBluetooth["bluetooth_mac_addr_4"].toInt();
			m_bluetooth_mac_addr[4] = jsonBluetooth["bluetooth_mac_addr_5"].toInt();
			m_bluetooth_mac_addr[5] = jsonBluetooth["bluetooth_mac_addr_6"].toInt();
			m_bluetooth_send_freq = jsonBluetooth["bluetooth_send_freq"].toInt();
			m_bluetooth_tm = jsonBluetooth["bluetooth_tm"].toInt();
			//按键配置
			QJsonObject jsonKey = jsonRoot["key"].toObject();
			m_nKeySum = jsonKey["sum"].toInt();
			for (int i = 0; i < m_nKeySum; ++i)
			{
				m_nKeyFun[i] = jsonKey[QString("key_fun_id_%1").arg(i + 1)].toInt();
			}

			ui.spinBox->setValue(m_volume_default);
			ui.spinBox_2->setValue(m_volume_tips);

			ui.doubleSpinBox->setValue(m_charge_full_voltage);
			ui.spinBox_5->setValue(m_charge_full_current);
			ui.spinBox_5->setValue(m_charge_current);
			ui.doubleSpinBox_3->setValue(m_low_voltage_tips);
			ui.doubleSpinBox_2->setValue(m_low_shut_down);

			ui.lineEdit->setText(m_bluetooth_name);
			
			ui.edtMac_1->setText(QString::number(m_bluetooth_mac_addr[0], 16).toUpper());
			ui.edtMac_2->setText(QString::number(m_bluetooth_mac_addr[1], 16).toUpper());
			ui.edtMac_3->setText(QString::number(m_bluetooth_mac_addr[2], 16).toUpper());
			ui.edtMac_4->setText(QString::number(m_bluetooth_mac_addr[3], 16).toUpper());
			ui.edtMac_5->setText(QString::number(m_bluetooth_mac_addr[4], 16).toUpper());
			ui.edtMac_6->setText(QString::number(m_bluetooth_mac_addr[5], 16).toUpper());

			ui.spinBox_3->setValue(m_bluetooth_send_freq);
			ui.spinBox_4->setValue(m_bluetooth_tm);

			ui.spinBox_5->setValue(m_nKeySum);
			ui.cmb_aj_1->setCurrentIndex(m_nKeyFun[0] > 0 ? (m_nKeyFun[0]-1) : 0);
			ui.cmb_aj_2->setCurrentIndex(m_nKeyFun[1] > 0 ? (m_nKeyFun[1] - 1) : 0);
			ui.cmb_aj_3->setCurrentIndex(m_nKeyFun[2] > 0 ? (m_nKeyFun[2] - 1) : 0);
			ui.cmb_aj_4->setCurrentIndex(m_nKeyFun[3] > 0 ? (m_nKeyFun[3] - 1) : 0);
			ui.cmb_aj_5->setCurrentIndex(m_nKeyFun[4] > 0 ? (m_nKeyFun[4] - 1) : 0);
			ui.cmb_aj_6->setCurrentIndex(m_nKeyFun[5] > 0 ? (m_nKeyFun[5] - 1) : 0);
			ui.cmb_aj_7->setCurrentIndex(m_nKeyFun[6] > 0 ? (m_nKeyFun[6] - 1) : 0);
			ui.cmb_aj_8->setCurrentIndex(m_nKeyFun[7] > 0 ? (m_nKeyFun[7] - 1) : 0);
			ui.cmb_aj_9->setCurrentIndex(m_nKeyFun[8] > 0 ? (m_nKeyFun[8] - 1) : 0);
			ui.cmb_aj_10->setCurrentIndex(m_nKeyFun[9] > 0 ? (m_nKeyFun[9] - 1) : 0);
		}
	}
	return bFlag;
}
