#include "beep.h"

void Beep_Init(void)
{   
	GPIO_InitTypeDef  GPIO_InitStructure;
  
	//ʹ��GPIOFʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	
  
	//��ʼ����������Ӧ����GPIOF8
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//��������������� Ҳ���Կ�©�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;//����
	GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIO
	
	//Ĭ��ֵ�͵�ƽ��������������
	GPIO_ResetBits(GPIOB,GPIO_Pin_10);  //��������Ӧ��������
}
