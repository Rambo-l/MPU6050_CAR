#ifndef __PWM_H__
#define __PWM_H__

#include "stm32f10x.h"
void TIM4_PWM_Init(u16 arr,u16 psc); 
void PWM_Init(u16 arr,u16 psc);    //arr-��ʱ�����ڣ�psc--��ʱ��ʱ�ӷ�Ƶ
void TIM2_Init_Init(u16 arr,u16 psc);
#endif
