#pragma once

#include <QWidget>
#include "ui_NetWork.h"

class NetWork : public QWidget
{
	Q_OBJECT

public:
	NetWork(QWidget *parent = Q_NULLPTR);
	~NetWork();

private:
	Ui::NetWork ui;

private slots:
	void on_pushButton_clicked();
	void on_pushButton_2_clicked();
	void on_pushButton_3_clicked();
signals:
	void nextTest(bool, int);
	void finishedInfo();
};
