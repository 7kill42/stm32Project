#include"iic.h"
GPIO_InitTypeDef GPIO_InitStruct;
//SCL -- PB6  SDA -- PB7
void IIC_init(void)
{
//	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	GPIO_SetBits(GPIOB,GPIO_Pin_6|GPIO_Pin_7);
}

void SDA_IN(void)
{
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
}

void SDA_OUT(void)
{
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
}

//产生起始信号
void IIC_start(void)
{
	SDA_OUT();
	//出现由高到低电平,表明起始信号
	SCL_H;
	SDA_H;
	delay_us(2); //启动信号是一种电平跳变时序信号，不是突然的电平变化
	SDA_L;
	delay_us(2); //保持	
}

//产生结束信号
void IIC_stop(void)
{
	SDA_OUT();
	//出现由低到高电平,表明结束信号
	SCL_H;
	SDA_L;
	delay_us(2); 
	SDA_H;
	delay_us(2); //保持	
}

//获取应答信号
u8 IIC_Receive_Ack(void)
{
	u8 time = 0;
	u8 ret = 1; //1为产生了应答
	
	SDA_IN();
	
	SDA_H;
	delay_us(2);
	
	SCL_H;  //将SCL拉高，释放SDA控制权
	delay_us(2);
	while(SDA_READ) //读取SDA状态一段时间判断是否拉低回应
	{
		time++;
		if(time>200)
		{
			IIC_stop();
			ret = 0; //表示没有应答
			break;
		}
	}
	SCL_L;    //拉低方便SDA修改
	return ret;
}

void IIC_SendAck(void)
{
	SDA_OUT();
	SCL_L;  //先将SCL线拉低才能将SDA线拉高
	delay_us(2);
	
	SDA_L;
	delay_us(2);

	SCL_H;  //先将SCL先和SDA线都拉低，维持一段时间后将SCL线拉高，好让从机读取被主机拉低的SDA。
	delay_us(2);
	SCL_L;  //?
}

void IIC_SendNoAck(void)
{
	SDA_OUT();
	SCL_L;
	delay_us(2);
	
	SDA_H;	//不拉低SDA应答
	delay_us(2);
	
	SCL_H;  //将SCL拉高，释放SDA控制权
	delay_us(2);
}

void IIC_Send_byte(u8 data)
{
	u8 i = 0;
	SDA_OUT();
	SCL_L;  //SCL拉低可以修改SDA
	delay_us(2);
	
	for(i = 0; i< 8; i++)
	{
		if((data & 0x80)>>7) //高位先发  &：清0 |：置1；
		{
			//发送数据的高位是1，拉高SDA
			SDA_H;
		}
		else
		{
			//发送数据的高位是0，拉低SDA
			SDA_L;
		}
		delay_us(2);
		data <<= 1;//左移1位，方便下次判断次高位
		
		SCL_H;//SCL拉高
		delay_us(2);
	
		SCL_L;//SCL拉低
		delay_us(2);
	}
	
}

u8 IIC_Receive_byte(void)
{
	uint8_t i = 0;
	uint8_t data = 0;
	SDA_IN();
	//8个比特位，读取8次
	for(i = 0; i < 8; i++)
	{
		SCL_L;//SCL拉低，让从机改变SDA状态
		delay_us(2);
		
		SCL_H;//SCL拉高
		delay_us(2);
		
		data <<= 1;//高位左移1位，方便接收次高位 正好移8次把第一次移的那一位
		if(SDA_READ)
		{
			//SDA高电平
			data |= 1;
		}
	}
	return data;
}
