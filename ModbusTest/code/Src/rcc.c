// Includes --------------------------------------------------------------------
#include "rcc.h"
#include "main.h"

// Private Typedef -------------------------------------------------------------

// Private Macro ---------------------------------------------------------------

// Private Variables -----------------------------------------------------------

// Private Function prototypes -------------------------------------------------

// Functions -------------------------------------------------------------------
void RccInit(void)
{
  MODIFY_REG(FLASH->ACR, FLASH_ACR_LATENCY, FLASH_ACR_LATENCY_7WS);
  if ((FLASH->ACR & FLASH_ACR_LATENCY) != FLASH_ACR_LATENCY_7WS)
  {
    Error_Handler();
  }
  MODIFY_REG(PWR->CR1, PWR_CR1_VOS, PWR_CR1_VOS_0);
  RCC->CR |= RCC_CR_HSEON;

  // Wait till HSE is ready
  while ((RCC->CR & RCC_CR_HSERDY) != RCC_CR_HSERDY)
  {
  }

  RccPllConfigDiv(RCC_PLLSOURCE_HSE,
                  RCC_PLLM_3,
                  RCC_PLLN_18,
                  RCC_PLLR_2,
                  RCC_PLLQ_2,
                  RCC_PLLP_2);

  RCC->PLLCFGR |= RCC_PLLCFGR_PLLREN;
  RCC->CR |= RCC_CR_PLLON;

  // Wait till PLL is ready
  while ((RCC->CR & RCC_CR_PLLRDY) != RCC_CR_PLLRDY)
  {
    // code
  }

  MODIFY_REG(RCC->CFGR, RCC_CFGR_SW, RCC_CFGR_SW_PLL);
  MODIFY_REG(RCC->CFGR, RCC_CFGR_HPRE, RCC_CFGR_HPRE_DIV1);
  // Wait till System clock is ready
  while ((RCC->CFGR & RCC_CFGR_SWS_PLL) != RCC_CFGR_SWS_PLL)
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



  MODIFY_REG(RCC->CFGR,
             RCC_CFGR_HPRE | RCC_CFGR_PPRE1 | RCC_CFGR_PPRE2,
             RCC_CFGR_HPRE_DIV1 | RCC_CFGR_PPRE1_DIV1 | RCC_CFGR_PPRE2_DIV1);
}

void SysTickInit(void)
{
  SysTick->LOAD = SystemCoreClock / 8 / 1000;
  SysTick->CTRL &= ~SysTick_CTRL_CLKSOURCE_Msk;
  SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
}
