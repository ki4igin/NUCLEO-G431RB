#include <stdint.h>

#include "settings.h"
#include "flash.h"

#define SETTINGS_PAGE_NUM  127
#define SETTINGS_PAGE_ADDR flash_get_page_addr(SETTINGS_PAGE_NUM)

union settings *settings = (union settings *)SETTINGS_PAGE_ADDR;

void settings_init(void)
{
    union settings *s = (union settings *)SETTINGS_PAGE_ADDR;

    if (s->magic_key != SETTINGS_MAGIC_KEY) {
        union settings s_default = {
            .magic_key = SETTINGS_MAGIC_KEY,
            .ip_addr = {192, 168, 0, 10},
            {0}
        };
        settings_write(&s_default);
    }

    while (s->magic_key == SETTINGS_MAGIC_KEY) {
        s++;
    }

    s--;

    settings = s;
}

void settings_write(union settings *s_new)
{
    settings++;
    flash_memcpy_u64(s_new, &settings, sizeof(union settings));
}

void settings_change_ipaddr(uint8_t ipaddr_new[4])
{
    union settings s_new = *settings;
    *(uint32_t*)s_new.ip_addr = *(uint32_t*)ipaddr_new;
    settings_write(&s_new);
}
