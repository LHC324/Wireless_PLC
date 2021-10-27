#include<STC8.h>
#include"HardWareIIC.h"

#define I2CCFG          (*(unsigned char volatile xdata *)0xfe80)
#define I2CMSCR         (*(unsigned char volatile xdata *)0xfe81)
#define I2CMSST         (*(unsigned char volatile xdata *)0xfe82)
#define I2CSLCR         (*(unsigned char volatile xdata *)0xfe83)
#define I2CSLST         (*(unsigned char volatile xdata *)0xfe84)
#define I2CSLADR        (*(unsigned char volatile xdata *)0xfe85)
#define I2CTXD          (*(unsigned char volatile xdata *)0xfe86)
#define I2CRXD          (*(unsigned char volatile xdata *)0xfe87)

bit busy11;
//*****************************************************************
sbit    SDA         =   P1^4;
sbit    SCL         =   P1^5;
//



void IIC_Init(void)
{
	P_SW2 = 0x80;

    I2CCFG = 0xe0;                              //使能I2C主机模式
    I2CMSST = 0x00;
    EA = 1;
}



void I2C_Isr() interrupt 24
{
    char store;
    
    store = P_SW2;
    P_SW2 |= 0x80;
    if (I2CMSST & 0x40)
    {
        I2CMSST &= ~0x40;                       //清中断标志
        busy11 = 0;
    }
    P_SW2 = store;
}

void Start()
{
	unsigned short ii = 2000;
    busy11 = 1;
    I2CMSCR = 0x81;                             //发送START命令
    while (busy11)
	{
	 	if(!ii --)
		{
			break;
		}
	}

}

void SendData(char dat)
{
	unsigned short ii = 2000;
    I2CTXD = dat;                               //写数据到数据缓冲区
    busy11 = 1;
    I2CMSCR = 0x82;                             //发送SEND命令
	while (busy11)
	{
	 	if(!ii --)
		{
			break;
		}
	}
}

void RecvACK()
{
    
	unsigned short ii = 2000;
	busy11 = 1;
    I2CMSCR = 0x83;                             //发送读ACK命令
     while (busy11)
	{
	 	if(!ii --)
		{
			break;
		}
	}
}

char RecvData()
{
	unsigned short ii = 2000;
    busy11 = 1;
    I2CMSCR = 0x84;                             //发送RECV命令
     while (busy11)
	{
	 	if(!ii --)
		{
			break;
		}
	}
    return I2CRXD;
}

void SendACK()
{
	unsigned short ii = 2000;
    I2CMSST = 0x00;                             //设置ACK信号
    busy11 = 1;
    I2CMSCR = 0x85;                             //发送ACK命令
     while (busy11)
	{
	 	if(!ii --)
		{
			break;
		}
	}
}

void SendNAK()
{
	unsigned short ii = 2000;
    I2CMSST = 0x01;                             //设置NAK信号
    busy11 = 1;
    I2CMSCR = 0x85;                             //发送ACK命令
     while (busy11)
	{
	 	if(!ii --)
		{
			break;
		}
	}
}

void Stop()
{
	unsigned short ii = 2000;
    busy11 = 1;
    I2CMSCR = 0x86;                             //发送STOP命令
     while (busy11)
	{
	 	if(!ii --)
		{
			break;
		}
	}
}

//void Delay()
//{
//    int i;
//
//    for (i=0; i<3000; i++)
//    {
//       _nop();_nop();_nop();
//    }
//}


