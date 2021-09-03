#include "EVB_Volume_Test.h"
#include <qeventloop.h>
#include <qmessagebox.h>
#include <qtextstream.h>
#include <qtablewidget.h>
#include "packet.h"
#include <qprogressbar.h>
#include <qtimer.h>
#include <QtSerialPort/qserialportinfo.h>
#include <qdatetime.h>

EVB_Volume_Test::EVB_Volume_Test(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	port_com = nullptr;
	//load_config_file(ui.tableWidget);
	this->setWindowTitle("EVB_Test_V1.1");
	this->setWindowIcon(QIcon("./Logo.png"));
	ui.pushButton->setEnabled(false);
	//port_com = new QSerialPort();
	//port_1 = new QSerialPort();
	//port_2 = new QSerialPort();
	//initSerialPort();
	//connect(port_com, SIGNAL(readyRead()), this, SLOT(readData()));
	//connect(port_1, SIGNAL(readyRead()), this, SLOT(readData_1()));
	//connect(port_2, SIGNAL(readyRead()), this, SLOT(readData_2()));

	//this->setStyleSheet("background-color: rgb(100,100,100, 100)");
	//QPalette palette(this->palette());
	//palette.setColor(QPalette::Background, Qt::black);
	//this->setPalette(palette);
	ui.pushButton->setIcon(QIcon("./Serial.jpg"));
	ui.pushButton->setFlat(true);
	buttonStyle(ui.pushButton);
	buttonStyle(ui.pushButton_2);
	buttonStyle(ui.pushButton_3);
	buttonStyle(ui.pushButton_4);
	buttonStyle(ui.pushButton_5);
	buttonStyle(ui.pushButton_6);
	lineEditStyle(ui.lineEdit);
	commboxStyle(ui.comboBox);
	groubboxStyle(ui.groupBox);
	groubboxStyle(ui.groupBox_2);
	groubboxStyle(ui.groupBox_3);
	groubboxStyle(ui.groupBox_4);
	labelStyle(ui.label,QString::fromLocal8Bit("屏幕尺寸:"));
	labelStyle(ui.label_2,"SN:");
	ui.tableWidget->setStyleSheet("QHeaderView::section{font-size:14px;font-family:"";color:#FFFFFF;background:#60669B;border:none;text-align:left; min - height:49px; max - height:49px; margin - left:0px; padding - left:0px;}");
	ui.tableWidget->setStyleSheet("QTableWidget{background:#FFFFFF;border:none;font-size:12px;color:#666666;}");
	ui.tableWidget->setStyleSheet("QTableWidget::item{border-bottom:1px solid #EEF1F7 ;}");
	ui.tableWidget->setStyleSheet("QTableWidget::item::selected{color:red;background:#EFF4FF;}");
	QStringList itemList;
	itemList << QString::number(1.54) << QString::number(5.5);
	ui.comboBox->addItems(itemList);
}

EVB_Volume_Test::~EVB_Volume_Test()
{
	close_serialport(port_com);
	if (port_com != nullptr)
	{
		delete port_com;
		port_com = nullptr;
	}
}

void EVB_Volume_Test::close_serialport(QSerialPort *sp)
{
	if (port_com != nullptr)
	{
		if (sp->isOpen())
		{
			sp->clear();
			sp->close();
		}
	}
	
	//if (sp != nullptr)
	//{
	//	delete sp;
	//	sp = nullptr;
	//}
}

void EVB_Volume_Test::buttonStyle(QPushButton *button)
{
	QString path = "./Button.qss";
	if (path.isEmpty())
		return;
	QFile styleFile(path);
	styleFile.open(QFile::ReadOnly);
	QString setQSS(styleFile.readAll());
	button->setStyleSheet(setQSS);
}

void EVB_Volume_Test::lineEditStyle(QLineEdit *edit)
{
	QString path = "./LineEdit.qss";
	if (path.isEmpty())
		return;
	QFile styleFile(path);
	styleFile.open(QFile::ReadOnly);
	QString setQSS(styleFile.readAll());
	edit->setStyleSheet(setQSS);
}

