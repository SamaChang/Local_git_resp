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

	//��ʼ����˾FFT�����豸
	bool initFFTEngine(int sampleRate, int bits, int nChannels);
	//�رչ�˾FFT�����豸
	void unitFFTEngine();


	//�����ڼ���FFT֮ǰӦ�õĴ��ں���
	void setWindowFunction(WindowFunction type);
	/**
	 * @brief  ����Ƶ��
	 * @param  ��Ƶ����
	 * @param  ��Ƶ���ݸ�ʽ
	 * @return  Ƶ�����첽����ġ����ؽ�� ͨ��Ƶ�ױ仯�ź� ����ͨ������cancelCalculation����ȡ�����ڽ��еļ���
	 */
	void calculate(const QByteArray & buffer, const QAudioFormat & format);
	/**
	 * @brief  �������Ƿ�׼����ִ����һ������
	 * @return  
	 */
	bool isReady() const;
	/**
	 * @brief  ȡ�����ڽ��еļ���
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
		Idle,	//����
		Busy,	
		Cancelled
	};
	State		m_state;

	int		m_nFFTEngineState;		//���ù�˾FFT�㷨�г�ʼ������״̬ 0Ϊ����ʧ�� 1Ϊ���سɹ�

#ifdef DUMP_SPECTRUMANALYSER
	QDir		m_outputDir;
	int			m_count;
	QFile		m_textFile;
	QTextStream m_textStream;
#endif // DUMP_SPECTRUMANALYSER

};
