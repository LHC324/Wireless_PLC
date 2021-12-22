#ifndef __CONFIG_H_
#define __CONFIG_H_

#include "STC8.H"
#include <stdio.h>
#include <intrins.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <absacc.h> //可直接操作内存地址

/*屏保界面LOGO*/
#define START_LOGO Kmust_Image
/**********************布尔变量定义**********************/
#define true 1
#define false 0
/**********************布尔变量定义**********************/
#define EXTERNAL_CRYSTAL 0 //使用外部晶振
#define USE_PRINTF_DEBUG 0 //调试是否启用串口

#define COUNTMAX 65536U
/*(1/FOSC)*count =times(us)->count = time*FOSC/1000(ms)*/
#define FOSC  27000000UL// 11059200UL
/*1ms(时钟频率越高，所能产生的时间越小)*/
#define TIMES 10U
/*定时器模式选择*/
#define TIMER_MODE 12U
/*定时器分频系数，默认为一分频*/
#define TIME_DIV 1U
#define T12_MODE (TIMES * FOSC / 1000 / 12 / TIME_DIV)
#define T1_MODE (TIMES * FOSC / 1000 / TIME_DIV)
#define TIMERS_OVERFLOW (COUNTMAX * 1000 * TIMER_MODE * TIME_DIV) / FOSC

#define OPEN_GLOBAL_OUTAGE() (EA = 1 << 0)
#define CLOSE_GLOBAL_OUTAGE() (EA = 0 << 0)
/*判断延时数是否超出硬件允许范围*/
#if (TIMES > TIMERS_OVERFLOW)
#error The timer cannot generate the current duration!
#endif
/*断言检查*/
// #define assert_param(expr) ((expr) ? (void)0U : assert_failed((uint8_t *)__FILE__, __LINE__))
// /* Exported functions ------------------------------------------------------- */
// void assert_failed(uint8_t* file, uint32_t line);
// #else
// #define assert_param(expr) ((void)0U)
// #endif /* USE_FULL_ASSERT */
/***********************************常用的数据类型***********************************/
typedef unsigned char uint8_t;
typedef signed char int8_t;
typedef unsigned short int uint16_t;
typedef unsigned long uint32_t;
typedef signed long int32_t;
typedef volatile __IO;
/***********************************常用的数据类型***********************************/

/***********************************系统上电参数***********************************/
#define DEFAULT_SYSTEM_PARAMETER "\xFF\xFF\xFF\xFF\x08\x08\x02\x08\x01\x01\x00\x00\x01\x02\x36\x71"
#define START_SAVEADDRESS 0x0000         //参数存储开始地址
#define BAUDRATE_SAVEADDRESS 0x0004      //波特率
#define PLCSTAE_SAVEADDRESS 0x0005       // PLC状态
#define COMMUNICATION_SAVEADDRESS 0x0006 //通讯类型
#define WIFIINIT_SAVEADDRESS 0x0007      // WIFI模块初始化标志位
#define PASSWORDBITS 4                   //密码位数
#define UARTX_NUMBERS 4                  //芯片串口数目

typedef struct
{
    /*当前密码索引*/
    uint8_t Index;
    /*密码有效长度标志位*/
    uint8_t Bit_Efficient_Flag;
    /*第一次修改密码标志*/
    uint8_t First_Input_Flag;
    uint8_t PassWordbuff[PASSWORDBITS];
} PASSWORDSTRUCT;

typedef struct
{
    PASSWORDSTRUCT PSWNext;           //密码
    uint8_t BaudIndex[UARTX_NUMBERS]; //波特率
    uint8_t PlcState;                 // PLC状态
    uint8_t CommunicationType;        //通讯类型
    uint8_t WifiInitFlag;             // WIFI初始化标志
    uint8_t Apstate;                  //热点状态
    uint8_t WorkMode;                 //工作模式
    uint8_t CurrentSlave;             //当前从机
    uint16_t CRC16;                   // CRC校验码
} SYSTEM_PARAMETER;                   //系统参数

extern SYSTEM_PARAMETER System_Parameter;
/***********************************系统上电参数***********************************/

/***********************************结构体的妙用 ***********************************/
#define offsetof(TYPE, MEMBER) ((size_t) & ((TYPE *)0)->MEMBER) //获取结构体成员对首地址偏移量
#define container_of(ptr, type, member) (                  \
    {                                                      \
        const typeof(((type *)0)->member) *__mptr = (ptr); \
        (type *)((char *)__mptr - offsetof(type, member)); \
    }) //过结构体成员变量获得对应的结构体首地址
