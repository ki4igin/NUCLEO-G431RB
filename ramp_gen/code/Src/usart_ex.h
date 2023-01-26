#ifndef __USART_EX_H__
#define __USART_EX_H__

#include "stm32g4xx.h"

void uart_send_str(USART_TypeDef *USARTx, uint8_t *str);
void uart_send_array(USART_TypeDef *USARTx, uint8_t *pbuf, uint32_t len);

#endif
