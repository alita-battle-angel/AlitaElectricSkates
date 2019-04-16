#ifndef _LED_
#define _LED_
#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx.h"

typedef enum LED {
  LED_GREEN  = GPIO_Pin_12,
  LED_ORANGE = GPIO_Pin_13,
  LED_RED    = GPIO_Pin_14,
  LED_BLUE   = GPIO_Pin_15,
} LED;

void LED_Init(void);
void LED_On(LED led);
void LED_Off(LED led);
void LED_Toggle(LED led);

#ifdef __cplusplus
}
#endif
#endif
