#include "FilePath.h"
#include <qmessagebox.h>

FilePath::FilePath(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
}

FilePath::~FilePath()
{
}
//Root Directory
void FilePath::on_pushButton_clicked()
{
	root_path = QFileDialog::getExistingDirectory(this, "choose source directory", "/");
	ui.lineEdit->setText(root_path);
	
}

//Creat Second File
void FilePath::on_pushButton_2_clicked()
{
	QString creatFile = ui.lineEdit_2->text();
	root_path = root_path + "/" + creatFile;
	QDir dir;
	bool exist = dir.exists(root_path);
	if (exist)
		QMessageBox::warning(this, "CreatDir", "Dir is already existed!");
	else
	{
		bool ok = dir.mkdir(root_path);
		if (ok)
			QMessageBox::information(this, "CreatDir", "Creat Dir Success!");
		else
			QMessageBox::warning(this, "CreatDir", "Creat Dir Fail!");
	}
	emit send_path(root_path);
}

//OK
void FilePath::on_pushButton_3_clicked()
{

}

//Cancel
void FilePath::on_pushButton_4_clicked()
{

}