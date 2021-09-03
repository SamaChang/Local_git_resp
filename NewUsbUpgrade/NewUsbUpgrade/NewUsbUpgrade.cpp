#include "NewUsbUpgrade.h"
#include <qsettings.h>
#include <qfile.h>
#include <qfiledialog.h>
#include <qmessagebox.h>

NewUsbUpgrade::NewUsbUpgrade(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
	this->setWindowIcon(QIcon("./Logo.png"));
	initWdg();
	//usbControl = new UsbControl;
	//usbControl->get_dev();
}


void NewUsbUpgrade::initWdg()
{
	for (int i = 0; i < WDG_COUNT; i++)
	{
		singleWdg = new SingleUpgrade(this, i + 1);
		ui.gridLayout->addWidget(singleWdg);
		single_vec.push_back(singleWdg);
		//singleWdg->run_handshake();
	}
}


void NewUsbUpgrade::readIni()
{
	Common common;
	////terminateMYSQL();
	uint8_t addr[PARA_LEN * 7] = { 0 };
	QString strPath = "./PacketFile/monocular_lock_combine_1P5M.ini";
	QString filePath = "./PacketFile/flash_download_file.bin";
	QByteArray fileData;
	QSettings setIni(strPath, QSettings::IniFormat);
	QString offset = setIni.value("boot_para/flash offset").toString();
	QString offset_805_dtcm = setIni.value("805_dtcm/flash offset").toString();
	QString offset_804_app = setIni.value("804_app/flash offset").toString();
	QString offset_805_ddr = setIni.value("805_ddr/flash offset").toString();
	QString offset_weight = setIni.value("weight/flash offset").toString();
	QString offset_ddr_rate = setIni.value("boot_para/ddr_rate").toString();
	QString offset_flash_div = setIni.value("boot_para/flash_div").toString();
	QString offset_flash_capture_delay = setIni.value("boot_para/flash_capture_delay").toString();

	int off_boot_para = offset.toInt(nullptr, isX(offset));
	int off_805_dtcm = offset_805_dtcm.toInt(nullptr, isX(offset_805_dtcm));
	int off_804_app = offset_804_app.toInt(nullptr, isX(offset_804_app));
	int off_805_ddr = offset_805_ddr.toInt(nullptr, isX(offset_805_ddr));
	int off_weight = offset_weight.toInt(nullptr, isX(offset_weight));
	int off_ddr_rate = offset_ddr_rate.toInt(nullptr, isX(offset_ddr_rate));
	int off_flash_div = offset_flash_div.toInt(nullptr, isX(offset_flash_div));
	int off_flash_capture_delay = offset_flash_capture_delay.toInt(nullptr, isX(offset_flash_capture_delay));
	QFile file(filePath);
	if (file.open(QIODevice::ReadOnly))
	{
		fileData = file.readAll();
	}
	else
	{
		return;
	}
	file.close();
	common.add_table(addr, off_805_dtcm, 0);
	common.add_table(addr + PARA_LEN, off_804_app, 0);
	common.add_table(addr + PARA_LEN * 2, off_805_ddr, 0);
	common.add_table(addr + PARA_LEN * 3, off_weight, 0);
	common.add_table(addr + PARA_LEN * 4, off_ddr_rate, 0);
	common.add_table(addr + PARA_LEN * 5, off_flash_div, 0);
	common.add_table(addr + PARA_LEN * 6, off_flash_capture_delay, 0);
	memcpy(fileData.data() + off_boot_para + PARA_LEN * 4, addr, PARA_LEN * 7);
	//QString write_path = "./PacketFile/new_flash_download_file.bin";
	QFile file_write(filePath);
	if (file_write.open(QIODevice::WriteOnly))
	{
		file_write.write(fileData);
	}
	file_write.close();
}


//选择bin文件
void NewUsbUpgrade::selected_file()
{
	if (!fileData.isEmpty())
		fileData.clear();
	QString str = QFileDialog::getOpenFileName(this, "Selected File", "", "*.bin");
	QFile file(str);
	if (!file.open(QIODevice::ReadOnly))
	{
		QMessageBox::warning(this, "Error", "Can Not Open File!", QMessageBox::Ok);
		return;
	}
	fileData = file.readAll();
	file.close();
	//ui.textEdit->append(QString::fromLocal8Bit("选择文件：") + str);
}


void NewUsbUpgrade::get_usb_dev()
{
	usb_init();
	int a = usb_find_busses();
	int b = usb_find_devices();
	int count = 0;

	struct usb_bus *bus;
	struct usb_device *dev;

	for (bus = usb_get_busses(); bus; bus = bus->next)
	{
		for (dev = bus->devices; dev; dev = dev->next)
		{
			if (dev->descriptor.idVendor == IDVendor
				&& dev->descriptor.idProduct == IDProduct)
			{
				count++;
			}
		}
	}
	usb_dev_count = count;
}
//握手
void NewUsbUpgrade::on_pushButton_clicked()
{
	//dev_list.clear();
	//usbControl = new UsbControl;
	//usbControl->get_dev();
	//int count = dev_list.size();
	get_usb_dev();
	
	for (int i = 0; i < usb_dev_count; i++)
	{
		single_vec[i]->reset_color();
		single_vec[i]->run_handshake(i);
	}
}
//选择文件
void NewUsbUpgrade::on_pushButton_2_clicked()
{
	readIni();
	selected_file();
}
//升级
void NewUsbUpgrade::on_pushButton_3_clicked()
{
	QString str = ui.lineEdit->text();
	QString str_2 = ui.lineEdit_2->text();
	int len = fileData.size();
	char *data_ptr = fileData.data();
	bool check = ui.checkBox->isChecked();
	for (int i = 0; i < usb_dev_count; i++)
	{
		int add = str.toInt(NULL, 16);
		int add_2 = str_2.toInt(NULL, 16);
		single_vec[i]->get_flash_addr(add, add_2);
		single_vec[i]->start_flash_load(i, add, len, check, add_2, data_ptr);
	}
	
}
//复位
void NewUsbUpgrade::on_pushButton_4_clicked()
{
	for (int i = 0; i < usb_dev_count; i++)
	{
		single_vec[i]->reset_flash(i);
	}
}

//文件打包
void NewUsbUpgrade::on_pushButton_5_clicked()
{
	system("cd ./PacketFile&JT_combine_and_load.bat");
}