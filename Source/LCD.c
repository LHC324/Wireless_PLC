#include "LCD.h"
#include "usart.h"
#include "pFunc.h"
#include <STC8.h>
#include "systemTimer.h"
#include "Chinese_code.h"

FRONT_PARM frontCurrent;

/*******************************************************************/
//				           液晶发送指令
/*******************************************************************/

void transfer_command(int data1)
{
    uint8_t i;
    LCD_CS = 0;
    LCD_RS = 0;

    for(i = 0; i < 8; i++)
    {
        LCD_SCK = 0;

        if(data1 & 0x80)
            LCD_SDA = 1;
        else
            LCD_SDA = 0;

        LCD_SCK = 1;
        data1 = data1 <<= 1;
    }

    LCD_CS = 1;
}


/*******************************************************************/
//				            液晶发送数据
/*******************************************************************/
void transfer_data(unsigned char data1)
{
    uint8_t i;
    LCD_CS = 0;
    LCD_RS = 1;

    for(i = 0; i < 8; i++)
    {
        LCD_SCK = 0;

        if(data1 & 0x80)
        {
            LCD_SDA = 1;
        }
        else
        {
            LCD_SDA = 0;
        }

        LCD_SCK = 1;

        data1 = data1 <<= 1;
    }

    LCD_CS = 1;
}

//void GUI_Point(unsigned char x, unsigned char y)
//{
//    uint8_t y_Dy, y_by;

//    y_Dy = y / 8;	//计算y坐标在哪一行
//    y_by = y & (~8);	//计算y坐标在哪一位

//}


/*******************************************************************/
//				            液晶清屏
/*******************************************************************/
void clear_screen()
{
    unsigned char i, j;

    for(i = 0; i < 8; i++)
    {
        transfer_command(0xB0 + i);	 //列地址为0xB0到0xB7

        for(j = 0; j < 192; j++)
        {
            transfer_data(0x00);
        }
    }
}


/*******************************************************************/
//				         设置液晶DDRAM地址
/*******************************************************************/

void lcd_address(unsigned char page, unsigned char column)
{
//	column = column - 1; //我们平常所说的第 1 列，在 LCD 驱动 IC 里是第 0 列。
//	page = page - 1;

    if(page < 2) 					    //第0列对应B6，第1列对应B7
    {
        transfer_command(0xB6 + page);	 //设置页地址。每页是 8 行。一个画面的 64 行被分成 8 个页。
    }
    else
    {
        transfer_command(0xAE + page);
    }

    transfer_command(((column >> 4) & 0x0f) + 0x10); //设置列地址的高 4 位
    transfer_command(column & 0x0f); //设置列地址的低 4 位
}

/*******************************************************************/
//				             液晶初始化
/*******************************************************************/
void initial_lcd()
{
    LCD_RST = 0; 			//低电平复位
    Delay_ms(100);
    LCD_RST = 1; 			//复位完毕

    Delay_ms(50);
    transfer_command(0xe2); //软复位
    Delay_ms(50);
    transfer_command(0x2f); //打开内部升压
    Delay_ms(20);
    transfer_command(0xa0); //
    Delay_ms(20);
    //transfer_command(0xff); //微调对比度
    Delay_ms(20);
    transfer_command(0x70); //微调对比度的值，可设置范围 0x00～0xFF
    //****************************
    Delay_ms(20);
    transfer_command(0x81); //微调对比度
    Delay_ms(20);
    transfer_command(0x70); //微调对比度的值，可设置范围 0x00～0xFF
    //******************************
    Delay_ms(20);
    transfer_command(0xeb); //1/9 偏压比（bias）
    Delay_ms(20);
    transfer_command(0xc4); //行列扫描顺序：从上到下
    Delay_ms(20);
    transfer_command(0xaf); //开显示

    LCD_BAK = 0;      //背光开启

    clear_screen();
}


/*******************************************************************/
//				     根据字库类型获取对应参数
/*******************************************************************/
uint8_t GetFrontParm(FONT font)   //获取字体参数
{
    switch(font)
    {
        case CH_12_12 :
        {
            frontCurrent.F_Bytes = 24;
            frontCurrent.F_High = 16;
            frontCurrent.F_Width = 12;
            frontCurrent.pArray = Chinese_code_12x12;  //中文字库指针
            frontCurrent.F_Offect = 12;			 //点阵之间的偏移量
            break;
        }

        case EN_5_8 :
        {
            frontCurrent.F_Bytes = 5;
            frontCurrent.F_High = 8;
            frontCurrent.F_Width = 5;
            frontCurrent.F_Offect = 7;
            frontCurrent.pArray = *Ascii_table_5x8;	  //英文字库指针
            break;
        }

//				case EN_6_12 :
//				{
//						frontCurrent.F_Bytes = 16;
//            frontCurrent.F_High = 16;
//            frontCurrent.F_Width = 8;
//            frontCurrent.F_Offect = 8;
//            frontCurrent.pArray = Ascii_table_6x12;	  //英文字库指针
//				}
        default:
            return 0;
    }

    return 1;
}

