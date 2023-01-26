#include "usart_ex.h"

void uart_send_str(USART_TypeDef *USARTx, uint8_t *str)
{
    while (*str != 0) {
        while ((USARTx->ISR & USART_ISR_TXE_TXFNF) != USART_ISR_TXE_TXFNF) {
            /* code */
        }

        USARTx->TDR = *str++;
    }
}

void uart_send_array(USART_TypeDef *USARTx, uint8_t *pbuf, uint32_t len)
{
    do {
        while ((USARTx->ISR & USART_ISR_TXE_TXFNF) != USART_ISR_TXE_TXFNF) {
            /* code */
        }

        USARTx->TDR = *pbuf++;
    } while (--len > 0);
}
