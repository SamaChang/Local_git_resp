#pragma once

#include <QWidget>
#include "ui_EQTools.h"

#include "../common/datastruct/DataStruct_anc_eq.h"
#include "../common/datastruct/FrequencySpectrum.h"

class HandleCom;

class EQTools : public QWidget
{
	Q_OBJECT

public:
	EQTools(QWidget *parent = Q_NULLPTR);
	~EQTools();

	struct ComboCtrl
	{
		ComboCtrl(int nIndex, QSlider* pSlider, /*QLineEdit* pBoostEdt,*/ QDoubleSpinBox* pSpinBox, QLineEdit* pQEdt)
			: m_nIndex(nIndex)
			, m_pSlider(pSlider)
			//, m_pBoostEdt(pBoostEdt)
			, m_pSpinBox(pSpinBox)
			, m_pQEdt(pQEdt)
			, nBoost(0)
			, dQ(0)
		{
		}
		int m_nIndex;
		QSlider* m_pSlider;
		//QLineEdit* m_pBoostEdt;
		QDoubleSpinBox* m_pSpinBox;
		QLineEdit* m_pQEdt;
		double nBoost;
		double dQ;
	};

	

private:
	void initUI();
	void setWaveChart(int nIndex, double nBoost, double nQ, int nTotal_gain = -100);		//-100无效值
	bool readCommonJson();

	void updateCom();

public slots:
	void slot_voice_valueChanged(int nTotal_Gain);
	void slot_slider_valueChanged(int nVal);
	void slot_spinbox_valueChanged(double dVal);
	void slot_boost_textChanged(const QString &text);
	void slot_Q_textChanged(const QString &text);

	void slot_chart_boost_valueChanged(int nIndex, int nVal);

	//void slot_tbtn_com();		//串口设置

	void slot_btn_open();		//打开文件
	void slot_btn_save();		//保存

	void slot_btn_link_dev();		//连接设备
	void slot_btn_write_hardware();		//写入硬件
	void slot_btn_clear_log_info();		//清空打印信息

	void slot_recv_data(QByteArray strData);

private:
	Ui::EQTools ui;
	HandleCom* m_pHandleCom;
	QVector<ComboCtrl> m_vec_comboCtrl;
	QVector<FrequencySpectrum> m_vec_data;			//存储十个波形的数据
	QVector<IIR_INFO> m_vec_IIR;
	double* m_pOutData;
	int m_nVoice;			//音量值
	int m_nFreq;			//采样频率

	int m_nPeakMax;			//可设置的波形峰值
	int m_nPeakError;		//实际波形减去峰值的误差
	int m_nPowerOfTwo;
};
