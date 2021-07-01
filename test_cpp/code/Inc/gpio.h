#ifndef __GPIO_H
#define __GPIO_H

// Includes --------------------------------------------------------------------
// #include "main.h"
#include "stm32g4_gpio.h"

// Typedef ---------------------------------------------------------------------

// Macro -----------------------------------------------------------------------

// GPIOA Pin5 - LED
#define LED_PORT GPIOA
#define LED_PIN  GPIO_PIN_5

// Variables -------------------------------------------------------------------

// Function prototypes ---------------------------------------------------------
void GpioInit(void);

// Inline Functions ------------------------------------------------------------
__STATIC_FORCEINLINE void LedOn(void)
{
  GpioOutSet(LED_PORT, LED_PIN);
}

__STATIC_FORCEINLINE void LedOff(void)
{
  GpioOutReset(LED_PORT, LED_PIN);
}

#endif
