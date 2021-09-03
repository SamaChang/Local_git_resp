#include "EQToolPlugin.h"
#include "EQTools.h"

QWidget* EQToolPlugin::createWidget(QWidget* parrent /*= nullptr*/)
{
	return new EQTools(parrent);
}

QString EQToolPlugin::getPluginName()
{
	return QStringLiteral("EQTools≈‰÷√π§æﬂ");
}
