#include "ANCTool.h"
#include "ui_ANCTool.h"

#include "../common/customplot/Utility.h"
#include "QWaveFilterDlg.h"
#include "QConfLineColorDlg.h"

//#include "..\3rd\waveAlgorithm\skv_wolf_function.h"
#include "../3rd/math/waveAlgorithm/skv_wolf_function.h"
#include "../common/serialport/HandleCom.h"

#include <QTime>
#include <qmath.h>
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include "ANCSoft.h"
#include "Config.h"

#include "../common/serialport/SerialPortDlg.h"
//#include "SerialPortDlg.h"
#include "CalcWgt.h"

ANCTool::ANCTool(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::ANCTool)
	, m_nqueueSize(1)
	, m_nSignalType(-1)
	, m_ndb(0)
	, m_spectrumCurrent(SpectrumLengthSamples)
	, m_pHandleCom(new HandleCom(this))
	, m_pWaveFilterDlg(new QWaveFilterDlg(this))
{
    ui->setupUi(this);
	initUI();
	

	m_axis_x_min = 20;			//最小频率20Hz
	m_axis_x_max = 20;

	m_fr_axis_y_min = 200;
	m_fr_axis_y_max = -300;

	m_phase_axis_y_min = 300;
	m_phase_axis_y_max = -300;
	m_pWaveFilterDlg->hide();
}

void ANCTool::initAxis()
{
	WAVE_LINE_VEC& frLineVec = Config::getIns()->getFrLinesConf();
	for (int i = 0; i < ConfWaveLinesMaxValue; ++i)
	{
		if (i >= ConfWaveLinesMaxValue - 2)
		{
			QColor strColor = QColor(frLineVec[i].clr);
			m_ckb_group_fr.button(i)->setStyleSheet(QString("color:%1").arg(frLineVec[i].clr));
			ui->frChartWgt->setLineColor(i, strColor);
			continue;
		}
		m_ckb_group_fr.button(i)->setText(frLineVec[i].name);

		QColor strColor = QColor(frLineVec[i].clr);
		m_ckb_group_fr.button(i)->setStyleSheet(QString("color:%1").arg(frLineVec[i].clr));

		ui->frChartWgt->setLineColor(i, strColor);
	}

	WAVE_LINE_VEC& phaseLineVec = Config::getIns()->getPhaseLinesConf();
	for (int i = 0; i < ConfWaveLinesMaxValue; ++i)
	{
		if (i >= ConfWaveLinesMaxValue - 2)
		{
			QColor strColor = QColor(phaseLineVec[i].clr);
			m_ckb_group_phase.button(i)->setStyleSheet(QString("color:%1").arg(phaseLineVec[i].clr));
			ui->phaseChartWgt->setLineColor(i, strColor);
			continue;
		}
		m_ckb_group_phase.button(i)->setText(phaseLineVec[i].name);

		QColor strColor = QColor(phaseLineVec[i].clr);
		m_ckb_group_phase.button(i)->setStyleSheet(QString("color:%1").arg(phaseLineVec[i].clr));

		ui->phaseChartWgt->setLineColor(i, strColor);
	}
}

void ANCTool::updateCom()
{
	QStringList strList = m_pHandleCom->getAvailablePorts();
	for each (QString var in strList)
	{
		//ui.cmb_port->addItem(var);
		ui->comboBox->addItem(var);
	}
}

