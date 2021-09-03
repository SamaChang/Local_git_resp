#pragma once

#include <QWidget>
#include "ui_BlueTooth.h"

class BlueTooth : public QWidget
{
	Q_OBJECT

public:
	BlueTooth(QWidget *parent = Q_NULLPTR);
	~BlueTooth();

private:
	Ui::BlueTooth ui;

private slots:
	void on_pushButton_clicked();
	void on_pushButton_2_clicked();
	void on_pushButton_3_clicked();
signals:
	void nextTest(bool, int);
	void finishedInfo();
};
