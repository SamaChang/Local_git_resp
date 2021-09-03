#pragma once

#include <QWidget>
#include "ui_SingleUpgrade.h"
#include "UsbThread.h"
//#include <qthread.h>
//#include "UsbControl.h"

class SingleUpgrade : public QWidget
{
	Q_OBJECT

public:
	//SingleUpgrade(QWidget *parent = Q_NULLPTR);
	SingleUpgrade(QWidget *parent,int index);
	~SingleUpgrade();
	void run_handshake(int dev_num);
	void get_flash_addr(int addr, int run_add);
	void start_flash_load(int dev_num,int flash_addr, int len, bool check, int run_addr,  char *data_ptr);
	void reset_flash(int dev_num);
	void reset_color();
private:
	Ui::SingleUpgrade ui;
	UsbThread *m_usbThread;
	//QThread *m_thread;
	//UsbControl *usbControl;
public slots:
	void test(int i);
	void progress_value(int i);
	void handshake_status_change();
	void upgrade_status_change();
	void reset_status_change();
	void delete_statck();
	
	
signals:
	void sig_handshake(int dev_num);
	void sig_upgrade(int dev_num, int flash_addr,  int len, bool check, int run_addr,  char *data_ptr);
	void sig_reset(int dev_num);
};
