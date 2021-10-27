//#include"config.h"
///*********************************************************************
//* 函数名：void PWM0_OUT(unsigned short cycle,unsigned short LOW_Val,unsigned short HIGH_Val,unsigned char Pin)
//* 功能：  指定引脚输出可控的PWM方波
//* 参数：
//* 作者：zhao1peng
//* note： 改PWM的输出时钟是基于PCA时钟的  可根据PCA时钟的三个模块进行
//* 分别设置，可同时四路输出PWM波 
//* PWM 引脚的输出默认是每一组PWM的第一个引脚输出。
//*
//********************************************************************/
//
//
///*
//	init() example:
//
//	PWM_STATUE PWM1QWQW;
//
//	PWM1QWQW.PWM_MOD = PWM_MOD7;
//	PWM1QWQW.OUT_PIN_GROUP= PIN_GROUP3;
//	PWM1QWQW.cycle = 0X1000;
//	PWM1QWQW.LOW_Val = 0X0100;
//	PWM1QWQW.HIGH_Val = 0X0200;
//	PWM_MOD_OUT(&PWM1QWQW);
//	
//	*/
//
//
//void PWM_MOD_OUT(PWM_STATUE *PWM_OUT)
//{	
//	if((PWM_OUT->PWM_MOD) == PWM_MOD0)
//	{
//		P_SW2 = 0x80;
//	
//	    PWMCKS = 0x00;                              // PWM时钟为系统时钟
//	    PWMC = PWM_OUT->cycle;                               //设置PWM周期为cycle H个PWM时钟
//	    PWM0T1= PWM_OUT->LOW_Val;                            //在计数值为LOW_Val H地方输出低电平
//	    PWM0T2= PWM_OUT->HIGH_Val;                           //在计数值为HIGH_Val H地方输出高电平
//	    
//		
//		switch(PWM_OUT->OUT_PIN_GROUP)  //使能PWM0输出
//		{
//		   case 0: PWM0_P20;
//		   		break;
//		   case 1: PWM0_P10;
//		   		break;
//		   case 2: PWM0_P60;
//		   		break;
//		   default:	PWM0_P20;
//		   		break;
//		}
//		                              
//	    P_SW2 = 0x00;
//		PWMCR = 0x80;  	  //启动PWM模块
//	}
//
//	if((PWM_OUT->PWM_MOD) == PWM_MOD1)
//	{
//		P_SW2 = 0x80;
//	
//	    PWMCKS = 0x00;                              // PWM时钟为系统时钟
//	    PWMC = PWM_OUT->cycle;                               //设置PWM周期为1000H个PWM时钟
//	    PWM1T1= PWM_OUT->LOW_Val;                            //在计数值为100H地方输出低电平
//	    PWM1T2= PWM_OUT->HIGH_Val;                           //在计数值为500H地方输出高电平
//	    switch(PWM_OUT->OUT_PIN_GROUP) //使能PWM0输出
//		{
//		   case 0: PWM1_P21;
//		   		break;
//		   case 1: PWM1_P11;
//		   		break;
//		   case 2: PWM1_P61;
//		   		break;
//		   default:	PWM1_P21;
//		   		break;
//		}                               
//	    P_SW2 = 0x00;
//		
//	    PWMCR = 0x80;                               //启动PWM模块
//	}
//	if((PWM_OUT->PWM_MOD) == PWM_MOD2)  //使能PWM0输出
//	{
//		P_SW2 = 0x80;
//	
//	    PWMCKS = 0x00;                              // PWM时钟为系统时钟
//	    PWMC = PWM_OUT->cycle;                               //设置PWM周期为1000H个PWM时钟
//	    PWM2T1= PWM_OUT->LOW_Val;                            //在计数值为100H地方输出低电平
//	    PWM2T2= PWM_OUT->HIGH_Val;                           //在计数值为500H地方输出高电平
//	   	switch(PWM_OUT->OUT_PIN_GROUP)
//		{
//		   case 0: PWM2_P22;
//		   		break;
//		   case 1: PWM2_P12;
//		   		break;
//		   case 2: PWM2_P62;
//		   		break;
//		   default:	PWM2_P22;
//		   		break;
//		}                             //使能PWM0输出
//	    P_SW2 = 0x00;
//		
//	
//	    PWMCR = 0x80;                               //启动PWM模块
//	}
//	if((PWM_OUT->PWM_MOD) == PWM_MOD3)
//	{
//		P_SW2 = 0x80;
//	
//	    PWMCKS = 0x00;                              // PWM时钟为系统时钟
//	    PWMC = PWM_OUT->cycle;                               //设置PWM周期为1000H个PWM时钟
//	    PWM3T1= PWM_OUT->LOW_Val;                            //在计数值为100H地方输出低电平
//	    PWM3T2= PWM_OUT->HIGH_Val;                           //在计数值为500H地方输出高电平
//	    switch(PWM_OUT->OUT_PIN_GROUP) //使能PWM0输出
//		{
//		   case 0: PWM3_P23;
//		   		break;
//		   case 1: PWM3_P13;
//		   		break;
//		   case 2: PWM3_P63;
//		   		break;
//		   default:	PWM3_P23;
//		   		break;
//		}                               
//	    P_SW2 = 0x00;
//		
//		
//	    PWMCR = 0x80;                               //启动PWM模块
//	}
//	if((PWM_OUT->PWM_MOD) == PWM_MOD4)
//	{
//		P_SW2 = 0x80;
//	
//	    PWMCKS = 0x00;                              // PWM时钟为系统时钟
//	    PWMC = PWM_OUT->cycle;                               //设置PWM周期为1000H个PWM时钟
//	    PWM4T1= PWM_OUT->LOW_Val;                            //在计数值为100H地方输出低电平
//	    PWM4T2= PWM_OUT->HIGH_Val;                           //在计数值为500H地方输出高电平
//	    switch(PWM_OUT->OUT_PIN_GROUP)	  //使能PWM0输出
//		{
//		   case 0: PWM4_P24;
//		   		break;
//		   case 1: PWM4_P14;
//		   		break;
//		   case 2: PWM4_P64;
//		   		break;
//		   default:	PWM4_P24;
//		   		break;
//		}                                
//	    P_SW2 = 0x00;
//		
//	
//	    PWMCR = 0x80;                               //启动PWM模块
//	}
//	if((PWM_OUT->PWM_MOD) == PWM_MOD5)	  //使能PWM0输出
//	{
//		P_SW2 = 0x80;
//	
//	    PWMCKS = 0x00;                              // PWM时钟为系统时钟
//	    PWMC = PWM_OUT->cycle;                               //设置PWM周期为1000H个PWM时钟
//	    PWM5T1= PWM_OUT->LOW_Val;                            //在计数值为100H地方输出低电平
//	    PWM5T2= PWM_OUT->HIGH_Val;                           //在计数值为500H地方输出高电平
//	    switch(PWM_OUT->OUT_PIN_GROUP)
//		{
//		   case 0: PWM5_P25;
//		   		break;
//		   case 1: PWM5_P15;
//		   		break;
//		   case 2: PWM5_P65;
//		   		break;
//		   default:	PWM5_P25;
//		   		break;
//		}                              
//	    P_SW2 = 0x00;		
//	    PWMCR = 0x80;                               //启动PWM模块
//	}
//	if((PWM_OUT->PWM_MOD) == PWM_MOD6)
//	{
//		P_SW2 = 0x80;
//	
//	    PWMCKS = 0x00;                              // PWM时钟为系统时钟
//	    PWMC = PWM_OUT->cycle;                               //设置PWM周期为1000H个PWM时钟
//	    PWM6T1= PWM_OUT->LOW_Val;                            //在计数值为100H地方输出低电平
//	    PWM6T2= PWM_OUT->HIGH_Val;                           //在计数值为500H地方输出高电平
//	    switch(PWM_OUT->OUT_PIN_GROUP)		  //使能PWM0输出
//		{
//		   case 0: PWM6_P26;
//		   		break;
//		   case 1: PWM6_P16;
//		   		break;
//		   case 2: PWM6_P66;
//		   		break;
//		   default:	PWM6_P26;
//		   		break;
//		}                                
//	    P_SW2 = 0x00;
//		
//	
//	    PWMCR = 0x80;                               //启动PWM模块
//	}
//	if((PWM_OUT->PWM_MOD) == PWM_MOD7)
//	{
//		P_SW2 = 0x80;
//	
//	    PWMCKS = 0x00;                              // PWM时钟为系统时钟
//	    PWMC = PWM_OUT->cycle;                               //设置PWM周期为1000H个PWM时钟
//	    PWM7T1= PWM_OUT->LOW_Val;                            //在计数值为100H地方输出低电平
//	    PWM7T2= PWM_OUT->HIGH_Val;                           //在计数值为500H地方输出高电平
//	    switch(PWM_OUT->OUT_PIN_GROUP)   //使能PWM0输出
//		{
//		   case 0: PWM7_P27;
//		   		break;
//		   case 1: PWM7_P17;
//		   		break;
//		   case 2: PWM7_P67;
//		   		break;
//		   default:	PWM7_P27;
//		   		break;
//		}                                
//	    P_SW2 = 0x00;
//		
//	
//	    PWMCR = 0x80;                               //启动PWM模块
//	}
//}


