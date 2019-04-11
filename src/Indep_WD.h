#ifndef _INDEPENDENT_WATCHDOG_
#define _INDEPENDENT_WATCHDOG_
#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx.h"

void iWD_Init(void);
int  iWD_Fault_is_Detected(void);
void iWD_RefreshCountet(void);

#ifdef __cplusplus
}
#endif
#endif
