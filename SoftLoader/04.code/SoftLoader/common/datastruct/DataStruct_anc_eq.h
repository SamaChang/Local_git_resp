#pragma once

#include <QByteArray>
#include <QString>
#include <QtEndian>

#pragma pack(push, 1)

struct FIFF_HEADER {	//12
	char			szRiffID[4];		//"RIFF"
	unsigned long	dwRiffSize;			//����wav�ļ���С��ȥID��Size��ռ�õ��ֽ���
	char			szRiffFormat[4];	//"WAVE"
};

struct WAVE_FORMAT {	
	unsigned short	wFormatTag;			//���������ĸ�ʽ���࣬Ҳ����˵�Ǳ��뷽ʽ��ֵΪ1ʱ����ʾ����Ϊ����PCM���룬����1ʱ��ʾ��ѹ���ı��룩
	unsigned short	wChannels;			//��Ƶͨ����Ŀ��1�C��ͨ������������2�C˫ͨ����������
	unsigned long	dwSamplesPerSec;	//����Ƶ�ʣ�ÿ����������
	unsigned long	dwAvgBytesPreSec;	//ÿ��Ĳ����ֽ���.�������ݴ������ʣ�ÿ��ƽ���ֽ����� ������Ƶ�� �� ��Ƶͨ���� �� ÿ�β����õ�������λ�� / 8��
	unsigned short	wBlockAlign;		//���ݿ���뵥λ(ÿ��������Ҫ���ֽ���) ��ͨ������ÿ�β����õ�����������λֵ��8��
	unsigned short	wBitsPerSample;		//����λ��.ÿ�β����õ�����������λ��ֵ��Qt�������ᵽһ������Ϊ8 �� 16 �� ��һЩϵͳ����֧�ָ��ߵ�����λ�����ٶȰٿ����ᵽ��ȡֵ 8��16��24��
	//unsigned short	cbSize;				//wFormatTagΪWAVE_FORMAT_PCMʱ,���Դ˲���
};

struct FMT_BLOCK		//24
{
	char			szFmtID[4];			//"fmt "
	unsigned long	dwFmtSize;			//��ʾ��ʽ���п����ݴ�С��ͨ��Ϊ16��Ϊ18ʱ��ʾ��ʽ���п������и�����Ϣ
	WAVE_FORMAT		wavFormat;
};

struct DATA_BLOCK
{
	char			szDataID[4];		//���ݿ��ʶ�� "data"
	unsigned long	dwDataSize;			//�����������ֽ��� / ���ݿ��п������ܴ�С����wav�ļ�ʵ����Ƶ������ռ�Ĵ�С��
};

struct WAVE_HEADER
{
	FIFF_HEADER fiff_header;
	FMT_BLOCK	fmt_header;
};

//���������ֺ�����չ
enum CONF_TYPE
{
	CONF_TYPE_PEAK=1,
	CONF_TYPE_LOW,
};

//�˲������ò���
struct CONF_WAVE_FILTER_PARAM
{
	CONF_WAVE_FILTER_PARAM()
		: nType(0)
		, nSerial(0)
		, freq(0)
		, boost(0)
		, nQ(0)
		, gain(0)
		, slope(0)
		,spare(0)
	{

	}
	qint16		nType;		//�������� 0bypass 1peak 2low
	qint16		nSerial;	//���
	qint16		freq;		//Ƶ��
	double		boost;		//����	/b0
	double		nQ;			// Ӱ��ΧQ /b1
	double		gain;		//����	/b2
	double		slope;		//�¶� LOW/HIGH SHELF	/a1
	double		spare;		// a2

	CONF_WAVE_FILTER_PARAM & operator=(const CONF_WAVE_FILTER_PARAM & stu)
	{
		this->nType = stu.nType;
		this->nSerial = stu.nSerial;
		this->freq = stu.freq;
		this->boost = stu.boost;
		this->nQ = stu.nQ;
		this->gain = stu.gain;
		this->slope = stu.slope;
		this->spare = stu.spare;
		return *this;
	}

	void reset()
	{
		freq = 0;
		boost = 0;
		nQ = 0;
		gain = 0;
		slope = 0;
		spare = 0;
	}
};

//�����߶����ò���
struct WAVE_LINE_PARAM
{
	int		nSerial;				//���
	QString name;					//����
	QString path;					//·��
	QString clr;					//��ɫ
};

struct AXIS_STRUCT
{
	AXIS_STRUCT():nMin_x(0),nMax_x(8000),nMin_y(-2),nMax_y(2)
	{}
	double nMin_x;
	double nMax_x;
	double nMin_y;
	double nMax_y;
};

