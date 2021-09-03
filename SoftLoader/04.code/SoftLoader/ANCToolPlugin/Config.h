#pragma once

/**
 * @class	��������ʱ���ȡһ�������ļ������������ü��ص������У��������˳�ʱ����������ļ��Ƿ��Ѿ����޸ģ�����иĶ��ͽ��б������  
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
	//�����ʼ������ ���ݷ���ֵ�жϳ��������Ƿ��д� ����1����
	int initConf();

	bool isNeedSave() { return m_wave_filter_modified_flag || m_wave_format_modified_flag || m_axis_modified_flag; }

	void saveOut();		//�����˳�

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
	QVector<FrequencySpectrum> m_fr_chart_data;				//�洢����fr����������
	QVector<FrequencySpectrum> m_phase_chart_data;			//�洢����Phase����������

	AXIS_STRUCT m_fr_chart_axis;
	AXIS_STRUCT m_phase_chart_axis;

	int m_sys_dB;					//ϵͳ����
	int m_nPowerOfTwo;		//ϵͳ�ĳ��Ե�2�Ĵη���
	int m_sys_freqRate;		//������õĲ���Ƶ��
	int m_sys_channel;			//������õ�ͨ�� 0��ʾ��ͨ�� 1��ʾ������

private:
	bool m_wave_format_modified_flag;			//��Ƶ��������޸ı�ʶ
	bool m_wave_filter_modified_flag;			//�˲��������޸ı�ʶ
	bool m_axis_modified_flag;					//����ϵ���޸�
	static Config* m_pIns;

	WAVE_LINE_VEC m_vec_fr_lines;
	WAVE_LINE_VEC m_vec_phase_lines;

	WAVE_FILTER_VEC m_vec_ff;
	WAVE_FILTER_VEC m_vec_fb;
	WAVE_FILTER_VEC m_vec_music;

};
