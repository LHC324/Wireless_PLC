#ifndef __LCD_H_
#define __LCD_H_

#include "config.h"


#define BIT_MASK_LEN(len)      ((1<<(len))-1)
#define BIT_RNG(s, e)  		   (BIT_MASK_LEN((e)-(s) + 1) << (s))
#define xor(d,n)               ((d)^BIT_RNG(0,n-1))       //一个字节的n位取反,是n位,不是第n位

//#define BIT_MASK(s,e)  (BIT_MASK_LEN(8 - s)^(BIT_MASK_LEN(7 -e)))	  //从左往右

#define BIT_MASK(s,e)          (BIT_MASK_LEN(s)^(BIT_MASK_LEN(e + 1)))		  //从右往左
#define GET_BITS_SE(d,s,e)     ((d) & BIT_MASK(s,e))  //一个字节取n位值
#define MULTIPLE_8(d)          (((d)&7) ? (((d)&(~7)) + 8):d)  //求一个字节是否是8的倍数，不是的话就清0低三位加8


#define  LCD_SCK     	P33
#define  LCD_SDA		P32
#define  LCD_CS			P34
#define  LCD_RST   	 	P35
#define  LCD_RS	   		P36
#define  LCD_BAK		P37

//******************************************************************************
//                             自定义字符类型
//******************************************************************************

typedef enum {
        CH_12_12,       //中文12*12点阵
        EN_5_8,         //英文 5*7 点阵
        EN_6_12         //英文 6*12 点阵
}FONT;	   

typedef struct 
{
    unsigned char F_Bytes;     //所占字节
    unsigned char F_Width;     //字符宽度
    unsigned char F_High;      //字符高度
    unsigned char F_Num;       //字符个数
    unsigned char F_Offect;    //文字间偏移量
    unsigned char *pArray;     //字符指针
}FRONT_PARM;


uint8_t GetFrontParm(FONT font);      //根据字库类型获取对应参数
unsigned short GetCHIndex(unsigned short ZoneCode); //获取中文字库索引
void GUI_String(unsigned char x,unsigned char y,unsigned char *pString,FONT font);  //液晶写字符串
void GUI_Lattice(unsigned char x,unsigned char y,unsigned char Width,unsigned char High,unsigned char* plattice); //液晶写自定义字符

void lcd_address(unsigned char page,unsigned char column);  //设置地址
void transfer_command(int data1);	   			//发送指令
void transfer_data(unsigned char data1);		//发送数据
void clear_screen();						    //清屏
void initial_lcd();								//液晶初始化
void DebugShow();						//测试

#endif

