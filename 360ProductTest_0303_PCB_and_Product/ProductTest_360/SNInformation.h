#pragma once

#include <QWidget>
#include "ui_SNInformation.h"
extern QString snInf;
extern QString dateTimeFileName;
class SNInformation : public QWidget
{
	Q_OBJECT

public:
	SNInformation(QWidget *parent = Q_NULLPTR);
	~SNInformation();

private:
	Ui::SNInformation ui;
	void csvFormat(QString result);
private slots:
	void on_pushButton_clicked();
	void on_pushButton_2_clicked();
signals:
	void testForms();
};
