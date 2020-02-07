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
  GPIOA1->MODER.PIN00 = OUTPUT;
  GPIOA1->MODER.PIN01 = OUTPUT;
  GPIOA1->MODER.PIN02 = OUTPUT;
  GPIOA1->MODER.PIN03 = OUTPUT;
  GPIO_SetPinMode(GPIOA, GPIO_PIN_10, GPIO_MODE_OUTPUT);
  GPIO_SetPinMode(GPIOA, GPIO_PIN_11, GPIO_MODE_OUTPUT);
  GPIO_SetPinMode(GPIOA, GPIO_PIN_12, GPIO_MODE_OUTPUT);
  GPIO_SetPinMode(GPIOA, GPIO_PIN_13, GPIO_MODE_OUTPUT);

  MODIFY_REG(LED_PORT->MODER,
             GPIO_MODER_MODE4_Msk | GPIO_MODER_MODE5_Msk |
                 GPIO_MODER_MODE6_Msk | GPIO_MODER_MODE7_Msk,
             GPIO_MODER_MODE4_0 | GPIO_MODER_MODE5_0 |
                 GPIO_MODER_MODE6_0 | GPIO_MODER_MODE7_0);
  // LED_PORT->MODER = (LED_PORT->MODER & ~(0b11 << (2 * LED_PIN_Pos))) | (GPIO_MODE_OUTPUT << (2 * LED_PIN_Pos));
}
