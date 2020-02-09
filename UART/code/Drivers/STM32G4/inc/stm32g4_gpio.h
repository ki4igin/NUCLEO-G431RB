#ifndef __STM32G4_GPIO_H
#define __STM32G4_GPIO_H

// Includes --------------------------------------------------------------------
#include "stm32g4xx.h"

// Typedef ---------------------------------------------------------------------

// Mode
typedef enum
{
  GPIO_MODE_INPUT     = (0x00000000U),       // Select input mode
  GPIO_MODE_OUTPUT    = GPIO_MODER_MODE0_0,  // Select output mode
  GPIO_MODE_ALTERNATE = GPIO_MODER_MODE0_1,  // Select alternate function mode
  GPIO_MODE_ANALOG    = GPIO_MODER_MODE0     // Select analog mode
} GPIO_MODE_TypeDef;

// Output Type
typedef enum
{
  GPIO_OUTPUT_PUSHPULL  = (0x00000000U),   // Select push-pull as output type
  GPIO_OUTPUT_OPENDRAIN = GPIO_OTYPER_OT0  // Select open-drain as output type
} GPIO_OUTPUT_TypeDef;

// Output Speed
typedef enum
{
  GPIO_SPEED_LOW    = (0x00000000U),
  GPIO_SPEED_MEDIUM = GPIO_OSPEEDR_OSPEED0_0,
  GPIO_SPEED_FAST   = GPIO_OSPEEDR_OSPEED0_1,
  GPIO_SPEED_HIGH   = GPIO_OSPEEDR_OSPEED0

} GPIO_SPEED_TypeDef;

// Pull Up Pull Down
typedef enum
{

  GPIO_PULL_NO   = (0x00000000U),       // Select I/O no pull
  GPIO_PULL_UP   = GPIO_PUPDR_PUPD0_0,  // Select I/O pull up
  GPIO_PULL_DOWN = GPIO_PUPDR_PUPD0_1   // Select I/O pull down
} GPIO_PULL_TypeDef;

// Alternate Function
typedef enum
{
  GPIO_AF_0 = (0x0000000U),  // Select alternate function 0
  GPIO_AF_1 = (0x0000001U),  // Select alternate function 1
  GPIO_AF_2 = (0x0000002U),  // Select alternate function 2
  GPIO_AF_3 = (0x0000003U),  // Select alternate function 3
  GPIO_AF_4 = (0x0000004U),  // Select alternate function 4
  GPIO_AF_5 = (0x0000005U),  // Select alternate function 5
  GPIO_AF_6 = (0x0000006U),  // Select alternate function 6
  GPIO_AF_7 = (0x0000007U),  // Select alternate function 7
  GPIO_AF_8 = (0x0000008U),  // Select alternate function 8
  GPIO_AF_9 = (0x0000009U),  // Select alternate function 9
  GPIO_AF_10 = (0x000000AU),  // Select alternate function 10
  GPIO_AF_11 = (0x000000BU),  // Select alternate function 11
  GPIO_AF_12 = (0x000000CU),  // Select alternate function 12
  GPIO_AF_13 = (0x000000DU),  // Select alternate function 13
  GPIO_AF_14 = (0x000000EU),  // Select alternate function 14
  GPIO_AF_15 = (0x000000FU)   // Select alternate function 15
} GPIO_AF_TypeDef;

// Macro -----------------------------------------------------------------------

// Pin
#define GPIO_PIN_0  GPIO_BSRR_BS0
#define GPIO_PIN_1  GPIO_BSRR_BS1
#define GPIO_PIN_2  GPIO_BSRR_BS2
#define GPIO_PIN_3  GPIO_BSRR_BS3
#define GPIO_PIN_4  GPIO_BSRR_BS4
#define GPIO_PIN_5  GPIO_BSRR_BS5
#define GPIO_PIN_6  GPIO_BSRR_BS6
#define GPIO_PIN_7  GPIO_BSRR_BS7
#define GPIO_PIN_8  GPIO_BSRR_BS8
#define GPIO_PIN_9  GPIO_BSRR_BS9
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

