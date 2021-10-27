#ifndef __TIMER_H_
#define __TIMER_H_

#include "config.h"


#define T0X1  0x80
#define T0X12 0x00

/*置位目标串口接收帧标志*/
// //#define SET_FRAME(COM_UARTx) (COM_UARTx.OverTime ? (COM_UARTx.OverTime--):(COM_UARTx.Frame_Flag = true))
#define SET_FRAME(COM_UARTx) (COM_UARTx.LNode[COM_UARTx.Wptr].OverTime ? \
							 (COM_UARTx.LNode[COM_UARTx.Wptr].OverTime--): \
							 ((COM_UARTx.LNode[COM_UARTx.Wptr].Frame_Flag = true), \
							 (COM_UARTx.Wptr = ((COM_UARTx.Wptr + 1U) % MAX_NODE)), \
							 (COM_UARTx.LNode[COM_UARTx.Wptr].Timer_Flag = false)))

typedef enum
{
	TIMER0 = 0x00,
	TIMER1,
	TIMER2,
	TIMER3,
	TIMER4
}Timer_TypsDef;

typedef struct 
{
	uint8_t Register_IP;
	uint8_t Register_IPH;
}TIMER_NVIC_TypeDef;

typedef struct
{
	Timer_TypsDef Instance;
	uint8_t Register_AUXR;
	uint8_t Timer_Mode;
	uint16_t Timer_Count;
	uint8_t RunTimer_Enable:1;
	uint8_t Interrupt_Enable:1;
	TIMER_NVIC_TypeDef Timer_NVIC;
}TIM_HandleTypeDef;


void TIM_Base_MspInit(TIM_HandleTypeDef *const tim_baseHandle);
void Timer0_Init();
void Timer1_Init();

#endif