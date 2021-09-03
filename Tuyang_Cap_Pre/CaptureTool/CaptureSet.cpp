#include "CaptureSet.h"

CaptureSet::CaptureSet(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
}

CaptureSet::~CaptureSet()
{
}

void CaptureSet::on_pushButton_clicked()
{
	if (ui.checkBox->isChecked())
	{
		int ms = ui.spinBox->value();
		int pic = ui.lineEdit->text().toInt();
		emit shot_mode(true, ms, pic);
		//emit delay_time(ui.spinBox->value());
	}	
	else
	{
		emit shot_mode(false, 0, 0);
	}
	this->close();
}
