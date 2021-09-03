#pragma once

#include "QAbstractDynamicLinesChart.h"

class QCustomPlot;

class QFreqLinesChart : public QAbstractDynamicLinesChart
{
	Q_OBJECT

public:
	QFreqLinesChart(QWidget *parent);
	~QFreqLinesChart();

	virtual void initDraw(int nLineNum=1);			//初始化画布
	virtual void drawLine();			//划线

	void setLineVisible(int nIndex, bool bShow = true);
	void setLineColor(int nIndex, const QColor & clr);
	void addData(int nPosLine, const QVector<double> &keys, const QVector<double> &values, bool alreadySorted = true);

	void reFreshAxis();
	
private:
	QCustomPlot *m_pCustomPlot;

};
