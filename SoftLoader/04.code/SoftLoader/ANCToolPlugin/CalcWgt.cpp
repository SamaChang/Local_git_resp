#include "CalcWgt.h"

CalcWgt::CalcWgt(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	connect(ui.pushButton, &QPushButton::clicked, [this] {
		this->accept();
	});
	connect(ui.pushButton_2, &QPushButton::clicked, [this] {
		this->reject();
	});
}

CalcWgt::~CalcWgt()
{
}

void CalcWgt::getCalc(int & nLine_1, int & nLine_2, int & nWay)
{
	nLine_1 = ui.comboBox->currentIndex() + 1;
	nLine_2 = ui.comboBox_2->currentIndex() + 1;
	nWay = ui.comboBox_3->currentIndex() + 1;
}
