#include "beep.h"

void Beep_Init(void)
{   
	GPIO_InitTypeDef  GPIO_InitStructure;
  
	//使能GPIOF时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	
  
	//初始化蜂鸣器对应引脚GPIOF8
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出（下拉） 也可以开漏输出（上拉）
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;//下拉
	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIO
	
	//默认值低电平，蜂鸣器不工作
	GPIO_ResetBits(GPIOB,GPIO_Pin_10);  //蜂鸣器对应引脚拉低
}
