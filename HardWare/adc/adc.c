#include "adc.h"

//ADC_IN0 -->光照-->PA0; 可作为ADC1、2、3的通道0
//ADC_IN10-->可变电压输入-->PC0；可作为ADC1、2、3的通道10
void Adc_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	ADC_InitTypeDef ADC_InitStructure;
	ADC_CommonInitTypeDef ADC_CommonInitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AN;
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1, ENABLE); //ADC复位
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1, DISABLE);//复位完毕
	
	ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent; //独立模式
	ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div4;  //两个采样阶段之间延迟5个时钟周期
	ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled; //不用DMA，失能
	ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;//4分频 ，ADC CLK = PLCK2/4 = 84/4 = 21Mhz,ADC最高不超过36Mhz
	ADC_CommonInit(&ADC_CommonInitStructure);  
	
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b; //12位模式，分辨率 
	ADC_InitStructure.ADC_ScanConvMode = DISABLE; //非扫描模式，对于多个通道转换使用
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE; //不使用连续转换
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;//不使用触发检测，使用软件触发
	ADC_InitStructure.ADC_NbrOfConversion = 1; //每次启动 ADC 转换时，只会转换一个通道的数据
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right; //右对齐
	ADC_Init(ADC1,&ADC_InitStructure);
	
	ADC_Cmd(ADC1,ENABLE);
}

//获取ADC值
//ch: ADC_channels ADC通道 这里使用的是1
//通道值 0到15
u16 getAdc(u8 ch)
{
	ADC_RegularChannelConfig( ADC1,ch, 1, ADC_SampleTime_480Cycles); //提高采样时间可以提高精度
	ADC_SoftwareStartConv(ADC1);
	while(!ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC));  //等待转换结束 
	return ADC_GetConversionValue(ADC1);  //返回最近一次转换的结果
}	

//获取通道ch的转换值，取times次，然后取平均
u16 getAdcAverage(u8 ch,u8 times)
{
	u32 temp_val=0;
	u8 t;
	for(t=0;t<times;t++)
	{
		temp_val += getAdc(ch);
		delay_ms(5);
	}
	return temp_val/times;
}
