#include "stm32g4xx.h"

#define FLASH_KEY1 0x45670123U
#define FLASH_KEY2 0xCDEF89ABU

static void flash_unlock(void)
{
    if (FLASH->CR & FLASH_CR_LOCK) {
        FLASH->KEYR = FLASH_KEY1;
        FLASH->KEYR = FLASH_KEY2;
    }
}

static void flash_lock(void)
{
    FLASH->CR |= FLASH_CR_LOCK;
}

static void flash_program_u64(uint32_t addr, uint64_t data)
{
    while (FLASH->SR & FLASH_SR_BSY) {
        ;
    }

    FLASH->CR |= FLASH_CR_PG;
    *(uint32_t *)addr = (uint32_t)data; 
    __ISB();
    *(uint32_t *)(addr + 4) = (uint32_t)(data >> 32); 

    while (FLASH->SR & FLASH_SR_BSY) {
        ;
    }
}

void flash_erase_page(uint32_t page)
{
    flash_unlock();

    while (FLASH->SR & FLASH_SR_BSY) {
        ;
    }

    FLASH->CR &= ~FLASH_CR_PNB;
    FLASH->CR |= FLASH_CR_PER | (page << FLASH_CR_PNB_Pos);
    FLASH->CR |= FLASH_CR_STRT;

    while (FLASH->SR & FLASH_SR_BSY) {
        ;
    }

    flash_lock();
}

void flash_memcpy_u64(void *src, void *dst, uint32_t size)
{
    flash_unlock();

    uint64_t *s = src;
    uint64_t *d = dst;

    size >>= 3;
    do {
        flash_program_u32((uint32_t)d++, *s++);
    } while (size--);

    flash_lock();
}
