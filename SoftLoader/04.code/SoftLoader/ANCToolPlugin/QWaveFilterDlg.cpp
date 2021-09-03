#include "QWaveFilterDlg.h"

#include "Config.h"
//#include "..\3rd\waveAlgorithm\skv_wolf_function.h"
#include "../3rd/math//waveAlgorithm/skv_wolf_function.h"
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QtMath>
#include <QListView>

//const int g_freqRates = 44100;		//采样频率
const int g_wave_points = 22000;	//波形采点数

QWaveFilterDlg::QWaveFilterDlg(QWidget *parent)
	: QDialog(parent)
	, m_freqData(FrequencySpectrum(g_wave_points))
{
	ui.setupUi(this);
	ui.comboBox->setView(new QListView);
	initConn();
	ui.frChartWgt->setAxis_x(20, 25000);
	ui.frChartWgt->setAxis_y(-45, 60);
	
	ui.frChartWgt->initDraw(1);
	ui.phaseChartWgt->initDraw(1);

	QString pattern("^(-?[0-9])|(-?\\d+)(.\\d{0,6})$");
	QRegExp regExp(pattern);
	ui.lineEdit_18->setValidator(new QRegExpValidator(regExp, this));
}

QWaveFilterDlg::~QWaveFilterDlg()
{
}

void QWaveFilterDlg::init(int nType, int nSerial, int nFreqRates)
{
	m_nWaveType = nType;
	m_nSerial = nSerial;
	m_nFreqRates = nFreqRates;

	initUI(nType, nSerial);

	ui.lineEdit_11->setText(QString());
	ui.lineEdit_12->setText(QString());
	ui.lineEdit_13->setText(QString());
	ui.lineEdit_14->setText(QString());
	ui.lineEdit_15->setText(QString());
	ui.lineEdit_16->setText(QString());
}

void QWaveFilterDlg::getConf(int &nType, int &nSerial, QString & strName)
{
	nType = m_nWaveType;
	nSerial = m_nSerial;
	strName = ui.comboBox->currentText();
}

void QWaveFilterDlg::initUI(int nType, int nSerial)
{
	//获取配置项
	m_cong_param = Config::getIns()->get_wave_filter_conf(WAVE_FILTER_TYPE(nType), nSerial);
	ui.comboBox->setCurrentIndex(m_cong_param.nType);
	switch (m_cong_param.nType)
	{
	case QWaveFilterDlg::FILTER_BYPASS:
	{
		ui.lineEdit->setText(QString::number(m_cong_param.freq));
		ui.lineEdit_2->setText(QString::number(m_cong_param.boost));
		ui.lineEdit_3->setText(QString::number(m_cong_param.nQ));
		ui.lineEdit_4->setText(QString::number(m_cong_param.gain));
		ui.stackedWidget->setCurrentIndex(0);
		break;
	}
	case QWaveFilterDlg::FILTER_PEAK:
	{
		ui.lineEdit->setText(QString::number(m_cong_param.freq));
		ui.lineEdit_2->setText(QString::number(m_cong_param.boost));
		ui.lineEdit_3->setText(QString::number(m_cong_param.nQ));
		ui.lineEdit_4->setText(QString::number(m_cong_param.gain));
		ui.stackedWidget->setCurrentIndex(0);
		break;
	}
	case QWaveFilterDlg::FILTER_LOWSHELF:
	case QWaveFilterDlg::FILTER_HIGHSHELF:
	{
		ui.lineEdit_5->setText(QString::number(m_cong_param.boost));
		ui.lineEdit_6->setText(QString::number(m_cong_param.freq));
		ui.lineEdit_7->setText(QString::number(m_cong_param.slope));
		ui.lineEdit_17->setText(QString::number(m_cong_param.gain));
		ui.stackedWidget->setCurrentIndex(1);
		break;
	}
	case QWaveFilterDlg::FILTER_LOWPASS:
	case QWaveFilterDlg::FILTER_HIGHPASS:
	{
		ui.lineEdit_8->setText(QString::number(m_cong_param.freq));
		ui.lineEdit_9->setText(QString::number(m_cong_param.nQ));
		ui.lineEdit_10->setText(QString::number(m_cong_param.gain));
		ui.stackedWidget->setCurrentIndex(2);
		break;
	}
	case QWaveFilterDlg::FILTER_IIR:
	{
		ui.stackedWidget->setCurrentIndex(3);
		ui.lineEdit_11->setText(QString::number(m_cong_param.boost, 'g', 12));
		ui.lineEdit_12->setText(QString::number(m_cong_param.nQ, 'g', 12));
		ui.lineEdit_13->setText(QString::number(m_cong_param.gain, 'g', 12));
		ui.lineEdit_14->setText(QString::number(1));
		ui.lineEdit_15->setText(QString::number(m_cong_param.slope, 'g', 12));
		ui.lineEdit_16->setText(QString::number(m_cong_param.spare, 'g', 12));
		break;
	}
		
	case QWaveFilterDlg::FILTER_GAIN:
		ui.stackedWidget->setCurrentIndex(4);
		ui.lineEdit_18->setText(QString::number(20* log10(m_cong_param.gain), 'g', 12));
		ui.lineEdit_19->setText(QString::number(m_cong_param.gain, 'g', 12));
		break;
	default:
		break;
	}
	
}

