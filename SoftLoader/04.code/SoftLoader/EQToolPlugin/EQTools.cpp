#include "EQTools.h"

#include "../common/serialport/SerialPortDlg.h"
#include "../common/serialport/HandleCom.h"
#include "../3rd/math/waveAlgorithm/skv_wolf_function.h"

#include <QDebug>
#include <QTime>
#include <QFileDialog>
#include <qmath.h>
#include <QMessageBox>
#include <QRegExp>
#include <QRegExpValidator>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

const int g_wave_points = 22000;				//波形采点数

EQTools::EQTools(QWidget *parent)
	: QWidget(parent)
	, m_vec_data(10,  FrequencySpectrum(g_wave_points))
	, m_vec_IIR(10)
	, m_pOutData(new double[g_wave_points * 2]{ 0 })
	, m_nFreq(44100)
	, m_nPeakMax(30)
	, m_nPeakError(0)
	, m_nVoice(0)
	, m_nPowerOfTwo(27)
	, m_pHandleCom(new HandleCom(this))
{
	ui.setupUi(this);
	setWindowIcon(QIcon(":/Img/image/wave.ico"));

	initUI();

	connect(ui.pushButton, &QPushButton::clicked, this, &EQTools::slot_btn_open);
	connect(ui.pushButton_2, &QPushButton::clicked, this, &EQTools::slot_btn_save);
	connect(ui.pushButton_3, &QPushButton::clicked, this, &EQTools::slot_btn_link_dev);
	connect(ui.pushButton_4, &QPushButton::clicked, this, &EQTools::slot_btn_write_hardware);
	connect(ui.pushButton_5, &QPushButton::clicked, this, &EQTools::slot_btn_clear_log_info);
	connect(m_pHandleCom, &HandleCom::sig_send_data, this, &EQTools::slot_recv_data);

	ui.chartWgt->initDraw();
	bool bLoad = readCommonJson();
	if (!bLoad)
	{
		QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("加载初始配置文件失败"), QMessageBox::Yes);
	}
	updateCom();
}

EQTools::~EQTools()
{
}

void EQTools::initUI()
{
	
	m_vec_comboCtrl.push_back(ComboCtrl(0, ui.slider_band,	 ui.spinBox_boost,    ui.edt_Q));
	m_vec_comboCtrl.push_back(ComboCtrl(1, ui.slider_band_2, ui.spinBox_boost_2,  ui.edt_Q_2));
	m_vec_comboCtrl.push_back(ComboCtrl(2, ui.slider_band_3, ui.spinBox_boost_3,  ui.edt_Q_3));
	m_vec_comboCtrl.push_back(ComboCtrl(3, ui.slider_band_4, ui.spinBox_boost_4,  ui.edt_Q_4));
	m_vec_comboCtrl.push_back(ComboCtrl(4, ui.slider_band_5, ui.spinBox_boost_5,  ui.edt_Q_5));
	m_vec_comboCtrl.push_back(ComboCtrl(5, ui.slider_band_6, ui.spinBox_boost_6,  ui.edt_Q_6));
	m_vec_comboCtrl.push_back(ComboCtrl(6, ui.slider_band_7, ui.spinBox_boost_7,  ui.edt_Q_7));
	m_vec_comboCtrl.push_back(ComboCtrl(7, ui.slider_band_8, ui.spinBox_boost_8,  ui.edt_Q_8));
	m_vec_comboCtrl.push_back(ComboCtrl(8, ui.slider_band_9, ui.spinBox_boost_9,  ui.edt_Q_9));
	m_vec_comboCtrl.push_back(ComboCtrl(9, ui.slider_band_10,ui.spinBox_boost_10, ui.edt_Q_10));

	connect(ui.slider_voice, &QSlider::valueChanged, this, &EQTools::slot_voice_valueChanged);
	ui.slider_voice->setPageStep(1);
	connect(ui.chartWgt, &QEQLinesChart::sig_freq_point_changed, this, &EQTools::slot_chart_boost_valueChanged);
	for (ComboCtrl &var : m_vec_comboCtrl)
	{
		connect(var.m_pSlider, &QSlider::valueChanged, this, &EQTools::slot_slider_valueChanged);
		var.m_pSlider->setPageStep(1);

		connect(var.m_pSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &EQTools::slot_spinbox_valueChanged);

		connect(var.m_pQEdt, &QLineEdit::textChanged, this, &EQTools::slot_Q_textChanged);		
		var.nBoost = 0;
		var.dQ = 1;
		//加入正则表达式
		//QString pattern("^(-?[0-9])|(-?\\d+)(\.\\d{0,3})$");
		QString pattern("^(-?[0-9])|(-?\\d+)(.\\d{0,3})$");
		QRegExp regExp(pattern);
		var.m_pQEdt->setValidator(new QRegExpValidator(regExp, this));
		/*
		connect(var.m_pBoostEdt, &QLineEdit::textChanged, this, &EQTools::slot_boost_textChanged);
		QString pattern_boost("^([0-9])|(\\d+)(\.\\d{0,1})$");
		QRegExp regExp_boost(pattern);
		var.m_pBoostEdt->setValidator(new QRegExpValidator(regExp_boost, this));
		*/
	}

	//connect(ui.tbtn_com, &QPushButton::clicked, this, &EQTools::slot_tbtn_com);
	//currentIndexChanged(const QString &text)
	connect(ui.comboBox, QOverload<const QString &>::of(&QComboBox::currentIndexChanged), [this](const QString &text){
		m_nFreq = text.toInt();
	});

	connect(ui.btn_setting, &QPushButton::clicked, [this] {
		if (m_nPeakMax != ui.spinBox->value())
		{
			m_nPeakMax = ui.spinBox->value();
			QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("当前峰值已设置为%1").arg(m_nPeakMax), QMessageBox::Yes);
		}
	});
}

