#ifndef __PWM_H__
#define __PWM_H__

#include "stm32f10x.h"
void TIM4_PWM_Init(u16 arr,u16 psc); 
void PWM_Init(u16 arr,u16 psc);    //arr-定时器周期，psc--定时器时钟分频
void TIM2_Init_Init(u16 arr,u16 psc);
#endif
