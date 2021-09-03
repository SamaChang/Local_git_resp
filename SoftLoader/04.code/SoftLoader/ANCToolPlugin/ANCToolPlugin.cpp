#include "ANCToolPlugin.h"
#include "ANCSoft.h"

QWidget* ANCToolPlugin::createWidget(QWidget* parrent /*= nullptr*/)
{
	return new ANCSoft(parrent);
}

QString ANCToolPlugin::getPluginName()
{
	return QStringLiteral("ANCToolµ˜ ‘≈‰÷√π§æﬂ");
}
