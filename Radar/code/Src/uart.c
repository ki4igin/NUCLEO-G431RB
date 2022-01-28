// Includes --------------------------------------------------------------------
#include "uart.h"
#include "gpio.h"
#include "stm32g4xx.h"
// Private Typedef -------------------------------------------------------------

// Private Macro ---------------------------------------------------------------
#define LPUART_RX_PIN    GPIO_PIN_3
#define LPUART_TX_PIN    GPIO_PIN_2
#define LPUART_PORT      GPIOA
#define LPUART_BAUD_RATE 115200

#define UART_RX_PIN    GPIO_PIN_5
#define UART_TX_PIN    GPIO_PIN_4
#define UART_PORT      GPIOC
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
    LPUART1->CR3   = USART_CR3_RXFTCFG_1;

    /* USART interrupt Init */
    // NVIC_SetPriority(LPUART1_IRQn, _EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
    // NVIC_EnableIRQ(LPUART1_IRQn);

    LPUART1->CR1 |= USART_CR1_UE;
}

void UartInit(void)
{
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;

    /* USART interrupt Init */
    NVIC_SetPriority(USART1_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
    NVIC_EnableIRQ(USART1_IRQn);

    // GPIO Configuration
    GpioSetMode(UART_PORT, UART_TX_PIN | UART_RX_PIN, GPIO_MODE_ALTERNATE);
    GpioSetAF(UART_PORT, UART_TX_PIN | UART_RX_PIN, GPIO_AF_7);
    // UART Congiguration
    USART1->PRESC = 0;
    USART1->BRR   = SystemCoreClock / UART_BAUD_RATE;

    USART1->CR1 = USART_CR1_FIFOEN | USART_CR1_RXNEIE | USART_CR1_TE | USART_CR1_RE;
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

void UsartSendArray(USART_TypeDef *USARTx, uint8_t *pbuf, uint8_t len)
{
    do
    {
        while ((USARTx->ISR & USART_ISR_TXE_TXFNF) != USART_ISR_TXE_TXFNF)
        {
            /* code */
        }

        USARTx->TDR = *pbuf++;
    } while (--len > 0);
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
label:
    if ((USARTx->ISR & USART_ISR_TXFT) == USART_ISR_TXFT)
    {
        USARTx->TDR = (uint8_t)(data >> 8);
        USARTx->TDR = (uint8_t)data;
    }
    else
    {
        goto label;
    }
}