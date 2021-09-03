#pragma once
#define MCUID						0x00
#define RUN510						0x01
//测试项
#define DPU							0x0a
#define DDR							0X0b
#define RTC							0x0c	
#define Timer1_0					0x0d
#define DMA							0x0e
#define USI1_SPI					0x0f
#define USI2_UART					0x10
#define UART1						0x11
#define OTPC						0x12
#define I2C0_1_2					0x13
#define ADC							0x14
#define SDIO0						0x15
#define SDIO1						0x16
#define GMAC						0x17
#define CRYPTO						0x18
#define VPU							0x19
#define PWM							0x1a
#define I2S							0x1b
#define Mailbox						0x1c
#define RNE							0x1d
#define _3D							0x1e
#define AMR							0x1f
#define USB2_0						0x20
#define MIPI_TX_USB3_0				0x21
#define WDT							0x22
#define SMU							0x23

#define GETPOWER					0xfd   //获取功耗
#define UPGRADE						0xfe   //升级
#define OVER						0xff   //结束断电
//上位机向下位机发送命令
typedef struct
{
	unsigned char SyncWord[2];
	unsigned char Msgid;
	unsigned char Size[2];
	unsigned char CheckSum;
}send_packet;

//上位机收到ACK
typedef struct
{
	unsigned char SyncWord[2];
	unsigned char Msgid;
	unsigned char Size[2];
	//char Result;
	unsigned char *data;     //data包含了result和信息
	unsigned char checkSum;
}rec_ack;


void send_info(char *packet, unsigned char cmd, unsigned short size, unsigned char check);  //上位机到下位机buf
void rec_info(char *packet);
void store_le_uint16(unsigned char *addr, unsigned short value);
unsigned short reverse_uint16(unsigned char *uint16_value);          /* big endian */