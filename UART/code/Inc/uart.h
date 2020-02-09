#ifndef __UART_H
#define __UART_H

// Includes --------------------------------------------------------------------
#include "stm32g4xx.h"
// Typedef ---------------------------------------------------------------------

// Macro -----------------------------------------------------------------------

// Variables -------------------------------------------------------------------

// Function prototypes ---------------------------------------------------------
void LPUartInit(void);
void UsartTransmitStr(USART_TypeDef *USARTx, uint8_t *str);
void UsartTransmitByte(USART_TypeDef *USARTx, uint8_t value);

// Inline Functions ------------------------------------------------------------

#endif
