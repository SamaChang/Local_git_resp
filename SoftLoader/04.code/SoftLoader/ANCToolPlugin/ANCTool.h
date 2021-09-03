#ifndef ANCTOOL_H
#define ANCTOOL_H

#include <QWidget>
#include <QButtonGroup>
#include <QTimer>
#include <QQueue>

#include "../common/datastruct/FrequencySpectrum.h"
#include "../common/serialport/SerialPortDlg.h"

class QWaveFilterDlg;

namespace Ui {
class ANCTool;
}

class ANCTool : public QWidget
{
    Q_OBJECT

public:
    explicit ANCTool(QWidget *parent = nullptr);
    ~ANCTool();

	void init();

	void resetData();

	void addInfo(QString strLog);

private:
	void initUI();
	void initConnect();
	void initAxis();

	void updateCom();			//更新串口信息
	/**
	 * @brief		根据算法计算IIR的值
	 * @param	滤波器参数信息
	 * @param  滤波器算法类型
	 * @param 获取的IIR的值
	 * @date   2021/07/08
	 * @return  
	 */
	void calcIIR(const CONF_WAVE_FILTER_PARAM &tempParam, double* pOut);

public slots:

	void slot_optimal_show();			//最有显示效果
	void slot_signal_type(int nType/*, int nVal*/);			//根据信号类型，减去音量值
	//统计点数
	void slot_comboBox_points_value_changed(int index);			//currentIndexChanged(int index)
	void slot_ckb_group_fr(int nId);		//buttonClicked(int id)
	void slot_ckb_group_phase(int nId);

	void slot_btn_group_fr(int nId);		//保存实时的FR波形
	void slot_btn_group_phase(int nId);	//保存实时的FR波形

	//checkBox的FF状态
	void slot_ckb_ff_stateChanged(int state);		//stateChanged(int state)   FR
	void slot_ckb_fb_stateChanged(int state);		//stateChanged(int state)  FR

	void slot_ckb_ff_stateChanged_phase(int state);		//stateChanged(int state)   FR
	void slot_ckb_fb_stateChanged_phase(int state);		//stateChanged(int state)  FR

	void slot_btn_group_ff(int nId);
	void slot_btn_group_fb(int nId);

	void slot_ckb_group_ff(int nId);
	void slot_ckb_group_fb(int nId);

	void slot_fr_chart_conf();		//FR波形配置
	void slot_phase_chart_conf();	//Phase波形配置

	void slot_spectrum_changed(int nType, const FrequencySpectrum &spectrum);		//更新声谱图

	void slot_axis_update();		//坐标系更新

	//保存波形数据
	void slot_save_data_fr();
	void slot_save_data_phase();

	void slot_write_hardware();

	void slot_link_dev();
	void slot_recv_data(QByteArray strData);

	void slot_wave_filter_dlg_conf(int nType, int nSerial, QString strName);

private:
    Ui::ANCTool *ui;
	HandleCom* m_pHandleCom;

	QButtonGroup m_ckb_group_ff;
	QButtonGroup m_btn_group_ff;

	QButtonGroup m_ckb_group_fb;
	QButtonGroup m_btn_group_fb;

	QButtonGroup m_ckb_group_fr;
	QButtonGroup m_ckb_group_phase;

	QButtonGroup m_btn_group_fr;
	QButtonGroup m_btn_group_phase;


	FrequencySpectrum m_spectrumData;
	FrequencySpectrum m_spectrumCurrent;			//当前图形显示的波形
	QList<FrequencySpectrum> m_queue_spectrum;		//用队列存储声谱数据
	int m_nqueueSize;								//设置队列的大小值

	//最优显示设置
	int m_axis_x_min;
	int m_axis_x_max;

	int m_fr_axis_y_min;
	int m_fr_axis_y_max;

	int m_phase_axis_y_min;
	int m_phase_axis_y_max;

	int m_nSignalType;
	int m_ndb;			//系统音量值

	QWaveFilterDlg* m_pWaveFilterDlg;

};

#endif // ANCTOOL_H
