#include "SpectrumAnalyser.h"

//#ifdef FFTREAL_USED

//#endif

#ifdef FFTREAL_USED
#include "fftreal/fftreal_wrapper.h"
#endif

//#include "../3rd/math/FFT/skv_fftwrap.h"
#include "../3rd/math/skv/skv_preprocess.h"

#include <qmath.h>
#include <math.h>
#include <QMetaType>
#include <QAudioFormat>
#include <QThread>
//#include "math/skv_fftwrap.h"


SpectrumAnalyserThread::SpectrumAnalyserThread(QObject *parent)
	: QObject(parent)
#ifdef FFTREAL_USED
	, m_fft(new FFTRealWrapper)
#endif
	, m_numSamples(SpectrumLengthSamples)
	, m_windowFunction(DefaultWindowFunction)
	, m_window(SpectrumLengthSamples, 0.0)
	, m_input(SpectrumLengthSamples, 0.0)
	, m_input_left(SpectrumLengthSamples, 0.0)
	, m_input_right(SpectrumLengthSamples, 0.0)
	, m_output(SpectrumLengthSamples, 0.0)
	, m_output_left(SpectrumLengthSamples, 0.0)
	, m_output_right(SpectrumLengthSamples, 0.0)
	, m_spectrum(SpectrumLengthSamples)
	, m_thread(new QThread(this))
{
	setParent(0);
	qRegisterMetaType<QVector<COMPLEX_OUT>>("QVector<COMPLEX_OUT>");
	moveToThread(m_thread);
	m_thread->start();

	calculateWindow();
}

SpectrumAnalyserThread::~SpectrumAnalyserThread()
{
	//delete m_fft;
}

void SpectrumAnalyserThread::setWindowFunction(WindowFunction type)
{
	m_windowFunction = type;
	calculateWindow();
}

void SpectrumAnalyserThread::calculateSpectrum_single(const QVector<COMPLEX_OUT> & input_left, int inputFrequency, int bytesPerSample, int nChannels)
{
	int nSize = input_left.count();
	for (int i = 0; i < nSize; ++i)
	{
		//计算频率
		m_spectrum[i].frequency = qreal(i*inputFrequency / 2) / (nSize);
		const qreal magnitude_left = qSqrt(input_left[i].realVal*input_left[i].realVal + input_left[i].imagVal*input_left[i].imagVal);
		m_spectrum[i].amplitude = SpectrumAnalyserMultiplier*log10(abs(magnitude_left));

		if (isnormal(m_spectrum[i].amplitude) == 0)
		{
			m_spectrum[i].amplitude = 0;
		}
		//m_spectrum[i].phase = atan2(imag_right, real_right) / M_PI * 180 -atan2(imag_left, real_left)/M_PI*180;
		const qreal phase_left = atan2(input_left[i].imagVal, input_left[i].realVal) / M_PI * 180;
		m_spectrum[i].phase = phase_left;
	}

	emit calculattionComplete(m_spectrum);
	QThread::msleep(1);
}

void SpectrumAnalyserThread::calculateSpectrum_music(const QVector<COMPLEX_OUT> & input_left, const QVector<COMPLEX_OUT> & input_right, int inputFrequency, int bytesPerSample, int nChannels)
{
	int nSize = input_left.count();
	for (int i = 0; i < nSize; ++i)
	{
		//计算频率
		m_spectrum[i].frequency = qreal(i*inputFrequency/2) / (nSize);
		const qreal magnitude_left = qSqrt(input_left[i].realVal*input_left[i].realVal + input_left[i].imagVal*input_left[i].imagVal);
		qreal magnitude_right = qSqrt(input_right[i].realVal*input_right[i].realVal + input_right[i].imagVal*input_right[i].imagVal);
		m_spectrum[i].amplitude = SpectrumAnalyserMultiplier*log10(abs(magnitude_left / magnitude_right));

		if (isnormal(m_spectrum[i].amplitude) == 0)
		{
			m_spectrum[i].amplitude = 0;
		}
		//m_spectrum[i].phase = atan2(imag_right, real_right) / M_PI * 180 -atan2(imag_left, real_left)/M_PI*180;
		const qreal phase_left = atan2(input_left[i].imagVal, input_left[i].realVal) / M_PI * 180;
		const qreal phase_right = atan2(input_right[i].imagVal, input_right[i].realVal) / M_PI * 180;
		qreal phase_val = phase_left - phase_right;
		if (phase_val > 180)
		{
			m_spectrum[i].phase = phase_val - 360;
		}
		else if (phase_val < -180)
		{
			m_spectrum[i].phase = phase_val + 360;
		}
		else
		{
			m_spectrum[i].phase = phase_val;
		}
	}

	emit calculattionComplete(m_spectrum);
	QThread::msleep(1);
}

