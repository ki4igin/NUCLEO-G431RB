#include <stdint.h>

#include "settings.h"
#include "flash.h"

#define SETTINGS_PAGE_NUM      63
#define SETTINGS_PAGE_SIZE     FLASH_PAGE_SIZE
#define SETTINGS_PAGE_ADDR     flash_get_page_addr(SETTINGS_PAGE_NUM)
#define SETTINGS_PAGE_ADDR_END (SETTINGS_PAGE_ADDR + SETTINGS_PAGE_SIZE - 1)

union settings *settings = (union settings *)SETTINGS_PAGE_ADDR;

void settings_init(void)
{
    if (settings->magic_key != SETTINGS_MAGIC_KEY) {
        union settings s_default = {
            .magic_key = SETTINGS_MAGIC_KEY,
            .ip_addr = {192, 168, 0, 10},
            {0}
        };
        flash_erase_page(SETTINGS_PAGE_NUM);
        flash_memcpy_u64(&s_default, settings, sizeof(union settings));
        return;
    }

    do {
        settings++;
        if (((uint32_t)settings + sizeof(union settings) - 1) > SETTINGS_PAGE_ADDR_END) {
            break;
        }
    } while (settings->magic_key == SETTINGS_MAGIC_KEY);

    settings--;
}

void settings_write(union settings *s_new)
{
    settings++;
    if (((uint32_t)settings + sizeof(union settings) - 1) > SETTINGS_PAGE_ADDR_END) {
        flash_erase_page(SETTINGS_PAGE_NUM);
        settings = (union settings *)SETTINGS_PAGE_ADDR;
    }
    flash_memcpy_u64(s_new, settings, sizeof(union settings));
}

void settings_change_ipaddr(uint32_t ipaddr_new)
{
    union settings s_new = *settings;
    *(uint32_t *)s_new.ip_addr = ipaddr_new;
    settings_write(&s_new);
}
