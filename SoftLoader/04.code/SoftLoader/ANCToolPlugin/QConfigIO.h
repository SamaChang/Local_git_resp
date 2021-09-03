#pragma once

#include <QDialog>
#include "ui_QConfigIO.h"

class QAudioDeviceInfo;

class QConfigIO : public QDialog
{
	Q_OBJECT

public:
	QConfigIO(QWidget *parent = Q_NULLPTR);
	~QConfigIO();

	void setAudioInfo(QAudioDeviceInfo* pInput, QAudioDeviceInfo* pOutput);

private:
	Ui::QConfigIO ui;
	QAudioDeviceInfo* m_pAudioInputInfo;
	QAudioDeviceInfo* m_pAudioOutputInfo;
};
