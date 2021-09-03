#pragma once

#include <QWidget>

class RingsProgressBar : public QWidget
{
	Q_OBJECT

public:
	RingsProgressBar(QWidget *parent = nullptr);
	~RingsProgressBar();
	void setRotateDelta(int delta);
	void setPersent(int nPersent);
	void setTitle(QString strTitle);

	void init();

protected:
	void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
	void resizeEvent(QResizeEvent *event);
private:
	int m_nRotateAngle;		//��ת�Ƕ�
	int m_nPersent;				//�ٷֱ�
	int m_nBorder;
	QString m_strTitle;
	int m_nWidth;
	int m_nHeight;
};
