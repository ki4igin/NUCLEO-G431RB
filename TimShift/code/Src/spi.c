// Includes --------------------------------------------------------------------
#include "spi.h"
#include "gpio.h"
#include "stm32g4xx.h"
// Private Typedef -------------------------------------------------------------

// Private Macro ---------------------------------------------------------------
#define SPI2_SCK_PIN   DDS_SCK_Pin
#define SPI2_MOSI_PIN  DDS_MOSI_Pin
#define SPI2_SCK_PORT  DDS_SCK_Port
#define SPI2_MOSI_PORT DDS_MOSI_Port

// Private Variables -----------------------------------------------------------

// Private Function prototypes -------------------------------------------------

// Functions -------------------------------------------------------------------
void Spi2Init(void)
{
  RCC->APB1ENR1 |= RCC_APB1ENR1_SPI2EN;
  RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN | RCC_AHB2ENR_GPIOFEN;

  // GPIO Configuration
  GpioSetMode(SPI2_SCK_PORT, SPI2_SCK_PIN, GPIO_MODE_ALTERNATE);
  GpioSetMode(SPI2_MOSI_PORT, SPI2_MOSI_PIN, GPIO_MODE_ALTERNATE);
  GpioSetOutType(SPI2_SCK_PORT, SPI2_SCK_PIN, GPIO_OUTPUT_PUSHPULL);
  GpioSetOutType(SPI2_MOSI_PORT, SPI2_MOSI_PIN, GPIO_OUTPUT_PUSHPULL);
  GpioSetSpeed(SPI2_SCK_PORT, SPI2_SCK_PIN, GPIO_SPEED_VERYHIGH);
  GpioSetSpeed(SPI2_MOSI_PORT, SPI2_MOSI_PIN, GPIO_SPEED_VERYHIGH);
  GpioSetAF(SPI2_SCK_PORT, SPI2_SCK_PIN, GPIO_AF_5);
  GpioSetAF(SPI2_MOSI_PORT, SPI2_MOSI_PIN, GPIO_AF_5);
  // SPI Congiguration
  LL_SPI_InitTypeDef SPI_InitStruct = {0};
  SPI_InitStruct.TransferDirection  = LL_SPI_HALF_DUPLEX_TX;
  SPI_InitStruct.Mode               = LL_SPI_MODE_MASTER;
  SPI_InitStruct.DataWidth          = LL_SPI_DATAWIDTH_16BIT;
  SPI_InitStruct.ClockPolarity      = LL_SPI_POLARITY_LOW;
  SPI_InitStruct.ClockPhase         = LL_SPI_PHASE_1EDGE;
  SPI_InitStruct.NSS                = LL_SPI_NSS_SOFT;
  SPI_InitStruct.BaudRate           = LL_SPI_BAUDRATEPRESCALER_DIV256;
  SPI_InitStruct.BitOrder           = LL_SPI_MSB_FIRST;
  SPI_InitStruct.CRCCalculation     = LL_SPI_CRCCALCULATION_DISABLE;
  SPI_InitStruct.CRCPoly            = 7;
  LL_SPI_Init(SPI2, &SPI_InitStruct);
  LL_SPI_SetStandard(SPI2, LL_SPI_PROTOCOL_MOTOROLA);
}
