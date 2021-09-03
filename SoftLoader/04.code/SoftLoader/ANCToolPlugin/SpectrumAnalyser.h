#pragma once

#include <QByteArray>
#include <QObject>
#include <QVector>
#include <QMutex>
#include <QMutexLocker>

#include "../common/customplot/Utility.h"
#include "../common/datastruct/FrequencySpectrum.h"

#include "../3rd/math/skv/FFTHeader.h"

//#include "../math/skv/FFTHeader.h"

#ifdef DUMP_SPECTRUMANALYSER
#include <QDir>
#include <QFile>
#include <QTextStream>
#endif // DUMP_SPECTRUMANALYSER

QT_FORWARD_DECLARE_CLASS(QAudioFormat)
QT_FORWARD_DECLARE_CLASS(QThread)

class FFTRealWrapper;

class SpectrumAnalyserThread : public QObject
{
	Q_OBJECT
public:
	SpectrumAnalyserThread(QObject *parent);
	~SpectrumAnalyserThread();

public slots:
	void setWindowFunction(WindowFunction type);
	void calculateSpectrum_single(const QVector<COMPLEX_OUT> & input_left, int inputFrequency, int bytesPerSample, int nChannels);
	void calculateSpectrum_music(const QVector<COMPLEX_OUT> & input_left, const QVector<COMPLEX_OUT> & input_right, int inputFrequency, int bytesPerSample, int nChannels);

signals:
	void calculattionComplete(const FrequencySpectrum & spectrum);
private:
	void calculateWindow();

private:
	//FFTRealWrapper*     m_fft;
	const int			m_numSamples;
	WindowFunction		m_windowFunction;

#ifdef FFTREAL_USED
	typedef FFTRealFixLenParam::DataType        DataType;
#elif HHHHH

#else
	typedef float	DataType;
#endif
	

	QVector<DataType>	m_window;
	QVector<DataType>	m_input;
	QVector<DataType>	m_input_left;
	QVector<DataType>	m_input_right;
	QVector<DataType>	m_output;
	QVector<DataType>	m_output_left;
	QVector<DataType>	m_output_right;
	FrequencySpectrum	m_spectrum;

	QThread*			m_thread;
	QMutex				m_mutex;
};

class SpectrumAnalyser : public QObject
{
	Q_OBJECT

public:
	SpectrumAnalyser(QObject *parent = nullptr);
	~SpectrumAnalyser();

#ifdef DUMP_SPECTRUMANALYSER
	void setOutputPath(const QString & outputPath);
#endif // DUMP_SPECTRUMANALYSER

public:

	//初始化公司FFT引擎设备
	bool initFFTEngine(int sampleRate, int bits, int nChannels);
	//关闭公司FFT引擎设备
	void unitFFTEngine();


	//设置在计算FFT之前应用的窗口函数
	void setWindowFunction(WindowFunction type);
	/**
	 * @brief  计算频谱
	 * @param  音频数据
	 * @param  音频数据格式
	 * @return  频谱是异步计算的。返回结果 通过频谱变化信号 可以通过调用cancelCalculation（）取消正在进行的计算
	 */
	void calculate(const QByteArray & buffer, const QAudioFormat & format);
	/**
	 * @brief  检查对象是否准备好执行另一个计算
	 * @return  
	 */
	bool isReady() const;
	/**
	 * @brief  取消正在进行的计算
	 * @return  
	 */
	void cancelCalculation();

signals:
	void spectrumChanged(const FrequencySpectrum & spectrum);

private slots:
	void calculationComplete(const FrequencySpectrum & spectrum);

private:
	void calculateWindow();

private:
	SpectrumAnalyserThread*		m_thread;
	QByteArray m_spectrumData;

	enum State
	{
		Idle,	//空闲
		Busy,	
		Cancelled
	};
	State		m_state;

	int		m_nFFTEngineState;		//引用公司FFT算法中初始化配置状态 0为加载失败 1为加载成功

#ifdef DUMP_SPECTRUMANALYSER
	QDir		m_outputDir;
	int			m_count;
	QFile		m_textFile;
	QTextStream m_textStream;
#endif // DUMP_SPECTRUMANALYSER

};
