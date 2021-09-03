#include "common.h"

void store_le_uint32(uint8_t *addr, uint32_t value)     /* big endian */
{
    addr[0] = value >> 24;
    addr[1] = (value >> 16) & 0xff;
    addr[2] = (value >> 8) & 0xff;
    addr[3] = value & 0xff;
}
//将分辨率转为两字节，按大端序上面和下面一个意思
void store_le_uint16(uint8_t *addr, uint16_t value)      /* big endian */
{
    addr[0] = value >> 8;
    addr[1] = value & 0xff;
}

uint32_t reverse_uint32(uint8_t *uint32_value)          /* big endian */
{
    return  uint32_value[0] << 24 |
            uint32_value[1] << 16 |
            uint32_value[2] << 8  |
            uint32_value[3];
}