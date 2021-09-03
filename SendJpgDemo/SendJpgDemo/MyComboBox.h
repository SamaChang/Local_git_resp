#pragma once
#include <qcombobox.h>
#include <QMouseEvent>
class MyComboBox :
	public QComboBox
{
	Q_OBJECT    //ֻ�м���Q_OBJECT������ʹ���ź�signal�Ͳ�slot�Ļ���

public:
	MyComboBox(QWidget *parent = 0);
	~MyComboBox();
protected:
	virtual void mousePressEvent(QMouseEvent *e);  //���������¼�

signals:
	void clicked();  //�Զ������źţ���mousePressEvent�¼�����ʱ����
};

