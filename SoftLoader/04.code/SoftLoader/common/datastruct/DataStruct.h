#pragma once
#include <string>
#include <QtEndian>
//using namespace std;

unsigned short calcCheckSum(unsigned char *pData, int nSize)
{
	uint16_t checksum = 0;
	for (int i = 0; i < nSize; ++i)
	{
		checksum += pData[i];
	}
	return checksum;
}

#pragma pack(push, 1)

//定义通信的报文标识
constexpr auto MSG_UNIFIED_MSGID = 0x55aa5a5a;						//报文开头统一标识
constexpr auto MSG_PC_TX_YL_PZ = 0xAE;									//PC端->TX231的音量配置报文
constexpr auto MSG_PC_TX_CD_PZ = 0xAF;									//PC端->TX231的充电配置报文
constexpr auto MSG_PC_TX_LY_PZ = 0xB1;									//PC端->TX231的蓝牙配置报文
constexpr auto MSG_PC_TX_AJ_PZ = 0xB2;									//PC端->TX231的按键配置报文
constexpr auto MSG_TX_PC_REPLY = 0xB3;									//TX231->PC端的接收状态回复报文

constexpr auto MSG_ACK_TX_YL_OK = 0x01;									//回复<<PC端->TX231的音量配置报文>>接收成功
constexpr auto MSG_ACK_TX_CD_OK = 0x02;								//回复<<PC端->TX231的充电配置报文>>接收成功
constexpr auto MSG_ACK_TX_LY_OK = 0x03;									//回复<<PC端->TX231的蓝牙配置报文>>接收成功
constexpr auto MSG_ACK_TX_AJ_OK = 0x04;									//回复<<PC端->TX231的按键配置报文>>接收成功
constexpr auto MSG_ACK_TX_CHECKSUM_ERROR = 0x05;			//回复<<PC端->TX231的配置报文>>接收失败

constexpr auto MSG_REMAIN = 9;		//SyncWord+MsgBodySize+MsgID+checksum
constexpr auto MSG_DIMENSION = 1000;

struct ComMsgHeader
{
	ComMsgHeader()
	{
		syncWord = MSG_UNIFIED_MSGID;
		nMsgBodySize = 0;
		nMsgBodySize = 0;
	}
	unsigned  int		syncWord;			//固定的消息开头 0x55aa5a5a
	unsigned short		nMsgBodySize;	//报文主体长度
	unsigned char		nMsgID;				//报文标识
	//MsgBody										//报文主体
	//checksum										//2字节校验位
};

//音量配置
struct VolumeConfStu
{
	VolumeConfStu()
	{
		header.nMsgBodySize = sizeof(VolumeConfStu) - MSG_REMAIN;
		header.nMsgID = MSG_PC_TX_YL_PZ;
		defaultVal = 0;
		tipsVal = 0;
		checksum = 0;
	}
	void reset()
	{
		header.syncWord = qFromBigEndian(header.syncWord);
		header.nMsgBodySize = qFromBigEndian(header.nMsgBodySize);

		checksum = calcCheckSum((unsigned char*)this + 4, sizeof(VolumeConfStu) - 6);
		checksum = qFromBigEndian(checksum);
	}
	ComMsgHeader header;
	unsigned char defaultVal;		//系统默认音量
	unsigned char tipsVal;				//提示音音量
	unsigned short checksum;		//校验位
};

