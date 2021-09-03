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

//����ͨ�ŵı��ı�ʶ
constexpr auto MSG_UNIFIED_MSGID = 0x55aa5a5a;						//���Ŀ�ͷͳһ��ʶ
constexpr auto MSG_PC_TX_YL_PZ = 0xAE;									//PC��->TX231���������ñ���
constexpr auto MSG_PC_TX_CD_PZ = 0xAF;									//PC��->TX231�ĳ�����ñ���
constexpr auto MSG_PC_TX_LY_PZ = 0xB1;									//PC��->TX231���������ñ���
constexpr auto MSG_PC_TX_AJ_PZ = 0xB2;									//PC��->TX231�İ������ñ���
constexpr auto MSG_TX_PC_REPLY = 0xB3;									//TX231->PC�˵Ľ���״̬�ظ�����

constexpr auto MSG_ACK_TX_YL_OK = 0x01;									//�ظ�<<PC��->TX231���������ñ���>>���ճɹ�
constexpr auto MSG_ACK_TX_CD_OK = 0x02;								//�ظ�<<PC��->TX231�ĳ�����ñ���>>���ճɹ�
constexpr auto MSG_ACK_TX_LY_OK = 0x03;									//�ظ�<<PC��->TX231���������ñ���>>���ճɹ�
constexpr auto MSG_ACK_TX_AJ_OK = 0x04;									//�ظ�<<PC��->TX231�İ������ñ���>>���ճɹ�
constexpr auto MSG_ACK_TX_CHECKSUM_ERROR = 0x05;			//�ظ�<<PC��->TX231�����ñ���>>����ʧ��

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
	unsigned  int		syncWord;			//�̶�����Ϣ��ͷ 0x55aa5a5a
	unsigned short		nMsgBodySize;	//�������峤��
	unsigned char		nMsgID;				//���ı�ʶ
	//MsgBody										//��������
	//checksum										//2�ֽ�У��λ
};

//��������
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
	unsigned char defaultVal;		//ϵͳĬ������
	unsigned char tipsVal;				//��ʾ������
	unsigned short checksum;		//У��λ
};

//�������
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
	int	 charge_full_voltage;		//�������ѹ������1000�������ѹֵΪ4.202��charge_full_voltage=4.202*1000����4202��֤����ʱ����ʧ���� [4.1, 4.5]
	int	 charge_full_current;		//��������� [3,10]
	int charge_current;				//������ [15,40]
	int low_voltage_tips;			//�͵�ѹ���ѵ�ѹ���ã�����1000 [3, 3.5]
	int low_shut_down;				//�͵�ػ���ѹ���ã�����1000 [3, 3.5]
	unsigned short checksum;
};

//��������
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
	char name[248];					//�������� utf-8����
	unsigned char mac[6];			//MAC��ַ
	//char mac[17];						//MAC��ַ
	unsigned char sendFreq;		//��������Ƶ�� [0,10]
	unsigned char tm;				//û�������Զ��ػ�����
	unsigned short checksum;
};

//��������
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
	unsigned char nSum;			//���ð�������
	unsigned char nKey[10];		//ʮ�������ֱ��Ӧ��ֵ�����û�м�Ϊ0�޹��� 1�����绰 2�Ҷϵ绰 3�ܽӵ绰 4�������� 5��һ�� 6��һ�� 7��ͣ���� 8������ 9����- 10��λ 11������������
	unsigned short checksum;	//У��λ
};

//TX231�ظ�PC����
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
	unsigned char ack_status;		//�ظ�״ֵ̬
	unsigned short checksum;

};

constexpr auto TX_PC_REPLY_LEN = sizeof(TX_PC_REPLY);

#pragma pack(pop)