#pragma once

#include <QDialog>
#include "ui_QConfAudioDlg.h"

#include <QAudioFormat>

class QConfAudioDlg : public QDialog
{
	Q_OBJECT

public:
	QConfAudioDlg(QWidget *parent = Q_NULLPTR);
	~QConfAudioDlg();

private:
	Ui::QConfAudioDlg ui;
};
