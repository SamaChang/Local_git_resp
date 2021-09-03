#include "SNInformation.h"
#include "packet.h"
QString snInf;
QString dateTimeFileName;
SNInformation::SNInformation(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->setWindowFlags(Qt::WindowCloseButtonHint);
	this->setWindowIcon(QIcon("./Logo.png"));
	buttonStyle(ui.pushButton, "./Button_Small.qss");
	buttonStyle(ui.pushButton_2, "./Button_Small.qss");
}

SNInformation::~SNInformation()
{
}

void SNInformation::csvFormat(QString result)
{
	//在这里创建好文件写入表头
	QDir *DataFile = new QDir;    //创建文件路径（创建一个文件夹）
	bool exist = DataFile->exists("D:/LogFile");
	if (!exist)
	{
		bool isok = DataFile->mkdir("D:/LogFile"); // 新建文件夹
		if (!isok)
			QMessageBox::warning(nullptr, "sdf", "can't mkdir", QMessageBox::Ok);
	}
	//QString fileName = "D:/LogFile/"/* + time_str + */"log.txt";
	//QString SN = "SJ51AE20440001";
	//QString result = "PASS";
	QString fileName = "D:/LogFile/" + dateTimeFileName + "-" + snInf + ".csv";
	QFile file(fileName);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))    //不加QIODevice::Append就擦除之前的内容，覆盖掉，如果加上就继续往下写（固定不变的格式，应该不用Append了吧，如果误点两次就创建两个表头了）
	{
		QMessageBox::warning(nullptr, "sdf", "can't open", QMessageBox::Ok);
	}
	QTextStream stream(&file);
	//stream << time_str + "\t\t\t" + item + "\t\t" + isPass << "\n";
	stream << "SN:" << "," << snInf << "\n";
	stream << QString::fromLocal8Bit("测试结果:") << "," << result << "\n";
	stream << QString::fromLocal8Bit("序号") << "," << QString::fromLocal8Bit("测试员") << "," << QString::fromLocal8Bit("测试时间") << "," << QString::fromLocal8Bit("测试项目")
		<< "," << QString::fromLocal8Bit("单位") << "," << QString::fromLocal8Bit("最小值") << "," << QString::fromLocal8Bit("最大值") << "," << QString::fromLocal8Bit("测试值")
		<< "," << QString::fromLocal8Bit("不良现象") << "," << QString::fromLocal8Bit("单项测试状态") << "\n";
	QMessageBox::information(nullptr, QString::fromLocal8Bit("通过"), QString::fromLocal8Bit("录入信息成功！"), QMessageBox::Ok);
}
//录入信息
void SNInformation::on_pushButton_clicked()
{
	QString qStr = ui.textEdit->toPlainText();
	snInf = qStr;
	QDateTime da_time;
	QString time_str = da_time.currentDateTime().toString("yyyyMMddHHmmss");
	dateTimeFileName = time_str;

	csvFormat("PASS");

	////在这里创建好文件写入表头
	//QDir *DataFile = new QDir;    //创建文件路径（创建一个文件夹）
	//bool exist = DataFile->exists("D:/LogFile");
	//if (!exist)
	//{
	//	bool isok = DataFile->mkdir("D:/LogFile"); // 新建文件夹
	//	if (!isok)
	//		QMessageBox::warning(nullptr, "sdf", "can't mkdir", QMessageBox::Ok);
	//}
	////QString fileName = "D:/LogFile/"/* + time_str + */"log.txt";
	////QString SN = "SJ51AE20440001";
	////QString result = "PASS";
	//QString fileName = "D:/LogFile/" + dateTimeFileName + "-" + qStr + ".csv";
	//QFile file(fileName);
	//if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))    //不加QIODevice::Append就擦除之前的内容，覆盖掉，如果加上就继续往下写（固定不变的格式，应该不用Append了吧，如果误点两次就创建两个表头了）
	//{
	//	QMessageBox::warning(nullptr, "sdf", "can't open", QMessageBox::Ok);
	//}
	//QTextStream stream(&file);
	////stream << time_str + "\t\t\t" + item + "\t\t" + isPass << "\n";
	//stream << "SN:" << "," << qStr << "\n";
	//stream << QString::fromLocal8Bit("测试结果:") << ","/*<< "," << result*/ << "\n";
	//stream << QString::fromLocal8Bit("序号") << "," << QString::fromLocal8Bit("测试员") << "," << QString::fromLocal8Bit("测试时间") << "," << QString::fromLocal8Bit("测试项目")
	//	<< "," << QString::fromLocal8Bit("单位") << "," << QString::fromLocal8Bit("最小值") << "," << QString::fromLocal8Bit("最大值") << "," << QString::fromLocal8Bit("测试值")
	//	<< "," << QString::fromLocal8Bit("不良现象") << "," << QString::fromLocal8Bit("单项测试状态") << "\n";
	//QMessageBox::information(nullptr, QString::fromLocal8Bit("通过"), QString::fromLocal8Bit("录入信息成功！"), QMessageBox::Ok);

}
//返回
void SNInformation::on_pushButton_2_clicked()
{
	this->close();
	emit testForms();
}
