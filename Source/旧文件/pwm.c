//#include"config.h"
///*********************************************************************
//* ��������void PWM0_OUT(unsigned short cycle,unsigned short LOW_Val,unsigned short HIGH_Val,unsigned char Pin)
//* ���ܣ�  ָ����������ɿص�PWM����
//* ������
//* ���ߣ�zhao1peng
//* note�� ��PWM�����ʱ���ǻ���PCAʱ�ӵ�  �ɸ���PCAʱ�ӵ�����ģ�����
//* �ֱ����ã���ͬʱ��·���PWM�� 
//* PWM ���ŵ����Ĭ����ÿһ��PWM�ĵ�һ�����������
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
//	    PWMCKS = 0x00;                              // PWMʱ��Ϊϵͳʱ��
//	    PWMC = PWM_OUT->cycle;                               //����PWM����Ϊcycle H��PWMʱ��
//	    PWM0T1= PWM_OUT->LOW_Val;                            //�ڼ���ֵΪLOW_Val H�ط�����͵�ƽ
//	    PWM0T2= PWM_OUT->HIGH_Val;                           //�ڼ���ֵΪHIGH_Val H�ط�����ߵ�ƽ
//	    
//		
//		switch(PWM_OUT->OUT_PIN_GROUP)  //ʹ��PWM0���
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
//		PWMCR = 0x80;  	  //����PWMģ��
//	}
//
//	if((PWM_OUT->PWM_MOD) == PWM_MOD1)
//	{
//		P_SW2 = 0x80;
//	
//	    PWMCKS = 0x00;                              // PWMʱ��Ϊϵͳʱ��
//	    PWMC = PWM_OUT->cycle;                               //����PWM����Ϊ1000H��PWMʱ��
//	    PWM1T1= PWM_OUT->LOW_Val;                            //�ڼ���ֵΪ100H�ط�����͵�ƽ
//	    PWM1T2= PWM_OUT->HIGH_Val;                           //�ڼ���ֵΪ500H�ط�����ߵ�ƽ
//	    switch(PWM_OUT->OUT_PIN_GROUP) //ʹ��PWM0���
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
//	    PWMCR = 0x80;                               //����PWMģ��
//	}
//	if((PWM_OUT->PWM_MOD) == PWM_MOD2)  //ʹ��PWM0���
//	{
//		P_SW2 = 0x80;
//	
//	    PWMCKS = 0x00;                              // PWMʱ��Ϊϵͳʱ��
//	    PWMC = PWM_OUT->cycle;                               //����PWM����Ϊ1000H��PWMʱ��
//	    PWM2T1= PWM_OUT->LOW_Val;                            //�ڼ���ֵΪ100H�ط�����͵�ƽ
//	    PWM2T2= PWM_OUT->HIGH_Val;                           //�ڼ���ֵΪ500H�ط�����ߵ�ƽ
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
//		}                             //ʹ��PWM0���
//	    P_SW2 = 0x00;
//		
//	
//	    PWMCR = 0x80;                               //����PWMģ��
//	}
//	if((PWM_OUT->PWM_MOD) == PWM_MOD3)
//	{
//		P_SW2 = 0x80;
//	
//	    PWMCKS = 0x00;                              // PWMʱ��Ϊϵͳʱ��
//	    PWMC = PWM_OUT->cycle;                               //����PWM����Ϊ1000H��PWMʱ��
//	    PWM3T1= PWM_OUT->LOW_Val;                            //�ڼ���ֵΪ100H�ط�����͵�ƽ
//	    PWM3T2= PWM_OUT->HIGH_Val;                           //�ڼ���ֵΪ500H�ط�����ߵ�ƽ
//	    switch(PWM_OUT->OUT_PIN_GROUP) //ʹ��PWM0���
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
//	    PWMCR = 0x80;                               //����PWMģ��
//	}
//	if((PWM_OUT->PWM_MOD) == PWM_MOD4)
//	{
//		P_SW2 = 0x80;
//	
//	    PWMCKS = 0x00;                              // PWMʱ��Ϊϵͳʱ��
//	    PWMC = PWM_OUT->cycle;                               //����PWM����Ϊ1000H��PWMʱ��
//	    PWM4T1= PWM_OUT->LOW_Val;                            //�ڼ���ֵΪ100H�ط�����͵�ƽ
//	    PWM4T2= PWM_OUT->HIGH_Val;                           //�ڼ���ֵΪ500H�ط�����ߵ�ƽ
//	    switch(PWM_OUT->OUT_PIN_GROUP)	  //ʹ��PWM0���
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
//	    PWMCR = 0x80;                               //����PWMģ��
//	}
//	if((PWM_OUT->PWM_MOD) == PWM_MOD5)	  //ʹ��PWM0���
//	{
//		P_SW2 = 0x80;
//	
//	    PWMCKS = 0x00;                              // PWMʱ��Ϊϵͳʱ��
//	    PWMC = PWM_OUT->cycle;                               //����PWM����Ϊ1000H��PWMʱ��
//	    PWM5T1= PWM_OUT->LOW_Val;                            //�ڼ���ֵΪ100H�ط�����͵�ƽ
//	    PWM5T2= PWM_OUT->HIGH_Val;                           //�ڼ���ֵΪ500H�ط�����ߵ�ƽ
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
//	    PWMCR = 0x80;                               //����PWMģ��
//	}
//	if((PWM_OUT->PWM_MOD) == PWM_MOD6)
//	{
//		P_SW2 = 0x80;
//	
//	    PWMCKS = 0x00;                              // PWMʱ��Ϊϵͳʱ��
//	    PWMC = PWM_OUT->cycle;                               //����PWM����Ϊ1000H��PWMʱ��
//	    PWM6T1= PWM_OUT->LOW_Val;                            //�ڼ���ֵΪ100H�ط�����͵�ƽ
//	    PWM6T2= PWM_OUT->HIGH_Val;                           //�ڼ���ֵΪ500H�ط�����ߵ�ƽ
//	    switch(PWM_OUT->OUT_PIN_GROUP)		  //ʹ��PWM0���
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
//	    PWMCR = 0x80;                               //����PWMģ��
//	}
//	if((PWM_OUT->PWM_MOD) == PWM_MOD7)
//	{
//		P_SW2 = 0x80;
//	
//	    PWMCKS = 0x00;                              // PWMʱ��Ϊϵͳʱ��
//	    PWMC = PWM_OUT->cycle;                               //����PWM����Ϊ1000H��PWMʱ��
//	    PWM7T1= PWM_OUT->LOW_Val;                            //�ڼ���ֵΪ100H�ط�����͵�ƽ
//	    PWM7T2= PWM_OUT->HIGH_Val;                           //�ڼ���ֵΪ500H�ط�����ߵ�ƽ
//	    switch(PWM_OUT->OUT_PIN_GROUP)   //ʹ��PWM0���
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
//	    PWMCR = 0x80;                               //����PWMģ��
//	}
//}


