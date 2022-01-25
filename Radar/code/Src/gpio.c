// Includes --------------------------------------------------------------------
#include "gpio.h"

// Private Typedef -------------------------------------------------------------

// Private Macro ---------------------------------------------------------------

// Private Variables -----------------------------------------------------------

// Private Function prototypes -------------------------------------------------

// Functions -------------------------------------------------------------------
void GpioInit(void)
{
  RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;

  // Lock SWD Interfece
  GpioSetLock(GPIOA, GPIO_PIN_13 | GPIO_PIN_14);

  GpioSetMode(LEDS_GPIO_Port, LED1_Pin | LED2_Pin | LED3_Pin, GPIO_MODE_OUTPUT);
}