/***********************************结构体的妙用 ***********************************/

/***********************************多串口通讯***********************************/
#define FREE 0 // 不忙
#define BUSY 1 // 忙
#define MASTER 0x00
#define SLAVE 0x01
#define ETHERNET_ID 0x00
#define WIFI_ID 0x01
#define RS485_ID 0x02

// 通信结构体用常量
#define MAX_SIZE 64    // 缓冲区长度
#define MAX_SILENCE 1   // 两个字符最大间隔时间，MAX_SILENCE * 定时器周期，若定时器10ms，则静默时间为：10 * 10 = 100ms  #define	MAX_SILENCE
#define T_PLC_ANSWER 20 // PLC应答超时定时器，要求PLC在200ms内应答  #define	T_PLC_ANSWER	20

typedef enum
{
    CHANNEL_IDLE = 0x00,  // 空闲通道
    CHANNEL_LAN = 0x01,   // 以太网串口通道
    CHANNEL_LTE = 0x02,   // 4G串口通道
    CHANNEL_WIFI = 0x03,  // WiFI串口通道
    CHANNEL_RS485 = 0x04, // RS485串口通道
    CHANNEL_PLC = 0x05,   // PLC串口通道
} SEL_CHANNEL;

/*把具体串口进行抽象，并映射到对应的链表上*/
#define COM_UART1 Uart_LinkList[0]
#define COM_UART2 Uart_LinkList[1]
#define COM_UART3 Uart_LinkList[2]
#define COM_UART4 Uart_LinkList[3]

/*定义当前链队条数*/
#define MAX_LQUEUE 4U
/*定义每条链表最大节点数*/
#define MAX_NODE 24U // 20
/*定义循环值*/
//#define LOOP(x) (COM_UART##x.Wptr + 1U) % MAX_NODE)
/*判断环形队列为空处理方式1*/
#define QUEU_EMPTY(x) ((COM_UART##x).Rptr == (COM_UART##x).Wptr)
/*判断环形队列是否满*/
#define QUEUE_FULL(x) ((((COM_UART##x).Wptr + 1U) % MAX_NODE) != 0U)
/*设置队列读指针*/
#define SET_RPTR(x) ((COM_UART##x).Rptr = (((COM_UART##x).Rptr + 1U) % MAX_NODE))
// #define SET_RPTR(x) ((COM_UART##x).Rptr++ , ((COM_UART##x).Rptr %= MAX_NODE))
/*设置队列写指针*/
#define SET_WPTR(x) ((COM_UART##x).Wptr = (((COM_UART##x).Wptr + 1U) % MAX_NODE))
// #define SET_WPTR(x) ((COM_UART##x).Wptr++ ,  ((COM_UART##x).Wptr%= MAX_NODE))

/*链队数据结构*/
typedef struct
{
    volatile SEL_CHANNEL Source_Channel;     /*数据起源通道*/
    volatile SEL_CHANNEL Target_Channel;     /*数据交付通道*/
    volatile uint8_t Frame_Flag;          /*帧标志*/
    volatile uint8_t Timer_Flag;          /*打开定时器标志*/
    volatile uint8_t Rx_Buffer[MAX_SIZE]; /*数据接收缓冲区*/
    volatile uint16_t Rx_Length;          /*数据接收长度*/
    volatile uint16_t OverTime;           /*目标设备响应超时时间*/
    // uint8_t Next;                   /*指向下一个节点*/
} Uart_Queu;

typedef struct
{
    volatile Uart_Queu LNode[MAX_NODE];
    //存储R ,W指针，表示一个队列
    volatile uint8_t Wptr;
    volatile uint8_t Rptr;
    // uint8_t Buffer_Size;
} Uart_List;

/*声明链队*/
extern Uart_List xdata Uart_LinkList[MAX_LQUEUE];

typedef struct
{
    SEL_CHANNEL Source_Channel; /*数据起源通道*/
    SEL_CHANNEL Target_Channel; /*数据交付通道*/
    void (*pHandle)(SEL_CHANNEL, SEL_CHANNEL);
    // void (*pHandle)(void);
} ComData_Handle;

/***********************************多串口通讯***********************************/
extern uint8_t xdata mempool[5U * 1024];
/***********************************函数声明***********************************/
void Init_All(void);
bit CheckIap_Flash(void);
// extern void Init_ListQueue(Uart_List *List);
/***********************************函数声明***********************************/
#endif