#pragma once

#include <QWidget>
#include "ui_Warn.h"

class Warn : public QWidget
{
	Q_OBJECT

public:
	Warn(QWidget *parent = Q_NULLPTR);
	~Warn();

private:
	Ui::Warn ui;

private slots:
	void on_pushButton_clicked();
	void on_pushButton_2_clicked();
	void on_pushButton_3_clicked();
signals:
	void nextTest(bool, int);
	void finishedInfo();
};
