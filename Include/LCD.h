#ifndef __LCD_H_
#define __LCD_H_

#include "config.h"
#include "systemTimer.h"
#include "Chinese_code.h"

/*液晶屏尺寸*/
#define LCD_WIDTH	192U
#define LCD_HIGH 	64U

#define BIT_MASK_LEN(len)      ((1<<(len))-1)
#define BIT_RNG(s, e)  		   (BIT_MASK_LEN((e)-(s) + 1) << (s))
#define xor(d,n)               ((d)^BIT_RNG(0,n-1))       //一个字节的n位取反,是n位,不是第n位

//#define BIT_MASK(s,e)  (BIT_MASK_LEN(8 - s)^(BIT_MASK_LEN(7 -e)))	  //从左往右

#define BIT_MASK(s,e)          (BIT_MASK_LEN(s)^(BIT_MASK_LEN(e + 1)))		  //从右往左
#define GET_BITS_SE(d,s,e)     ((d) & BIT_MASK(s,e))  //一个字节取n位值
#define MULTIPLE_8(d)          (((d)&7) ? (((d)&(~7)) + 8):d)  //求一个字节是否是8的倍数，不是的话就清0低三位加8

/*LDC192*64液晶屏引脚定义*/
#define  LCD_SCK     	P33
#define  LCD_SDA		P32
#define  LCD_CS			P34
#define  LCD_RST   	 	P35
#define  LCD_RS	   		P36
#define  LCD_BAK		P37

/**
 * @brief	自定义字符类型
 * @details	
 * @param	data1:1Byte CMD
 * @retval	None
 */
typedef enum {
        CH_12_12,       //中文12*12点阵
        EN_5_8,         //英文 5*7 点阵
        EN_6_12         //英文 6*12 点阵
}FONT;	   

typedef struct 
{
    uint8_t F_Bytes;     //所占字节
    uint8_t F_Width;     //字符宽度
    uint8_t F_High;      //字符高度
    uint8_t F_Num;       //字符个数
    uint8_t F_Offect;    //文字间偏移量
    uint8_t *pArray;     //字符指针
}FRONT_PARM;


/**
 * @brief	液晶发送指令
 * @details	
 * @param	data1:1Byte CMD
 * @retval	None
 */
extern void transfer_command(uint8_t data1);

/**
 * @brief	液晶发送数据
 * @details	
 * @param	data1:1Byte data
 * @retval	None
 */
extern void transfer_data(uint8_t data1);

/**
 * @brief	液晶清屏
 * @details	
 * @param	None
 * @retval	None
 */
extern void clear_screen();

/**
 * @brief	设置液晶DDRAM地址
 * @details	
 * @param	page:页，column:列
 * @retval	None
 */
static void lcd_address(uint8_t page, uint8_t column);

/**
 * @brief	液晶初始化
 * @details	
 * @param	None
 * @retval	None
 */
extern void initial_lcd(void);

/**
 * @brief	根据字库类型获取对应参数
 * @details	
 * @param	font：字体类型
 * @retval	None
 */
static uint8_t GetFrontParm(FONT font);

/**
 * @brief	获取文字的字库索引
 * @details	
 * @param	ZoneCode：字符的区位码
 * @retval	None
 */
static uint16_t GetCHIndex(uint16_t ZoneCode);

/**
 * @brief	写自定义字符串
 * @details	
 * @param	x:起始横坐标, y:起始纵坐标, *pString:字符串指针, front:字体类型
 * @retval	None
 */
extern void GUI_String(uint8_t x, uint8_t y, uint8_t *pString, FONT font);

/**
 * @brief	液晶写自定义点阵
 * @details	
 * @param	x:起始横坐标, y:起始纵坐标, width:宽度, high:高度, *plattice:指向目标点阵的指针
 * @retval	None
 */
extern void GUI_Lattice(uint8_t x, uint8_t y, uint8_t Width, uint8_t High, uint8_t* plattice);

#endif

