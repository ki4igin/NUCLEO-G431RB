// Includes --------------------------------------------------------------------
#include "AD9102.h"
#include "spi.h"
#include "gpio.h"
#include "uart.h"

// Private Typedef -------------------------------------------------------------

// Private Macro ---------------------------------------------------------------
#define DDS_SPI SPI2
// Private Variables -----------------------------------------------------------

// Private Function prototypes -------------------------------------------------

// Functions -------------------------------------------------------------------
uint16_t AD9102Read(uint16_t regAddr)
{
  uint16_t data_tx = {0};
  uint16_t data_rx = {0};

  data_tx = regAddr | 0x8000;
  GpioOutReset(DDS_CS_Port, DDS_CS_Pin);
  while (!LL_SPI_IsActiveFlag_TXE(DDS_SPI))
  {
  }
  LL_SPI_TransmitData16(DDS_SPI, data_tx);
  while (LL_SPI_IsActiveFlag_BSY(DDS_SPI))
  {
  }

  LL_SPI_Disable(DDS_SPI);
  LL_SPI_SetTransferDirection(DDS_SPI, LL_SPI_HALF_DUPLEX_RX);
  LL_SPI_Enable(DDS_SPI);
  //      for (uint16_t i = 0; i < 60; ++i)
  //      {
  //        __asm("nop");
  //      }
  while (!LL_SPI_IsActiveFlag_RXNE(DDS_SPI))
  {
  }
  LL_SPI_Disable(DDS_SPI);
  data_rx = LL_SPI_ReceiveData16(DDS_SPI);

  GpioOutSet(DDS_CS_Port, DDS_CS_Pin);

  LL_SPI_SetTransferDirection(DDS_SPI, LL_SPI_HALF_DUPLEX_TX);
  LL_SPI_Enable(DDS_SPI);
  return data_rx;
}

void AD9102Write(uint16_t regAddr, uint16_t data)
{
  uint16_t data_tx[2] = {0};

  data_tx[0] = regAddr & ~0x8000;
  data_tx[1] = data;

  GpioOutReset(DDS_CS_Port, DDS_CS_Pin);
  while (!LL_SPI_IsActiveFlag_TXE(DDS_SPI))
  {
  }
  LL_SPI_TransmitData16(DDS_SPI, data_tx[0]);
  while (!LL_SPI_IsActiveFlag_TXE(DDS_SPI))
  {
  }
  LL_SPI_TransmitData16(DDS_SPI, data_tx[1]);
  while (LL_SPI_IsActiveFlag_BSY(DDS_SPI))
  {
  }
  GpioOutSet(DDS_CS_Port, DDS_CS_Pin);
}

void AD9102Init(void)
{
  uint16_t data = 0;

  data = SPICONFIG_SPI3WIRE;
  AD9102Write(SPICONFIG, data);

  data = AD9102Read(PAT_TIMEBASE);
  if (data == 0x111)
  {
    UsartSendStr(USART1, (uint8_t*)"DDS Ok\n");
  }
  else
  {
    UsartSendStr(USART1, (uint8_t*)"DDS Error\n");
  }

  AD9102Write(DACRSET, DAC_RSET | DAC_RSET_EN);
  AD9102Write(WAV_CONFIG, WAV_SEL);
  AD9102Write(DACDOF, DAC_DIG_OFFSET);
  AD9102Write(DAC_DGAIN, DAC_DIG_GAIN);
  AD9102Write(PAT_TIMEBASE,
              PAT_TIMEBASE_HOLD | PAT_PERIOD_BASE | START_DELAY_BASE);
  AD9102Write(PAT_PERIOD, PATTERN_PERIOD);
  AD9102Write(START_ADDR_REG, START_ADDR);
  AD9102Write(STOP_ADDR_REG, STOP_ADDR);
  data = MEM_ACCESS;
  AD9102Write(PAT_STATUS, data);
  AD9102Write(RAMUPDATE, UPDATE);

  int16_t data_ram = -0x4000 / 2;

  for (uint16_t i = 0x6000; i != PATTERN_PERIOD + 0x6000; i++)
  {
    //  	AD9102Write(i, data_ram << 2);
    AD9102Write(i, data_ram << 2);
    data_ram = data_ram + 0x4000 / (PATTERN_PERIOD - 1);
  }

  AD9102Write(PAT_STATUS, RUN);
}
