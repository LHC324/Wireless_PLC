#ifndef __KEY_H
#define __KEY_H

#include "config.h"
#include "systemTimer.h"
#include "usart.h"

//----------------------------------1行5列--------------------------------//
/*按键引脚*/
#define KEY_MENU_GPIO 		P22	//菜单按钮4
#define KEY_DOWN_GPIO 		P23	//向下按键2
#define KEY_UP_GPIO 		P24 //向上按键0
#define KEY_ENTER_GPIO 		P25	//确认按键3
#define KEY_CANCEL_GPIO 	P26 //返回按键1

#define KEY_PRESS_DOWN  	0 //按键按下时的电平
#define KEY_PRESS_UP    	1 //按键抬起时的电平

/*枚举值对应数字值*/
typedef enum
{
	NO_KEY 		= 0x1F,
	KEY_CANCEL 	= 0x1D,
	KEY_ENTER 	= 0x17,
	KEY_UP 		= 0x1E,
	KEY_DOWN 	= 0x1B,
	KEY_MENU 	= 0x0F,
} KEY_e;

typedef enum
{
	KEY_PRESS,	//按键按下
	KEY_UPLIFT, //按键抬起
	KEY_HOLD,	//按键保持
	KEY_NON,	//无按键
} KEY_STATE;

					   
/**
 * @brief	获取按键值
 * @details	None
 * @param	None
 * @retval	返回按键值
 */
extern KEY_e Key_Chick(void);

#endif