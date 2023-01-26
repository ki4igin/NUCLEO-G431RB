#ifndef __GPIO_EX_H__
#define __GPIO_EX_H__

#include "stm32g4xx_ll_dac.h"

#define B1_Pin               LL_GPIO_PIN_13
#define B1_GPIO_Port         GPIOC
#define LPUART1_TX_Pin       LL_GPIO_PIN_2
#define LPUART1_TX_GPIO_Port GPIOA
#define LPUART1_RX_Pin       LL_GPIO_PIN_3
#define LPUART1_RX_GPIO_Port GPIOA
#define T_SWDIO_Pin          LL_GPIO_PIN_13
#define T_SWDIO_GPIO_Port    GPIOA
#define T_SWCLK_Pin          LL_GPIO_PIN_14
#define T_SWCLK_GPIO_Port    GPIOA
#define T_SWO_Pin            LL_GPIO_PIN_3
#define T_SWO_GPIO_Port      GPIOB

inline static void led_on(void)
{
    LL_DAC_ConvertData12RightAligned(DAC1, LL_DAC_CHANNEL_2, 0xFFF);
}

inline static void led_off(void)
{
    LL_DAC_ConvertData12RightAligned(DAC1, LL_DAC_CHANNEL_2, 0);
}

#endif /*__ GPIO_H__ */
