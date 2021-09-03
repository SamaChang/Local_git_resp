#include "pic_deal.h"
#include "packet.h"
#include "def.h"
#include "common.h"


static void pic_resize(cv::Mat &img, cv::Mat &img_resize, float scale)
{
	int srcH = img.rows * scale;
	int srcW = img.cols * scale;

	cv::resize(img, img_resize, cv::Size(srcW, srcH));
#ifdef PIC_DEBUG	
	cv::imshow("img", img);
	cv::imshow("img_resize", img_resize);
	cv::waitKey(0);
#endif

	return;
}

static void pic_mat2dat(cv::Mat &img, unsigned char *buf)
{
	int srcH = img.rows;
	int srcW = img.cols;
	int ch = img.channels();

	pic_payload_t *payload = (pic_payload_t *)buf;

	store_le_uint16(payload->ch, ch);																/*real size*/
	store_le_uint16(payload->height, srcH);
	store_le_uint16(payload->width, srcW);
	memcpy(payload->dat, img.data, srcH * srcW * ch);

	return;
}

static void pic_verify_image(uint8_t *buf)
{
	unsigned int channals, srcW, srcH;
	pic_payload_t *payload = (pic_payload_t *)buf;
	cv::Mat img = cv::Mat::zeros(PIC_HEIGHT, PIC_WIDTH, CV_8UC4);

	channals = GET_PIC_CHANNEL(payload);
	srcH = GET_PIC_HEIGHT(payload);
	srcW = GET_PIC_WIDTH(payload);
	memcpy(img.data, payload->dat, channals * srcH * srcW);
	cv::imshow("verify", img);
	cv::waitKey(0);

	return;
}


static void pic_covert(cv::Mat &img, cv::Mat &img_conv)
{
	cv::Mat img_resize;
	int srcH = img.rows;
	int srcW = img.cols;
	float scaleH = (float)PIC_HEIGHT / srcH;
	float scaleW = (float)PIC_WIDTH / srcW;
	float scale = scaleH < scaleW ? scaleH : scaleW;

	pic_resize(img, img_resize, scale);
	cv::Mat imgc4 = cv::Mat::zeros(img_resize.rows, img_resize.cols, CV_8UC4);
	cv::cvtColor(img_resize, imgc4, cv::COLOR_BGR2BGRA);
#ifdef PIC_DEBUG	
	cv::imshow("imgconv", imgc4);
	cv::waitKey(0);
#endif
	cv::Mat imageROI = img_conv(cv::Rect(0, 0, imgc4.cols, imgc4.rows));
	imgc4.copyTo(imageROI);
#ifdef PIC_DEBUG
	cv::imshow("imgfill", img_conv);
	cv::waitKey(0);
#endif
}

void pic_pack_payload(cv::Mat &img, uint8_t *buf)
{
	cv::Mat img_conv = cv::Mat::zeros(PIC_HEIGHT, PIC_WIDTH, CV_8UC4);
	pic_covert(img, img_conv);
#ifdef PIC_DEBUG
	cv::imshow("img_after_fill", img_conv);
	cv::waitKey(0);
#endif
	pic_mat2dat(img_conv, buf);
#ifdef PIC_DEBUG
	pic_verify_image(buf);
#endif
}
