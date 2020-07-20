#ifndef __UART_H
#define __UART_H

// Includes --------------------------------------------------------------------
#include "stm32g4xx.h"
// Typedef ---------------------------------------------------------------------
typedef struct
{
  uint8_t rx : 1;  // Флаг приема данных
  uint8_t tx : 1;  // Флаг передачи данных
  uint8_t cntRx;   // колличество принятых данных
  uint8_t cnt15t;   // колличество интервалов > 1.5t
} UartFlags_t;
// Macro -----------------------------------------------------------------------

// Variables -------------------------------------------------------------------
extern UartFlags_t uartFlags;
// Function prototypes ---------------------------------------------------------
void LPUartInit(void);
void UsartSendStr(USART_TypeDef *USARTx, uint8_t *str);
void UsartSendStrIT(USART_TypeDef *USARTx, uint8_t *str);
void UsartSendByte(USART_TypeDef *USARTx, uint8_t value);
void UsartSendArray(USART_TypeDef *USARTx, uint8_t *pbuf, uint8_t bufSize);
void UsartSendArrayIT(USART_TypeDef *USARTx, uint8_t *pbuf, uint8_t bufSize);
void UsartReceiveIT(USART_TypeDef *USARTx, uint8_t *pbuf);

void Lpuart1Rx_Callback(void);
void Lpuart1Tx_Callback(void);
void Tim4Update_Callback(void);
void Tim4CC1_Callback();
// Inline Functions ------------------------------------------------------------

#endif
