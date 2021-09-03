#include "ArrowWorkChartWgt.h"
#include <QPainter>

ArrowWorkChartWgt::ArrowWorkChartWgt(QWidget *parent)
	: QWidget(parent)
	, m_font("Microsoft YaHei", 8, QFont::Bold)
	, m_nCount(5)
	, m_nBlock(12)
	, m_nSpace(4)
	, m_nCurStep(1)
{
	this->setFixedSize(200, 25);
	m_strListColor << "#dddddc" << "#ffab50" << "#ff7274" << "#ff45b1" << "#079acf"<<"#25d03a";
	//m_nWidth = 300;
	//m_nHeight = 80;
}

ArrowWorkChartWgt::ArrowWorkChartWgt(QWidget *parent, QStringList strListTitles)
	: ArrowWorkChartWgt(parent)
{
	m_nCount = strListTitles.size();
	m_strList = strListTitles;
}

ArrowWorkChartWgt::~ArrowWorkChartWgt()
{
}

void ArrowWorkChartWgt::setTitles(QStringList strList)
{
	m_strList = strList;
	m_nCount = m_strList.size();
}

void ArrowWorkChartWgt::initUI()
{
	m_vecStatus = QVector<bool>(m_nCount, false);
	update();
}

void ArrowWorkChartWgt::setStepStatus(int nStep, bool bFinished)
{
	m_vecStatus[nStep] = bFinished;
}

void ArrowWorkChartWgt::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.setFont(m_font);
	if (!m_vecStatus.at(0))
	{
		paintFirstStep(&painter, QColor(m_strListColor.at(0)));
	}
	else
	{
		m_nCurStep = 1;
		paintFirstStep(&painter, QColor(m_strListColor.at(m_nCurStep)));
	}
	
	for (int i = 2; i < m_nCount; ++i)
	{
		m_nCurStep = i;
		if (!m_vecStatus.at(m_nCurStep-1))
		{
			paintMiddleStep(&painter, QColor(m_strListColor.at(0)));
		}
		else
		{
			paintMiddleStep(&painter, QColor(m_strListColor.at(m_nCurStep)));
		}
	}
	if (!m_vecStatus.last())
	{
		paintLastStep(&painter, QColor(m_strListColor.at(0)));
	}
	else
	{
		m_nCurStep = m_nCount;
		paintLastStep(&painter, QColor(m_strListColor.at(m_nCurStep)));
	}
	QWidget::paintEvent(event);
}

void ArrowWorkChartWgt::resizeEvent(QResizeEvent *event)
{
	QWidget::resizeEvent(event);
	m_nWidth = this->width();
	m_nSubWidth = m_nWidth / m_nCount;
	m_nHeight = this->height();
	this->resize(m_nWidth, m_nHeight);
	
}

void ArrowWorkChartWgt::paintFirstStep(QPainter *painter, QColor bgColor, QColor txtColor)
{
	m_nCurStep = 1;
	painter->save();
	QPointF arrowTopPt;
	QPointF arrowCenterPt;
	QPointF arrowBottomPt;
	arrowCenterPt.rx() = m_nWidth / m_nCount-m_nSpace/2+m_nBlock/2;
	arrowCenterPt.ry() = m_nHeight / 2;

	arrowTopPt.rx() = arrowCenterPt.rx() - m_nBlock;
	arrowTopPt.ry() = 0;

	arrowBottomPt.rx() = arrowCenterPt.rx() - m_nBlock;
	arrowBottomPt.ry() = m_nHeight;

	QVector<QPointF> vecPts;
	vecPts.push_back(QPointF(0, 0));
	vecPts.push_back(arrowTopPt);
	vecPts.push_back(arrowCenterPt);
	vecPts.push_back(arrowBottomPt);
	vecPts.push_back(QPointF(0, m_nHeight));

	QPolygonF polygon(vecPts);

	QPainterPath path;
	path.addPolygon(polygon);
	path.setFillRule(Qt::WindingFill);
	painter->setPen(Qt::NoPen);
	painter->setBrush(bgColor);
	painter->drawPath(path);
	//设置字体颜色
	painter->setPen(QPen(txtColor));
	painter->drawText(QRect(m_nSubWidth*(m_nCurStep - 1), 0, m_nSubWidth, m_nHeight), Qt::AlignCenter, m_strList.at(0));
	painter->restore();
}

