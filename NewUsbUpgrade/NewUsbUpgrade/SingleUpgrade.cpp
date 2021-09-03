#include "SingleUpgrade.h"

SingleUpgrade::SingleUpgrade(QWidget *parent,int index)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.groupBox->setTitle("USB_" + QString::number(index));
	QImage img("./Logo.png");
	ui.label->setPixmap(QPixmap::fromImage(img));
	ui.label->setAlignment(Qt::AlignCenter);
	ui.progressBar->setValue(0);
	//m_thread = new QThread();
	//m_usbThread = new UsbThread;
	//usbControl = new UsbControl(this);
	//m_usbThread->moveToThread(m_thread);
	//connect(m_thread, &QThread::finished, m_usbThread, &QObject::deleteLater);
	//connect(this, &SingleUpgrade::sig_handshake, m_usbThread, &UsbThread::packet_connect_send);
	//connect(m_usbThread, &UsbThread::get_count, this, &SingleUpgrade::test);
	//m_thread->start();
}

SingleUpgrade::~SingleUpgrade()
{
	//m_thread->quit();
	//m_thread->wait();
}

void SingleUpgrade::get_flash_addr(int addr,int run_add)
{
	ui.lineEdit->setText("0x" + QString::number(addr, 16));
	ui.lineEdit_2->setText("0x" + QString::number(run_add, 16));
}

void SingleUpgrade::run_handshake(int dev_num)
{
	//emit sig_handshake();
	m_usbThread = new UsbThread;
	connect(this, &SingleUpgrade::sig_handshake, m_usbThread, &UsbThread::packet_connect_send);
	connect(m_usbThread, &UsbThread::get_count, this, &SingleUpgrade::test);
	connect(this, &SingleUpgrade::sig_upgrade, m_usbThread, &UsbThread::runUpgrade);
	connect(m_usbThread, &UsbThread::sed_progress, this, &SingleUpgrade::progress_value);
	connect(this, &SingleUpgrade::sig_reset, m_usbThread, &UsbThread::reset_usb_flash);
	connect(m_usbThread, &UsbThread::sed_handshake_status, this, &SingleUpgrade::handshake_status_change);
	connect(m_usbThread, &UsbThread::sed_run_flash_status, this, &SingleUpgrade::upgrade_status_change);
	connect(m_usbThread, &UsbThread::sed_reset_status, this, &SingleUpgrade::reset_status_change);
	connect(m_usbThread, &UsbThread::delete_thread, this, &SingleUpgrade::delete_statck);
	emit sig_handshake(dev_num);
}

void SingleUpgrade::start_flash_load(int dev_num, int flash_addr, int len, bool check,int run_addr, char *data_ptr)
{
	emit sig_upgrade(dev_num, flash_addr,len,check,run_addr,data_ptr);
}

void SingleUpgrade::reset_flash(int dev_num)
{
	emit sig_reset(dev_num);
}

void SingleUpgrade::test(int i)
{
	ui.label->setText(QString::number(i));
}

void SingleUpgrade::handshake_status_change()
{
	ui.pushButton->setStyleSheet("background: rgb(0,255,0)");
}

void SingleUpgrade::upgrade_status_change()
{
	ui.pushButton_2->setStyleSheet("background: rgb(0,255,0)");
}

void SingleUpgrade::reset_status_change()
{
	ui.pushButton_3->setStyleSheet("background: rgb(0,255,0)");
}

void SingleUpgrade::progress_value(int i)
{
	ui.progressBar->setValue(i);
}

void SingleUpgrade::reset_color()
{
	ui.pushButton->setStyleSheet("background: rgb(255,255,255)");
	ui.pushButton_2->setStyleSheet("background: rgb(255,255,255)");
	ui.pushButton_3->setStyleSheet("background: rgb(255,255,255)");
}

void SingleUpgrade::delete_statck()
{
	disconnect(this, &SingleUpgrade::sig_handshake, m_usbThread, &UsbThread::packet_connect_send);
	disconnect(m_usbThread, &UsbThread::get_count, this, &SingleUpgrade::test);
	disconnect(this, &SingleUpgrade::sig_upgrade, m_usbThread, &UsbThread::runUpgrade);
	disconnect(m_usbThread, &UsbThread::sed_progress, this, &SingleUpgrade::progress_value);
	disconnect(this, &SingleUpgrade::sig_reset, m_usbThread, &UsbThread::reset_usb_flash);
	disconnect(m_usbThread, &UsbThread::sed_handshake_status, this, &SingleUpgrade::handshake_status_change);
	disconnect(m_usbThread, &UsbThread::sed_run_flash_status, this, &SingleUpgrade::upgrade_status_change);
	disconnect(m_usbThread, &UsbThread::sed_reset_status, this, &SingleUpgrade::reset_status_change);
	disconnect(m_usbThread, &UsbThread::delete_thread, this, &SingleUpgrade::delete_statck);
	delete m_usbThread;
	m_usbThread = nullptr;
}
