#include "Config.h"
#include <QFile>
#include <QApplication>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>
#include <QMessageBox>

#include "../common/customplot/Utility.h"



Config* Config::m_pIns = nullptr;
Config::Config()
	: m_wave_format_modified_flag(false)
	, m_wave_filter_modified_flag(false)
	, m_axis_modified_flag(false)
	, m_vec_fr_lines(ConfWaveLinesMaxValue)
	, m_vec_phase_lines(ConfWaveLinesMaxValue)
	, m_vec_fb(ConfFilesMaxValue)
	, m_vec_ff(ConfFilesMaxValue)
	, m_vec_music(ConfFilesMaxValue)
	, m_fr_chart_data(ConfWaveLinesMaxValue)
	, m_phase_chart_data(ConfFilesMaxValue)
	, m_sys_dB(0)
	, m_nPowerOfTwo(27)
{

	for (int i = 0; i < ConfWaveLinesMaxValue; ++i)
	{
		m_vec_fr_lines[i].name = QString("Line_%1").arg(i + 1);
		m_vec_fr_lines[i].clr = LineColors[i];

		m_vec_phase_lines[i].name = QString("Line_%1").arg(i + 1);
		m_vec_phase_lines[i].clr = LineColors[i];

		
	}

	for (int i=0; i<ConfFilesMaxValue; ++i)
	{
		m_vec_fb[i].nSerial = i + 1;
		m_vec_ff[i].nSerial = i + 1;
	}
}

Config::~Config()
{
}

Config * Config::getIns()
{
	if (m_pIns == nullptr)
	{
		m_pIns = new Config;
	}
	return m_pIns;
}

int Config::initConf()
{
	int nRet = 0;
	readCommonJson();
	int nRetAxis = 0;
	bool bReadJson = readJson_axis();
	if (!bReadJson)
	{
		nRetAxis = 10;
	}
	return nRet+nRetAxis;
}

void Config::saveOut()
{
	writeJson_axis();
}

bool Config::readCommonJson()
{
	QString strPathFile = QApplication::applicationDirPath();
	strPathFile = strPathFile + QString("/config/ANCTool/common.json");
	QFile file(strPathFile);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		qDebug() << "打开文件失败,错误信息为：" << file.errorString();
		return false;
	}

	QByteArray allData = file.readAll();
	file.close();

	QJsonParseError jsonError;
	QJsonDocument jsonDoc(QJsonDocument::fromJson(allData, &jsonError));

	if (jsonError.error != QJsonParseError::NoError)
	{
		qDebug() << "json error!" << jsonError.errorString();
		return false;
	}

	QJsonObject root = jsonDoc.object();
	m_nPowerOfTwo = root["powerOfTwo"].toInt();
	m_sys_dB = root["sys_db"].toInt();
	m_sys_freqRate = root["freqrate"].toInt();
	m_sys_channel = root["channel"].toInt();
	return true;
}

bool Config::writeCommonJson()
{
	QString strPathFile = QApplication::applicationDirPath();
	strPathFile = strPathFile + QString("/config/ANCTool/common.json");
	QFile file(strPathFile);
	if (!file.open(QIODevice::ReadWrite |QIODevice::Text))
	{
		qDebug() << QStringLiteral("打开文件失败,错误信息为:" )<< file.errorString();
		return false;
	}
	file.resize(0);	//清空文件中的原有内容

	QJsonDocument jsonDoc;
	QJsonObject jsonRoot;

	jsonRoot["powerOfTwo"] = m_nPowerOfTwo;
	jsonRoot["sys_db"] = m_sys_dB;
	jsonRoot["freqrate"] = m_sys_freqRate;
	jsonRoot["channel"] = m_sys_channel;

	jsonDoc.setObject(jsonRoot);
	file.write(jsonDoc.toJson());
	file.close();
	return true;
}

