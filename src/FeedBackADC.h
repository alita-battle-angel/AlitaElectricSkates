#include "stm32f4xx.h"
#include <stdio.h>
#ifndef _FADCC_
#define _FADCC_
#ifdef __cplusplus
extern "C" {
#endif  
void  FeedBackADC_Init(void);
void FeedBackADC_ClockInit(void);
void FeedBackADC_GPIOInit(void);
uint16_t FeedBackADC_GetMeasuredVoltageLevel(void);
double FeedBackADC_GetMeasuredVoltageWithAvergage(uint32_t AvergageFactor);
#ifdef __cplusplus
}
#endif   
#endif 