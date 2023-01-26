
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "dac.h"
#include "usart.h"
#include "tim.h"
#include "gpio.h"
#include "debug.h"
#include "tools.h"

#include "stm32g4xx_ll_tim.h"
#include "gpio_ex.h"

/* Private includes ----------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/* Private user code ---------------------------------------------------------*/

/**
 * @brief  The application entry point.
 * @retval int
 */

void cmd_work(uint32_t cmd)
{
    switch (cmd) {
    case str2uint('b', 'l', 'i', 'k'): // blik
        led_on();
        delay_ms(200);
        led_off();
        delay_ms(200);
        led_on();
        delay_ms(200);
        led_off();
        break;
    case str2uint('q', 'w', 'e', 'r'): // qwer
        NVIC_SystemReset();
        break;

    default:
        // DebugSendArray(&cmd, sizeof(cmd));
        break;
    }

    if ((cmd >> 3) == 'd') {
        LL_DAC_ConvertData12RightAligned(DAC1, LL_DAC_CHANNEL_2, cmd & 0xFFF);
    }
}

int main(void)
{
    /* MCU Configuration--------------------------------------------------------*/

    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);

    /* System interrupt init*/
    NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

    /** Disable the internal Pull-Up in Dead Battery pins of UCPD peripheral
     */
    LL_PWR_DisableUCPDDeadBattery();

    /* Configure the system clock */
    SystemClock_Config();

    /* Initialize all configured peripherals */
    MX_GPIO_Init();
    MX_DAC1_Init();
    MX_LPUART1_UART_Init();
    MX_TIM4_Init();

    debug_printf("Base Init Complete\n");

    LL_TIM_EnableCounter(TIM4);
    LL_TIM_CC_EnableChannel(TIM4, LL_TIM_CHANNEL_CH1);
    LL_TIM_CC_EnableChannel(TIM4, LL_TIM_CHANNEL_CH2);

    /* Infinite loop */

    while (1) {
        static uint16_t timeout_cnt = 0;
        if (READ_BIT(LPUART1->ISR, USART_ISR_RXFT) == (USART_ISR_RXFT)) {
            timeout_cnt = 0;
            uint32_t cmd = 0;
            uint8_t *pcmd = (uint8_t *)&cmd;
            for (uint32_t i = 0; i < 4; i++) {
                *pcmd++ = LPUART1->RDR;
            }
            cmd_work(__REV(cmd));
        }
        if (READ_BIT(LPUART1->ISR, USART_ISR_RXNE) == (USART_ISR_RXNE)) {
            timeout_cnt++;
        }
        if (timeout_cnt >= 9999) {
            while (READ_BIT(LPUART1->ISR, USART_ISR_RXNE) == (USART_ISR_RXNE)) {
                volatile uint8_t temp = LPUART1->RDR;
                (void)temp;
            }
            timeout_cnt = 0;
        }
    }
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void)
{
    LL_FLASH_SetLatency(LL_FLASH_LATENCY_4);
    while (LL_FLASH_GetLatency() != LL_FLASH_LATENCY_4) {
    }
    LL_PWR_SetRegulVoltageScaling(LL_PWR_REGU_VOLTAGE_SCALE1);
    LL_RCC_HSE_Enable();
    /* Wait till HSE is ready */
    while (LL_RCC_HSE_IsReady() != 1) {
    }

    LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_2, 25, LL_RCC_PLLR_DIV_2);
    LL_RCC_PLL_EnableDomain_SYS();
    LL_RCC_PLL_Enable();
    /* Wait till PLL is ready */
    while (LL_RCC_PLL_IsReady() != 1) {
    }

    LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);
    LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_2);
    /* Wait till System clock is ready */
    while (LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL) {
    }

    /* Insure 1�s transition state at intermediate medium speed clock*/
    for (__IO uint32_t i = (170 >> 1); i != 0; i--) {
        ;
    }

    /* Set AHB prescaler*/
    LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
    LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
    LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_1);

    LL_Init1msTick(150000000);

    LL_SetSystemCoreClock(150000000);
}

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void)
{
    /* User can add his own implementation to report the HAL error return state */
    __disable_irq();
    while (1) {
    }
}

#ifdef USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line)
{
    /* User can add his own implementation to report the file name and line number,
       ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
}
#endif /* USE_FULL_ASSERT */
