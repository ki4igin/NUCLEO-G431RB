#ifndef __STM32G4_RCC_H
#define __STM32G4_RCC_H

// Includes --------------------------------------------------------------------
#include "stm32g4xx.h"
// Typedef ---------------------------------------------------------------------

// PLL entry clock source
typedef enum
{
  RCC_PLLSOURCE_NONE = 0U, /*!< No clock */
  RCC_PLLSOURCE_HSI  = 2U, /*!< HSI16 clock selected as PLL entry clock source */
  RCC_PLLSOURCE_HSE  = 3U  /*!< HSE clock selected as PLL entry clock source */
} RCC_PLLSOURCE_TypeDef;

// PLL division factor
typedef enum
{
  RCC_PLLM_1  = 0U,  /*!< PLL division factor by 1 */
  RCC_PLLM_2  = 1U,  /*!< PLL division factor by 2 */
  RCC_PLLM_3  = 2U,  /*!< PLL division factor by 3 */
  RCC_PLLM_4  = 3U,  /*!< PLL division factor by 4 */
  RCC_PLLM_5  = 4U,  /*!< PLL division factor by 5 */
  RCC_PLLM_6  = 5U,  /*!< PLL division factor by 6 */
  RCC_PLLM_7  = 6U,  /*!< PLL division factor by 7 */
  RCC_PLLM_8  = 7U,  /*!< PLL division factor by 8 */
  RCC_PLLM_9  = 8U,  /*!< PLL division factor by 9 */
  RCC_PLLM_10 = 9U,  /*!< PLL division factor by 10 */
  RCC_PLLM_11 = 10U, /*!< PLL division factor by 11 */
  RCC_PLLM_12 = 11U, /*!< PLL division factor by 12 */
  RCC_PLLM_13 = 12U, /*!< PLL division factor by 13 */
  RCC_PLLM_14 = 13U, /*!< PLL division factor by 14 */
  RCC_PLLM_15 = 14U, /*!< PLL division factor by 15 */
  RCC_PLLM_16 = 15U  /*!< PLL division factor by 16 */

} RCC_PLLM_TypeDef;

// PLL division factor (PLLR)
typedef enum
{
  RCC_PLLR_2 = 0U, /*!< Main PLL division factor for PLLCLK (system clock) by 2 */
  RCC_PLLR_4 = 1U, /*!< Main PLL division factor for PLLCLK (system clock) by 4 */
  RCC_PLLR_6 = 2U, /*!< Main PLL division factor for PLLCLK (system clock) by 6 */
  RCC_PLLR_8 = 3U  /*!< Main PLL division factor for PLLCLK (system clock) by 8 */
} RCC_PLLR_TypeDef;

// RCC_LL_EC_PLLP_DIV  PLL division factor (PLLP)
typedef enum
{
  RCC_PLLP_2  = 2U,  /*!< Main PLL division factor for PLLP output by 2 */
  RCC_PLLP_3  = 3U,  /*!< Main PLL division factor for PLLP output by 3 */
  RCC_PLLP_4  = 4U,  /*!< Main PLL division factor for PLLP output by 4 */
  RCC_PLLP_5  = 5U,  /*!< Main PLL division factor for PLLP output by 5 */
  RCC_PLLP_6  = 6U,  /*!< Main PLL division factor for PLLP output by 6 */
  RCC_PLLP_7  = 7U,  /*!< Main PLL division factor for PLLP output by 7 */
  RCC_PLLP_8  = 8U,  /*!< Main PLL division factor for PLLP output by 8 */
  RCC_PLLP_9  = 9U,  /*!< Main PLL division factor for PLLP output by 9 */
  RCC_PLLP_10 = 10U, /*!< Main PLL division factor for PLLP output by 10 */
  RCC_PLLP_11 = 11U, /*!< Main PLL division factor for PLLP output by 11 */
  RCC_PLLP_12 = 12U, /*!< Main PLL division factor for PLLP output by 12 */
  RCC_PLLP_13 = 13U, /*!< Main PLL division factor for PLLP output by 13 */
  RCC_PLLP_14 = 14U, /*!< Main PLL division factor for PLLP output by 14 */
  RCC_PLLP_15 = 15U, /*!< Main PLL division factor for PLLP output by 15 */
  RCC_PLLP_16 = 16U, /*!< Main PLL division factor for PLLP output by 16 */
  RCC_PLLP_17 = 17U, /*!< Main PLL division factor for PLLP output by 17 */
  RCC_PLLP_18 = 18U, /*!< Main PLL division factor for PLLP output by 18 */
  RCC_PLLP_19 = 19U, /*!< Main PLL division factor for PLLP output by 19 */
  RCC_PLLP_20 = 20U, /*!< Main PLL division factor for PLLP output by 20 */
  RCC_PLLP_21 = 21U, /*!< Main PLL division factor for PLLP output by 21 */
  RCC_PLLP_22 = 22U, /*!< Main PLL division factor for PLLP output by 22 */
  RCC_PLLP_23 = 23U, /*!< Main PLL division factor for PLLP output by 23 */
  RCC_PLLP_24 = 24U, /*!< Main PLL division factor for PLLP output by 24 */
  RCC_PLLP_25 = 25U, /*!< Main PLL division factor for PLLP output by 25 */
  RCC_PLLP_26 = 26U, /*!< Main PLL division factor for PLLP output by 26 */
  RCC_PLLP_27 = 27U, /*!< Main PLL division factor for PLLP output by 27 */
  RCC_PLLP_28 = 28U, /*!< Main PLL division factor for PLLP output by 28 */
  RCC_PLLP_29 = 29U, /*!< Main PLL division factor for PLLP output by 29 */
  RCC_PLLP_30 = 30U, /*!< Main PLL division factor for PLLP output by 30 */
  RCC_PLLP_31 = 31U  /*!< Main PLL division factor for PLLP output by 31 */
} RCC_PLLP_TypeDef;

