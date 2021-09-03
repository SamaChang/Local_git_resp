#pragma once

#include <QWidget>
#include "ui_IRLamp.h"

class IRLamp : public QWidget
{
	Q_OBJECT

public:
	IRLamp(QWidget *parent = Q_NULLPTR);
	~IRLamp();

private:
	Ui::IRLamp ui;
private slots:
	void on_pushButton_clicked();
	void on_pushButton_2_clicked();
	void on_pushButton_3_clicked();
	void on_pushButton_4_clicked();
signals:
	void nextTest(bool, int);
	void finishedInfo();
};
