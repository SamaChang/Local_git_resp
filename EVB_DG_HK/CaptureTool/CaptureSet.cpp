#include "CaptureSet.h"

CaptureSet::CaptureSet(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	//format.resize(3);
}

CaptureSet::~CaptureSet()
{
}

void CaptureSet::on_pushButton_clicked()
{
	char format[6] = { 0 };
	//rgb
	if (ui.checkBox_2->isChecked())
	{
		//format.push_back(1);
		format[0] = 1;
	}
	else
	{
		//format.push_back(0);
		format[0] = 0;
	}
	//ir
	if (ui.checkBox_3->isChecked())
	{
		//format.push_back(1);
		format[1] = 1;
	}
	else
	{
		format[1] = 0;
		//format.push_back(0);
	}
	//spk
	if (ui.checkBox_4->isChecked())
	{
		format[2] = 1;
	}
	else
	{
		format[2] = 0;
	}
	//Camera_EVB
	if (ui.checkBox_5->isChecked())
		format[3] = 1;
	else
	{
		format[3] = 0;
	}
	//Camera_DG
	if (ui.checkBox_6->isChecked())
		format[4] = 1;
	else
	{
		format[4] = 0;
	}
	//Camera_HK
	if (ui.checkBox_7->isChecked())
		format[5] = 1;
	else
	{
		format[5] = 0;
	}
	emit pic_format(format);
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
