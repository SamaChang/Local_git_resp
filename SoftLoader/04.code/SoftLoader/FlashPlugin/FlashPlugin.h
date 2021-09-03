#pragma once

#include <QWidget>
#include <QtPlugin>

#include "../common/MyInterface.h"

#define PLUGIN_FLASH_IID "TSingmicro.PlatformOne.HC.Plugin.Flash.Interface"

class  FlashPlugin : public QObject, public MyInterface
{
	Q_OBJECT
#if QT_VERSION >= 0x050000
		Q_PLUGIN_METADATA(IID PLUGIN_FLASH_IID FILE "flash.json")
		Q_INTERFACES(MyInterface)
#endif
public:
	QWidget* createWidget(QWidget* parrent = nullptr);
	QString getPluginName();
};
