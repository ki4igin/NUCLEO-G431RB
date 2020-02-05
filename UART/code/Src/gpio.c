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
  MODIFY_REG(LED_PORT->MODER, GPIO_MODER_MODE5_Msk, GPIO_MODER_MODE5_0);
}
