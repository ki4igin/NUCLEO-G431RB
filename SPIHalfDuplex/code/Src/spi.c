// Includes --------------------------------------------------------------------
#include "spi.h"
#include "gpio.h"
#include "stm32g4xx.h"
// Private Typedef -------------------------------------------------------------

// Private Macro ---------------------------------------------------------------
#define SPI2_SCK_PIN GPIO_PIN_13
#define SPI2_MOSI_PIN GPIO_PIN_15
#define SPI2_PORT    GPIOB

#define SPI3_SCK_PIN  GPIO_PIN_10
#define SPI3_MISO_PIN GPIO_PIN_11
#define SPI3_PORT     GPIOC
// Private Variables -----------------------------------------------------------

// Private Function prototypes -------------------------------------------------

// Functions -------------------------------------------------------------------
void Spi2Init(void)
{
    RCC->APB1ENR1 |= RCC_APB1ENR1_SPI2EN;
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;

    // GPIO Configuration
    GpioSetMode(SPI2_PORT, SPI2_SCK_PIN | SPI2_MOSI_PIN, GPIO_MODE_ALTERNATE);
    GpioSetSpeed(SPI2_PORT, SPI2_SCK_PIN | SPI2_MOSI_PIN, GPIO_SPEED_FAST);
    GpioSetAF(SPI2_PORT, SPI2_SCK_PIN | SPI2_MOSI_PIN, GPIO_AF_5);
    // SPI Congiguration
    LL_SPI_InitTypeDef SPI_InitStruct = {0};
    SPI_InitStruct.TransferDirection  = LL_SPI_HALF_DUPLEX_TX;
    SPI_InitStruct.Mode               = LL_SPI_MODE_MASTER;
    SPI_InitStruct.DataWidth          = LL_SPI_DATAWIDTH_16BIT;
    SPI_InitStruct.ClockPolarity      = LL_SPI_POLARITY_LOW;
    SPI_InitStruct.ClockPhase         = LL_SPI_PHASE_1EDGE;
    SPI_InitStruct.NSS                = LL_SPI_NSS_SOFT;
    SPI_InitStruct.BaudRate           = LL_SPI_BAUDRATEPRESCALER_DIV16;
    SPI_InitStruct.BitOrder           = LL_SPI_MSB_FIRST;
    SPI_InitStruct.CRCCalculation     = LL_SPI_CRCCALCULATION_DISABLE;
    SPI_InitStruct.CRCPoly            = 7;
    LL_SPI_Init(SPI2, &SPI_InitStruct);
    LL_SPI_SetStandard(SPI2, LL_SPI_PROTOCOL_MOTOROLA);
}

void Spi3Init(void)
{
    RCC->APB1ENR1 |= RCC_APB1ENR1_SPI3EN;
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;

    // GPIO Configuration
    GpioSetMode(SPI3_PORT, SPI3_SCK_PIN | SPI3_MISO_PIN, GPIO_MODE_ALTERNATE);
    GpioSetSpeed(SPI3_PORT, SPI3_SCK_PIN | SPI3_MISO_PIN, GPIO_SPEED_FAST);
    GpioSetAF(SPI3_PORT, SPI3_SCK_PIN | SPI3_MISO_PIN, GPIO_AF_6);
    // SPI Congiguration
    LL_SPI_InitTypeDef SPI_InitStruct = {0};
    SPI_InitStruct.TransferDirection  = LL_SPI_HALF_DUPLEX_RX;
    SPI_InitStruct.Mode               = LL_SPI_MODE_SLAVE;
    SPI_InitStruct.DataWidth          = LL_SPI_DATAWIDTH_16BIT;
    SPI_InitStruct.ClockPolarity      = LL_SPI_POLARITY_LOW;
    SPI_InitStruct.ClockPhase         = LL_SPI_PHASE_1EDGE;
    SPI_InitStruct.NSS                = LL_SPI_NSS_SOFT;
    SPI_InitStruct.BitOrder           = LL_SPI_MSB_FIRST;
    SPI_InitStruct.CRCCalculation     = LL_SPI_CRCCALCULATION_DISABLE;
    SPI_InitStruct.CRCPoly            = 7;
    LL_SPI_Init(SPI3, &SPI_InitStruct);
    LL_SPI_SetStandard(SPI3, LL_SPI_PROTOCOL_MOTOROLA);
}



// void UsartTransmitStr(USART_TypeDef *USARTx, uint8_t *str)
// {
//     while (*str != 0)
//     {
//         while ((USARTx->ISR & USART_ISR_TXE_TXFNF) != USART_ISR_TXE_TXFNF)
//         {
//             /* code */
//         }

//         USARTx->TDR = *str++;
//     }
// }

// void UsartTransmitByte(USART_TypeDef *USARTx, uint8_t value)
// {
//     while ((USARTx->ISR & USART_ISR_TXE_TXFNF) != USART_ISR_TXE_TXFNF)
//     {
//         /* code */
//     }
//     USARTx->TDR = value;
// }
