#pragma once

#include <QWidget>
#include "ui_DeviceInformation.h"

class DeviceInformation : public QWidget
{
	Q_OBJECT

public:
	DeviceInformation(QWidget *parent = Q_NULLPTR);
	~DeviceInformation();

private:
	Ui::DeviceInformation ui;
private slots:
	void on_pushButton_clicked();
signals:
	void nextTest(bool, int);
	void finishedInfo();
};
