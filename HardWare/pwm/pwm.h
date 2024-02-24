#ifndef __PWM_H__
#define __PWM_H__
#include "stm32f4xx.h"

void PWM_Init(u16 psc, u16 period);
void PWM_SetCompare1(uint16_t Compare);
#endif
