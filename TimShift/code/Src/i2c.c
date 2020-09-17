/**
  ******************************************************************************
  * File Name          : I2C.c
  * Description        : This file provides code for the configuration
  *                      of the I2C instances.
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
#include "i2c.h"
#include "stm32g4xx_ll_i2c.h"
#include "stm32g4xx_ll_bus.h"
#include "gpio.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* I2C2 init function */
void MX_I2C2_Init(void)
{
  LL_I2C_InitTypeDef I2C_InitStruct = {0};

  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOA);
  /**I2C2 GPIO Configuration  
  PA8   ------> I2C2_SDA
  PA9   ------> I2C2_SCL 
  */
  GpioSetMode(I2C_Port, I2C_SCL_Pin | I2C_SDA_Pin, GPIO_MODE_ALTERNATE);
  GpioSetOutType(I2C_Port, I2C_SCL_Pin | I2C_SDA_Pin, GPIO_OUTPUT_OPENDRAIN);
  GpioSetSpeed(I2C_Port, I2C_SCL_Pin | I2C_SDA_Pin, GPIO_SPEED_LOW);
  GpioSetPull(I2C_Port, I2C_SCL_Pin | I2C_SDA_Pin, GPIO_PULL_UP);
  GpioSetAF(I2C_Port, I2C_SCL_Pin | I2C_SDA_Pin, GPIO_AF_4);

  /* Peripheral clock enable */
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_I2C2);

  /** I2C Initialization 
  */
  I2C_InitStruct.PeripheralMode  = LL_I2C_MODE_I2C;
  I2C_InitStruct.Timing          = 0x30A0A7FB;
  I2C_InitStruct.AnalogFilter    = LL_I2C_ANALOGFILTER_ENABLE;
  I2C_InitStruct.DigitalFilter   = 0;
  I2C_InitStruct.OwnAddress1     = 0;
  I2C_InitStruct.TypeAcknowledge = LL_I2C_ACK;
  I2C_InitStruct.OwnAddrSize     = LL_I2C_OWNADDRESS1_7BIT;
  LL_I2C_Init(I2C2, &I2C_InitStruct);
  LL_I2C_EnableAutoEndMode(I2C2);
  LL_I2C_SetOwnAddress2(I2C2, 0, LL_I2C_OWNADDRESS2_NOMASK);
  LL_I2C_DisableOwnAddress2(I2C2);
  LL_I2C_DisableGeneralCall(I2C2);
  LL_I2C_EnableClockStretching(I2C2);
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
