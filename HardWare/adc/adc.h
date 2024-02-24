#ifndef __ADC_H__
#define __ADC_H__

#include "stm32f4xx.h"

void Adc_Init(void);
u16 getAdc(u8 ch);
u16 getAdcAverage(u8 ch,u8 times);

#endif
