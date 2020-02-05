#ifndef __GPIO_H
#define __GPIO_H

// Includes --------------------------------------------------------------------
#include "main.h"
#include "stm32g4xx.h"

// Typedef ---------------------------------------------------------------------

// Macro -----------------------------------------------------------------------


// GPIOA Pin5 - LED
#define LED_PORT GPIOA
#define LED_PIN GPIO_BSRR_BS5

// Variables -------------------------------------------------------------------

// Function prototypes ---------------------------------------------------------
void GpioInit(void);

// Inline Functions ------------------------------------------------------------
__STATIC_FORCEINLINE void GpioOutSet(GPIO_TypeDef *port, uint32_t pin)
{
  port->BSRR |= pin;
}

__STATIC_FORCEINLINE void GpioOutReset(GPIO_TypeDef *port, uint32_t pin)
{
  port->BRR |= pin;
}

__STATIC_FORCEINLINE void LedOn(void)
{
  GpioOutSet(LED_PORT, LED_PIN);
}

__STATIC_FORCEINLINE void LedOff(void)
{
  GpioOutReset(LED_PORT, LED_PIN);
}


#endif
