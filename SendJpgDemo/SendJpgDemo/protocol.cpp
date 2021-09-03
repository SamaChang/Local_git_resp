#include "protocol.h"

void store_le_uint16(char *addr, short value)      /* big endian */
{
	addr[0] = value >> 8;
	addr[1] = value & 0xff;
}


void store_le_uint32(uint8_t *addr, uint32_t value)     /* big endian */
{
	addr[0] = value >> 24;
	addr[1] = (value >> 16) & 0xff;
	addr[2] = (value >> 8) & 0xff;
	addr[3] = value & 0xff;
}

unsigned short reverse_uint16(unsigned char *uint16_value)          /* big endian */
{
	//return  uint32_value[0] << 24 |
	//	uint32_value[1] << 16 |
	//	uint32_value[2] << 8 |
	//	uint32_value[3];
	return uint16_value[0] << 8 |
		uint16_value[1];
}

//void ada(char *packet,char *buf)
//{
//	buffer_send *req = (buffer_send *)packet;
//	req->data = buf;
//}

void syncWord(/*unsigned*/ char *packet,/*unsigned*/ short size, /*unsigned*//* char *data,*/ buffer_send bs, /*unsigned*/ char parityCheck)
{
	UartProtocol *req = (UartProtocol *)packet;
	req->SyncWord[0] = 0xEF;
	req->SyncWord[1] = 0xAA;
	req->MsgID = 0x14;
	store_le_uint16(req->Size, size);
	req->s = bs;
	req->ParityCheck = parityCheck;
}

void testNewProtocol(char *packet, short size/*, char parityCheck*//*,Test *test*/)
{
	Test *req = (Test *)packet;
	req->MsgID = 0x14;
	req->SyncWord[0] = 'S';
	req->SyncWord[1] = 'J';
	//req->ParityCheck = parityCheck;
	store_le_uint16(req->Size, size);
	//req->data = test.data;
}

void progresPortocol(char *packet, uint32_t size)
{
	ProgressPro *req = (ProgressPro *)packet;
	req->MsgID = 0x14;
	req->SyncWord[1] = 0xAA;
	store_le_uint32(req->Size, size);
	req->SyncWord[0] = 0xEF;
}

void featurePortocol(char *packet, uint32_t size)
{
	ProgressPro *req = (ProgressPro *)packet;
	req->MsgID = 0x15;
	req->SyncWord[1] = 0xAA;
	store_le_uint32(req->Size, size);
	req->SyncWord[0] = 0xEF;
}

void checkCMD(char *packet, uint32_t size)
{
	ProgressPro *req = (ProgressPro *)packet;
	req->SyncWord[0] = 0xEF;
	req->SyncWord[1] = 0xAA;
	req->MsgID = 0xB0;
	store_le_uint32(req->Size, size);
}
void insertCheck(char *packet,char check)
{
	Check *req = (Check *)packet;
	req->ParityCheck = check;
}


void checkID(char *packet)
{
	sendCheck *sed = (sendCheck *)packet;
	sed->SyncWord[0] = 0xEF;
	sed->SyncWord[1] = 0xAA;
	sed->Cmd = SENDCHECKID;
	sed->ChildCmd = CURRENTID;
}
//void pic_data(unsigned char *packet, unsigned char e)
//{
//	UartProtocol *req = (UartProtocol *)packet;
//	unsigned char data[1000] = { 0 };
//	req->data[0] = e;
//}

//void saveLog(const QString &SN, const QString &item, const QString &isPass)
//{
//	//QDateTime da_time;
//	//QString time_str = da_time.currentDateTime().toString("yyyy-MM-dd HH-mm-ss");
//	QDir *DataFile = new QDir;    //创建文件路径（创建一个文件夹）
//	bool exist = DataFile->exists("D:/Pic_360*640");
//	if (!exist)
//	{
//		bool isok = DataFile->mkdir("D:/Pic_360*640"); // 新建文件夹
//		if (!isok)
//			QMessageBox::warning(nullptr, "sdf", "can't mkdir", QMessageBox::Ok);
//	}
//	//QString fileName = "D:/LogFile/"/* + time_str + */"log.txt";
//	QString fileName = "D:/LogFile/" + SN + "log.txt";
//	QFile file(fileName);
//	if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
//	{
//		QMessageBox::warning(nullptr, "sdf", "can't open", QMessageBox::Ok);
//	}
//	QTextStream stream(&file);
//	stream << time_str + "\t\t\t" + item + "\t\t" + isPass << "\n";
//	file.close();
//}