void SpectrumAnalyserThread::calculateWindow()
{
	for (int i = 0; i < m_numSamples; ++i)
	{
		DataType x = 0.0;
		switch (m_windowFunction)
		{
		case NoWindow:
			x = 1.0;
			break;
		case HannWindow:		//汉宁窗：w(k) = 0.5*(1 - cos(2 * pi*k / (N - 1)))    0 <= k <= N - 1
			x = 0.5*(1 - qCos((2 * M_PI*i) / (m_numSamples - 1)));
			break;
		default:
			break;
		}
		m_window[i] = x;
	}
}

SpectrumAnalyser::SpectrumAnalyser(QObject *parent)
	: QObject(parent)
	, m_thread(new SpectrumAnalyserThread(this))
	, m_state(Idle)
#ifdef DUMP_SPECTRUMANALYSER
	, m_count(0)
#endif // DUMP_SPECTRUMANALYSER
	, m_nFFTEngineState(0)
{
	
	connect(m_thread, &SpectrumAnalyserThread::calculattionComplete, this, &SpectrumAnalyser::calculationComplete);
}

SpectrumAnalyser::~SpectrumAnalyser()
{
}

#ifdef DUMP_SPECTRUMANALYSER
void SpectrumAnalyser::setOutputPath(const QString & outputPath)
{
	m_outputDir.setPath(outputPath);
	m_textFile.setFileName(m_outputDir.filePath("spectrum.txt"));
	m_textFile.open(QIODevice::WriteOnly | QIODevice::Text);
	m_textStream.setDevice(&m_textFile);
}
#endif // DUMP_SPECTRUMANALYSER

bool SpectrumAnalyser::initFFTEngine(int sampleRate, int bits, int nChannels)
{
	m_nFFTEngineState = skv_preprocess_state_init(sampleRate, bits, nChannels);
	return m_nFFTEngineState == 1 ? true : false;
}

void SpectrumAnalyser::unitFFTEngine()
{
	skv_preprocess_state_destroy();
}

void SpectrumAnalyser::setWindowFunction(WindowFunction type)
{
	//QMetaObject::invokeMethod可以是异步调用，也可以是同步调用。这取决与它的连接方式Qt::ConnectionType type。如果type为Qt::DirectConnection，则为同步调用，若为Qt::QueuedConnection，则为异步调用
	const bool b = QMetaObject::invokeMethod(m_thread, "setWindowFunction", Qt::AutoConnection, Q_ARG(WindowFunction, type));
	Q_ASSERT(b);
	Q_UNUSED(b)
}

#define IN_SIZE 4096

