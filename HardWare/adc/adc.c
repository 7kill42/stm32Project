#include "adc.h"

//ADC_IN0 -->����-->PA0; ����ΪADC1��2��3��ͨ��0
//ADC_IN10-->�ɱ��ѹ����-->PC0������ΪADC1��2��3��ͨ��10
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
	
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1, ENABLE); //ADC��λ
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1, DISABLE);//��λ���
	
	ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent; //����ģʽ
	ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div4;  //���������׶�֮���ӳ�5��ʱ������
	ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled; //����DMA��ʧ��
	ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;//4��Ƶ ��ADC CLK = PLCK2/4 = 84/4 = 21Mhz,ADC��߲�����36Mhz
	ADC_CommonInit(&ADC_CommonInitStructure);  
	
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b; //12λģʽ���ֱ��� 
	ADC_InitStructure.ADC_ScanConvMode = DISABLE; //��ɨ��ģʽ�����ڶ��ͨ��ת��ʹ��
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE; //��ʹ������ת��
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;//��ʹ�ô�����⣬ʹ���������
	ADC_InitStructure.ADC_NbrOfConversion = 1; //ÿ������ ADC ת��ʱ��ֻ��ת��һ��ͨ��������
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right; //�Ҷ���
	ADC_Init(ADC1,&ADC_InitStructure);
	
	ADC_Cmd(ADC1,ENABLE);
}

//��ȡADCֵ
//ch: ADC_channels ADCͨ�� ����ʹ�õ���1
//ͨ��ֵ 0��15
u16 getAdc(u8 ch)
{
	ADC_RegularChannelConfig( ADC1,ch, 1, ADC_SampleTime_480Cycles); //��߲���ʱ�������߾���
	ADC_SoftwareStartConv(ADC1);
	while(!ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC));  //�ȴ�ת������ 
	return ADC_GetConversionValue(ADC1);  //�������һ��ת���Ľ��
}	

//��ȡͨ��ch��ת��ֵ��ȡtimes�Σ�Ȼ��ȡƽ��
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
