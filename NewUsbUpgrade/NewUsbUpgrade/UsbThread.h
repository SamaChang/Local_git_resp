#pragma once

#include <QObject>
#include "UsbControl.h"
#include "def.h"
#include <qthread.h>
#include "Common.h"

class UsbThread : public QObject
{
	Q_OBJECT

public:
	UsbThread(QObject *parent = nullptr);
	~UsbThread();
	//int count = 100;

private:
	int get_con_acd(uint32_t id, uint8_t *send, uint8_t *recv, uint8_t send_cmd, uint8_t rec_cmd);
	int get_rec(uint8_t *recv, uint8_t cmd, int timeout);
	int connect_send(uint8_t *packet, uint32_t len);
	int data_packet_send(uint8_t *packet, uint32_t len, char *data, uint8_t *recv, int usb_num);
	//void add_bin_head(uint32_t addr, uint32_t bin_len, uint32_t tmp_res, uint8_t *data);
	//void sm_store_le_uint32(uint8_t *addr, uint32_t value_1);
	UsbControl *usbControl;
	QThread *m_thread;

public slots:
	void packet_connect_send(int dev_num);
	void runUpgrade(int dev_num, int add, int len, bool check, int run_addr, char *data_ptr);
	void reset_usb_flash(int dev_num);
signals:
	void get_count(int i);
	void sed_progress(int i);
	void sed_handshake_status();  //ÎÕÊÖ×´Ì¬
	void sed_run_flash_status();  //Éı¼¶×´Ì¬
	void sed_reset_status();  //¸´Î»×´Ì¬
	void delete_thread();   //É¾³ıÏß³Ì
};
