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
	//�����ﴴ�����ļ�д���ͷ
	QDir *DataFile = new QDir;    //�����ļ�·��������һ���ļ��У�
	bool exist = DataFile->exists("D:/LogFile");
	if (!exist)
	{
		bool isok = DataFile->mkdir("D:/LogFile"); // �½��ļ���
		if (!isok)
			QMessageBox::warning(nullptr, "sdf", "can't mkdir", QMessageBox::Ok);
	}
	//QString fileName = "D:/LogFile/"/* + time_str + */"log.txt";
	//QString SN = "SJ51AE20440001";
	//QString result = "PASS";
	QString fileName = "D:/LogFile/" + dateTimeFileName + "-" + snInf + ".csv";
	QFile file(fileName);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))    //����QIODevice::Append�Ͳ���֮ǰ�����ݣ����ǵ���������Ͼͼ�������д���̶�����ĸ�ʽ��Ӧ�ò���Append�˰ɣ����������ξʹ���������ͷ�ˣ�
	{
		QMessageBox::warning(nullptr, "sdf", "can't open", QMessageBox::Ok);
	}
	QTextStream stream(&file);
	//stream << time_str + "\t\t\t" + item + "\t\t" + isPass << "\n";
	stream << "SN:" << "," << snInf << "\n";
	stream << QString::fromLocal8Bit("���Խ��:") << "," << result << "\n";
	stream << QString::fromLocal8Bit("���") << "," << QString::fromLocal8Bit("����Ա") << "," << QString::fromLocal8Bit("����ʱ��") << "," << QString::fromLocal8Bit("������Ŀ")
		<< "," << QString::fromLocal8Bit("��λ") << "," << QString::fromLocal8Bit("��Сֵ") << "," << QString::fromLocal8Bit("���ֵ") << "," << QString::fromLocal8Bit("����ֵ")
		<< "," << QString::fromLocal8Bit("��������") << "," << QString::fromLocal8Bit("�������״̬") << "\n";
	QMessageBox::information(nullptr, QString::fromLocal8Bit("ͨ��"), QString::fromLocal8Bit("¼����Ϣ�ɹ���"), QMessageBox::Ok);
}
//¼����Ϣ
void SNInformation::on_pushButton_clicked()
{
	QString qStr = ui.textEdit->toPlainText();
	snInf = qStr;
	QDateTime da_time;
	QString time_str = da_time.currentDateTime().toString("yyyyMMddHHmmss");
	dateTimeFileName = time_str;

	csvFormat("PASS");

	////�����ﴴ�����ļ�д���ͷ
	//QDir *DataFile = new QDir;    //�����ļ�·��������һ���ļ��У�
	//bool exist = DataFile->exists("D:/LogFile");
	//if (!exist)
	//{
	//	bool isok = DataFile->mkdir("D:/LogFile"); // �½��ļ���
	//	if (!isok)
	//		QMessageBox::warning(nullptr, "sdf", "can't mkdir", QMessageBox::Ok);
	//}
	////QString fileName = "D:/LogFile/"/* + time_str + */"log.txt";
	////QString SN = "SJ51AE20440001";
	////QString result = "PASS";
	//QString fileName = "D:/LogFile/" + dateTimeFileName + "-" + qStr + ".csv";
	//QFile file(fileName);
	//if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))    //����QIODevice::Append�Ͳ���֮ǰ�����ݣ����ǵ���������Ͼͼ�������д���̶�����ĸ�ʽ��Ӧ�ò���Append�˰ɣ����������ξʹ���������ͷ�ˣ�
	//{
	//	QMessageBox::warning(nullptr, "sdf", "can't open", QMessageBox::Ok);
	//}
	//QTextStream stream(&file);
	////stream << time_str + "\t\t\t" + item + "\t\t" + isPass << "\n";
	//stream << "SN:" << "," << qStr << "\n";
	//stream << QString::fromLocal8Bit("���Խ��:") << ","/*<< "," << result*/ << "\n";
	//stream << QString::fromLocal8Bit("���") << "," << QString::fromLocal8Bit("����Ա") << "," << QString::fromLocal8Bit("����ʱ��") << "," << QString::fromLocal8Bit("������Ŀ")
	//	<< "," << QString::fromLocal8Bit("��λ") << "," << QString::fromLocal8Bit("��Сֵ") << "," << QString::fromLocal8Bit("���ֵ") << "," << QString::fromLocal8Bit("����ֵ")
	//	<< "," << QString::fromLocal8Bit("��������") << "," << QString::fromLocal8Bit("�������״̬") << "\n";
	//QMessageBox::information(nullptr, QString::fromLocal8Bit("ͨ��"), QString::fromLocal8Bit("¼����Ϣ�ɹ���"), QMessageBox::Ok);

}
//����
void SNInformation::on_pushButton_2_clicked()
{
	this->close();
	emit testForms();
}
