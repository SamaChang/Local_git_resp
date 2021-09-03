#include "ANCSoft.h"
#include "ui_ANCSoft.h"

#include "QConfigIO.h"
#include "QConfAudioDlg.h"
#include <QSerialPortInfo>

#include "../common/datastruct/FrequencySpectrum.h"

#include "RealTimeEngine.h"
//#include "Engine.h"
#include "WaveChart.h"
#include "Config.h"
#include "QConfigAxisDlg.h"

#include <QProcess>

#include <QMessageBox>
#include <QFileDialog>

ANCSoft::ANCSoft(QWidget *parent)
	: QWidget(parent)
	, m_nSignalType(TYPE_NONE)
	//, m_mode(NoMode)
	//, m_engine(new Engine(this))
	, m_engine(new RealTimeEngine(this))
	, m_audioInputFormatConf(QAudioFormat())
	
{
	ui = new Ui::ANCSoft();
	ui->setupUi(this);

	initUI();

	Config::getIns()->initConf();
	initAudioFormat();
	ui->ancWgt->init();

}

ANCSoft::~ANCSoft()
{
	delete ui;
}

void ANCSoft::initUI()
{
	initConn();
}

void ANCSoft::initConn()
{
	connect(ui->btn_tool_open, &QPushButton::clicked, this, &ANCSoft::slot_btn_open_file);
	connect(ui->btn_tool_save, &QPushButton::clicked, this, &ANCSoft::slot_btn_save_file);

	connect(ui->btn_tool_conf_io, &QPushButton::clicked, this, &ANCSoft::slot_btn_confio);		//设置IO
	connect(ui->btn_tool_conf_axis, &QPushButton::clicked, this, &ANCSoft::slot_btn_axis);		//配置坐标系
	connect(this, &ANCSoft::sig_axis_update, ui->ancWgt, &ANCTool::slot_axis_update);
	connect(this, &ANCSoft::sig_signal_type, ui->ancWgt, &ANCTool::slot_signal_type);

	//connect(ui->btn_tool_open_file, &QPushButton::clicked, this, &ANCSoft::slot_btn_open_file);		//打开文件
	connect(ui->btn_tool_record_param, &QPushButton::clicked, this, &ANCSoft::slot_btn_record_param);		//音频参数设置
	connect(ui->btn_tool_record, &QPushButton::clicked, this, &ANCSoft::slot_btn_record);			//录音开启
	connect(ui->btn_tool_suspend, &QPushButton::clicked, this, &ANCSoft::slot_btn_suspend);			//暂停
	//connect(ui->btn_tool_playback, &QPushButton::clicked, this, &ANCSoft::slot_btn_playback);		//播放音频
	connect(ui->btn_optimal_show, &QPushButton::clicked, ui->ancWgt, &ANCTool::slot_optimal_show);

	connect(ui->comboBox_type, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &ANCSoft::slot_cmb_type_currentIndexChanged);

	connect(ui->btn_save_data_fr, &QPushButton::clicked, ui->ancWgt, &ANCTool::slot_save_data_fr);
	connect(ui->btn_save_data_phase, &QPushButton::clicked, ui->ancWgt, &ANCTool::slot_save_data_phase);
	connect(ui->comboBox_points, QOverload<int>::of(&QComboBox::currentIndexChanged), ui->ancWgt, &ANCTool::slot_comboBox_points_value_changed);

	connect(m_engine, &RealTimeEngine::formatChanged, this, &ANCSoft::slot_audio_format_changed);	//音频格式变化
	connect(m_engine, &RealTimeEngine::stateChanged, this, &ANCSoft::slot_audio_state_changed);

	//connect(m_engine, &RealTimeEngine::bufferLengthChanged, this, &ANCSoft::slot_buffer_length_changed);
	//connect(m_engine, &RealTimeEngine::recordPositionChanged, this, &ANCSoft::slot_audio_position_changed);
	//connect(m_engine, &RealTimeEngine::playPositionChanged, this, &ANCSoft::slot_audio_position_changed);
	connect(m_engine, QOverload<qint64, qint64, const FrequencySpectrum&>::of(&RealTimeEngine::spectrumChanged), this, QOverload<qint64, qint64, const FrequencySpectrum&>::of(&ANCSoft::slot_spectrum_changed));
	connect(this, &ANCSoft::sig_spectrum_changed, ui->ancWgt, &ANCTool::slot_spectrum_changed);

}

