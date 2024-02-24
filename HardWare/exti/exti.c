#include "exti.h"
u8 key;
void EXIT_Init(void)
{
	EXTI_InitTypeDef EXTI_InitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource4);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource5);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource6);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource13);
	
	EXTI_InitStruct.EXTI_Line = EXTI_Line4| EXTI_Line5|EXTI_Line6|EXTI_Line13;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStruct);
	
	NVIC_InitStruct.NVIC_IRQChannel=EXTI0_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=3;
	NVIC_Init(&NVIC_InitStruct);
	
	NVIC_InitStruct.NVIC_IRQChannel = EXTI4_IRQn;
    NVIC_Init(&NVIC_InitStruct);

    NVIC_InitStruct.NVIC_IRQChannel = EXTI9_5_IRQn;
    NVIC_Init(&NVIC_InitStruct);

    NVIC_InitStruct.NVIC_IRQChannel = EXTI15_10_IRQn;
    NVIC_Init(&NVIC_InitStruct);
}

void EXTI4_IRQHandler(void)
{
    if(EXTI_GetITStatus(EXTI_Line4) != RESET)
    {
	   LED1_Open;
       EXTI_ClearITPendingBit(EXTI_Line4);
    }
}

void EXTI9_5_IRQHandler(void)
{
    if(EXTI_GetITStatus(EXTI_Line5) != RESET)
    {
		LED2_Open;
        EXTI_ClearITPendingBit(EXTI_Line5);
    }
	if(EXTI_GetITStatus(EXTI_Line6) != RESET)
    {
		LED3_Open;
        EXTI_ClearITPendingBit(EXTI_Line6);
    }
}

void EXTI15_10_IRQHandler(void)
{
    if(EXTI_GetITStatus(EXTI_Line13) != RESET)
    {
		LED1_Close;
        LED2_Close;
		LED3_Close;
        EXTI_ClearITPendingBit(EXTI_Line13);
    }
}
