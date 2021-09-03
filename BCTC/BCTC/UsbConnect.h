#pragma once
#include "packet.h"
class UsbConnect
{
public:
	UsbConnect();
public:
	int send_usb_data(uint8_t *packet, uint32_t len);
	int rec_usb_data(uint32_t id, uint8_t *send, uint8_t *recv);
	int get_ir_image(uint8_t *recv);
};