void EVB_Volume_Test::groubboxStyle(QGroupBox *box)
{
	QString path = "./QGroupBox.qss";
	if (path.isEmpty())
		return;
	QFile styleFile(path);
	styleFile.open(QFile::ReadOnly);
	QString setQSS(styleFile.readAll());
	box->setStyleSheet(setQSS);
}

void EVB_Volume_Test::labelStyle(QLabel *label,QString text)
{
	QPalette pa;
	pa.setColor(QPalette::WindowText, Qt::black);
	label->setPalette(pa);
	QFont ft;
	ft.setPointSize(12);
	ft.setBold(true);
	label->setContentsMargins(0, 0, 0, 0);
	label->setFont(ft);
	label->setText(text);
}

void EVB_Volume_Test::commboxStyle(QComboBox *box)
{
	QString path = "./Commbox.qss";
	if (path.isEmpty())
		return;
	QFile styleFile(path);
	styleFile.open(QFile::ReadOnly);
	QString setQSS(styleFile.readAll());
	box->setStyleSheet(setQSS);
}

void EVB_Volume_Test::writeCSV(QString SN, QString error)
{
	QDateTime timer;
	QString recordTime = timer.currentDateTime().toString("yyyyMMddHHmmss");
	QString fileName = "./" + recordTime + "-" + SN + ".csv";
	QFile file(fileName);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))   //不加QIODevice::Append就擦除之前的内容，覆盖掉，如果加上就继续往下写
	{
		QMessageBox::warning(nullptr, "sdf", "can't open", QMessageBox::Ok);
		return;
	}
	QTextStream stream(&file);
	stream << SN << "," << error << "\n";
	file.close();
}

//串口握手发送接口
void EVB_Volume_Test::test_serialport()
{
	load_config_file(ui.tableWidget,"./Test_SerialPort.xls");
	serial_count = ui.tableWidget->rowCount();
	char send_remark_data[7] = { 0 };
	QStringList list = getPortNameList();
	//QEventLoop loop;
	//connect(this, SIGNAL(finished()), &loop, SLOT(quit()));
	if (!list.isEmpty())
	{
		for (int i = 0; i < list.count(); i++)
		{
			QSerialPort *serial = new QSerialPort();
			initSerialPort(serial, list.at(i));
			connect(serial, SIGNAL(readyRead()), this, SLOT(serialConnect()));
			QString str = ui.tableWidget->item(i, 1)->text();
			int cmd = str.toInt(nullptr, 16);
			QString str_remark = ui.tableWidget->item(i, 5)->text();
			int add_cmd = str_remark.toInt(nullptr, 16);
			char rem[1] = { (char)add_cmd };
			//progressBar = new QProgressBar();
			//progressBar->setStyleSheet("QProgressBar {border: 2px solid grey;   border-radius: 5px;"
			//	"background-color: #FFFFFF;"
			//	"text-align: center;}"
			//	"QProgressBar::chunk {background-color: rgb(0,250,0) ;}");
			//ui.tableWidget->setCellWidget(i, 2, progressBar);
			//progressBar->setValue(0);
			send_msg(send_remark_data, cmd, 0, cmd);
			memcpy(send_remark_data + 6, rem, 1);
			serial->write(send_remark_data, 7);
			//loop.exec();
			QEventLoop loop;
			QTimer::singleShot(100, &loop, SLOT(quit()));
			loop.exec();
			disconnect(serial, SIGNAL(readyRead()), this, SLOT(serialConnect()));   //串口全部解绑
		}
	}
	else
	{
		QMessageBox::warning(0, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("未检测到串口!"), QMessageBox::Ok);
	}
	//connect(port_com, SIGNAL(readyRead()), this, SLOT(readData()));
}
//可以灵活通过配置文件修改发送命令，但是涉及到不同命令使用不同串口发送，不适用
void EVB_Volume_Test::test()
{
	char send_data[6] = { 0 };
	char send_remark_data[7] = { 0 };
	int len = ui.tableWidget->rowCount();
	QEventLoop loop;
	connect(this, SIGNAL(finished()), &loop, SLOT(quit()));
	for (int i = 0; i < len; i++)
	{
		QString str = ui.tableWidget->item(i, 1)->text();
		if (str == "")
			continue;
		if (!ui.tableWidget->item(i, 5)->text().isEmpty())    //有备注的发送cmd都为0xF0+0x0D;ef aa f0 00 00 f0 0d
		{
			int cmd = str.toInt(nullptr, 16);
			QString str_remark = ui.tableWidget->item(i, 5)->text();
			int add_cmd = str_remark.toInt(nullptr, 16);
			char rem[1] = { (char)add_cmd };
			progressBar = new QProgressBar();
			progressBar->setStyleSheet("QProgressBar {border: 2px solid grey;   border-radius: 5px;"
				"background-color: #FFFFFF;"
				"text-align: center;}"
				"QProgressBar::chunk {background-color: rgb(0,250,0) ;}");
			ui.tableWidget->setCellWidget(i, 2, progressBar);
			progressBar->setValue(0);
			send_msg(send_remark_data, cmd, 0, cmd);
			memcpy(send_remark_data + 6, rem, 1);
			port_com->write(send_remark_data, 7);
			loop.exec();
			continue;
		}
		int cmd = str.toInt(nullptr, 16);

		progressBar = new QProgressBar();
		progressBar->setStyleSheet("QProgressBar {border: 2px solid grey;   border-radius: 5px;"
			"background-color: #FFFFFF;"
			"text-align: center;}"
			"QProgressBar::chunk {background-color: rgb(0,250,0) ;}");

		ui.tableWidget->setCellWidget(i, 2, progressBar);
		progressBar->setValue(0);

		send_msg(send_data, cmd, 0, cmd);
		port_com->write(send_data, 6);
		loop.exec();
	}
}

