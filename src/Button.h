#ifndef _BUTTON_
#define _BUTTON_
#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f4xx.h"

typedef enum Button_SignalEdge
{
  Button_SignalEdge_Rissing,
  Button_SignalEdge_Falling,
}Button_SignalEdge;

typedef enum Button_State
{
  Button_State_Pressed,
  Button_State_NotPressed,
}Button_State;   
   
typedef void (*Button_PressStateChanged)(Button_State state);     
typedef void (*Button_SignalEdgeChanged)(Button_SignalEdge state); 


typedef struct Button_InitStructure
{
 GPIO_TypeDef*              Port;
 uint32_t                   Pin;
 Button_SignalEdge          CurrentEdge;
 Button_State               CurrentButtonState;
 Button_State               LastButtonState;
 uint32_t                   StableStateThershold;
 int                        LevelCounter;
 Button_PressStateChanged   OnButtonStateChanged;
 Button_SignalEdgeChanged   OnEdgeStateChanged;
}Button_InitStructure;
   
void Button_Init(Button_InitStructure* Button);
void Button_CheckPressState(Button_InitStructure* Button);
void Button_CheckEdgeSignal(Button_InitStructure* Button);
void Button_Thershold(Button_InitStructure* Button);
void Button_Check(Button_InitStructure* Button);
#ifdef __cplusplus
}
#endif 
#endif