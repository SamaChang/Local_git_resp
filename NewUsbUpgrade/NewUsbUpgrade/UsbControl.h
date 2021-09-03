#pragma once

#include <QObject>
#include "lusb0_usb.h"
#include <vector>

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
//static std::vector<struct usb_device *>dev_list;
class UsbControl : public QObject
{
	Q_OBJECT

public:
	UsbControl(QObject *parent=nullptr);
	~UsbControl();
	void get_dev();
	int usb_initial(int num);
	//int usb_initial();
	int usb_write(char *dat, int size, int timeout/*, usb_dev_handle *usb*/);
	int usb_read(char *dat, int size, int timeout/*, int num*/);
	int usb_release(/*int num*/);
	std::vector<struct usb_device *>dev_list;
	//std::vector<struct usb_dev_handle *>handle_lists;
	struct usb_dev_handle *usb_handle;

private:
	int usb_config(struct usb_dev_handle* usb);
};
