// Includes --------------------------------------------------------------------
#include "modbus.h"
#include "main.h"
#include "crc16.h"
#include "uart.h"
#include "tim.h"

// Private Typedef -------------------------------------------------------------

// Private Macro ---------------------------------------------------------------
#define UART LPUART

#define SLA ('1')
// Private Variables -----------------------------------------------------------
uint8_t rxBuf[256] = {0};
uint8_t txBuf[256] = {0};
// Private Function prototypes -------------------------------------------------

// Functions -------------------------------------------------------------------
void ModBusInit()
{
  LPUartInit();
  TIM6_Init();

  UsartReceiveIT(LPUART1, rxBuf);
}

void ModBusProcess()
{
  if (uartFlags.rx)
  {
    uartFlags.rx = 0;
    uint8_t rxBufSize = uartFlags.cntRx;
    if ((rxBuf[0] != SLA) || (rxBufSize < 4))
    {
      UsartSendStrIT(LPUART1, (uint8_t*)"SLA Error\n");
      UsartReceiveIT(LPUART1, rxBuf);
      return;
    }
    uint16_t crc16   = Crc16(rxBuf, rxBufSize - 2);
    uint16_t crc16rx = __REV16(*((uint16_t*)&rxBuf[rxBufSize - 2]));
    if (crc16rx != crc16)
    {
      UsartSendStrIT(LPUART1, (uint8_t*)"Crc Error\n");
      UsartReceiveIT(LPUART1, rxBuf);
      return;
    }
    UsartSendStrIT(LPUART1, (uint8_t*)"Ok\n");
            
    UsartReceiveIT(LPUART1, rxBuf);
  }
}
