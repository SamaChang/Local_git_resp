#pragma once
//TX231->PC
#define MSG_ACK_BL_START		0x01
#define MSG_ACK_ERASE_OK		0x02
#define MSG_ACK_PAGE_PROGRAM_OK 0x03
#define MSG_ACK_CHECKSUM_ERROR  0x04
#define MSG_ACK_ERASE_CHIP_OK   0x05

#define DEBUG_MODE				1

#define FLASH_OPERATE_WAIT_IDLE 0

//CheckSum  or  CRC
#define CHECK_SUM_16BIT			1
#define CHECK_CRC16				2
#define CHECK_MODE				CHECK_CRC16

//×Ô¶¨Òå
#define FILE_LEN_ERROR			-1
#define DATA_LEN				256
#define CHANGE_PACKET(x)		(x/DATA_LEN)
#define ERASE_LEN				(64*1024)
#define ERASE_MEM(x)			(x/ERASE_LEN)

//PC->TX231
#define MSG_SEDN_ERASE			0x81
#define MSG_SEND_ERASE_CHIP		0x85
#define MSG_SEND_WRITE_PAGE		0x82


