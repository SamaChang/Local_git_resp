#pragma once

#include <QWidget>
#include "ui_GPIO.h"

class GPIO : public QWidget
{
	Q_OBJECT

public:
	GPIO(QWidget *parent = Q_NULLPTR);
	~GPIO();

private:
	Ui::GPIO ui;
private slots:
	void on_pushButton_clicked();
	void on_pushButton_2_clicked();
signals:
	void nextTest(bool, int);
	void finishedInfo();
};
