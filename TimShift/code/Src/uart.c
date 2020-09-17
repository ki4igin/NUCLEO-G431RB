// Includes --------------------------------------------------------------------
#include "uart.h"
#include "gpio.h"
#include "stm32g4xx.h"
// Private Typedef -------------------------------------------------------------

// Private Macro ---------------------------------------------------------------
#define LPUART_RX_PIN    GPIO_PIN_3
#define LPUART_TX_PIN    GPIO_PIN_2
#define LPUART_PORT      GPIOA
#define LPUART_BAUD_RATE 937500

#define UART_TX_Pin    GPIO_PIN_6
#define UART_RX_Pin    GPIO_PIN_7
#define UART_Port      GPIOB
#define UART_BAUD_RATE 937500
// Private Variables -----------------------------------------------------------

// Private Function prototypes -------------------------------------------------

// Functions -------------------------------------------------------------------
void LPUartInit(void)
{
  RCC->APB1ENR2 |= RCC_APB1ENR2_LPUART1EN;
  RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;

  // GPIO Configuration
  GpioSetMode(LPUART_PORT, LPUART_TX_PIN | LPUART_RX_PIN, GPIO_MODE_ALTERNATE);
  GpioSetAF(LPUART_PORT, LPUART_TX_PIN | LPUART_RX_PIN, GPIO_AF_12);
  // UART Congiguration
  LPUART1->PRESC = 0;
  LPUART1->BRR   = (uint32_t)(((uint64_t)(256) * SystemCoreClock) / LPUART_BAUD_RATE);
  LPUART1->CR1   = USART_CR1_FIFOEN | USART_CR1_TE | USART_CR1_RE;
  LPUART1->CR1 |= USART_CR1_UE;
}

void UartInit(void)
{
  RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
  RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
  // GPIO Configuration
  GpioSetMode(UART_Port, UART_TX_Pin | UART_RX_Pin, GPIO_MODE_ALTERNATE);
  GpioSetSpeed(UART_Port, UART_TX_Pin | UART_RX_Pin, GPIO_SPEED_LOW);
  GpioSetAF(UART_Port, UART_TX_Pin | UART_RX_Pin, GPIO_AF_7);
  // UART Congiguration
  USART1->PRESC = 0;
  USART1->BRR   = SystemCoreClock / UART_BAUD_RATE;
  USART1->CR1   = USART_CR1_FIFOEN | USART_CR1_RXNEIE |
                USART_CR1_TE | USART_CR1_RE;
}

void UsartSendStr(USART_TypeDef *USARTx, uint8_t *str)
{
  while (*str != 0)
  {
    while ((USARTx->ISR & USART_ISR_TXE_TXFNF) != USART_ISR_TXE_TXFNF)
    {
      /* code */
    }

    USARTx->TDR = *str++;
  }
}

void UsartSendByte(USART_TypeDef *USARTx, uint8_t data)
{
  if ((USARTx->ISR & USART_ISR_TXE_TXFNF) == USART_ISR_TXE_TXFNF)
  {
    USARTx->TDR = data;
  }
  else
  {
    /* code */
  }
}

void UsartSendWord(USART_TypeDef *USARTx, uint16_t data)
{
  if ((USARTx->ISR & USART_ISR_TXE_TXFNF) == USART_ISR_TXE_TXFNF)
  {
    USARTx->TDR = (uint8_t)(data >> 8);
    USARTx->TDR = (uint8_t)data;
  }
  else
  {
    /* code */
  }
}
