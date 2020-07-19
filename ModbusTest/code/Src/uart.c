// Includes --------------------------------------------------------------------
#include "uart.h"
#include "gpio.h"
#include "stm32g4xx.h"
#include "main.h"
// Private Typedef -------------------------------------------------------------

// Private Macro ---------------------------------------------------------------
#define LPUART_RX_PIN    GPIO_PIN_3
#define LPUART_TX_PIN    GPIO_PIN_2
#define LPUART_PORT      GPIOA
#define LPUART_BAUD_RATE 115200

#define UART_RX_PIN    GPIO_PIN_5
#define UART_TX_PIN    GPIO_PIN_4
#define UART_PORT      GPIOC
#define UART_BAUD_RATE 9375000
// Private Variables -----------------------------------------------------------
UartFlags_t uartFlags = {0};

static uint8_t  cntRx     = {0};
static uint8_t  txBufSize = {0};
static uint8_t *ptxBuf;
static uint8_t *prxBuf;
// Private Function prototypes -------------------------------------------------

// Functions -------------------------------------------------------------------
void LPUartInit(void)
{
  RCC->APB1ENR2 |= RCC_APB1ENR2_LPUART1EN;
  RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;

  /* LPUSART interrupt Init */
  NVIC_SetPriority(LPUART1_IRQn,
                   NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
  NVIC_EnableIRQ(LPUART1_IRQn);

  // GPIO Configuration
  GpioSetMode(LPUART_PORT, LPUART_TX_PIN | LPUART_RX_PIN, GPIO_MODE_ALTERNATE);
  GpioSetAF(LPUART_PORT, LPUART_TX_PIN | LPUART_RX_PIN, GPIO_AF_12);
  // UART Congiguration
  LPUART1->PRESC = 0;
  LPUART1->BRR =
      (uint32_t)(((uint64_t)(256) * SystemCoreClock) / LPUART_BAUD_RATE);
  LPUART1->CR1 = USART_CR1_TE | USART_CR1_RE;
  LPUART1->CR1 |= USART_CR1_UE;
}

void UartInit(void)
{
  RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN | RCC_APB2ENR_USART1EN;

  // GPIO Configuration
  GpioSetMode(UART_PORT, UART_TX_PIN | UART_RX_PIN, GPIO_MODE_ALTERNATE);
  GpioSetAF(UART_PORT, UART_TX_PIN | UART_RX_PIN, GPIO_AF_7);
  // UART Congiguration
  USART1->PRESC = 0;
  USART1->BRR   = SystemCoreClock / UART_BAUD_RATE;

  USART1->CR1 =
      USART_CR1_FIFOEN | USART_CR1_RXNEIE | USART_CR1_TE | USART_CR1_RE;
  USART1->CR1 |= USART_CR1_UE;
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

void UsartSendArray(USART_TypeDef *USARTx, uint8_t *pbuf, uint8_t bufSize)
{
  for (uint8_t i = 0; i < bufSize; i++)
  {
    while ((USARTx->ISR & USART_ISR_TXE_TXFNF) != USART_ISR_TXE_TXFNF)
    {
      /* code */
    }
    USARTx->TDR = *pbuf++;
  }
}

void UsartSendStrIT(USART_TypeDef *USARTx, uint8_t *str)
{
  ptxBuf    = str;
  txBufSize = 0;
  while (*str != 0)
  {
    txBufSize++;
    str++;
  }
  USARTx->CR1 |= USART_CR1_TXEIE;
}

void UsartSendArrayIT(USART_TypeDef *USARTx, uint8_t *pbuf, uint8_t bufSize)
{
  if (txBufSize)
  {
    return;
  }
  txBufSize = bufSize;
  ptxBuf    = pbuf;
  USARTx->CR1 |= USART_CR1_TXEIE;
}

void UsartSendByte(USART_TypeDef *USARTx, uint8_t value)
{
  while ((USARTx->ISR & USART_ISR_TXE_TXFNF) != USART_ISR_TXE_TXFNF)
  {
    /* code */
  }
  USARTx->TDR = value;
}

void UsartReceiveIT(USART_TypeDef *USARTx, uint8_t *pbuf)
{
  if (cntRx)
  {
    return;
  }
  
  prxBuf = pbuf;
  USARTx->CR1 |= USART_CR1_RXNEIE;
}

void Lpuart1Rx_Callback()
{
  TIM6->CNT = 0;
  if (!cntRx)
  {
    TIM6->CR1 |= TIM_CR1_CEN;
  }

  *prxBuf++ = LPUART1->RDR;
  cntRx++;
}

void Lpuart1Tx_Callback()
{
  if (txBufSize)
  {
    txBufSize--;
    LPUART1->TDR = *ptxBuf++;
  }
  else
  {
    LPUART1->CR1 &= ~USART_CR1_TXEIE;
  }
}

void Tim6Update_Callback()
{
  CLEAR_BIT(TIM6->CR1, TIM_CR1_CEN);
  CLEAR_BIT(LPUART1->CR1, USART_CR1_RXNEIE);

  uartFlags.rx     = 1;
  uartFlags.cntRx = cntRx;

  cntRx = 0;
}
// End File --------------------------------------------------------------------