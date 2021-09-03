#include "DevEvent.h"
#include <qserialportinfo.h>
DevEvent::DevEvent(QWidget *parent):QComboBox(parent)
{

}

void DevEvent::mousePressEvent(QMouseEvent *events)
{
	QStringList list;
	if (events->button()==Qt::LeftButton)
	{
		for(const QSerialPortInfo &info:QSerialPortInfo::availablePorts())
		{
			list << info.portName();
		}
	}
	emit sed_list(list);
	QComboBox::mousePressEvent(events);
}