// PLL division factor (PLLQ)
typedef enum
{
  RCC_PLLQ_2 = 0U, /*!< Main PLL division factor for PLLQ output by 2 */
  RCC_PLLQ_4 = 1U, /*!< Main PLL division factor for PLLQ output by 4 */
  RCC_PLLQ_6 = 2U, /*!< Main PLL division factor for PLLQ output by 6 */
  RCC_PLLQ_8 = 3U  /*!< Main PLL division factor for PLLQ output by 8 */
} RCC_PLLQ_TypeDef;

typedef enum
{
  RCC_PLLN_8   = 8,
  RCC_PLLN_9   = 9,
  RCC_PLLN_10  = 10,
  RCC_PLLN_11  = 11,
  RCC_PLLN_12  = 12,
  RCC_PLLN_13  = 13,
  RCC_PLLN_14  = 14,
  RCC_PLLN_15  = 15,
  RCC_PLLN_16  = 16,
  RCC_PLLN_17  = 17,
  RCC_PLLN_18  = 18,
  RCC_PLLN_19  = 19,
  RCC_PLLN_20  = 20,
  RCC_PLLN_21  = 21,
  RCC_PLLN_22  = 22,
  RCC_PLLN_23  = 23,
  RCC_PLLN_24  = 24,
  RCC_PLLN_25  = 25,
  RCC_PLLN_26  = 26,
  RCC_PLLN_27  = 27,
  RCC_PLLN_28  = 28,
  RCC_PLLN_29  = 29,
  RCC_PLLN_30  = 30,
  RCC_PLLN_31  = 31,
  RCC_PLLN_32  = 32,
  RCC_PLLN_33  = 33,
  RCC_PLLN_34  = 34,
  RCC_PLLN_35  = 35,
  RCC_PLLN_36  = 36,
  RCC_PLLN_37  = 37,
  RCC_PLLN_38  = 38,
  RCC_PLLN_39  = 39,
  RCC_PLLN_40  = 40,
  RCC_PLLN_41  = 41,
  RCC_PLLN_42  = 42,
  RCC_PLLN_43  = 43,
  RCC_PLLN_44  = 44,
  RCC_PLLN_45  = 45,
  RCC_PLLN_46  = 46,
  RCC_PLLN_47  = 47,
  RCC_PLLN_48  = 48,
  RCC_PLLN_49  = 49,
  RCC_PLLN_50  = 50,
  RCC_PLLN_51  = 51,
  RCC_PLLN_52  = 52,
  RCC_PLLN_53  = 53,
  RCC_PLLN_54  = 54,
  RCC_PLLN_55  = 55,
  RCC_PLLN_56  = 56,
  RCC_PLLN_57  = 57,
  RCC_PLLN_58  = 58,
  RCC_PLLN_59  = 59,
  RCC_PLLN_60  = 60,
  RCC_PLLN_61  = 61,
  RCC_PLLN_62  = 62,
  RCC_PLLN_63  = 63,
  RCC_PLLN_64  = 64,
  RCC_PLLN_65  = 65,
  RCC_PLLN_66  = 66,
  RCC_PLLN_67  = 67,
  RCC_PLLN_68  = 68,
  RCC_PLLN_69  = 69,
  RCC_PLLN_70  = 70,
  RCC_PLLN_71  = 71,
  RCC_PLLN_72  = 72,
  RCC_PLLN_73  = 73,
  RCC_PLLN_74  = 74,
  RCC_PLLN_75  = 75,
  RCC_PLLN_76  = 76,
  RCC_PLLN_77  = 77,
  RCC_PLLN_78  = 78,
  RCC_PLLN_79  = 79,
  RCC_PLLN_80  = 80,
  RCC_PLLN_81  = 81,
  RCC_PLLN_82  = 82,
  RCC_PLLN_83  = 83,
  RCC_PLLN_84  = 84,
  RCC_PLLN_85  = 85,
  RCC_PLLN_86  = 86,
  RCC_PLLN_87  = 87,
  RCC_PLLN_88  = 88,
  RCC_PLLN_89  = 89,
  RCC_PLLN_90  = 90,
  RCC_PLLN_91  = 91,
  RCC_PLLN_92  = 92,
  RCC_PLLN_93  = 93,
  RCC_PLLN_94  = 94,
  RCC_PLLN_95  = 95,
  RCC_PLLN_96  = 96,
  RCC_PLLN_97  = 97,
  RCC_PLLN_98  = 98,
  RCC_PLLN_99  = 99,
  RCC_PLLN_100 = 100,
  RCC_PLLN_101 = 101,
  RCC_PLLN_102 = 102,
  RCC_PLLN_103 = 103,
  RCC_PLLN_104 = 104,
  RCC_PLLN_105 = 105,
  RCC_PLLN_106 = 106,
  RCC_PLLN_107 = 107,
  RCC_PLLN_108 = 108,
  RCC_PLLN_109 = 109,
  RCC_PLLN_110 = 110,
  RCC_PLLN_111 = 111,
  RCC_PLLN_112 = 112,
  RCC_PLLN_113 = 113,
  RCC_PLLN_114 = 114,
  RCC_PLLN_115 = 115,
  RCC_PLLN_116 = 116,
  RCC_PLLN_117 = 117,
  RCC_PLLN_118 = 118,
  RCC_PLLN_119 = 119,
  RCC_PLLN_120 = 120,
  RCC_PLLN_121 = 121,
  RCC_PLLN_122 = 122,
  RCC_PLLN_123 = 123,
  RCC_PLLN_124 = 124,
  RCC_PLLN_125 = 125,
  RCC_PLLN_126 = 126,
  RCC_PLLN_127 = 127
} RCC_PLLN_TypeDef;

