// Includes --------------------------------------------------------------------
#include "gpio.h"

// Private Typedef -------------------------------------------------------------

// Private Macro ---------------------------------------------------------------

// Private Variables -----------------------------------------------------------

// Private Function prototypes -------------------------------------------------

// Functions -------------------------------------------------------------------
void GpioInit(void)
{
  RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN | RCC_AHB2ENR_GPIOBEN |
                  RCC_AHB2ENR_GPIOFEN | RCC_AHB2ENR_GPIOGEN;

  // Lock SWD Interfece
  GpioSetLock(SWD_Port, SWDIO_Pin | SWCLK_Pin);

  // RCC_MCO
  GpioSetMode(RCC_MCO_Port, RCC_MCO_Pin, GPIO_MODE_ALTERNATE);
  GpioSetOutType(RCC_MCO_Port, RCC_MCO_Pin, GPIO_OUTPUT_PUSHPULL);
  GpioSetSpeed(RCC_MCO_Port, RCC_MCO_Pin, GPIO_SPEED_HIGH);
  GpioSetPull(RCC_MCO_Port, RCC_MCO_Pin, GPIO_PULL_NO);
  GpioSetAF(RCC_MCO_Port, RCC_MCO_Pin, GPIO_AF_0);

  // DDS_CS
  GpioOutSet(DDS_CS_Port, DDS_CS_Pin);
  GpioSetMode(DDS_CS_Port, DDS_CS_Pin, GPIO_MODE_OUTPUT);
  GpioSetSpeed(DDS_CS_Port, DDS_CS_Pin, GPIO_SPEED_VERYHIGH);
  GpioSetOutType(DDS_CS_Port, DDS_CS_Pin, GPIO_OUTPUT_PUSHPULL);
  GpioSetPull(DDS_CS_Port, DDS_CS_Pin, GPIO_PULL_NO);

  // DDS_RESET
  GpioOutSet(DDS_RESET_Port, DDS_RESET_Pin);
  GpioSetMode(DDS_RESET_Port, DDS_RESET_Pin, GPIO_MODE_OUTPUT);
  GpioSetSpeed(DDS_RESET_Port, DDS_RESET_Pin, GPIO_SPEED_LOW);
  GpioSetOutType(DDS_RESET_Port, DDS_RESET_Pin, GPIO_OUTPUT_PUSHPULL);
  GpioSetPull(DDS_RESET_Port, DDS_RESET_Pin, GPIO_PULL_NO);

  // DDS_TRIGGER
  GpioSetMode(DDS_TRIGGER_Port, DDS_TRIGGER_Pin, GPIO_MODE_INPUT);
  GpioSetPull(DDS_TRIGGER_Port, DDS_TRIGGER_Pin, GPIO_PULL_NO);

  // LED
  GpioOutReset(LED_Port, LED_Pin);
  GpioSetMode(LED_Port, LED_Pin, GPIO_MODE_OUTPUT);
  GpioSetSpeed(LED_Port, LED_Pin, GPIO_SPEED_LOW);
  GpioSetOutType(LED_Port, LED_Pin, GPIO_OUTPUT_PUSHPULL);
  GpioSetPull(LED_Port, LED_Pin, GPIO_PULL_NO);

  // VEN_TRX
  GpioOutReset(VEN_TRX_Port, VEN_TRX_Pin);
  GpioSetMode(VEN_TRX_Port, VEN_TRX_Pin, GPIO_MODE_OUTPUT);
  GpioSetSpeed(VEN_TRX_Port, VEN_TRX_Pin, GPIO_SPEED_LOW);
  GpioSetOutType(VEN_TRX_Port, VEN_TRX_Pin, GPIO_OUTPUT_PUSHPULL);
  GpioSetPull(VEN_TRX_Port, VEN_TRX_Pin, GPIO_PULL_NO);

  // VCO_DIS
  GpioOutReset(VCO_DIS_Port, VCO_DIS_Pin);
  GpioSetMode(VCO_DIS_Port, VCO_DIS_Pin, GPIO_MODE_OUTPUT);
  GpioSetSpeed(VCO_DIS_Port, VCO_DIS_Pin, GPIO_SPEED_LOW);
  GpioSetOutType(VCO_DIS_Port, VCO_DIS_Pin, GPIO_OUTPUT_PUSHPULL);
  GpioSetPull(VCO_DIS_Port, VCO_DIS_Pin, GPIO_PULL_NO);
}
