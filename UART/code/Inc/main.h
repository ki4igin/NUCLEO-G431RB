#ifndef __MAIN_H
#define __MAIN_H

// Includes --------------------------------------------------------------------

// Typedef ---------------------------------------------------------------------

// Macro -----------------------------------------------------------------------
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



#ifndef NVIC_PRIORITYGROUP_0
#define NVIC_PRIORITYGROUP_0 ((uint32_t)0x00000007) /*!< 0 bit  for pre-emption priority,
                                                                 4 bits for subpriority */
#define NVIC_PRIORITYGROUP_1 ((uint32_t)0x00000006) /*!< 1 bit  for pre-emption priority,
                                                                 3 bits for subpriority */
#define NVIC_PRIORITYGROUP_2 ((uint32_t)0x00000005) /*!< 2 bits for pre-emption priority,
                                                                 2 bits for subpriority */
#define NVIC_PRIORITYGROUP_3 ((uint32_t)0x00000004) /*!< 3 bits for pre-emption priority,
                                                                 1 bit  for subpriority */
#define NVIC_PRIORITYGROUP_4 ((uint32_t)0x00000003) /*!< 4 bits for pre-emption priority,
                                                                 0 bit  for subpriority */
#endif

// Variables -------------------------------------------------------------------

// Function prototypes ---------------------------------------------------------
void Error_Handler(void);
void Tim6Update_Callback(void);

// Inline Functions ------------------------------------------------------------

#endif
