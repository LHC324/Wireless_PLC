#include"adc.h"
#include<STC8.h>


unsigned short ADC_Value;
unsigned char ADC_vol_L;
unsigned char ADC_vol_H;


bit ADC_Start;

/*********************************************************
* ��������unsigned short  ADC_CHANCEL_getValue(unaigned char chanel)
* ���ܣ�  ��ȡ��Ӧͨ����ADֵ 
* ������
* ���ߣ�zhao1peng
* note���˺���ʹ�õ�������ʽ ��ȡADֵ 
* 
*  AD�ɼ�֧��P0.0 -- P0.7  ��P1.0--P1.7 ��16·��AD���ݲɼ�
*  �ɼ���������Ϊ 12λ �����
*
*  �κ������ڵ����⣺�ɼ����ĵ����ݲ��ԣ������ǵ��ԵĿ������Ӳ����·������ ���µİ�.
*   �����ǲο���ѹѡ��Ĳ��� 
**********************************************************/
unsigned short ADC_CHANCEL_getValue(unsigned char chanel)
{
	unsigned short ii = 4000,jj = 500;
	unsigned short ADbuff;
	unsigned char CHANEL = 0X01;

	if(chanel < 0x08)
	{
		  P1M0 = chanel;                    //����ADC�������������
	    P1M1 = (CHANEL << chanel);
	}
	else if(chanel < 0x10)
	{
		  P0M0 = chanel;                    //����ADC�������������
	    P0M1 = (CHANEL << chanel);
	}

	 ADC_CONTR = 0x00;//
   ADCCFG = 0x0f;                              //����ADCʱ��Ϊϵͳʱ��/2/16/16
   ADC_CONTR = 0x80|chanel ;                   //ʹ��ADCģ��
   EADC = 1;                                   //ʹ��ADC�ж�
   EA = 1;

   ADC_CONTR |= 0x40;                          //����ADת��
	 ADC_Start = 1;
	 while(jj--);

	 while (ADC_Start)													   //�ȴ�ת�����
	 {
		 if(!(ii --))
		 {
			 break;
		 }
		 CLRWDT();//������Ź�
	 }

	ADC_Value |= ADC_vol_H;
	ADbuff = ADC_Value << 8;
	ADC_Value = ADbuff|ADC_vol_L;
	
	return  ADC_Value;
}


void ADC_Isr() interrupt 5
{
    ADC_CONTR &= ~0x20;         //���жϱ�־
		ADCCFG = 0X00;								//��������

    ADC_vol_H = ADC_RES;        //��ȡADC�����λ
		ADC_vol_L = ADC_RESL;				//��ȡADC�����λ

    ADC_RES = 0;
    ADC_RESL = 0;
		ADC_Start = 0;							//ת�����
    ADC_CONTR |= 0x40;          //����ADת��
}