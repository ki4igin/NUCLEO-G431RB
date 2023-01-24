#ifndef __FLASH_H
#define __FLASH_H

#include <stdint.h>
#include "assert.h"

#define FLASH_PAGE_SIZE (4 * 1024)
#define FLASH_BASE_ADDR 0x08000000
#define flash_get_page_addr(_page) (FLASH_BASE_ADDR + (_page * FLASH_PAGE_SIZE))

void flash_memcpy_u64(void *src, void *dst, uint32_t size);
void flash_erase_page(uint32_t page);

#endif
