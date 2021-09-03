#pragma once

#include <QtWidgets/QWidget>
#include "ui_NewUsbUpgrade.h"
#include "SingleUpgrade.h"
#include <vector>
#include "Common.h"
//#include "UsbControl.h"

#define WDG_COUNT	8

class NewUsbUpgrade : public QWidget
{
    Q_OBJECT

public:
    NewUsbUpgrade(QWidget *parent = Q_NULLPTR);

private:
    Ui::NewUsbUpgradeClass ui;
	SingleUpgrade *singleWdg;
	std::vector<SingleUpgrade *>single_vec;
	void initWdg();
	void get_usb_dev();
	void readIni();
	void usb_upgrade();
	//UsbControl *usbControl;
	QByteArray fileData;
	int usb_dev_count;
	void selected_file();
	inline int isX(QString str)
	{
		if (str.contains('x') || str.contains('X'))
			return 16;
		return 10;
	}

private slots:
	void on_pushButton_clicked();
	void on_pushButton_2_clicked();
	void on_pushButton_3_clicked();
	void on_pushButton_4_clicked();
	void on_pushButton_5_clicked();


signals:
	void handShake();
	
};