void ANCTool::calcIIR(const CONF_WAVE_FILTER_PARAM &tempParam, double* pOut)
{
	int nFreqRates = Config::getIns()->m_sys_freqRate;
	switch (tempParam.nType)
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
		wolf_function_peak(tempParam.freq, tempParam.boost, tempParam.nQ, nFreqRates, tempParam.gain, pOut);
		break;
	case QWaveFilterDlg::FILTER_LOWSHELF:
		wolf_function_low_shelving_new(tempParam.boost, tempParam.gain, tempParam.freq, nFreqRates, tempParam.slope, pOut);
		break;
	case QWaveFilterDlg::FILTER_HIGHSHELF:
		wolf_function_high_shelving_new(tempParam.boost, tempParam.gain, tempParam.freq, nFreqRates, tempParam.slope, pOut);
		break;
	case QWaveFilterDlg::FILTER_LOWPASS:
		wolf_function_low_pass(nFreqRates, tempParam.freq, tempParam.nQ, tempParam.gain, pOut);
		break;
	case QWaveFilterDlg::FILTER_HIGHPASS:
		wolf_function_high_pass(nFreqRates, tempParam.freq, tempParam.nQ, tempParam.gain, pOut);
		break;
	case QWaveFilterDlg::FILTER_IIR:
	{
		pOut[0] = tempParam.boost;
		pOut[1] = tempParam.nQ;
		pOut[2] = tempParam.gain;
		pOut[3] = 1;
		pOut[4] = tempParam.slope;
		pOut[5] = tempParam.spare;
		break;
	}
	case QWaveFilterDlg::FILTER_GAIN:
	{
		pOut[0] = tempParam.gain;
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
}

ANCTool::~ANCTool()
{
    delete ui;
}

void ANCTool::init()
{
	AXIS_STRUCT& axis_fr = Config::getIns()->m_fr_chart_axis;
	ui->frChartWgt->setAxis_x(axis_fr.nMin_x, axis_fr.nMax_x);
	ui->frChartWgt->setAxis_y(axis_fr.nMin_y, axis_fr.nMax_y);

	AXIS_STRUCT& axis_phase = Config::getIns()->m_phase_chart_axis;
	ui->phaseChartWgt->setAxis_x(axis_phase.nMin_x, axis_phase.nMax_x);
	ui->phaseChartWgt->setAxis_y(axis_phase.nMin_y, axis_phase.nMax_y);

	ui->frChartWgt->initDraw(8);
	ui->phaseChartWgt->initDraw(8);

	initAxis();
	initConnect();
	connect(m_pWaveFilterDlg, &QWaveFilterDlg::sig_conf, this, &ANCTool::slot_wave_filter_dlg_conf);
	updateCom();
}

void ANCTool::initUI()
{
	//FF CHECKBOX
	m_ckb_group_ff.setExclusive(false);
	m_ckb_group_ff.addButton(ui->ff_ckb_1, 0);
	m_ckb_group_ff.addButton(ui->ff_ckb_2, 1);
	m_ckb_group_ff.addButton(ui->ff_ckb_3, 2);
	m_ckb_group_ff.addButton(ui->ff_ckb_4, 3);
	m_ckb_group_ff.addButton(ui->ff_ckb_5, 4);
	m_ckb_group_ff.addButton(ui->ff_ckb_6, 5);
	m_ckb_group_ff.addButton(ui->ff_ckb_7, 6);
	m_ckb_group_ff.addButton(ui->ff_ckb_8, 7);
	m_ckb_group_ff.addButton(ui->ff_ckb_9, 8);
	m_ckb_group_ff.addButton(ui->ff_ckb_10, 9);
	connect(&m_ckb_group_ff, QOverload<int>::of(&QButtonGroup::buttonClicked), this, &ANCTool::slot_ckb_group_ff);
	//FF
	m_btn_group_ff.addButton(ui->ff_btn_1, 0);
	m_btn_group_ff.addButton(ui->ff_btn_2, 1);
	m_btn_group_ff.addButton(ui->ff_btn_3, 2);
	m_btn_group_ff.addButton(ui->ff_btn_4, 3);
	m_btn_group_ff.addButton(ui->ff_btn_5, 4);
	m_btn_group_ff.addButton(ui->ff_btn_6, 5);
	m_btn_group_ff.addButton(ui->ff_btn_7, 6);
	m_btn_group_ff.addButton(ui->ff_btn_8, 7);
	m_btn_group_ff.addButton(ui->ff_btn_9, 8);
	m_btn_group_ff.addButton(ui->ff_btn_10, 9);
	connect(&m_btn_group_ff, static_cast<void (QButtonGroup::*)(int)>(&QButtonGroup::buttonClicked), this, &ANCTool::slot_btn_group_ff);

	//FB CHECKBOX
	m_ckb_group_fb.setExclusive(false);
	m_ckb_group_fb.addButton(ui->fb_ckb_1, 0);
	m_ckb_group_fb.addButton(ui->fb_ckb_2, 1);
	m_ckb_group_fb.addButton(ui->fb_ckb_3, 2);
	m_ckb_group_fb.addButton(ui->fb_ckb_4, 3);
	m_ckb_group_fb.addButton(ui->fb_ckb_5, 4);
	m_ckb_group_fb.addButton(ui->fb_ckb_6, 5);
	m_ckb_group_fb.addButton(ui->fb_ckb_7, 6);
	m_ckb_group_fb.addButton(ui->fb_ckb_8, 7);
	m_ckb_group_fb.addButton(ui->fb_ckb_9, 8);
	m_ckb_group_fb.addButton(ui->fb_ckb_10, 9);
	connect(&m_ckb_group_fb, QOverload<int>::of(&QButtonGroup::buttonClicked), this, &ANCTool::slot_ckb_group_fb);

	//FB
	m_btn_group_fb.addButton(ui->fb_btn_1, 0);
	m_btn_group_fb.addButton(ui->fb_btn_2, 1);
	m_btn_group_fb.addButton(ui->fb_btn_3, 2);
	m_btn_group_fb.addButton(ui->fb_btn_4, 3);
	m_btn_group_fb.addButton(ui->fb_btn_5, 4);
	m_btn_group_fb.addButton(ui->fb_btn_6, 5);
	m_btn_group_fb.addButton(ui->fb_btn_7, 6);
	m_btn_group_fb.addButton(ui->fb_btn_8, 7);
	m_btn_group_fb.addButton(ui->fb_btn_9, 8);
	m_btn_group_fb.addButton(ui->fb_btn_10, 9);
	connect(&m_btn_group_fb, static_cast<void (QButtonGroup::*)(int)>(&QButtonGroup::buttonClicked), this, &ANCTool::slot_btn_group_fb);

	//FR
	m_ckb_group_fr.setExclusive(false);
	m_ckb_group_fr.addButton(ui->fr_line_1, 0);
	m_ckb_group_fr.addButton(ui->fr_line_2, 1);
	m_ckb_group_fr.addButton(ui->fr_line_3, 2);
	m_ckb_group_fr.addButton(ui->fr_line_4, 3);
	m_ckb_group_fr.addButton(ui->fr_line_5, 4);
	m_ckb_group_fr.addButton(ui->fr_line_6, 5);
	m_ckb_group_fr.addButton(ui->fr_line_FF, 6);
	m_ckb_group_fr.addButton(ui->fr_line_FB, 7);
	connect(&m_ckb_group_fr, static_cast<void (QButtonGroup::*)(int)>(&QButtonGroup::buttonClicked), this, &ANCTool::slot_ckb_group_fr);

	m_btn_group_fr.setExclusive(false);
	m_btn_group_fr.addButton(ui->fr_line_btn_1, 0);
	m_btn_group_fr.addButton(ui->fr_line_btn_2, 1);
	m_btn_group_fr.addButton(ui->fr_line_btn_3, 2);
	m_btn_group_fr.addButton(ui->fr_line_btn_4, 3);
	m_btn_group_fr.addButton(ui->fr_line_btn_5, 4);
	m_btn_group_fr.addButton(ui->fr_line_btn_6, 5);
	connect(&m_btn_group_fr, static_cast<void (QButtonGroup::*)(int)>(&QButtonGroup::buttonClicked), this, &ANCTool::slot_btn_group_fr);

	//PHASE
	m_ckb_group_phase.setExclusive(false);
	m_ckb_group_phase.addButton(ui->phase_line_1, 0);
	m_ckb_group_phase.addButton(ui->phase_line_2, 1);
	m_ckb_group_phase.addButton(ui->phase_line_3, 2);
	m_ckb_group_phase.addButton(ui->phase_line_4, 3);
	m_ckb_group_phase.addButton(ui->phase_line_5, 4);
	m_ckb_group_phase.addButton(ui->phase_line_6, 5);
	m_ckb_group_phase.addButton(ui->phase_line_FF, 6);
	m_ckb_group_phase.addButton(ui->phase_line_FB, 7);
	connect(&m_ckb_group_phase, static_cast<void (QButtonGroup::*)(int)>(&QButtonGroup::buttonClicked), this, &ANCTool::slot_ckb_group_phase);

	m_btn_group_phase.setExclusive(false);
	m_btn_group_phase.addButton(ui->phase_line_btn_1, 0);
	m_btn_group_phase.addButton(ui->phase_line_btn_2, 1);
	m_btn_group_phase.addButton(ui->phase_line_btn_3, 2);
	m_btn_group_phase.addButton(ui->phase_line_btn_4, 3);
	m_btn_group_phase.addButton(ui->phase_line_btn_5, 4);
	m_btn_group_phase.addButton(ui->phase_line_btn_6, 5);
	connect(&m_btn_group_phase, static_cast<void (QButtonGroup::*)(int)>(&QButtonGroup::buttonClicked), this, &ANCTool::slot_btn_group_phase);
	
	
}

void ANCTool::initConnect()
{
	connect(ui->frChart_btn_conf, &QPushButton::clicked, this, &ANCTool::slot_fr_chart_conf);
	connect(ui->phaseChart_btn_conf, &QPushButton::clicked, this, &ANCTool::slot_phase_chart_conf);
	
	connect(ui->fr_line_FF, &QCheckBox::stateChanged, this, &ANCTool::slot_ckb_ff_stateChanged);
	connect(ui->fr_line_FB, &QCheckBox::stateChanged, this, &ANCTool::slot_ckb_fb_stateChanged);

	connect(ui->phase_line_FF, &QCheckBox::stateChanged, this, &ANCTool::slot_ckb_ff_stateChanged_phase);
	connect(ui->phase_line_FB, &QCheckBox::stateChanged, this, &ANCTool::slot_ckb_fb_stateChanged_phase);

	connect(ui->btn_write_hardware, &QPushButton::clicked, this, &ANCTool::slot_write_hardware);
	connect(ui->pushButton_2, &QPushButton::clicked, this, &ANCTool::slot_link_dev);

	connect(m_pHandleCom, &HandleCom::sig_send_data, this, &ANCTool::slot_recv_data);
}

void ANCTool::resetData()
{
	QList<FrequencySpectrum>().swap(m_queue_spectrum);
}

void ANCTool::addInfo(QString strLog)
{
	//ui->
}

//最优显示效果
void ANCTool::slot_optimal_show()
{
	ui->frChartWgt->setAxis_x(m_axis_x_min, m_axis_x_max);
	ui->frChartWgt->setAxis_y(m_fr_axis_y_min, m_fr_axis_y_max);
	ui->frChartWgt->reFreshAxis();
	ui->phaseChartWgt->setAxis_x(m_axis_x_min, m_axis_x_max);
	ui->phaseChartWgt->setAxis_y(m_phase_axis_y_min, m_phase_axis_y_max);
	ui->phaseChartWgt->reFreshAxis();
}

void ANCTool::slot_signal_type(int nType/*, int nVal*/)
{
	m_nSignalType = nType;
	//m_ndb = nVal;
}

void ANCTool::slot_comboBox_points_value_changed(int index)
{
	QList<FrequencySpectrum>().swap(m_queue_spectrum);
	int nVal = index+1;
	if (nVal == 21)
	{
		nVal = 1000;
	}
	m_nqueueSize = nVal;
}

void ANCTool::slot_ckb_group_fr(int nId)
{
	QCheckBox* pBtn = qobject_cast<QCheckBox*>(m_ckb_group_fr.button(nId));
	if (pBtn)
	{
		if (Qt::Checked == pBtn->checkState())
		{
			ui->frChartWgt->setLineVisible(nId, true);
		}
		else
		{
			ui->frChartWgt->setLineVisible(nId, false);
		}
	}
}

void ANCTool::slot_ckb_group_phase(int nId)
{
	QCheckBox* pBtn = qobject_cast<QCheckBox*>(m_ckb_group_phase.button(nId));
	if (pBtn)
	{
		if (Qt::Checked == pBtn->checkState())
		{
			ui->phaseChartWgt->setLineVisible(nId, true);
		}
		else
		{
			ui->phaseChartWgt->setLineVisible(nId, false);
		}
	}
}

void ANCTool::slot_btn_group_fr(int nId)
{
	if (nId == 5)
	{
		CalcWgt dlg;
		if (QDialog::Accepted == dlg.exec())
		{
			int nLine_1 = -1;
			int nLine_2 = -1;
			int nWay = -1;
			dlg.getCalc(nLine_1, nLine_2, nWay);

			FrequencySpectrum& tempSpectrum_line1 = Config::getIns()->m_fr_chart_data[nLine_1];
			FrequencySpectrum& tempSpectrum_line2 = Config::getIns()->m_fr_chart_data[nLine_2];

			int nMin = qMin(tempSpectrum_line1.count(), tempSpectrum_line2.count());


			QVector<double> x(nMin), y(nMin);
			for (int i = 0; i < nMin; ++i)
			{
				x[i] = tempSpectrum_line1[i].frequency;
				if (nWay == 1)
				{
					y[i] = tempSpectrum_line1[i].amplitude - tempSpectrum_line2[i].amplitude;
				}
				else if (nWay == 2)
				{
					y[i] = tempSpectrum_line1[i].amplitude + tempSpectrum_line2[i].amplitude;
				}
				else
				{
					y[i] = 0;
				}
			}
			ui->frChartWgt->addData(5, x, y);
		}
		return;
	}

	FrequencySpectrum& tempSpectrum = Config::getIns()->m_fr_chart_data[nId];
	tempSpectrum.reset();

	QString strPath = qApp->applicationDirPath();
	strPath += QString("/WaveFiles/wave_fr_%1.txt").arg(nId);
	QFile *saveFile = new QFile(strPath);
	int nCount = m_spectrumCurrent.count();
	QVector<double> x(nCount, 0);
	QVector<double> y(nCount, 0);
	bool bOpen = saveFile->open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text);
	if (bOpen)
	{
		QTextStream out(saveFile);
		for (int i = 0; i < nCount; ++i)
		{
			FrequencySpectrum::Element element;
			out << m_spectrumCurrent[i].frequency << "\t" << m_spectrumCurrent[i].amplitude << "\t" << m_spectrumCurrent[i].phase << "\n";

			element.frequency = m_spectrumCurrent[i].frequency;
			element.amplitude = m_spectrumCurrent[i].amplitude;
			element.phase = m_spectrumCurrent[i].phase;
			
			tempSpectrum.push_back(element);
			x[i] = element.frequency;
			y[i] = element.amplitude;
		}
	}
	saveFile->close();
	delete saveFile;

	if (bOpen)
	{
		WAVE_LINE_VEC & vecConf = Config::getIns()->getFrLinesConf();
		vecConf[nId].path = strPath;
		ui->frChartWgt->addData(nId, x, y);
	}
}