void ArrowWorkChartWgt::paintMiddleStep(QPainter *painter, QColor bgColor, QColor txtColor)
{
	painter->save();
	QPointF arrowTopPt_left;
	QPointF arrowCenterPt_left;
	QPointF arrowBottomPt_left;
	QPointF arrowTopPt_right;
	QPointF arrowCenterPt_right;
	QPointF arrowBottomPt_right;
	//m_nSubWidth = m_nWidth / m_nCount;
	//计算中间部分的左边坐标
	arrowCenterPt_left.rx() = m_nSubWidth * (m_nCurStep - 1) + m_nBlock / 2 + m_nSpace / 2 ;
	arrowCenterPt_left.ry() = m_nHeight / 2;

	arrowTopPt_left.rx() = arrowCenterPt_left.rx() - m_nBlock;
	arrowTopPt_left.ry() = 0;

	arrowBottomPt_left.rx() = arrowCenterPt_left.rx() - m_nBlock;
	arrowBottomPt_left.ry() = m_nHeight;
	//计算中间部分的右边坐标
	arrowCenterPt_right.rx() = m_nSubWidth * (m_nCurStep) + m_nBlock / 2- m_nSpace / 2;
	arrowCenterPt_right.ry() = m_nHeight / 2;

	arrowTopPt_right.rx() = arrowCenterPt_right.rx() - m_nBlock;
	arrowTopPt_right.ry() = 0;

	arrowBottomPt_right.rx() = arrowCenterPt_right.rx() - m_nBlock;
	arrowBottomPt_right.ry() = m_nHeight;

	//绘制中间流程箭头
	QVector<QPointF> vecPts;
	vecPts.push_back(arrowTopPt_left);
	vecPts.push_back(arrowCenterPt_left);
	vecPts.push_back(arrowBottomPt_left);
	vecPts.push_back(arrowBottomPt_right);
	vecPts.push_back(arrowCenterPt_right);
	vecPts.push_back(arrowTopPt_right);
	QPolygonF polygon(vecPts);

	QPainterPath path;
	path.addPolygon(polygon);
	path.setFillRule(Qt::WindingFill);
	painter->setPen(Qt::NoPen);
	painter->setBrush(bgColor);
	painter->drawPath(path);
	//设置字体颜色
	painter->setPen(QPen(txtColor));
	painter->drawText(QRect(m_nSubWidth*(m_nCurStep - 1), 0, m_nSubWidth, m_nHeight), Qt::AlignCenter, m_strList.at(m_nCurStep-1));

	painter->restore();
}

void ArrowWorkChartWgt::paintLastStep(QPainter *painter, QColor bgColor, QColor txtColor)
{
	m_nCurStep = m_nCount;
	painter->save();
	QPointF arrowTopPt;
	QPointF arrowCenterPt;
	QPointF arrowBottomPt;
	arrowCenterPt.rx() = m_nWidth / m_nCount*(m_nCurStep-1) + m_nSpace / 2 + m_nBlock / 2;
	arrowCenterPt.ry() = m_nHeight / 2;

	arrowTopPt.rx() = arrowCenterPt.rx() - m_nBlock;
	arrowTopPt.ry() = 0;

	arrowBottomPt.rx() = arrowCenterPt.rx() - m_nBlock;
	arrowBottomPt.ry() = m_nHeight;

	QVector<QPointF> vecPts;
	vecPts.push_back(arrowTopPt);
	vecPts.push_back(QPointF(m_nWidth,0));
	vecPts.push_back(QPointF(m_nWidth, m_nHeight));
	vecPts.push_back(arrowBottomPt);
	vecPts.push_back(arrowCenterPt);

	QPolygonF polygon(vecPts);

	QPainterPath path;
	path.addPolygon(polygon);
	path.setFillRule(Qt::WindingFill);
	painter->setPen(Qt::NoPen);
	painter->setBrush(bgColor);
	painter->drawPath(path);

	//设置字体颜色
	painter->setPen(QPen(txtColor));
	painter->drawText(QRect(m_nSubWidth*(m_nCurStep - 1), 0, m_nSubWidth, m_nHeight), Qt::AlignCenter, m_strList.last());
	painter->restore();
}