// Macro -----------------------------------------------------------------------

// Variables -------------------------------------------------------------------

// Function prototypes ---------------------------------------------------------

// Inline Functions ------------------------------------------------------------
__STATIC_FORCEINLINE void RccPllConfigDiv(RCC_PLLSOURCE_TypeDef source,
                                          RCC_PLLM_TypeDef      pllm,
                                          RCC_PLLN_TypeDef      plln,
                                          RCC_PLLR_TypeDef      pllr,
                                          RCC_PLLQ_TypeDef      pllq,
                                          RCC_PLLP_TypeDef      pllp)
{
  MODIFY_REG(RCC->PLLCFGR,
             RCC_PLLCFGR_PLLSRC | RCC_PLLCFGR_PLLM | RCC_PLLCFGR_PLLN |
                 RCC_PLLCFGR_PLLR | RCC_PLLCFGR_PLLQ | RCC_PLLCFGR_PLLP,
             source << RCC_PLLCFGR_PLLSRC_Pos | pllm << RCC_PLLCFGR_PLLM_Pos |
                 plln << RCC_PLLCFGR_PLLN_Pos | pllr << RCC_PLLCFGR_PLLR_Pos |
                 pllq << RCC_PLLCFGR_PLLQ_Pos | pllp << RCC_PLLCFGR_PLLP_Pos);
}

#endif
