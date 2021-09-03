#pragma once

#include <QWidget>
#include "ui_DataCode.h"

class DataCode : public QWidget
{
	Q_OBJECT

public:
	DataCode(QWidget *parent = Q_NULLPTR);
	~DataCode();

private:
	Ui::DataCode ui;

private slots:
	void on_pushButton_clicked();
	void on_pushButton_2_clicked();
	void on_pushButton_3_clicked();
signals:
	void nextTest(bool, int);
	void finishedInfo();
};
