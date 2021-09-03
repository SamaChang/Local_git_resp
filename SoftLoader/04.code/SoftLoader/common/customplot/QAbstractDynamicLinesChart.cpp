#include "QAbstractDynamicLinesChart.h"

QAbstractDynamicLinesChart::QAbstractDynamicLinesChart(QWidget *parent)
	: QWidget(parent)
	, m_nAxisXMin(1)
	, m_nAxisXMax(8000)
	, m_nAxisYMin(-60)
	, m_nAxisYMax(60)
{
}

QAbstractDynamicLinesChart::~QAbstractDynamicLinesChart()
{
}

void QAbstractDynamicLinesChart::setAxisXMin(double nMin)
{
	m_nAxisXMin = nMin;
}

void QAbstractDynamicLinesChart::setAxisXMax(double nMax)
{
	m_nAxisXMax = nMax;
}

void QAbstractDynamicLinesChart::setAxisYMin(double nMin)
{
	m_nAxisYMin = nMin;
}

void QAbstractDynamicLinesChart::setAxisYMax(double nMax)
{
	m_nAxisYMax = nMax;
}

void QAbstractDynamicLinesChart::setAxis_x(double nMin, double nMax)
{
	m_nAxisXMin = nMin;
	m_nAxisXMax = nMax;
}

void QAbstractDynamicLinesChart::setAxis_y(double nMin, double nMax)
{
	m_nAxisYMin = nMin;
	m_nAxisYMax = nMax;
}

