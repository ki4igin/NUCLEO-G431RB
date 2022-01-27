// Includes --------------------------------------------------------------------
#include "debug.h"
#include "uart.h"
// Private Typedef -------------------------------------------------------------

// Private Macro ---------------------------------------------------------------

// Private Variables -----------------------------------------------------------

// Private Function prototypes -------------------------------------------------

// Functions -------------------------------------------------------------------
#ifdef DEBUG
void DebugSendMessage(char *str)
{
    UsartSendStr(LPUART1, (uint8_t *)str);
}

void DebugSendArray(void *pbuf, int len)
{
    UsartSendArray(LPUART1, (uint8_t *)pbuf, (uint8_t)len);
}

void DebugSendWord(int data)
{
    UsartSendWord(LPUART1, (uint16_t)data);
}
#else
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

void _Error_Handler(char *file, int line)
{
    DebugSendMessage(file);
    DebugSendWord(line);
    while (1)
    {
    }
}

void Delay_ms(unsigned long delay)
{
    // __IO uint32_t temp = SysTick->CTRL;
    delay++;
    while (delay)
    {
        if (SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk)
        {
            delay--;
        }
    }
}