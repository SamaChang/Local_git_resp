#pragma once

#include "usb.h"

typedef unsigned char       uint8_t;
typedef unsigned short      uint16_t;
typedef unsigned int        uint32_t;
typedef unsigned long long uint64_t;

typedef signed char         int8_t;
typedef signed short        int16_t;
typedef signed int          int32_t;




#define DEPTH_MAP_WIDTH			640
#define DEPTH_MAP_HEIGHT		360

//ͼ��IR
#define IR_WIDTH                1280
#define IR_HEIGHT               800
//ͼ��SPK
#define SPK_WIDTH               1280
#define SPK_HEIGHT              800
//ͼ��DEPTH
#define DEPTH_WIDTH             640   
#define DEPTH_HEIGHT            400
//ͼ��IRS2887C_TOF
#define IRS2887C_TOF_WIDTH		640
#define IRS2887C_TOF_HEIGHT		1205
//ͼ��S5K33D_TOF
#define S5K33D_TOF_WIDTH		1280
#define S5K33D_TOF_HEIGHT		962

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

#define SEL_ALL_IMGS			0x0
#define SEL_ALL_IMGS_SPK		0x1
#define SEL_IR_IMG				0x2
#define SEL_RGB_IMG				0x3
#define SEL_ALL_IMGS_SPK_DBG	0x4

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
#define BUF_RECV_IR_SPK_DEPTH            (5*1024*1024)                          /*5M*///ͼ����

#define BUF_SEND_BIN					(50*1024*1024)							/*USB����*/

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

//����
#define USB_UPGRADE_CONNECT_SEND_CMD	0x10    
#define USB_UPGRADE_CONNECT_ACK_CMD		0x30
//�����ܳ�����Ϣ
#define USB_UPGRADE_SEND_BIN_LEN_CMD	0x11
#define USB_UPGRADE_ACK_BIN_LEN_CMD		0x31
//���͹̼�
#define USB_UPGRADE_SEND_BIN_CMD		0x12	//����
#define USB_UPGRADE_ACK_BIN_OK_CMD		0x32    //�ɹ�����
//��ʼ��¼
#define USB_UPGRADE_PROGRAMMER_BIN_CMD	0x13    
#define USB_UPGRADE_PROGRAMMER_OK_CMD	0x33    //��¼�ɹ�
//��¼��ɣ�������¼��ʱ����и�λ
#define USB_UPGRADE_RESET_SEND_CMD		0x14    //���͸�λ
#define USB_UPGRADE_RESET_OK_CMD		0x34    //ִ�и�λ
#define CRC_LEN							0x04    //CRC����
#define DATA_LEN						0x08    //���ݳ���
#define ADDRESS							0x04    //��ַ����
#define HEAD_LEN						12    //ͷ��
#define PARA_LEN						12    //��������
#define BIN_HEAD_LENGTH					16    //ͷ��
#define ADD_LEN							16    //16B���볤��
#define DATA_PER_LEN					(FRAME_LEN-CRC_LEN-HEAD_LEN)   //bin����ʵ�ʳ���
#define FIXED_BURNING_SIZE				(64*1024)   //64K