void EVB_Volume_Test::load_config_file(QTableWidget *tb,QString path)
{
	ui.tableWidget->clear();
	if (!path.isEmpty())
	{
		QFile file(path);
		if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		{
			QMessageBox msg;
			msg.setText(QString::fromLocal8Bit("打开文件失败!"));
			msg.exec();
		}
		else
		{
			//将文件数据导入表格
			int r_count = 0;        //统计文件的行数
			QStringList textList;   //记录文件中每一行的数据
			QTextStream in(&file);
			while (!in.atEnd())
			{
				QString line = in.readLine();
				textList.append(line);          //保存文件的数据
				r_count++;                      //记录文件的行数 前两行为表头
			}
			file.close();       //关闭文件
			if (!textList.isEmpty())
			{
				//QStringList listColHeader = textList.at(1).split("\t");
				QStringList listRowHeader = textList.at(0).split("\t");
				int c_count = listRowHeader.count();
				tb->clear();
				tb->setRowCount(r_count - 1);      //前两行是行列表头
				tb->setColumnCount(c_count/* - 1*/);   //最后一行是“\t"   如果代码写入文件的话会有\t,需要-1，手动创建文件写的话不需要-1.详见TestTry项目解释  
				tb->setHorizontalHeaderLabels(listRowHeader);
				//ui.tableWidget->setVerticalHeaderLabels(listColHeader);
				for (int row = 1; row < r_count; row++)
				{
					QStringList tmpList;
					tmpList = textList.at(row).split("\t");
#if 0
					/*QProgressBar **/progressBar = new QProgressBar();
					progressBar->setStyleSheet("QProgressBar {border: 2px solid grey;   border-radius: 5px;"
						"background-color: #FFFFFF;"
						"text-align: center;}"
						"QProgressBar::chunk {background-color: rgb(0,250,0) ;}");
					ui.tableWidget->setCellWidget(row - 1, 2, progressBar);
					progressBar->setValue(0);
#endif
					for (int col = 0; col < c_count; col++)
					{
						QTableWidgetItem *item = new QTableWidgetItem(tmpList.at(col));
						tb->setItem(row - 1, col, item);
					}
				}
				//QMessageBox::information(0, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("导入成功!"));
			}
		}
	}
	else
	{
		QMessageBox::warning(0, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("配置文件不存在!"), QMessageBox::Ok);
	}
}

QStringList EVB_Volume_Test::getPortNameList()
{
	QStringList m_serialPortName;
	foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
	{
		if (info.description() == "Silicon Labs CP210x USB to UART Bridge")
		{
			//if(info.portName() !="COM67")
			//	m_serialPortName << info.portName();
			m_serialPortName << info.portName();
		}
	}
	return m_serialPortName;
}

