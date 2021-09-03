#pragma once

#include <QWidget>

class QAbstractDynamicLinesChart : public QWidget
{
	Q_OBJECT

public:
	QAbstractDynamicLinesChart(QWidget *parent = nullptr);
	virtual ~QAbstractDynamicLinesChart();

public:
	//��ʼ��������
	virtual void initDraw(int nLineNum = 1) = 0;
	//����
	virtual void drawLine() = 0;
	//����X����Сֵ
	virtual void setAxisXMin(double nMin);
	//����X�����ֵ
	virtual void setAxisXMax(double nMax);
	//����Y����Сֵ
	virtual void setAxisYMin(double nMin);
	//����Y�����ֵ
	virtual void setAxisYMax(double nMax);
	//����X�᷶Χ
	virtual void setAxis_x(double nMin, double nMax);
	//����Y�᷶Χ
	virtual void setAxis_y(double nMin, double nMax);


public:
	double m_nAxisXMin;
	double m_nAxisXMax;
	double m_nAxisYMin;
	double m_nAxisYMax;

	int m_linesNum;			//�ܹ���ӵ��߶���
};
