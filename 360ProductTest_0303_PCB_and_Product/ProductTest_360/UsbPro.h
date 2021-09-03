#pragma once

#include <QWidget>
#include "ui_UsbPro.h"

class UsbPro : public QWidget
{
	Q_OBJECT

public:
	UsbPro(QWidget *parent = Q_NULLPTR);
	~UsbPro();

private:
	Ui::UsbPro ui;

private slots:
	void on_pushButton_clicked();
	void on_pushButton_2_clicked();
	void on_pushButton_3_clicked();
signals:
	void nextTest(bool, int);
	void finishedInfo();
};
