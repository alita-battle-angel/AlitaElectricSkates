#include "FeedBackADC.h"

void  FeedBackADC_Init(void)
{
  FeedBackADC_GPIOInit(); 
  FeedBackADC_ClockInit();
}

void FeedBackADC_ClockInit(void)
{
 /*
   APB2 CLK             = 21 Mhz
   ADC_Prescaler        = 2
   ADC_CLK              = 10.5 Mhz
   T_ADC_CLK            = 0.095 uSec
   Channel_SampleTime   = 144(144*0.095us ->14 uSec)
   F_Channel_Conversiom = 67 Khz 
   */
  
  ADC_InitTypeDef        ADCSetup;
  ADC_CommonInitTypeDef  ComonInitADC;
  ADC_CommonStructInit(&ComonInitADC);
  ComonInitADC.ADC_Prescaler		= ADC_Prescaler_Div2;// 21Mhz(APB2 CLK) /2 = 10.5 Mhz(100us)
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
  ADC_StructInit(&ADCSetup);
  ADCSetup.ADC_ContinuousConvMode	= ENABLE;
  ADCSetup.ADC_DataAlign	        = ADC_DataAlign_Right;
  ADCSetup.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
  ADCSetup.ADC_Resolution           = ADC_Resolution_12b;
  ADCSetup.ADC_ScanConvMode         = ENABLE;
  ADCSetup.ADC_NbrOfConversion      = 1;
  ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_144Cycles);//144*0.1ms = 14.4 ms  - 70 KHz;
  ADC_Init(ADC1,&ADCSetup);
  ADC_Cmd(ADC1,ENABLE);
  ADC_SoftwareStartConv(ADC1);
}

void FeedBackADC_GPIOInit(void)
{
  RCC_AHB1PeriphClockCmd (RCC_AHB1Periph_GPIOA,ENABLE); 
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Pin          = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode         = GPIO_Mode_AN;          
  GPIO_Init (GPIOA, &GPIO_InitStructure); 
}

uint16_t FeedBackADC_GetMeasuredVoltageLevel(void)
{
  while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC)!=SET){};
  uint16_t Value = ADC_GetConversionValue(ADC1);
  return  Value;
}

double FeedBackADC_GetMeasuredVoltageWithAvergage(uint32_t AvergageFactor)
{
	double Value = 0;
	for(uint32_t i = 0; i < AvergageFactor; i++) {
 		Value+=(double)FeedBackADC_GetMeasuredVoltageLevel();
	}
	Value/=(double)AvergageFactor;
	return Value;
}

