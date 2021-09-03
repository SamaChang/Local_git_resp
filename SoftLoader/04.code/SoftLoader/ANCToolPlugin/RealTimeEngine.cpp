#include "RealTimeEngine.h"

#include <QAudioInput>
#include <QAudioOutput>
#include <QMetaObject>
#include <QCoreApplication>
#include <QMessageBox>

#include "Config.h"


RealTimeEngine::RealTimeEngine(QObject *parent)
	: QObject(parent)
	, m_mode(QAudio::AudioInput)
	, m_state(QAudio::StoppedState)
	, m_format(QAudioFormat())
	, m_audioInput(nullptr)
	, m_audioInputInfo(QAudioDeviceInfo::defaultInputDevice())
	, m_audioInputIODev(nullptr)
	, m_audioOutput(nullptr)
	, m_audioOutputInfo(QAudioDeviceInfo::defaultOutputDevice())
	, m_file(nullptr)
	, m_analysisFile(nullptr)
	, m_bufferLength(32768)
	, m_dataLength(0)
	, m_bufferPos(0)
	, m_bEnd(false)
	, m_spectrumBufferLength(0)
	, m_spectrumPos(0)

{
	//注册类
	qRegisterMetaType<FrequencySpectrum>("FrequencySpectrum");
	connect(&m_spectrumAnalyser, QOverload<const FrequencySpectrum&>::of(&SpectrumAnalyser::spectrumChanged), this, QOverload<const FrequencySpectrum&>::of(&RealTimeEngine::spectrumChanged));
}

RealTimeEngine::~RealTimeEngine()
{
}

void RealTimeEngine::setFormat(const QAudioFormat & format)
{
	//判断音频模式是否改变
	const bool changed = (format != m_format);
	m_format = format;
	//计算声谱图缓冲长度
	qDebug() <<"set format--------"<< format;
	m_spectrumBufferLength = SpectrumLengthSamples*(m_format.sampleSize() / 8)*m_format.channelCount();
	if (changed)
	{
		emit formatChanged(m_format);
	}
}

void RealTimeEngine::reset()
{
	stopRecording();
	stopPlayback();
	setState(QAudio::AudioInput, QAudio::StoppedState);
	//setFormat(QAudioFormat());
	delete m_file;
	m_file = nullptr;
	delete m_analysisFile;
	m_analysisFile = nullptr;
	resetAudioDevices();
}

void RealTimeEngine::setAudioInputDeviceInfo(const QAudioDeviceInfo & device)
{
	if (device.deviceName() != m_audioInputInfo.deviceName())
	{
		m_audioInputInfo = device;
		initialize();
	}
}

void RealTimeEngine::setAudioOutputDeviceInfo(const QAudioDeviceInfo & device)
{
	if (device.deviceName() != m_audioOutputInfo.deviceName())
	{
		m_audioOutputInfo = device;
		initialize();
	}
}

bool RealTimeEngine::loadFile(const QString & fileName)
{
	reset();
	bool result = false;
	Q_ASSERT(!m_file);
	Q_ASSERT(!fileName.isEmpty());
	m_file = new WavFile(this);
	if (m_file->open(fileName))
	{
		if (isPCMS16LE(m_file->fileFormat()))
		{
			resetAudioDevices();		//重置音频输入输出
			m_buffer.resize(m_bufferLength);
			m_buffer.fill(0);

			m_audioInput = new QAudioInput(m_audioInputInfo, m_format, this);
			//设置发送notify()信号的时间间隔。这个ms时间间隔与操作系统平台相关，并不是实际的ms数
			m_audioInput->setNotifyInterval(NotifyIntervalMs);

			m_audioOutput = new QAudioOutput(m_audioOutputInfo, m_file->fileFormat(), this);
			m_audioOutput->setNotifyInterval(NotifyIntervalMs);
			result = true;
			//result = initialize();
		}
		else
		{
			QMessageBox::information(nullptr, QStringLiteral("提示"), QStringLiteral("音频参数不支持该文件格式"), QMessageBox::Yes);
		}
	}
	else
	{
		QMessageBox::information(nullptr, QStringLiteral("提示"), QStringLiteral("不能打开该文件"), QMessageBox::Yes);
	}
	if (result)
	{
		m_analysisFile = new WavFile(this);
		m_analysisFile->open(fileName);
	}
	return result;
}

