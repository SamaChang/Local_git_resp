#include "ConfItemPlugin.h"
#include "ConfItemWgt.h"

QWidget* ConfItemPlugin::createWidget(QWidget* parrent /* = nullptr */) 
{
	return new ConfItemWgt(parrent);
}

QString ConfItemPlugin::getPluginName()
{
	return QStringLiteral("≈‰÷√œÓ»Ìº˛");
}
