// Includes --------------------------------------------------------------------
#include "main.h"
#include "gpio.h"
#include "uart.h"
#include "rcc.h"
#include "tim.h"

// Private Typedef -------------------------------------------------------------

// Private Macro ---------------------------------------------------------------

// Private Variables -----------------------------------------------------------

// Private Function prototypes git -------------------------------------------------
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
    // TIM2_Init();    
    TIM6_Init();
    LPUartInit();
    UsartTransmitStr(LPUART1, (uint8_t *)"Init Complete\n");
    LedAllOff();

    LL_TIM_EnableIT_UPDATE(TIM6);
    LL_TIM_EnableCounter(TIM6);

    // Infinite loop
    while (1)
    {
    }
}

void Tim2Update_Callback(void)
{
    // static uint16_t cnt;
    // UsartTransmitByte(LPUART1, (uint8_t)(cnt >> 8));
    // UsartTransmitByte(LPUART1, (uint8_t)cnt);
    // cnt++;
}

void Tim6Update_Callback(void)
{
    // GpioOutToggle(LEDS_GPIO_Port, LED2_Pin);
    // UsartTransmitStr(LPUART1, (uint8_t *)"Init Complete\n");
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
        LedAllOn();
        Delay_ms(300);
        LedAllOff();
        Delay_ms(300);
    }
}
