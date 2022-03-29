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

    GpioOutSet(RF_3V3_EN_GPIO_Port, RF_3V3_EN_Pin);
    GpioOutSet(PLL_CLK_EN_GPIO_Port, PLL_CLK_EN_Pin);

    // Infinite loop
    while (1)
    {
        static uint16_t timaut_cnt = 0;
        if (READ_BIT(LPUART1->ISR, USART_ISR_RXFT) == (USART_ISR_RXFT))
        {
            timaut_cnt    = 0;
            uint32_t cmd  = 0;
            uint8_t* pcmd = (uint8_t*)&cmd;
            for (uint32_t i = 0; i < 4; i++)
            {
                *pcmd++ = LPUART1->RDR;
            }
            CmdWork(cmd);
        }
        if (READ_BIT(LPUART1->ISR, USART_ISR_RXNE) == (USART_ISR_RXNE))
        {
            timaut_cnt++;
        }
        if (timaut_cnt >= 9999)
        {
            while (READ_BIT(LPUART1->ISR, USART_ISR_RXNE) == (USART_ISR_RXNE))
            {
                volatile uint8_t temp = LPUART1->RDR;
                (void)temp;
            }
            timaut_cnt = 0;
        }
        
    }
}

void CmdWork(uint32_t cmd)
{
    static uint8_t isPLLData = 0;

    if (isPLLData)
    {
        DebugSendArray(&cmd, sizeof(cmd));
        ADF4159_WriteReg(cmd);
        isPLLData = 0;
    }
    else
    {
        switch (__REV(cmd))
        {
            case 0x626c696b:  // blik
                Led1On();
                Delay_ms(200);
                LedAllOff();
                Led2On();
                Delay_ms(200);
                LedAllOff();
                Led3On();
                Delay_ms(200);
                LedAllOff();
                break;
            case 0x706c7772:  // plwr
                isPLLData = 1;
                break;
            case 0x71776572:  // qwer
                NVIC_SystemReset();
                break;
            default:
                DebugSendArray(&cmd, sizeof(cmd));
                break;
        }
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
