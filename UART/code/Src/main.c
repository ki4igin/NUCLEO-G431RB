// Includes --------------------------------------------------------------------
#include "main.h"
#include "stm32g4xx.h"
#include "gpio.h"

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
  SET_BIT(RCC->APB2ENR, RCC_APB2ENR_SYSCFGEN | RCC_APB1ENR1_PWREN);
  NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

  // System interrupt init

  // Disable the internal Pull-Up in Dead Battery pins of UCPD peripheral

  CLEAR_BIT(PWR->CR3, PWR_CR3_UCPD_DBDIS);
  // Configure the system clock
  SystemClock_Config();
  GpioInit();

  // Initialize all configured peripherals

  // Infinite loop
  while (1)
  {
    LedOn();
    Delay_ms(1000);
    LedOff();
    Delay_ms(1000);
  }
}

void SystemClock_Config(void)
{
  MODIFY_REG(FLASH->ACR, FLASH_ACR_LATENCY, FLASH_ACR_LATENCY_7WS);
  if (READ_BIT(FLASH->ACR, FLASH_ACR_LATENCY) != FLASH_ACR_LATENCY_7WS)
  {
    Error_Handler();
  }
  MODIFY_REG(PWR->CR1, PWR_CR1_VOS, PWR_CR1_VOS_0);
  SET_BIT(RCC->CR, RCC_CR_HSEON);

  // Wait till HSE is ready
  while (READ_BIT(RCC->CR, RCC_CR_HSERDY) != RCC_CR_HSERDY)
  {
  }

  MODIFY_REG(RCC->PLLCFGR,
             RCC_PLLCFGR_PLLSRC | RCC_PLLCFGR_PLLM |
                 RCC_PLLCFGR_PLLN | RCC_PLLCFGR_PLLR,
             RCC_PLLCFGR_PLLSRC_HSE | 4 << RCC_PLLCFGR_PLLM_Pos |
                 50 << RCC_PLLCFGR_PLLN_Pos | 2 << RCC_PLLCFGR_PLLR_Pos);
  SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLPEN);
  SET_BIT(RCC->CR, RCC_CR_PLLON);

  // Wait till PLL is ready
  while (!(RCC->CR & RCC_CR_PLLRDY))
  {
    // code
  }

  MODIFY_REG(RCC->CFGR, RCC_CFGR_SW, RCC_CFGR_SW_PLL);
  MODIFY_REG(RCC->CFGR, RCC_CFGR_HPRE, RCC_CFGR_HPRE_DIV2);
  // Wait till System clock is ready
  while (!(RCC->CFGR & RCC_CFGR_SWS_PLL))
  {
    // code
  }

  // Insure 1�s transition state at intermediate medium speed clock based on DWT
  CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
  DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
  DWT->CYCCNT = 0;
  while (DWT->CYCCNT < 100)
  {
  }

  SystemCoreClockUpdate();

  SysTick->LOAD = SystemCoreClock /8 / 1000;
  SysTick->CTRL &= ~SysTick_CTRL_CLKSOURCE_Msk;
  SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;

  MODIFY_REG(RCC->CFGR,
             RCC_CFGR_HPRE | RCC_CFGR_PPRE1 | RCC_CFGR_PPRE2,
             RCC_CFGR_HPRE_DIV1 | RCC_CFGR_PPRE1_DIV1 | RCC_CFGR_PPRE2_DIV1);
}

void Tim6Update_Callback(void)
{
}

void Delay_ms(uint32_t delay)
{
  __IO uint32_t temp = SysTick->CTRL;
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
    // code
  }
}
