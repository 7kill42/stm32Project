#ifndef __SYSTICK_H__
#define __SYSTICK_H__
#include "stm32f4xx.h"

void Systick_Init(int32_t Systick);
void delay_nms(uint32_t n);

#endif
