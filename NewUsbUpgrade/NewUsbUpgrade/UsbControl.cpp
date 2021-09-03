#include "UsbControl.h"

UsbControl::UsbControl(QObject *parent)
	: QObject(parent)
{
}

UsbControl::~UsbControl()
{
	dev_list.clear();
}

void UsbControl::get_dev()
{
	usb_init();
	int a = usb_find_busses();
	int b = usb_find_devices();


	struct usb_bus *bus;
	struct usb_device *dev;

	for (bus = usb_get_busses(); bus; bus = bus->next)
	{
		for (dev = bus->devices; dev; dev = dev->next)
		{
			if (dev->descriptor.idVendor == IDVendor
				&& dev->descriptor.idProduct == IDProduct)
			{
				dev_list.push_back(dev);
			}
		}
	}
}

//struct usb_dev_handle* usb_open_dev(void)
//{
//	usb_init();
//	usb_find_busses();
//	usb_find_devices();
//
//	return open_dev();
//}

int UsbControl::usb_config(struct usb_dev_handle* usb)
{
	if (usb_set_configuration(usb, MY_CONFIG) < 0)
		return ESETCFG;
	if (usb_claim_interface(usb, MY_INT) < 0)
		return ECLAIMINF;

	return SUCCESS;
}

//int UsbControl::usb_initial()
//{
//	usb = usb_open_dev();
//	if (!usb)
//		return EOPEN;
//	if (usb_config() < 0) {
//		usb_close(usb);
//		return ECONFIG;
//	}
//
//	return SUCCESS;
//}

int UsbControl::usb_initial(int num)
{
	//usb = usb_open_dev();
	//std::vector<struct usb_device *>dev_lists = dev_list;
	struct usb_dev_handle *usb = usb_open(dev_list[num]);

	if (!usb)
		return EOPEN;
	//if (usb_config() < 0) {
	//	usb_close(usb);
	//	return ECONFIG;
	//}

	if (usb_config(usb) < 0) {
		usb_close(usb);
		return ECONFIG;
	}
	//handle_lists.push_back(usb);
	usb_handle = usb;
	return SUCCESS;
}

int UsbControl::usb_write(char *dat, int size, int timeout/*, usb_dev_handle *usb*/)
{
	struct usb_dev_handle *usb = usb_handle;
	int ret = 0;

	if (!dat)
		return EPARAM;
	ret = usb_bulk_write(usb, EP_OUT, dat, size, timeout);  //发送端口是EP_OUT  0x02
	if (ret < 0 || ret != size)
		return EWRITE;
	else
		return SUCCESS;
}

int UsbControl::usb_read(char *dat, int size, int timeout/*, int num*/)
{
	struct usb_dev_handle *usb = usb_handle;
	int ret = 0;

	if (!dat)
		return EPARAM;
	ret = usb_bulk_read(usb, EP_IN, dat, size, timeout);   //读取端口是EP_IN     0x82
	if (ret < 0)
		return EREAD;
	else
		return ret;
}

int UsbControl::usb_release(/*int num*/)
{
	struct usb_dev_handle *usb = usb_handle;
	usb_release_interface(usb, MY_INT);
	if (usb)
		usb_close(usb);
	return SUCCESS;
}