#include "stdafx.h"
#include "usb.h"

static	struct usb_dev_handle* usb = NULL;

static usb_dev_handle *open_dev()
{
	struct usb_bus *bus;
	struct usb_device *dev;

	for (bus = usb_get_busses(); bus; bus = bus->next)
	{
		for (dev = bus->devices; dev; dev = dev->next)
		{
			if (dev->descriptor.idVendor == IDVendor
				&& dev->descriptor.idProduct == IDProduct)
			{
				return usb_open(dev);
			}
		}
	}
	return NULL;
}

static struct usb_dev_handle* usb_open_dev(void)
{	
	usb_init();
	usb_find_busses();
	usb_find_devices();

	return open_dev();
}	

static int usb_config(void)
{
	if (usb_set_configuration(usb, MY_CONFIG) < 0)
		return ESETCFG;
	if (usb_claim_interface(usb, MY_INT) < 0) 
		return ECLAIMINF;

	return SUCCESS;
}

int usb_initial(void)
{
	usb = usb_open_dev();
	if (!usb)
		return EOPEN;
	if (usb_config() < 0) {
		usb_close(usb);
		return ECONFIG;
	}

	return SUCCESS;
}

int usb_write(char *dat, int size, int timeout)	
{
	int ret = 0;

	if (!dat)
		return EPARAM;
	ret = usb_bulk_write(usb, EP_OUT, dat, size, timeout);  //发送端口是EP_OUT  0x02
	if (ret < 0 || ret != size)
		return EWRITE;
	else
		return SUCCESS;
}

int usb_read(char *dat, int size, int timeout)	
{
	int ret = 0;

	if (!dat)
		return EPARAM;
	ret = usb_bulk_read(usb, EP_IN, dat, size, timeout);   //读取端口是EP_IN     0x82
	if (ret < 0)
		return EREAD;
	else
		return ret;
}

int usb_release()
{
	usb_release_interface(usb, MY_INT);
	if (usb)
		usb_close(usb);
	return SUCCESS; 	
}
