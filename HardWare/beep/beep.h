#ifndef __BEEP_H__
#define __BEEP_H__
#include "stm32f4xx.h"
#include "delay.h"

void Beep_Init(void);

#define Beep_On GPIO_SetBits(GPIOB, GPIO_Pin_10)
#define Beep_Off GPIO_ResetBits(GPIOB, GPIO_Pin_10)

#endif
