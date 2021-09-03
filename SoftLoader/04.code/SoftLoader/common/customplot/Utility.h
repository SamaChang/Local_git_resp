#pragma once
#include <QtCore/qglobal.h>
#include <QDebug>
/**
 * @Class		实用工具功能		
 * @date		2021/04/25
 */

/*	//基础知识
 *	奈奎斯特频率（Nyquist frequency）是离散信号系统采样频率的一半

*/

//定义常量
const int		FFTLengthPowerOfTwo_my = 12;			//快速傅里叶变换长度为2^12
//频谱中的频带数
const int		SpectrumNumBands = 10;
//声谱第一带的下限
const qreal		SpectrumLowFreq = 0.0;	//Hz
//声谱最后一带的上限
const qreal		SpectrumHighFreq = 1000.0;	//Hz
//波形窗口大小（微秒）0.5秒
const qint64	WaveformWindowDuration = 500 * 1000;
//波形块的长度
//理想情况下，它们将匹配QAudio*：：bufferSize（），但在调用QAudio*：：start（）之后的一段时间才可用，我们需要这个值来初始化波形显示。因此，我们只需选择一个合理的值。
//const int		WaveformTitleLength = 4096;
//用于计算谱线高度的模糊因子
const qreal		SpectrumAnalyserMultiplier = 20;
//禁用消息超时
const int		NullMessageTimeout = -1;

//每微妙时间片数据大小 10秒
const qint64 BufferDurationUs = 100 * 1000000;
//设置发送notify()信号的时间间隔。这个ms毫秒时间间隔与操作系统平台相关，并不是实际的ms数
const int    NotifyIntervalMs = 50;

// 每微妙计算的水平窗口数量
const int    LevelWindowUs = 0.1 * 1000000;

//定义配置文件的最大容量
const int	ConfFilesMaxValue = 10;
//定义配置线段最大容量
const int	ConfWaveLinesMaxValue = 8;

const QString LineColors[8] = {
	"#DC143C",	// Crimson 220,20,60
	"#FF00FF",	// Magenta 255,0,255
	"#800080",	// Purple  	128,0,128
	"#8552a1",  // 	MediumBlue  	0,0,205
	"#00FF00",  // 	Lime 0,255,0
	"#1d953f",  // 纯黑 0,0,0
	"#FFFF00",  // 纯黑 0,0,0
	"#00FFFF"  // 纯黑 0,0,0
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

const int	SpectrumLengthSamples = PowerOfTwo<FFTLengthPowerOfTwo_my>::Result;	//4096 最好为一个采样周期，但是由于采样周期比较大，软件负担会很大，导致程序特别卡

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

//声明前置
QT_FORWARD_DECLARE_CLASS(QAudioFormat)
/**
 * @brief  根据字节数获取时间片段
 * @param  音频格式参数
 * @param  字节数
 * @return  时间片（微妙）
 */
qint64 audioDuration(const QAudioFormat & format, qint64 bytes);
/**
 * @brief  根据时间片段获取字节数
 * @param  音频格式参数
 * @param  时间片段（微妙）
 * @return  字节数
 */
qint64 audioLength(const QAudioFormat & format, qint64 microSeconds);
/**
 * @brief  获取奈奎斯特频率
 * @param  音频格式参数
 * @return  奈奎斯特频率
 */
qreal nyquist(const QAudioFormat & format);
/**
 * @brief  将音频参数转换成字符串
 * @param  音频格式参数
 * @return 显示字符串
 */
QString formatToString(const QAudioFormat & format);
/**
* @brief  检查音频格式是否PCM
* @param  音频格式参数
* @return bool
*/
bool isPCM(const QAudioFormat & format);
/**
* @brief	检查音频格式是否有符号，小端，16位PCM
* @param	音频格式参数
* @return  bool
*/
bool isPCMS16LE(const QAudioFormat & format);
/**
 * @brief  将PCM值转换成[-1.0,1.0]之间的数
 * @param  PCM值
 * @return  
 */
qreal pcmToReal(qint16 pcm);
/**
 * @brief  将[-1.0,1.0]转换成PCM值
 * @param  [-1.0, 1.0]
 * @return PCM值 
 */
qint16 realToPcm(qreal real);


