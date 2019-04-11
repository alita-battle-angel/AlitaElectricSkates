#ifndef _ERROR_PROVIDER_
#define _ERROR_PROVIDER_
#ifdef __cplusplus
extern "C" {
#endif

void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);

#ifdef __cplusplus
}
#endif
#endif
