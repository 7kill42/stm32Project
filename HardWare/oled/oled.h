#ifndef __OLED_H__
#define __OLED_H__

#include "stm32f4xx.h"
#include "iic.h"


void WriteOLedCmd(u8 cmd);
void WriteOLedData(u8 data);
void OLED_Set_Position(u8 x, u8 y);
void OLed_Fill(u8 data);
void oled_init(void);
void OLed_Write_chinese(u8 x , u8 y,char* data);
void OLed_Write_String(u8 x , u8 y,char* str);
#endif 
