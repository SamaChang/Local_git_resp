#pragma once

#include <QWidget>

struct PluginStu
{
	int nID;							//插件ID
	QString pluginName;	//插件名称
	QString softName;		//软件名称
	bool bLoad;					//是否加载
};

namespace Ui { class SoftLoader; };

class SoftLoader : public QWidget
{
	Q_OBJECT

public:
	SoftLoader(QWidget *parent = Q_NULLPTR);
	~SoftLoader();

	void initStyle();		//初始化无边框窗体
	void initForm();		//初始化窗体数据

	bool readPluginConfig();
	int loadPlugins();
	bool loadPlugin(QString strPluginName);

protected:
	void resizeEvent(QResizeEvent *event);
	//void paintEvent(QPaintEvent *event);

	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);


private:
	QVector<PluginStu> m_vecPlugin;
private slots:
	void slot_btn();

	void slot_btn_mined();
	void slot_btn_normal();
	void slot_btn_close();
	void slot_btn_help();

private:
	Ui::SoftLoader *ui;
	QWidget* m_pWgt;
	QString m_strName;
	bool m_mousePressed;  //鼠标是否按下
	QPoint m_mousePoint;  //鼠标拖动自定义标题栏时的坐标
	QString m_strPdfFile;
};
