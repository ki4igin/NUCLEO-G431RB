#ifndef __SETTINGS_H
#define __SETTINGS_H

#include <stdint.h>
#include <assert.h>

#define SETTINGS_MAGIC_KEY 0x00112233

union settings
{
    struct {
        uint32_t magic_key;
        uint8_t ip_addr[4];
        uint32_t reserv0[6];
        uint32_t vibr_calibr_val[8];
        uint32_t rtd_calibr_val[8];
        uint32_t reserv1[8];
    };
    uint8_t bytes[128];    
};

extern union settings *settings;

void settings_init(void);
void settings_write(union settings *s_new);
void settings_change_ipaddr(uint32_t ipaddr_new);

static_assert(sizeof(union settings) == 128, "Err");

#endif
