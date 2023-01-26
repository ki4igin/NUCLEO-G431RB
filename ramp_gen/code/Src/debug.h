#ifndef __DEBUG_H
#define __DEBUG_H

#include <stdint.h>
#include "stm32g4xx.h"

// #define Error_Handler error_handler

#define error_handler() _error_handler(__FILE__, __LINE__)

void debug_printf(const char *fmt, ...);
void _error_handler(const char *file, uint32_t line);
void delay_ms(uint64_t delay);

inline static void debug_timer_init(void)
{
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
    DWT->CYCCNT = 0;
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
}

static uint32_t t;

inline static void debug_timer_start(void)
{
    t = DWT->CYCCNT;
}

inline static uint32_t debug_timer_stop(void)
{
    return DWT->CYCCNT - t;
}

#endif