/*******************************************************************/
//				         获取文字的字库索引
/*******************************************************************/

uint16_t GetCHIndex(uint16_t ZoneCode)
{
    uint16_t i = 0;
    uint16_t CHCode;

    for(i = 0; i < MAX_WORD_LIBRARY; i++)
    {
        CHCode = (ChineseTable[i][0] << 8) | (ChineseTable[i][1]);

        if(CHCode == ZoneCode)
        {
            break;         // 返回汉字在gbkCodeTable[][]表中的索引位置
        }
    }

    return i;
}

/*******************************************************************/
//				          写自定义字符串
/*******************************************************************/
void GUI_String(unsigned char x, unsigned char y, unsigned char *pString, FONT font)
{
    //FRONT_PARM front_parm;                     // 字符参数
    unsigned short ChIndex;                          // 要显示的字符在gbkCodeTable[][2]中的序号
    unsigned char  Offset;                           // 点阵内偏移量

    uint16_t ZoneCode;                         // 字符的区位码
    GetFrontParm(font);    //获取不同点阵对应参数

    Offset = 0;

    do
    {
        if(*(pString + Offset) < 0x80)          //英文字符或数字显示
        {
            ChIndex = *(pString + Offset) - ' '; //获取英文或字符的索引
            //Uart1Send(ChIndex);
            GUI_Lattice(x, y, 5, 8, frontCurrent.pArray + ChIndex * 5); //液晶显示
            x += frontCurrent.F_Offect;
            Offset ++;
        }
        else                                    //汉字显示
        {

            ZoneCode = *(pString + Offset) << 8;  //0x80为文字起始
            ZoneCode = ZoneCode | *(pString + Offset + 1);  //不是区位码,是国标码

            ChIndex = GetCHIndex(ZoneCode);
//			Uart1Send(frontCurrent.F_High);
//			Uart1Send(frontCurrent.F_Bytes);
//			Uart1Send(frontCurrent.F_Width);
            GUI_Lattice(x, y, 12, 16, frontCurrent.pArray + ChIndex * 24); //液晶显示
            x += frontCurrent.F_Offect;
            Offset += 2;
        }

    }
    while(*(pString + Offset) != '\0');
}


/*******************************************************************/
//				          液晶写自定义点阵
/*******************************************************************/
void GUI_Lattice(unsigned char x, unsigned char y, unsigned char Width, unsigned char High, unsigned char* plattice) //x:起始坐标x    y:起始坐标y
{
    uint8_t y_Dy, y_by, y1_Dy, y1_by, y_Bytes;
    uint8_t i, j;
    uint8_t tempH, tempL;

    High = MULTIPLE_8(High);   //高度不为8的倍数时，要补齐，不然会出错，此句很重要

    y1_Dy = (y + High) / 8;	 	//求出y终点的所在列
    y1_by = (y + High) % 8;

    y_Dy = y / 8;			 //求出y起点的所在列
    y_by = y % 8;

    y_Bytes = y1_Dy - y_Dy + 1;

    for(i = 0; i < y_Bytes; i++)
    {
        if(y1_Dy > y_Dy)
        {
            for(j = 0; j < Width; j++)
            {
                if(i == 0)  //第一行
                {
                    lcd_address(y_Dy, x + j);
                    transfer_data(*(plattice + j ) << y_by);

                }
                else if(i == y_Bytes - 1)  //最后一行
                {
                    lcd_address(y1_Dy, x + j);
                    transfer_data(*(plattice + Width * (i - 1) + j) >> (8 - y1_by));	//16点阵 offect16
                }
                else
                {
                    tempH = (*(plattice + j + Width * (i - 1)) >> (8 - y_by));
                    tempL = (*(plattice + j + Width * i) << y_by);

                    lcd_address(y_Dy + i, x + j);
                    transfer_data(tempH | tempL);
                }
            }
        }
        else		   //只有一行的点阵
        {
            lcd_address(y_Dy, x + j); //设置第一字节y首地址
            transfer_data(GET_BITS_SE(*(plattice + j), y_by, y1_by));		 //通过
        }
    }
}

