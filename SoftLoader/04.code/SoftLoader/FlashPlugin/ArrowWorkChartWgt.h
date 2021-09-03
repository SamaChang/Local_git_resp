#pragma once

#include <QWidget>

class QPainter;

class ArrowWorkChartWgt : public QWidget
{
	Q_OBJECT

public:
	ArrowWorkChartWgt(QWidget *parent, QStringList strListTitles);
	ArrowWorkChartWgt(QWidget *parent = nullptr);
	~ArrowWorkChartWgt();

	void setTitles(QStringList strList);
	void initUI();		//初始化 状态
	void setStepStatus(int nStep, bool bFinished);

protected:
	void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
	void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;

private:
	void paintFirstStep(QPainter *painter, QColor bgColor, QColor txtColor= QColor(255,255,255));
	void paintMiddleStep(QPainter *painter, QColor bgColor, QColor txtColor = QColor(255, 255, 255));
	void paintLastStep(QPainter *painter, QColor bgColor, QColor txtColor = QColor(255, 255, 255));

private:
	int m_nCount;			//总共步数
	int m_nCurStep;
	int m_nSpace;			//步骤之间的间隙，必须为偶数
	int m_nBlock;
	int m_nSubWidth;
	int m_nWidth;
	int m_nHeight;
	QFont m_font;
	QStringList m_strList;
	QStringList m_strListColor;
	QVector<bool> m_vecStatus;
};
