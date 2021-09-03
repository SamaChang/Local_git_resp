#pragma once

#include <QWidget>
#include "ui_Uart.h"

class Uart : public QWidget
{
	Q_OBJECT

public:
	Uart(QWidget *parent = Q_NULLPTR);
	~Uart();
	
private:
	Ui::Uart ui;

private slots:
	void on_pushButton_clicked();
	void on_pushButton_2_clicked();
	void on_pushButton_3_clicked();
signals:
	void nextTest(bool, int);
	void finishedInfo();
};
