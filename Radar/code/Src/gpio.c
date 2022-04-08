// Includes --------------------------------------------------------------------
#include "gpio.h"

// Private Typedef -------------------------------------------------------------

// Private Macro ---------------------------------------------------------------

// Private Variables -----------------------------------------------------------

// Private Function prototypes -------------------------------------------------

// Functions -------------------------------------------------------------------
void GpioInit(void)
{
  RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN | RCC_AHB2ENR_GPIOBEN;

  // Lock SWD Interfece
  GpioSetLock(GPIOA, GPIO_PIN_13 | GPIO_PIN_14);

  GpioSetMode(LEDS_GPIO_Port, LED1_Pin | LED2_Pin | LED3_Pin, GPIO_MODE_OUTPUT);

  GpioSetMode(RF_3V3_EN_GPIO_Port, RF_3V3_EN_Pin, GPIO_MODE_OUTPUT);

  GpioSetMode(PLL_CLK_EN_GPIO_Port, PLL_CLK_EN_Pin, GPIO_MODE_OUTPUT);

  // GpioSetMode(RFE_PWR1_GPIO_Port, RFE_PWR1_Pin, GPIO_MODE_OUTPUT);
  GpioSetMode(RFE_PWR_GPIO_Port, RFE_PWR1_Pin, GPIO_MODE_OUTPUT);
}
