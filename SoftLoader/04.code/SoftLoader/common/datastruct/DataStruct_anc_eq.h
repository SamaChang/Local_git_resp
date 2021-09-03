#pragma once

#include <QByteArray>
#include <QString>
#include <QtEndian>

#pragma pack(push, 1)

struct FIFF_HEADER {	//12
	char			szRiffID[4];		//"RIFF"
	unsigned long	dwRiffSize;			//整个wav文件大小减去ID和Size所占用的字节数
	char			szRiffFormat[4];	//"WAVE"
};

struct WAVE_FORMAT {	
	unsigned short	wFormatTag;			//波形声音的格式种类，也可以说是编码方式（值为1时，表示数据为线性PCM编码，大于1时表示有压缩的编码）
	unsigned short	wChannels;			//音频通道数目，1–单通道（声道）；2–双通道（声道）
	unsigned long	dwSamplesPerSec;	//采样频率（每秒样本数）
	unsigned long	dwAvgBytesPreSec;	//每秒的采样字节数.波形数据传输速率（每秒平均字节数） （采样频率 × 音频通道数 × 每次采样得到的样本位数 / 8）
	unsigned short	wBlockAlign;		//数据块对齐单位(每个采样需要的字节数) （通道数×每次采样得到的样本数据位值／8）
	unsigned short	wBitsPerSample;		//采样位数.每次采样得到的样本数据位数值（Qt助手中提到一般设置为8 或 16 ， 有一些系统可能支持更高的数据位数，百度百科中提到可取值 8、16、24）
	//unsigned short	cbSize;				//wFormatTag为WAVE_FORMAT_PCM时,忽略此参数
};

struct FMT_BLOCK		//24
{
	char			szFmtID[4];			//"fmt "
	unsigned long	dwFmtSize;			//表示格式块中块数据大小，通常为16，为18时表示格式块中块数据有附加信息
	WAVE_FORMAT		wavFormat;
};

struct DATA_BLOCK
{
	char			szDataID[4];		//数据块标识符 "data"
	unsigned long	dwDataSize;			//采样数据总字节数 / 数据块中块数据总大小（即wav文件实际音频数据所占的大小）
};

struct WAVE_HEADER
{
	FIFF_HEADER fiff_header;
	FMT_BLOCK	fmt_header;
};

//先设置两种后面扩展
enum CONF_TYPE
{
	CONF_TYPE_PEAK=1,
	CONF_TYPE_LOW,
};

//滤波器配置参数
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
	qint16		nType;		//参数类型 0bypass 1peak 2low
	qint16		nSerial;	//序号
	qint16		freq;		//频点
	double		boost;		//增益	/b0
	double		nQ;			// 影像范围Q /b1
	double		gain;		//音量	/b2
	double		slope;		//坡度 LOW/HIGH SHELF	/a1
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

//波形线段配置参数
struct WAVE_LINE_PARAM
{
	int		nSerial;				//序号
	QString name;					//名称
	QString path;					//路径
	QString clr;					//颜色
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

//定义通信的报文标识
constexpr auto MSG_UNIFIED_MSGID = 0x55aa5a5a;
constexpr auto MSG_SEND_EQ_TX = 0xAA;
constexpr auto MSG_SEND_ANC_TX_FB = 0xAB;
constexpr auto MSG_SEND_ANC_TX_FF = 0xAC;
constexpr auto MSG_REPLY_TX = 0xAD;
constexpr auto MSG_ACK_TX_EQ_OK = 0x01;
constexpr auto MSG_ACK_TX_ANC_FB_OK = 0x02;
constexpr auto MSG_ACK_TX_ANC_FF_OK = 0x03;
constexpr auto MSG_ACK_TX_CHECKSUM_ERROR = 0x04;


//单个IIR_INFO结构
#define IIR_INFO_LEN 35
//因为需求中提到“调试区中，对应三个通路有三个精度设置选项，通过鼠标拖动控制。都是一共32位，默	认小数27位，整数5位”，所以采用字符串存取的方式来存取IIR的六个值
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

///EQ主体部分结构体定义
struct ComMsgHeader
{
	ComMsgHeader()
	{
		syncWord = MSG_UNIFIED_MSGID;	//报文统一头 
		msgID = 0xAA;			 
	}
	unsigned int	syncWord;		//固定的消息开头同步字 0x55aa5a5a
	unsigned short	nSize;		//Data部分的长度 取值范围[0,65535]
	unsigned char	msgID;		//消息ID 0xAA

	//char* pData;					//消息对应的data,如command消息对应的参数。当nSize为零时，此消息为空
	//unsigned char	checkSum;		//协议的奇偶校验码，计算方式为整条协议出去SyncWord部分后，其他字节按位做XOR运算
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

//整个EQ报文结构
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

//整个ANC报文结构
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
