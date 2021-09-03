#pragma once

#include <QDialog>
#include "ui_QConfigAxisDlg.h"

class QConfigAxisDlg : public QDialog
{
	Q_OBJECT

public:
	QConfigAxisDlg(QWidget *parent = Q_NULLPTR);
	~QConfigAxisDlg();
private:
	Ui::QConfigAxisDlg ui;
};
