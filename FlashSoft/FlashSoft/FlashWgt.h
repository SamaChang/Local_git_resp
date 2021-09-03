#pragma once

#include <QWidget>
#include "ui_FlashWgt.h"

class SingleWgt;
class CheckAvailablePort;

class FlashWgt : public QWidget
{
	Q_OBJECT

	

public:
	FlashWgt(QWidget *parent = Q_NULLPTR);
	~FlashWgt();

public slots:
	void slot_available_port(QString strCom);
	void on_pushButton_1_clicked();		//选择文件
	void on_pushButton_2_clicked();		//检测可用串口
	void on_pushButton_3_clicked();		//烧写程序
	void slot_burn_finished();

private:
	bool loadFirstBin();

private:

	struct SINGLEWGT
	{
		SINGLEWGT()
		{
			pWgt = nullptr;
			bLoad = false;
		}
		SINGLEWGT(SingleWgt* pWidget, bool bFlag = false)
		{
			pWgt = pWidget;
			bLoad = bFlag;
		}
		SingleWgt* pWgt;
		bool bLoad;
	};

	Ui::FlashWgt ui;
	CheckAvailablePort* m_pCheckAvailablePort;

	QByteArray m_array_first_bin;
	QByteArray m_array_second_bin;
	int m_n_second_bin_length;
	QVector<SINGLEWGT> m_vec_p_singleWgt;
	
};
