#include "usart.h"
#include "Control.h"
#include "systemTimer.h"
// #include "queue.h"

/*********************************************************
* 函数名：
* 功能：
* 参数：
* 作者：
* note：
        同时使用多个串口的时候会出现数据传输错误的情况 建议在使用该板子与其他
        通讯模块建立通讯的时候使用1对1的建立连接的模式

        解决了多串口同时数据传输错误问题 //2021/5/31

        在切换串口的引脚输入时，建议将RX端初始化的时候给个0值 TX引脚手动给个1值
        （基于STC单片机的特性）

**********************************************************/

Uart_HandleTypeDef Uart1; //串口1句柄
Uart_HandleTypeDef Uart2; //串口2句柄
Uart_HandleTypeDef Uart3; //串口3句柄
Uart_HandleTypeDef Uart4; //串口4句柄

#define ISR_RECEIVE(current_uart, uart_id, src, dest)                                                                                 \
    do                                                                                                                                \
    {                                                                                                                                 \
        current_uart.LNode[current_uart.Wptr].Timer_Flag = true;                                                                      \
        if (!current_uart.LNode[current_uart.Wptr].Frame_Flag)                                                                        \
        {                                                                                                                             \
            current_uart.LNode[current_uart.Wptr].OverTime = MAX_SILENCE;                                                             \
            if (current_uart.LNode[current_uart.Wptr].Rx_Length < MAX_SIZE)                                                           \
            {                                                                                                                         \
                current_uart.LNode[current_uart.Wptr].Rx_Buffer[current_uart.LNode[current_uart.Wptr].Rx_Length++] = S##uart_id##BUF; \
                current_uart.LNode[current_uart.Wptr].Source_Channel = src;                                                           \
                current_uart.LNode[current_uart.Wptr].Target_Channel = dest;                                                          \
            }                                                                                                                         \
        }                                                                                                                             \
    } while (0);

/*定义一个当前发起请求通道变量*/
volatile  SEL_CHANNEL current_request_channel = CHANNEL_IDLE;

/*********************************************************
 * 函数名：void Uart_1Init(void)
 * 功能：  串口1的初始化
 * 参数：
 * 作者：  LHC
 * note：
 *		使用的是定时器1作为波特率发生器,LAN口用
 **********************************************************/
void Uart1_Init(void) //串口1选择定时器1作为波特率发生器
{
    Uart1.Instance = UART1;
    Uart1.Register_SCON = 0x50; //模式1，8位数据，可变波特率
    Uart1.Uart_Mode = 0x00;     //定时器模式0，16bit自动重载
    Uart1.Uart_Count = UART1_BRT;
    Uart1.RunUart_Enable = true;
    Uart1.Interrupt_Enable = true;
    Uart1.Register_AUXR = 0x40;  //定时器1，1T模式
    Uart1.Register_AUXR &= 0xFE; //波特率发生器选用定时器1，最好按照要求来

    Uart1.Uart_NVIC.Register_IP = 0xEF; // PS=0,PSH=0,串口1中断优先级为第0级，最低级
    Uart1.Uart_NVIC.Register_IPH = 0xEF;

    Uart_Base_MspInit(&Uart1);
}

/*********************************************************
 * 函数名：void Uart1_ISR() interrupt 4 using 2
 * 功能：  串口1的定时中断服务函数
 * 参数：
 * 作者：  LHC
 * note：
 *		使用的是定时器1作为波特率发生器,LAN口用
 **********************************************************/
void Uart1_ISR() interrupt 4 using 2 //串口1的定时中断服务函数
{
    /*发送中断标志*/
    if (TI)
    {
        TI = 0;
        /*发送完成，清除占用*/
        Uart1.Uartx_busy = false;
    }
    /*接收中断标志*/
    if (RI)
    {
        RI = 0;

        COM_UART1.LNode[COM_UART1.Wptr].Timer_Flag = true;
        if (!COM_UART1.LNode[COM_UART1.Wptr].Frame_Flag)
        {
            COM_UART1.LNode[COM_UART1.Wptr].OverTime = MAX_SILENCE;
            if (COM_UART1.LNode[COM_UART1.Wptr].Rx_Length < MAX_SIZE)
            {
                COM_UART1.LNode[COM_UART1.Wptr].Rx_Buffer[COM_UART1.LNode[COM_UART1.Wptr].Rx_Length++] = SBUF;
                COM_UART1.LNode[COM_UART1.Wptr].Source_Channel = CHANNEL_LAN;
                COM_UART1.LNode[COM_UART1.Wptr].Target_Channel = CHANNEL_PLC;
            }
        }
        /*设置当前请求通道*/
        current_request_channel = CHANNEL_LAN;
        // ISR_RECEIVE(COM_UART1, ,CHANNEL_LAN, CHANNEL_PLC);
    }
}

