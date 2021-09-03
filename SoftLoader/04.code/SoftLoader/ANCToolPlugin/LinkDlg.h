#pragma once

#include <QDialog>
#include "ui_LinkDlg.h"

class LinkDlg : public QDialog
{
	Q_OBJECT

public:
	LinkDlg(QWidget *parent = Q_NULLPTR);
	~LinkDlg();

private:
	Ui::LinkDlg ui;
};
