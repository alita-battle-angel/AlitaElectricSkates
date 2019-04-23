#include "Button.h"

void Button_Init(Button_InitStructure* Button) {
  GPIO_InitTypeDef GPIO_InitOpts;
  GPIO_InitOpts.GPIO_Pin   = Button->Pin;
  GPIO_InitOpts.GPIO_Mode  = GPIO_Mode_IN;
  GPIO_InitOpts.GPIO_OType = GPIO_OType_PP;
  GPIO_InitOpts.GPIO_PuPd  = GPIO_PuPd_DOWN;
  GPIO_InitOpts.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_Init(Button->Port, &GPIO_InitOpts);
  Button->LevelCounter          = 0;
  Button->CurrentEdge           = Button_SignalEdge_Falling;
}

void Button_CheckPressState(Button_InitStructure* Button) {
  if (Button->OnButtonStateChanged) {
    if (Button->CurrentButtonState != Button->LastButtonState) {
      Button->OnButtonStateChanged(Button->CurrentButtonState);
    }
  }
}

void Button_CheckEdgeSignal(Button_InitStructure* Button) {
  if (Button->OnEdgeStateChanged) {
    if (Button->CurrentButtonState == Button_State_Pressed &&
        Button->LastButtonState    == Button_State_NotPressed) {
      Button->CurrentEdge = Button_SignalEdge_Rissing;
    }
    if (Button->CurrentButtonState == Button_State_NotPressed &&
        Button->LastButtonState    == Button_State_Pressed) {
      Button->CurrentEdge = Button_SignalEdge_Falling;
    }
    Button->OnEdgeStateChanged(Button->CurrentEdge);
  }
}

void Button_Thershold(Button_InitStructure* Button) {
  int InputValue = GPIO_ReadInputDataBit(Button->Port, Button->Pin) ? 1 : -1;
  Button->LevelCounter += InputValue;
  if (Button->LevelCounter == Button->StableStateThershold) {
    Button->CurrentButtonState = Button_State_Pressed;
    Button->LevelCounter = 0;
  }
  if (Button->LevelCounter == -Button->StableStateThershold) {
    Button->CurrentButtonState = Button_State_NotPressed;
    Button->LevelCounter = 0;
  }
  Button_CheckEdgeSignal(Button);
  Button_CheckPressState(Button);
  Button->LastButtonState = Button->CurrentButtonState;
}

void Button_Check(Button_InitStructure* Button) {
  Button_Thershold(Button);
}