/*********************************************************
 * 函数名：void Uart_2Init(void)
 * 功能：  串口2的初始化
 * 参数：
 * 作者：  LHC
 * note：
 *		使用的是定时器2作为波特率发生器,485口用
 **********************************************************/
void Uart2_Init(void) //串口2选择定时器2作为波特率发生器
{
    Uart2.Instance = UART2;
    Uart2.Register_SCON = 0x10; //模式1，8位数据，可变波特率，开启串口2接收
    Uart2.Uart_Mode = 0x00;     //定时器模式0，16bit自动重载
    Uart2.Uart_Count = UART2_BRT;
    Uart2.RunUart_Enable = true;
    Uart2.Interrupt_Enable = 0x01;
    Uart2.Register_AUXR = 0x14;         //开启定时器2，1T模式
    Uart2.Uart_NVIC.Register_IP = 0xFE; // PS2=0,PS2H=0,串口2中断优先级为第0级
    Uart2.Uart_NVIC.Register_IPH = 0xFE;

    Uart_Base_MspInit(&Uart2);
}

/*********************************************************
 * 函数名：void Uart2_ISR() interrupt 8 using 2
 * 功能：  串口2中断函数
 * 参数：
 * 作者：  LHC
 * note：
 *		使用的是定时器2作为波特率发生器,4G口用
 **********************************************************/
void Uart2_ISR() interrupt 8 using 2
{   /*发送中断*/
    if (S2CON & S2TI)
    {
        S2CON &= ~S2TI;
        /*发送完成，清除占用*/
        Uart2.Uartx_busy = false;
    }
    /*接收中断*/
    if (S2CON & S2RI)
    {
        S2CON &= ~S2RI;

        COM_UART2.LNode[COM_UART2.Wptr].Timer_Flag = true;
        if (!COM_UART2.LNode[COM_UART2.Wptr].Frame_Flag)
        {
            COM_UART2.LNode[COM_UART2.Wptr].OverTime = MAX_SILENCE;
            if (COM_UART2.LNode[COM_UART2.Wptr].Rx_Length < MAX_SIZE)
            {
                COM_UART2.LNode[COM_UART2.Wptr].Rx_Buffer[COM_UART2.LNode[COM_UART2.Wptr].Rx_Length++] = S2BUF;
                COM_UART2.LNode[COM_UART2.Wptr].Source_Channel = CHANNEL_WIFI;
                COM_UART2.LNode[COM_UART2.Wptr].Target_Channel = CHANNEL_PLC;
            }
        }

        /*设置当前请求通道*/
        current_request_channel = CHANNEL_WIFI;
        // ISR_RECEIVE(COM_UART2, 2, CHANNEL_WIFI, CHANNEL_PLC);
    }
}

///*********************************************************
//* 函数名：void Uart_3Init(void)
//* 功能：  串口3的初始化
//* 参数：
//* 作者：  LHC
//* note：
//*		使用的是定时器3作为波特率发生器,恩外部485转发
//**********************************************************/
void Uart3_Init(void) //串口3选择定时器3作为波特率发生器
{
    Uart3.Instance = UART3;
    Uart3.Register_SCON = 0x50; //模式0，8位数据，可变波特率；定时器3，1T模式
	// Uart3.Register_SCON = 0xD0; //模式1，9位数据，可变波特率；定时器3，1T模式
    Uart3.Uart_Mode = 0x0A;     //打开定时器3，1T模式
    Uart3.Uart_Count = UART3_BRT;
    Uart3.Interrupt_Enable = 0x08;

    Uart_Base_MspInit(&Uart3);
}

/*********************************************************
 * 函数名：void Uart3_ISR() interrupt 17 using 2
 * 功能：  串口3中断函数
 * 参数：
 * 作者：  LHC
 * note：
 *		使用的是定时器3作为波特率发生器,RS485模块
 **********************************************************/
