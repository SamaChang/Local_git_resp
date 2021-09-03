#pragma once

#include "usb.h"

typedef unsigned char       uint8_t;
typedef unsigned short      uint16_t;
typedef unsigned int        uint32_t;

typedef signed char         int8_t;
typedef signed short        int16_t;
typedef signed int          int32_t;

#define BUF_RESERVE_SPACE   128
#define BUF_RECV_SPACE		(FRAME_LEN + BUF_RESERVE_SPACE) 
#define ROUND_DOWN_TIMES(x, align)          ((x) / (align))

//#define PIC_DEBUG
//#define SORT_DEBUG
//#define TIME_DEBUG
