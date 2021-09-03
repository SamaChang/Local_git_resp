#pragma once

#include "QAbstractDynamicLinesChart.h"

class QCustomPlot;

class QEQLinesChart : public QAbstractDynamicLinesChart
{
	Q_OBJECT

public:
	QEQLinesChart(QWidget *parent);
	~QEQLinesChart();

	virtual void initDraw(int nLineNum = 1) override;
	virtual void drawLine() override;

	void addData(int nPosLine, const QVector<double> &keys, const QVector<double> &values, const QVector<double> &keys_2, const QVector<double> &values_2, bool alreadySorted = true);

	void set_freq_point_change(int nIndex, int nVal);

	void set_freq_point_voice_xishu(double dVal);

private:
	void updatePosition();

public slots:
/*
	void plotMousePressEvent(QMouseEvent* event);
	void plotMouseReleaseEvent(QMouseEvent* event);
	void plotMouseMoveEvent(QMouseEvent* event);
*/

signals:
	void sig_freq_point_changed(int nIndex, int nVal);

private:
	QCustomPlot *m_pCustomPlot;
	QVector<double> m_vec_x;
	QVector<double> m_vec_y;
	int m_point;
	int m_nVoice_xishu;
	float m_dMoveDis;		//距离大于一个DB时发送
};
