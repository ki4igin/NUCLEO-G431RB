#ifndef __H
#define __H

// Includes --------------------------------------------------------------------
// #include "main.h"
#include "stm32g4_gpio.h"

// Typedef ---------------------------------------------------------------------

// Macro -----------------------------------------------------------------------
#define DDS_SCK_Pin      GPIO_PIN_1
#define DDS_SCK_Port     GPIOF
#define DDS_MOSI_Pin     GPIO_PIN_11
#define DDS_MOSI_Port    GPIOA
#define DDS_CS_Pin       GPIO_PIN_0
#define DDS_CS_Port      GPIOA
#define DDS_RESET_Pin    GPIO_PIN_1
#define DDS_RESET_Port   GPIOA
#define DDS_TRIGGER_Pin  GPIO_PIN_12
#define DDS_TRIGGER_Port GPIOA
#define DAC1_Pin         GPIO_PIN_4
#define DAC2_Pin         GPIO_PIN_5
#define DAC_Port         GPIOA
#define VEN_TRX_Pin      GPIO_PIN_6
#define VEN_TRX_Port     GPIOA
#define ADC2_Pin         GPIO_PIN_7
#define ADC2_Port        GPIOA
#define ADC1_Pin         GPIO_PIN_0
#define ADC1_Port        GPIOB
#define I2C_SDA_Pin      GPIO_PIN_8
#define I2C_SCL_Pin      GPIO_PIN_9
#define I2C_Port         GPIOA
#define SWDIO_Pin        GPIO_PIN_13
#define SWCLK_Pin        GPIO_PIN_14
#define SWD_Port         GPIOA
#define VCO_DIS_Pin      GPIO_PIN_8
#define VCO_DIS_Port     GPIOB
#define RCC_MCO_Pin      GPIO_PIN_10
#define RCC_MCO_Port     GPIOG
#define LED_Pin          GPIO_PIN_5
#define LED_Port         GPIOB

// Variables -------------------------------------------------------------------

// Function prototypes ---------------------------------------------------------
void GpioInit(void);

// Inline Functions ------------------------------------------------------------
__STATIC_FORCEINLINE void LedOn(void)
{
  GpioOutSet(LED_Port, LED_Pin);
}

__STATIC_FORCEINLINE void LedOff(void)
{
  GpioOutReset(LED_Port, LED_Pin);
}

#endif
