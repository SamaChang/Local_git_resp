#pragma once
//#define CMD_HAND	"TX21"

typedef struct {
	char SyncWord[4];
	//char *SyncWord;
	char MsgSize[2];
	char MsgID;
	//char *MsgBody;
	//char checkSum;
}dataProtorl;

void short2char(char *size, short len);
void store_le_uint32(unsigned char *addr, unsigned int value);
void data2protorl(char *data, short size, char id);
void pc2tx231(char *data);
unsigned short reverse_uint16(unsigned char *uint16_value);
void insertEraseDataBody();
