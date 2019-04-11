#include "ModuleUnitTests.h"
#include "LED.h"
#include "Button.h"
#include "Timer.h"

Button_InitStructure ButtonControl;
const LED leds[] = { LED_GREEN, LED_RED, LED_ORANGE, LED_BLUE };

void LED_ModuleTest(void) {
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
}

void LED_ModuleTestLoop(void) {
  for (uint8_t i = 0; i < sizeof(leds) / sizeof(leds[0]); i++) {
    LED led = leds[i];
    LED_On(led);
    Timer_WaitMilisec(100);
    LED_Off(led);
  }
}

void Button_ModuleTestLoop(void) {
  Button_Check(&ButtonControl);
}

static void Button_StateChanged(Button_State state) {
  switch(state) {
    case Button_State_Pressed: {
      LED_On(LED_GREEN);
      break;
    }
    case Button_State_NotPressed: {
      LED_Off(LED_GREEN);
      break;
    }
  }
}

static void Button_SignalChanged(Button_SignalEdge state) {
  switch(state) {
    case Button_SignalEdge_Rissing: {
      LED_On(LED_RED);
      break;
    }
    case Button_SignalEdge_Falling: {
      LED_Off(LED_RED);
      break;
    }
  }
}

void Button_ModuleTest(void) {
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
  ButtonControl.Port                 = GPIOA;
  ButtonControl.Pin                  = GPIO_Pin_0;
  ButtonControl.OnEdgeStateChanged   = Button_SignalChanged;
  ButtonControl.OnButtonStateChanged = Button_StateChanged;
  ButtonControl.StableStateThershold = 5;
  Button_Init(&ButtonControl);
}