void ANCTool::slot_btn_group_phase(int nId)
{
	if (nId == 5)
	{
		CalcWgt dlg;
		if (QDialog::Accepted == dlg.exec())
		{
			int nLine_1 = -1;
			int nLine_2 = -1;
			int nWay = -1;
			dlg.getCalc(nLine_1, nLine_2, nWay);

			FrequencySpectrum& tempSpectrum_line1 = Config::getIns()->m_phase_chart_data[nLine_1];
			FrequencySpectrum& tempSpectrum_line2 = Config::getIns()->m_phase_chart_data[nLine_2];

			int nMin = qMin(tempSpectrum_line1.count(), tempSpectrum_line2.count());


			QVector<double> x(nMin), y(nMin);
			for (int i = 0; i < nMin; ++i)
			{
				x[i] = tempSpectrum_line1[i].frequency;
				if (nWay == 1)
				{
					y[i] = tempSpectrum_line1[i].phase - tempSpectrum_line2[i].phase;
				}
				else if (nWay == 2)
				{
					y[i] = tempSpectrum_line1[i].phase + tempSpectrum_line2[i].phase;
				}
				else
				{
					y[i] = 0;
				}
			}
			ui->phaseChartWgt->addData(5, x, y);
		}
		return;
	}

	FrequencySpectrum& tempSpectrum = Config::getIns()->m_phase_chart_data[nId];
	tempSpectrum.reset();

	QString strPath = qApp->applicationDirPath();
	strPath += QString("/WaveFiles/wave_phase_%1.txt").arg(nId);
	QFile *saveFile = new QFile(strPath);
	int nCount = m_spectrumCurrent.count();
	QVector<double> x(nCount, 0);
	QVector<double> y(nCount, 0);
	bool bOpen = saveFile->open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text);
	if (bOpen)
	{
		QTextStream out(saveFile);
		for (int i = 0; i < nCount; ++i)
		{
			FrequencySpectrum::Element element;
			out << m_spectrumCurrent[i].frequency << "\t" << m_spectrumCurrent[i].amplitude << "\t" << m_spectrumCurrent[i].phase << "\n";

			element.frequency = m_spectrumCurrent[i].frequency;
			element.amplitude = m_spectrumCurrent[i].amplitude;
			element.phase = m_spectrumCurrent[i].phase;

			tempSpectrum.push_back(element);
			x[i] = element.frequency;
			y[i] = element.phase;
		}
	}
	saveFile->close();
	delete saveFile;

	if (bOpen)
	{
		WAVE_LINE_VEC & vecConf = Config::getIns()->getPhaseLinesConf();
		vecConf[nId].path = strPath;
		ui->phaseChartWgt->addData(nId, x, y);
	}
}