void EVB_Volume_Test::initSerialPort(QSerialPort *sp,QString name)
{
	sp->close();
	if (sp->isOpen())
	{
		sp->clear();
		sp->close();
	}
	sp->setPortName(name);
	if (!sp->open(QIODevice::ReadWrite))
	{
		QMessageBox::warning(0, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("串口打开失败或串口已被占用!"), QMessageBox::Ok);
		return;
	}
	sp->setBaudRate(QSerialPort::Baud115200, QSerialPort::AllDirections);//设置波特率和读写方向
	sp->setDataBits(QSerialPort::Data8);		//数据位为8位
	sp->setFlowControl(QSerialPort::NoFlowControl);//无流控制
	sp->setParity(QSerialPort::NoParity);	//无校验位
	sp->setStopBits(QSerialPort::OneStop); //一位停止位
}
//开始测试
void EVB_Volume_Test::on_pushButton_clicked()
{
	//int a = system("calc");
	ui.textEdit->append(QString::fromLocal8Bit("开始测试..."));
	ui.pushButton_2->setEnabled(false);
	ui.pushButton->setEnabled(false);
	connect(port_com, SIGNAL(readyRead()), this, SLOT(readData()));
	sendData();
	disconnect(port_com, SIGNAL(readyRead()), this, SLOT(readData()));    //防止整机测试点击button时会触发readData
	ui.pushButton_2->setEnabled(true);
	ui.pushButton->setEnabled(true);
	ui.textEdit->append(QString::fromLocal8Bit("测试完成！"));
}

void EVB_Volume_Test::sendData()
{
	char send_data[6] = { 0 };
	int len = ui.tableWidget->rowCount();
	QEventLoop loop;
	connect(this, SIGNAL(finished()), &loop, SLOT(quit()));
	for (int i = 0; i < len; i++)    //第一行写“板级测试”，非测试项
	{
		if (ui.tableWidget->item(i, 0)->text().contains(QString::fromLocal8Bit("整机测试")))
			break;

		progressBar = new QProgressBar();
		progressBar->setStyleSheet("QProgressBar {border: 2px solid grey;   border-radius: 5px;"
			"background-color: #FFFFFF;"
			"text-align: center;}"
			"QProgressBar::chunk {background-color: rgb(0,250,0) ;}");

		ui.tableWidget->setCellWidget(i, 2, progressBar);
		progressBar->setValue(0);

		QString str = ui.tableWidget->item(i, 1)->text();
		int cmd = str.toInt(nullptr, 16);
		send_msg(send_data, cmd, 0, cmd);
		port_com->write(send_data, 6);
		loop.exec();
	}
	ui.pushButton->setEnabled(true);
}

void EVB_Volume_Test::readData()
{
	QByteArray rec;
	rec.append(port_com->readAll());
	char compare[5] = { 0xef,0xaa,0x01,0x00,0x55 };
	int len = rec.length();
	int id = 0;
	for (int i = 0; i < len; i++)
	{
		if (rec.at(i) == compare[0] && i < len - 5)
		{
			if (rec.at(i + 1) == compare[1])
			{
				unsigned char size[2] = { rec.at(i + 3),rec.at(i + 4) };
				ushort Size = reverse_uint16(size);
				if (i + 5 + Size < len)
				{
					char checkSum = std::accumulate(rec.data() + i + 2, rec.data() + i + 5 + Size, 0);
					if (rec.at(i + 5 + Size) == checkSum)
					{
						char cmd = rec.at(i + 2);
						for (int j = 0; j < ui.tableWidget->rowCount(); j++)
						{
							//if (ui.tableWidget->item(j, 1)->text().isEmpty())
							//	continue;
							QString strCmd = ui.tableWidget->item(j, 1)->text();
							int cmd_16 = strCmd.toInt(nullptr, 16);
							if (cmd == (char)cmd_16)
							{
								id = j;
								break;
							}
						}
						if (rec.at(i + 5) == compare[1])
						{
							progressBar->setValue(100);
							ui.tableWidget->setItem(id, 3, new QTableWidgetItem(QIcon("./Success.jpg"), QString::fromLocal8Bit("成功"))); 
							emit finished();
							break;
						}
						if (rec.at(i + 5) == compare[4])
						{
							progressBar->setStyleSheet("QProgressBar {border: 2px solid grey;   border-radius: 5px;"
								"background-color: #FFFFFF;"
								"text-align: center;}"
								"QProgressBar::chunk {background-color: rgb(255,0,0) ;}");
							progressBar->setValue(100);
							ui.tableWidget->setItem(id, 3, new QTableWidgetItem(QIcon("./Fail.jpg"), QString::fromLocal8Bit("失败")));
							emit finished();
							writeCSV(ui.lineEdit->text(), ui.tableWidget->item(id, 0)->text());
							break;
						}
					}
				}
			}
		}
	}
}

