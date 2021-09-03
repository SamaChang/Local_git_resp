#pragma once

#include <QWidget>

class QAbstractDynamicLinesChart : public QWidget
{
	Q_OBJECT

public:
	QAbstractDynamicLinesChart(QWidget *parent = nullptr);
	virtual ~QAbstractDynamicLinesChart();

public:
	//初始化线配置
	virtual void initDraw(int nLineNum = 1) = 0;
	//划线
	virtual void drawLine() = 0;
	//设置X轴最小值
	virtual void setAxisXMin(double nMin);
	//设置X轴最大值
	virtual void setAxisXMax(double nMax);
	//设置Y轴最小值
	virtual void setAxisYMin(double nMin);
	//设置Y轴最大值
	virtual void setAxisYMax(double nMax);
	//设置X轴范围
	virtual void setAxis_x(double nMin, double nMax);
	//设置Y轴范围
	virtual void setAxis_y(double nMin, double nMax);


public:
	double m_nAxisXMin;
	double m_nAxisXMax;
	double m_nAxisYMin;
	double m_nAxisYMax;

	int m_linesNum;			//能够添加的线段数
};
