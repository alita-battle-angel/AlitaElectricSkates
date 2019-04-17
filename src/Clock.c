#include "Clock.h"

// 1-st Stage
void Clock_HSI_Init(void) {
  RCC_DeInit();
  FLASH_SetLatency(FLASH_Latency_7);
  RCC_HSICmd(ENABLE);
  while (RCC_GetFlagStatus(RCC_FLAG_HSIRDY) != SET);
  RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

  /*
  finput   = 168 Mhz
  PLLM     = 16
  PLLM     = 336
  PLLP     = 2
  PLLQ     = 8

  FVCO = finput * (PLLN/PLLM) = 16 * (336/16) = 336 Mhz
  FPLL = FVCO/PLLP = 336/2 = 168 Mhz
  FUSB = FVCO/PLLQ = 336/7 = 48 Mhz
  AHB  Clock = FPLL = 168 Mhz;
  APB1 Clock = FPLL/DIVAPB1 = 168/8 = 21 Mhz
  APB2 Clock = FPLL/DIVAPB2 = 168/4 = 42 Mhz
  */
  RCC_PLLConfig(RCC_PLLSource_HSI, 16, 336, 2, 7);
  RCC_PLLCmd(ENABLE);
  while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) != SET);
  RCC_HCLKConfig(RCC_SYSCLK_Div1);    // 168 mhz AHB (OTG HS, ETH, DMA, CRC, GPIOx)
  RCC_PCLK1Config(RCC_HCLK_Div8);     // 21 mhz APB1 (DAC, PWR, I2Cx, SPIx)
  RCC_PCLK2Config(RCC_HCLK_Div4);     
}

// 2-nd Stage
void Clock_HSE_Init(void) {
  RCC_DeInit();
  RCC_HSICmd(ENABLE);
  while (RCC_GetFlagStatus(RCC_FLAG_HSIRDY) != SET);
  RCC_HSEConfig(RCC_HSE_ON);
  RCC_WaitForHSEStartUp();
  RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

  /*
  finput   = 8 Mhz
  PLLM     = 8
  PLLM     = 336
  PLLP     = 2
  PLLQ     = 8

  FVCO = finput * (PLLN/PLLM) = 8 * (336/8) = 336 Mhz
  FPLL = FVCO/PLLP = 336/2 = 168 Mhz
  FUSB = FVCO/PLLQ = 336/7 = 48 Mhz
  AHB  Clock = FPLL = 168 Mhz;
  APB1 Clock = FPLL/DIVAPB1 = 168/8 = 21 Mhz
  APB2 Clock = FPLL/DIVAPB2 = 168/4 = 42 Mhz
  */
  RCC_PLLConfig(RCC_PLLSource_HSE, 8, 336, 2, 7);
  RCC_PLLCmd(ENABLE);
  while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) != SET);
  RCC_HCLKConfig(RCC_SYSCLK_Div1);    // 168 mhz AHB (OTG HS, ETH, DMA, CRC, GPIOx)
  RCC_PCLK1Config(RCC_HCLK_Div8);     // 21 mhz APB1 (DAC, PWR, I2Cx, SPIx)
  RCC_PCLK2Config(RCC_HCLK_Div4);     // 42 mhz APB2
  SYSCFG_CompensationCellCmd(ENABLE);
}

void Clock_InitUSB(void) {
  RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_OTG_FS, ENABLE);
}

void RCC_IRQHandler(void){
  if(RCC_GetITStatus(RCC_IT_CSS) == SET){
    Clock_HSI_Init();
    RCC_ClearITPendingBit(RCC_IT_CSS);
  } 
}
