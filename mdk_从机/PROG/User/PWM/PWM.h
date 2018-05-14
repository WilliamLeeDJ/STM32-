#include "stm32f10x.h"
#include "stm32f10x_tim.h"
#ifndef __PWM_H
#define __PWM_H
void TIM_PWM_Init(u16 arr,u16 psc);
void TIM_Configuration(void);
void SetJointAngle(u8 ID, float angle);
#endif
