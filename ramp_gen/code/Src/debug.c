// Includes --------------------------------------------------------------------
#include "debug.h"
#include "usart_ex.h"
#include "stm32g4xx.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#define USE_UART
// #define USE_USB

#define DEBUG_UART     LPUART1
#define DEBUG_BUF_SIZE 100

#ifdef DEBUG

char debug_buf[DEBUG_BUF_SIZE];

void debug_printf(const char *fmt, ...)
{
    va_list argp;
    va_start(argp, fmt);

    uint32_t len = vsprintf(debug_buf, fmt, argp);
#ifdef USE_UART
    uart_send_array(DEBUG_UART, (uint8_t *)debug_buf, len);
#endif
#ifdef USE_USB
    CDC_Transmit_FS((uint8_t *)debug_buf, len);
#endif

    va_end(argp);
}

#else
void debug_printf(const char *fmt, ...)
{
}

void DebugSendMessage(char *str)
{
    (void)str;
}

void DebugSendArray(void *pbuf, int len)
{
    (void)pbuf;
    (void)len;
}

void DebugSendWord(int data)
{
    (void)data;
}
#endif

void _error_handler(const char *file, uint32_t line)
{
    __disable_irq();
    debug_printf("Error: %s, %d", file, line);
    while (1) {
        delay_ms(300);
        // led_toggle();
    }
}

void delay_ms(uint64_t delay)
{
    // __IO uint32_t temp = SysTick->CTRL;
    delay++;
    while (delay) {
        if (SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) {
            delay--;
        }
    }
}
