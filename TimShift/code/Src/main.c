// Includes --------------------------------------------------------------------
#include "main.h"
#include "gpio.h"
#include "uart.h"
#include "rcc.h"
#include "tim.h"
#include "spi.h"
#include "AD9102.h"
#include "adc.h"
#include "dac.h"
#include "i2c.h"
#include "stm32g4xx_ll_adc.h"
#include "stm32g4xx_ll_dac.h"
#include "stm32g4xx_ll_tim.h"
#include "FIlterHP.h"

// Private Typedef -------------------------------------------------------------
typedef struct
{
  uint8_t f60 : 1;
  uint8_t complete : 1;
} Flag_t;
// Private Macro ---------------------------------------------------------------
#define MOVMEANLENGHT (128)
#define GAIN1         10
#define GAIN2         10
// Private Variables -----------------------------------------------------------
uint16_t adcValueMid1 = 2048;
uint16_t adcValueMid2 = 2048;
uint16_t dacValue1    = 0;
uint16_t dacValue2    = 0;
Flag_t   flag         = {0};
float    movMeanSum1;
float    movMeanSum2;
float    movMeanBuf1[MOVMEANLENGHT];
float    movMeanBuf2[MOVMEANLENGHT];
// Private Function prototypes -------------------------------------------------
void Delay_ms(uint32_t delay);

// Functions -------------------------------------------------------------------
int main(void)
{
  // MCU Configuration
  // Reset of all peripherals, Initializes the Flash interface and the Systick.
  RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
  RCC->APB1ENR1 |= RCC_APB1ENR1_PWREN;
  NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

  // System interrupt init

  // Disable the internal Pull-Up in Dead Battery pins of UCPD peripheral
  PWR->CR3 &= ~PWR_CR3_UCPD_DBDIS;
  // Configure the system clock
  RccInit();
  SysTickInit();
  // Initialize all configured peripherals
  GpioInit();
  UartInit();
  UsartEnable(USART1);
  UsartSendStr(USART1, (uint8_t *)"Init Start\n");
  MX_ADC1_Init();
  MX_ADC2_Init();
  MX_I2C2_Init();
  MX_DAC1_Init();
  MX_TIM4_Init();
  LL_TIM_ClearFlag_UPDATE(TIM4);
  MX_TIM2_Init();
  MX_TIM3_Init();
  LL_TIM_DisableCounter(TIM4);
  MX_TIM6_Init();
  Spi2Init();
  LL_SPI_Enable(SPI2);
  //AD9102Init();
  LL_SPI_Disable(SPI2);

  //  LedOn();
  //  Delay_ms(1000);
  //  LedOff();
  //  Delay_ms(1000);
  //  LedOn();
  //  Delay_ms(1000);
  //  LedOff();
  //  UsartSendStr(USART1, (uint8_t *)"Init Complete\n");
  //  Delay_ms(2000);

  GpioOutSet(VEN_TRX_Port, VEN_TRX_Pin);
  Delay_ms(100);
  GpioOutSet(VCO_DIS_Port, VCO_DIS_Pin);

  LL_ADC_EnableIT_EOC(ADC1);
  LL_ADC_EnableIT_EOC(ADC2);
  LL_ADC_Enable(ADC1);
  LL_ADC_Enable(ADC2);
  LL_ADC_REG_StartConversion(ADC1);
  LL_ADC_REG_StartConversion(ADC2);
  //  LL_TIM_SetCounter(TIM2, 0);
  //	LL_TIM_SetCounter(TIM3, 600);
  LL_TIM_CC_EnableChannel(TIM2, LL_TIM_CHANNEL_CH1);
  LL_TIM_CC_EnableChannel(TIM3, LL_TIM_CHANNEL_CH1);
  LL_TIM_EnableCounter(TIM2);
  LL_TIM_EnableCounter(TIM3);

  Delay_ms(5000);
  LL_TIM_EnableCounter(TIM6);
  LL_TIM_EnableIT_UPDATE(TIM6);
  //   LL_TIM_EnableCounter(TIM4);

//FLASH->KEYR = 0x45670123;
//FLASH->KEYR = 0xCDEF89AB;
//	FLASH->OPTKEYR =  0x08192A3B;
//	FLASH->OPTKEYR =  0x4C5D6E7F;
//	FLASH->OPTR &= ~FLASH_OPTR_nBOOT0;
//	FLASH->OPTR &= ~FLASH_OPTR_nSWBOOT0;
//	FLASH->OPTR |= FLASH_OPTR_nBOOT1;
	
	Delay_ms(100);

  // Infinite loop
  while (1)
  {
    if ((dacValue1 / dacValue2) > 2)
    {
      flag.f60 = 1;
    }

    if ((flag.f60 == 1) && (dacValue2 > dacValue1))
    {
      flag.complete = 1;
    }

    if (flag.complete == 1)
    {
      LedOn();
      Delay_ms(500);
      flag.f60      = 0;
      flag.complete = 0;
      LedOff();
    }
  }
}