void SpectrumAnalyser::calculate(const QByteArray & buffer, const QAudioFormat & format)
{
	qDebug() << "SpectrumAnalyser::calculate" << QThread::currentThread() << " state" << m_state;
	if (isReady())
	{
		//是否需要判断PCM必须是16bit编码的
		//Q_ASSERT(isPCMS16LE(format));
		const int bytesPerSample = format.sampleSize()*format.channelCount() / 8;
		const int nChannels = format.channelCount();

		const char *ptr = buffer.constData();

		char* pIn = new char[IN_SIZE*4];
		memcpy(pIn, ptr, IN_SIZE*4);
		COMPLEX_OUT* pOut = new COMPLEX_OUT[IN_SIZE*2];
		memset(pOut, 0, IN_SIZE * 2*sizeof(COMPLEX_OUT));

		
		
		if (nChannels == 1)
		{
			int nSIze = skv_preprocess_byte_hc((unsigned char*)pIn, pOut, IN_SIZE * 2, 2);
			QVector<COMPLEX_OUT> input_left(nSIze);
			for (int i = 0; i < nSIze; i++)
			{
				input_left[i].realVal = pOut[i].realVal;
				input_left[i].imagVal = pOut[i].imagVal;
			}
			m_state = Busy;
			QMetaObject::invokeMethod(m_thread, "calculateSpectrum_single", Qt::AutoConnection, Q_ARG(const QVector<COMPLEX_OUT> &, input_left), Q_ARG(int, format.sampleRate()), Q_ARG(int, bytesPerSample), Q_ARG(int, nChannels));
		}
		else
		{
			int nSIze = skv_preprocess_byte_hc((unsigned char*)pIn, pOut, IN_SIZE * 4, 2);
			QVector<COMPLEX_OUT> input_left(nSIze);
			QVector<COMPLEX_OUT> input_right(nSIze);
			for (int i = 0; i < nSIze; i++)
			{
				input_left[i].realVal = pOut[i].realVal;
				input_left[i].imagVal = pOut[i].imagVal;
				input_right[i].realVal = pOut[i + nSIze].realVal;
				input_right[i].imagVal = pOut[i + nSIze].imagVal;
			}
			m_state = Busy;
			const bool b = QMetaObject::invokeMethod(m_thread, "calculateSpectrum_music", Qt::AutoConnection, Q_ARG(const QVector<COMPLEX_OUT> &, input_left), Q_ARG(const QVector<COMPLEX_OUT> &, input_right), Q_ARG(int, format.sampleRate()), Q_ARG(int, bytesPerSample), Q_ARG(int, nChannels));
			Q_ASSERT(b);
			Q_UNUSED(b)
		}

		/*
		QVector<int> input_left(SpectrumLengthSamples, 0);
		QVector<int> input_right(SpectrumLengthSamples, 0);
		for (int i = 0; i < SpectrumLengthSamples; ++i)
		{
			const qint16 pcmSample_left = *reinterpret_cast<const qint16*>(ptr);
			const qint16 pcmSample_right = *reinterpret_cast<const qint16*>(ptr + bytesPerSample / nChannels);

			if (i >= 2078)
			{
				int mmmm = 0;
			}

			input_left[i] = pcmSample_left;
			input_right[i] = pcmSample_right;
			ptr += bytesPerSample;
		}

		m_state = Busy;
		//使用QMetaObject调用SpectrumAnalyserThread:：calculateSpectrum。如果m\u线程与当前线程位于不同的线程中，则计算将在子线程中完成。一旦计算完成，m\ U线程将发出calculationChanged信号
		//const bool b = QMetaObject::invokeMethod(m_thread, "calculateSpectrum", Qt::AutoConnection, Q_ARG(QByteArray, m_spectrumData), Q_ARG(int, format.sampleRate()), Q_ARG(int, bytesPerSample), Q_ARG(int, nChannels));


		
		const bool b = QMetaObject::invokeMethod(m_thread, "calculateSpectrum_music", Qt::AutoConnection, Q_ARG(const QVector<int> &, input_left), Q_ARG(const QVector<int> &, input_right), Q_ARG(int, format.sampleRate()), Q_ARG(int, bytesPerSample), Q_ARG(int, nChannels));
		Q_ASSERT(b);
		Q_UNUSED(b)
		*/
	}
	else
	{
		int mmmm = 0;
	}
}

bool SpectrumAnalyser::isReady() const
{
	return (Idle == m_state);
}

void SpectrumAnalyser::cancelCalculation()
{
	if (Busy == m_state)
	{
		m_state = Cancelled;
	}
}

void SpectrumAnalyser::calculationComplete(const FrequencySpectrum & spectrum)
{
	//Q_ASSERT(Idle != m_state);
	if (Busy == m_state)
	{
		emit spectrumChanged(spectrum);
	}
	m_state = Idle;
}

void SpectrumAnalyser::calculateWindow()
{

}