bool RealTimeEngine::isPlaybackabled()
{
	bool bFlag = false;
	if (m_file)
	{
		bFlag = true;
	}
	return bFlag;
}

bool RealTimeEngine::initializeRecord()
{
	return initialize();
}

void RealTimeEngine::startRecording()
{
	if (m_audioInput)
	{
		if (QAudio::AudioInput == m_mode && QAudio::SuspendedState == m_state)
		{
			m_audioInput->suspend();
			m_audioInput->resume();		//重新开始

			m_audioOutput->suspend();
			m_audioOutput->resume();
		}
		else
		{
			m_spectrumAnalyser.cancelCalculation();
			//stopPlayback();
			//m_mode = QAudio::AudioInput;

			connect(m_audioInput, &QAudioInput::stateChanged, this, &RealTimeEngine::audioStateChanged);
			connect(m_audioInput, &QAudioInput::notify, this, &RealTimeEngine::audioNotify);

			m_audioInputIODev = m_audioInput->start();
			connect(m_audioInputIODev, &QIODevice::readyRead, this, &RealTimeEngine::audioDataReady);
		}
		bool bLoadFFTEngine = m_spectrumAnalyser.initFFTEngine(m_format.sampleRate(),m_format.sampleSize(),m_format.channelCount());
		int mmmm = 0;
	}
}

void RealTimeEngine::startPlayback()
{
	if (m_audioOutput)
	{
		if (QAudio::AudioOutput == m_mode && QAudio::SuspendedState == m_state)
		{
			m_audioOutput->suspend();
			m_audioOutput->resume();

			m_audioInput->suspend();
			m_audioInput->resume();
		}
		else
		{
			m_spectrumAnalyser.cancelCalculation();
			//stopRecording();
			//m_mode = QAudio::AudioOutput;
			connect(m_audioOutput, &QAudioOutput::stateChanged, this, &RealTimeEngine::audioStateChanged);
			connect(m_audioOutput, &QAudioOutput::notify, this, &RealTimeEngine::audioNotify);
		}

		if (m_file)
		{
			m_file->seek(0);
			m_audioOutput->start(m_file);
		}
		else
		{
			m_audioOutputIODev.close();
			//m_audioOutputIODev.setBuffer(&m_buffer);
			m_audioOutputIODev.open(QIODevice::ReadOnly);
			m_audioOutput->start(&m_audioOutputIODev);
		}
	}
}

void RealTimeEngine::suspend()
{
	if (QAudio::ActiveState == m_state || QAudio::IdleState == m_state)
	{
		m_audioInput->suspend();
		m_audioOutput->suspend();
		m_spectrumAnalyser.unitFFTEngine();
	}
}

void RealTimeEngine::audioStateChanged(QAudio::State state)
{
	qDebug() << "RealTimeEngine::audioStateChanged from" << m_state << "to" << m_state;
	if (QAudio::IdleState == state && m_file && m_file->pos()== m_file->size())
	{
		m_file->seek(0);
		m_audioOutput->start(m_file);
		//reset();
		//QMessageBox::information(nullptr, QStringLiteral("提示"), QStringLiteral("播放完毕"), QMessageBox::Yes);
	}
	else
	{
		if (QAudio::StoppedState == state)
		{
			QAudio::Error error = QAudio::NoError;
			switch (m_mode)
			{
			case QAudio::AudioInput:
				error = m_audioInput->error();
				break;
			case QAudio::AudioOutput:
				error = m_audioOutput->error();
				break;
			default:
				break;
			}
			if (QAudio::NoError != error)
			{
				reset();
				return;
			}
		}
		setState(state);
	}

}

