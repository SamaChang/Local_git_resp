#pragma once

#include <QDialog>
#include "ui_FilePath.h"
#include <qfiledialog.h>

class FilePath : public QDialog
{
	Q_OBJECT

public:
	FilePath(QWidget *parent = Q_NULLPTR);
	~FilePath();
	//QString root_path;
private:
	Ui::FilePath ui;
	QString root_path;
private slots:
	void on_pushButton_clicked();
	void on_pushButton_2_clicked();
	void on_pushButton_3_clicked();
	void on_pushButton_4_clicked();
signals:
	void send_path(QString path);
};