void ANCSoft::getFreqRates(int &nFreqRates)
{
	nFreqRates = ui->lab_dev_state_input_freq->text().toInt();
}

void ANCSoft::slot_btn_confio()
{
	QConfigIO dlg;
	dlg.setAudioInfo(m_engine->getAudioInputDeviceInfo(), m_engine->getAudioOutputDeviceInfo());
	if (QDialog::Accepted == dlg.exec())
	{
		//m_waveChart->reset();
		//m_engine->reset();
	}
}

void ANCSoft::slot_btn_axis()
{
	QConfigAxisDlg dlg;
	if (QDialog::Accepted == dlg.exec())
	{

		emit sig_axis_update();
	}
}

void ANCSoft::slot_btn_open_file()
{
	QString strPathFile = QApplication::applicationDirPath();
	strPathFile += "/config/ANCTool";
	QString path = QFileDialog::getOpenFileName(this, QStringLiteral("加载文件"), strPathFile, tr("CONF FILE (*.txt *.txt)"));
	if (path.length() > 0) 
	{
		bool bLoad = Config::getIns()->readJson(path);
		if (bLoad)
		{
			
		}
		else
		{
			
		}
	}
}

void ANCSoft::slot_btn_save_file()
{
	QString strPathFile = QApplication::applicationDirPath();
	strPathFile += "/config/ANCTool/";
	QString strPath = QFileDialog::getSaveFileName(this, tr("Save File"), strPathFile, tr("CONF FILE (*.txt *.txt)"));
	if (!strPath.isEmpty())
	{
		Config::getIns()->writeJson(strPath);
	}
}

void ANCSoft::slot_btn_record_param()
{
	if (ui->btn_tool_suspend->isChecked() || m_nSignalType== TYPE_NONE)
	{
		this->reset();

		QConfAudioDlg dlg;
		if (QDialog::Accepted == dlg.exec())
		{
			initAudioFormat();
			m_engine->setFormat(m_audioInputFormatConf);
		}
	}
	else
	{
		QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("请先暂停，再进行音频设置！"), QMessageBox::Yes);
	}
}

void ANCSoft::slot_btn_record()
{
	///step0 重新初始化
	///step1 设置音频参数
	///step2 初始化音频
	///step3 开始录音

	if (m_nSignalType == TYPE_REL_CJ || m_nSignalType== TYPE_NONE)
	{
		this->reset();
		int nVal = ui->lab_dev_state_input_freq->text().toInt();

		m_engine->setFormat(m_audioInputFormatConf);
		initializeRecord();
		m_engine->startRecording();
		updateButtonStates();
	}
	else
	{
		if (m_engine->isPlaybackabled())
		{
			m_engine->startPlayback();
			updateButtonStates();
			m_engine->startRecording();
		}
		else
		{
			m_engine->startPlayback();
			updateButtonStates();
			m_engine->startRecording();
			//QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("请加载音频文件后，再进行播放"), QMessageBox::Yes);
		}
	}
	
}

void ANCSoft::slot_btn_suspend()
{
	ui->ancWgt->resetData();
	m_engine->suspend();
	updateButtonStates();

}

void ANCSoft::slot_btn_playback()
{
	if (m_engine->isPlaybackabled())
	{
		m_engine->startPlayback();
		updateButtonStates();
		m_engine->startRecording();
	}
	else
	{
		QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("请加载音频文件后，再进行播放"), QMessageBox::Yes);
	}
}