void EVB_Volume_Test::zhengTest(QStringList list,int row)
{
	QStringList tmpList= list.at(row).split("\t");
	QPushButton *pushButton = new QPushButton();
	pushButton->setObjectName(tmpList.at(0));
	connect(pushButton, SIGNAL(clicked()), this, SLOT(Product_test()));
	pushButton->setText(tmpList.at(0));
	ui.tableWidget->setCellWidget(row - 1, 0, pushButton);
}

void EVB_Volume_Test::Product_test()
{
	char send_data[6] = { 0 };
	QObject *obj = QObject::sender();
	QPushButton *button = qobject_cast<QPushButton *>(obj);
	QString button_name = button->text();
	buttonName = button_name;
	int all_len = product_list.count();
	QStringList tmpList;
	//QEventLoop loop;
	//connect(this, SIGNAL(finished()), &loop, SLOT(quit()));
	for (int i = zheng_count; i < all_len; i++)
	{
		tmpList = product_list.at(i).split("\t");
		if (button_name == tmpList.at(0))
		{
			QString str_cmd = tmpList.at(1);
			int cmd = str_cmd.toInt(nullptr, 16);
			send_msg(send_data, cmd, 0, cmd);
			if (tmpList.at(0) == "ADC")    //测试项ADC需要收到回复，是自检而不是主观判断
			{
				connect(port_com, SIGNAL(readyRead()), this, SLOT(rec_adc()));
				progressBar = new QProgressBar();
				progressBar->setStyleSheet("QProgressBar {border: 2px solid grey;   border-radius: 5px;"
					"background-color: #FFFFFF;"
					"text-align: center;}"
					"QProgressBar::chunk {background-color: rgb(0,250,0) ;}");

				ui.tableWidget->setCellWidget(zheng_count - 1, 2, progressBar);
				progressBar->setValue(0);
			}
				
			port_com->write(send_data, 6);
		}
	}
}
//ADC测试需要回环测试，ADC需放在配置文件整机测试的第一个
void EVB_Volume_Test::rec_adc()
{
	QByteArray rec;
	rec.append(port_com->readAll());
	char compare[5] = { 0xef,0xaa,0x01,0x00,0x55 };
	int len = rec.length();
	int id = 0;
	for (int i = 0; i < len; i++)
	{
		if (rec.at(i) == compare[0] && i < len - 5)
		{
			if (rec.at(i + 1) == compare[1])
			{
				unsigned char size[2] = { rec.at(i + 3),rec.at(i + 4) };
				ushort Size = reverse_uint16(size);
				if (i + 5 + Size < len)
				{
					char checkSum = std::accumulate(rec.data() + i + 2, rec.data() + i + 5 + Size, 0);
					if (rec.at(i + 5 + Size) == checkSum)
					{
						char cmd = rec.at(i + 2);
						if (rec.at(i + 5) == compare[1])
						{
							progressBar->setValue(100);
							ui.tableWidget->setItem(zheng_count - 1, 3, new QTableWidgetItem(QIcon("./Success.jpg"), QString::fromLocal8Bit("成功")));
							disconnect(port_com, SIGNAL(readyRead()), this, SLOT(rec_adc()));
							//emit finished();
							break;
						}
						if (rec.at(i + 5) == compare[4])
						{
							progressBar->setStyleSheet("QProgressBar {border: 2px solid grey;   border-radius: 5px;"
								"background-color: #FFFFFF;"
								"text-align: center;}"
								"QProgressBar::chunk {background-color: rgb(255,0,0) ;}");
							progressBar->setValue(100);
							ui.tableWidget->setItem(zheng_count - 1, 3, new QTableWidgetItem(QIcon("./Fail.jpg"), QString::fromLocal8Bit("失败")));
							disconnect(port_com, SIGNAL(readyRead()), this, SLOT(rec_adc()));
							//emit finished();
							break;
						}
					}
				}
			}
		}
	}
}
//连接串口(必须要有，每次换板子先点这里，放构造函数只能执行一次)
void EVB_Volume_Test::on_pushButton_2_clicked()
{
	ui.textEdit->append(QString::fromLocal8Bit("连接串口..."));
	ui.pushButton->setEnabled(false);
	test_serialport();
	ui.textEdit->append(QString::fromLocal8Bit("串口测试完成..."));
}
//板级测试
void EVB_Volume_Test::on_pushButton_3_clicked()
{
	ui.textEdit->append(QString::fromLocal8Bit("板级测试"));
	//connect(port_com, SIGNAL(readyRead()), this, SLOT(readData()));
	//ui.pushButton_3->setEnabled(false);
	//ui.pushButton_4->setEnabled(false);
	ui.pushButton_2->setEnabled(false);
	load_config_file(ui.tableWidget, "./ban_test.xls");
	ui.pushButton->setEnabled(true);
	//sendData();
}
//整机测试
void EVB_Volume_Test::on_pushButton_4_clicked()
{
	ui.textEdit->append(QString::fromLocal8Bit("整机测试"));
	//connect(port_com, SIGNAL(readyRead()), this, SLOT(readData()));
	//ui.pushButton->setEnabled(false);
	//ui.pushButton_2->setEnabled(false);
	//ui.pushButton_3->setEnabled(false);
	int zheng_case = 0;
	ui.tableWidget->clear();
	QString path;
	if (ui.comboBox->currentIndex() == 0)
		path = "./Test_1.54.xls";
	if (ui.comboBox->currentIndex() == 1)
		path = "./Test_5.5.xls";
	if (!path.isEmpty())
	{
		QFile file(path);
		if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		{
			QMessageBox msg;
			msg.setText(QString::fromLocal8Bit("打开文件失败!"));
			msg.exec();
		}
		else
		{
			//将文件数据导入表格
			int r_count = 0;        //统计文件的行数
			QStringList textList;   //记录文件中每一行的数据
			QTextStream in(&file);
			while (!in.atEnd())
			{
				QString line = in.readLine();
				textList.append(line);          //保存文件的数据
				product_list.append(line);
				r_count++;                      //记录文件的行数 前两行为表头
			}
			file.close();       //关闭文件
			if (!textList.isEmpty())
			{
				QStringList listRowHeader = textList.at(0).split("\t");
				int c_count = listRowHeader.count();
				ui.tableWidget->clear();
				ui.tableWidget->setRowCount(r_count - 1);      //前两行是行列表头
				ui.tableWidget->setColumnCount(c_count/* - 1*/);   //最后一行是“\t"   如果代码写入文件的话会有\t,需要-1，手动创建文件写的话不需要-1.详见TestTry项目解释  
				ui.tableWidget->setHorizontalHeaderLabels(listRowHeader);
				for (int row = 1; row < r_count; row++)
				{
					QStringList tmpList;
					tmpList = textList.at(row).split("\t");
					QString str = tmpList.at(0);
					if (str == QString::fromLocal8Bit("整机测试"))
					{
						zheng_count = row + 1;
						QTableWidgetItem *item = new QTableWidgetItem(tmpList.at(0));
						ui.tableWidget->setItem(row - 1, 0, item);
						for (int i = row+1; i < r_count; i++)
						{
							zhengTest(textList, i);
							tmpList = textList.at(i).split("\t");
							QTableWidgetItem *item = new QTableWidgetItem(tmpList.at(1));
							ui.tableWidget->setItem(i - 1, 1, item);
						}
						break;
					}
					for (int col = 0; col < c_count; col++)
					{
						QTableWidgetItem *item = new QTableWidgetItem(tmpList.at(col));
						ui.tableWidget->setItem(row - 1, col, item);
					}
				}
			}
		}
	}
	else
	{
		QMessageBox::warning(0, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("配置文件不存在!"), QMessageBox::Ok);
	}
	ui.pushButton->setEnabled(true);
}

