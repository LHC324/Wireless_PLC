#include"HardWareSPI.h"
#include<STC8.h>

/*********************************************************************************
* ��������
* ���ܣ�
* ������
* ���ߣ�zhao1peng
* note��
* ��STC��Ƭ������ֻ��һ��SPIͨѶ�Ĵ������������л�SPIͨѶ������ �Ӷ�ʵ�ֶ�·��SPI
* 
*
*
*********************************************************************************/

 #define SPI1_CS P1^0
 bit busy_spi;

 #define LED1 P30
 #define LED2 P31
 #define uint8_t unsigned char

 unsigned char SPI_DATA;//����SPI�ض�����


/*********************************************************
* ��������void SPI_MasterIit(void)
* ���ܣ�  ��ʼ��SPI���ж���ʽ
* ������
* ���ߣ�zhao1peng
* note��
*Ӳ��SPI��ʱ��ѡ�������ʵ����������޸���Ӧ�Ĵ��� SPCTL �Ĳ���ֵ
* 
*
**********************************************************/


void SPI_MasterInit(void)
{
	SPCTL = 0x53;                               //ʹ��SPI����ģʽ
    SPSTAT = 0xc0;                              //���жϱ�־
    IE2 = ESPI;                                 //ʹ��SPI�ж�
    EA = 1;
}

void SPI_Isr() interrupt 9
{
    SPSTAT = 0xc0;                              //���жϱ�־
//    SS = 1;                                     //���ߴӻ���SS�ܽ�
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

//Ӳ��SPI�������д�����
unsigned char SPI_readByte(void)
{
	busy_spi = 1;

	SPI_writeByte(0xFF);

	return SPI_DATA;
} 


/*********************************************************
* ��������void SPI_writeString( unsigned char *pData,   ����ָ��
								unsigned char length,	���ݳ���	
							    unsigned char PORT)		Ƭѡ�źŵ�����
* ���ܣ�
* ������
* ���ߣ�zhao1peng
* note��
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