////信号类型
void ANCSoft::slot_cmb_type_currentIndexChanged(int index)
{
	this->reset();

	emit sig_signal_type(index);

	switch (index)
	{
	case ANCSoft::TYPE_REL_CJ:
	{
		setSignalType(TYPE_REL_CJ);
		break;
	}
	case ANCSoft::TYPE_W_ZS:
	{
		//setMode(LoadFileMode);
		QString strPath = qApp->applicationDirPath();
		strPath += "/WaveFiles/whitenoise.wav";
		setSignalType(TYPE_W_ZS);
		bool bLoad = m_engine->loadFile(strPath);
		if (bLoad)
		{
			//ui->lab_dev_state_input_freq->setText(QString::number(m_engine->format().sampleRate()));
			//ui->lab_dev_state_input_bits->setText(QString("%1Bit").arg(m_engine->format().sampleSize()));
			//ui->lab_dev_state_input_channel->setText(QString::number(m_engine->format().channelCount()));
		}
		updateButtonStates();
		break;
	}
	case ANCSoft::TYPE_F_ZS:
	{
		//setMode(LoadFileMode);
		setSignalType(TYPE_F_ZS);
		QString strPath = qApp->applicationDirPath();
		strPath += "/WaveFiles/pinknoise.wav";
		bool bLoad = m_engine->loadFile(strPath);
		if (bLoad)
		{
			//ui->lab_dev_state_input_freq->setText(QString::number(m_engine->format().sampleRate()));
			//ui->lab_dev_state_input_bits->setText(QString("%1Bit").arg(m_engine->format().sampleSize()));
			//ui->lab_dev_state_input_channel->setText(QString::number(m_engine->format().channelCount()));
		}
		updateButtonStates();
		break;
	}
	case ANCSoft::TYPE_1K_ZXB:
	{
		setSignalType(TYPE_1K_ZXB);
		QString strPath = qApp->applicationDirPath();
		strPath += "/WaveFiles/1kHz.wav";
		bool bLoad = m_engine->loadFile(strPath);
		if (bLoad)
		{
			//ui->lab_dev_state_input_freq->setText(QString::number(m_engine->format().sampleRate()));
			//ui->lab_dev_state_input_bits->setText(QString("%1Bit").arg(m_engine->format().sampleSize()));
			//ui->lab_dev_state_input_channel->setText(QString::number(m_engine->format().channelCount()));
		}
		updateButtonStates();
		break;
	}
	case ANCSoft::TYPE_SP:
	{
		setSignalType(TYPE_SP);
		QString strPath = qApp->applicationDirPath();
		strPath += "/WaveFiles/SP.wav";
		bool bLoad = m_engine->loadFile(strPath);
		if (bLoad)
		{
			ui->lab_dev_state_input_freq->setText(QString::number(m_engine->format().sampleRate()));
			ui->lab_dev_state_input_bits->setText(QString("%1Bit").arg(m_engine->format().sampleSize()));
			ui->lab_dev_state_input_channel->setText(QString::number(m_engine->format().channelCount()));
		}
		updateButtonStates();
		break;
	}
	default:
		break;
	}
}

void ANCSoft::initializeRecord()
{
	//setMode(RecordMode);
	setSignalType(TYPE_REL_CJ);
	if (m_engine->initializeRecord())
	{
	}
	else
	{
		QMessageBox::information(nullptr, QStringLiteral("提示"), QStringLiteral("初始化音频输入设备失败"), QMessageBox::Yes);
	}
}

void ANCSoft::slot_audio_state_changed(QAudio::Mode mode, QAudio::State state)
{
	Q_UNUSED(mode);
	updateButtonStates();
	if (QAudio::ActiveState != state && QAudio::SuspendedState != state && QAudio::InterruptedState != state)
	{
		//重置

	}
}

void ANCSoft::slot_audio_format_changed(const QAudioFormat & format)
{
	if (QAudioFormat() != format)
	{
		//ui->waveChartWgt->initialize(format, WaveformTitleLength, WaveformWindowDuration);
	}
}

void ANCSoft::slot_spectrum_changed(qint64 position, qint64 length, const FrequencySpectrum &spectrum)
{
	//ui->processWgt->windowChanged(position, length);
	emit sig_spectrum_changed(1, spectrum);
}

void ANCSoft::slot_audio_position_changed(qint64 position)
{
	Q_UNUSED(position)
	//ui->waveChartWgt->audioPositionChanged(position);
}

void ANCSoft::slot_buffer_length_changed(qint64 length)
{
	//ui->processWgt->bufferLengthChanged(length);
}

void ANCSoft::updateModeMenu()
{
	//ui->actRecord->setChecked(RecordMode == m_mode);
}