//串口握手接收接口
void EVB_Volume_Test::serialConnect()
{
	QObject *obj = QObject::sender();
	QSerialPort *sp= qobject_cast<QSerialPort *>(obj);
	QByteArray rec;
	rec.append(sp->readAll());
	char compare[5] = { 0xef,0xaa,0x01,0x00,0x55 };
	int len = rec.length();
	int id = 0;
	for (int i = 0; i < len; i++)
	{
		if (rec.at(i) == compare[0] && i < len - 5)
		{
			if (rec.at(i + 1) == compare[1])
			{
				unsigned char size[2] = { rec.at(i + 3),rec.at(i + 4) };
				ushort Size = reverse_uint16(size);
				if (i + 5 + Size < len)
				{
					char checkSum = std::accumulate(rec.data() + i + 2, rec.data() + i + 5 + Size, 0);
					if (rec.at(i + 5 + Size) == checkSum)
					{
						char cmd_rec = rec.at(i + 2);
						for (int j = 0; j < serial_count; j++)
						{
							QString strCmd = ui.tableWidget->item(j, 4)->text();
							int cmd_16 = strCmd.toInt(nullptr, 16);
							if (cmd_rec == (char)cmd_16)
							{
								id = j;
								break;
							}
						}
						QString strConnectCmd = ui.tableWidget->item(0, 4)->text();  //通讯串口都放在配置文件第一个
						int cmd_connect = strConnectCmd.toInt(nullptr, 16);
						if (cmd_rec == (char)cmd_connect)
						{
							port_com = sp;
							progressBar = new QProgressBar();
							progressBar->setStyleSheet("QProgressBar {border: 2px solid grey;   border-radius: 5px;"
								"background-color: #FFFFFF;"
								"text-align: center;}"
								"QProgressBar::chunk {background-color: rgb(0,250,0) ;}");
							ui.tableWidget->setCellWidget(0, 2, progressBar);
							progressBar->setValue(100);
							ui.tableWidget->setItem(0, 3, new QTableWidgetItem(QIcon("./Success.jpg"), QString::fromLocal8Bit("成功")));
							emit finished();
							//disconnect(sp,SIGNAL(readyRead()),this,SLOT(serialConnect()));
							break;
						}
						if (serial_count > 1)
						{
							for (int j = 1; j < serial_count; j++)
							{
								QString strCmd = ui.tableWidget->item(j, 4)->text();
								int cmd_16 = strCmd.toInt(nullptr, 16);
								if (cmd_rec == (char)cmd_16)
								{
									if (rec.at(i + 5) == compare[1])
									{
										progressBar = new QProgressBar();
										progressBar->setStyleSheet("QProgressBar {border: 2px solid grey;   border-radius: 5px;"
											"background-color: #FFFFFF;"
											"text-align: center;}"
											"QProgressBar::chunk {background-color: rgb(0,250,0) ;}");
										ui.tableWidget->setCellWidget(id, 2, progressBar);
										progressBar->setValue(100);
										ui.tableWidget->setItem(id, 3, new QTableWidgetItem(QIcon("./Success.jpg"), QString::fromLocal8Bit("成功")));
										emit finished();
									}
									if (rec.at(i + 5) == compare[4])
									{
										progressBar = new QProgressBar();
										progressBar->setStyleSheet("QProgressBar {border: 2px solid grey;   border-radius: 5px;"
											"background-color: #FFFFFF;"
											"text-align: center;}"
											"QProgressBar::chunk {background-color: rgb(255,0,0) ;}");
										progressBar->setValue(100);
										ui.tableWidget->setItem(id, 3, new QTableWidgetItem(QIcon("./Fail.jpg"), QString::fromLocal8Bit("失败")));
										emit finished();
									}
								}
							}
						}
					}
				}
			}
		}
	}
}
//通过
void EVB_Volume_Test::on_pushButton_5_clicked()
{
	QMessageBox::information(nullptr, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("测试通过！"), QMessageBox::Ok);
}
//失败
void EVB_Volume_Test::on_pushButton_6_clicked()
{
	QString sn = ui.lineEdit->text();
	writeCSV(sn, buttonName);
	QMessageBox::warning(nullptr, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("测试失败！"), QMessageBox::Ok);
}