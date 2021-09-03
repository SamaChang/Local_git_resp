#pragma once

#include<opencv2\opencv.hpp>
#include "def.h"

#define PIC_CHANNELS	4
#define PIC_WIDTH		320
#define PIC_HEIGHT		180
// #define PIC_WIDTH		640
// #define PIC_HEIGHT		360


void pic_pack_payload(cv::Mat &img, uint8_t *buf);
