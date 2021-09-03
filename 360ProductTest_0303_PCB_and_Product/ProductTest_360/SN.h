#pragma once

#include <QWidget>
#include "ui_SN.h"
//extern QString snInf;
class SN : public QWidget
{
	Q_OBJECT

public:
	SN(QWidget *parent = Q_NULLPTR);
	~SN();

private:
	Ui::SN ui;

private slots:
	void on_pushButton_clicked();
	void on_pushButton_2_clicked();
	void on_pushButton_3_clicked();
signals:
	void nextTest(bool, int);
	void finishedInfo();
};
