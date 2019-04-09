#include "Timer.h"

void Timer_WaitInit(void) {
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
  TIM_DeInit(TIM6);
  TIM_TimeBaseInitTypeDef Timer_Intit;
  Timer_Intit.TIM_ClockDivision      = TIM_CKD_DIV1;  // 21Mhz * 2x
  Timer_Intit.TIM_CounterMode        = TIM_CounterMode_Up;
  Timer_Intit.TIM_Period             = 1;
  Timer_Intit.TIM_Prescaler          = 42000;
  Timer_Intit.TIM_RepetitionCounter  = 0;
  TIM_TimeBaseInit(TIM6, &Timer_Intit);
  TIM_ClearITPendingBit(TIM6, TIM_IT_Update);
}

void Timer_TraceInit(void) {
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
  TIM_DeInit(TIM5);
  TIM_TimeBaseInitTypeDef Timer_Intit;

  Timer_Intit.TIM_ClockDivision      = TIM_CKD_DIV1;  // 21Mhz * 2x
  Timer_Intit.TIM_CounterMode        = TIM_CounterMode_Up;
  Timer_Intit.TIM_Period             = 0xFFFFFFFF - 1;
  Timer_Intit.TIM_Prescaler          = 42000;  // Milliseconds
  Timer_Intit.TIM_RepetitionCounter  = 0;
  TIM_TimeBaseInit(TIM5, &Timer_Intit);
}

void Timer_TraceBase(TimeBase Base) {
  TIM5->PSC = Base;
}

void Timer_TraceBegin(void) {
  TIM_SetCounter(TIM5, 0);
  TIM_Cmd(TIM5, ENABLE);
}

void Timer_TraceEnd(void) {
  TIM_Cmd(TIM5, DISABLE);
}

uint32_t Timer_TraceGetTime(void) {
  return TIM_GetCounter(TIM5);
}

void Timer_WaitMilisec(uint16_t Time) {
  Timer_WaitTimeBase(TimeBase_Milisec);
  TIM_SetAutoreload(TIM6, Time);
  TIM_ClearITPendingBit(TIM6, TIM_IT_Update);
  TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE);
  NVIC_EnableIRQ(TIM6_DAC_IRQn);
  TIM_Cmd(TIM6, ENABLE);
  Timer_WaitLoop();
}

void Timer_WaitMicrosec(uint16_t Time) {
  Timer_WaitTimeBase(TimeBase_Microsec);
  TIM_SetAutoreload(TIM6, Time);
  TIM_ClearITPendingBit(TIM6, TIM_IT_Update);
  TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE);
  NVIC_EnableIRQ(TIM6_DAC_IRQn);
  TIM_Cmd(TIM6, ENABLE);
  Timer_WaitLoop();
}

void TIM6_DAC_IRQHandler(void) {
  if (TIM_GetITStatus(TIM6, TIM_IT_Update)!= RESET) {
    TIM_ClearITPendingBit(TIM6, TIM_IT_Update);;
    TIM_Cmd(TIM6, DISABLE);
  }
}

void Timer_WaitLoop(void) {
  while (TIM6->CR1 & TIM_CR1_CEN);
}

void Timer_WaitTimeBase(TimeBase Base) {
  TIM6->PSC = Base;
}
