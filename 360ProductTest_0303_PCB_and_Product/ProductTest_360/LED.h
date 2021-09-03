#pragma once

#include <QWidget>
#include "ui_LED.h"

class LED : public QWidget
{
	Q_OBJECT

public:
	LED(QWidget *parent = Q_NULLPTR);
	~LED();

private:
	Ui::LED ui;
private slots:
	void on_pushButton_clicked();
	void on_pushButton_2_clicked();
	void on_pushButton_3_clicked();
	void on_pushButton_4_clicked();
	void on_pushButton_5_clicked();
signals:
	void nextTest(bool, int);
	void finishedInfo();
};
