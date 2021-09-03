#pragma once

#include "def.h"
#include <string>
//typedef unsigned char uchar;


#pragma pack(push)		//�����ֽڶ���
#pragma pack(1)				//һ�ֽڶ���

struct DataProtorl
{
	DataProtorl()
	{
		SyncWord = MSG_UNIFIED_MSGID;	//����ͳһͷ
		MsgSize = 0;
		MsgID = 0;
	}
	unsigned int SyncWord;	//����ͳһͷ
	//char *SyncWord;
	unsigned short MsgSize;		//�������ݳ���
	unsigned char MsgID;				//����Ψһ��ʶ
	//char *MsgBody;
	//char checkSum;
};

struct TX_PC_REPLY
{
	TX_PC_REPLY()
	{
		head.MsgSize = 0x0002;
		head.MsgID = MSG_TX_PC_MSGID;
		socketid = 0;
		ack_status = 0;
		checksum = 0;
	}
	DataProtorl head;
	unsigned char socketid;
	unsigned char ack_status;
	unsigned short checksum;
	void readyData();
};

constexpr auto TX_PC_REPLY_LEN = sizeof(TX_PC_REPLY);

//PC֪ͨTX231����ָ��
struct PC_TX_ERASE_CMD
{
	PC_TX_ERASE_CMD()
	{
		head.MsgSize = 0x0005;
		head.MsgID = MSG_SEND_ERASE;
		block_addr = 0;
		block_num = 0;
		checksum = 0;
	}
	
	DataProtorl head;
	unsigned int block_addr;
	unsigned char block_num;
	unsigned short checksum;
	void readyData();
};

constexpr auto PC_TX_ERASE_CMD_LEN = sizeof(PC_TX_ERASE_CMD);

//PC֪ͨTX231дҳ
struct PC_TX_WRITE_PAGE
{
	PC_TX_WRITE_PAGE()
	{
		head.MsgSize = 0x0105;
		head.MsgID = MSG_SEND_WRITE_PAGE;
		page_addr = 0;
		last_page_flag = 0;
		memset(firmware_data, 0, 256);
		checksum = 0;
	}
	DataProtorl head;
	unsigned int page_addr;
	unsigned char last_page_flag;
	unsigned char firmware_data[256];
	unsigned short checksum;
	void readyData();
};

constexpr auto PC_TX_WRITE_PAGE_LEN = sizeof(PC_TX_WRITE_PAGE);

#pragma pack(pop)			//�ָ��ֽڶ���