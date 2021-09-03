#pragma once

#include <QtWidgets/QWidget>
#include "ui_BCTC.h"
#include "SerialPort.h"
#include "UsbConnect.h"
#include <qfiledialog.h>
#include <opencv.hpp>
#include <opencv2/highgui.hpp>
#include <memory>
#include "DevEvent.h"
class BCTC : public QWidget
{
    Q_OBJECT

enum
{
	PROSTHESIS = 0,
	ALIVE_FULL,
	ALIVE_FACE,
	ALL_ALIVE_IR,
	ALL_ALIVE_DEPTH
};

public:
    BCTC(QWidget *parent = Q_NULLPTR);
    ~BCTC();

private:
    Ui::BCTCClass ui;
	//void seri_cmd_send_data(/*SerialPort *serial*/);
	void usb_connect_data(std::vector<char> result,bool flag);
	std::vector<char> get_checkBox_result();
	std::vector<QString> files;
	void creatFilePath(QString fileName);
	void send_pic_serial();
	SerialPort *serial;
	QString current_file_name;
	void copyFile(QString path);
	void initSerialPortList();
	//std::unique_ptr<SerialPort> serial;
private slots:
	void on_pushButton_clicked();
	void on_pushButton_2_clicked();
	void on_pushButton_3_clicked();
	void on_pushButton_4_clicked();
	void on_pushButton_5_clicked();
	void usb_send_fun(bool flag);
	void write_file(unsigned char *data, short channel, ushort height, ushort width, int id);
	void save_check_pic_type(int id);
	void seri_cmd_send_data(/*SerialPort *serial*/);
	void update_port_list(QStringList list);
signals:
	void start_write_file(unsigned char *, short, ushort, ushort, int);
	void finished();
};
