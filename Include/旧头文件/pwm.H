#ifndef __PWM_H_
#define	__PWM_H_

#include "config.h"

#define PWM0_P20	PWM0CR = 0x80                              //PWM0/P2.0
#define PWM0_P10	PWM0CR = 0x88                              //PWM0_2/P1.0
#define PWM0_P60	PWM0CR = 0x90                              //PWM0_3/P6.0

#define PWM1_P21	PWM1CR = 0x80                              //PWM1/P2.1
#define PWM1_P11	PWM1CR = 0x88                              //PWM1_2/P1.1
#define PWM1_P61	PWM1CR = 0x90                              //PWM1_3/P6.1

#define PWM2_P22	PWM2CR = 0x80                              //PWM2/P2.2
#define PWM2_P12	PWM2CR = 0x88                              //PWM2_2/P1.2
#define PWM2_P62	PWM2CR = 0x90                              //PWM2_3/P6.2

#define PWM3_P23	PWM3CR = 0x80                              //PWM3/P2.3
#define PWM3_P13	PWM3CR = 0x88                              //PWM3_2/P1.3
#define PWM3_P63	PWM3CR = 0x90                              //PWM3_3/P6.3

#define PWM4_P24	PWM4CR = 0x80                              //PWM4/P2.4
#define PWM4_P14	PWM4CR = 0x88                              //PWM4_2/P1.4
#define PWM4_P64	PWM4CR = 0x90                              //PWM4_3/P6.4

#define PWM5_P25	PWM5CR = 0x80                              //PWM5/P2.5
#define PWM5_P15	PWM5CR = 0x88                             //PWM5_2/P1.5
#define PWM5_P65	PWM5CR = 0x90                              //PWM5_3/P6.5

#define PWM6_P26	PWM6CR = 0x80                              //PWM6/P2.6
#define PWM6_P16	PWM6CR = 0x88                              //PWM6_2/P1.6
#define PWM6_P66	PWM6CR = 0x90                              //PWM6_3/P6.6

#define PWM7_P27	PWM7CR = 0x80                              //PWM7/P2.7
#define PWM7_P17	PWM7CR = 0x88                              //PWM7_2/P1.7
#define PWM7_P67	PWM7CR = 0x90                              //PWM7_3/P6.7

#define PWM_MOD0 0	//mode 0
#define PWM_MOD1 1	//mode 1
#define PWM_MOD2 2	//mode 2
#define PWM_MOD3 3	//mode 3
#define PWM_MOD4 4	//mode 4
#define PWM_MOD5 5	//mode 5
#define PWM_MOD6 6	//mode 6
#define PWM_MOD7 7	//mode 7

#define PIN_GROUP1 0 
#define PIN_GROUP2 1 
#define PIN_GROUP3 2 


typedef struct
{
	unsigned char PWM_MOD;	 //PWM 使用的模块
	unsigned char OUT_PIN_GROUP;	 //该模块输出PWM的输出引脚
	unsigned short cycle;	 //PWM的输出频率周期
	unsigned short LOW_Val;	 //在计数值为LOW_Val地方输出低电平
	unsigned short HIGH_Val; //在计数值为HIGH_Val地方输出高电平

}PWM_STATUE;


void PWM_MOD_OUT(PWM_STATUE *PWM_OUT); 

#endif