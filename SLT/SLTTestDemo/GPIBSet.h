#pragma once

#include <QWidget>
#include "ui_GPIBSet.h"

class GPIBSet : public QWidget
{
	Q_OBJECT

public:
	GPIBSet(QWidget *parent = Q_NULLPTR);
	~GPIBSet();

private:
	Ui::GPIBSet ui;
	int findRsrc();
	QStringList list;
	QString gpib_name;
private slots:
	void on_pushButton_clicked();
	void on_pushButton_2_clicked();
	void on_pushButton_3_clicked();
signals:
	void send_gpib(QString str);
};