bool Config::readJson(QString strFile)
{
	//QString strPathFile = QApplication::applicationDirPath();
	//strPathFile = strPathFile + QString("/config/ANCTool/wave_filter_conf.json");
	QFile file(strFile);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		qDebug() << "打开文件失败,错误信息为："<<file.errorString();
		return false;
	}

	QByteArray allData = file.readAll();
	file.close();

	QJsonParseError jsonError;
	QJsonDocument jsonDoc(QJsonDocument::fromJson(allData, &jsonError));

	if (jsonError.error != QJsonParseError::NoError)
	{
		qDebug() << "json error!" << jsonError.errorString();
		return false;
	}

	QJsonObject root = jsonDoc.object();
	int nSysFreqRate = root["freqrate"].toInt();
	if (m_sys_freqRate != nSysFreqRate)
	{
		QMessageBox::StandardButton button = QMessageBox::information(nullptr, QStringLiteral("提示"), QStringLiteral("当前系统设置的采样率与加载的配置不符，是否继续加载配置文件？"), QMessageBox::Yes, QMessageBox::No);
		if (button == QMessageBox::No)
		{
			return false;
		}

	}
	QJsonObject obj_wave_filter_ff = root["wave_filter_ff"].toObject();
	QJsonObject obj_wave_filter_fb = root["wave_filter_fb"].toObject();
	//QJsonObject obj_wave_filter_music = root["wave_filter_music"].toObject();
	//FF配置读取
	QJsonArray objArray_wave_filter_ff = obj_wave_filter_ff["data"].toArray();
	for (int i = 0; i < objArray_wave_filter_ff.size(); i++)
	{
		QJsonObject tempObj = objArray_wave_filter_ff.at(i).toObject();
		CONF_WAVE_FILTER_PARAM tempStu;
		tempStu.nType		= tempObj["type"].toInt();
		tempStu.nSerial		= tempObj["serial"].toInt();
		tempStu.freq		= tempObj["freq"].toInt();
		tempStu.boost		= tempObj["boost"].toDouble();
		tempStu.nQ			= tempObj["bandWidth"].toDouble();
		tempStu.gain		= tempObj["gain"].toInt();
		tempStu.slope = tempObj["slope"].toDouble();
		m_vec_ff[i] =tempStu;
	}
	//FB配置读取
	QJsonArray objArray_wave_filter_fb = obj_wave_filter_fb["data"].toArray();
	for (int i = 0; i < objArray_wave_filter_fb.size(); i++)
	{
		QJsonObject tempObj = objArray_wave_filter_fb.at(i).toObject();
		CONF_WAVE_FILTER_PARAM tempStu;
		tempStu.nType = tempObj["type"].toInt();
		tempStu.nSerial = tempObj["serial"].toInt();
		tempStu.freq = tempObj["freq"].toInt();
		tempStu.boost = tempObj["boost"].toDouble();
		tempStu.nQ = tempObj["bandWidth"].toDouble();
		tempStu.gain = tempObj["gain"].toInt();
		m_vec_fb[i] = tempStu;
	}
	/*
	//MUSIC配置读取
	QJsonArray objArray_wave_filter_music = obj_wave_filter_music["data"].toArray();
	for (int i = 0; i < objArray_wave_filter_music.size(); i++)
	{
		QJsonObject tempObj = objArray_wave_filter_music.at(i).toObject();
		CONF_WAVE_FILTER_PARAM tempStu;
		tempStu.nType = WAVE_MUSIC;
		tempStu.nSerial = tempObj["serial"].toInt();
		tempStu.freq = tempObj["freq"].toInt();
		tempStu.boost = tempObj["boost"].toInt();
		tempStu.nQ = tempObj["bandWidth"].toInt();
		tempStu.gain = tempObj["gain"].toInt();
		m_vec_music[i] = tempStu;
	}
	*/
	return true;
}

