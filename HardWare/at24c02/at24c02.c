#include "at24c02.h"
//监测芯片是否正常，在255地址中如果读到0x55的值，表示正常
u8 AT24C02_Init(void)
{
	u8 temp;
	u8 ret = 0;
	IIC_init();
	temp = AT24C02_Read_byte(255);
//	printf("%x",temp);
	if(temp == 0x55)
		ret =  1; //表示正常
	else
	{
		AT24C02_Write_byte(255,0x55);
		temp = AT24C02_Read_byte(255);
		if(temp == 0x55)
			ret =  1;
	}
	return ret;
}	

void AT24C02_Write_byte(u8 addr, u8 data)
{
	IIC_start();
	
	IIC_Send_byte(0xA0);  //设备地址0xA0
	IIC_Receive_Ack();
	
	IIC_Send_byte(addr);  //字地址
	IIC_Receive_Ack();
	
	IIC_Send_byte(data);
	IIC_Receive_Ack();
	
	IIC_stop();
	delay_ms(10);
}

u8 AT24C02_Read_byte(u8 addr)
{
	u8 data;
	
	IIC_start();
	
	IIC_Send_byte(0xA0);  //设备地址0xA0
	IIC_Receive_Ack();
	
	IIC_Send_byte(addr);  //字地址
	IIC_Receive_Ack();
	
	IIC_start();
	
	IIC_Send_byte(0xA1);  //设备地址0xA1
	IIC_Receive_Ack();
	
	data = IIC_Receive_byte();
	IIC_SendNoAck();	
	
	IIC_stop();
	return data;
}

void AT24C02_Write_bytes(u8 addr,u8 *data,u8 size)
{
	while(size--)
	{
		AT24C02_Write_byte(addr,*data);
		addr++;
		data++;
	}
	
}

//buf:用来存储多字节数据空间
void AT24C02_Read_bytes(u8 addr,u8 *buf,u8 size)
{
	while(size--)
	{
		*buf = AT24C02_Read_byte(addr);
		addr++;
		buf++;
	}
}
