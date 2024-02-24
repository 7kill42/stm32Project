#ifndef __IIC_H__
#define __IIC_H__
#include "stm32f4xx.h"
#include "delay.h"

#define SCL_PIN				GPIO_PIN_6
#define SDA_PIN				GPIO_PIN_7

#define SCL_PORT			GPIOB
#define SDA_PORT			GPIOB

#define SCL_L   GPIO_ResetBits(GPIOB,GPIO_Pin_6)
#define SCL_H   GPIO_SetBits(GPIOB,GPIO_Pin_6)

#define SDA_L   GPIO_ResetBits(GPIOB,GPIO_Pin_7)
#define SDA_H   GPIO_SetBits(GPIOB,GPIO_Pin_7)
#define SDA_READ    GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7)

void IIC_init(void);
void SDA_IN(void);
void SDA_OUT(void);
void IIC_start(void);
void IIC_stop(void);
u8 IIC_Receive_Ack(void);
void IIC_SendAck(void);
void IIC_SendNoAck(void);
void IIC_Send_byte(u8 data);
u8 IIC_Receive_byte(void);

#endif
