#include "Timer.h"

void Timer_Wait_Init(void) {
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
  TIM_DeInit(TIM6);

  TIM_TimeBaseInitTypeDef TIM_BaseInit;
  TIM_BaseInit.TIM_ClockDivision     = TIM_CKD_DIV1;  // 21Mhz * 2x
  TIM_BaseInit.TIM_CounterMode       = TIM_CounterMode_Up;
  TIM_BaseInit.TIM_Period            = 0xFFFFFFFF;
  TIM_BaseInit.TIM_Prescaler         = TimeUnit_Millisec;
  TIM_BaseInit.TIM_RepetitionCounter = 0;
  TIM_TimeBaseInit(TIM6, &TIM_BaseInit);

  TIM_Cmd(TIM6, DISABLE);
}

void Timer_Trace_Init(TimeUnit unit) {
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
  TIM_DeInit(TIM5);

  TIM_TimeBaseInitTypeDef TIM_BaseInit;
  TIM_BaseInit.TIM_ClockDivision     = TIM_CKD_DIV1;  // 21Mhz * 2x
  TIM_BaseInit.TIM_CounterMode       = TIM_CounterMode_Up;
  TIM_BaseInit.TIM_Period            = 0xFFFFFFFF;
  TIM_BaseInit.TIM_Prescaler         = unit;
  TIM_BaseInit.TIM_RepetitionCounter = 0;
  TIM_TimeBaseInit(TIM5, &TIM_BaseInit);
}

void Timer_Trace_Reset() {
  TIM_SetCounter(TIM5, 0);
}

Time Timer_Trace_GetTime(void) {
  return TIM_GetCounter(TIM5);
}

void Timer_Wait(TimeUnit unit, Time delay) {
  TIM_PrescalerConfig(TIM6, unit, TIM_PSCReloadMode_Immediate);
  TIM_SetCounter(TIM6, 0);
  TIM_Cmd(TIM6, ENABLE);
  while (TIM_GetCounter(TIM6) < delay);
  TIM_Cmd(TIM6, DISABLE);
}

void Timer_WaitMillisec(Time delay) { Timer_Wait(TimeUnit_Millisec, delay); }
void Timer_WaitMicrosec(Time delay) { Timer_Wait(TimeUnit_Microsec, delay); }
