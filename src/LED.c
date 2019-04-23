#include "LED.h"

void LED_Init(void) {
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
  GPIO_InitTypeDef GPIO_InitOpts;
  GPIO_InitOpts.GPIO_Pin   = LED_GREEN | LED_RED | LED_ORANGE | LED_BLUE;
  GPIO_InitOpts.GPIO_Mode  = GPIO_Mode_OUT;
  GPIO_InitOpts.GPIO_OType = GPIO_OType_PP;
  GPIO_InitOpts.GPIO_PuPd  = GPIO_PuPd_DOWN;
  GPIO_Init(GPIOD, &GPIO_InitOpts);
}

void LED_On    (LED led) { GPIO_SetBits   (GPIOD, led); }
void LED_Off   (LED led) { GPIO_ResetBits (GPIOD, led); }
void LED_Toggle(LED led) { GPIO_ToggleBits(GPIOD, led); }
