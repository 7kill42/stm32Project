#include "usart.h"

void usart1_init(void)
{
	USART_InitTypeDef USART_InitStruct;
	GPIO_InitTypeDef GPIO_InitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_10;	//����
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;			//���ģʽ����λ
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;		//����ٶȣ�����
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;		//������ͣ�����
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;		//������������
	GPIO_Init(GPIOA, &GPIO_InitStruct);

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1); //��������
	
	
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;			//�ֳ�
	USART_InitStruct.USART_Parity = USART_Parity_No;					//��żУ��λ
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//Ӳ��������λ
	USART_InitStruct.USART_StopBits = USART_StopBits_1;					//1bit�ĸߵ�ƽ
	USART_InitStruct.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;			//ģʽ
	USART_InitStruct.USART_BaudRate = 9600;							//�����ʣ����ֶ����ã����纯�����Σ�
	USART_Init(USART1,&USART_InitStruct);	
	
	// ʹ�ܽ����ж�
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

    // ���ô����ж����ȼ�
    NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;     
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 3;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStruct);
	
	USART_Cmd(USART1, ENABLE);
}

void USART1_IRQHandler(void)
{
	char ret = 0;
	//�ж��Ƿ��ǽ����ж�
	if(USART_GetITStatus(USART1,USART_IT_RXNE))
	{
		ret = USART_ReceiveData(USART1);//���������жϺ��ȡ���ݼĴ����е�ֵ
		USART_SendData(USART1,ret);//�����յ���ֵ�ٷ��͸�����
	}
	USART_ClearITPendingBit(USART1,USART_IT_RXNE);
}

int fputc(int ch,FILE *f)
{
	USART_ClearFlag(USART1, USART_FLAG_TC); 
	//��������֮ǰ��Ҫȷ�� USART_FLAG_TC ��־λ�Ѿ�������������Ӱ�����ݵ���ȷ���䡣
	USART_SendData(USART1,ch);
    // �ȴ��������
    while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);

	// ���������ɱ�־λ
	
    return ch;
}

///�ض���c�⺯��scanf�����ڣ���д����ʹ��scanf��getchar�Ⱥ���
int fgetc(FILE *f)
{
		/* �ȴ������������� */
		while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);
 
		return (int)USART_ReceiveData(USART1);
}
