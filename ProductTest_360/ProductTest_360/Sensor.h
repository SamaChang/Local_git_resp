#pragma once

#include <QWidget>
#include "ui_Sensor.h"

class Sensor : public QWidget
{
	Q_OBJECT

public:
	Sensor(QWidget *parent = Q_NULLPTR);
	~Sensor();

private:
	Ui::Sensor ui;

private slots:
	void on_pushButton_clicked();
	void on_pushButton_2_clicked();
	void on_pushButton_3_clicked();
signals:
	void nextTest(bool, int);
	void finishedInfo();
};
