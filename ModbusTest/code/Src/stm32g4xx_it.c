
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32g4xx_it.h"
#include "stm32g4xx.h"
#include "uart.h"
#include "tim.h"

/******************************************************************************/
/*           Cortex-M4 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  while (1)
  {
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  while (1)
  {
  }
}

/**
  * @brief This function handles Prefetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  while (1)
  {
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  while (1)
  {
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
}

/******************************************************************************/
/* STM32G4xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32g4xx.s).                    */
/******************************************************************************/
// void USART1_IRQHandler(void)
// {
//   if ((USART1->ISR & USART_ISR_RXNE) == USART_ISR_RXNE)
//   {
//     UsartTransmitByte(LPUART1, (uint8_t)USART1->RDR);
//   }
// }

void LPUART1_IRQHandler(void)
{
  if (((LPUART1->ISR & USART_ISR_RXNE) == USART_ISR_RXNE) && ((LPUART1->CR1 & USART_CR1_RXNEIE) == USART_CR1_RXNEIE))
  {
    Lpuart1Rx_Callback();
  }
  if (((LPUART1->ISR & USART_ISR_TC) == USART_ISR_TC) && ((LPUART1->CR1 & USART_CR1_TCIE) == USART_CR1_TCIE))
  {
    LPUART1->ICR |= USART_ICR_TCCF;
  }
  if (((LPUART1->ISR & USART_ISR_TXE) == USART_ISR_TXE) && ((LPUART1->CR1 & USART_CR1_TXEIE) == USART_CR1_TXEIE))
  {
    Lpuart1Tx_Callback();
  }
  if ((LPUART1->ISR & USART_ISR_ORE) == USART_ISR_ORE)
  {
    LPUART1->ICR |= USART_ICR_ORECF;
  }
}
/**
  * @brief This function handles TIM4 global interrupt, DAC1 and DAC3 channel underrun error interrupts.
  */
void TIM4_IRQHandler(void)
{
  if (LL_TIM_IsActiveFlag_UPDATE(TIM4))
  {
    LL_TIM_ClearFlag_UPDATE(TIM4);
    Tim4Update_Callback();
  }
  if (LL_TIM_IsActiveFlag_CC1(TIM4))
  {
    LL_TIM_ClearFlag_CC1(TIM4);
    Tim4CC1_Callback();
  }
}

// void TIM2_IRQHandler(void)
// {
//   if (LL_TIM_IsActiveFlag_UPDATE(TIM2))
//   {
//     LL_TIM_ClearFlag_UPDATE(TIM2);
//     Tim2Update_Callback();
//   }
// }