//����ͨ�ŵı��ı�ʶ
constexpr auto MSG_UNIFIED_MSGID = 0x55aa5a5a;
constexpr auto MSG_SEND_EQ_TX = 0xAA;
constexpr auto MSG_SEND_ANC_TX_FB = 0xAB;
constexpr auto MSG_SEND_ANC_TX_FF = 0xAC;
constexpr auto MSG_REPLY_TX = 0xAD;
constexpr auto MSG_ACK_TX_EQ_OK = 0x01;
constexpr auto MSG_ACK_TX_ANC_FB_OK = 0x02;
constexpr auto MSG_ACK_TX_ANC_FF_OK = 0x03;
constexpr auto MSG_ACK_TX_CHECKSUM_ERROR = 0x04;


//����IIR_INFO�ṹ
#define IIR_INFO_LEN 35
//��Ϊ�������ᵽ���������У���Ӧ����ͨ·��������������ѡ�ͨ������϶����ơ�����һ��32λ��Ĭ	��С��27λ������5λ�������Բ����ַ�����ȡ�ķ�ʽ����ȡIIR������ֵ
struct IIR_INFO_2		
{
	IIR_INFO_2()
	{
		memset(b0, 0, IIR_INFO_LEN);
		memset(b1, 0, IIR_INFO_LEN);
		memset(b2, 0, IIR_INFO_LEN);
		memset(a0, 0, IIR_INFO_LEN);
		memset(a1, 0, IIR_INFO_LEN);
		memset(a2, 0, IIR_INFO_LEN);
	}
	char b0[35];
	char b1[35];
	char b2[35];
	char a0[35];
	char a1[35];
	char a2[35];
};

///EQ���岿�ֽṹ�嶨��
struct ComMsgHeader
{
	ComMsgHeader()
	{
		syncWord = MSG_UNIFIED_MSGID;	//����ͳһͷ 
		msgID = 0xAA;			 
	}
	unsigned int	syncWord;		//�̶�����Ϣ��ͷͬ���� 0x55aa5a5a
	unsigned short	nSize;		//Data���ֵĳ��� ȡֵ��Χ[0,65535]
	unsigned char	msgID;		//��ϢID 0xAA

	//char* pData;					//��Ϣ��Ӧ��data,��command��Ϣ��Ӧ�Ĳ�������nSizeΪ��ʱ������ϢΪ��
	//unsigned char	checkSum;		//Э�����żУ���룬���㷽ʽΪ����Э���ȥSyncWord���ֺ������ֽڰ�λ��XOR����
};

struct IIR_INFO
{
	IIR_INFO()
	{
		b0 = 1;
		b1 = 0;
		b2 = 0;
		a0 = 1;
		a1 = 0;
		a2 = 0;
	}
	double b0;
	double b1;
	double b2;
	double a0;
	double a1;
	double a2;
};

struct IIR_INFO_INT
{
	IIR_INFO_INT()
	{
		b0 = 1;
		b1 = 0;
		b2 = 0;
		a0 = 1;
		a1 = 0;
		a2 = 0;
	}
	int b0;
	int b1;
	int b2;
	int a0;
	int a1;
	int a2;
};

//����EQ���Ľṹ
struct SEND_INFO_MSG
{
	ComMsgHeader header;
	IIR_INFO_INT cData[10];
	unsigned short checkSum;
	void reset()
	{
		header.syncWord = qFromBigEndian(header.syncWord);
		header.nSize = qFromBigEndian(header.nSize);
		for (int i = 0; i < 10; ++i)
		{
			cData[i].b0 = qFromBigEndian(cData[i].b0);
			cData[i].b1 = qFromBigEndian(cData[i].b1);
			cData[i].b2 = qFromBigEndian(cData[i].b2);
			cData[i].a0 = qFromBigEndian(cData[i].a0);
			cData[i].a1 = qFromBigEndian(cData[i].a1);
			cData[i].a2 = qFromBigEndian(cData[i].a2);
		}
		checkSum = qFromBigEndian(checkSum);
	}

};

constexpr auto SEND_INFO_MSG_LEN = sizeof(SEND_INFO_MSG);

//����ANC���Ľṹ
struct ANC_INFO_MSG
{
	ComMsgHeader header;
	IIR_INFO cData_FF[10];
	IIR_INFO cData_FB[10];
	unsigned short checkSum;
};

struct TX_PC_REPLY
{
	TX_PC_REPLY()
	{
		head.syncWord = MSG_UNIFIED_MSGID;
		head.nSize = 0x0001;
		head.msgID = MSG_REPLY_TX;
		ack_status = 0;
		checksum = 0;
	}
	ComMsgHeader head;
	unsigned char ack_status;
	unsigned short checksum;
	void reset()
	{
		head.syncWord = qFromBigEndian(head.syncWord);
		head.nSize = qFromBigEndian(head.nSize);
		checksum = qFromBigEndian(checksum);
	}
};
constexpr auto TX_PC_REPLY_LEN = sizeof(TX_PC_REPLY);



#pragma pack(pop)
