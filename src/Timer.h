#ifndef _Timer_
#define _Timer_
#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx.h"

typedef enum TimeBase {
  TimeBase_Microsec = 42,
  TimeBase_Milisec  = 42000,
} TimeBase;

void Timer_TraceInit(void);
void Timer_TraceBase(TimeBase Base);
void Timer_TraceBegin(void);
void Timer_TraceEnd(void);
uint32_t Timer_TraceGetTime(void);

void Timer_WaitInit(void);
void Timer_WaitTimeBase(TimeBase Base);
void Timer_WaitMilisec(uint16_t Time);
void Timer_WaitMicrosec(uint16_t Time);
void Timer_WaitLoop(void);
void TIM6_DAC_IRQHandler(void);
void TIM3_IRQHandler(void);

#ifdef __cplusplus
}
#endif
#endif
