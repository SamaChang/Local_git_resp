#include "QFreqLinesChart.h"
#include "qcustomplot.h"
#include "Utility.h"

QFreqLinesChart::QFreqLinesChart(QWidget *parent)
	: QAbstractDynamicLinesChart(parent)
{
}

QFreqLinesChart::~QFreqLinesChart()
{
}

void QFreqLinesChart::initDraw(int nLineNum)
{
	m_linesNum = nLineNum;
	m_pCustomPlot = new QCustomPlot;

	//设置画布背景色 

	QLinearGradient plotGradient;

	/*
	plotGradient.setStart(0, 0);
	plotGradient.setFinalStop(0, 350);
	plotGradient.setColorAt(0, QColor(80, 80, 80));
	plotGradient.setColorAt(1, QColor(50, 50, 50));
	m_pCustomPlot->setBackground(plotGradient);
	*/
	//添加六条线
	for (int i = 0; i < m_linesNum; ++i)
	{
		m_pCustomPlot->addGraph();
		m_pCustomPlot->graph(i)->setPen(QPen(QColor(LineColors[i])));
	}
	
	//将Chart显示到界面中
	QHBoxLayout *pLayout = new QHBoxLayout(this);
	pLayout->addWidget(m_pCustomPlot);
	this->setLayout(pLayout);
	pLayout->setMargin(0);

	connect(m_pCustomPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), m_pCustomPlot->xAxis2, SLOT(setRange(QCPRange)));
	connect(m_pCustomPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), m_pCustomPlot->yAxis2, SLOT(setRange(QCPRange)));

	m_pCustomPlot->rescaleAxes(true);

	m_pCustomPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

	m_pCustomPlot->xAxis->setRange(m_nAxisXMin, m_nAxisXMax);
	m_pCustomPlot->yAxis->setRange(m_nAxisYMin, m_nAxisYMax);
	
	QSharedPointer<QCPAxisTickerLog> logTicker(new QCPAxisTickerLog);
	m_pCustomPlot->xAxis->setTicker(logTicker);
	m_pCustomPlot->xAxis->setScaleType(QCPAxis::stLogarithmic);
	logTicker->setLogBase(10);

	m_pCustomPlot->xAxis->ticker()->setTickCount(10);
	m_pCustomPlot->xAxis->setSubTicks(true);
	m_pCustomPlot->xAxis->grid()->setSubGridVisible(true);
	m_pCustomPlot->yAxis->grid()->setSubGridVisible(true);
	
}

void QFreqLinesChart::drawLine()
{

}

void QFreqLinesChart::setLineVisible(int nIndex, bool bShow /*= true*/)
{
	if (nIndex > m_linesNum)
		return;

	QCPGraph* pCPGraph = m_pCustomPlot->graph(nIndex);
	if (pCPGraph)
	{
		pCPGraph->setVisible(bShow);
	}
	m_pCustomPlot->replot();
}

void QFreqLinesChart::setLineColor(int nIndex, const QColor & clr)
{
	if (nIndex > m_linesNum)
		return;

	QCPGraph* pCPGraph = m_pCustomPlot->graph(nIndex);
	if (pCPGraph)
	{
		pCPGraph->setPen(QPen(clr));
	}
	m_pCustomPlot->replot();
}

void QFreqLinesChart::addData(int nPosLine, const QVector<double> &keys, const QVector<double> &values, bool alreadySorted /*= true*/)
{
	if (nPosLine > m_linesNum)
		return;

	QCPGraph* pCPGraph = m_pCustomPlot->graph(nPosLine);
	if (pCPGraph)
	{
		pCPGraph->setData(keys, values, alreadySorted);
	}
	m_pCustomPlot->replot();
}

void QFreqLinesChart::reFreshAxis()
{
	m_pCustomPlot->xAxis->setRange(m_nAxisXMin, m_nAxisXMax);
	m_pCustomPlot->yAxis->setRange(m_nAxisYMin, m_nAxisYMax);
	m_pCustomPlot->replot();
}
