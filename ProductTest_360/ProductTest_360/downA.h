#pragma once

#include <QWidget>
#include "ui_downA.h"

class downA : public QWidget
{
	Q_OBJECT

public:
	downA(QWidget *parent = Q_NULLPTR);
	~downA();

private:
	Ui::downA ui;
private slots:
	void on_pushButton_clicked();
	void on_pushButton_2_clicked();
	void on_pushButton_3_clicked();
signals:
	void nextTest(bool, int);
	void finishedInfo();
};
