/**
  ******************************************************************************
  * File Name          : TIM.c
  * Description        : This file provides code for the configuration
  *                      of the TIM instances.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "tim.h"
#include "stm32g4_gpio.h"
#include "stm32g4xx_ll_tim.h"
#include "stm32g4xx_ll_rcc.h"
#include "stm32g4xx_ll_bus.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* TIM2 init function */
void MX_TIM2_Init(void)
{
  LL_TIM_InitTypeDef    TIM_InitStruct    = {0};
  LL_TIM_OC_InitTypeDef TIM_OC_InitStruct = {0};

  /* Peripheral clock enable */
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM2);

  /* TIM2 interrupt Init */
  NVIC_SetPriority(TIM2_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
  NVIC_EnableIRQ(TIM2_IRQn);

  TIM_InitStruct.Prescaler     = 10 - 1;
  TIM_InitStruct.CounterMode   = LL_TIM_COUNTERMODE_UP;
  TIM_InitStruct.Autoreload    = 500 - 1;
  TIM_InitStruct.ClockDivision = LL_TIM_CLOCKDIVISION_DIV1;
  LL_TIM_Init(TIM2, &TIM_InitStruct);
  LL_TIM_DisableARRPreload(TIM2);
  LL_TIM_SetClockSource(TIM2, LL_TIM_CLOCKSOURCE_INTERNAL);

  LL_TIM_OC_EnablePreload(TIM2, LL_TIM_CHANNEL_CH1);
  TIM_OC_InitStruct.OCMode       = LL_TIM_OCMODE_PWM1;
  TIM_OC_InitStruct.OCState      = LL_TIM_OCSTATE_DISABLE;
  TIM_OC_InitStruct.OCNState     = LL_TIM_OCSTATE_DISABLE;
  TIM_OC_InitStruct.CompareValue = 200;
  TIM_OC_InitStruct.OCPolarity   = LL_TIM_OCPOLARITY_HIGH;
  LL_TIM_OC_Init(TIM2, LL_TIM_CHANNEL_CH1, &TIM_OC_InitStruct);

  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOA);
  /**TIM2 GPIO Configuration    
    PA15     ------> TIM2_CH1 
    */
  GpioSetMode(GPIOA, GPIO_PIN_15, GPIO_MODE_ALTERNATE);
  GpioSetSpeed(GPIOA, GPIO_PIN_15, GPIO_SPEED_VERYHIGH);
  GpioSetOutType(GPIOA, GPIO_PIN_15, GPIO_OUTPUT_PUSHPULL);
  GpioSetAF(GPIOA, GPIO_PIN_15, GPIO_AF_1);
}
/* TIM3 init function */
void MX_TIM3_Init(void)
{
  LL_TIM_InitTypeDef    TIM_InitStruct    = {0};
  LL_TIM_OC_InitTypeDef TIM_OC_InitStruct = {0};
  /* Peripheral clock enable */
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM3);

  /* TIM3 interrupt Init */
  NVIC_SetPriority(TIM3_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
  NVIC_EnableIRQ(TIM3_IRQn);

  TIM_InitStruct.Prescaler     = 10 - 1;
  TIM_InitStruct.CounterMode   = LL_TIM_COUNTERMODE_UP;
  TIM_InitStruct.Autoreload    = 500 - 1;
  TIM_InitStruct.ClockDivision = LL_TIM_CLOCKDIVISION_DIV1;
  LL_TIM_Init(TIM3, &TIM_InitStruct);
  LL_TIM_DisableARRPreload(TIM3);
  LL_TIM_SetClockSource(TIM3, LL_TIM_CLOCKSOURCE_INTERNAL);

  LL_TIM_OC_EnablePreload(TIM3, LL_TIM_CHANNEL_CH1);
  TIM_OC_InitStruct.OCMode       = LL_TIM_OCMODE_PWM1;
  TIM_OC_InitStruct.OCState      = LL_TIM_OCSTATE_DISABLE;
  TIM_OC_InitStruct.OCNState     = LL_TIM_OCSTATE_DISABLE;
  TIM_OC_InitStruct.CompareValue = 200;
  TIM_OC_InitStruct.OCPolarity   = LL_TIM_OCPOLARITY_HIGH;
  LL_TIM_OC_Init(TIM3, LL_TIM_CHANNEL_CH1, &TIM_OC_InitStruct);

  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOB);
  /**TIM2 GPIO Configuration    
    PA15     ------> TIM2_CH1 
    */
  GpioSetMode(GPIOB, GPIO_PIN_4, GPIO_MODE_ALTERNATE);
  GpioSetSpeed(GPIOB, GPIO_PIN_4, GPIO_SPEED_VERYHIGH);
  GpioSetOutType(GPIOB, GPIO_PIN_4, GPIO_OUTPUT_PUSHPULL);
  GpioSetAF(GPIOB, GPIO_PIN_4, GPIO_AF_2);
}
/* TIM4 init function */
void MX_TIM4_Init(void)
{
  LL_TIM_InitTypeDef TIM_InitStruct = {0};

  /* Peripheral clock enable */
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM4);

  TIM_InitStruct.Prescaler     = 10 - 1;
  TIM_InitStruct.CounterMode   = LL_TIM_COUNTERMODE_UP;
  TIM_InitStruct.Autoreload    = 1200 - 1;
  TIM_InitStruct.ClockDivision = LL_TIM_CLOCKDIVISION_DIV1;
  LL_TIM_Init(TIM4, &TIM_InitStruct);
  LL_TIM_DisableARRPreload(TIM4);
  LL_TIM_SetClockSource(TIM4, LL_TIM_CLOCKSOURCE_INTERNAL);
  LL_TIM_SetTriggerOutput(TIM4, LL_TIM_TRGO_UPDATE);
  LL_TIM_EnableMasterSlaveMode(TIM4);
}
/* TIM6 init function */
void MX_TIM6_Init(void)
{
  LL_TIM_InitTypeDef TIM_InitStruct = {0};

  /* Peripheral clock enable */
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM6);

  /* TIM6 interrupt Init */
  NVIC_SetPriority(TIM6_DAC_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
  NVIC_EnableIRQ(TIM6_DAC_IRQn);

  TIM_InitStruct.Prescaler   = 50000 - 1;
  TIM_InitStruct.CounterMode = LL_TIM_COUNTERMODE_UP;
  TIM_InitStruct.Autoreload  = 3000 - 1;
  LL_TIM_Init(TIM6, &TIM_InitStruct);
  LL_TIM_DisableARRPreload(TIM6);
  LL_TIM_SetTriggerOutput(TIM6, LL_TIM_TRGO_UPDATE);
  LL_TIM_DisableMasterSlaveMode(TIM6);
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
