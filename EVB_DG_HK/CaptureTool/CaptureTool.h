#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_CaptureTool.h"
#include <qlabel.h>
#include <opencv.hpp>
#include <highgui.hpp>
#include <thread>
#include "FilePath.h"
#include "CaptureSet.h"
//#include "CameraDS.h"
#include "camera.hpp"
#include <condition_variable>
#include <qlabel.h>
#include "HCNetSDK.h"

#include <Windows.h>
//#include <qtimer.h>

#define VIDEOCOUNT    6   //屏幕显示分屏数
#define UVC_IMG_WIDTH		360/*720*/
#define UVC_IMG_HEIGHT		640/*1280*/

class CaptureTool : public QMainWindow
{
    Q_OBJECT

public:
    CaptureTool(QWidget *parent = Q_NULLPTR);
	~CaptureTool();

//protected:
//	bool eventFilter(QObject *watched, QEvent *event);

private:
    Ui::CaptureToolClass ui;
	void initForm();
	//int videoCount;
	//QList<QLabel *> widgets;
	bool videoMax;
	QMenu *videoMenu;
	QString videoType;    //屏幕分屏类型
	void initMenu();
	void show_video_all();
	void change_video_4(int index);
	void change_video_6(int index);
	void change_video_8(int index);
	void change_video_9(int index);
	void change_video_16(int index);
	void hide_video_all();
	void change_video(int index, int flag);
	cv::VideoCapture cap_rgb1;
	cv::VideoCapture cap_ir1;
	cv::VideoCapture cap_spk1;
	cv::VideoCapture cap_depth1;
	cv::Mat rgb_stream;
	cv::Mat ir_stream;
	cv::Mat spk_stream;
	cv::Mat depth_stream;
	std::thread *rgb1_thread;
	std::thread *ir1_thread;
	std::thread *depth1_thread;
	std::thread *spk1_thread;
	void show_rgb1_video();
	void show_ir1_video();
	void show_spk1_video();
	void show_depth1_video();
	bool stopPlay;
	FilePath *filePath;
	void bulk_depth();
	void runHist(uint16_t* src, int h, int w, int step);
	void scaleGray(uint16_t* gray, int num, int min, int max);
	void enhanceDepth(uint16_t* src, uint16_t* dst, int h, int w, int minDist, int maxDist, bool invert_white);
	void readBufferTo16RawStream(char* buffer);
	QString saveFileName;
	CaptureSet *capset;
	bool isCircleShoot;
	int delay_time_to_shoot;  //ms
	int shot_times;
	int record_times;
	void showAllStream();
	//QTimer *timer;
	//std::vector <uint8_t>all_stream;
	//std::vector <uint8_t>all_stream_1;
	//std::vector <uint8_t>all_stream_2;
	//CCameraDS cameraDs;
	Camera *camera;
	Camera *camera_2;
	std::thread *all_stream_thread;
	void irVideo();
	void rgbVideo();
	void depthVideo();
	void send_rec(QString path, QString send_info, QString sendOrRec);
	std::vector<unsigned char> yuyv;
	std::thread *rgb_video_thread;
	std::thread *ir_video_thread;
	std::thread *depth_video_thread;

	//抓图线程
	std::thread *cap_rgb_ir_spk_thread;
	void m_cap();   
	//抓图线程

	std::condition_variable con_ir;
	std::condition_variable con_rgb;
	std::condition_variable con_depth;

	std::mutex loc;

	QLabel *status;
	
	bool isCut;  //截取部分显示

	//海康
	LONG IUserID;                //NET_DVR_Login_V30的返回值
	LONG IRealPlayHandle;        //NET_DVR_RealPlay_V40的返回值

	void initCamera();       //初始化
	void connectCamera();    //连接
	void registerCamera();   //注册
	void startPreview();     //预览
	void stopPreview();      //停止预览
	void hkCapture();

	int multiple;   //放大缩小倍数

public:
	//evb
	std::vector <uint8_t>all_stream;   //ir
	std::vector <uint8_t>all_stream_1; //rgb
	std::vector <uint8_t>all_stream_2; //spk
	//dg(门禁)
	std::vector <uint8_t>all_stream_3; //ir
	std::vector <uint8_t>all_stream_4; //rgb
	//std::vector <uint8_t>all_stream_5; //spk
	void mainThread_show(QLabel *label, QPixmap pix);
	QList<QLabel *> widgets;
	std::vector<std::wstring>  cam_dev_name;
	std::vector<int> cam_dev_num;
	std::wstring dev_name_string;
	char *format_value;
private slots:
	void show_video_4();
	void show_video_6();
	void show_video_8();
	void show_video_9();
	void show_video_16();
	void snapshot_video_one();
	void playAllVideo();
	void showFileDialog();
	void cap_ir_spk_dep();
	void get_save_path(QString path);
	void start_rgb1_video_thread();
	void start_ir1_video_thread();
	void start_spk1_video_thread();
	void start_depth1_video_thread();
	void getUsbDev();
	void stop_stream();
	void open_capture_set_form();
	void shot_set(bool circle_shoot, int delay_time, int shoot_times);
	void format_set(char *value);
	void cap_rgb_ir_dep();
	void updateUI(int screen_index, QPixmap pixmap);
	void cutVideo();
	void biggerVideo();
	void smallerVideo();
	//void mainThread_show(QLabel *label, QPixmap pix);
	void cap_rgb_ir_spk();
signals:
	void ui_show(int screen_index, QPixmap pixmap);
	
};
