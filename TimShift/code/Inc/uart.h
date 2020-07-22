#ifndef __UART_H
#define __UART_H

// Includes --------------------------------------------------------------------
#include "stm32g4xx.h"
// Typedef ---------------------------------------------------------------------

// Macro -----------------------------------------------------------------------

// Variables -------------------------------------------------------------------

// Function prototypes ---------------------------------------------------------
void UartInit(void);
void UsartSendStr(USART_TypeDef *USARTx, uint8_t *str);
void UsartSendByte(USART_TypeDef *USARTx, uint8_t data);
void UsartSendWord(USART_TypeDef *USARTx, uint16_t data);

// Inline Functions ------------------------------------------------------------
__STATIC_FORCEINLINE void UsartEnable(USART_TypeDef *USARTx)
{
  SET_BIT(USARTx->CR1, USART_CR1_UE);
}

__STATIC_FORCEINLINE void UsartDisable(USART_TypeDef *USARTx)
{
  CLEAR_BIT(USARTx->CR1, USART_CR1_UE);
}

#endif