void ANCTool::slot_ckb_ff_stateChanged(int state)
{
	//Qt::Checked
	//int nFreqRates = m_nDebugFreqRates;
	//int nSimpleCount = m_nDebugSimpleCount;
	int nFreqRates = 0;
	ANCSoft* pParent = qobject_cast<ANCSoft*>(parent());
	pParent->getFreqRates(nFreqRates);
	int nSimpleCount = nFreqRates / 2;
	if (nFreqRates <= 0)
	{
		QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("请先设置音频，再进行该操作"), QMessageBox::Yes);
		return;
	}

	QVector<double> x(nSimpleCount), y_amplitude(nSimpleCount,0), y_phase(nSimpleCount,0);
	if (Qt::Checked == state)
	{
		ui->frChartWgt->setLineVisible(6, true);
		for (int j = 0; j < 10; ++j)
		{
			if (!m_ckb_group_ff.button(j)->isChecked())
			{
				CONF_WAVE_FILTER_PARAM tempParam = Config::getIns()->get_wave_filter_conf(WAVE_FF, j+1);

				double* pOut = new double[6]{ 0 };
				
				switch (tempParam.nType)
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
					wolf_function_peak(tempParam.freq, tempParam.boost, tempParam.nQ, nFreqRates, tempParam.gain, pOut);
					break;
				case QWaveFilterDlg::FILTER_LOWSHELF:
					wolf_function_low_shelving_new(tempParam.boost, tempParam.gain, tempParam.freq, nFreqRates, tempParam.slope, pOut);
					break;
				case QWaveFilterDlg::FILTER_HIGHSHELF:
					wolf_function_high_shelving_new(tempParam.boost, tempParam.gain, tempParam.freq, nFreqRates, tempParam.slope, pOut);
					break;
				case QWaveFilterDlg::FILTER_LOWPASS:
					wolf_function_low_pass(nFreqRates, tempParam.freq, tempParam.nQ, tempParam.gain, pOut);
					break;
				case QWaveFilterDlg::FILTER_HIGHPASS:
					wolf_function_high_pass(nFreqRates, tempParam.freq, tempParam.nQ, tempParam.gain, pOut);
					break;
				case QWaveFilterDlg::FILTER_IIR:
				{
					pOut[0] = tempParam.boost;
					pOut[1] = tempParam.nQ;
					pOut[2] = tempParam.gain;
					pOut[3] = 1;
					pOut[4] = tempParam.slope;
					pOut[5] = tempParam.spare;
					break;
				}
				case QWaveFilterDlg::FILTER_GAIN:
				{
					pOut[0] = tempParam.gain;
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

				double* pOutData = new double[nSimpleCount * 2]{ 0 };
				print_freqz(nFreqRates, 2, pOut, pOut + 3, pOutData, nSimpleCount);
				for (int i = 0; i < nSimpleCount; ++i)
				{
					x[i] = i;
					//FR_IIR_1 = 20*log10(abs(freqz_IIR1));
					qreal dVal_amplitude = -20 * log10(abs(sqrt(pow(pOutData[i * 2], 2) + pow(pOutData[i * 2 + 1], 2))));
					qreal dVal_phase = atan2(pOutData[i * 2 + 1], pOutData[i * 2]) * 180 / M_PI;
					y_amplitude[i] += dVal_amplitude;
					y_phase[i] += dVal_phase;
				}

				delete[] pOut;
				pOut = nullptr;
				delete[] pOutData;
				pOutData = nullptr;
			}
			
		}
		ui->frChartWgt->addData(6, x, y_amplitude, true);
	}
	else
	{
		ui->frChartWgt->setLineVisible(6,false);
	}
}

void ANCTool::slot_ckb_fb_stateChanged(int state)
{
	int nFreqRates = 0;
	ANCSoft* pParent = qobject_cast<ANCSoft*>(parent());
	pParent->getFreqRates(nFreqRates);
	int nSimpleCount = nFreqRates / 2;

	if (nFreqRates <= 0)
	{
		QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("请先设置音频，再进行该操作"), QMessageBox::Yes);
		return;
	}


	QVector<double> x(nSimpleCount), y_amplitude(nSimpleCount, 0), y_phase(nSimpleCount, 0);
	if (Qt::Checked == state)
	{
		//ui->phaseChartWgt
		ui->frChartWgt->setLineVisible(7, true);
		for (int j = 0; j < 10; ++j)
		{
			if (!m_ckb_group_fb.button(j)->isChecked())
			{
				CONF_WAVE_FILTER_PARAM tempParam = Config::getIns()->get_wave_filter_conf(WAVE_FB, j + 1);

				double* pOut = new double[6]{ 0 };

				switch (tempParam.nType)
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
					wolf_function_peak(tempParam.freq, tempParam.boost, tempParam.nQ, nFreqRates, tempParam.gain, pOut);
					break;
				case QWaveFilterDlg::FILTER_LOWSHELF:
					wolf_function_low_shelving_new(tempParam.boost, tempParam.gain, tempParam.freq, nFreqRates, tempParam.slope, pOut);
					break;
				case QWaveFilterDlg::FILTER_HIGHSHELF:
					wolf_function_high_shelving_new(tempParam.boost, tempParam.gain, tempParam.freq, nFreqRates, tempParam.slope, pOut);
					break;
				case QWaveFilterDlg::FILTER_LOWPASS:
					wolf_function_low_pass(nFreqRates, tempParam.freq, tempParam.nQ, tempParam.gain, pOut);
					break;
				case QWaveFilterDlg::FILTER_HIGHPASS:
					wolf_function_high_pass(nFreqRates, tempParam.freq, tempParam.nQ, tempParam.gain, pOut);
					break;
				case QWaveFilterDlg::FILTER_IIR:
				{
					pOut[0] = tempParam.boost;
					pOut[1] = tempParam.nQ;
					pOut[2] = tempParam.gain;
					pOut[3] = 1;
					pOut[4] = tempParam.slope;
					pOut[5] = tempParam.spare;
					break;
				}
				case QWaveFilterDlg::FILTER_GAIN:
				{
					pOut[0] = tempParam.gain;
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

				double* pOutData = new double[nSimpleCount * 2]{ 0 };
				print_freqz(nFreqRates, 2, pOut, pOut + 3, pOutData, nSimpleCount);
				for (int i = 0; i < nSimpleCount; ++i)
				{
					x[i] = i;
					//FR_IIR_1 = 20*log10(abs(freqz_IIR1));
					qreal dVal_amplitude = -20 * log10(abs(sqrt(pow(pOutData[i * 2], 2) + pow(pOutData[i * 2 + 1], 2))));
					qreal dVal_phase = atan2(pOutData[i * 2 + 1], pOutData[i * 2]) * 180 / M_PI;
					y_amplitude[i] += dVal_amplitude;
					y_phase[i] += dVal_phase;
				}

				delete[] pOutData;
				pOutData = nullptr;
			}

		}
		ui->frChartWgt->addData(7, x, y_amplitude, true);
	}
	else
	{
		ui->frChartWgt->setLineVisible(7, false);
	}
}

void ANCTool::slot_ckb_ff_stateChanged_phase(int state)
{
	//Qt::Checked
	int nFreqRates = 0;
	ANCSoft* pParent = qobject_cast<ANCSoft*>(parent());
	pParent->getFreqRates(nFreqRates);
	int nSimpleCount = nFreqRates / 2;

	if (nFreqRates <= 0)
	{
		QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("请先设置音频，再进行该操作"), QMessageBox::Yes);
		return;
	}

	QVector<double> x(nSimpleCount), y_amplitude(nSimpleCount, 0), y_phase(nSimpleCount, 0);
	if (Qt::Checked == state)
	{
		ui->phaseChartWgt->setLineVisible(6, true);
		for (int j = 0; j < 10; ++j)
		{
			if (!m_ckb_group_ff.button(j)->isChecked())
			{
				CONF_WAVE_FILTER_PARAM tempParam = Config::getIns()->get_wave_filter_conf(WAVE_FF, j + 1);

				double* pOut = new double[6]{ 0 };

				switch (tempParam.nType)
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
					wolf_function_peak(tempParam.freq, tempParam.boost, tempParam.nQ, nFreqRates, tempParam.gain, pOut);
					break;
				case QWaveFilterDlg::FILTER_LOWSHELF:
					wolf_function_low_shelving_new(tempParam.boost, tempParam.gain, tempParam.freq, nFreqRates, tempParam.slope, pOut);
					break;
				case QWaveFilterDlg::FILTER_HIGHSHELF:
					wolf_function_high_shelving_new(tempParam.boost, tempParam.gain, tempParam.freq, nFreqRates, tempParam.slope, pOut);
					break;
				case QWaveFilterDlg::FILTER_LOWPASS:
					wolf_function_low_pass(nFreqRates, tempParam.freq, tempParam.nQ, tempParam.gain, pOut);
					break;
				case QWaveFilterDlg::FILTER_HIGHPASS:
					wolf_function_high_pass(nFreqRates, tempParam.freq, tempParam.nQ, tempParam.gain, pOut);
					break;
				case QWaveFilterDlg::FILTER_IIR:
				{
					pOut[0] = tempParam.boost;
					pOut[1] = tempParam.nQ;
					pOut[2] = tempParam.gain;
					pOut[3] = 1;
					pOut[4] = tempParam.slope;
					pOut[5] = tempParam.spare;
					break;
				}
				case QWaveFilterDlg::FILTER_GAIN:
				{
					pOut[0] = tempParam.gain;
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

				double* pOutData = new double[nSimpleCount * 2]{ 0 };
				print_freqz(nFreqRates, 2, pOut, pOut + 3, pOutData, nSimpleCount);
				for (int i = 0; i < nSimpleCount; ++i)
				{
					x[i] = i;
					//FR_IIR_1 = 20*log10(abs(freqz_IIR1));
					qreal dVal_amplitude = -20 * log10(abs(sqrt(pow(pOutData[i * 2], 2) + pow(pOutData[i * 2 + 1], 2))));
					qreal dVal_phase = atan2(pOutData[i * 2 + 1], pOutData[i * 2]) * 180 / M_PI;
					y_amplitude[i] += dVal_amplitude;
					y_phase[i] += dVal_phase;
				}

				delete[] pOut;
				pOut = nullptr;
				delete[] pOutData;
				pOutData = nullptr;
			}

		}
		ui->phaseChartWgt->addData(6, x, y_phase, true);
	}
	else
	{
		ui->phaseChartWgt->setLineVisible(6, false);
	}
}

