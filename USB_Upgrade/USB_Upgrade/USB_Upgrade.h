#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_USB_Upgrade.h"
#include <thread>
#include <qsettings.h>

class USB_Upgrade : public QMainWindow
{
    Q_OBJECT

public:
    USB_Upgrade(QWidget *parent = Q_NULLPTR);
	~USB_Upgrade();
private:
    Ui::USB_UpgradeClass ui;
	void packet_connect_send();
	void selected_file();
	void send_packet();
	QByteArray fileData;
	int data_packet_send(uint8_t *packet, uint32_t len, char *data, uint8_t *recv);
	std::thread *current_thread;
	void startThread(/*uint8_t *packet, uint32_t len, char *data, uint8_t *recv*/);
	void test();
	void runCmd();
	void readIni();
	//int isX(QString str);
	inline int isX(QString str)
	{
		if (str.contains('x') || str.contains('X'))
			return 16;
		return 10;
	}
	
private slots:
	void on_pushButton_clicked();
	void on_pushButton_2_clicked();
	void on_pushButton_3_clicked();
	void on_pushButton_4_clicked();
	void on_pushButton_5_clicked();
	void progress_bar(int value);
	void log_msg(QString str);
signals:
	void sed_progress(int value);
	void sed_log_msg(QString str);
};
