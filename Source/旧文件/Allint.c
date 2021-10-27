#include "Allint.h"
#include<STC8.h>
/*********************************************************
* 函数名：void Int0_init(unsigned char edge)
* 功能：  初始化外部中断0
* 参数：  char edge ：触发方式 ：FALL_AND_RISE_EDGE 0  //下降或上升沿中断
								 FALL_EDGE 1     //下降沿中断
* 作者：zhao1peng
* note： 外部中断 0 1 支持下降沿中断或者上升沿下降沿触发中断 和根据实际需求进行选择
*
**********************************************************/

void Int0_init(unsigned char edge)
{
	IT0 = edge;                                    //使能INT0上升沿和下降沿中断
    EX0 = 1;                                    //使能INT0中断
    EA = 1;	
}

void Int1_init(unsigned char edge)
{
	IT1 = edge;                                    //使能INT1上升沿和下降沿中断
    EX1 = 1;                                    //使能INT1中断
    EA = 1;
}

 /*********************************************************
* 函数名：void int_234_choose(unsigned char INTC)
* 功能：  外部中断2 3 4 的初始化
* 参数：  unsigned char INTC
					 EX2             0x10  //使能中断2
					 EX3             0x20  //使能中断3
					 EX4             0x40  //使能中断4
* 作者：zhao1peng
* note：
*	  外部中断 2 3 4 只支持下降沿中断
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
* 函数名：
* 功能：  以下为各个外部中断的中断服务函数
* 参数：
* 作者：zhao1peng
* note：
*		用户可根据实际需求来编写中断服务函数
**********************************************************/
void INT0_Isr() interrupt 0	  //外部中断1的中断服务函数
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