void ANCTool::slot_ckb_fb_stateChanged_phase(int state)
{
	int nFreqRates = 0;
	ANCSoft* pParent = qobject_cast<ANCSoft*>(parent());
	pParent->getFreqRates(nFreqRates);
	int nSimpleCount = nFreqRates / 2;

	if (nFreqRates <= 0)
	{
		QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("请先设置音频，再进行该操作"), QMessageBox::Yes);
		return;
	}

	QVector<double> x(nSimpleCount), y_amplitude(nSimpleCount, 0), y_phase(nSimpleCount, 0);
	if (Qt::Checked == state)
	{
		//ui->phaseChartWgt
		ui->phaseChartWgt->setLineVisible(7, true);
		for (int j = 0; j < 10; ++j)
		{
			if (!m_ckb_group_fb.button(j)->isChecked())
			{
				CONF_WAVE_FILTER_PARAM tempParam = Config::getIns()->get_wave_filter_conf(WAVE_FB, j + 1);

				double* pOut = new double[6]{ 0 };

				switch (tempParam.nType)
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
					wolf_function_peak(tempParam.freq, tempParam.boost, tempParam.nQ, nFreqRates, tempParam.gain, pOut);
					break;
				case QWaveFilterDlg::FILTER_LOWSHELF:
					wolf_function_low_shelving_new(tempParam.boost, tempParam.gain, tempParam.freq, nFreqRates, tempParam.slope, pOut);
					break;
				case QWaveFilterDlg::FILTER_HIGHSHELF:
					wolf_function_high_shelving_new(tempParam.boost, tempParam.gain, tempParam.freq, nFreqRates, tempParam.slope, pOut);
					break;
				case QWaveFilterDlg::FILTER_LOWPASS:
					wolf_function_low_pass(nFreqRates, tempParam.freq, tempParam.nQ, tempParam.gain, pOut);
					break;
				case QWaveFilterDlg::FILTER_HIGHPASS:
					wolf_function_high_pass(nFreqRates, tempParam.freq, tempParam.nQ, tempParam.gain, pOut);
					break;
				case QWaveFilterDlg::FILTER_IIR:
				{
					pOut[0] = tempParam.boost;
					pOut[1] = tempParam.nQ;
					pOut[2] = tempParam.gain;
					pOut[3] = 1;
					pOut[4] = tempParam.slope;
					pOut[5] = tempParam.spare;
					break;
				}
				case QWaveFilterDlg::FILTER_GAIN:
				{
					pOut[0] = tempParam.gain;
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

				double* pOutData = new double[nSimpleCount * 2]{ 0 };
				print_freqz(nFreqRates, 2, pOut, pOut + 3, pOutData, nSimpleCount);
				for (int i = 0; i < nSimpleCount; ++i)
				{
					x[i] = i;
					//FR_IIR_1 = 20*log10(abs(freqz_IIR1));
					qreal dVal_amplitude = -20 * log10(abs(sqrt(pow(pOutData[i * 2], 2) + pow(pOutData[i * 2 + 1], 2))));
					qreal dVal_phase = atan2(pOutData[i * 2 + 1], pOutData[i * 2]) * 180 / M_PI;
					y_amplitude[i] += dVal_amplitude;
					y_phase[i] += dVal_phase;
				}

				delete[] pOutData;
				pOutData = nullptr;
			}

		}
		ui->phaseChartWgt->addData(7, x, y_phase, true);
	}
	else
	{
		ui->phaseChartWgt->setLineVisible(7, false);
	}
}

void ANCTool::slot_btn_group_ff(int nId)
{
	int nFreqRates = 0;
	ANCSoft* pParent = qobject_cast<ANCSoft*>(parent());
	pParent->getFreqRates(nFreqRates);
	int nSimpleCount = nFreqRates / 2;

	if (nFreqRates <= 0)
	{
		QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("请先设置音频，再进行该操作"), QMessageBox::Yes);
		return;
	}
	m_pWaveFilterDlg->init(WAVE_FF, nId + 1, nFreqRates);
	m_pWaveFilterDlg->show();
	/*
	QWaveFilterDlg dlg(WAVE_FF, nId+1, nFreqRates);
	if (QDialog::Accepted == dlg.exec())
	{
		int nType = 0;
		int nSerial = -1;
		QString strName;
		dlg.getConf(nType, nSerial, strName);
		if (!m_ckb_group_ff.button(nId)->isChecked())
		{
			CONF_WAVE_FILTER_PARAM temp = Config::getIns()->get_wave_filter_conf(WAVE_FF, nId + 1);
			QString strNNN;
			if (temp.freq > 0)
			{
				strNNN = strName + "_" + QString::number(temp.freq);
			}
			else
			{
				strNNN = strName;
			}
			m_btn_group_ff.button(nId)->setText(strNNN);
		}

		if (ui->fr_line_FF->isChecked())
		{
			slot_ckb_ff_stateChanged(Qt::Checked);
		}
		else
		{
			slot_ckb_ff_stateChanged(Qt::Unchecked);
		}

		if (ui->phase_line_FF->isChecked())
		{
			slot_ckb_ff_stateChanged_phase(Qt::Checked);
		}
		else
		{
			slot_ckb_ff_stateChanged_phase(Qt::Unchecked);
		}
	}
	*/
}

void ANCTool::slot_btn_group_fb(int nId)
{
	int nFreqRates = 0;
	ANCSoft* pParent = qobject_cast<ANCSoft*>(parent());
	pParent->getFreqRates(nFreqRates);
	int nSimpleCount = nFreqRates / 2;

	if (nFreqRates <= 0)
	{
		QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("请先设置音频，再进行该操作"), QMessageBox::Yes);
		return;
	}

	m_pWaveFilterDlg->init(WAVE_FB, nId + 1, nFreqRates);
	m_pWaveFilterDlg->show();
	/*
	QWaveFilterDlg dlg(WAVE_FB, nId + 1, nFreqRates);
	if (QDialog::Accepted == dlg.exec())
	{
		int nType = 0;
		int nSerial = -1;
		QString strName;
		dlg.getConf(nType, nSerial, strName);
		//m_btn_group_fb.button(nId)->setText(strName);
		if (!m_ckb_group_fb.button(nId)->isChecked())
		{
			CONF_WAVE_FILTER_PARAM temp = Config::getIns()->get_wave_filter_conf(WAVE_FB, nId + 1);
			QString strNNN;
			if (temp.freq > 0)
			{
				strNNN = strName + "_" + QString::number(temp.freq);
			}
			else
			{
				strNNN = strName;
			}
			m_btn_group_fb.button(nId)->setText(strNNN);
		}

		if (ui->fr_line_FF->isChecked())
		{
			slot_ckb_ff_stateChanged(Qt::Checked);
		}
		else
		{
			slot_ckb_ff_stateChanged(Qt::Unchecked);
		}

		if (ui->phase_line_FF->isChecked())
		{
			slot_ckb_ff_stateChanged_phase(Qt::Checked);
		}
		else
		{
			slot_ckb_ff_stateChanged_phase(Qt::Unchecked);
		}
	}
	*/
}

