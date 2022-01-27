// Includes --------------------------------------------------------------------
#include "main.h"
#include "gpio.h"
#include "uart.h"
#include "rcc.h"
#include "tim.h"
#include "ADF4159.h"
#include "debug.h"

// Private Typedef -------------------------------------------------------------

// Private Macro ---------------------------------------------------------------

// Private Variables -----------------------------------------------------------

// Private Function prototypes git -------------------------------------------------
void SystemClock_Config(void);
void Delay_ms(uint32_t delay);
void CmdWork(uint32_t cmd);

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
    DebugSendMessage("Init Complete\n");
    Delay_ms(1000);
    LedAllOff();

    ADF4159_Init();

    LL_TIM_EnableIT_UPDATE(TIM6);
    LL_TIM_EnableCounter(TIM6);

    // Infinite loop
    while (1)
    {
    }
}

void CmdWork(uint32_t cmd)
{
    switch (__REV(cmd))
    {
        case 0x626c696b:  // blik
            break;
        case 0x706c7772:  // plwr
            break;
        case 0x71776572:  // qwer
            NVIC_SystemReset();
            break;
        default:
            DebugSendArray(&cmd, sizeof(cmd));
            break;
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
