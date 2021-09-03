#include "RingsProgressBar.h"
#include <QPainter>
constexpr auto MAX_BORDER = 100;
#define INIT_STRING	 QStringLiteral("¥˝∂®")

RingsProgressBar::RingsProgressBar(QWidget *parent)
	: QWidget(parent)
	, m_nRotateAngle(0)
	, m_nPersent(0)
	, m_nBorder(MAX_BORDER)
	, m_strTitle(INIT_STRING)
{
	//this->setFixedSize(250, 250);
	QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	sizePolicy.setHorizontalStretch(0);
	sizePolicy.setVerticalStretch(0);
	this->setSizePolicy(sizePolicy);
}

RingsProgressBar::~RingsProgressBar()
{
}

void RingsProgressBar::setRotateDelta(int delta)
{

}

void RingsProgressBar::setPersent(int nPersent)
{
	if (nPersent != m_nPersent)
	{
		m_nPersent = nPersent;
		m_nBorder = MAX_BORDER - 40 * m_nPersent / 100;
		update();
	}
}

void RingsProgressBar::setTitle(QString strTitle)
{
	m_strTitle = strTitle;
}

void RingsProgressBar::init()
{
	m_strTitle = INIT_STRING;
	m_nPersent = 0;
	update();
}

void RingsProgressBar::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	QWidget* parentWgt = qobject_cast<QWidget*>(parent());
	//int nWidth = parentWgt->width()-10;
	//int nHeight = parentWgt->height()-10;

	m_nRotateAngle = 360 * m_nPersent / 100;
	//int nSide = qMin(this->width(), this->height());
	int nSide = qMin(m_nWidth, m_nHeight)-5;
	int x = 0, y = 0;
	if (nSide <= m_nWidth)
	{
		x = (m_nWidth - nSide) / 2;
	}
	if (nSide <= m_nHeight)
	{
		y = (m_nHeight - nSide) / 2;
	}
	QRectF outRect(x, y, nSide, nSide);
	QRectF inRect(m_nBorder/2+x, m_nBorder/2+y, nSide - m_nBorder, nSide - m_nBorder);
	QString valueStr;
	if (m_nPersent > 0)
	{
		valueStr = QString("%1\n%2%").arg(m_strTitle).arg(QString::number(m_nPersent));
	}
	else
	{
		valueStr = m_strTitle;
	}
	
	//ª≠Õ‚‘≤
	painter.setPen(Qt::NoPen);
	painter.setBrush(QBrush(QColor(97, 117, 118)));
	painter.drawEllipse(outRect);
	painter.setBrush(QBrush(QColor(255, 107, 107)));
	painter.drawPie(outRect, (90 - m_nRotateAngle) * 16, m_nRotateAngle * 16);

	//ª≠’⁄’÷
	painter.setBrush(QBrush(QColor(0, 0, 0)));
	painter.drawEllipse(inRect);

	//ª≠Œƒ◊÷
	QFont font = QFont("Microsoft YaHei", 15, QFont::Bold);
	painter.setFont(font);
	painter.setPen(QColor(70,144,183));
	painter.drawText(inRect, Qt::AlignCenter, valueStr);
	QWidget::paintEvent(event);
}

void RingsProgressBar::resizeEvent(QResizeEvent *event)
{
	//QWidget* parentWgt = qobject_cast<QWidget*>(parent());
	int nWidth = this->width();
	int nHeight = this->height();
	this->resize(nWidth, nHeight);
	m_nWidth = nWidth;
	m_nHeight = nHeight;
	QWidget::resizeEvent(event);
}
