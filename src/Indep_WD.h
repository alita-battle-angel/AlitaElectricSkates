#ifndef _INDEPENDET_WATCHDOG_
#define _INDEPENDET_WATCHDOG_

#include "stm32f4xx.h"

#ifdef __cplusplus
 extern "C" {
#endif 
void iWD_Init(void);
int  iWD_Fault_is_Detected(void);
void iWD_RefreshCountet(void);
#ifdef __cplusplus
}
#endif 
#endif