void Adc1ConvComplete_Callback()
{
  //  LL_GPIO_SetOutputPin(LED_GPIO_Port, LED_Pin);
  //  LL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
  static uint16_t count;
  // LedOn();
  uint16_t dataADC1 = LL_ADC_REG_ReadConversionData12(ADC1);
  //	 uint16_t dataADC1 = 0;

  uint16_t sendWorld = 0x8000 | (flag.f60 << 14) | (flag.complete << 13) | dataADC1;
  UsartSendWord(USART1, sendWorld);

  //  LL_DAC_ConvertData12RightAligned(DAC, LL_DAC_CHANNEL_1, dataADC1);

  float freq1 = iir_Dopler1((float)(dataADC1 - adcValueMid1));
  //  freq1 = (float)(dataADC1 - adcValueMid1);
  movMeanSum1        = movMeanSum1 - movMeanBuf1[count] + GAIN1 * freq1 * freq1;
  movMeanBuf1[count] = movMeanSum1 / MOVMEANLENGHT;
  dacValue1          = (uint16_t)(movMeanBuf1[count] / 1);
  count              = (count + 1) & (MOVMEANLENGHT - 1);

  //  ����� ������� �� ���
  dacValue1 = dacValue1 > 0xFFF ? 0xFFF : dacValue1;
  //  LL_DAC_ConvertData12RightAligned(DAC, LL_DAC_CHANNEL_1, ((dacValue1 << 6)/dacValue2));
  LL_DAC_ConvertData12RightAligned(DAC, LL_DAC_CHANNEL_1, dacValue1);

  //  LL_GPIO_ResetOutputPin(LED_GPIO_Port, LED_Pin);
  //  LL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
  // LedOff();
}

void Adc2ConvComplete_Callback()
{
  static uint16_t count;
  static uint8_t  cnt;

  //  LL_GPIO_SetOutputPin(LED_GPIO_Port, LED_Pin);
  //  LL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);

  uint16_t dataADC2 = LL_ADC_REG_ReadConversionData12(ADC2);

  uint16_t sendWorld = (cnt << 12) | dataADC2;
  UsartSendWord(USART1, sendWorld);
  cnt = (cnt + 1) & 0x7;
  //  LL_DAC_ConvertData12RightAligned(DAC, LL_DAC_CHANNEL_2, dataADC2);
  //
  float freq2 = iir_Dopler2((float)(dataADC2 - adcValueMid2));
  //  freq2 = (float)(dataADC2 - adcValueMid2);
  movMeanSum2        = movMeanSum2 - movMeanBuf2[count] + GAIN2 * freq2 * freq2;
  movMeanBuf2[count] = movMeanSum2 / MOVMEANLENGHT;
  dacValue2          = (uint16_t)(movMeanBuf2[count] / 1);
  count              = (count + 1) & (MOVMEANLENGHT - 1);

  //  ����� ������� �� ���
  dacValue2 = dacValue2 > 0xFFF ? 0xFFF : dacValue2;
  //  LL_DAC_ConvertData12RightAligned(DAC, LL_DAC_CHANNEL_1, ((dacValue1 << 6)/dacValue2));
  LL_DAC_ConvertData12RightAligned(DAC, LL_DAC_CHANNEL_2, dacValue2);
  //  LL_GPIO_ResetOutputPin(LED_GPIO_Port, LED_Pin);
  //  LL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
}

void Tim6Update_Callback(void)
{
  //	if (TIM3->CNT >0)
  //	{
  //
  //	}
  // TIM2->CNT -= 12 - 1;
  TIM3->CNT -= 10 - 1;
}

void Delay_ms(uint32_t delay)
{
  // __IO uint32_t temp = SysTick->CTRL;
  delay++;
  while (delay)
  {
    if (SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk)
    {
      delay--;
    }
  }
}

void Error_Handler(void)
{
  while (1)
  {
    LedOn();
    Delay_ms(300);
    LedOff();
    Delay_ms(300);
  }
}
// End File -------------------------------------------------------------------