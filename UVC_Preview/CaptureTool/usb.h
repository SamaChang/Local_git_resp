#pragma once

#include "lusb0_usb.h"

#define IDVendor        0x04CC
#define IDProduct       0x0017
#define EP_OUT          0x02
#define EP_IN           0x82
#define MY_CONFIG		0x01
#define MY_INT          0x02
//#define FRAME_LEN       64 
#define FRAME_LEN       512 


#define SUCCESS          0 
#define EPARAM          -1 
#define ESETCFG         -2 
#define ECLAIMINF       -3 
#define EWRITE          -4 
#define EREAD           -5 
#define EOPEN           -6 
#define ECONFIG         -7 


int usb_initial(void);
int usb_write(char *dat, int size, int timeout);
int usb_read(char *dat, int size, int timeout);
int usb_release(void);

