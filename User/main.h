#ifndef __MAIN_H__
#define __MAIN_H__
#include "led.h"
#include "Key.h"
#include "delay.h"
#include "Systick.h"
#include "beep.h"
#include "exti.h"
#include "timer.h"
#include "pwm.h"
#include "usart.h"
#include "dht11.h"
#include "iic.h"
#include "at24c02.h"
#include "oled.h"
#include "adc.h"
#include "stm32f4xx.h"


//��(0) ��(1) ��(2) ˭(3) ��(4) ��(5)
const unsigned char s[100][32]=
{
	{0x10,0x2C,0x24,0x24,0xA4,0xA4,0x65,0xA6,0x24,0x24,0x24,0x24,0xA4,0x34,0x0C,0x00,
	0x40,0x49,0x49,0x29,0x24,0x14,0x52,0x89,0x7F,0x04,0x0A,0x11,0x10,0x20,0x20,0x00},/*"��",0*/
	{0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0x3F,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x80,0x40,0x20,0x10,0x0C,0x03,0x00,0x00,0x00,0x03,0x0C,0x10,0x20,0x40,0x80,0x00},/*"��",1*/
	{0x00,0x80,0x60,0xF8,0x07,0x00,0xF8,0x01,0x06,0x00,0x04,0x04,0x04,0xFC,0x00,0x00,
	0x01,0x00,0x00,0xFF,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x40,0x80,0x7F,0x00,0x00},/*"��",2*/
	{0x40,0x42,0xCC,0x00,0x40,0x20,0xF8,0x4F,0x48,0x49,0xFE,0x48,0x48,0x48,0x08,0x00,
	0x00,0x00,0x7F,0x20,0x10,0x00,0xFF,0x22,0x22,0x22,0x3F,0x22,0x22,0x22,0x20,0x00},/*"˭",3*/
	{0xE0,0x00,0xFF,0x10,0x20,0x22,0xAA,0xAF,0xAA,0xFA,0xAA,0xAF,0xAA,0x22,0x02,0x00,
	0x01,0x00,0xFF,0x00,0x80,0xA0,0xAF,0xAA,0xAA,0xFF,0xAA,0xAA,0xAF,0xA0,0x80,0x00},/*"��",4*/
	{0xFC,0x04,0xFC,0x00,0xFE,0x42,0xBE,0x00,0xF2,0x12,0xF2,0x02,0xFE,0x02,0x00,0x00,
	0x0F,0x04,0x0F,0x00,0xFF,0x10,0x0F,0x00,0x0F,0x04,0x4F,0x80,0x7F,0x00,0x00,0x00},/*"��",5*/
};

#endif