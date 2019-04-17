#include "Timer.h"

void Timer_InitWait(void) {
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
  TIM_DeInit(TIM6);

  TIM_TimeBaseInitTypeDef TIM_BaseInit;
  TIM_BaseInit.TIM_ClockDivision     = TIM_CKD_DIV1;  // 21Mhz * 2x
  TIM_BaseInit.TIM_CounterMode       = TIM_CounterMode_Up;
  TIM_BaseInit.TIM_Period            = UINT32_MAX;
  TIM_BaseInit.TIM_Prescaler         = 0;
  TIM_BaseInit.TIM_RepetitionCounter = 0;
  TIM_TimeBaseInit(TIM6, &TIM_BaseInit);
  TIM_SelectOnePulseMode(TIM6, TIM_OPMode_Single);

  TIM_Cmd(TIM6, DISABLE);
}

void Timer_InitTime(TimeUnit unit) {
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
  TIM_DeInit(TIM5);

  TIM_TimeBaseInitTypeDef TIM_BaseInit;
  TIM_BaseInit.TIM_ClockDivision     = TIM_CKD_DIV1;  // 21Mhz * 2x
  TIM_BaseInit.TIM_CounterMode       = TIM_CounterMode_Up;
  TIM_BaseInit.TIM_Period            = UINT32_MAX;
  TIM_BaseInit.TIM_Prescaler         = unit;
  TIM_BaseInit.TIM_RepetitionCounter = 0;
  TIM_TimeBaseInit(TIM5, &TIM_BaseInit);
}

void Timer_ResetTime() {
  TIM_SetCounter(TIM5, 0);
}

Time Timer_GetTime(void) {
  return TIM_GetCounter(TIM5);
}

void Timer_Wait(TimeUnit unit, Time delay) {
  if (delay == 0) return;
  TIM_PrescalerConfig(TIM6, unit, TIM_PSCReloadMode_Immediate);
  TIM_SetAutoreload(TIM6, delay);
  TIM_SetCounter(TIM6, 0);
  TIM_Cmd(TIM6, ENABLE);
  while (TIM6->CR1 & TIM_CR1_CEN);
}

void Timer_WaitMillisec(Time delay) { Timer_Wait(TimeUnit_Millisec, delay); }
void Timer_WaitMicrosec(Time delay) { Timer_Wait(TimeUnit_Microsec, delay); }