//充电配置
struct ChargeConfStu
{
	ChargeConfStu()
	{
		header.nMsgBodySize = sizeof(ChargeConfStu) - MSG_REMAIN;
		header.nMsgID = MSG_PC_TX_CD_PZ;
		charge_full_voltage = 0;
		charge_full_current = 0;
		charge_current = 0;
		low_voltage_tips = 0;
		low_shut_down = 0;
		checksum = 0;
	}
	void reset()
	{
		header.syncWord = qFromBigEndian(header.syncWord);
		header.nMsgBodySize = qFromBigEndian(header.nMsgBodySize);
		

		charge_full_voltage = qFromBigEndian(charge_full_voltage);
		charge_full_current = qFromBigEndian(charge_full_current);
		charge_current = qFromBigEndian(charge_current);
		low_voltage_tips = qFromBigEndian(low_voltage_tips);
		low_shut_down = qFromBigEndian(low_shut_down);

		checksum = calcCheckSum((unsigned char*)this + 4, sizeof(VolumeConfStu) - 6);
		checksum = qFromBigEndian(checksum);
	}
	ComMsgHeader header;
	int	 charge_full_voltage;		//充电满电压，量纲1000，比如电压值为4.202，charge_full_voltage=4.202*1000，即4202保证传输时不丢失数据 [4.1, 4.5]
	int	 charge_full_current;		//充满电电流 [3,10]
	int charge_current;				//充电电流 [15,40]
	int low_voltage_tips;			//低电压提醒电压设置，量纲1000 [3, 3.5]
	int low_shut_down;				//低电关机电压设置，量纲1000 [3, 3.5]
	unsigned short checksum;
};

//蓝牙配置
struct BluetoothConfStu
{
	BluetoothConfStu()
	{
		header.nMsgBodySize = sizeof(BluetoothConfStu) - MSG_REMAIN;
		header.nMsgID = MSG_PC_TX_LY_PZ;
		memset(name, 0, 248);
		memset(mac, 0, 6);
		sendFreq = 0;
		tm = 0;
	}
	void reset()
	{
		header.syncWord = qFromBigEndian(header.syncWord);
		header.nMsgBodySize = qFromBigEndian(header.nMsgBodySize);

		checksum = calcCheckSum((unsigned char*)this + 4, sizeof(VolumeConfStu) - 6);
		checksum = qFromBigEndian(checksum);
	}
	ComMsgHeader header;
	char name[248];					//蓝牙名字 utf-8编码
	unsigned char mac[6];			//MAC地址
	//char mac[17];						//MAC地址
	unsigned char sendFreq;		//蓝牙发射频率 [0,10]
	unsigned char tm;				//没有连接自动关机配置
	unsigned short checksum;
};

//按键配置
struct KeyConfStu
{
	KeyConfStu()
	{
		header.nMsgBodySize = sizeof(KeyConfStu) - MSG_REMAIN;
		header.nMsgID = MSG_PC_TX_AJ_PZ;
		nSum = 0;
		for (int i = 0; i < 10; ++i)
		{
			nKey[i] = 0;
		}
		checksum = 0;
	}
	void reset()
	{
		header.syncWord = qFromBigEndian(header.syncWord);
		header.nMsgBodySize = qFromBigEndian(header.nMsgBodySize);

		checksum = calcCheckSum((unsigned char*)this + 4, sizeof(VolumeConfStu) - 6);
		checksum = qFromBigEndian(checksum);
	}
	ComMsgHeader header;
	unsigned char nSum;			//配置按键数量
	unsigned char nKey[10];		//十个按键分别对应的值，如果没有即为0无功能 1接听电话 2挂断电话 3拒接电话 4播放音乐 5上一首 6下一首 7暂停音乐 8音量＋ 9音量- 10复位 11唤醒语音助手
	unsigned short checksum;	//校验位
};

//TX231回复PC报文
struct TX_PC_REPLY
{
	TX_PC_REPLY()
	{
		header.syncWord = MSG_UNIFIED_MSGID;
		header.nMsgBodySize = 1;
		header.nMsgID = 0xB3;
		ack_status = 0;
		checksum = 0;
	}

	void reset()
	{
		header.syncWord = qFromBigEndian(header.syncWord);
		header.nMsgBodySize = qFromBigEndian(header.nMsgBodySize);
		checksum = qFromBigEndian(checksum);
	}

	ComMsgHeader header;
	unsigned char ack_status;		//回复状态值
	unsigned short checksum;

};

constexpr auto TX_PC_REPLY_LEN = sizeof(TX_PC_REPLY);

#pragma pack(pop)