// Variables -------------------------------------------------------------------

// Function prototypes ---------------------------------------------------------

// Inline Functions ------------------------------------------------------------
__STATIC_FORCEINLINE void GpioSetMode(GPIO_TypeDef*     GPIOx,
                                      uint16_t          pins,
                                      GPIO_MODE_TypeDef mode)
{
  uint32_t temp = 0;

  for (uint8_t i = 0; i < 16; i++)
  {
    temp += (pins & (1U << i)) << i;
  }

  MODIFY_REG(GPIOx->MODER,
             (GPIO_MODER_MODE0 * temp),
             (mode * temp));
}

__STATIC_FORCEINLINE void GpioSetOutType(GPIO_TypeDef*       GPIOx,
                                         uint16_t            pins,
                                         GPIO_OUTPUT_TypeDef outType)
{
  MODIFY_REG(GPIOx->OTYPER, pins, (pins * outType));
}

__STATIC_FORCEINLINE void GpioSetSpeed(GPIO_TypeDef*      GPIOx,
                                       uint16_t           pins,
                                       GPIO_SPEED_TypeDef speed)
{
  uint32_t temp = 0;

  for (uint8_t i = 0; i < 16; i++)
  {
    temp += (pins & (1U << i)) << i;
  }

  MODIFY_REG(GPIOx->MODER,
             (GPIO_OSPEEDR_OSPEED0 * temp),
             (speed * temp));
}

__STATIC_FORCEINLINE void GpioSetPull(GPIO_TypeDef*     GPIOx,
                                      uint16_t          pins,
                                      GPIO_PULL_TypeDef pull)
{
  uint32_t temp = 0;

  for (uint8_t i = 0; i < 16; i++)
  {
    temp += (pins & (1U << i)) << i;
  }

  MODIFY_REG(GPIOx->PUPDR,
             (GPIO_PUPDR_PUPD0 * temp),
             (pull * temp));
}

__STATIC_FORCEINLINE void GpioSetAF(GPIO_TypeDef*   GPIOx,
                                    uint16_t        pins,
                                    GPIO_AF_TypeDef af)
{
  uint32_t tempL = 0;
  uint32_t tempH = 0;

  for (uint8_t i = 0; i < 8; i++)
  {
    tempL += (pins & (1U << i)) << (3 * i);
    tempH += ((pins & (1U << (i + 8))) >> 8) << (3 * i);
  }
  MODIFY_REG(GPIOx->AFR[0],
             (GPIO_AFRL_AFSEL0 * tempL),
             (af * tempL));
  MODIFY_REG(GPIOx->AFR[1],
             (GPIO_AFRL_AFSEL0 * tempH),
             (af * tempH));
}

__STATIC_FORCEINLINE void GpioSetLock(GPIO_TypeDef* GPIOx, uint16_t pins)
{
  WRITE_REG(GPIOx->LCKR, GPIO_LCKR_LCKK | pins);
  WRITE_REG(GPIOx->LCKR, pins);
  WRITE_REG(GPIOx->LCKR, GPIO_LCKR_LCKK | pins);
  /* Read LCKR register. This read is mandatory to complete key lock sequence */
  __IO uint32_t temp = READ_REG(GPIOx->LCKR);
  (void)temp;
}

__STATIC_FORCEINLINE void GpioOutSet(GPIO_TypeDef* port, uint32_t pin)
{
  port->BSRR |= pin;
}

__STATIC_FORCEINLINE void GpioOutReset(GPIO_TypeDef* port, uint32_t pin)
{
  port->BRR |= pin;
}

__STATIC_FORCEINLINE void GpioOutToggle(GPIO_TypeDef* GPIOx, uint32_t PinMask)
{
  WRITE_REG(GPIOx->ODR, READ_REG(GPIOx->ODR) ^ PinMask);
}

#endif
