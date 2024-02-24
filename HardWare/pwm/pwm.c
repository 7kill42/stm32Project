#include "pwm.h"

void PWM_Init(u16 psc, u16 period)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_OCInitTypeDef TIM_OCInitStruct;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOE, &GPIO_InitStruct);

	GPIO_PinAFConfig(GPIOE,GPIO_PinSource9, GPIO_AF_TIM1);

	TIM_TimeBaseInitStruct.TIM_Period = period - 1;  //计数周期，每1ms中断一次 
	TIM_TimeBaseInitStruct.TIM_Prescaler = psc - 1;  //1MHz的时钟频率
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStruct);

	// 配置定时器输出比较参数
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStruct.TIM_Pulse = 0;
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_Low; //输出高极性
	TIM_OC1Init(TIM1, &TIM_OCInitStruct);
	
	TIM_OC1PreloadConfig(TIM1,TIM_OCPreload_Enable);  
//使能通道1的预装载功能。这意味着改变PWM占空比的设置会在计数器溢出时生效，
//从而确保占空比的改变平滑过渡，而不会出现突变。
	TIM_ARRPreloadConfig(TIM1,ENABLE);
	TIM_CtrlPWMOutputs(TIM1,ENABLE);
	TIM_Cmd(TIM1, ENABLE);
}

