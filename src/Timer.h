#ifndef _Timer_
#define _Timer_
#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx.h"

typedef uint32_t Time;

typedef enum TimeUnit {
  TimeUnit_Microsec = 42,
  TimeUnit_Millisec = 42000,
} TimeUnit;

void Timer_InitTime(TimeUnit unit);
void Timer_ResetTime(void);
Time Timer_GetTime(void);

void Timer_InitWait(void);
void Timer_Wait(TimeUnit unit, Time delay);
void Timer_WaitMillisec(Time delay);
void Timer_WaitMicrosec(Time delay);

#ifdef __cplusplus
}
#endif
#endif