void EQTools::setWaveChart(int nIndex, double nBoost, double nQ, int nTotal_gain)
{
	QVector<double> x_2 = { 31,63,125,250,500,1000,2000,4000,8000,16000 };

	int fc = x_2[nIndex];	//中心频率

	//int fs = 22050;	//采样频率
	//int nTotal_gain = 0;		//全局增益

	double* pOut = new double[6]{0};
	double dVal_voice_xishu = 1.0;
	

	if ( abs(nBoost-0) < 0.0001 && nQ == 1)		//说明没有调节这个波形
	{
		pOut[0] = 1;
		pOut[1] = 0;
		pOut[2] = 0;
		pOut[3] = 1;
		pOut[4] = 0;
		pOut[5] = 0;
	}
	else
	{
		wolf_function_peak(fc, nBoost, nQ, m_nFreq, 0, pOut);	
	}

	if (m_nVoice != 0 && nIndex == 0)
	{
		dVal_voice_xishu = pow(10, m_nVoice / 20.0);
		pOut[0] *= dVal_voice_xishu;
		pOut[1] *= dVal_voice_xishu;
		pOut[2] *= dVal_voice_xishu;
	}

	m_vec_IIR[nIndex].b0 = pOut[0];
	m_vec_IIR[nIndex].b1 = pOut[1];
	m_vec_IIR[nIndex].b2 = pOut[2];
	m_vec_IIR[nIndex].a0 = pOut[3];
	m_vec_IIR[nIndex].a1 = pOut[4];
	m_vec_IIR[nIndex].a2 = pOut[5];
	
	//m_pOutData
	memset(m_pOutData, 0, g_wave_points * 2);
	print_freqz(m_nFreq, 2, pOut, pOut + 3, m_pOutData, g_wave_points);

	delete[] pOut;
	pOut = nullptr;

	QVector<double> x(g_wave_points,0);
	QVector<double> y(g_wave_points,0);
	
	QVector<double> y_2(10, 0);
	for (int i = 0,nPos=0; i < g_wave_points; ++i)
	{
		//FR_IIR_1 = 20*log10(abs(freqz_IIR1));
		//此处不明包为什么会取反
		m_vec_data[nIndex][i].amplitude = -20 * log10(abs(sqrt(pow(*(m_pOutData + i * 2), 2) + pow(*(m_pOutData + i * 2 + 1), 2))));
		x[i] = i;
		for (int j = 0; j < 10; ++j)
		{
			y[i] += m_vec_data[j][i].amplitude;
		}
		
		if (y[i]-m_nPeakMax > 0.000001)
		{
			int nError = qCeil(y[i] - m_nPeakMax);
			m_nPeakError = nError > m_nPeakError ? nError : m_nPeakError;		//加1的目的是不超过峰值
		}

		if (nPos<10 && x_2[nPos] == i)
		{
			y_2[nPos] = y[i];
			++nPos;
		}
	}
	
	if (m_nPeakError > 0)
	{
		m_nVoice = m_nVoice - m_nPeakError;
		m_nPeakError = 0;
		ui.slider_voice->setValue(m_nVoice);
		
		//ui.edt_voice->setText(QString("%1dB").arg(m_nVoice));
	}
	else
	{
		ui.chartWgt->addData(0, x, y, x_2, y_2);
	}
}