bool Config::writeJson(QString strFile)
{
	//QString strPathFile = QApplication::applicationDirPath();
	//strPathFile = strPathFile + QString("/config/ANCTool/wave_filter_conf.json");
	QFile file(strFile);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		qDebug() << "打开文件失败,错误信息为：" << file.errorString();
		return false;
	}
	file.resize(0);	//清空文件中的原有内容

	//
	QJsonDocument jsonDoc;
	QJsonObject jsonConf;
	QJsonObject jsonWaveFF;
	QJsonObject jsonWaveFB;
	QJsonArray jsonArrayWaveFF;
	QJsonArray jsonArrayWaveFB;

	for (int i = 0; i < ConfFilesMaxValue; i++)
	{
		QJsonObject jsonObj;
		CONF_WAVE_FILTER_PARAM tempParam = m_vec_ff[i];
		jsonObj["serial"] = tempParam.nSerial;
		jsonObj["type"] = tempParam.nType;
		jsonObj["freq"] = tempParam.freq;
		jsonObj["boost"] = tempParam.boost;
		jsonObj["bandWidth"] = tempParam.nQ;
		jsonObj["gain"] = tempParam.gain;
		jsonObj["slope"] = tempParam.slope;
		jsonArrayWaveFF.append(jsonObj);
 	}
	jsonWaveFF["data"] = jsonArrayWaveFF;

	for (int i = 0; i < ConfFilesMaxValue; i++)
	{
		QJsonObject jsonObj;
		CONF_WAVE_FILTER_PARAM tempParam = m_vec_fb[i];
		jsonObj["serial"] = tempParam.nSerial;
		jsonObj["type"] = tempParam.nType;
		jsonObj["freq"] = tempParam.freq;
		jsonObj["boost"] = tempParam.boost;
		jsonObj["bandWidth"] = tempParam.nQ;
		jsonObj["gain"] = tempParam.gain;
		jsonObj["slope"] = tempParam.slope;
		jsonArrayWaveFB.append(jsonObj);
	}
	jsonWaveFB["data"] = jsonArrayWaveFB;
	/*
	for(int i = 0; i < ConfFilesMaxValue; i++)
	{
		QJsonObject jsonObj;
		CONF_WAVE_FILTER_PARAM tempParam = m_vec_music[i];
		jsonObj["serial"] = tempParam.nSerial;
		jsonObj["freq"] = tempParam.freq;
		jsonObj["boost"] = tempParam.boost;
		jsonObj["bandWidth"] = tempParam.nQ;
		jsonObj["gain"] = tempParam.gain;
		jsonArrayWaveMUSIC.append(jsonObj);
	}
	jsonWaveMUSIC["data"] = jsonArrayWaveMUSIC;
	*/
	jsonConf["wave_filter_ff"] = jsonWaveFF;
	jsonConf["wave_filter_fb"] = jsonWaveFB;
	jsonConf["freqrate"] = m_sys_freqRate;
	//jsonConf["wave_filter_music"] = jsonWaveMUSIC;
	

	jsonDoc.setObject(jsonConf);
	file.write(jsonDoc.toJson());
	file.close();
	return true;
}

bool Config::readJson_axis()
{
	QString strPathFile = QApplication::applicationDirPath();
	strPathFile = strPathFile + QString("/config/ANCTool/axis_conf.json");
	QFile file(strPathFile);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		qDebug() << "打开文件失败,错误信息为：" << file.errorString();
		return false;
	}

	QByteArray allData = file.readAll();
	file.close();

	QJsonParseError jsonError;
	QJsonDocument jsonDoc(QJsonDocument::fromJson(allData, &jsonError));

	if (jsonError.error != QJsonParseError::NoError)
	{
		qDebug() << "json error!" << jsonError.errorString();
		return false;
	}

	QJsonObject root = jsonDoc.object();
	QJsonObject obj_axis = root["axis"].toObject();
	QJsonObject obj_fr = obj_axis["fr"].toObject();
	m_sys_dB = obj_axis["sysdb"].toInt();
	QJsonObject obj_phase = obj_axis["phase"].toObject();
	//配置读取FR
	m_fr_chart_axis.nMin_x = obj_fr["min_x"].toInt();
	m_fr_chart_axis.nMax_x = obj_fr["max_x"].toInt();
	m_fr_chart_axis.nMin_y = obj_fr["min_y"].toInt();
	m_fr_chart_axis.nMax_y = obj_fr["max_y"].toInt();
	//配置读取FR
	m_phase_chart_axis.nMin_x = obj_phase["min_x"].toInt();
	m_phase_chart_axis.nMax_x = obj_phase["max_x"].toInt();
	m_phase_chart_axis.nMin_y = obj_phase["min_y"].toInt();
	m_phase_chart_axis.nMax_y = obj_phase["max_y"].toInt();
	return true;
}

