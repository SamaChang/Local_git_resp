#include "QEQLinesChart.h"
#include "qcustomplot.h"

QEQLinesChart::QEQLinesChart(QWidget *parent)
	: QAbstractDynamicLinesChart(parent)
	, m_vec_x(10)
	, m_vec_y(10,0)
	, m_point(-1)
	, m_nVoice_xishu(0)
	, m_dMoveDis(0)
{

	m_vec_x = {31,63,125,250,500,1000,2000,4000,8000,16000};

}

QEQLinesChart::~QEQLinesChart()
{
}

void QEQLinesChart::initDraw(int nLineNum /*= 1*/)
{
	m_linesNum = nLineNum;
	m_pCustomPlot = new QCustomPlot(this);
	//m_pCustomPlot->setBackground(QColor(255, 255, 255, 0));
	m_pCustomPlot->addGraph();

	//将Chart显示到界面中
	QHBoxLayout *pLayout = new QHBoxLayout(this);
	pLayout->addWidget(m_pCustomPlot);
	this->setLayout(pLayout);
	pLayout->setMargin(0);

	//m_pCustomPlot->setInteractions(QCP::iSelectItems);
	m_nAxisXMin = 10;
	m_nAxisXMax = 20000;
	m_nAxisYMin = -35;
	m_nAxisYMax = 35;
	m_pCustomPlot->xAxis->setRange(m_nAxisXMin, m_nAxisXMax);
	m_pCustomPlot->yAxis->setRange(m_nAxisYMin, m_nAxisYMax);

	

	QSharedPointer<QCPAxisTickerLog> logTicker(new QCPAxisTickerLog);
	m_pCustomPlot->xAxis->setTicker(logTicker);
	m_pCustomPlot->xAxis->setScaleType(QCPAxis::stLogarithmic);
	logTicker->setLogBase(10);


	m_pCustomPlot->addGraph();
	//m_pCustomPlot->graph(0)->setLineStyle(QCPGraph::lsNone);
	m_pCustomPlot->graph(0)->setLineStyle(QCPGraph::LineStyle::lsNone);
	m_pCustomPlot->graph(0)->setData(m_vec_x, m_vec_y);
	m_pCustomPlot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, QPen(Qt::black, 1.5), QBrush(Qt::red), 9));
	m_pCustomPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

	m_pCustomPlot->addGraph();
	m_pCustomPlot->graph(1)->setLineStyle(QCPGraph::lsLine);
	QVector<double> x(22050), y(22050);
	for (int i= 0; i<22050; ++i)
	{
		x[i] = i + 1;
		y[i] = 0;
	}
	m_pCustomPlot->graph(1)->setData(x, y);
	//connect(m_pCustomPlot, &QCustomPlot::mousePress, this, &QEQLinesChart::plotMousePressEvent);
	//connect(m_pCustomPlot, &QCustomPlot::mouseRelease, this, &QEQLinesChart::plotMouseReleaseEvent);
	//connect(m_pCustomPlot, &QCustomPlot::mouseMove, this, &QEQLinesChart::plotMouseMoveEvent);
}

void QEQLinesChart::drawLine()
{

}

void QEQLinesChart::addData(int nPosLine, const QVector<double> &keys, const QVector<double> &values, const QVector<double> &keys_2, const QVector<double> &values_2, bool alreadySorted /*= true*/)
{
	m_vec_x = keys_2;
	m_vec_y = values_2;
	m_pCustomPlot->graph(0)->setData(keys_2, values_2);
	m_pCustomPlot->graph(1)->setData(keys, values, alreadySorted);
	m_pCustomPlot->replot();
}

void QEQLinesChart::set_freq_point_change(int nIndex, int nVal)
{
	m_vec_y[nIndex-1] = nVal;
	m_pCustomPlot->graph(0)->setData(m_vec_x, m_vec_y);
	m_pCustomPlot->replot();
}

void QEQLinesChart::set_freq_point_voice_xishu(double dVal)
{
	m_nVoice_xishu = dVal;
	updatePosition();

}

void QEQLinesChart::updatePosition()
{
	//加上音量值，如果大于30，Y轴坐标整体就下移； 如果小于-30，Y轴坐标整体上移
	int nSeek = 0;
	int nError = 0;
	for (int i = 0; i < 10; i++)
	{
		int nTemp = m_vec_y[i] + m_nVoice_xishu;
		nError = fabs(nTemp) - 30;
		if (nError > 0)		//说明在上象限或者下象限有值超过了30
		{
			if (nTemp > 0)
			{
				nSeek = nTemp - 30;
			}
			else
			{
				nSeek = nTemp + 30;
			}
			break;
		}
	}

	if (nError > 0)
	{
		for (int i = 0; i < 10; ++i)
		{
			m_vec_y[i] = m_vec_y[i] - nSeek;
		}
		m_pCustomPlot->graph(0)->setData(m_vec_x, m_vec_y);
		//m_pCustomPlot->replot();
		/*
		for (int i = 0; i < 10; ++i)
		{
			emit sig_freq_point_changed(i, m_vec_y[i]);
		}
		*/
	}
}

/*

void QEQLinesChart::plotMousePressEvent(QMouseEvent* event)
{
	int x_pos = event->pos().x();
	int y_pos = event->pos().y();

	float x_val = m_pCustomPlot->xAxis->pixelToCoord(x_pos);
	float y_val = m_pCustomPlot->yAxis->pixelToCoord(y_pos);



	for (int i = 0; i < 10; i++)
	{
		if (fabs(x_val - m_vec_x.at(i)) < (i>0?(1+(i-1)*10):1) && fabs(y_val - m_vec_y.at(i)) < 0.5)
		{
			qDebug() << QStringLiteral("现在选中了频点是 ") << m_vec_x.at(i);
			m_point = i;
			m_dMoveDis = y_val;
			break;
		}
	}
}

void QEQLinesChart::plotMouseReleaseEvent(QMouseEvent* event)
{
	m_pCustomPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
	m_point = -1;
}

void QEQLinesChart::plotMouseMoveEvent(QMouseEvent* event)
{
	if (m_point == -1)
	{
		return;
	}

	m_pCustomPlot->setInteractions(QCP::iRangeZoom);

	int x_pos = event->pos().x();
	int y_pos = event->pos().y();

	float x_val = m_pCustomPlot->xAxis->pixelToCoord(x_pos);
	float y_val = m_pCustomPlot->yAxis->pixelToCoord(y_pos);

	double dCCC = abs(abs(y_val) - abs(m_dMoveDis));
	if (dCCC > 1)
	{
		//m_vec_x[m_point] = x_val;
		int nVal = qRound(y_val);
		if (nVal > 30)
		{
			nVal = 30;
		}
		else if (nVal < -30)
		{
			nVal = -30;
		}
		m_vec_y[m_point] = nVal;
		//m_pCustomPlot->graph(0)->setData(m_vec_x, m_vec_y);
		emit sig_freq_point_changed(m_point, nVal);
		updatePosition();
		m_dMoveDis = y_val;
	}
}

*/