void Uart3_ISR() interrupt 17 using 2
{
    /*发送中断完成*/
    if (S3CON & S3TI)
    {
        S3CON &= ~S3TI;
        Uart3.Uartx_busy = false; //发送完成，清除占用
    }
    /*接收中断*/
    if (S3CON & S3RI)
    {
        S3CON &= ~S3RI;

        COM_UART3.LNode[COM_UART3.Wptr].Timer_Flag = true;
        if (!COM_UART3.LNode[COM_UART3.Wptr].Frame_Flag)
        {
            COM_UART3.LNode[COM_UART3.Wptr].OverTime = MAX_SILENCE;
            if (COM_UART3.LNode[COM_UART3.Wptr].Rx_Length < MAX_SIZE)
            {
                COM_UART3.LNode[COM_UART3.Wptr].Rx_Buffer[COM_UART3.LNode[COM_UART3.Wptr].Rx_Length++] = S3BUF;
                COM_UART3.LNode[COM_UART3.Wptr].Source_Channel = CHANNEL_RS485;
                COM_UART3.LNode[COM_UART3.Wptr].Target_Channel = CHANNEL_PLC;
            }
        }

        /*设置当前请求通道*/
        current_request_channel = CHANNEL_RS485;
        // ISR_RECEIVE(COM_UART3, 3, CHANNEL_RS485, CHANNEL_PLC);
    }
}

///*********************************************************
//* 函数名：void Uart_4Init(void)
//* 功能：  串口4的初始化
//* 参数：
//* 作者：  LHC
//* note：
//*		使用的是定时器4作为波特率发生器,PLC口用
//**********************************************************/
void Uart4_Init(void) //串口4选择定时器4作为波特率发生器
{
    Uart4.Instance = UART4;
    Uart4.Register_SCON = 0x50; //模式0，8位数据，可变波特率
	// Uart4.Register_SCON = 0xD0; //模式1，9位数据，可变波特率
    Uart4.Uart_Mode = 0xA0;     //定时器模式0，16bit自动重载;开启定时器4，1T模式
    Uart4.Uart_Count = UART4_BRT;
    Uart4.Interrupt_Enable = 0x10;

    Uart_Base_MspInit(&Uart4);
}

/*********************************************************
 * 函数名：void Uart4_Isr() interrupt 18 using 1
 * 功能：  串口4中断函数
 * 参数：
 * 作者：  LHC
 * note：
 *		使用的是定时器4作为波特率发生器,PLC口用
 **********************************************************/
void Uart4_Isr() interrupt 18 using 2
{                             /*发送中断*/
    // SEL_CHANNEL temp_channel = CHANNEL_RS485;

    if (S4CON & S4TI)
    {
        S4CON &= ~S4TI;
        /*发送完成，清除占用*/
        Uart4.Uartx_busy = false;
    }
    /*接收中断*/
    if (S4CON & S4RI)
    {
        S4CON &= ~S4RI;

        COM_UART4.LNode[COM_UART4.Wptr].Timer_Flag = true;
        if (!COM_UART4.LNode[COM_UART4.Wptr].Frame_Flag)
        {
            COM_UART4.LNode[COM_UART4.Wptr].OverTime = MAX_SILENCE;
            if (COM_UART4.LNode[COM_UART4.Wptr].Rx_Length < MAX_SIZE)
            {
                COM_UART4.LNode[COM_UART4.Wptr].Rx_Buffer[COM_UART4.LNode[COM_UART4.Wptr].Rx_Length++] = S4BUF;
                COM_UART4.LNode[COM_UART4.Wptr].Source_Channel = CHANNEL_PLC;
                COM_UART4.LNode[COM_UART4.Wptr].Target_Channel = current_request_channel;
            }
        }

        /*判断当前PLC是主动发送还是被动请求*/
        // if (current_request_channel != CHANNEL_IDLE)
        // {
        //     temp_channel = CHANNEL_RS485;
        // }
        // else
        // {
        //     temp_channel = current_request_channel;
        // }
        // ISR_RECEIVE(COM_UART4, 4, CHANNEL_PLC, CHANNEL_RS485);
    }
}

/**********************************公用函数************************/

/*********************************************************
 * 函数名：Uart_Base_MspInit(Uart_HandleTypeDef *uart_baseHandle)
 * 功能：  所有串口底层初始化函数
 * 参数：  Uart_HandleTypeDef *uart_baseHandle串口句柄
 * 作者：  LHC
 * note：
 *		注意正确给出串口句柄
 **********************************************************/
