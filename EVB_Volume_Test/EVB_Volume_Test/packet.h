#pragma once
//#define DDR							0x1
//#define DMA							0x1
//#define OTPC						0x1
//#define SDIO0_EMMC					0x1
//#define SDIO1_SD					0x1
//#define USI0_UART					0x1
//#define USI2_UART					0x1
//#define CK805_UART					0x1
//#define CK804_JTAG					0x1
//#define CK805_JTAG					0x1
//#define QSPI						0x1
//#define SPIFLASH					0x1
//#define MAILBOX						0x1
//#define CRYPTO						0x1
//#define VPU							0x1
//#define GMAC						0x1
//#define _3D							0x1
//#define AIE							0x1
//#define TIMER						0x1
//#define IIC3_RTC					0x1
//#define IIC1_IIC2_MIPI_RX0_1_ISP	0x1
//#define IIC2_MIPI_RX2_XC7022		0x1
//#define WDT							0x1
//#define SMU							0x1
//#define USB2						0x1
//#define IIC0_IIS0_1_CODEC			0x1
//#define MIPI_TX						0x1
//#define DPU							0x1
//#define ADC							0x1


typedef struct 
{
	unsigned char Syn[2];
	unsigned char Msd;
	unsigned char Size[2];
	unsigned char checksum;
}sendInfo;

void send_msg(char *packet, unsigned char cmd, unsigned short size, unsigned char check);
void store_le_uint16(unsigned char *addr, unsigned short value);
unsigned short reverse_uint16(unsigned char *uint16_value);
