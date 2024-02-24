#ifndef __AT24C02_H__
#define __AT24C02_H__
#include "stm32f4xx.h"
#include "delay.h"
#include "iic.h"

u8 AT24C02_Init(void);
void AT24C02_Write_byte(u8 addr, u8 data);
u8 AT24C02_Read_byte(u8 addr);
void AT24C02_Write_bytes(u8 addr,u8 *data,u8 size);
void AT24C02_Read_bytes(u8 addr,u8 *buf,u8 size);

#endif
