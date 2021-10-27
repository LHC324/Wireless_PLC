#include"HardWareSPI.h"
#include<STC8.h>

/*********************************************************************************
* 函数名：
* 功能：
* 参数：
* 作者：zhao1peng
* note：
* 该STC单片机由于只有一个SPI通讯寄存器，但是能切换SPI通讯的引脚 从而实现多路主SPI
* 
*
*
*********************************************************************************/

 #define SPI1_CS P1^0
 bit busy_spi;

 #define LED1 P30
 #define LED2 P31
 #define uint8_t unsigned char

 unsigned char SPI_DATA;//储存SPI回读数据


/*********************************************************
* 函数名：void SPI_MasterIit(void)
* 功能：  初始化SPI的中断形式
* 参数：
* 作者：zhao1peng
* note：
*硬件SPI的时钟选择请根据实际需求进行修改相应寄存器 SPCTL 的参数值
* 
*
**********************************************************/


void SPI_MasterInit(void)
{
	SPCTL = 0x53;                               //使能SPI主机模式
    SPSTAT = 0xc0;                              //清中断标志
    IE2 = ESPI;                                 //使能SPI中断
    EA = 1;
}

void SPI_Isr() interrupt 9
{
    SPSTAT = 0xc0;                              //清中断标志
//    SS = 1;                                     //拉高从机的SS管脚
    busy_spi = 0;
	SPI_DATA = SPDAT ;
	//SPDAT = SPDAT ;
	                                            
}


void SPI_writeByte(unsigned char data__)
{
	unsigned short tt = 2000;
	busy_spi = 1;

	SPDAT = data__; 
	while(busy_spi)
	{
		tt --;
		if(!tt)
		{
			break;
		}
	}
}

//硬件SPI读数据有待测试
unsigned char SPI_readByte(void)
{
	busy_spi = 1;

	SPI_writeByte(0xFF);

	return SPI_DATA;
} 


/*********************************************************
* 函数名：void SPI_writeString( unsigned char *pData,   数据指针
								unsigned char length,	数据长度	
							    unsigned char PORT)		片选信号的引脚
* 功能：
* 参数：
* 作者：zhao1peng
* note：
*
**********************************************************/

void SPI_writeString(unsigned char *pData,unsigned char length)//
{
	unsigned char dataLength;

	dataLength = length;
	 
	while(dataLength--)
	{
		SPI_writeByte(*pData ++);
	}
	LED1 = !LED1;
}

void SPI_readString(unsigned char *pData,unsigned char length)
{
	unsigned char dataLength;
	dataLength = length;

	while(dataLength--)
	{
		*pData = SPI_readByte();
		pData ++;
	}
	LED1 = !LED1;

}





