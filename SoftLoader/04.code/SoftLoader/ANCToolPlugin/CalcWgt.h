#pragma once

#include <QDialog>
#include "ui_CalcWgt.h"

class CalcWgt : public QDialog
{
	Q_OBJECT

public:
	CalcWgt(QWidget *parent = Q_NULLPTR);
	~CalcWgt();

	/**
	* @brief  获取计算方式
	* @param  线段1
	* @param  线段2
	* @date   计算方式 1(线段1-线段2） 2(线段1+线段2)
	* @return
	*/
	void  getCalc(int & nLine_1, int & nLine_2, int & nWay);

private:
	Ui::CalcWgt ui;
};
