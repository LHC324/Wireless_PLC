#include "Key.h"
#include "systemTimer.h"
#include "usart.h"

KEY_STATE KeyStateCurrrent = KEY_NON;    //按键当前状态,初始化为无按键


//========================================================================
// 函数: KEY_e Key_Chick(void)
// 描述: 获取按键值
// 参数: NONE
// 返回: 返回按键值
// 备注: 调试通过
//========================================================================
KEY_e Key_Chick(void)
{
	static uint8_t KeyTemp;
	//获取按键值
	uint8_t KeyValue = (uint8_t)(KEY_UP_GPIO) | ((uint8_t)KEY_CANCEL_GPIO << 1) | ((uint8_t)KEY_DOWN_GPIO << 2) | ((uint8_t)KEY_ENTER_GPIO << 3) | ((uint8_t)KEY_MENU_GPIO << 4);
	switch(KeyStateCurrrent)
	{
		case KEY_NON:				//无按键
		{		
			if(KeyValue != NO_KEY)
			{
				KeyStateCurrrent = KEY_PRESS;	
			}
		}break;
		case KEY_PRESS:		//按键按下
		{
			Delay_ms(10);
			if(KeyValue != NO_KEY)
			{
				KeyTemp = KeyValue;    //保存key的值
				KeyStateCurrrent = KEY_HOLD;
			}
		}break;
		case KEY_HOLD:		//按键保持
		{
			if(KeyValue == NO_KEY)
			{
				KeyStateCurrrent = KEY_UPLIFT;
				return KeyTemp;
			}
		}break;
		case KEY_UPLIFT:  //按键抬起
		{
			KeyTemp = NO_KEY;  //抬起后使keytemp变为无按键
			KeyStateCurrrent = KEY_NON;
			Delay_ms(10);
		}break;		
	}
	return NO_KEY;
}