void RealTimeEngine::audioNotify()
{
	QAudioOutput* pSender = qobject_cast<QAudioOutput*>(sender());
	if (pSender)
	{
		int mmmm = 0;
	}
	switch (m_mode)
	{
	case QAudio::AudioInput:
	{
		//processedUSecs 返回自调用start（）以来处理的音频数据量
		/*
		const qint64 recordPos = audioLength(m_format, m_audioInput->processedUSecs());
		if (m_dataLength >= m_spectrumBufferLength && !m_bEnd)
		{
			//计算最新的声谱图缓冲区数据
			const qint64 spectrumPosition = m_dataLength - m_spectrumBufferLength;
			calculateSpectrum(spectrumPosition);
		}
		*/
		break;
	}
	case QAudio::AudioOutput:
	{
		int mmm = 0;
		break;
	}
	default:
		break;
	}
}

void RealTimeEngine::audioDataReady()
{
	int nBufferSize = m_audioInput->bufferSize();
	const qint64 bytesReady = m_audioInput->bytesReady();
	qint64 nMaxLen = 1000000;	//32768;
	QByteArray cDataArray;
	cDataArray.resize(nMaxLen);
	//qint64 nReadMax = qMin(bytesReady, m_spectrumBufferLength);
	qint64 nReadMax = qMin(bytesReady, nMaxLen);


	const qint64 nRead = m_audioInputIODev->read(cDataArray.data(), nReadMax);
	qDebug() << "read---------------------------------" << nRead;
	
	if (nRead)
	{
		//每个单元的大小，如果双声道，左右声道的大小
		int nCellSize = m_format.sampleSize()*m_format.channelCount() / 8;

		const char* pAddr = cDataArray.constData();

		if (m_spectrumPos == 0)
		{
			//几个波形数据
			int nTime = nRead/m_spectrumBufferLength;
			//剩下的波形长度
			m_spectrumPos = nRead%m_spectrumBufferLength;
			for (int i=0; i<nTime; ++i)
			{
				m_spectrumBuffer = QByteArray::fromRawData(cDataArray.constData()+i*m_spectrumBufferLength, m_spectrumBufferLength);
				m_spectrumAnalyser.calculate(m_spectrumBuffer, m_format);
			}
			memcpy(m_buffer.data(), cDataArray.data(), m_spectrumPos);
		}
		else
		{
			if (nRead + m_spectrumPos >= m_spectrumBufferLength)
			{
				memcpy(m_buffer.data()+m_spectrumPos, cDataArray.data(), m_spectrumBufferLength - m_spectrumPos);
				m_spectrumBuffer = QByteArray::fromRawData(m_buffer, m_spectrumBufferLength);
				m_spectrumAnalyser.calculate(m_spectrumBuffer, m_format);

				int nTemp = nRead - m_spectrumBufferLength + m_spectrumPos;
				int nTime = nTemp/m_spectrumBufferLength;
				//剩下的波形长度
				m_spectrumPos = nTemp%m_spectrumBufferLength;
				for (int i = 0; i < nTime; ++i)
				{
					m_spectrumBuffer = QByteArray::fromRawData(cDataArray.constData() + i*m_spectrumBufferLength, m_spectrumBufferLength);
					m_spectrumAnalyser.calculate(m_spectrumBuffer, m_format);
				}
				memcpy(m_buffer.data(), cDataArray.data(), m_spectrumPos);
			}
			else if (nRead + m_spectrumPos < m_spectrumBufferLength)
			{
				memcpy(m_buffer.data()+m_spectrumPos, cDataArray.data(), nRead);
				m_spectrumPos += nRead;
			}
		}
		/*
		//m_spectrumPos += nRead;
		if (m_spectrumPos+nRead < m_spectrumBufferLength)
		{
			memcpy(m_buffer.data() + m_spectrumPos, cDataArray.data(), nRead);
			m_spectrumPos += nRead;
		}
		else if (m_spectrumPos + nRead >= m_spectrumBufferLength)
		{
			int nRemain = m_spectrumBufferLength - m_spectrumPos;
			memcpy(m_buffer.data() + m_spectrumPos, cDataArray.data(), nRemain);
			m_spectrumBuffer = QByteArray::fromRawData(m_buffer.constData(), m_spectrumBufferLength);
			m_spectrumAnalyser.calculate(m_spectrumBuffer, m_format);
			m_buffer.fill(0);
			memcpy(m_buffer.data(), cDataArray.data(), nRead-nRemain);
			m_spectrumPos = nRead - nRemain;
		}
		*/
	}
	else
	{
		qDebug() << "error-----" << m_audioInputIODev->errorString();
	}
}

