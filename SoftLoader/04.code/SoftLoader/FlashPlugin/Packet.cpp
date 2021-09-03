#include "Packet.h"
#include <QtEndian>

void PC_TX_ERASE_CMD::readyData()
{
	head.SyncWord = qFromBigEndian(head.SyncWord);
	head.MsgSize = qFromBigEndian(head.MsgSize);
	block_addr = qFromBigEndian(block_addr);
	checksum = qFromBigEndian(checksum);
}

void PC_TX_WRITE_PAGE::readyData()
{
	head.SyncWord = qFromBigEndian(head.SyncWord);
	head.MsgSize = qFromBigEndian(head.MsgSize);
	page_addr = qFromBigEndian(page_addr);
	checksum = qFromBigEndian(checksum);
}

void TX_PC_REPLY::readyData()
{
	head.SyncWord = qFromBigEndian(head.SyncWord);
	head.MsgSize = qFromBigEndian(head.MsgSize);
	checksum = qFromBigEndian(checksum);
}
