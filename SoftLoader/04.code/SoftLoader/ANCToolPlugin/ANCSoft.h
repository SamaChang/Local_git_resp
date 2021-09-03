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

	void initUI();			//��ʼ��UI
	void initConn();		//��ʼ���źŲ�

	void getFreqRates(int &nFreqRates);

public slots:
	//ACTION
	void slot_btn_open_file();	//���ļ�
	void slot_btn_save_file();		//�����ļ�

	void slot_btn_confio();		//����IO	
	void slot_btn_axis();		//��������ϵ
	
	void slot_btn_record_param();	//��Ƶ��������
	void slot_btn_record();		//¼��
	void slot_btn_suspend();	//��ͣ
	void slot_btn_playback();	//������Ƶ

	//currentIndexChanged(int index)  comboBox_type
	//�ź�����
	void slot_cmb_type_currentIndexChanged(int index);

public slots:
	void initializeRecord();		//��ʼ��¼������
	void slot_audio_state_changed(QAudio::Mode mode, QAudio::State state);								//��Ƶ״̬�仯
	void slot_audio_format_changed(const QAudioFormat & format);										//��Ƶ�����ı�
	void slot_spectrum_changed(qint64 position, qint64 length, const FrequencySpectrum &spectrum);		//��������ͼ����
	void slot_audio_position_changed(qint64 position);													//���²���λ��
	void slot_buffer_length_changed(qint64 length);														//���������ȱ仯

signals:
	void sig_spectrum_changed(int nType, const FrequencySpectrum &spectrum);							//����ͼ����	
	void sig_axis_update();		//����ϵ����			

	void sig_signal_type(int nType/*, int nVal*/);

public slots:
	void updateModeMenu();			//����ģʽ�˵�
	void updateButtonStates();		//���°�ť״̬

protected:
	void closeEvent(QCloseEvent *event) override;		//�ر��麯��

private:

	enum SIGNAL_TYPE
	{
		TYPE_NONE = -1,
		TYPE_REL_CJ = 0,			//ʵʱ�ɼ�
		TYPE_W_ZS,						//������
		TYPE_F_ZS,						//������
		TYPE_1K_ZXB,					//1K���Ҳ�
		TYPE_SP							//ɨƵ
	};

	enum Mode
	{
		NoMode,
		RecordMode,
		LoadFileMode
	};

	void setSignalType(SIGNAL_TYPE nType);			//������Ƶģʽ
	void reset();						//����
	void initAudioFormat();

private:
	Ui::ANCSoft *ui;
	SIGNAL_TYPE m_nSignalType;
	//Mode		m_mode;			//��Ƶģʽ
	RealTimeEngine*		m_engine;		//��Ƶ��������
	QAudioFormat m_audioInputFormatConf;
	
};
