#pragma once

#include <QWidget>

struct PluginStu
{
	int nID;							//���ID
	QString pluginName;	//�������
	QString softName;		//�������
	bool bLoad;					//�Ƿ����
};

namespace Ui { class SoftLoader; };

class SoftLoader : public QWidget
{
	Q_OBJECT

public:
	SoftLoader(QWidget *parent = Q_NULLPTR);
	~SoftLoader();

	void initStyle();		//��ʼ���ޱ߿���
	void initForm();		//��ʼ����������

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
	bool m_mousePressed;  //����Ƿ���
	QPoint m_mousePoint;  //����϶��Զ��������ʱ������
	QString m_strPdfFile;
};
