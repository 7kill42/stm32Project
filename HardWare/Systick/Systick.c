#include "Systick.h"
int8_t fs_us = 0;
int16_t fs_ms = 0;
void Systick_Init(int32_t Systick)
{
	//Systick->CTRL &= 0xfffffffa ������ȼ�
	SysTick->CTRL &= ~0x05; //ʱ��8��Ƶ���رն�ʱ�� 8��Ƶ����168/8 = 21mhz ͳ��һ��ʱ�����1/21*10^6 s
	                        //��ô����10^-6sҲ����1us��Ҫ��21�Σ�
	fs_us = Systick/8;
	fs_ms = 1000 * fs_us;
}
void delay_nms(uint32_t ms)
{
//	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
	SysTick->LOAD = fs_ms;
	SysTick->VAL = 0;
	SysTick->CTRL |= 0x01;
	while(ms > 0)
	{
		if((SysTick->CTRL & 0x01<<16) !=0)
			ms--;
	}
	SysTick->CTRL &= ~0x01; //�رն�ʱ��
	SysTick->VAL = 0;
	
}

void delay_nus(uint32_t us)
{
	SysTick->LOAD = fs_us;
	SysTick->VAL = 0;
	SysTick->CTRL |= 0x01;
	while(us > 0)
	{
		if((SysTick->CTRL & 0x01<<16) !=0)
			us--;
	}
	SysTick->CTRL &= ~0x01; //�رն�ʱ��
	SysTick->VAL = 0;
}
