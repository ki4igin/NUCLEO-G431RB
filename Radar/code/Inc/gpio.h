#ifndef __GPIO_H
#define __GPIO_H

// Includes --------------------------------------------------------------------
// #include "main.h"
#include "stm32g4_gpio.h"

// Typedef ---------------------------------------------------------------------

// Macro -----------------------------------------------------------------------

#define B1_Pin       GPIO_PIN_13
#define B1_GPIO_Port GPIOC

#define PLL_CLK_EN_Pin       GPIO_PIN_2
#define PLL_TXDATA_Pin       GPIO_PIN_5
#define PLL_CE_Pin           GPIO_PIN_4
#define PLL_3STATE_Pin       GPIO_PIN_6
#define PLL_LE_Pin           GPIO_PIN_7
#define PLL_CLK_EN_GPIO_Port GPIOC
#define PLL_TXDATA_GPIO_Port GPIOC
#define PLL_CE_GPIO_Port     GPIOB
#define PLL_3STATE_GPIO_Port GPIOB
#define PLL_LE_GPIO_Port     GPIOB

#define RF_3V3_EN_Pin         GPIO_PIN_0
#define RF_3V3_EN_GPIO_Port   GPIOB

#define RFE_PWR_Pin        GPIO_PIN_3
#define RFE_PWR_GPIO_Port  GPIOC
#define RFE_PWR1_Pin       GPIO_PIN_8
#define RFE_PWR1_GPIO_Port GPIOB
#define RFE_VCT_Pin        GPIO_PIN_9
#define RFE_VCT_GPIO_Port  GPIOB

#define IF_I_L_Pin       GPIO_PIN_0
#define IF_I_L_GPIO_Port GPIOA
#define IF_Q_L_Pin       GPIO_PIN_1
#define IF_Q_L_GPIO_Port GPIOA
// #define LPUART1_TX_Pin           GPIO_PIN_2
// #define LPUART1_TX_GPIO_Port     GPIOA
// #define LPUART1_RX_Pin           GPIO_PIN_3
// #define LPUART1_RX_GPIO_Port     GPIOA
#define BB_REF_Pin           GPIO_PIN_4
#define BB_REF_GPIO_Port     GPIOA
#define LD2_Pin              GPIO_PIN_5
#define LD2_GPIO_Port        GPIOA
#define IF_I_H_Pin           GPIO_PIN_6
#define IF_I_H_GPIO_Port     GPIOA
#define IF_Q_H_Pin           GPIO_PIN_7
#define IF_Q_H_GPIO_Port     GPIOA

#define P_1V8_EN_Pin         GPIO_PIN_15
#define P_1V8_EN_GPIO_Port   GPIOA


#define EEPROM_CS_Pin        GPIO_PIN_12
#define EEPROM_CS_GPIO_Port  GPIOB
#define BOARD_SCK_Pin        GPIO_PIN_13
#define BOARD_SCK_GPIO_Port  GPIOB
#define BOARD_MISO_Pin       GPIO_PIN_14
#define BOARD_MISO_GPIO_Port GPIOB
#define BOARD_MOSI_Pin       GPIO_PIN_15
#define BOARD_MOSI_GPIO_Port GPIOB

#define LED1_Pin       GPIO_PIN_9
#define LED2_Pin       GPIO_PIN_8
#define LED3_Pin       GPIO_PIN_6
#define LEDS_GPIO_Port GPIOC

#define MC_TX_Pin           GPIO_PIN_9
#define MC_TX_GPIO_Port     GPIOA
#define CABLE_RX_Pin        GPIO_PIN_10
#define CABLE_RX_GPIO_Port  GPIOA
#define T_SWDIO_Pin         GPIO_PIN_13
#define T_SWDIO_GPIO_Port   GPIOA
#define T_SWCLK_Pin         GPIO_PIN_14
#define T_SWCLK_GPIO_Port   GPIOA
#define HOST_SCK_Pin        GPIO_PIN_10
#define HOST_SCK_GPIO_Port  GPIOC
#define HOST_MISO_Pin       GPIO_PIN_11
#define HOST_MISO_GPIO_Port GPIOC
#define HOST_MOSI_Pin       GPIO_PIN_12
#define HOST_MOSI_GPIO_Port GPIOC
#define HOST_CS_Pin         GPIO_PIN_2
#define HOST_CS_GPIO_Port   GPIOD
#define T_SWO_Pin           GPIO_PIN_3
#define T_SWO_GPIO_Port     GPIOB

// Variables -------------------------------------------------------------------

// Function prototypes ---------------------------------------------------------
void GpioInit(void);

// Inline Functions ------------------------------------------------------------
__STATIC_FORCEINLINE void Led1On(void)
{
    GpioOutReset(LEDS_GPIO_Port, LED1_Pin);
}

__STATIC_FORCEINLINE void Led1Off(void)
{
    GpioOutSet(LEDS_GPIO_Port, LED1_Pin);
}

__STATIC_FORCEINLINE void Led2On(void)
{
    GpioOutReset(LEDS_GPIO_Port, LED2_Pin);
}

__STATIC_FORCEINLINE void Led2Off(void)
{
    GpioOutSet(LEDS_GPIO_Port, LED2_Pin);
}

__STATIC_FORCEINLINE void Led3On(void)
{
    GpioOutReset(LEDS_GPIO_Port, LED3_Pin);
}

__STATIC_FORCEINLINE void Led3Off(void)
{
    GpioOutSet(LEDS_GPIO_Port, LED3_Pin);
}

__STATIC_FORCEINLINE void LedAllOn(void)
{
    GpioOutReset(LEDS_GPIO_Port, LED1_Pin | LED2_Pin | LED3_Pin);
}

__STATIC_FORCEINLINE void LedAllOff(void)
{
    GpioOutSet(LEDS_GPIO_Port, LED1_Pin | LED2_Pin | LED3_Pin);
}

#endif
