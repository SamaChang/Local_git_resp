#pragma once
#include <QThread>
#include <QString>

constexpr auto PORT_BAUD_RATE = 500000;

constexpr auto MSG_UNIFIED_MSGID = 0x55aa5a5a;
//TX231->PC
constexpr auto MSG_TX_PC_MSGID = 0x01;
constexpr auto MSG_ACK_BL_START = 0x01;
constexpr auto MSG_ACK_ERASE_OK = 0x02;
constexpr auto MSG_ACK_PAGE_PROGRAM_OK = 0x03;
constexpr auto MSG_ACK_CHECKSUM_ERROR = 0x04;
constexpr auto MSG_ACK_ERASE_CHIP_OK = 0x05;

//PC->TX231
constexpr auto MSG_SEND_ERASE = 0x81;					//擦除指令报文头;
constexpr auto MSG_SEND_ERASE_LEN = 5;				//擦除指令报文长度;
constexpr auto MSG_SEND_ERASE_CHIP = 0x85;
constexpr auto MSG_SEND_WRITE_PAGE = 0x82;		//写页报文标识;

constexpr auto DEBUG_MODE = 1;
constexpr auto FLASH_OPERATE_WAIT_IDLE = 0;

//CheckSum  or  CRC
constexpr auto CHECK_SUM_16BIT = 1;
constexpr auto CHECK_CRC16 = 2;

//自定义
constexpr auto FILE_LEN_ERROR = -1;
constexpr auto DATA_LEN = 256;
constexpr auto ERASE_LEN = (64*1024);

constexpr auto SERIAL_STRING = "Silicon Labs CP210x USB to UART Bridge";
//constexpr auto PC_ASK = "TX21";
#define PC_ASK "TX21"
constexpr auto TX_REPLY = "ZZ";		//板子握手回复指令;

#define CHECK_MODE				CHECK_CRC16
#define CHANGE_PACKET(x)		(x/DATA_LEN)
#define ERASE_MEM(x)			(x/ERASE_LEN)

enum BURN_STATE
{
	BURN_NONE,
	BURN_HANDSHAKE,
	BURN_FIRST_BIN,
	BURN_REPLY_BL,
	BURN_ERASE,
	BURN_REPLY_ERASE,
	BURN_SECOND_BIN,
	BRUN_PROGRAM,
	BURN_REPLY_PROGRAM
};

#define THREAD_NAME		QString::number(quintptr(QThread::currentThreadId()))
#define LOG_HEAD			QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss") + QStringLiteral("--%1<<<%2(%3)>>>").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__)



