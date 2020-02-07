#ifndef __GPIO_H
#define __GPIO_H

// Includes --------------------------------------------------------------------
#include "main.h"
#include "stm32g4xx.h"

// Typedef ---------------------------------------------------------------------
typedef enum
{
  INPUT = 0, /*!< GPIO port mode register,               Address offset: 0x00      */
  OUTPUT,    /*!< GPIO port output type register,        Address offset: 0x04      */
  ALTERNATE, /*!< GPIO port output speed register,       Address offset: 0x08      */
  ANALOG     /*!< GPIO port pull-up/pull-down register,  Address offset: 0x0C      */
} MODER_TypeDef;

typedef struct
{
  __IO MODER_TypeDef PIN00 : 2; /*!< GPIO port mode register,               Address offset: 0x00      */
  __IO MODER_TypeDef PIN01 : 2; /*!< GPIO port mode register,               Address offset: 0x00      */
  __IO MODER_TypeDef PIN02 : 2; /*!< GPIO port mode register,               Address offset: 0x00      */
  __IO MODER_TypeDef PIN03 : 2; /*!< GPIO port mode register,               Address offset: 0x00      */
  __IO MODER_TypeDef PIN04 : 2; /*!< GPIO port mode register,               Address offset: 0x00      */
  __IO MODER_TypeDef PIN05 : 2; /*!< GPIO port mode register,               Address offset: 0x00      */
  __IO MODER_TypeDef PIN06 : 2; /*!< GPIO port mode register,               Address offset: 0x00      */
  __IO MODER_TypeDef PIN07 : 2; /*!< GPIO port mode register,               Address offset: 0x00      */
  __IO MODER_TypeDef PIN08 : 2; /*!< GPIO port mode register,               Address offset: 0x00      */
  __IO MODER_TypeDef PIN09 : 2; /*!< GPIO port mode register,               Address offset: 0x00      */
  __IO MODER_TypeDef PIN10 : 2; /*!< GPIO port mode register,               Address offset: 0x00      */
  __IO MODER_TypeDef PIN11 : 2; /*!< GPIO port mode register,               Address offset: 0x00      */
  __IO MODER_TypeDef PIN12 : 2; /*!< GPIO port mode register,               Address offset: 0x00      */
  __IO MODER_TypeDef PIN13 : 2; /*!< GPIO port mode register,               Address offset: 0x00      */
  __IO MODER_TypeDef PIN14 : 2; /*!< GPIO port mode register,               Address offset: 0x00      */
  __IO MODER_TypeDef PIN15 : 2; /*!< GPIO port mode register,               Address offset: 0x00      */
} PIN_TypeDef;

typedef struct
{
  __IO PIN_TypeDef MODER;   /*!< GPIO port mode register,               Address offset: 0x00      */
  __IO uint32_t    OTYPER;  /*!< GPIO port output type register,        Address offset: 0x04      */
  __IO uint32_t    OSPEEDR; /*!< GPIO port output speed register,       Address offset: 0x08      */
  __IO uint32_t    PUPDR;   /*!< GPIO port pull-up/pull-down register,  Address offset: 0x0C      */
  __IO uint32_t    IDR;     /*!< GPIO port input data register,         Address offset: 0x10      */
  __IO uint32_t    ODR;     /*!< GPIO port output data register,        Address offset: 0x14      */
  __IO uint32_t    BSRR;    /*!< GPIO port bit set/reset  register,     Address offset: 0x18      */
  __IO uint32_t    LCKR;    /*!< GPIO port configuration lock register, Address offset: 0x1C      */
  __IO uint32_t    AFR[2];  /*!< GPIO alternate function registers,     Address offset: 0x20-0x24 */
  __IO uint32_t    BRR;     /*!< GPIO Bit Reset register,               Address offset: 0x28      */
} GPIO_Type;

// Macro -----------------------------------------------------------------------

// Pin
#define GPIO_PIN_0   GPIO_BSRR_BS0
#define GPIO_PIN_1   GPIO_BSRR_BS1
#define GPIO_PIN_2   GPIO_BSRR_BS2
#define GPIO_PIN_3   GPIO_BSRR_BS3
#define GPIO_PIN_4   GPIO_BSRR_BS4
#define GPIO_PIN_5   GPIO_BSRR_BS5
#define GPIO_PIN_6   GPIO_BSRR_BS6
#define GPIO_PIN_7   GPIO_BSRR_BS7
#define GPIO_PIN_8   GPIO_BSRR_BS8
#define GPIO_PIN_9   GPIO_BSRR_BS9
#define GPIO_PIN_10  GPIO_BSRR_BS10
#define GPIO_PIN_11  GPIO_BSRR_BS11
#define GPIO_PIN_12  GPIO_BSRR_BS12
#define GPIO_PIN_13  GPIO_BSRR_BS13
#define GPIO_PIN_14  GPIO_BSRR_BS14
#define GPIO_PIN_15  GPIO_BSRR_BS15
#define GPIO_PIN_ALL (GPIO_BSRR_BS0 | GPIO_BSRR_BS1 | GPIO_BSRR_BS2 |    \
                      GPIO_BSRR_BS3 | GPIO_BSRR_BS4 | GPIO_BSRR_BS5 |    \
                      GPIO_BSRR_BS6 | GPIO_BSRR_BS7 | GPIO_BSRR_BS8 |    \
                      GPIO_BSRR_BS9 | GPIO_BSRR_BS10 | GPIO_BSRR_BS11 |  \
                      GPIO_BSRR_BS12 | GPIO_BSRR_BS13 | GPIO_BSRR_BS14 | \
                      GPIO_BSRR_BS15)

