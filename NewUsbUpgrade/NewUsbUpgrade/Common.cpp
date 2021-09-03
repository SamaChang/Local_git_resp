#include "Common.h"
//#include <Windows.h>
#include <windows.h>
#pragma comment(lib, "wsock32.lib")

Common::Common(QObject *parent)
	: QObject(parent)
{
}

Common::~Common()
{
}

void Common::store_uint32(uint8_t *addr, uint32_t value_1)   /*small endian*/
{
	uint32_t value = htonl(value_1);
	addr[0] = value >> 24;
	addr[1] = (value >> 16) & 0xff;
	addr[2] = (value >> 8) & 0xff;
	addr[3] = value & 0xff;
}

void Common::add_table(uint8_t *addr, uint32_t value, uint32_t res)
{
	para_struct *para = (para_struct *)addr;
	para->magic[0] = 'Q';
	para->magic[1] = 'W';
	para->magic[2] = 'Z';
	para->magic[3] = 'N';
	store_uint32(para->offset, value);
	store_uint32(para->res, res);
}

//小端保存
void Common::add_bin_head(uint32_t addr, uint32_t bin_len, uint32_t tmp_res, uint8_t *data)
{
	bin_head *head = (bin_head *)data;
	head->magic[0] = 'Q';
	head->magic[1] = 'W';
	head->magic[2] = 'Z';
	head->magic[3] = 'N';

	/****************小端**********************/
	store_uint32(head->load_addr, addr);
	store_uint32(head->img_len, bin_len);
	store_uint32(head->res, tmp_res);
	/*****************************************/

	/****************大端************************/
	//store_le_uint32(head->load_addr, addr);
	//store_le_uint32(head->img_len, bin_len);
	//store_le_uint32(head->res, tmp_res);
	/***************************************/
}