void Uart_Base_MspInit(Uart_HandleTypeDef *const uart_baseHandle)
{
    if (uart_baseHandle->Instance == UART1)
    {
        SCON = uart_baseHandle->Register_SCON;
        TMOD |= uart_baseHandle->Uart_Mode;
        TL1 = uart_baseHandle->Uart_Count;
        TH1 = uart_baseHandle->Uart_Count >> 8;
        TR1 = uart_baseHandle->RunUart_Enable;
        AUXR |= uart_baseHandle->Register_AUXR;
        IP &= uart_baseHandle->Uart_NVIC.Register_IP;
        IPH &= uart_baseHandle->Uart_NVIC.Register_IPH;
#if USEING_PRINTF //如果使用printf
        TI = 1;   //放到printf重定向
#else
        ES = uart_baseHandle->Interrupt_Enable; //串口1中断允许位
#endif
    }
    else if (uart_baseHandle->Instance == UART2)
    {
        S2CON = uart_baseHandle->Register_SCON;
        TL2 = uart_baseHandle->Uart_Count;
        TH2 = uart_baseHandle->Uart_Count >> 8;
        AUXR |= uart_baseHandle->Register_AUXR;
        IE2 |= uart_baseHandle->Interrupt_Enable; //串口2中断允许位
        IP2 &= uart_baseHandle->Uart_NVIC.Register_IP;
        IP2H &= uart_baseHandle->Uart_NVIC.Register_IPH;
    }
    else if (uart_baseHandle->Instance == UART3)
    {
        S3CON = uart_baseHandle->Register_SCON;
        T4T3M = uart_baseHandle->Uart_Mode;
        T3L = uart_baseHandle->Uart_Count;
        T3H = uart_baseHandle->Uart_Count >> 8;
        IE2 |= uart_baseHandle->Interrupt_Enable; //串口3中断允许位
    }
    else if (uart_baseHandle->Instance == UART4)
    {
        S4CON = uart_baseHandle->Register_SCON;
        T4T3M |= uart_baseHandle->Uart_Mode; //此处串口3和串口4共用
        T4L = uart_baseHandle->Uart_Count;
        T4H = uart_baseHandle->Uart_Count >> 8;
        IE2 |= uart_baseHandle->Interrupt_Enable; //串口4中断允许位
    }
}

/*********************************************************
 * 函数名：static void Busy_Await(Uart_HandleTypeDef * const Uart, uint16_t overtime)
 * 功能：  字节发送超时等待机制
 * 参数：  Uart_HandleTypeDef * const Uart;uint16_t overtime
 * 作者：  LHC
 * note：
 *
 **********************************************************/
void Busy_Await(Uart_HandleTypeDef *const Uart, uint16_t overtime)
{

    while (Uart->Uartx_busy) //等待发送完成：Uart->Uartx_busy清零
    {
        if (!(overtime--))
            break;
    }

    Uart->Uartx_busy = true; //发送数据，把相应串口置忙
}

/*********************************************************
 * 函数名：Uartx_SendStr(Uart_HandleTypeDef *const Uart,uint8_t *p,uint8_t length)
 * 功能：  所有串口字符串发送函数
 * 参数：  Uart_HandleTypeDef *const Uart,uint8_t *p;uint8_t length
 * 作者：  LHC
 * note：
 *
 **********************************************************/
void Uartx_SendStr(Uart_HandleTypeDef *const Uart, uint8_t *p, uint8_t length)
{
	uint8_t psw_p = P;
	psw_p <<= 3U;
	
    while (length--)
    {
        Busy_Await(&(*Uart), UART_BYTE_SENDOVERTIME); //等待当前字节发送完成
        switch (Uart->Instance)
        {
        case UART1:
            SBUF = *p++;
            break;
        case UART2:
            S2BUF = *p++;
            break;
        case UART3:
            // if (System_Parameter.Ppistate)
            {
                S3CON |= psw_p;
            }
            S3BUF = *p++;
            break;
        case UART4:
            // if (System_Parameter.Ppistate)
            {
                S4CON |= psw_p;
            }
            S4BUF = *p++;
            break;
        default:
            break;
        }
    }
}

/*********************************************************
 * 函数名：char putchar(char str)
 * 功能：  putchar重定向,被printf调用
 * 参数：  char str，发送的字符串
 * 作者：  LHC
 * note：
 *		  使用printf函数将会占用1K 左右FLASH
 **********************************************************/
#if (USEING_PRINTF)
char putchar(char str)
{
    ES = 0; //关闭串口1中断
    SBUF = str;

    while (!TI)
        ;

    TI = 0;
    ES = 1;
    return str;
}
#endif

/**********************************公用函数************************/
