#pragma once

#include <QWidget>

#define PLUGIN_IID "TSingmicro.PlatformOne.HC.Plugin"

class MyInterface {
public:
	virtual QWidget* createWidget(QWidget* parrent = nullptr) = 0;
	virtual QString getPluginName() = 0;
};

Q_DECLARE_INTERFACE(MyInterface, PLUGIN_IID)