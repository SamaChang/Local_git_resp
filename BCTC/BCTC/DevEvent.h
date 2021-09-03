#pragma once
#include <qcombobox.h>
#include <qevent.h>
#include <qgroupbox.h>
#include <qserialport.h>
#include <qobject.h>
class DevEvent :
	public QComboBox
{
	Q_OBJECT
public:
	DevEvent(QWidget *parent = 0);
private:
	virtual void mousePressEvent(QMouseEvent *events);
signals:
	void sed_list(QStringList list);
};

