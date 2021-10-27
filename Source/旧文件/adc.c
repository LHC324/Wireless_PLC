#include"adc.h"
#include<STC8.h>


unsigned short ADC_Value;
unsigned char ADC_vol_L;
unsigned char ADC_vol_H;


bit ADC_Start;

/*********************************************************
* 函数名：unsigned short  ADC_CHANCEL_getValue(unaigned char chanel)
* 功能：  获取对应通道的AD值 
* 参数：
* 作者：zhao1peng
* note：此函数使用的是阻塞式 读取AD值 
* 
*  AD采集支持P0.0 -- P0.7  和P1.0--P1.7 共16路的AD数据采集
*  采集到的数据为 12位 左对齐
*
*  次函数存在的问题：采集到的的数据不对，可能是调试的开发板的硬件电路有问题 导致的吧.
*   或者是参考电压选择的不对 
**********************************************************/
unsigned short ADC_CHANCEL_getValue(unsigned char chanel)
{
	unsigned short ii = 4000,jj = 500;
	unsigned short ADbuff;
	unsigned char CHANEL = 0X01;

	if(chanel < 0x08)
	{
		  P1M0 = chanel;                    //设置ADC的输入引脚入口
	    P1M1 = (CHANEL << chanel);
	}
	else if(chanel < 0x10)
	{
		  P0M0 = chanel;                    //设置ADC的输入引脚入口
	    P0M1 = (CHANEL << chanel);
	}

	 ADC_CONTR = 0x00;//
   ADCCFG = 0x0f;                              //设置ADC时钟为系统时钟/2/16/16
   ADC_CONTR = 0x80|chanel ;                   //使能ADC模块
   EADC = 1;                                   //使能ADC中断
   EA = 1;

   ADC_CONTR |= 0x40;                          //启动AD转换
	 ADC_Start = 1;
	 while(jj--);

	 while (ADC_Start)													   //等待转换完成
	 {
		 if(!(ii --))
		 {
			 break;
		 }
		 CLRWDT();//清除看门狗
	 }

	ADC_Value |= ADC_vol_H;
	ADbuff = ADC_Value << 8;
	ADC_Value = ADbuff|ADC_vol_L;
	
	return  ADC_Value;
}


void ADC_Isr() interrupt 5
{
    ADC_CONTR &= ~0x20;         //清中断标志
		ADCCFG = 0X00;								//结果左对齐

    ADC_vol_H = ADC_RES;        //读取ADC结果高位
		ADC_vol_L = ADC_RESL;				//读取ADC结果低位

    ADC_RES = 0;
    ADC_RESL = 0;
		ADC_Start = 0;							//转换完成
    ADC_CONTR |= 0x40;          //继续AD转换
}