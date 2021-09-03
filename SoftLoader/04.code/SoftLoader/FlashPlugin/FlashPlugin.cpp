#include "FlashPlugin.h"
#include "FlashWgt.h"

QWidget* FlashPlugin::createWidget(QWidget* parrent /*= nullptr*/)
{
	return new FlashWgt(parrent);
}

QString FlashPlugin::getPluginName()
{
	return QStringLiteral("FLASH…’–¥π§æﬂ");
}
