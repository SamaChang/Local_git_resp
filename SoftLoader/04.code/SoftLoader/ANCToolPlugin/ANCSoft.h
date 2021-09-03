#pragma once

#include <QWidget>
#include <QAudio>
#include <QAudioFormat>

namespace Ui { class ANCSoft; };

class RealTimeEngine;
class FrequencySpectrum;

class ANCSoft : public QWidget
{
	Q_OBJECT

public:
	ANCSoft(QWidget *parent = Q_NULLPTR);
	~ANCSoft();

	void initUI();			//初始化UI
	void initConn();		//初始化信号槽

	void getFreqRates(int &nFreqRates);

public slots:
	//ACTION
	void slot_btn_open_file();	//打开文件
	void slot_btn_save_file();		//保存文件

	void slot_btn_confio();		//配置IO	
	void slot_btn_axis();		//配置坐标系
	
	void slot_btn_record_param();	//音频参数设置
	void slot_btn_record();		//录音
	void slot_btn_suspend();	//暂停
	void slot_btn_playback();	//播放音频

	//currentIndexChanged(int index)  comboBox_type
	//信号类型
	void slot_cmb_type_currentIndexChanged(int index);

public slots:
	void initializeRecord();		//初始化录音设置
	void slot_audio_state_changed(QAudio::Mode mode, QAudio::State state);								//音频状态变化
	void slot_audio_format_changed(const QAudioFormat & format);										//音频参数改变
	void slot_spectrum_changed(qint64 position, qint64 length, const FrequencySpectrum &spectrum);		//更新声谱图数据
	void slot_audio_position_changed(qint64 position);													//更新播放位置
	void slot_buffer_length_changed(qint64 length);														//缓冲区长度变化

signals:
	void sig_spectrum_changed(int nType, const FrequencySpectrum &spectrum);							//声谱图更新	
	void sig_axis_update();		//坐标系更新			

	void sig_signal_type(int nType/*, int nVal*/);

public slots:
	void updateModeMenu();			//更新模式菜单
	void updateButtonStates();		//更新按钮状态

protected:
	void closeEvent(QCloseEvent *event) override;		//关闭虚函数

private:

	enum SIGNAL_TYPE
	{
		TYPE_NONE = -1,
		TYPE_REL_CJ = 0,			//实时采集
		TYPE_W_ZS,						//白噪声
		TYPE_F_ZS,						//粉噪声
		TYPE_1K_ZXB,					//1K正弦波
		TYPE_SP							//扫频
	};

	enum Mode
	{
		NoMode,
		RecordMode,
		LoadFileMode
	};

	void setSignalType(SIGNAL_TYPE nType);			//设置音频模式
	void reset();						//重置
	void initAudioFormat();

private:
	Ui::ANCSoft *ui;
	SIGNAL_TYPE m_nSignalType;
	//Mode		m_mode;			//音频模式
	RealTimeEngine*		m_engine;		//音频解析引擎
	QAudioFormat m_audioInputFormatConf;
	
};