void QWaveFilterDlg::initConn()
{
	connect(ui.comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, QOverload<int>::of(&QWaveFilterDlg::slot_cmb_currentIndexChanged));
	connect(ui.pushButton, &QPushButton::clicked, this, &QWaveFilterDlg::slot_btn_show);
	connect(ui.pushButton_4, &QPushButton::clicked, this, &QWaveFilterDlg::slot_btn_save_conf);
	connect(ui.pushButton_5, &QPushButton::clicked, this, &QWaveFilterDlg::slot_btn_data_saveas);
	connect(ui.pushButton_6, &QPushButton::clicked, this, &QWaveFilterDlg::slot_btn_load_iir);

	connect(ui.pushButton_2, &QPushButton::clicked, this, &QWaveFilterDlg::slot_btn_set_db);
	connect(ui.pushButton_3, &QPushButton::clicked, this, &QWaveFilterDlg::slot_btn_set_xx);
}

void QWaveFilterDlg::slot_cmb_currentIndexChanged(int index)
{
	ui.lineEdit_11->setReadOnly(true);
	ui.lineEdit_12->setReadOnly(true);
	ui.lineEdit_13->setReadOnly(true);
	ui.lineEdit_14->setReadOnly(true);
	ui.lineEdit_15->setReadOnly(true);
	ui.lineEdit_16->setReadOnly(true);
	switch (index)
	{
	case QWaveFilterDlg::FILTER_BYPASS:
	case QWaveFilterDlg::FILTER_PEAK:
		ui.stackedWidget->setCurrentIndex(0);
		break;
	case QWaveFilterDlg::FILTER_LOWSHELF:
	case QWaveFilterDlg::FILTER_HIGHSHELF:
		ui.stackedWidget->setCurrentIndex(1);
		break;
	case QWaveFilterDlg::FILTER_LOWPASS:
	case QWaveFilterDlg::FILTER_HIGHPASS:
		ui.stackedWidget->setCurrentIndex(2);
		break;
	case QWaveFilterDlg::FILTER_IIR:
	{
		ui.stackedWidget->setCurrentIndex(3);
		ui.lineEdit_11->setReadOnly(false);
		ui.lineEdit_12->setReadOnly(false);
		ui.lineEdit_13->setReadOnly(false);
		ui.lineEdit_14->setReadOnly(false);
		ui.lineEdit_15->setReadOnly(false);
		ui.lineEdit_16->setReadOnly(false);
		break;
	}
	case QWaveFilterDlg::FILTER_GAIN:
		ui.stackedWidget->setCurrentIndex(4);
		break;
	default:
		break;
	}
}

