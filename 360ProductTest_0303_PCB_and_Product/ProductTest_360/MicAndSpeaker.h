#pragma once

#include <QWidget>
#include "ui_MicAndSpeaker.h"

class MicAndSpeaker : public QWidget
{
	Q_OBJECT

public:
	MicAndSpeaker(QWidget *parent = Q_NULLPTR);
	~MicAndSpeaker();

private:
	Ui::MicAndSpeaker ui;

private slots:
	void on_pushButton_clicked();
	void on_pushButton_2_clicked();
	void on_pushButton_3_clicked();
	void on_pushButton_4_clicked();
signals:
	void nextTest(bool, int);
	void finishedInfo();
};
