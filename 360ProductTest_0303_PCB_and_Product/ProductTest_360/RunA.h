#pragma once

#include <QWidget>
#include "ui_RunA.h"

class RunA : public QWidget
{
	Q_OBJECT

public:
	RunA(QWidget *parent = Q_NULLPTR);
	~RunA();

private:
	Ui::RunA ui;
	float curr;//≤‚ ‘µÁ¡˜
private slots:
	void on_pushButton_clicked();
	void on_pushButton_2_clicked();
	void on_pushButton_3_clicked();
signals:
	void nextTest(bool, int);
	void finishedInfo();
};
