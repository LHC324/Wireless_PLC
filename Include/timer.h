#ifndef __TIMER_H_
#define __TIMER_H_

#include "config.h"

#define T0X1 0x80
#define T0X12 0x00

/*判断目标软件定时器是否超时*/
#define SET_SOFTTIMER_FLAG(_TARGET_FLAG)                   \
	do                                                     \
	{                                                      \
		if (_TARGET_FLAG.MenuDly16.Timer16Count)           \
		{                                                  \
			_TARGET_FLAG.MenuDly16.Timer16Count--;         \
			if (!_TARGET_FLAG.MenuDly16.Timer16Count)      \
			{                                              \
				_TARGET_FLAG.MenuDly16.Timer16Flag = true; \
			}                                              \
		}                                                  \
	} while (0);

/*置位目标串口接收帧标志*/

#define SET_FRAME(_COM_UARTx) \
	(_COM_UARTx.LNode[_COM_UARTx.Wptr].OverTime ? \
	(_COM_UARTx.LNode[_COM_UARTx.Wptr].OverTime--) : \
	((_COM_UARTx.LNode[_COM_UARTx.Wptr].Frame_Flag = true), \
 	(_COM_UARTx.Wptr = ((++_COM_UARTx.Wptr) & (MAX_NODE - 1))), \
 	(_COM_UARTx.LNode[_COM_UARTx.Wptr].Timer_Flag = false)))

typedef enum
{
	TIMER0 = 0x00,
	TIMER1,
	TIMER2,
	TIMER3,
	TIMER4
} Timer_TypsDef;

typedef struct
{
	uint8_t Register_IP;
	uint8_t Register_IPH;
} TIMER_NVIC_TypeDef;

typedef struct
{
	Timer_TypsDef Instance;
	uint8_t Register_AUXR;
	uint8_t Timer_Mode;
	uint16_t Timer_Count;
	uint8_t RunTimer_Enable : 1;
	uint8_t Interrupt_Enable : 1;
	TIMER_NVIC_TypeDef Timer_NVIC;
} TIM_HandleTypeDef;

void TIM_Base_MspInit(TIM_HandleTypeDef *const tim_baseHandle);
void Timer0_Init();
void Timer1_Init();

#endif