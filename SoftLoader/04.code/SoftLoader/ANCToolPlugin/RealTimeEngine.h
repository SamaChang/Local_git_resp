#pragma once

/**
 * @class	�������qt������Ƶ������׷�����Ľӿڣ�������Ƶ���ݵ�ʵʱ�ɼ������Բɼ��������ݽ���ʵʱ����  
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

	//��ȡ��Ƶģʽ
	QAudio::Mode mode() const { return m_mode; }
	//��ȡ��Ƶ��ǰ״̬
	QAudio::State state() const { return m_state; }
	//��ȡ��ǰ��Ƶ��ʽ
	const QAudioFormat & format() const { return m_format; }
	//������Ƶ��ʽ
	void setFormat(const QAudioFormat & format);
	//���ã�ֹͣ�κ����ڽ��е�¼�ƻ򲥷ţ���������״̬Ϊ��̬
	void reset();
	//��ȡ��Ƶ������Ϣ
	QAudioDeviceInfo* getAudioInputDeviceInfo() { return &m_audioInputInfo; }
	//������Ƶ������Ϣ
	void setAudioInputDeviceInfo(const QAudioDeviceInfo & device);
	//��ȡ��Ƶ�����Ϣ
	QAudioDeviceInfo* getAudioOutputDeviceInfo() { return &m_audioOutputInfo; }
	//������Ƶ�����Ϣ
	void setAudioOutputDeviceInfo(const QAudioDeviceInfo & device);


	//��wav�ļ��м�������
	bool loadFile(const QString & fileName);
	//�Ƿ���Բ���
	bool isPlaybackabled();
	//��ʼ��¼������
	bool initializeRecord();

public slots:
	void startRecording();	//¼��
	void startPlayback();	//����
	void suspend();			//��ͣ

private slots:
	void audioNotify();	//��Ƶ֪ͨ
	void audioStateChanged(QAudio::State state);	//��Ƶ״̬�ı�
	void audioDataReady();	//��Ƶ�������
	void spectrumChanged(const FrequencySpectrum & spectrum);

signals:
	void stateChanged(QAudio::Mode mode, QAudio::State state);
	//��Ƶ���ݵ�ģʽ���������仯
	void formatChanged(const QAudioFormat & format);
	//ɫ��ͼ�����仯 ���ڵ���ʼλ�� ���ڳ��� ������Ƶ��
	void spectrumChanged(qint64 position, qint64 length, const FrequencySpectrum & spectrum);
private:
	void resetAudioDevices();		//������Ƶ�豸��Ϣ
	bool initialize();				//��ʼ����Ƶ�������
	bool slectedFormat();			//�Ƿ��Ѿ�ѡ����Ƶģʽ
	void stopRecording();			//ֹͣ¼��
	void stopPlayback();			//ֹͣ����
	void setState(QAudio::State state);
	void setState(QAudio::Mode mode, QAudio::State state);
	void calculateSpectrum(qint64 position);

private:
	QAudio::Mode		m_mode;				//�������ģʽ
	QAudio::State		m_state;			//����Ƶ״̬
	SpectrumAnalyser	m_spectrumAnalyser;	//����ͼ������

	QAudioFormat		m_format;			//��Ƶģʽ

	QAudioInput			*m_audioInput;		//��Ƶ����ӿ�
	QAudioDeviceInfo	m_audioInputInfo;	//��Ƶ������Ϣ
	QIODevice			*m_audioInputIODev;	//��Ƶ��������

	QAudioOutput		*m_audioOutput;		//��Ƶ����ӿ�
	QAudioDeviceInfo	m_audioOutputInfo;	//��Ƶ�����Ϣ
	QBuffer				m_audioOutputIODev;


	WavFile				*m_file;			//�򿪵��ļ�
	WavFile				*m_analysisFile;	//������Ҫ�ڶ����ļ������ͨ���������ݶ��뻺�������з���

	
	QByteArray			m_buffer;			//�������洢��Ƶ��������ݣ�ѭ��ʹ��
	qint64				m_bufferLength;		//�������ܳ���
	qint64				m_dataLength;		//�������Ѿ���������ݳ���
	qint64				m_bufferPos;		//��¼��ǰ�Ѿ����뻺���������ݳ���
	bool				m_bEnd;				//��ȡ�������Ƿ��ѳ����������������������ͷ��ʼ������

	qint64				m_spectrumBufferLength;		//����ͼ���������ݳ���
	qint64				m_spectrumPos;			//��¼����������ͼ��ȡ�Ļ�����λ��
	QByteArray			m_spectrumBuffer;	
};
