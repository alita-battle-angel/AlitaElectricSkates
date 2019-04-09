#ifndef _Clock_
#define _Clock_
#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx.h"

void Clock_HSI_Init(void);
void Clock_HSE_Init(void);
void Clock_InitUSB(void);

#ifdef __cplusplus
}
#endif
#endif
