#pragma once
#include <qdir.h>
#include "qmessagebox.h"
#define SENDCHECKID 0xB0
#define RECCHECKID  0xB1
#define CURRENTID	0xB2    //查询当前id
#define ALLID		0xB3    //查询所有已注册id

//统一大端
struct sendCheck
{
	char SyncWord[2];
	char Cmd;        //查询命令
	char ChildCmd;   //查询当前、所有命令
};

struct recCheck
{
	char SyncWord[2];
	char CMD;
	char ChileCmd;
	char ID[4];    //当前注册ID
};

typedef struct
{
	/*unsigned */char data[1024 * 100];
	//char *data = (char *)malloc(1024 * 1024);
}buffer_send;

typedef struct
{
	/*unsigned */char SyncWord[2];
	/*unsigned */char MsgID;
	/*unsigned */char Size[2];
	/*unsigned *//*char *data[1000];*/
	buffer_send s;
	/*unsigned */char ParityCheck;
}UartProtocol;

struct Test
{
	char SyncWord[2];
	char MsgID;
	char Size[2];
	char *data;
	char ParityCheck;
};

typedef struct
{
	char SyncWord[2];
	char MsgID;
	uint8_t Size[4];
}ProgressPro;

typedef struct
{
	char ParityCheck;
}Check;

void checkCMD(char *packet, uint32_t size);
void checkID(char *packet);
void syncWord(/*unsigned */char *packet, /*unsigned */short size, /*unsigned *//*char *data,*/ buffer_send bs,/*unsigned */char parityCheck);
void store_le_uint16(/*unsigned*/ char *addr, /*unsigned*/ short value);
void store_le_uint32(uint8_t *addr, uint32_t value);     /* big endian */
//void saveLog(const QString &SN, const QString &item, const QString &isPass);
void testNewProtocol(char *packet, short syncword/*, char parityCheck*/ /*char *data*//*Test &test*//*Test &test*/);
void progresPortocol(char *packet, uint32_t size);
void insertCheck(char *packet, char check);
void featurePortocol(char *packet, uint32_t size);
unsigned short reverse_uint16(unsigned char *uint16_value);