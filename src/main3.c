void init() {
  GPIOinit();
  TimerInit();
}

void TimerInit() {
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

  uint16_t PrescalerValue = (uint16_t)((SystemCoreClock / 2) / 21000000);
  TIM_TimeBaseInitTypeDef time_init;
  time_init.TIM_Period = 665;
  time_init.TIM_Prescaler = PrescalerValue;
  time_init.TIM_ClockDivision = 0;
  time_init.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM4, &time_init);

  TIM_OCInitTypeDef oc_init;
  oc_init.TIM_OCMode = TIM_OCMode_PWM1;
  oc_init.TIM_OutputState = TIM_OutputState_Enable;
  oc_init.TIM_Pulse = 0;
  oc_init.TIM_OCPolarity = TIM_OCPolarity_High;

  TIM_OC1Init(TIM4, &oc_init);
  TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);

  oc_init.TIM_OutputState = TIM_OutputState_Enable;
  oc_init.TIM_Pulse = 0;
  TIM_OC2Init(TIM4, &oc_init);
  TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);
  oc_init.TIM_OutputState = TIM_OutputState_Enable;
  oc_init.TIM_Pulse = 0;

  TIM_OC3Init(TIM4, &oc_init);
  TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);

  oc_init.TIM_OutputState = TIM_OutputState_Enable;
  oc_init.TIM_Pulse = 0;

  TIM_OC4Init(TIM4, &oc_init);
  TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);

  TIM_ARRPreloadConfig(TIM4, ENABLE);
  TIM_Cmd(TIM4, ENABLE);
}

void GPIOinit() {
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

  GPIO_InitTypeDef gpio_init;
  gpio_init.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
  gpio_init.GPIO_Mode = GPIO_Mode_AF;
  gpio_init.GPIO_Speed = GPIO_Speed_100MHz;
  gpio_init.GPIO_OType = GPIO_OType_PP;
  gpio_init.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOD, &gpio_init);

  GPIO_PinAFConfig(GPIOD, GPIO_PinSource12, GPIO_AF_TIM4);
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource13, GPIO_AF_TIM4);
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource14, GPIO_AF_TIM4);
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource15, GPIO_AF_TIM4);
}

int main(void) {
  init();
  int t = 0;
  int i;
  while (1) {
    t++;
    TIM_SetCompare1(TIM4, t % 333);
    TIM_SetCompare2(TIM4, t % 333);
    TIM_SetCompare3(TIM4, t % 333);
    TIM_SetCompare4(TIM4, t % 333);
    for (i=0; i < 25000; ++i);
  }
}
