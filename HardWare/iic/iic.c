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

//������ʼ�ź�
void IIC_start(void)
{
	SDA_OUT();
	//�����ɸߵ��͵�ƽ,������ʼ�ź�
	SCL_H;
	SDA_H;
	delay_us(2); //�����ź���һ�ֵ�ƽ����ʱ���źţ�����ͻȻ�ĵ�ƽ�仯
	SDA_L;
	delay_us(2); //����	
}

//���������ź�
void IIC_stop(void)
{
	SDA_OUT();
	//�����ɵ͵��ߵ�ƽ,���������ź�
	SCL_H;
	SDA_L;
	delay_us(2); 
	SDA_H;
	delay_us(2); //����	
}

//��ȡӦ���ź�
u8 IIC_Receive_Ack(void)
{
	u8 time = 0;
	u8 ret = 1; //1Ϊ������Ӧ��
	
	SDA_IN();
	
	SDA_H;
	delay_us(2);
	
	SCL_H;  //��SCL���ߣ��ͷ�SDA����Ȩ
	delay_us(2);
	while(SDA_READ) //��ȡSDA״̬һ��ʱ���ж��Ƿ����ͻ�Ӧ
	{
		time++;
		if(time>200)
		{
			IIC_stop();
			ret = 0; //��ʾû��Ӧ��
			break;
		}
	}
	SCL_L;    //���ͷ���SDA�޸�
	return ret;
}

void IIC_SendAck(void)
{
	SDA_OUT();
	SCL_L;  //�Ƚ�SCL�����Ͳ��ܽ�SDA������
	delay_us(2);
	
	SDA_L;
	delay_us(2);

	SCL_H;  //�Ƚ�SCL�Ⱥ�SDA�߶����ͣ�ά��һ��ʱ���SCL�����ߣ����ôӻ���ȡ���������͵�SDA��
	delay_us(2);
	SCL_L;  //?
}

void IIC_SendNoAck(void)
{
	SDA_OUT();
	SCL_L;
	delay_us(2);
	
	SDA_H;	//������SDAӦ��
	delay_us(2);
	
	SCL_H;  //��SCL���ߣ��ͷ�SDA����Ȩ
	delay_us(2);
}

void IIC_Send_byte(u8 data)
{
	u8 i = 0;
	SDA_OUT();
	SCL_L;  //SCL���Ϳ����޸�SDA
	delay_us(2);
	
	for(i = 0; i< 8; i++)
	{
		if((data & 0x80)>>7) //��λ�ȷ�  &����0 |����1��
		{
			//�������ݵĸ�λ��1������SDA
			SDA_H;
		}
		else
		{
			//�������ݵĸ�λ��0������SDA
			SDA_L;
		}
		delay_us(2);
		data <<= 1;//����1λ�������´��жϴθ�λ
		
		SCL_H;//SCL����
		delay_us(2);
	
		SCL_L;//SCL����
		delay_us(2);
	}
	
}

u8 IIC_Receive_byte(void)
{
	uint8_t i = 0;
	uint8_t data = 0;
	SDA_IN();
	//8������λ����ȡ8��
	for(i = 0; i < 8; i++)
	{
		SCL_L;//SCL���ͣ��ôӻ��ı�SDA״̬
		delay_us(2);
		
		SCL_H;//SCL����
		delay_us(2);
		
		data <<= 1;//��λ����1λ��������մθ�λ ������8�ΰѵ�һ���Ƶ���һλ
		if(SDA_READ)
		{
			//SDA�ߵ�ƽ
			data |= 1;
		}
	}
	return data;
}
