#pragma once

#include "def.h"

void store_le_uint32(uint8_t *addr, uint32_t value);     /* big endian */
void store_le_uint16(uint8_t *addr, uint16_t value);     /* big endian */
uint32_t reverse_uint32(uint8_t *uint32_value);          /* big endian */