void RealTimeEngine::spectrumChanged(const FrequencySpectrum & spectrum)
{
	emit spectrumChanged(m_spectrumPos, m_spectrumBufferLength, spectrum);
}

void RealTimeEngine::resetAudioDevices()
{
	delete m_audioInput;
	m_audioInput = nullptr;
	m_audioInputIODev = nullptr;

	delete m_audioOutput;
	m_audioOutput = nullptr;
	//setPlayPosition(0);

}

bool RealTimeEngine::initialize()
{
	bool result = false;
	QAudioFormat format = m_format;
	if (slectedFormat())		//查询是否已设置音频参数信息
	{
		if (m_format != format || m_format != QAudioFormat())
		{
			resetAudioDevices();	//重置音频输入输出
		}

		if (m_file)	//如果是播放设置一些参数
		{
			m_buffer.resize(m_bufferLength);
			m_buffer.fill(0);
		}
		else     //录音设置一些参数
		{
			m_buffer.resize(m_bufferLength);
			m_buffer.fill(0);
		}
		result = true;

		m_audioInput = new QAudioInput(m_audioInputInfo, m_format, this);
		//设置发送notify()信号的时间间隔。这个ms时间间隔与操作系统平台相关，并不是实际的ms数
		m_audioInput->setNotifyInterval(NotifyIntervalMs);

		m_audioOutput = new QAudioOutput(m_audioOutputInfo, m_format, this);
		m_audioOutput->setNotifyInterval(NotifyIntervalMs);
	}
	else
	{
		if (m_file)
		{
			QMessageBox::information(nullptr, QStringLiteral("提示"), QStringLiteral("当前音频参数不支持！！！"), QMessageBox::Yes);
		}
		else
		{
			//QMessageBox::information(nullptr, QStringLiteral("提示"), QStringLiteral("音频参数未设置！！！"), QMessageBox::Yes);
		}
	}
	qDebug() << "RealTimeEngine::initialize" << "format" << m_format;
	return result;
}

bool RealTimeEngine::slectedFormat()
{
	bool foundSupportedFormat = true;
	if (QAudioFormat() == m_format)
	{
		//QAudioFormat format = m_format;
		/*
		if (m_file)
		{
			format = m_file->fileFormat();
		}
		*/
		//检查设备的输出音频设备是否支持视频格式参数
		/*
		if (m_audioOutputInfo.isFormatSupported(format))
		{
			setFormat(format);
			foundSupportedFormat = true;
		}
		*/
		//setFormat(format);
		foundSupportedFormat = false;
	}
	return foundSupportedFormat;
}

void RealTimeEngine::stopRecording()
{
	if (m_audioInput)
	{
		m_audioInput->stop();
		m_audioInputIODev->disconnect();
		//processEvents函数主要是将正在处理的事件的控制权还给Qt
		QCoreApplication::instance()->processEvents();
		m_audioInput->disconnect();
	}
	m_audioInputIODev = nullptr;
}

void RealTimeEngine::stopPlayback()
{
	if (m_audioOutput)
	{
		m_audioOutput->stop();
		QCoreApplication::instance()->processEvents();
		m_audioOutput->disconnect();
		//setPlayPosition(0);
	}
}

void RealTimeEngine::setState(QAudio::State state)
{
	const bool changed = (m_state != state);
	m_state = state;
	if (changed)
	{
		emit stateChanged(m_mode, m_state);
	}
}

void RealTimeEngine::setState(QAudio::Mode mode, QAudio::State state)
{
	const bool changed = (m_mode != mode || m_state != state);
	m_mode = mode;
	m_state = state;
	if (changed)
	{
		emit stateChanged(m_mode, m_state);
	}
}

void RealTimeEngine::calculateSpectrum(qint64 position)
{
	if (m_spectrumAnalyser.isReady())
	{
		m_spectrumBuffer = QByteArray::fromRawData(m_buffer.constData() + position - m_bufferPos, m_spectrumBufferLength);
		m_spectrumPos = position;
		m_spectrumAnalyser.calculate(m_spectrumBuffer, m_format);
	}
}
