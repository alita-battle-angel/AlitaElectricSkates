#include "LED.h"
#include "Clock.h"
#include "Timer.h"

const LED leds[] = { LED_GREEN, LED_RED, LED_ORANGE, LED_BLUE };

int main(void) {
  Clock_HSI_Init();
  Clock_HSE_Init();
  LED_Init();
  Timer_WaitInit();

  LED all_leds = 0;
  for (uint8_t i = 0; i < sizeof(leds) / sizeof(leds[0]); i++) {
    all_leds |= leds[i];
  }
  for (uint8_t i = 0; i < 3; i++) {
    LED_On(all_leds);
    Timer_WaitMilisec(75);
    LED_Off(all_leds);
    Timer_WaitMilisec(100);
  }

  while (1) {
    for (uint8_t i = 0; i < sizeof(leds) / sizeof(leds[0]); i++) {
      LED led = leds[i];
      LED_On(led);
      Timer_WaitMilisec(1000);
      LED_Off(led);
    }
  }
}
