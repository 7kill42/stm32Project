#ifndef __KEY_H__
#define __KEY_H__

#include "stm32f4xx.h"
#include "delay.h"

void Key_Init(void);
u8 Key_Scan(u8 mode);

#define KEY1 GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)
#define KEY2 GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)
#define KEY3 GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_6)
#define KEY4 GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13)

#endif