void ANCTool::slot_wave_filter_dlg_conf(int nType, int nSerial, QString strName)
{
	
	if (nType == WAVE_FF)
	{
		ui->plainTextEdit->appendPlainText(QStringLiteral("设置FF成功"));
		if (!m_ckb_group_ff.button(nSerial-1)->isChecked())
		{
			CONF_WAVE_FILTER_PARAM temp = Config::getIns()->get_wave_filter_conf(WAVE_FF, nSerial);
			QString strNNN;
			if (temp.freq > 0)
			{
				strNNN = strName + "_" + QString::number(temp.freq);
			}
			else
			{
				strNNN = strName;
			}
			m_btn_group_ff.button(nSerial-1)->setText(strNNN);
		}

		if (ui->fr_line_FF->isChecked())
		{
			slot_ckb_ff_stateChanged(Qt::Checked);
		}
		else
		{
			slot_ckb_ff_stateChanged(Qt::Unchecked);
		}

		if (ui->phase_line_FF->isChecked())
		{
			slot_ckb_ff_stateChanged_phase(Qt::Checked);
		}
		else
		{
			slot_ckb_ff_stateChanged_phase(Qt::Unchecked);
		}
	}
	else
	{
		ui->plainTextEdit->appendPlainText(QStringLiteral("设置FB成功"));
		if (!m_ckb_group_fb.button(nSerial - 1)->isChecked())
		{
			CONF_WAVE_FILTER_PARAM temp = Config::getIns()->get_wave_filter_conf(WAVE_FB, nSerial);
			QString strNNN;
			if (temp.freq > 0)
			{
				strNNN = strName + "_" + QString::number(temp.freq);
			}
			else
			{
				strNNN = strName;
			}
			m_btn_group_fb.button(nSerial-1)->setText(strNNN);
		}

		if (ui->fr_line_FB->isChecked())
		{
			slot_ckb_fb_stateChanged(Qt::Checked);
		}
		else
		{
			slot_ckb_fb_stateChanged(Qt::Unchecked);
		}

		if (ui->phase_line_FB->isChecked())
		{
			slot_ckb_fb_stateChanged_phase(Qt::Checked);
		}
		else
		{
			slot_ckb_fb_stateChanged_phase(Qt::Unchecked);
		}
	}
}


void ANCTool::slot_ckb_group_ff(int nId)
{
	if (!m_ckb_group_ff.button(nId)->isChecked())
	{
		QString strName = "bypass";
		CONF_WAVE_FILTER_PARAM temp = Config::getIns()->get_wave_filter_conf(WAVE_FF, nId + 1);
		switch (temp.nType)
		{
		case QWaveFilterDlg::FILTER_BYPASS:
			strName = "bypass";
			break;
		case QWaveFilterDlg::FILTER_PEAK:
			strName = "PEAK";
			break;
		case QWaveFilterDlg::FILTER_LOWSHELF:
			strName = "LOWSHELF";
			break;
		case QWaveFilterDlg::FILTER_HIGHSHELF:
			strName = "HIGHSHELF";
			break;
		case QWaveFilterDlg::FILTER_LOWPASS:
			strName = "LOWPASS";
			break;
		case QWaveFilterDlg::FILTER_HIGHPASS:
			strName = "HIGHPASS";
			break;
		case QWaveFilterDlg::FILTER_IIR:
			strName = "IIR";
			break;
		case QWaveFilterDlg::FILTER_GAIN:
			strName = "GAIN";
			break;
		default:
			break;
		}
		QString strNNN;
		if (temp.freq > 0)
		{
			strNNN = strName + "_" + QString::number(temp.freq);
		}
		else
		{
			strNNN = strName;
		}
		m_btn_group_ff.button(nId)->setText(strNNN);
		m_btn_group_ff.button(nId)->setStyleSheet("QPushButton{background-color: #009ad6;}");
		
	}
	else
	{
		m_btn_group_ff.button(nId)->setText("bypass");
		m_btn_group_ff.button(nId)->setStyleSheet("QPushButton{background-color: #008792;}");
	}

	if (ui->fr_line_FF->isChecked())
	{
		slot_ckb_ff_stateChanged(Qt::Checked);
	}
	else
	{
		slot_ckb_ff_stateChanged(Qt::Unchecked);
	}

	if (ui->phase_line_FF->isChecked())
	{
		slot_ckb_ff_stateChanged_phase(Qt::Checked);
	}
	else
	{
		slot_ckb_ff_stateChanged_phase(Qt::Unchecked);
	}
}

void ANCTool::slot_ckb_group_fb(int nId)
{
	if (!m_ckb_group_fb.button(nId)->isChecked())
	{
		QString strName = "bypass";
		switch (Config::getIns()->get_wave_filter_conf(WAVE_FB, nId + 1).nType)
		{
		case QWaveFilterDlg::FILTER_PEAK:
			strName = "PEAK";
			break;
		case QWaveFilterDlg::FILTER_LOWSHELF:
			strName = "LOWSHELF";
			break;
		case QWaveFilterDlg::FILTER_HIGHSHELF:
			strName = "HIGHSHELF";
			break;
		case QWaveFilterDlg::FILTER_LOWPASS:
			strName = "LOWPASS";
			break;
		case QWaveFilterDlg::FILTER_HIGHPASS:
			strName = "HIGHPASS";
			break;
		case QWaveFilterDlg::FILTER_IIR:
			strName = "IIR";
			break;
		case QWaveFilterDlg::FILTER_GAIN:
			strName = "GAIN";
			break;
		default:
			break;
		}
		m_btn_group_fb.button(nId)->setText(strName);
		m_btn_group_fb.button(nId)->setStyleSheet("QPushButton{background-color: #009ad6;}");
	}
	else
	{
		m_btn_group_fb.button(nId)->setText("bypass");
		m_btn_group_fb.button(nId)->setStyleSheet("QPushButton{background-color: #008792;}");
	}

	if (ui->fr_line_FB->isChecked())
	{
		slot_ckb_fb_stateChanged(Qt::Checked);
	}
	else
	{
		slot_ckb_fb_stateChanged(Qt::Unchecked);
	}

	if (ui->phase_line_FB->isChecked())
	{
		slot_ckb_fb_stateChanged_phase(Qt::Checked);
	}
	else
	{
		slot_ckb_fb_stateChanged_phase(Qt::Unchecked);
	}

}


