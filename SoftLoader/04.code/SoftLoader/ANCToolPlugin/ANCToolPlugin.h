#pragma once

#include <QWidget>
#include <QtPlugin>

#include "../common/MyInterface.h"

#define PLUGIN_ANCTOOL_IID "TSingmicro.PlatformOne.HC.Plugin.ANCTool.Interface"


class  ANCToolPlugin : public QObject, public MyInterface
{
	Q_OBJECT
#if QT_VERSION >= 0x050000
		Q_PLUGIN_METADATA(IID PLUGIN_ANCTOOL_IID FILE "anctool.json")
		Q_INTERFACES(MyInterface)
#endif
public:
	QWidget* createWidget(QWidget* parrent = nullptr);
	QString getPluginName();
};
