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

static void flash_clear_err(void)
{
    FLASH->SR |= FLASH_SR_OPERR | FLASH_SR_RDERR | FLASH_SR_MISERR
               | FLASH_SR_PGAERR | FLASH_SR_PGSERR | FLASH_SR_SIZERR
               | FLASH_SR_WRPERR | FLASH_SR_FASTERR | FLASH_SR_OPTVERR
               | FLASH_SR_PROGERR;
}

static void flash_program_u64(uint32_t addr, uint64_t data)
{
    while (FLASH->SR & FLASH_SR_BSY) {
        ;
    }

    *(uint32_t *)addr = (uint32_t)data;
    __ISB();
    *(uint32_t *)(addr + 4) = (uint32_t)(data >> 32);

    while ((FLASH->SR & FLASH_SR_EOP) != FLASH_SR_EOP) {
        ;
    }
    FLASH->SR |= FLASH_SR_EOP;
}

void flash_erase_page(uint32_t page)
{
    flash_unlock();
    flash_clear_err();

    while (FLASH->SR & FLASH_SR_BSY) {
        ;
    }

    FLASH->CR &= ~FLASH_CR_PNB;
    FLASH->CR |= FLASH_CR_EOPIE | FLASH_CR_PER | (page << FLASH_CR_PNB_Pos);
    FLASH->CR |= FLASH_CR_STRT;

    while ((FLASH->SR & FLASH_SR_EOP) != FLASH_SR_EOP) {
        ;
    }
    FLASH->SR |= FLASH_SR_EOP;

    FLASH->CR &= ~(FLASH_CR_EOPIE | FLASH_CR_PER);
    flash_lock();
}

void flash_memcpy_u64(void *src, void *dst, uint32_t size)
{
    flash_unlock();
    flash_clear_err();
    FLASH->CR |= FLASH_CR_EOPIE | FLASH_CR_PG;

    uint64_t *s = src;
    uint64_t *d = dst;

    size >>= 3;
    do {
        flash_program_u64((uint32_t)d++, *s++);
    } while (--size);

    FLASH->CR &= ~(FLASH_CR_EOPIE | FLASH_CR_PG);
    flash_lock();
}
