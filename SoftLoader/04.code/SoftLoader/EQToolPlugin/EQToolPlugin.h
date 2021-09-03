#pragma once

#include <QWidget>
#include <QtPlugin>

#include "../common/MyInterface.h"

#define PLUGIN_EQTOOL_IID "TSingmicro.PlatformOne.HC.Plugin.EQTool.Interface"

class EQToolPlugin : public QObject, public MyInterface
{
	Q_OBJECT
#if QT_VERSION >= 0x050000
		Q_PLUGIN_METADATA(IID PLUGIN_EQTOOL_IID FILE "eqtool.json")
		Q_INTERFACES(MyInterface)
#endif
public:
	QWidget* createWidget(QWidget* parrent = nullptr);
	QString getPluginName();
};
