#include "dht11.h"
GPIO_InitTypeDef GPIO_InitStructure;
void Dht11_Init(void)
{ 
//	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_SetBits(GPIOA,GPIO_Pin_3);
}

void Set_in_mode(void)
{
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void Set_out_mode(void)
{
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}
//�����Ӧ�źţ�80�͵�ƽ80�ߵ�ƽ���ɹ�����1��ʧ�ܷ���0
u8 dhtll_check_Ack(void)
{
	u16 time = 0;
	while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3) && time < 100)//Խ��80us֮ǰ�ĸߵ�ƽ�ź�
	{
		time++;
		delay_us(50);
	}
	if(time >=100)
	{
		return 0;
	}	
	else
		time = 0;
	//˵������˵͵�ƽ
	while(!GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3) && time < 100)//Խ��80us֮ǰ�ĵ͵�ƽ�ź�
	{
		time++;
		delay_us(1);
	}
	if(time >=100)
	{
		return 0;
	}
	//˵������˸ߵ�ƽ
	return 1; //��Ӧ�ɹ�
}

// ��ȡһ�ֽ����ݣ�50us�͵�ƽ ��0Ϊ���� 26-28us �ߵ�ƽ 1Ϊ����70us�ߵ�ƽ
u8 read_byte_data(void)
{
	u8 i;
	u8 data = 0;
	for(i = 0 ; i < 8 ;i++)
	{
		data <<= 1;
//		printf("\r\n��������\r\n");
		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3));
		while(!GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3));
		delay_us(50);
		if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3))
			data |=1;
	}
	return data;
}	

u8 Read_dht11_data(u8 *temp,u8 *humidity)
{
	u8 receive_data[5] = "";
	u8 return_mode;
	//��ʼ�ź�
	Set_out_mode();
	GPIO_ResetBits(GPIOA, GPIO_Pin_3);
	delay_ms(20);
	GPIO_SetBits(GPIOA, GPIO_Pin_3);
	delay_us(30);
	
	//��Ӧ�ź�
	Set_in_mode();
	if(dhtll_check_Ack())
	{
		for(u8 i = 0;i<5;i++)
			receive_data[i] = read_byte_data();
		Set_out_mode(); //����Ϊ���������Ϊ��һ�μ��
		if(receive_data[0] + receive_data[1] + receive_data[2] + receive_data[3] == receive_data[4])
		{
			//��ʪ�����ݷ��ز���ӡ
			*temp = receive_data[2];
			*humidity = receive_data[0];
			return_mode = 1;  //����ɹ�
		}
		else return_mode = 2; //У��ʧ��
	}
	else return_mode = 0;	//��Ӧʧ��
	return return_mode;
}
