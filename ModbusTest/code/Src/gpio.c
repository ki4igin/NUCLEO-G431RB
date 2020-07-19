// Includes --------------------------------------------------------------------
#include "gpio.h"

// Private Typedef -------------------------------------------------------------

// Private Macro ---------------------------------------------------------------

// Private Variables -----------------------------------------------------------

// Private Function prototypes -------------------------------------------------

// Functions -------------------------------------------------------------------
void GpioInit(void)
{
  RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;

  // Lock SWD Interfece
  GpioSetLock(GPIOA, GPIO_PIN_13 | GPIO_PIN_14);

  GpioSetMode(LED_PORT, LED_PIN, GPIO_MODE_OUTPUT);
}
