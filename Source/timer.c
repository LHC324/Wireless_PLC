#include "timer.h"
#include "systemTimer.h"

TIM_HandleTypeDef Timer0;
PUBLIC_TIMER16 PublicTimer16;

/*********************************************************
* 函数名：void WDT_init(void)
* 功能：  初始化看门狗
* 参数：
* 作者：
* note：
*
**********************************************************/
//void WDT_init(void)
//{
////  WDT_CONTR = 0x23;                           //使能看门狗,溢出时间约为0.5s
//    WDT_CONTR = 0x24;                           //使能看门狗,溢出时间约为1s
////  WDT_CONTR = 0x27;                           //使能看门狗,溢出时间约为8s
//}

//void CLRWDT(void)
//{
//		WDT_CONTR |= 0x10;//喂狗
//}

/*********************************************************
* 函数名： Timer0_Init()
* 功能：   定时器0 的初始化设置
* 参数：   无
* 作者：   LHC
* note：
*		   定时器2、3、4均工作在16bit自动重载模式
**********************************************************/

void Timer0_Init(void)
{
	Timer0.Instance = TIMER0;
	Timer0.Register_AUXR = T0X12; //12T模式
	Timer0.Timer_Mode = 0x00;
	Timer0.Timer_Count = (COUNTMAX - (T12_MODE));
	Timer0.RunTimer_Enable = true;		  //开启定时器0
	Timer0.Interrupt_Enable = true;		  //开启定时器0中断
	Timer0.Timer_NVIC.Register_IP = 0x20; //定时器0优先级为11，最高优先级
	Timer0.Timer_NVIC.Register_IPH = 0x20;
	TIM_Base_MspInit(&Timer0);
}

void TIM_Base_MspInit(TIM_HandleTypeDef *const tim_baseHandle)
{
	if (tim_baseHandle->Instance == TIMER0)
	{ //首次初始化，把TMOD和AUXR全部置零
		AUXR = tim_baseHandle->Register_AUXR;
		TMOD = tim_baseHandle->Timer_Mode;			  //模式0
		TL0 = (uint8_t)(tim_baseHandle->Timer_Count); //65536-11.0592M/12/1000
		TH0 = (uint8_t)((tim_baseHandle->Timer_Count) >> 8);
		TR0 = tim_baseHandle->RunTimer_Enable;	//启动定时器
		ET0 = tim_baseHandle->Interrupt_Enable; //使能定时器中断
		IP |= tim_baseHandle->Timer_NVIC.Register_IP;
		IPH |= tim_baseHandle->Timer_NVIC.Register_IPH;
		//		EA = 1;
	}
}

#define CHECK_UART_FRAME(_ID) 							   \
do									     				   \
{									                       \
	if(COM_UART##_ID.LNode[COM_UART##_ID.Wptr].Timer_Flag) \
	SET_FRAME(COM_UART##_ID);	                           \
} while (0)

/**
 * @brief	定时器0的中断服务函数
 * @details	
 * @param	None
 * @retval	None
 */
void Timer0_ISR() interrupt 1 using 0
{
	/*软件定时器*/
	// systemTimer();
	SET_SOFTTIMER_FLAG(PublicTimer16);

	// if(COM_UART1.LNode[COM_UART1.Wptr].Timer_Flag)
	// 	/*以太网串口接收字符间隔超时处理*/
	// 	SET_FRAME(COM_UART1);
	// if(COM_UART2.LNode[COM_UART2.Wptr].Timer_Flag)
	// 	/*4G/WiFi串口接收字符间隔超时处理*/
	// 	SET_FRAME(COM_UART2);
	// if(COM_UART3.LNode[COM_UART3.Wptr].Timer_Flag)
	// 	/*RS485串口接收字符间隔超时处理*/
	// 	SET_FRAME(COM_UART3);
	// if(COM_UART4.LNode[COM_UART4.Wptr].Timer_Flag)
	// 	/*PLC串口接收字符间隔超时处理*/
	// 	SET_FRAME(COM_UART4);

	CHECK_UART_FRAME(1); /*以太网串口接收字符间隔超时处理*/
	CHECK_UART_FRAME(2); /*4G/WiFi串口接收字符间隔超时处理*/
	CHECK_UART_FRAME(3); /*RS485串口接收字符间隔超时处理*/
#if !USING_PORT0_SINGLE
	CHECK_UART_FRAME(4); /*PLC串口接收字符间隔超时处理*/
#else
//	if (!COM_UART4.Timer_Flag)
//		return;
	if (COM_UART4.OverTime)
	{
		if (!--COM_UART4.OverTime)
			COM_UART4.Frame_Flag = true;
	}
	// COM_UART4.Timer_Flag = false;

					
#endif
}


void Delay_ms(unsigned short time)
{
    unsigned short temp;

    temp = time;

    while(temp --)
    {
        Delay1ms();
    }
}

/*禁止编译器优化该模块*/
#pragma OPTIMIZE(0)

void Delay1ms()		//@27MHz
{
    unsigned char i, j;

    i = 11;
    j = 300;

    do
    {
        while (--j);
    }
    while (--i);
}
