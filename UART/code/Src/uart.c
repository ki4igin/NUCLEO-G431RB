// Includes --------------------------------------------------------------------
#include "uart.h"
#include "stm32g4xx.h"
// Private Typedef -------------------------------------------------------------

// Private Macro ---------------------------------------------------------------
#define LPUARD_RX_PIN GPIO_BSRR_BS3
#define LPUARD_TX_PIN GPIO_BSRR_BS2
#define LPUARD_PORT   GPIOA
// Private Variables -----------------------------------------------------------

// Private Function prototypes -------------------------------------------------

// Functions -------------------------------------------------------------------
void LPUartInit(void)
{
  RCC->APB1ENR2 |= RCC_APB1ENR2_LPUART1EN;
  RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
  

  //   GPIO Configuration
  //   PA2  ------> LPUART1_TX
  //   PA3  ------> LPUART1_RX
  GPIOA->MODER |= GPIO_MODER_MODE0_1;
}
