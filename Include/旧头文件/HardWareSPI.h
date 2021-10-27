#ifndef __HARDWARESPI_H
#define __HARDWARESPI_H


void SPI_MasterInit(void);
void SPI_writeByte(unsigned char data__);//SPI的写一个字节的函数
unsigned char SPI_readByte(void); //SPI的读一个字节的函数
void SPI_writeString(unsigned char *pData_,unsigned char length_);//
void SPI_readString(unsigned char *pData,unsigned char length);//


//以下是SPI mosi miso sclk 引脚的切换宏定义
//对于片选信号而言 可根据实际需要来重新宏定义引脚

#define SPI_P13_P14_P15       P_SW1 = 0x00   //SS  /P1.2, 	MOSI/P1.3, MISO/P1.4, SCLK/P1.5
#define SPI_P23_P24_P25 	  P_SW1 = 0x04   //SS_2/P2.2, 	MOSI_2/P2.3, MISO_2/P2.4, SCLK_2/P2.5
#define SPI_P75_P76_P77 	  P_SW1 = 0x08   //SS_3/P7.4, 	MOSI_3/P7.5, MISO_3/P7.6, SCLK_3/P7.7
#define SPI_P34_P33_P32 	  P_SW1 = 0x0c   //SS_4/P3.5, 	MOSI_4/P3.4, MISO_4/P3.3, SCLK_4/P3.2


#endif