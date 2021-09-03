#pragma once

#include <QWidget>
#include "ui_BTAndWifi.h"


class BTAndWifi : public QWidget
{
	Q_OBJECT

public:
	BTAndWifi(QWidget *parent = Q_NULLPTR);
	~BTAndWifi();

private:
	Ui::BTAndWifi ui;

private slots:
	void on_pushButton_clicked();
	void on_pushButton_2_clicked();
	void on_pushButton_3_clicked();
	void on_pushButton_4_clicked();
signals:
	void nextTest(bool, int);
	void finishedInfo();
};