bool EQTools::readCommonJson()
{
	QString strPathFile = QApplication::applicationDirPath();
	strPathFile = strPathFile + QString("/config/EQTool/common.json");
	QFile file(strPathFile);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		qDebug() << QStringLiteral("打开文件失败,错误信息为：") << file.errorString();
		return false;
	}

	QByteArray allData = file.readAll();
	file.close();

	QJsonParseError jsonError;
	QJsonDocument jsonDoc(QJsonDocument::fromJson(allData, &jsonError));

	if (jsonError.error != QJsonParseError::NoError)
	{
		qDebug() << "json error!" << jsonError.errorString();
		return false;
	}

	QJsonObject root = jsonDoc.object();
	m_nPowerOfTwo = root["powerOfTwo"].toInt();
	return true;
}

void EQTools::updateCom()
{
	QStringList strList = m_pHandleCom->getAvailablePorts();
	for each (QString var in strList)
	{
		//ui.cmb_port->addItem(var);
		ui.comboBox_2->addItem(var);
	}
}

void EQTools::slot_voice_valueChanged(int nTotal_Gain)
{
	m_nVoice = nTotal_Gain;
	ui.edt_voice->setText(QString("%1dB").arg(nTotal_Gain));

	//ui.chartWgt->set_freq_point_voice(nTotal_Gain);


	ComboCtrl &var = m_vec_comboCtrl[0];
	setWaveChart(var.m_nIndex, var.nBoost, var.dQ, nTotal_Gain);
	
}

void EQTools::slot_slider_valueChanged(int nVal)
{
	QSlider* pSlider = qobject_cast<QSlider*>(sender());
	if (!pSlider)
	{
		return;
	}

	double dVar = nVal / 10.0;

	for (ComboCtrl &var : m_vec_comboCtrl)
	{
		if (var.m_pSlider == pSlider)
		{
			//var.m_pBoostEdt->setText(QString::number(dVar, 'f', 1));
			var.m_pSpinBox->setValue(dVar);
			var.nBoost = dVar;
			//ui.chartWgt->set_freq_point_change(var.m_nIndex, nVal);
			setWaveChart(var.m_nIndex, var.nBoost, var.dQ);
			break;
		}
	}
}

void EQTools::slot_spinbox_valueChanged(double dVal)
{
	QDoubleSpinBox* pSpinBoost = qobject_cast<QDoubleSpinBox*>(sender());
	if (!pSpinBoost)
	{
		return;
	}

	for (ComboCtrl &var : m_vec_comboCtrl)
	{
		if (var.m_pSpinBox == pSpinBoost)
		{
			int nValue = dVal * 10;
			var.m_pSlider->setValue(nValue);
			break;
		}
	}
}

void EQTools::slot_boost_textChanged(const QString &text)
{
	return;

	QString strText = text;

	QLineEdit* pEdtBoost = qobject_cast<QLineEdit*>(sender());
	if (!pEdtBoost)
	{
		return;
	}

	strText.replace(QString::fromLocal8Bit("【"), "");
	strText.replace(QString::fromLocal8Bit("】"), "");
	strText.replace(QString::fromLocal8Bit("？"), "");
	strText.replace(QString::fromLocal8Bit("！"), "");
	strText.replace(QString::fromLocal8Bit("·"), "");
	strText.replace(QString::fromLocal8Bit("￥"), "");
	strText.replace(QString::fromLocal8Bit("……"), "");
	strText.replace(QString::fromLocal8Bit("（"), "");
	strText.replace(QString::fromLocal8Bit("）"), "");
	strText.replace(QString::fromLocal8Bit("——"), "");
	strText.replace(QString::fromLocal8Bit("、"), "");
	strText.replace(QString::fromLocal8Bit("："), "");
	strText.replace(QString::fromLocal8Bit("；"), "");
	strText.replace(QString::fromLocal8Bit("“"), "");    //引号两边分开过滤
	strText.replace(QString::fromLocal8Bit("”"), "");
	strText.replace(QString::fromLocal8Bit("’"), "");    //引号两边分开过滤
	strText.replace(QString::fromLocal8Bit("‘"), "");
	strText.replace(QString::fromLocal8Bit("《"), "");
	strText.replace(QString::fromLocal8Bit("》"), "");
	strText.replace(QString::fromLocal8Bit("，"), "");
	strText.replace(QString::fromLocal8Bit("。"), "");
	pEdtBoost->setText(strText);

	/*
	for (ComboCtrl &var : m_vec_comboCtrl)
	{
		if (var.m_pBoostEdt == pEdtBoost)
		{
			int nValue = strText.toInt() * 10;
			var.m_pSlider->setValue(nValue);
			break;
		}
	}
*/
}

