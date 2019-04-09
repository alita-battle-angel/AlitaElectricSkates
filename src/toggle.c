#include "stm32f4xx.h"

#include "LED.h"
#include "Clock.h"
#include "Timer.h"

const uint16_t delay = 100;
const LED leds[] = { LED_GREEN, LED_RED, LED_ORANGE, LED_BLUE };

int main() {
  Clock_HSI_Init();
  Clock_HSE_Init();
  LED_Init();
  Timer_WaitInit();

  while (1) {
    for (uint8_t i = 0; i < sizeof(leds) / sizeof(leds[0]); i++) {
      LED led = leds[i];
      LED_On(led);
      Timer_WaitMilisec(delay);
      LED_Off(led);
    }
  }
}
