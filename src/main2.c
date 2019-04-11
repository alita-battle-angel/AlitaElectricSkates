int main(void) {
  GPIO_Config();
  INTTIM_Config();
  while(1);
}

void TIM2_IRQHandler(void) {
  if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) {
    TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    GPIO_ToggleBits(GPIOD, GPIO_Pin_13);
  }
}

void GPIO_Config(void) {
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

  GPIO_InitTypeDef gpio_struct;
  gpio_struct.GPIO_Pin = GPIO_Pin_13;
  gpio_struct.GPIO_Mode = GPIO_Mode_OUT;
  gpio_struct.GPIO_OType = GPIO_OType_PP;
  gpio_struct.GPIO_PuPd = GPIO_PuPd_NOPULL;
  gpio_struct.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_Init(GPIOD, &gpio_struct);
}

void INTTIM_Config(void) {
  NVIC_InitTypeDef nvic_struct;
  nvic_struct.NVIC_IRQChannel = TIM2_IRQn;
  nvic_struct.NVIC_IRQChannelPreemptionPriority = 0;
  nvic_struct.NVIC_IRQChannelSubPriority = 1;
  nvic_struct.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&nvic_struct);

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
  TIM_TimeBaseInitTypeDef tim_struct;
  tim_struct.TIM_Period = 10000 - 1;
  tim_struct.TIM_Prescaler = 168 / 2 - 1;
  tim_struct.TIM_ClockDivision = 0;
  tim_struct.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM2, &tim_struct);
  TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
  TIM_Cmd(TIM2, ENABLE);
}
