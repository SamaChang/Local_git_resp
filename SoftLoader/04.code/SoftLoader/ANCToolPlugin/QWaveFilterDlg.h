#pragma once

#include <QDialog>
#include "ui_QWaveFilterDlg.h"

#include "../common/datastruct/FrequencySpectrum.h"
#include "../common/datastruct/DataStruct_anc_eq.h"

class QWaveFilterDlg : public QDialog
{
	Q_OBJECT

public:
	QWaveFilterDlg(QWidget *parent = Q_NULLPTR);
	~QWaveFilterDlg();

	//此处的枚举与下拉列表一一对应
	enum FILTER_TYPE  
	{
		FILTER_BYPASS=0,
		FILTER_PEAK,
		FILTER_LOWSHELF,
		FILTER_HIGHSHELF,
		FILTER_LOWPASS,
		FILTER_HIGHPASS,
		FILTER_IIR,
		FILTER_GAIN
	};

	void getConf(int &nType, int &nSerial, QString & strName);

	/**
	 * @brief  
	 * @param  波形类型是 WAVE_FF，还是WAVE_FB
	 * @param  滤波器序号
	 * @param  采样率
	 * @return  null
	 */
	void init(int nType, int nSerial, int nFreqRates);


private:
	void initUI(int nType, int nSerial);
	void initConn();

signals:
	void sig_conf(int nType, int nSerial, QString strName);

public slots:
	void slot_cmb_currentIndexChanged(int index);
	void slot_btn_show();
	void slot_btn_save_conf();

	void slot_btn_data_saveas();

	void slot_btn_load_iir();

	void slot_btn_set_db();
	void slot_btn_set_xx();

private:

	void testData();

private:
	Ui::QWaveFilterDlg ui;
	int m_nWaveType;		//FF FB MUSIC
	int m_nSerial;
	FrequencySpectrum m_freqData;
	CONF_WAVE_FILTER_PARAM	m_cong_param;
	int m_nFreqRates;
};
