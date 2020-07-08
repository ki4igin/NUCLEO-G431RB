// Includes --------------------------------------------------------------------
#include "main.h"
#include "gpio.h"
#include "uart.h"
#include "rcc.h"
#include "tim.h"
#include "spi.h"

// Private Typedef -------------------------------------------------------------

// Private Macro ---------------------------------------------------------------

// Private Variables -----------------------------------------------------------
char *str    = "12345";
char  str1[] = "12345";
// Private Function prototypes -------------------------------------------------
void SystemClock_Config(void);
void Delay_ms(uint32_t delay);

// Functions -------------------------------------------------------------------
int main(void)
{
    // MCU Configuration
    // Reset of all peripherals, Initializes the Flash interface and the Systick.    
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
    RCC->APB1ENR1 |= RCC_APB1ENR1_PWREN;
    NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

    // System interrupt init

    // Disable the internal Pull-Up in Dead Battery pins of UCPD peripheral

    PWR->CR3 &= ~PWR_CR3_UCPD_DBDIS;
    // Configure the system clock
    RccInit();
    SysTickInit();
    // Initialize all configured peripherals
    GpioInit();
    TIM2_Init();
    LPUartInit();
    Spi2Init();
    Spi3Init();
    UsartTransmitStr(LPUART1, (uint8_t *)"Init Complete\n");

    LL_SPI_Enable(SPI2);
    LL_SPI_Enable(SPI3);
    while (!LL_SPI_IsActiveFlag_TXE(SPI2))
    {
        /* code */
    }    
    LL_SPI_TransmitData16(SPI2, 'A');
    while (!LL_SPI_IsActiveFlag_RXNE(SPI3))
    {
        /* code */
    }
    uint16_t data = LL_SPI_ReceiveData16(SPI3);
    UsartTransmitByte(LPUART1, data);
    UsartTransmitByte(LPUART1, '\n');
    LL_SPI_Disable(SPI2);
    LL_SPI_Disable(SPI3);
    LL_SPI_SetTransferDirection(SPI2, LL_SPI_HALF_DUPLEX_RX);
    LL_SPI_SetTransferDirection(SPI3, LL_SPI_HALF_DUPLEX_TX);
    LL_SPI_TransmitData16(SPI3, 'C');    
    LL_SPI_Enable(SPI3);
    // for (uint16_t i = 0; i < 60000; i++)
    // {
    //     __asm("nop");
    // }
    LL_SPI_Enable(SPI2);
    
    while (!LL_SPI_IsActiveFlag_RXNE(SPI2))
    {
        /* code */
    }
    LL_SPI_Disable(SPI2);
    LL_SPI_Disable(SPI3);
    data = LL_SPI_ReceiveData16(SPI2);
    UsartTransmitByte(LPUART1, data);
    UsartTransmitByte(LPUART1, '\n');

    //    LL_TIM_EnableIT_UPDATE(TIM2);
    //    LL_TIM_EnableCounter(TIM2);

    // Infinite loop
    while (1)
    {
        
        LedOn();
        Delay_ms(1000);
        LedOff();
        Delay_ms(1000);
    }
}

void Tim2Update_Callback(void)
{
    static uint16_t cnt;
    UsartTransmitByte(LPUART1, (uint8_t)(cnt >> 8));
    UsartTransmitByte(LPUART1, (uint8_t)cnt);
    cnt++;
}

void Tim6Update_Callback(void)
{
}

void Delay_ms(uint32_t delay)
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

void Error_Handler(void)
{
    while (1)
    {
        LedOn();
        Delay_ms(300);
        LedOff();
        Delay_ms(300);
    }
}
