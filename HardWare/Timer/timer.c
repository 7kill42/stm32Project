#include "timer.h"
void TIM2_Init(u16 psc, u16 period)
{

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); // 使能TIM2的时钟
	NVIC_InitTypeDef NVIC_InitStruct;
	
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
    TIM_TimeBaseInitStruct.TIM_Prescaler = psc - 1;  
    TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up; 
    TIM_TimeBaseInitStruct.TIM_Period = period - 1; 
    TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1; 
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);

	TIM_ITConfig(TIM2,TIM_IT_Update, ENABLE);
	
	NVIC_InitStruct.NVIC_IRQChannel = TIM2_IRQn;  
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;  
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;  
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;  
	NVIC_Init(&NVIC_InitStruct);
	
    TIM_Cmd(TIM2, ENABLE);
}
void TIM2_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM2, TIM_IT_Update))
    {
		GPIO_ToggleBits(GPIOE, GPIO_Pin_8); //电平翻转
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    }
}
