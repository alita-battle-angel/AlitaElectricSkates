#include "LED.h"
#include "Clock.h"
#include "Timer.h"
#include "Indep_WD.h"
#include "ModuleUnitTests.h"

int main() {
  Clock_HSI_Init();
  Clock_HSE_Init();
  LED_Init();
  Timer_WaitInit();
  LED_ModuleTest();
  if (iWD_Fault_is_Detected()) {
    LED_On(LED_RED);
  }
  Button_ModuleTest();
  iWD_Init();
  while (1) {
    iWD_RefreshCountet();
    Button_ModuleTestLoop();
  }
}
