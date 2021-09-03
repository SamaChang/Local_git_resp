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
	//ui.textEdit_2->append(QString::fromLocal8Bit("打开路径：") + fileName);
	//QList<QFileInfo> *fileInfo = new QList<QFileInfo>(dir->entryInfoList(filter));
	qint32 count = dir.count();
	//for (int i = 0; i < count; i++)
	//{
	//	QString file_name = dir[i];  //文件名称
	//	filter.append(file_name); 
	//}
	//ui.textEdit_2->append(QString::fromLocal8Bit("文件数：") + count);
	for (int i = 0; i < count; i++)
	{
		QString file_name = dir[i];
		files.push_back(file_name);
		//ui.textEdit_2->append(QString::fromLocal8Bit("文件名:") + file_name);
	}
}

void CutPicture::on_pushButton_2_clicked()
{
	//通过ROI方式裁剪
	QString cutFilePath = "D:/CutPic";
	QDir* dir = new QDir();
	if (!dir->exists(cutFilePath)) {
		dir->mkpath(cutFilePath);
	}
	//下面裁图有一个问题，就是如果正好是360*640的话，本来可以不用裁剪的，但是这样的方法会缩小后补边
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

			//如果图片是瘦高的（与640*360相比），那么要除以大的数才行，说明width/640要比height/360要大，不然resize后，可能会比360或者640大，无法补充
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
			//缩放
			//cv::resize(src, dst, cv::Size(height / ((width / 640) + 1), width / ((width / 640) + 1))/*src.size() / 2*/, (0, 0), (0, 0), cv::INTER_LINEAR);
			//cv::imshow("Resize", dst);



			cv::Mat imageROI;
			cv::Mat image(640, 360, dst.type()/*CV_8UC1*//*, cv::Scalar(255, 255, 255)*/);//创建一个高64，宽64的灰度图的Mat对象

			imageROI = image(cv::Rect(0, 0, dst.cols, dst.rows));
			dst.copyTo(imageROI);
			//cv::namedWindow("result");
			//cv::imshow("result", image);
			std::string saveStr = cutFilePath.toStdString() + "/" + std::string((const char *)files[i].toLocal8Bit().constData());
			cv::imwrite(saveStr, image);
		}
	}

	QMessageBox::information(nullptr, QString::fromLocal8Bit("裁剪"), QString::fromLocal8Bit("裁剪完成！"), QMessageBox::Ok);
}