#pragma once

#include <QWidget>
#include "ui_Wgen.h"

class Wgen : public QWidget
{
	Q_OBJECT

public:
	Wgen(QWidget *parent = Q_NULLPTR);
	~Wgen();

private:
	Ui::Wgen ui;

private slots:
	void on_pushButton_clicked();
	void on_pushButton_2_clicked();
	void on_pushButton_3_clicked();
	void on_pushButton_4_clicked();
signals:
	void nextTest(bool, int);
	void finishedInfo();
};
