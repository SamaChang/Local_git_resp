#pragma once

#include "usb.h"

typedef unsigned char       uint8_t;
typedef unsigned short      uint16_t;
typedef unsigned int        uint32_t;

typedef signed char         int8_t;
typedef signed short        int16_t;
typedef signed int          int32_t;



#define DEPTH_MAP_WIDTH			640
#define DEPTH_MAP_HEIGHT		360

#define DEFAULT_IMG_RGB_CH		4
#define DEFAULT_IMG_IR_CH		1
#define DEFAULT_IMG_DEPTH_CH	1
#define DEFAULT_IMG_WIDTH		640
#define DEFAULT_IMG_HEIGHT		360

#define ALL_IMGS_DEPTH_CH		1
#define ALL_IMGS_IR_CH			1
#define ALL_IMGS_RGB_CH			4
#define ALL_IMGS_WIDTH			DEFAULT_IMG_WIDTH
#define ALL_IMGS_HEIGHT			DEFAULT_IMG_HEIGHT


#define RGB_IMG_CH				2
#define RGB_IMG_WIDTH			1920
#define RGB_IMG_HEIGHT			1080

#define IR_IMG_CH				1
#define IR_IMG_WIDTH			1280
#define IR_IMG_HEIGHT			720

//欧菲模式
#define IR_OFI_CH               1
#define IR_OFI_WIDTH            640
#define IR_OFI_HEIGHT           360

#define SPK_OFI_CH              1
#define SPK_OFI_WIDTH           640
#define SPK_OFI_HEIGHT          360

#define DEPTH_OFI_CH            2
#define DEPTH_OFI_WIDTH         640
#define DEPTH_OFI_HEIGHT        360

#define SEL_ALL_IMGS			0x0
#define SEL_ALL_IMGS_SPK		0x1
#define SEL_IR_IMG				0x2
#define SEL_RGB_IMG				0x3
#define SEL_ALL_IMGS_SPK_DBG	0x4
//欧菲模式选择
#define SEL_OFI_DEPTH           0x0+0x50
#define SEL_OFI_IR              0x1+0x50
#define SEL_OFI_SPK             0x2+0x50


#define SEL_AUTO_EXPO			0x0
#define SEL_MANUAL_EXPO_INDOOR	0x1
#define SEL_MANUAL_EXPO_OUTDOOR	0x2



#define BUF_RESERVE_LEN					(128 + FRAME_LEN)
#define DEPTH_MAP_LEN					(640 * 360 * 2)
#define IR_IMG_LEN						(640 * 360 * 1)
#define RGB_IMG_LEN						(640 * 360 * 4)
#define BUF_SEND_LEN					BUF_RESERVE_LEN
#define BUF_RECV_DEPTH_MAP_LEN			(DEPTH_MAP_LEN  + BUF_RESERVE_LEN) 
#define BUF_ALL_IMG_LEN					(DEPTH_MAP_LEN  + IR_IMG_LEN + RGB_IMG_LEN + BUF_RESERVE_LEN) 
#define BUF_RECV_LEN					(20 * 1024 * 1024)						/* 20M */ 
#define BUF_RECV_GAP_LEN				(1 * 1024 * 1024)						/* 1M */ 
#define BUF_RGB_RECV_GAP_LEN			(10 * 1024 * 1024)						/* 10M */ 

#define ROUND_DOWN_TIMES(x, align)          ((x) / (align))
#define ROUND_UP_TIMES(x, align)          (((x) + (align - 1)) / (align))
//#define PIC_DEBUG
//#define SORT_DEBUG
//#define TIME_DEBUG
//#define DEPTH_DEBUG
//#define IR_DEBUG
//#define IMG_AFFINE
//#define DEPTH_DEAL_DEBUG
//#define YUV_TO_PNG_DEBUG
#define DOUBLE_BASE		/* double base mode */
#define POINT_CLOUD_RECTIFY
//#define POINT_CLOUD_RECTIFY_DEBUG
#define POINT_CLOUD_THRED 295

#define SINGLE_SAVE_MODE		0
#define CONTINUOUS_SAVE_MODE	1

#define SPK_DBG_END_STR	"\x5a\x5a\x5a\x5a\x5a"
#define SPK_DBG_END_STR_LEN	5