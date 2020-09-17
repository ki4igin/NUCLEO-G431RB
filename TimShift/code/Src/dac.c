/**
  ******************************************************************************
  * File Name          : DAC.c
  * Description        : This file provides code for the configuration
  *                      of the DAC instances.
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
#include "dac.h"
#include "stm32g4xx_ll_dac.h"
#include "stm32g4xx_ll_rcc.h"
#include "stm32g4xx_ll_bus.h"
#include "gpio.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* DAC1 init function */
void MX_DAC1_Init(void)
{
  LL_DAC_InitTypeDef DAC_InitStruct = {0};

  /* Peripheral clock enable */
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_DAC1);

  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOA);
  /**DAC1 GPIO Configuration  
  PA4   ------> DAC1_OUT1
  PA5   ------> DAC1_OUT2 
  */
  GpioSetMode(DAC_Port, DAC1_Pin | DAC2_Pin, GPIO_MODE_ANALOG);
  GpioSetPull(DAC_Port, DAC1_Pin | DAC2_Pin, GPIO_PULL_NO);

  /* DAC1 interrupt Init */
  NVIC_SetPriority(TIM6_DAC_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
  NVIC_EnableIRQ(TIM6_DAC_IRQn);

  /** DAC channel OUT1 config 
  */
  LL_DAC_SetSignedFormat(DAC1, LL_DAC_CHANNEL_1, LL_DAC_SIGNED_FORMAT_DISABLE);
  DAC_InitStruct.TriggerSource      = LL_DAC_TRIG_SOFTWARE;
  DAC_InitStruct.TriggerSource2     = LL_DAC_TRIG_SOFTWARE;
  DAC_InitStruct.WaveAutoGeneration = LL_DAC_WAVE_AUTO_GENERATION_NONE;
  DAC_InitStruct.OutputBuffer       = LL_DAC_OUTPUT_BUFFER_ENABLE;
  DAC_InitStruct.OutputConnection   = LL_DAC_OUTPUT_CONNECT_GPIO;
  DAC_InitStruct.OutputMode         = LL_DAC_OUTPUT_MODE_NORMAL;
  LL_DAC_Init(DAC1, LL_DAC_CHANNEL_1, &DAC_InitStruct);
  LL_DAC_DisableTrigger(DAC1, LL_DAC_CHANNEL_1);
  LL_DAC_DisableDMADoubleDataMode(DAC1, LL_DAC_CHANNEL_1);
  /** DAC channel OUT2 config 
  */
  LL_DAC_SetSignedFormat(DAC1, LL_DAC_CHANNEL_2, LL_DAC_SIGNED_FORMAT_DISABLE);
  DAC_InitStruct.OutputConnection = LL_DAC_OUTPUT_CONNECT_GPIO;
  LL_DAC_Init(DAC1, LL_DAC_CHANNEL_2, &DAC_InitStruct);
  LL_DAC_DisableTrigger(DAC1, LL_DAC_CHANNEL_2);
  LL_DAC_DisableDMADoubleDataMode(DAC1, LL_DAC_CHANNEL_2);
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
