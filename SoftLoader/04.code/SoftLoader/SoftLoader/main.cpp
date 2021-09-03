#include "SoftLoader.h"
#include <QtWidgets/QApplication>
#include <QTextCodec>
#include <QFile>
#include <QMessageBox>

bool getQssFile(QString & strQss)
{
	QString strPath = QApplication::applicationDirPath();
	strPath += QString("/config/style.sty");
	QFile file(strPath);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QMessageBox::information(nullptr, QStringLiteral("提示"), QStringLiteral("加载美化配置文件失败！！！"), QMessageBox::Yes);
		return false;
	}
	strQss = file.readAll();
	return true;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

	QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB2312"));

	QString strQSS;
	bool bLoad = getQssFile(strQSS);
	if (bLoad)
	{
		a.setStyleSheet(strQSS);
	}

	SoftLoader w;
	w.show();
    return a.exec();
}
