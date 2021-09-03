#pragma once

/**
 * @class	程序启动时会读取一次配置文件，将所有配置加载到程序中，当程序退出时，检查配置文件是否已经被修改，如果有改动就进行保存操作  
 * @date   2021/04/28
 */


#include <QString>

#include "../common/customplot/Utility.h"
#include "../common/datastruct/FrequencySpectrum.h"
#include "../common/datastruct/DataStruct_anc_eq.h"

typedef QVector<WAVE_LINE_PARAM>					WAVE_LINE_VEC;
typedef QVector<CONF_WAVE_FILTER_PARAM>				WAVE_FILTER_VEC;
//typedef QVector<CONF_WAVE_FILTER_PARAM>::iterator	WAVE_FILTER_ITER;

class Config
{
protected:
	Config();
	~Config();
public:
	
	static Config* getIns();
	//程序初始化配置 根据返回值判断程序启动是否有错 返回1正常
	int initConf();

	bool isNeedSave() { return m_wave_filter_modified_flag || m_wave_format_modified_flag || m_axis_modified_flag; }

	void saveOut();		//保存退出

	bool readCommonJson();
	bool writeCommonJson();

	bool readJson(QString strFile);
	bool writeJson(QString strFile);

	bool readJson_axis();
	bool writeJson_axis();

	void set_wave_filter_conf(WAVE_FILTER_TYPE nType, const CONF_WAVE_FILTER_PARAM & stuVal);
	CONF_WAVE_FILTER_PARAM get_wave_filter_conf(WAVE_FILTER_TYPE nType, int nSerial);

	WAVE_LINE_VEC & getFrLinesConf() { return m_vec_fr_lines; }
	WAVE_LINE_VEC & getPhaseLinesConf() { return m_vec_phase_lines; }

	void setAxisModified(bool bFlag) { m_axis_modified_flag = bFlag;  }

public:
	QVector<FrequencySpectrum> m_fr_chart_data;				//存储六条fr的曲线数据
	QVector<FrequencySpectrum> m_phase_chart_data;			//存储六条Phase的曲线数据

	AXIS_STRUCT m_fr_chart_axis;
	AXIS_STRUCT m_phase_chart_axis;

	int m_sys_dB;					//系统音量
	int m_nPowerOfTwo;		//系统的乘以的2的次方数
	int m_sys_freqRate;		//软件采用的采样频率
	int m_sys_channel;			//软件才用的通道 0表示单通道 1表示立体声

private:
	bool m_wave_format_modified_flag;			//音频输入参数修改标识
	bool m_wave_filter_modified_flag;			//滤波器配置修改标识
	bool m_axis_modified_flag;					//坐标系被修改
	static Config* m_pIns;

	WAVE_LINE_VEC m_vec_fr_lines;
	WAVE_LINE_VEC m_vec_phase_lines;

	WAVE_FILTER_VEC m_vec_ff;
	WAVE_FILTER_VEC m_vec_fb;
	WAVE_FILTER_VEC m_vec_music;

};
