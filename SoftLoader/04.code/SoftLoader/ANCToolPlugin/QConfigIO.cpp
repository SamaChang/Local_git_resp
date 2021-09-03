#include "QConfigIO.h"

#include "Config.h"
#include <QDebug>
#include <QAudioDeviceInfo>
#include <QDebug>

QConfigIO::QConfigIO(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	const QList<QAudioDeviceInfo> lstInputDevInfos = QAudioDeviceInfo::availableDevices(QAudio::AudioInput);
	qDebug() << "*****************audio input count: " << lstInputDevInfos.count()<<"********************";
	QVector<QAudioDeviceInfo> tempVal_input;
    foreach (QAudioDeviceInfo var, lstInputDevInfos)
	{
		bool bFind = false;
		qDebug()<<"name: " << var.deviceName();
        foreach (QAudioDeviceInfo var_2, tempVal_input)
		{
			if (var_2.deviceName() == var.deviceName())
			{
				bFind = true;
				break;
			}
		} 
		if (!bFind)
		{
			tempVal_input.push_back(var);
		}
	}
	qDebug() << "************************************************************";
	
    foreach (QAudioDeviceInfo var, tempVal_input)
	{
		ui.comboBox->addItem(var.deviceName(),QVariant::fromValue(var));
	}
	
	const QList<QAudioDeviceInfo> lstOutputDevInfos = QAudioDeviceInfo::availableDevices(QAudio::AudioOutput);
	QVector<QAudioDeviceInfo> tempVal_output;
    foreach (QAudioDeviceInfo var, lstOutputDevInfos)
	{
		bool bFind = false;
        foreach (QAudioDeviceInfo var_2, tempVal_output)
		{
			if (var_2.deviceName() == var.deviceName())
			{
				bFind = true;
				break;
			}
		}
		if (!bFind)
		{
			tempVal_output.push_back(var);
		}
	}
    foreach (QAudioDeviceInfo var, tempVal_output)
	{
		ui.comboBox_2->addItem(var.deviceName(), QVariant::fromValue(var));
	}

	//确定
	connect(ui.pushButton, &QPushButton::clicked, [this] {
		if (ui.comboBox->currentIndex() >= 0)
		{
			if (ui.comboBox->currentText() != m_pAudioInputInfo->deviceName())
			{
				//修改音频输入，并通知
				*m_pAudioInputInfo = ui.comboBox->itemData(ui.comboBox->currentIndex()).value<QAudioDeviceInfo>();
			}
		}
		if (ui.comboBox_2->currentIndex() >= 0)
		{
			if (ui.comboBox_2->currentText() != m_pAudioOutputInfo->deviceName())
			{
				//修改音频输出，并通知
				*m_pAudioOutputInfo = ui.comboBox_2->itemData(ui.comboBox_2->currentIndex()).value<QAudioDeviceInfo>();
			}
		}
	});
}

QConfigIO::~QConfigIO()
{
}

void QConfigIO::setAudioInfo(QAudioDeviceInfo* pInput, QAudioDeviceInfo* pOutput)
{
	m_pAudioInputInfo = pInput;
	m_pAudioOutputInfo = pOutput;
	ui.comboBox->setCurrentText(m_pAudioInputInfo->deviceName());
	ui.comboBox_2->setCurrentText(m_pAudioOutputInfo->deviceName());
}
