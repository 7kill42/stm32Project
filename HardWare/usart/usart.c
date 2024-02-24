#include "usart.h"

void usart1_init(void)
{
	USART_InitTypeDef USART_InitStruct;
	GPIO_InitTypeDef GPIO_InitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_10;	//引脚
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;			//输出模式：复位
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;		//输出速度：中速
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;		//输出类型：推挽
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;		//上下拉：上拉
	GPIO_Init(GPIOA, &GPIO_InitStruct);

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1); //复用声明
	
	
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;			//字长
	USART_InitStruct.USART_Parity = USART_Parity_No;					//奇偶校验位
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//硬件流控制位
	USART_InitStruct.USART_StopBits = USART_StopBits_1;					//1bit的高电平
	USART_InitStruct.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;			//模式
	USART_InitStruct.USART_BaudRate = 9600;							//波特率（可手动设置，比如函数传参）
	USART_Init(USART1,&USART_InitStruct);	
	
	// 使能接收中断
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

    // 配置串口中断优先级
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
	//判断是否是接收中断
	if(USART_GetITStatus(USART1,USART_IT_RXNE))
	{
		ret = USART_ReceiveData(USART1);//发生接收中断后读取数据寄存器中的值
		USART_SendData(USART1,ret);//将接收到的值再发送给电脑
	}
	USART_ClearITPendingBit(USART1,USART_IT_RXNE);
}

int fputc(int ch,FILE *f)
{
	USART_ClearFlag(USART1, USART_FLAG_TC); 
	//发送数据之前需要确保 USART_FLAG_TC 标志位已经被清除，否则会影响数据的正确传输。
	USART_SendData(USART1,ch);
    // 等待发送完成
    while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);

	// 清除发送完成标志位
	
    return ch;
}

///重定向c库函数scanf到串口，重写向后可使用scanf、getchar等函数
int fgetc(FILE *f)
{
		/* 等待串口输入数据 */
		while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);
 
		return (int)USART_ReceiveData(USART1);
}
