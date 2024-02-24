#ifndef __LED_H
#define __LED_H
#include "stm32f4xx.h"
void LED_Init(void);

#define LED1_Open GPIO_ResetBits(GPIOE, GPIO_Pin_8)
#define LED1_Close GPIO_SetBits(GPIOE, GPIO_Pin_8)

#define LED2_Open GPIO_ResetBits(GPIOE, GPIO_Pin_9)
#define LED2_Close GPIO_SetBits(GPIOE, GPIO_Pin_9)

#define LED3_Open GPIO_ResetBits(GPIOE, GPIO_Pin_10)
#define LED3_Close GPIO_SetBits(GPIOE, GPIO_Pin_10)

#endif