void EQTools::slot_Q_textChanged(const QString &text)
{
	QString strText = text;
	
	QLineEdit* pEdtQ = qobject_cast<QLineEdit*>(sender());
	if (!pEdtQ)
	{
		return;
	}
	
	strText.replace(QString::fromLocal8Bit("【"), "");
	strText.replace(QString::fromLocal8Bit("】"), "");
	strText.replace(QString::fromLocal8Bit("？"), "");
	strText.replace(QString::fromLocal8Bit("！"), "");
	strText.replace(QString::fromLocal8Bit("·"), "");
	strText.replace(QString::fromLocal8Bit("￥"), "");
	strText.replace(QString::fromLocal8Bit("……"), "");
	strText.replace(QString::fromLocal8Bit("（"), "");
	strText.replace(QString::fromLocal8Bit("）"), "");
	strText.replace(QString::fromLocal8Bit("——"), "");
	strText.replace(QString::fromLocal8Bit("、"), "");
	strText.replace(QString::fromLocal8Bit("："), "");
	strText.replace(QString::fromLocal8Bit("；"), "");
	strText.replace(QString::fromLocal8Bit("“"), "");    //引号两边分开过滤
	strText.replace(QString::fromLocal8Bit("”"), "");
	strText.replace(QString::fromLocal8Bit("’"), "");    //引号两边分开过滤
	strText.replace(QString::fromLocal8Bit("‘"), "");
	strText.replace(QString::fromLocal8Bit("《"), "");
	strText.replace(QString::fromLocal8Bit("》"), "");
	strText.replace(QString::fromLocal8Bit("，"), "");
	strText.replace(QString::fromLocal8Bit("。"), "");
	pEdtQ->setText(strText);
	

	double dVal = text.toDouble();
	if (abs(dVal) < 0.01)
	{
		return;
	}

	for (ComboCtrl &var : m_vec_comboCtrl)
	{
		if (var.m_pQEdt == pEdtQ)
		{
			var.dQ = dVal;
			setWaveChart(var.m_nIndex, var.nBoost, var.dQ);
			break;
		}
	}
}

void EQTools::slot_chart_boost_valueChanged(int nIndex, int nVal)
{
	for (ComboCtrl &var : m_vec_comboCtrl)
	{
		if (var.m_nIndex == nIndex)
		{
			var.m_pSlider->setValue(nVal);
			var.nBoost = nVal;
			//var.m_pBoostEdt->setText(QString("%1dB").arg(QString::number(nVal / 10.0, 'f', 1)));
			//var.m_pBoostEdt->setText(QString::number(nVal / 10.0, 'f', 1));
			var.m_pSpinBox->setValue(nVal / 10.0);
			setWaveChart(nIndex, var.nBoost, var.dQ);
			break;
		}
	}
}

/*
void EQTools::slot_tbtn_com()
{
	SerialPortDlg w(this, 27);
	w.setData(m_vec_IIR);
	w.exec();
}
*/

void EQTools::slot_btn_open()
{
	QString strPathFile = QApplication::applicationDirPath();
	strPathFile += "/config/EQTool";
	QString path = QFileDialog::getOpenFileName(this, QStringLiteral("加载文件"), strPathFile, tr("CONF FILE (*.txt *.txt)"));
	if (path.length() == 0) {
		QMessageBox::information(NULL, QStringLiteral("提示"), QStringLiteral("请设置你要保存的文件路径"));
	}
	else 
	{
		QFile saveFile(path);
		if (saveFile.open(QIODevice::ReadOnly | QIODevice::Text))
		{
			QByteArray allData = saveFile.readAll();
			saveFile.close();

			QJsonParseError jsonError;
			QJsonDocument jsonDoc(QJsonDocument::fromJson(allData, &jsonError));
			if (jsonError.error == QJsonParseError::NoError)
			{
				QJsonObject root = jsonDoc.object();
				
				QJsonArray jsonArray = root["eqtool_conf"].toArray();
				if (jsonArray.count() <= 0)
				{
					QMessageBox::information(NULL, QStringLiteral("提示"), QStringLiteral("配置文件格式格式错误，加载失败"), QMessageBox::Yes);
					return;
				}
				for (int i = 0; i < jsonArray.count(); ++i)
				{
					QJsonObject jsonObj = jsonArray.at(i).toObject();
					int nIndex = jsonObj["serial"].toInt();
					double nBoost = jsonObj["boost"].toDouble();
					double nQ = jsonObj["Q"].toDouble();
					for (int j = 0; j < m_vec_comboCtrl.count(); ++j)
					{
						ComboCtrl &tempStu = m_vec_comboCtrl[j];
						if (nIndex == tempStu.m_nIndex)
						{
							tempStu.nBoost = nBoost;
							tempStu.dQ = nQ;
							tempStu.m_pQEdt->setText(QString::number(nQ));
							tempStu.m_pSpinBox->setValue(nBoost);
							break;
						}
					}
				}

				m_nVoice = root["sys_dB"].toInt();
				ui.slider_voice->setValue(m_nVoice);
			}
			else
			{
				QMessageBox::information(NULL, QStringLiteral("提示"), QStringLiteral("配置文件格式格式错误，加载失败"), QMessageBox::Yes);
			}
		}

	}
}

