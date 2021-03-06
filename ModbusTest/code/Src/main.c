// Includes --------------------------------------------------------------------
#include "main.h"
#include "gpio.h"
#include "uart.h"
#include "rcc.h"
#include "tim.h"
#include "modbus.h"
// Private Typedef -------------------------------------------------------------

// Private Macro ---------------------------------------------------------------

// Private Variables -----------------------------------------------------------


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
  ModBusInit();
  UsartSendStrIT(LPUART1, (uint8_t*)"\nInit Complete\n");

  // Infinite loop
  while (1)
  {
    ModBusProcess();
    LedOn();
    Delay_ms(1000);
    LedOff();
    Delay_ms(1000);
  }
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
