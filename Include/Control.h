#ifndef __CONTROL_H_
#define __CONTROL_H_

#include "config.h"
#include "KEY.h"
#include "LCD.h"
#include "Chinese_code.h"
#include "eeprom.h"
#include "usart.h"
#include "pFunc.h"
//#include "LTE.h"
#include "systemTimer.h"
#include "wifi.h"

#define T1L TL1
#define T1H TH1

/*对应串口可变波特率设置*/
#define SET_BRT(SN,LOAD_VALUE) ((SN < 3U) ? (TL##SN = LOAD_VALUE, TH##SN = (LOAD_VALUE >> 8U)) : \
										    (T##SN##L = LOAD_VALUE, T##SN##H = (LOAD_VALUE >> 8U)))

// #define SET_BRT0(SN,LOAD_VALUE) (TL##SN = LOAD_VALUE, TH##SN = (LOAD_VALUE >> 8U))
#define SET_BRT1(SN,LOAD_VALUE) (T##SN##L = LOAD_VALUE, T##SN##H = (LOAD_VALUE >> 8U))

typedef enum //控件
{
	CONTROL_TIME = 0x00,
	CONTROL_PLCPOWER,		 //PLC开关控件
	CONTROL_BAUDSETTING,	 //波特率设置控件
	CONTROL_COMMUNICA,		 //通讯控件
	CONTROL_WORKMODE,			 //工作模式
	CONTROL_PASSWORD,		 //密码输入控件
	CONTROL_PASSWORD_CHANGE, //密码修改控件
	CONTROL_RELOAD,			 //恢复出厂设置
	CONTROL_SCREENSAVE,		 //屏保控件
	CONTROL_BAUD1,			//波特率1控件
	CONTROL_BAUD2,			//波特率2控件
	CONTROL_BAUD3,			//波特率3控件
	CONTROL_BAUD4,			//波特率4控件
	CONTROL_HOTSPOT,		//热点控件
	CONTROL_NO,
} CONTROL_TYPE;

extern CONTROL_TYPE ControlType; //缺省控件类型

void ControlInit(void);
extern void ControlSave(void); //控件参数存盘，统一存盘,有点乱

//***************************密码控件*********************************//

#define ADD 1 //加
#define SUB 2 //减

extern SYSTEM_PARAMETER PassWordI; //输入密码

extern SYSTEM_PARAMETER PassWordChange1; //修改密码1
extern SYSTEM_PARAMETER PassWordChange2; //修改密码2
/*使用空闲的内存空间作为临时变量*/
#define SYS_TEMP_PARA PassWordChange1

extern unsigned char PassWordFirstChangeFlag;

unsigned char PassWordInput(unsigned char operation, SYSTEM_PARAMETER *Password);	 //密码输入
void InputOffect(SYSTEM_PARAMETER *Password);										 //下一位地址
unsigned char PassWordjudge(SYSTEM_PARAMETER PasswordA, SYSTEM_PARAMETER PasswordB); //密码判断
void PassWordChange(void);															 //密码修改
void PassWordCheak(void);															 //密码查询
// void PassWordinit(void);															 //密码初始化
void PassWordDelete(SYSTEM_PARAMETER *Password);									 //密码归0
void PassWordInputUIShow(void);														 //输入密码界面进入显示
void PassWordChangeUIShow(void);													 //修改密码界面进入显示
void WorkModeUIshow(void);
/*屏保显示页面*/
void ScreensaverUiShow(void);
//********************************************************************//

//****************************开关控件*********************************//

#define RUN 0  //启动
#define STOP 1 //待机

#define RUNKEY P07

void PlcPowerUIshow(void);
void PowerInit(void);
//*********************************************************************//

//****************************连接控件*********************************//
#define LOCAL 0
#define GLOBAL 1

void CommunicaUIshow(void);
void CommunicaInit(void);
//*********************************************************************

//****************************波特率设置控件***************************//
typedef struct
{
	unsigned char Index;
	unsigned short BaudValue;
	unsigned char *pstring;
} BAUDSTRUCT; //波特率变量

extern BAUDSTRUCT Baudlist[];	//波特率列表
extern uint8_t G_BaudList_Size;

/*热点状态切换*/
typedef struct Control
{
	unsigned char *pstring;
	void (*fun)(void);
}APSTRUCT;
extern APSTRUCT Aplist[];
extern uint8_t G_Aplist_Size;

typedef struct 
{
	unsigned char *pstring;
	void (*fun)(void);
}MODESTRUCT;
extern MODESTRUCT Modelist[];
extern uint8_t G_Modelist_Size;

typedef struct 
{
	unsigned char *pstring;
}OBJCTSTRUCT;
extern OBJCTSTRUCT Objlist[];
extern uint8_t G_Objlist_Size;

// void BaudSettingUIshow(void); //波特率设置界面显示
void BaudSettingUI1show(void);
void BaudSettingUI2show(void);
void BaudSettingUI3show(void);
void BaudSettingUI4show(void);
void BaudInit(void);
void HotspotSettingUIshow(void);
void Mode_Slave(void);
void Mode_Master(void);
//*********************************************************************//

//****************************恢复出厂设置****************************//
void ReloadSettingUIshow(void);
#endif