#include "Allint.h"
#include<STC8.h>
/*********************************************************
* ��������void Int0_init(unsigned char edge)
* ���ܣ�  ��ʼ���ⲿ�ж�0
* ������  char edge ��������ʽ ��FALL_AND_RISE_EDGE 0  //�½����������ж�
								 FALL_EDGE 1     //�½����ж�
* ���ߣ�zhao1peng
* note�� �ⲿ�ж� 0 1 ֧���½����жϻ����������½��ش����ж� �͸���ʵ���������ѡ��
*
**********************************************************/

void Int0_init(unsigned char edge)
{
	IT0 = edge;                                    //ʹ��INT0�����غ��½����ж�
    EX0 = 1;                                    //ʹ��INT0�ж�
    EA = 1;	
}

void Int1_init(unsigned char edge)
{
	IT1 = edge;                                    //ʹ��INT1�����غ��½����ж�
    EX1 = 1;                                    //ʹ��INT1�ж�
    EA = 1;
}

 /*********************************************************
* ��������void int_234_choose(unsigned char INTC)
* ���ܣ�  �ⲿ�ж�2 3 4 �ĳ�ʼ��
* ������  unsigned char INTC
					 EX2             0x10  //ʹ���ж�2
					 EX3             0x20  //ʹ���ж�3
					 EX4             0x40  //ʹ���ж�4
* ���ߣ�zhao1peng
* note��
*	  �ⲿ�ж� 2 3 4 ֻ֧���½����ж�
*
**********************************************************/
void int_234_choose(unsigned char INTC)
{
	switch(INTC)
	{
		case EX2: INTCLKO = INTC;
		break;
		case EX3: INTCLKO = INTC;
		break;
		case EX4: INTCLKO = INTC;
		break;
		default:
		break;
	}
	 EA = 1;
}

 //***************************************************************************
 /*********************************************************
* ��������
* ���ܣ�  ����Ϊ�����ⲿ�жϵ��жϷ�����
* ������
* ���ߣ�zhao1peng
* note��
*		�û��ɸ���ʵ����������д�жϷ�����
**********************************************************/
void INT0_Isr() interrupt 0	  //�ⲿ�ж�1���жϷ�����
{
    //add your code

//	 LED1 = ~LED1;
//     LED2 = ~LED2;


}
void INT1_Isr() interrupt 2
{
   //add your code
   
    
}
void INT2_Isr() interrupt 10
{
    //add your code


}

void INT3_Isr() interrupt 11
{
    //add your code


}

void INT4_Isr() interrupt 16
{
     //add your code



}
