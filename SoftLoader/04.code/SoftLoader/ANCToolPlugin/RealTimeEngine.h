#pragma once

/**
 * @class	该类调用qt的音视频类和声谱分析类的接口，管理音频数据的实时采集，并对采集到的数据进行实时分析  
 * @date   2021/05/17 
 */

#include <QObject>
#include <QAudioDeviceInfo>
#include <QAudioFormat>
#include <QBuffer>

#include "WavFile.h"
#include "../common/datastruct/FrequencySpectrum.h"
#include "SpectrumAnalyser.h"

class QAudioInput;
class QAudioOutput;

class RealTimeEngine : public QObject
{
	Q_OBJECT

public:
	RealTimeEngine(QObject *parent = nullptr);
	~RealTimeEngine();

	//获取音频模式
	QAudio::Mode mode() const { return m_mode; }
	//获取音频当前状态
	QAudio::State state() const { return m_state; }
	//获取当前音频格式
	const QAudioFormat & format() const { return m_format; }
	//设置音频格式
	void setFormat(const QAudioFormat & format);
	//重置，停止任何正在进行的录制或播放，重置所有状态为基态
	void reset();
	//获取音频输入信息
	QAudioDeviceInfo* getAudioInputDeviceInfo() { return &m_audioInputInfo; }
	//设置音频输入信息
	void setAudioInputDeviceInfo(const QAudioDeviceInfo & device);
	//获取音频输出信息
	QAudioDeviceInfo* getAudioOutputDeviceInfo() { return &m_audioOutputInfo; }
	//设置音频输出信息
	void setAudioOutputDeviceInfo(const QAudioDeviceInfo & device);


	//从wav文件中加载数据
	bool loadFile(const QString & fileName);
	//是否可以播放
	bool isPlaybackabled();
	//初始化录音操作
	bool initializeRecord();

public slots:
	void startRecording();	//录音
	void startPlayback();	//播放
	void suspend();			//暂停

private slots:
	void audioNotify();	//音频通知
	void audioStateChanged(QAudio::State state);	//音频状态改变
	void audioDataReady();	//音频输入接收
	void spectrumChanged(const FrequencySpectrum & spectrum);

signals:
	void stateChanged(QAudio::Mode mode, QAudio::State state);
	//音频数据的模式参数发生变化
	void formatChanged(const QAudioFormat & format);
	//色谱图发生变化 窗口的起始位置 窗口长度 产生的频谱
	void spectrumChanged(qint64 position, qint64 length, const FrequencySpectrum & spectrum);
private:
	void resetAudioDevices();		//重置音频设备信息
	bool initialize();				//初始化音频输入输出
	bool slectedFormat();			//是否已经选中音频模式
	void stopRecording();			//停止录音
	void stopPlayback();			//停止播放
	void setState(QAudio::State state);
	void setState(QAudio::Mode mode, QAudio::State state);
	void calculateSpectrum(qint64 position);

private:
	QAudio::Mode		m_mode;				//输入输出模式
	QAudio::State		m_state;			//音视频状态
	SpectrumAnalyser	m_spectrumAnalyser;	//声谱图分析器

	QAudioFormat		m_format;			//音频模式

	QAudioInput			*m_audioInput;		//音频输入接口
	QAudioDeviceInfo	m_audioInputInfo;	//音频输入信息
	QIODevice			*m_audioInputIODev;	//音频输入数据

	QAudioOutput		*m_audioOutput;		//音频输出接口
	QAudioDeviceInfo	m_audioOutputInfo;	//音频输出信息
	QBuffer				m_audioOutputIODev;


	WavFile				*m_file;			//打开的文件
	WavFile				*m_analysisFile;	//我们需要第二个文件句柄，通过它将数据读入缓冲区进行分析

	
	QByteArray			m_buffer;			//缓冲区存储音频输入的数据，循环使用
	qint64				m_bufferLength;		//缓冲区总长度
	qint64				m_dataLength;		//缓冲区已经保存的数据长度
	qint64				m_bufferPos;		//记录当前已经存入缓冲区的数据长度
	bool				m_bEnd;				//读取的数据是否已超出缓冲区，如果超出，从头开始存数据

	qint64				m_spectrumBufferLength;		//声谱图缓冲区数据长度
	qint64				m_spectrumPos;			//记录缓冲区声谱图读取的缓冲区位置
	QByteArray			m_spectrumBuffer;	
};
