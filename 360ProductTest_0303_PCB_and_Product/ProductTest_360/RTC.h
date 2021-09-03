#pragma once

#include <QWidget>
#include "ui_RTC.h"

class RTC : public QWidget
{
	Q_OBJECT

public:
	RTC(QWidget *parent = Q_NULLPTR);
	~RTC();

private:
	Ui::RTC ui;
private slots:
	void on_pushButton_clicked();
	void on_pushButton_2_clicked();
	void on_pushButton_3_clicked();
signals:
	void nextTest(bool, int);
	void finishedInfo();
};