void QWaveFilterDlg::slot_btn_show()
{
	///step1 首先是修改配置文件
	///step2 然后根据选中算法加载响应的图形，
	///step3 相应的图形数据保存再Config中

	m_cong_param.nType = ui.comboBox->currentIndex();		//这里需要设置
	m_cong_param.nSerial = m_nSerial;

	double* pOut = new double[6]{ 0 };
	switch (m_cong_param.nType)
	{
	case QWaveFilterDlg::FILTER_BYPASS:
	{
		pOut[0] = 1;
		pOut[1] = 0;
		pOut[2] = 0;
		pOut[3] = 1;
		pOut[4] = 0;
		pOut[5] = 0;
		break;
	}
	case QWaveFilterDlg::FILTER_PEAK:
	{	
		m_cong_param.freq = ui.lineEdit->text().toInt();
		m_cong_param.boost = ui.lineEdit_2->text().toDouble();
		m_cong_param.nQ = ui.lineEdit_3->text().toDouble();
		m_cong_param.gain = ui.lineEdit_4->text().toDouble();
		wolf_function_peak(m_cong_param.freq, m_cong_param.boost, m_cong_param.nQ, m_nFreqRates, m_cong_param.gain, pOut);
		break;
	}
	case QWaveFilterDlg::FILTER_LOWSHELF:
	{
		m_cong_param.boost = ui.lineEdit_5->text().toDouble();
		m_cong_param.gain = ui.lineEdit_17->text().toDouble();
		m_cong_param.freq = ui.lineEdit_6->text().toInt();
		m_cong_param.slope = ui.lineEdit_7->text().toDouble();
		wolf_function_low_shelving_new(m_cong_param.boost, m_cong_param.gain, m_cong_param.freq, m_nFreqRates, m_cong_param.slope, pOut);
		break;
	}
	case QWaveFilterDlg::FILTER_HIGHSHELF:
	{
		m_cong_param.boost = ui.lineEdit_5->text().toDouble();
		m_cong_param.gain = ui.lineEdit_17->text().toDouble();
		m_cong_param.freq = ui.lineEdit_6->text().toInt();
		m_cong_param.slope = ui.lineEdit_7->text().toDouble();
		wolf_function_high_shelving_new(m_cong_param.boost, m_cong_param.gain, m_cong_param.freq, m_nFreqRates, m_cong_param.slope, pOut);
		break;
	}
	case QWaveFilterDlg::FILTER_LOWPASS:
	{
		m_cong_param.freq = ui.lineEdit_8->text().toInt();
		m_cong_param.nQ = ui.lineEdit_9->text().toDouble();
		m_cong_param.gain = ui.lineEdit_10->text().toDouble();
		wolf_function_low_pass(m_nFreqRates, m_cong_param.freq, m_cong_param.nQ, m_cong_param.gain, pOut);
		break;
	}
	case QWaveFilterDlg::FILTER_HIGHPASS:
	{
		m_cong_param.freq = ui.lineEdit_8->text().toInt();
		m_cong_param.nQ = ui.lineEdit_9->text().toDouble();
		m_cong_param.gain = ui.lineEdit_10->text().toDouble();
		wolf_function_high_pass(m_nFreqRates, m_cong_param.freq, m_cong_param.nQ, m_cong_param.gain, pOut);
		break;
	}
	case QWaveFilterDlg::FILTER_IIR:
	{
		pOut[0] = ui.lineEdit_11->text().toDouble();
		pOut[1] = ui.lineEdit_12->text().toDouble();
		pOut[2] = ui.lineEdit_13->text().toDouble();
		pOut[3] = ui.lineEdit_14->text().toDouble();
		pOut[4] = ui.lineEdit_15->text().toDouble();
		pOut[5] = ui.lineEdit_16->text().toDouble();

		m_cong_param.boost = pOut[0];
		m_cong_param.nQ = pOut[1];
		m_cong_param.gain = pOut[2];
		m_cong_param.slope = pOut[4];
		m_cong_param.spare = pOut[5];
		break;
	}
	case QWaveFilterDlg::FILTER_GAIN:
	{
		double nGain = ui.lineEdit_19->text().toDouble();
		
		m_cong_param.gain = nGain;
		pOut[0] = 1* m_cong_param.gain;
		pOut[1] = 0;
		pOut[2] = 0;
		pOut[3] = 1;
		pOut[4] = 0;
		pOut[5] = 0;
		break;
	}
	default:
		break;
	}
	

	double* pOutData = new double[g_wave_points * 2]{ 0 };
	print_freqz(m_nFreqRates, 2, pOut, pOut + 3, pOutData, g_wave_points);

	ui.lineEdit_11->setText(QString::number(pOut[0]/pOut[3],'g',12));
	ui.lineEdit_12->setText(QString::number(pOut[1] / pOut[3], 'g', 12));
	ui.lineEdit_13->setText(QString::number(pOut[2] / pOut[3], 'g', 12));
	ui.lineEdit_14->setText(QString::number(1, 'g', 12));
	ui.lineEdit_15->setText(QString::number(pOut[4] / pOut[3], 'g', 12));
	ui.lineEdit_16->setText(QString::number(pOut[5] / pOut[3], 'g', 12));

	delete[] pOut;
	pOut = nullptr;

	QVector<double> x(g_wave_points, 0);
	QVector<double> y_amplitude(g_wave_points, 0);
	QVector<double> y_phase(g_wave_points, 0);
	for (int i = 0; i < g_wave_points; ++i)
	{
		x[i] = i;
		//FR_IIR_1 = 20*log10(abs(freqz_IIR1));
		qreal dVal_amplitude = -20 * log10(abs(sqrt(pow(pOutData[i * 2], 2) + pow(pOutData[i * 2+1], 2))));
		qreal dVal_phase = atan2(pOutData[i * 2 + 1], pOutData[i * 2]) * 180 / M_PI;

		m_freqData[i].amplitude = dVal_amplitude;
		m_freqData[i].phase = dVal_phase;

		y_amplitude[i] = dVal_amplitude;
		y_phase[i] = dVal_phase;
	}

	delete[] pOutData;
	pOutData = nullptr;

	ui.frChartWgt->addData(0, x, y_amplitude, true);
	ui.phaseChartWgt->addData(0, x, y_phase, true);
}

