#include "CutPicture.h"
#include <opencv2\opencv.hpp>
#include <highgui.hpp>
#include <qfiledialog.h>
#include <qmessagebox.h>

CutPicture::CutPicture(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
}

void CutPicture::on_pushButton_clicked()
{
	fileName = QFileDialog::getExistingDirectory(this, "choose src Directory",
		"/");
	QDir dir(fileName);
	//ui.textEdit_2->append(QString::fromLocal8Bit("��·����") + fileName);
	//QList<QFileInfo> *fileInfo = new QList<QFileInfo>(dir->entryInfoList(filter));
	qint32 count = dir.count();
	//for (int i = 0; i < count; i++)
	//{
	//	QString file_name = dir[i];  //�ļ�����
	//	filter.append(file_name); 
	//}
	//ui.textEdit_2->append(QString::fromLocal8Bit("�ļ�����") + count);
	for (int i = 0; i < count; i++)
	{
		QString file_name = dir[i];
		files.push_back(file_name);
		//ui.textEdit_2->append(QString::fromLocal8Bit("�ļ���:") + file_name);
	}
}

void CutPicture::on_pushButton_2_clicked()
{
	//ͨ��ROI��ʽ�ü�
	QString cutFilePath = "D:/CutPic";
	QDir* dir = new QDir();
	if (!dir->exists(cutFilePath)) {
		dir->mkpath(cutFilePath);
	}
	//�����ͼ��һ�����⣬�������������360*640�Ļ����������Բ��òü��ģ����������ķ�������С�󲹱�
	if (files.count() > 2)
	{
		for (int i = 2; i < files.count(); i++)
		{
			//std::string aa = std::string((const char *)files[i].toLocal8Bit().constData());
			std::string redStr = fileName.toStdString() + "/" + std::string((const char *)files[i].toLocal8Bit().constData());
			cv::Mat src = cv::imread(redStr);
			cv::Mat dst;
			//cv::imshow("Source", src);

			int width = src.rows;    //1440
			int height = src.cols;     //1080

			//���ͼƬ���ݸߵģ���640*360��ȣ�����ôҪ���Դ�������У�˵��width/640Ҫ��height/360Ҫ�󣬲�Ȼresize�󣬿��ܻ��360����640���޷�����
			if ((width / height) > (640 / 360))
			{
				cv::resize(src, dst, cv::Size(height / ((width / 640) + 1), width / ((width / 640) + 1))/*src.size() / 2*/, (0, 0), (0, 0), cv::INTER_LINEAR);
			}
			else
			{
				cv::resize(src, dst, cv::Size(height / ((height / 360) + 1), width / ((height / 360) + 1))/*src.size() / 2*/, (0, 0), (0, 0), cv::INTER_LINEAR);
			}

			int he = height / ((width / 640) + 1);
			int wi = width / ((width / 640) + 1);
			//����
			//cv::resize(src, dst, cv::Size(height / ((width / 640) + 1), width / ((width / 640) + 1))/*src.size() / 2*/, (0, 0), (0, 0), cv::INTER_LINEAR);
			//cv::imshow("Resize", dst);



			cv::Mat imageROI;
			cv::Mat image(640, 360, dst.type()/*CV_8UC1*//*, cv::Scalar(255, 255, 255)*/);//����һ����64����64�ĻҶ�ͼ��Mat����

			imageROI = image(cv::Rect(0, 0, dst.cols, dst.rows));
			dst.copyTo(imageROI);
			//cv::namedWindow("result");
			//cv::imshow("result", image);
			std::string saveStr = cutFilePath.toStdString() + "/" + std::string((const char *)files[i].toLocal8Bit().constData());
			cv::imwrite(saveStr, image);
		}
	}

	QMessageBox::information(nullptr, QString::fromLocal8Bit("�ü�"), QString::fromLocal8Bit("�ü���ɣ�"), QMessageBox::Ok);
}