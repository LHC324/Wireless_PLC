#ifndef __MENU_H
#define __MENU_H

#include "config.h"
#include "Control.h"
#include "LCD.h"
//#include "systemTimer.h"
#include "pFunc.h"
#include "eeprom.h"
#include "Chinese_code.h"
//#include "LTE.h"
#include "wifi.h"
#include "Key.h"
#include "Control.h"

#define REFRESH_AWAYS 1 //刷新标题
#define REFRESH_TTEM  2	//刷新子项
#define REFRESH_MENU  3	//刷新菜单项

typedef enum
{
	MENU_STATE,	   //菜单界面
	MAIN_STATE,	   //主界面
	CONTROL_STATE, //控件界面
	BAUD_STATE	   //波特率控件
} SHOW_STATE;

typedef struct
{
	KEY_e Keycodel;	   //按键码
	SHOW_STATE Stage;  //对应状态
	void (*fun)(void); //对应函数
} KEY_MAP;

typedef void (*pshow)(void);
typedef struct
{
	unsigned char *pString;	  //对应字符串
	CONTROL_TYPE ControlType; //对应控件类型
	pshow ControlShow;		  //对应控件显示界面
} OPTION;

#define MAIN_MENU  0U
#define SEC0_MENU  1U

/*每一级菜单最多显示的列表项*/
#define SHOWSIZE  3U
typedef struct 
{
	/*当前UI控件*/
	SHOW_STATE Ui_State;
	/*菜单选项索引*/
	uint8_t Option_Index;
	/*菜单箭头索引*/
	uint8_t Finger_Index;
	/*菜单显示索引数组 */
	uint8_t OptionIndex_buf[SHOWSIZE];
	/*当前选项卡*/
	OPTION *OptionNow;
}Menu_Show;
//*******************************************************************************

void KeyEvent(void);		   //按键事件
void RefreshMainDisp(void);	   //主界面刷新显示
void RefreshControlDisp(void); //控件界面刷新显示
void RefreshMenuDisp(void);	   //菜单界面刷新显示
/*菜单界面下二级菜单刷新显示*/
void RefreshBaudDisp(void);
void LcdShowInit(void);			   //界面显示初始化
void LcdShow(pshow InterfaceShow); //界面显示接口

//****************************菜单状态函数*********************************
void LcdDly(KEY_e key); //无操作返回
//*************************************************************************

void KeyMain_Enter(void);  //主界面状态--enter
void KeyMain_Up(void);	   //主界面状态--Up
void KeyMain_Menu(void);   //主界面状态--Menu
void KeyMain_Cancel(void); //主界面状态--Cancel
void KeyMain_Down(void);   //主界面状态--Down

void KeyMenu_Enter(void);  //菜单状态--Enter
void KeyMenu_Up(void);	   //菜单状态--Up
void KeyMenu_Menu(void);   //菜单状态--Menu
void KeyMenu_Cancel(void); //菜单状态--Cancel
void KeyMenu_Down(void);   //菜单状态--Down

void KeyControl_Enter(void);  //控件状态--Enter
void KeyControl_Up(void);	  //控件状态--Up
void KeyControl_Menu(void);	  //控件状态--Menu
void KeyControl_Cancel(void); //控件状态--Cancel
void KeyControl_Down(void);	  //控件状态--Down

/*波特率控件状态--up*/
void KeyBaud_Up(void);
/*波特率控件状态--Down*/
void KeyBaud_Down(void);
/*波特率控件状态--Enter*/
void KeyBaud_Enter(void);
/*波特率控件状态--Cancel*/
void KeyBaud_Cancel(void);
/*波特率控件状态--Menue*/
void KeyBaud_Menu(void);

/*波特率设置二级菜单*/
void Baud_Setting(void);
//********************************************************

#endif