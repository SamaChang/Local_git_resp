#pragma once

#include <QDialog>
#include "ui_QConfLineColorDlg.h"
#include "Config.h"

class QConfLineColorDlg : public QDialog
{
	Q_OBJECT

public:
	QConfLineColorDlg(int nType, QWidget *parent = Q_NULLPTR);
	~QConfLineColorDlg();

private:  
	void initUIShow(const WAVE_LINE_VEC & vecConf);
	void loadData(int nIndex, QString strPath);
	void saveData(int nIndex, QString strPath);

public slots:
	void slot_btn_ok();
	void slot_btn_cancel();
	void slot_btn_default();

	void slot_tbtn_set_color();
	void slot_tbtn_load();
	void slot_tbtn_save();

private:
	Ui::QConfLineColorDlg ui;
	int m_nType;	
};