// Mode
#define GPIO_MODE_INPUT     (0x00000000U)      /*!< Select input mode */
#define GPIO_MODE_OUTPUT    GPIO_MODER_MODE0_0 /*!< Select output mode */
#define GPIO_MODE_ALTERNATE GPIO_MODER_MODE0_1 /*!< Select alternate function mode */
#define GPIO_MODE_ANALOG    GPIO_MODER_MODE0   /*!< Select analog mode */

// Output Type
#define GPIO_OUTPUT_PUSHPULL  (0x00000000U)   /*!< Select push-pull as output type */
#define GPIO_OUTPUT_OPENDRAIN GPIO_OTYPER_OT0 /*!< Select open-drain as output type */

// Output Speed
#define GPIO_SPEED_LOW    (0x00000000U)
#define GPIO_SPEED_MEDIUM GPIO_OSPEEDR_OSPEED0_0
#define GPIO_SPEED_FAST   GPIO_OSPEEDR_OSPEED0_1
#define GPIO_SPEED_HIGH   GPIO_OSPEEDR_OSPEED0

// Pull Up Pull Down
#define GPIO_PULL_NO   (0x00000000U)      /*!< Select I/O no pull */
#define GPIO_PULL_UP   GPIO_PUPDR_PUPD0_0 /*!< Select I/O pull up */
#define GPIO_PULL_DOWN GPIO_PUPDR_PUPD0_1 /*!< Select I/O pull down */

// Alternate Function
#define GPIO_AF_0  (0x0000000U) /*!< Select alternate function 0 */
#define GPIO_AF_1  (0x0000001U) /*!< Select alternate function 1 */
#define GPIO_AF_2  (0x0000002U) /*!< Select alternate function 2 */
#define GPIO_AF_3  (0x0000003U) /*!< Select alternate function 3 */
#define GPIO_AF_4  (0x0000004U) /*!< Select alternate function 4 */
#define GPIO_AF_5  (0x0000005U) /*!< Select alternate function 5 */
#define GPIO_AF_6  (0x0000006U) /*!< Select alternate function 6 */
#define GPIO_AF_7  (0x0000007U) /*!< Select alternate function 7 */
#define GPIO_AF_8  (0x0000008U) /*!< Select alternate function 8 */
#define GPIO_AF_9  (0x0000009U) /*!< Select alternate function 9 */
#define GPIO_AF_10 (0x000000AU) /*!< Select alternate function 10 */
#define GPIO_AF_11 (0x000000BU) /*!< Select alternate function 11 */
#define GPIO_AF_12 (0x000000CU) /*!< Select alternate function 12 */
#define GPIO_AF_13 (0x000000DU) /*!< Select alternate function 13 */
#define GPIO_AF_14 (0x000000EU) /*!< Select alternate function 14 */
#define GPIO_AF_15 (0x000000FU) /*!< Select alternate function 15 */

// GPIOA Pin5 - LED
#define GPIOA1 ((GPIO_Type*)GPIOA_BASE)

#define LED_PORT    GPIOA
#define LED_PIN_Pos 5U
#define LED_PIN    (1UL << LED_PIN_Pos)

// Variables -------------------------------------------------------------------

// Function prototypes ---------------------------------------------------------
void GpioInit(void);

// Inline Functions ------------------------------------------------------------
__STATIC_FORCEINLINE void GPIO_SetPinMode(GPIO_TypeDef* GPIOx, uint32_t Pin, uint32_t Mode)
{
  MODIFY_REG(GPIOx->MODER, (GPIO_MODER_MODE0 << (POSITION_VAL(Pin) * 2U)), (Mode << (POSITION_VAL(Pin) * 2U)));
}

__STATIC_FORCEINLINE void GpioOutSet(GPIO_TypeDef* port, uint32_t pin)
{
  port->BSRR |= pin;
}

__STATIC_FORCEINLINE void GpioOutReset(GPIO_TypeDef* port, uint32_t pin)
{
  port->BRR |= pin;
}

__STATIC_FORCEINLINE void LedOn(void)
{
  GpioOutSet(LED_PORT, LED_PIN);
}

__STATIC_FORCEINLINE void LedOff(void)
{
  GpioOutReset(LED_PORT, LED_PIN);
}

#endif
