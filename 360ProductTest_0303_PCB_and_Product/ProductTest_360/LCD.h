#pragma once

#include <QWidget>
#include "ui_LCD.h"

class LCD : public QWidget
{
	Q_OBJECT

public:
	LCD(QWidget *parent = Q_NULLPTR);
	~LCD();

private:
	Ui::LCD ui;

private slots:
	void on_pushButton_clicked();
	void on_pushButton_2_clicked();
	void on_pushButton_3_clicked();
	void on_pushButton_4_clicked();
signals:
	void nextTest(bool, int);
	void finishedInfo();
};
