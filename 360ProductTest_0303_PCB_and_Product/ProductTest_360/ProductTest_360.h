#pragma once

#include <QtWidgets/QWidget>
#include "ui_ProductTest_360.h"
#include "ChoosePro.h"
#include "SNInformation.h"

class ProductTest_360 : public QWidget
{
    Q_OBJECT

public:
    ProductTest_360(QWidget *parent = Q_NULLPTR);
	~ProductTest_360();
private:
    Ui::ProductTest_360Class ui;
	ChoosePro *product;
	SNInformation *snInformation;
	//QStringList devices;
private slots:
	void mainTest();
	void showMainForm();
	void on_pushButton_clicked();
};
