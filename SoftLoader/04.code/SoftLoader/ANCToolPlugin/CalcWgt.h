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
	* @brief  ��ȡ���㷽ʽ
	* @param  �߶�1
	* @param  �߶�2
	* @date   ���㷽ʽ 1(�߶�1-�߶�2�� 2(�߶�1+�߶�2)
	* @return
	*/
	void  getCalc(int & nLine_1, int & nLine_2, int & nWay);

private:
	Ui::CalcWgt ui;
};
