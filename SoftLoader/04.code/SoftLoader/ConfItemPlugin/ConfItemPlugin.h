#pragma once

#include <QWidget>
#include <QtPlugin>

#include "../common/MyInterface.h"

#define PLUGIN_CONFITEM_IID "TSingmicro.PlatformOne.HC.Plugin.ConfItem.Interface"

class ConfItemPlugin : public QObject, public MyInterface
{
	Q_OBJECT
#if QT_VERSION >= 0x050000
		Q_PLUGIN_METADATA(IID PLUGIN_CONFITEM_IID FILE "confitemplugin.json")
		Q_INTERFACES(MyInterface)
#endif

public:
	QWidget* createWidget(QWidget* parrent  = nullptr ) Q_DECL_OVERRIDE;
	QString getPluginName() Q_DECL_OVERRIDE;

};
