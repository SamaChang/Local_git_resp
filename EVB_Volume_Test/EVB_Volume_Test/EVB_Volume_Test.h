#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_EVB_Volume_Test.h"
#include <qserialport.h>
#include <qprogressbar.h>
#include <qfile.h>

class EVB_Volume_Test : public QMainWindow
{
    Q_OBJECT

public:
    EVB_Volume_Test(QWidget *parent = Q_NULLPTR);
	~EVB_Volume_Test();
signals:
	void finished();

private:
    Ui::EVB_Volume_TestClass ui;
	void load_config_file(QTableWidget *tb, QString path);
	void initSerialPort(QSerialPort *sp, QString name);
	QStringList getPortNameList();
	QStringList product_list;
	void sendData();
	QSerialPort *port_com;		//USI2(通信口)
	//QSerialPort *port_1;       //USI0
	//QSerialPort *port_2;		//UART805
	//QSerialPort *common_port;		//通用串口
	int serial_count;
	int zheng_count;
	QProgressBar *progressBar;
	void test();
	void test_serialport();
	void close_serialport(QSerialPort *sp);
	void buttonStyle(QPushButton *button);
	void lineEditStyle(QLineEdit *edit);
	void groubboxStyle(QGroupBox *box);
	void labelStyle(QLabel *label, QString text);
	void commboxStyle(QComboBox *box);
	QString SN;
	void writeCSV(QString SN, QString error);
	QString buttonName;
private slots:
	void on_pushButton_clicked();
	void on_pushButton_2_clicked();
	void on_pushButton_3_clicked();
	void on_pushButton_4_clicked();
	void on_pushButton_5_clicked();
	void on_pushButton_6_clicked();
	void readData();
	void serialConnect();
	void zhengTest(QStringList list,int row);
	void Product_test();
	void rec_adc();
};
