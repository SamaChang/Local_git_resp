#include "MyComboBox.h"


MyComboBox::MyComboBox(QWidget *parent) :QComboBox(parent)
{

}

MyComboBox::~MyComboBox()
{

}

void MyComboBox::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		emit clicked();  //����clicked�ź�
	}
	QComboBox::mousePressEvent(event);  //�����¼��������ദ����仰����Ҫ�����û�У������޷��������ĵ���¼�
}