void EQTools::slot_btn_save()
{
	QString strPathFile = QApplication::applicationDirPath();
	strPathFile += "/config/EQTool/";
	QString strPath = QFileDialog::getSaveFileName(this, tr("Save File"), strPathFile, tr("CONF FILE (*.txt *.txt)"));
	if (strPath.isEmpty())
	{
		QMessageBox::information(NULL, QStringLiteral("提示"), QStringLiteral("请设置你要保存的文件路径"));
	}
	else
	{
		//QFile* pFile = new QFile(strPath)
		QFile file(strPath);
		if (file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
		{
			file.resize(0);	//清空文件中的原有内容
			QJsonDocument jsonDoc;
			QJsonObject root;
			QJsonArray jsonArray;
			for (int i = 0; i < m_vec_comboCtrl.count(); ++i)
			{
				QJsonObject jsonObj;
				ComboCtrl & tempStu = m_vec_comboCtrl[i];
				jsonObj["serial"] = tempStu.m_nIndex;
				jsonObj["boost"] = tempStu.nBoost;
				jsonObj["Q"] = tempStu.dQ;
				jsonArray.push_back(jsonObj);
			}
			root["eqtool_conf"] = jsonArray;
			root["sys_dB"] = m_nVoice;
			jsonDoc.setObject(root);

			file.write(jsonDoc.toJson());
			file.close();
		}
	}
}

void EQTools::slot_btn_link_dev()
{
	if (ui.pushButton_3->isChecked())
	{
		
		COM_INFO tempCom;
		tempCom.strComName = ui.comboBox_2->currentText();
		if (!tempCom.strComName.isEmpty())
		{
			m_pHandleCom->setComParam(tempCom);
			bool bOpen = m_pHandleCom->openCom();
			if (bOpen)
			{
				ui.pushButton_3->setText(QStringLiteral("断开"));
				ui.plainTextEdit->appendPlainText(QStringLiteral("设备连接成功"));
			}
			else
			{
				ui.plainTextEdit->appendPlainText(QStringLiteral("设备连接失败"));
			}
		}
	}
	else
	{
		ui.pushButton_3->setText(QStringLiteral("连接"));
		m_pHandleCom->closeCom();
		ui.plainTextEdit->appendPlainText(QStringLiteral("设备断开"));
	}
}

void EQTools::slot_btn_write_hardware()
{
	//m_vec_IIR
	//按照A0等于1进行处理
	//都除以a0操作
	for (int i = 0; i < m_vec_IIR.count(); ++i)
	{
		IIR_INFO & temp = m_vec_IIR[i];
		if (fabs(temp.a0) > 0.00001)			//认为a0不是零时
		{
			temp.b0 = temp.b0 / temp.a0;
			temp.b1 = temp.b1 / temp.a0;
			temp.b2 = temp.b2 / temp.a0;
			temp.a1 = temp.a1 / temp.a0;
			temp.a2 = temp.a2 / temp.a0;
			temp.a0 = 1;

		}
	}
	int nSend = m_pHandleCom->sendData(m_vec_IIR, MSG_SEND_EQ_TX);
	if (nSend > 0)
	{
		ui.plainTextEdit->appendPlainText(QStringLiteral("发送EQ成功"));
	}
	else
	{
		ui.plainTextEdit->appendPlainText(QStringLiteral("发送EQ失败"));
	}
}

void EQTools::slot_btn_clear_log_info()
{
	ui.plainTextEdit->clear();
}

void EQTools::slot_recv_data(QByteArray strData)
{
	QByteArray byteArray = strData;
	QString strArray;
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
				ui.plainTextEdit->appendPlainText(QStringLiteral("EQ配置传输成功"));
			}
			else if (txReply.ack_status == MSG_ACK_TX_CHECKSUM_ERROR)
			{
				ui.plainTextEdit->appendPlainText(QStringLiteral("校验失败"));
			}
			else
			{
				ui.plainTextEdit->appendPlainText(QStringLiteral("无效报文"));
			}
		}
	}
}

