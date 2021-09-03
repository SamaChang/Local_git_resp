#pragma once

#include <QWidget>
#include "ui_PreventRemove.h"

class PreventRemove : public QWidget
{
	Q_OBJECT

public:
	PreventRemove(QWidget *parent = Q_NULLPTR);
	~PreventRemove();

private:
	Ui::PreventRemove ui;

private slots:
	void on_pushButton_clicked();
	void on_pushButton_2_clicked();
	void on_pushButton_3_clicked();
signals:
	void nextTest(bool, int);
	void finishedInfo();
};
