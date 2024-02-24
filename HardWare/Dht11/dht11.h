#ifndef __DHT11_H__
#define __DHT11_H__
#include "stm32f4xx.h"
#include "delay.h"

void Dht11_Init(void);
void Set_in_mode(void);
void Set_out_mode(void);
u8 dhtll_check_Ack(void);
u8 read_byte_data(void);
u8 Read_dht11_data(u8 *temp,u8 *humidity);

#endif
