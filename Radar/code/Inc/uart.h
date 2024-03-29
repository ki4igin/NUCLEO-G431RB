#ifndef __UART_H
#define __UART_H

// Includes --------------------------------------------------------------------
#include "stm32g4xx.h"
// Typedef ---------------------------------------------------------------------

// Macro -----------------------------------------------------------------------

// Variables -------------------------------------------------------------------

// Function prototypes ---------------------------------------------------------
void LPUartInit(void);
void UartInit(void);
void UsartSendStr(USART_TypeDef *USARTx, uint8_t *str);
void UsartSendArray(USART_TypeDef *USARTx, uint8_t *pbuf, uint8_t len);
void UsartSendByte(USART_TypeDef *USARTx, uint8_t data);
void UsartSendWord(USART_TypeDef *USARTx, uint16_t data);

// Inline Functions ------------------------------------------------------------

#endif