void QWaveFilterDlg::slot_btn_save_conf()
{
	Config::getIns()->set_wave_filter_conf(WAVE_FILTER_TYPE(m_nWaveType), m_cong_param);
	QString strName = ui.comboBox->currentText();
	emit sig_conf(m_nWaveType, m_nSerial, strName);
}

void QWaveFilterDlg::slot_btn_data_saveas()
{
	QString path = QFileDialog::getSaveFileName(this, tr("Save File"), QString("D://"), tr("Data TEXT (*.txt *.txt)"));
	if (path.length() == 0) {
		QMessageBox::information(NULL, QStringLiteral("提示"), QStringLiteral("请设置你要保存的文件路径"));
	}
	else {
		QFile *saveFile = new QFile(path);
		saveFile->open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text);
		QTextStream out(saveFile);

		out << ui.lineEdit_11->text() << "\n" << ui.lineEdit_12->text() << "\n" << ui.lineEdit_13->text() << "\n"<< ui.lineEdit_15->text() << "\n" << ui.lineEdit_16->text();
	
		saveFile->close();
		delete saveFile;
		saveFile = nullptr;
	}
}

void QWaveFilterDlg::slot_btn_load_iir()
{
	QString strPath = QFileDialog::getOpenFileName(this, QStringLiteral("加载文件"), QString("D://"), QString("Datas (*.txt *.txt )"));
	if (!strPath.isEmpty())
	{
		QFile *openFile = new QFile(strPath);
		openFile->open(QIODevice::ReadOnly | QIODevice::Text);
		QString byteArray = openFile->readAll();
		openFile->close();
		delete openFile;
		openFile = nullptr;

		QStringList strList = byteArray.split("\n");
		if (strList.size() == 5)
		{
			ui.lineEdit_11->setText(strList.at(0));
			ui.lineEdit_12->setText(strList.at(1));
			ui.lineEdit_13->setText(strList.at(2));
			ui.lineEdit_14->setText(QString::number(1));
			ui.lineEdit_15->setText(strList.at(3));
			ui.lineEdit_16->setText(strList.at(4));
		}
		else
		{
			QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("加载的文件不正确"), QMessageBox::Yes);
		}
	}
}

//设置dB值
void QWaveFilterDlg::slot_btn_set_db()
{
	QString text = ui.lineEdit_18->text();
	double nVal = pow(10, text.toDouble() / 20);
	ui.lineEdit_19->setText(QString::number(nVal, 'g', 12));
}

//设置线性值
void QWaveFilterDlg::slot_btn_set_xx()
{
	QString text = ui.lineEdit_19->text();
	double nVal = text.toDouble();
	nVal = fabs(nVal);
	nVal = 20 * log10(nVal);
	ui.lineEdit_18->setText(QString::number(nVal, 'g', 6));
}

void QWaveFilterDlg::testData()
{
	QString strPath = QApplication::applicationDirPath();
	strPath += "\\WaveFiles\\sample_1.txt";
	QFile *loadFile = new QFile(strPath);
	bool bOpen = loadFile->open(QIODevice::ReadOnly | QIODevice::Text);
	int nPos = 0;

	//数据初始化

	m_freqData.reset();

	while (!loadFile->atEnd())
	{
		FrequencySpectrum::Element element;
		QByteArray line = loadFile->readLine();
		QString temp = line;
		QStringList sss = temp.split("\t");
		if (sss.size() == 2)
		{
			element.frequency = sss.at(0).toDouble();
			element.amplitude = sss.at(1).toDouble();
		}
		else if (sss.size() == 3)
		{
			element.frequency = sss.at(0).toDouble();
			element.amplitude = sss.at(1).toDouble();
			element.phase = sss.at(2).toDouble();
		}
		m_freqData.push_back(element);
		++nPos;
	}

	loadFile->close();
	delete loadFile;
	loadFile = nullptr;
}
