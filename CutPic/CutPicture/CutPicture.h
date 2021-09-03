#pragma once

#include <QtWidgets/QWidget>
#include "ui_CutPicture.h"

class CutPicture : public QWidget
{
    Q_OBJECT

public:
    CutPicture(QWidget *parent = Q_NULLPTR);

private:
    Ui::CutPictureClass ui;
	QString fileName;
	QVector<QString>files;

private slots:
	void on_pushButton_clicked();
	void on_pushButton_2_clicked();
};
