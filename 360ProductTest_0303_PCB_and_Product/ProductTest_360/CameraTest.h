#pragma once

#include <QWidget>
#include "ui_CameraTest.h"

class CameraTest : public QWidget
{
	Q_OBJECT

public:
	CameraTest(QWidget *parent = Q_NULLPTR);
	~CameraTest();

private:
	Ui::CameraTest ui;

private slots:
	void on_pushButton_clicked();
	void on_pushButton_2_clicked();
	void on_pushButton_3_clicked();
	void on_pushButton_4_clicked();
signals:
	void nextTest(bool, int);
	void finishedInfo();
};
