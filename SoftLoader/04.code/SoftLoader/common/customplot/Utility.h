#pragma once
#include <QtCore/qglobal.h>
#include <QDebug>
/**
 * @Class		ʵ�ù��߹���		
 * @date		2021/04/25
 */

/*	//����֪ʶ
 *	�ο�˹��Ƶ�ʣ�Nyquist frequency������ɢ�ź�ϵͳ����Ƶ�ʵ�һ��

*/

//���峣��
const int		FFTLengthPowerOfTwo_my = 12;			//���ٸ���Ҷ�任����Ϊ2^12
//Ƶ���е�Ƶ����
const int		SpectrumNumBands = 10;
//���׵�һ��������
const qreal		SpectrumLowFreq = 0.0;	//Hz
//�������һ��������
const qreal		SpectrumHighFreq = 1000.0;	//Hz
//���δ��ڴ�С��΢�룩0.5��
const qint64	WaveformWindowDuration = 500 * 1000;
//���ο�ĳ���
//��������£����ǽ�ƥ��QAudio*����bufferSize���������ڵ���QAudio*����start����֮���һ��ʱ��ſ��ã�������Ҫ���ֵ����ʼ��������ʾ����ˣ�����ֻ��ѡ��һ�������ֵ��
//const int		WaveformTitleLength = 4096;
//���ڼ������߸߶ȵ�ģ������
const qreal		SpectrumAnalyserMultiplier = 20;
//������Ϣ��ʱ
const int		NullMessageTimeout = -1;

//ÿ΢��ʱ��Ƭ���ݴ�С 10��
const qint64 BufferDurationUs = 100 * 1000000;
//���÷���notify()�źŵ�ʱ���������ms����ʱ���������ϵͳƽ̨��أ�������ʵ�ʵ�ms��
const int    NotifyIntervalMs = 50;

// ÿ΢������ˮƽ��������
const int    LevelWindowUs = 0.1 * 1000000;

//���������ļ����������
const int	ConfFilesMaxValue = 10;
//���������߶��������
const int	ConfWaveLinesMaxValue = 8;

const QString LineColors[8] = {
	"#DC143C",	// Crimson 220,20,60
	"#FF00FF",	// Magenta 255,0,255
	"#800080",	// Purple  	128,0,128
	"#8552a1",  // 	MediumBlue  	0,0,205
	"#00FF00",  // 	Lime 0,255,0
	"#1d953f",  // ���� 0,0,0
	"#FFFF00",  // ���� 0,0,0
	"#00FFFF"  // ���� 0,0,0
};


template<int N> class PowerOfTwo
{
public: static const int Result = PowerOfTwo<N - 1>::Result * 2;
};

template<> class PowerOfTwo<0>
{
public:
	static const int Result = 1;
};

const int	SpectrumLengthSamples = PowerOfTwo<FFTLengthPowerOfTwo_my>::Result;	//4096 ���Ϊһ���������ڣ��������ڲ������ڱȽϴ����������ܴ󣬵��³����ر�

enum WindowFunction
{
	NoWindow,		
	HannWindow
};

enum WAVE_CHART_TYPE
{
	WAVE_CHART_FR=1,
	WAVE_CHART_PHASE
};

enum WAVE_FILTER_TYPE
{
	WAVE_FF = 1,
	WAVE_FB,
	WAVE_MUSIC
};

const WindowFunction DefaultWindowFunction = HannWindow;

//����ǰ��
QT_FORWARD_DECLARE_CLASS(QAudioFormat)
/**
 * @brief  �����ֽ�����ȡʱ��Ƭ��
 * @param  ��Ƶ��ʽ����
 * @param  �ֽ���
 * @return  ʱ��Ƭ��΢�
 */
qint64 audioDuration(const QAudioFormat & format, qint64 bytes);
/**
 * @brief  ����ʱ��Ƭ�λ�ȡ�ֽ���
 * @param  ��Ƶ��ʽ����
 * @param  ʱ��Ƭ�Σ�΢�
 * @return  �ֽ���
 */
qint64 audioLength(const QAudioFormat & format, qint64 microSeconds);
/**
 * @brief  ��ȡ�ο�˹��Ƶ��
 * @param  ��Ƶ��ʽ����
 * @return  �ο�˹��Ƶ��
 */
qreal nyquist(const QAudioFormat & format);
/**
 * @brief  ����Ƶ����ת�����ַ���
 * @param  ��Ƶ��ʽ����
 * @return ��ʾ�ַ���
 */
QString formatToString(const QAudioFormat & format);
/**
* @brief  �����Ƶ��ʽ�Ƿ�PCM
* @param  ��Ƶ��ʽ����
* @return bool
*/
bool isPCM(const QAudioFormat & format);
/**
* @brief	�����Ƶ��ʽ�Ƿ��з��ţ�С�ˣ�16λPCM
* @param	��Ƶ��ʽ����
* @return  bool
*/
bool isPCMS16LE(const QAudioFormat & format);
/**
 * @brief  ��PCMֵת����[-1.0,1.0]֮�����
 * @param  PCMֵ
 * @return  
 */
qreal pcmToReal(qint16 pcm);
/**
 * @brief  ��[-1.0,1.0]ת����PCMֵ
 * @param  [-1.0, 1.0]
 * @return PCMֵ 
 */
qint16 realToPcm(qreal real);