void ANCTool::slot_fr_chart_conf()
{
	QConfLineColorDlg dlg(WAVE_CHART_FR);
	if (QDialog::Accepted == dlg.exec())
	{
		WAVE_LINE_VEC& frLineVec = Config::getIns()->getFrLinesConf();
		for (int i=0; i<ConfWaveLinesMaxValue; ++i)
		{
			if (i >= ConfWaveLinesMaxValue - 2)
			{
				QColor strColor = QColor(frLineVec[i].clr);
				m_ckb_group_fr.button(i)->setStyleSheet(QString("color:%1").arg(frLineVec[i].clr));
				ui->frChartWgt->setLineColor(i, strColor);
				continue;
			}
			m_ckb_group_fr.button(i)->setText(frLineVec[i].name);

			QColor strColor = QColor(frLineVec[i].clr);
			m_ckb_group_fr.button(i)->setStyleSheet(QString("color:%1").arg(frLineVec[i].clr));

			ui->frChartWgt->setLineColor(i, strColor);

			FrequencySpectrum& tempSpectrum = Config::getIns()->m_fr_chart_data[i];
			int nCount = tempSpectrum.count();
			if (nCount > 0)
			{
				QVector<double> x(nCount), y(nCount);
				for (int i = 0; i < nCount; ++i)
				{
					x[i] = tempSpectrum[i].frequency;
					y[i] = tempSpectrum[i].amplitude;
					//y[i] = tempSpectrum[i].amplitude;
				}
				ui->frChartWgt->addData(i, x, y, true);
			}
		}
	}
}

void ANCTool::slot_phase_chart_conf()
{
	QConfLineColorDlg dlg(WAVE_CHART_PHASE);
	if (QDialog::Accepted == dlg.exec())
	{
		WAVE_LINE_VEC& phaseLineVec = Config::getIns()->getPhaseLinesConf();
		for (int i = 0; i < ConfWaveLinesMaxValue; ++i)
		{

			if (i >= ConfWaveLinesMaxValue - 2)
			{
				QColor strColor = QColor(phaseLineVec[i].clr);
				m_ckb_group_phase.button(i)->setStyleSheet(QString("color:%1").arg(phaseLineVec[i].clr));
				ui->phaseChartWgt->setLineColor(i, strColor);
				continue;
			}

			m_ckb_group_phase.button(i)->setText(phaseLineVec[i].name);

			QColor strColor = QColor(phaseLineVec[i].clr);
			m_ckb_group_phase.button(i)->setStyleSheet(QString("color:%1").arg(phaseLineVec[i].clr));

			ui->phaseChartWgt->setLineColor(i, strColor);

			FrequencySpectrum& tempSpectrum = Config::getIns()->m_phase_chart_data[i];
			int nCount = tempSpectrum.count();
			if (nCount > 0)
			{
				QVector<double> x(nCount), y(nCount);
				for (int i = 0; i < nCount; ++i)
				{
					x[i] = tempSpectrum[i].frequency;
					y[i] = tempSpectrum[i].phase;
				}
				ui->phaseChartWgt->addData(i, x, y, true);
			}
		}
	}
}

void ANCTool::slot_spectrum_changed(int nType, const FrequencySpectrum &spectrum)
{
	if (nType == 1)
	{
		QTime testTm;
		testTm.start();
		m_spectrumData = spectrum;
		//m_spectrumCurrent.reset();
		
		//int nCount = spectrum.count();
		int nCount = spectrum.count();
		if (nCount <= 0)
		{
			return;
		}
		QVector<double> x(nCount), y_fr(nCount), y_phase(nCount);

		if (m_queue_spectrum.size() >= m_nqueueSize)
		{
			m_queue_spectrum.pop_front();
			m_queue_spectrum.append(spectrum);
		}
		else
		{
			m_queue_spectrum.append(spectrum);
		}

		for (int i = 0; i < nCount; ++i)
		{
			//double nVal_x = 0;
			double nVal_y_fr = 0;
			double nVal_y_phase = 0;
			x[i] = spectrum[i].frequency;
			m_spectrumCurrent[i].frequency = x[i];
			for (int j = 0; j < m_queue_spectrum.size(); ++j)
			{
				const FrequencySpectrum &tempSpectrum = m_queue_spectrum[j];
				nVal_y_fr += tempSpectrum[i].amplitude;
				nVal_y_phase += tempSpectrum[i].phase;
			}
			//x[i] = nVal_x / m_queue_spectrum.size();
			y_fr[i] = nVal_y_fr / m_queue_spectrum.size();
			y_phase[i] = nVal_y_phase / m_queue_spectrum.size();
			m_spectrumCurrent[i].amplitude = y_fr[i];
			m_spectrumCurrent[i].phase = y_phase[i];

			if (m_nSignalType > 0)
			{
				y_fr[i] = y_fr[i] + m_ndb;
			}
			 
			m_fr_axis_y_min = y_fr[i] > m_fr_axis_y_min ? m_fr_axis_y_min : y_fr[i];
			m_fr_axis_y_max = y_fr[i] > m_fr_axis_y_max ? y_fr[i] : m_fr_axis_y_max;

			m_phase_axis_y_min = y_phase[i] > m_phase_axis_y_min ? m_phase_axis_y_min : y_phase[i];
			m_phase_axis_y_max = y_phase[i] > m_phase_axis_y_max ? y_phase[i] : m_phase_axis_y_max;
		}

		//最优显示x轴
		m_axis_x_max = x[nCount - 1];

		ui->frChartWgt->addData(0, x, y_fr, true);
		ui->phaseChartWgt->addData(0, x, y_phase, true);
		qDebug() << QStringLiteral("slot_spectrum_changed运行时间：") << testTm.elapsed() << "ms";
	}
}

void ANCTool::slot_axis_update()
{
	Config::getIns()->setAxisModified(true);
	AXIS_STRUCT & axis_fr = Config::getIns()->m_fr_chart_axis;
	ui->frChartWgt->setAxis_x(axis_fr.nMin_x, axis_fr.nMax_x);
	ui->frChartWgt->setAxis_y(axis_fr.nMin_y, axis_fr.nMax_y);
	ui->frChartWgt->reFreshAxis();

	AXIS_STRUCT & axis_phase = Config::getIns()->m_phase_chart_axis;
	ui->phaseChartWgt->setAxis_x(axis_phase.nMin_x, axis_phase.nMax_x);
	ui->phaseChartWgt->setAxis_y(axis_phase.nMin_y, axis_phase.nMax_y);
	ui->phaseChartWgt->reFreshAxis();
}

void ANCTool::slot_save_data_phase()
{
	QString path = QFileDialog::getSaveFileName(this, tr("Save File"), QString("D://"), tr("Data TEXT (*.txt *.txt)"));
	if (path.length() == 0) {
		QMessageBox::information(NULL, QStringLiteral("提示"), QStringLiteral("请设置你要保存的文件路径"));
	}
	else {
		QFile *saveFile = new QFile(path);
		saveFile->open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text);
		QTextStream out(saveFile);
		for (int i = 0; i < m_spectrumData.count(); ++i)
		{
			out << m_spectrumData[i].frequency << "\t" << m_spectrumData[i].amplitude << "\t" << m_spectrumData[i].phase << "\n";
		}
		saveFile->close();
		delete saveFile;
		saveFile = nullptr;
	}
}