void ANCSoft::updateButtonStates()
{
	if (QAudio::AudioInput == m_engine->mode())		//录音模式
	{
		if (QAudio::ActiveState == m_engine->state())	//音频状态 活动
		{
			ui->btn_tool_conf_io->setEnabled(false);
			//ui->btn_tool_open_file->setEnabled(false);
			ui->btn_tool_record->setEnabled(false);
			//ui->btn_tool_playback->setEnabled(false);
			ui->btn_tool_suspend->setEnabled(true);

			ui->btn_tool_record->setChecked(true);
			ui->btn_tool_suspend->setChecked(false);
			//ui->btn_tool_playback->setChecked(false);
		}
		else   //停止状态
		{
			ui->btn_tool_conf_io->setEnabled(true);
			//ui->btn_tool_open_file->setEnabled(true);
			ui->btn_tool_record->setEnabled(true);
			//ui->btn_tool_playback->setEnabled(true);
			ui->btn_tool_suspend->setEnabled(false);

			ui->btn_tool_record->setChecked(false);
			ui->btn_tool_suspend->setChecked(true);
			//ui->btn_tool_playback->setChecked(false);
		}
	}
	else if(QAudio::AudioInput == m_engine->mode())		//播放模式
	{
		if (QAudio::ActiveState == m_engine->state())	//音频状态 活动
		{
			ui->btn_tool_conf_io->setEnabled(false);
			//ui->btn_tool_open_file->setEnabled(false);
			ui->btn_tool_record->setEnabled(false);
			//ui->btn_tool_playback->setEnabled(false);
			ui->btn_tool_suspend->setEnabled(true);

			ui->btn_tool_record->setChecked(false);
			ui->btn_tool_suspend->setChecked(false);
			//ui->btn_tool_playback->setChecked(true);
		}
		else   //停止状态
		{
			ui->btn_tool_conf_io->setEnabled(true);
			//ui->btn_tool_open_file->setEnabled(true);
			ui->btn_tool_record->setEnabled(true);
			//ui->btn_tool_playback->setEnabled(true);
			ui->btn_tool_suspend->setEnabled(false);

			ui->btn_tool_record->setChecked(false);
			ui->btn_tool_suspend->setChecked(true);
			//ui->btn_tool_playback->setChecked(false);
		}
	}
}

void ANCSoft::closeEvent(QCloseEvent *event)
{
	//判断配置文件是否修改过
	if (Config::getIns()->isNeedSave())
	{
		int ret = QMessageBox::information(this, QStringLiteral("关闭提示"), QStringLiteral("系统配置已经修改过，是否需要保存？"), QMessageBox::Yes, QMessageBox::No);
		if (ret == QMessageBox::Yes)
		{
			Config::getIns()->saveOut();
		}
	}

	QWidget::closeEvent(event);
}

void ANCSoft::setSignalType(SIGNAL_TYPE nType)
{
	//m_mode = mode;
	m_nSignalType = nType;
}

void ANCSoft::reset()
{
	m_engine->reset();
	ui->ancWgt->resetData();
	//ui->waveChartWgt->reset();
}

void ANCSoft::initAudioFormat()
{
	m_audioInputFormatConf.setCodec("audio/pcm");
	m_audioInputFormatConf.setSampleRate(Config::getIns()->m_sys_freqRate);
	m_audioInputFormatConf.setChannelCount(Config::getIns()->m_sys_channel);
	m_audioInputFormatConf.setSampleType(QAudioFormat::SignedInt);
	m_audioInputFormatConf.setByteOrder(QAudioFormat::LittleEndian);		//设置格式为小端
	m_audioInputFormatConf.setSampleSize(16);

	ui->lab_dev_state_input_freq->setText(QString::number(m_audioInputFormatConf.sampleRate()));
	ui->lab_dev_state_input_bits->setText(QString("%1Bit").arg(m_audioInputFormatConf.sampleSize()));
	if (Config::getIns()->m_sys_channel == 1)	//单通道
	{
		ui->lab_dev_state_input_channel->setText( QStringLiteral("单声道"));
	}
	else
	{
		ui->lab_dev_state_input_channel->setText(QStringLiteral("立体声"));
	}
	m_engine->setFormat(m_audioInputFormatConf);
	
}
