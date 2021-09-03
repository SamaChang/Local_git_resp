#pragma once

#include <QDialog>
#include "ui_CaptureSet.h"
#include <vector>

class CaptureSet : public QDialog
{
	Q_OBJECT

public:
	CaptureSet(QWidget *parent = Q_NULLPTR);
	~CaptureSet();

private:
	Ui::CaptureSet ui;
	//std::vector<char>format;
private slots:
	void on_pushButton_clicked();
signals:
	void shot_mode(bool check, int seconds, int shoot_pic);
	void pic_format(char *value);
	//void delay_time(int seconds);
};
