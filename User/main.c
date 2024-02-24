#include "main.h"
int main(void)
{
//	LED_Init();
	Key_Init();
	Beep_Init();
//	Systick_Init(168);
	delay_init(168);
	
	usart1_init();
//	Adc_Init();
//	oled_init();
//	OLed_Fill(0xff);    //高亮
//	Dht11_Init();
	PWM_Init(84,1000);
//	TIM2_Init(8400,10000);
//	EXIT_Init();

//	u8 i;
//	u8 key;
	u16 bright = 0;
	u8 direction = 1;
//	u8 temp,humidity = 0;
//	u8 ret = 0;
//    u8 data[100] = "";
//	printf("%d",getAdcAverage(0,10));
//	for(u8 i = 0;i < 6;i++)
//		OLed_Write_chinese(i*16,0,(char*)s[i]);
//	OLed_Write_chinese(8,0,(char*)s[0]);
	while(1)
	{
//		key = Key_Scan(1);
//		if(key)
//		{
//			switch(key)
//			{
//				case 1: Beep_On;LED1_Open;break;
//				case 2: Beep_Off;LED1_Close;break;
//				case 3: LED2_Open;break;
//				case 4: LED2_Close;break;
//				default: break;
//			}
//		}else delay_ms(10);
//		LED1_Open;
//		delay_nus(500000);
//		LED1_Close;
//		delay_nus(500000);	
		if (direction == 1)
			bright++;
		else
			bright--;
		if(bright == 800)
			direction = 0;
		if(bright == 0)
			direction = 1;
		TIM_SetCompare1(TIM1,bright);
		delay_ms(10);
//		ret = Read_dht11_data(&temp,&humidity);
//		if(ret == 1)
//		{
//			printf("\r\n正在工作了喵\r\n");
//			printf("\r\n现在的温度是：%d，湿度是:%d喵\r\n",temp,humidity);
//		}
//		else if(ret == 0)
//			printf("\r\n响应失败了喵\r\n");
//		else if(ret == 2)
//			printf("\r\n校验失败了喵\r\n");
//		delay_ms(1000);
//		if(AT24C02_Init())
//		{
//			AT24C02_Write_bytes(0,(u8 *)"\r\n写入成功了喵\r\n",strlen("\r\n写入成功了喵\r\n"));
//			delay_ms(500);
////			printf("\r\n进入了喵\r\n");
//			AT24C02_Read_bytes(0,data,strlen("\r\n写入成功了喵\r\n"));
//			delay_ms(500);
//			printf("%s",data);
//		}
//		else
//		{
//			delay_ms(1000);
//			printf("\r\n芯片检测失败了喵\r\n");
//		}
	}
	
}