bool Config::writeJson_axis()
{
	QString strPathFile = QApplication::applicationDirPath();
	strPathFile = strPathFile + QString("/config/ANCTool/axis_conf.json");
	QFile file(strPathFile);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		qDebug() << "打开文件失败,错误信息为：" << file.errorString();
		return false;
	}
	file.resize(0);	//清空文件中的原有内容

					//
	QJsonDocument jsonDoc;
	QJsonObject root;
	QJsonObject obj_axis;
	QJsonObject obj_fr;
	QJsonObject obj_phase;
	//获取配置数据fr
	obj_fr["min_x"] = m_fr_chart_axis.nMin_x;
	obj_fr["max_x"] = m_fr_chart_axis.nMax_x;
	obj_fr["min_y"] = m_fr_chart_axis.nMin_y;
	obj_fr["max_y"] = m_fr_chart_axis.nMax_y;
	//获取配置数据fr
	obj_phase["min_x"] = m_phase_chart_axis.nMin_x;
	obj_phase["max_x"] = m_phase_chart_axis.nMax_x;
	obj_phase["min_y"] = m_phase_chart_axis.nMin_y;
	obj_phase["max_y"] = m_phase_chart_axis.nMax_y;
	obj_axis["fr"] = obj_fr;
	obj_axis["phase"] = obj_phase;
	obj_axis["sysdb"] = m_sys_dB;
	root["axis"] = obj_axis;

	jsonDoc.setObject(root);
	file.write(jsonDoc.toJson());
	file.close();
	return true;
}

void Config::set_wave_filter_conf(WAVE_FILTER_TYPE nType, const CONF_WAVE_FILTER_PARAM & stuVal)
{
	m_wave_filter_modified_flag = true;
	switch (nType)
	{
	case WAVE_FF:
		for (int i = 0; i < ConfFilesMaxValue; ++i)
		{
			if (m_vec_ff[i].nSerial == stuVal.nSerial)
			{
				m_vec_ff[i] = stuVal;
				break;
			}
		}
		break;
	case WAVE_FB:
		for (int i = 0; i < ConfFilesMaxValue; ++i)
		{
			if (m_vec_fb[i].nSerial == stuVal.nSerial)
			{
				m_vec_fb[i] = stuVal;
				break;
			}
		}
		break;
	case WAVE_MUSIC:
		for (int i = 0; i < ConfFilesMaxValue; ++i)
		{
			if (m_vec_music[i].nSerial == stuVal.nSerial)
			{
				m_vec_music[i] = stuVal;
				break;
			}
		}
		break;
	default:
		break;
	}
}

CONF_WAVE_FILTER_PARAM Config::get_wave_filter_conf(WAVE_FILTER_TYPE nType, int nSerial)
{
	CONF_WAVE_FILTER_PARAM tempStu;
	switch (nType)
	{
	case WAVE_FF:
		for (int i = 0; i < ConfFilesMaxValue; ++i)
		{
			if (m_vec_ff[i].nSerial == nSerial)
			{
				tempStu = m_vec_ff[i];
				break;
			}
		}
		break;
	case WAVE_FB:
		for (int i = 0; i < ConfFilesMaxValue; ++i)
		{
			if (m_vec_fb[i].nSerial == nSerial)
			{
				tempStu = m_vec_fb[i];
				break;
			}
		}
		break;
	case WAVE_MUSIC:
		for (int i = 0; i < ConfFilesMaxValue; ++i)
		{
			if (m_vec_music[i].nSerial == nSerial)
			{
				tempStu = m_vec_music[i];
				break;
			}
		}
		break;
	default:
		break;
	}
	return tempStu;
}