void ANCTool::slot_write_hardware()
{
	
	int nFreqRates = 0;
	ANCSoft* pParent = qobject_cast<ANCSoft*>(parent());
	pParent->getFreqRates(nFreqRates);
	int nSimpleCount = nFreqRates / 2;

	if (nFreqRates <= 0)
	{
		QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("请先设置音频，再进行该操作"), QMessageBox::Yes);
		return;
	}

	QVector<IIR_INFO> vec_iir_FF(10);
	for (int i = 0; i< 10; ++i)
	{
		if (!m_ckb_group_ff.button(i)->isChecked())
		{
			CONF_WAVE_FILTER_PARAM tempParam = Config::getIns()->get_wave_filter_conf(WAVE_FF, i + 1);

			double* pOut = new double[6]{ 0 };

			switch (tempParam.nType)
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
				wolf_function_peak(tempParam.freq, tempParam.boost, tempParam.nQ, nFreqRates, tempParam.gain, pOut);
				break;
			case QWaveFilterDlg::FILTER_LOWSHELF:
				wolf_function_low_shelving_new(tempParam.boost, tempParam.gain, tempParam.freq, nFreqRates, tempParam.slope, pOut);
				break;
			case QWaveFilterDlg::FILTER_HIGHSHELF:
				wolf_function_high_shelving_new(tempParam.boost, tempParam.gain, tempParam.freq, nFreqRates, tempParam.slope, pOut);
				break;
			case QWaveFilterDlg::FILTER_LOWPASS:
				wolf_function_low_pass(nFreqRates, tempParam.freq, tempParam.nQ, tempParam.gain, pOut);
				break;
			case QWaveFilterDlg::FILTER_HIGHPASS:
				wolf_function_high_pass(nFreqRates, tempParam.freq, tempParam.nQ, tempParam.gain, pOut);
				break;
			case QWaveFilterDlg::FILTER_IIR:
			{
				pOut[0] = tempParam.boost;
				pOut[1] = tempParam.nQ;
				pOut[2] = tempParam.gain;
				pOut[3] = 1;
				pOut[4] = tempParam.slope;
				pOut[5] = tempParam.spare;
				break;
			}
			case QWaveFilterDlg::FILTER_GAIN:
			{
				pOut[0] = tempParam.gain;
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
			vec_iir_FF[i].b0 = pOut[0];
			vec_iir_FF[i].b1 = pOut[1];
			vec_iir_FF[i].b2 = pOut[2];
			vec_iir_FF[i].a0 = pOut[3];
			vec_iir_FF[i].a1 = pOut[4];
			vec_iir_FF[i].a2 = pOut[5];
			delete[] pOut;
			pOut = nullptr;
		}
	}

	QVector<IIR_INFO> vec_iir_FB(10);
	for (int i = 0; i < 10; ++i)
	{
		if (!m_ckb_group_fb.button(i)->isChecked())
		{
			CONF_WAVE_FILTER_PARAM tempParam = Config::getIns()->get_wave_filter_conf(WAVE_FB, i + 1);

			double* pOut = new double[6]{ 0 };

			switch (tempParam.nType)
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
				wolf_function_peak(tempParam.freq, tempParam.boost, tempParam.nQ, nFreqRates, tempParam.gain, pOut);
				break;
			case QWaveFilterDlg::FILTER_LOWSHELF:
				wolf_function_low_shelving_new(tempParam.boost, tempParam.gain, tempParam.freq, nFreqRates, tempParam.slope, pOut);
				break;
			case QWaveFilterDlg::FILTER_HIGHSHELF:
				wolf_function_high_shelving_new(tempParam.boost, tempParam.gain, tempParam.freq, nFreqRates, tempParam.slope, pOut);
				break;
			case QWaveFilterDlg::FILTER_LOWPASS:
				wolf_function_low_pass(nFreqRates, tempParam.freq, tempParam.nQ, tempParam.gain, pOut);
				break;
			case QWaveFilterDlg::FILTER_HIGHPASS:
				wolf_function_high_pass(nFreqRates, tempParam.freq, tempParam.nQ, tempParam.gain, pOut);
				break;
			case QWaveFilterDlg::FILTER_IIR:
			{
				pOut[0] = tempParam.boost;
				pOut[1] = tempParam.nQ;
				pOut[2] = tempParam.gain;
				pOut[3] = 1;
				pOut[4] = tempParam.slope;
				pOut[5] = tempParam.spare;
				break;
			}
			case QWaveFilterDlg::FILTER_GAIN:
			{
				pOut[0] = tempParam.gain;
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
			vec_iir_FB[i].b0 = pOut[0];
			vec_iir_FB[i].b1 = pOut[1];
			vec_iir_FB[i].b2 = pOut[2];
			vec_iir_FB[i].a0 = pOut[3];
			vec_iir_FB[i].a1 = pOut[4];
			vec_iir_FB[i].a2 = pOut[5];
			delete[] pOut;
			pOut = nullptr;
		}
	}
	
	/*
	SerialPortDlg w(this, Config::getIns()->m_nPowerOfTwo);
	w.setData(vec_iir_FF,vec_iir_FB);
	w.exec();
	*/
	
	//按照A0等于1进行处理
	//都除以a0操作
	for (int i = 0; i < vec_iir_FF.count(); ++i)
	{
		IIR_INFO & temp = vec_iir_FF[i];
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
	int nSend = m_pHandleCom->sendData(vec_iir_FF, MSG_SEND_ANC_TX_FF);
	if (nSend > 0)
	{
		ui->plainTextEdit->appendPlainText(QStringLiteral("发送FF成功"));
	}
	else
	{
		ui->plainTextEdit->appendPlainText(QStringLiteral("发送FF失败"));
	}


	for (int i = 0; i < vec_iir_FB.count(); ++i)
	{
		IIR_INFO & temp = vec_iir_FB[i];
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
	nSend = m_pHandleCom->sendData(vec_iir_FB, MSG_SEND_ANC_TX_FB);
	if (nSend > 0)
	{
		ui->plainTextEdit->appendPlainText(QStringLiteral("发送FB成功"));
	}
	else
	{
		ui->plainTextEdit->appendPlainText(QStringLiteral("发送FB失败"));
	}
	
}

void ANCTool::slot_link_dev()
{
	COM_INFO tempCom;
	tempCom.strComName = ui->comboBox->currentText();
	if (!tempCom.strComName.isEmpty())
	{
		if (ui->pushButton_2->isChecked())
		{
			m_pHandleCom->setComParam(tempCom);
			bool bOpen = m_pHandleCom->openCom();
			if (bOpen)
			{
				ui->pushButton_2->setText(QStringLiteral("断开"));
				ui->plainTextEdit->appendPlainText(QStringLiteral("设备连接成功"));
			}
			else
			{
				ui->plainTextEdit->appendPlainText(QStringLiteral("设备连接失败"));
			}
		}
		else
		{
			ui->pushButton_2->setText(QStringLiteral("连接"));
			m_pHandleCom->closeCom();
			ui->plainTextEdit->appendPlainText(QStringLiteral("设备断开"));
		}
	}
}

void ANCTool::slot_recv_data(QByteArray strData)
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
				ui->plainTextEdit->appendPlainText(QStringLiteral("EQ配置传输成功"));
			}
			else if (txReply.ack_status == MSG_ACK_TX_ANC_FB_OK)
			{
				ui->plainTextEdit->appendPlainText(QStringLiteral("ANC.FB配置传输成功"));
			}
			else if (txReply.ack_status == MSG_ACK_TX_ANC_FF_OK)
			{
				ui->plainTextEdit->appendPlainText(QStringLiteral("ANC.FF配置传输成功"));
			}
			else if (txReply.ack_status == MSG_ACK_TX_CHECKSUM_ERROR)
			{
				ui->plainTextEdit->appendPlainText(QStringLiteral("校验失败"));
			}
			else
			{
				ui->plainTextEdit->appendPlainText(QStringLiteral("无效报文"));
			}
		}
	}
}



void ANCTool::slot_save_data_fr()
{
	QString path = QFileDialog::getSaveFileName(this, tr("Save File"), QString("D://"), tr("Data TEXT (*.txt *.txt)"));
	if (path.length() == 0) {
		QMessageBox::information(NULL, QStringLiteral("提示"), QStringLiteral("请设置你要保存的文件路径"));
	}
	else {
		QFile *saveFile = new QFile(path);
		saveFile->open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text);
		QTextStream out(saveFile);
		for (int i=0; i<m_spectrumData.count(); ++i)
		{
			out << m_spectrumData[i].frequency << "\t" << m_spectrumData[i].amplitude << "\t" << m_spectrumData[i].phase << "\n";
		}
		saveFile->close();
		delete saveFile;
		saveFile = nullptr;
	}
}
