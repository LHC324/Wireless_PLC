#include "Control.h"

extern uint16_t getCrc16(const uint8_t *ptr, uint8_t length, uint16_t IniDat);
extern void Uart1SendStr(unsigned char *p, unsigned char length);
//*************************密码变量****************************

SYSTEM_PARAMETER PassWordI; //输入密码
//默认密码将在校验无误的情况下存到System_Parameter.PSWNext.PassWordbuff

SYSTEM_PARAMETER PassWordChange1; //修改密码1
SYSTEM_PARAMETER PassWordChange2; //修改密码2

// PASSWORDSTRUCT PassWordChange1 = {0, false, false, {0}}; //修改密码1
// PASSWORDSTRUCT PassWordChange2 = {0, false, false, {0}}; //修改密码2
//*************************************************************

/*****************波特率变量*********************************/
BAUDSTRUCT Baudlist[] =
{
		{0, BRT_1T(BAUD_2400),   " 2400 "},
		{1, BRT_1T(BAUD_4800),   " 4800 "},
		{2, BRT_1T(BAUD_9600),   " 9600 "},
		{3, BRT_1T(BAUD_14400),  "14400 "},
		{4, BRT_1T(BAUD_19200),  "19200 "},
		{5, BRT_1T(BAUD_38400),  "38400 "},
		{6, BRT_1T(BAUD_56000),  "56000 "},
		{7, BRT_1T(BAUD_57600),  "57600 "},
		{8, BRT_1T(BAUD_115200), "115200"},
		{9, BRT_1T(BAUD_921600), "921600"},
};

uint8_t G_BaudList_Size = (sizeof(Baudlist) / sizeof(BAUDSTRUCT));
/************************************************************/

/*热点设置*/
APSTRUCT Aplist[] =
{
	{"打开", Wifi_Open_Ap},
	{"关闭", Wifi_Close_Ap}
};
uint8_t G_Aplist_Size = (sizeof(Aplist) / sizeof(APSTRUCT));

/*工作模式设置*/
MODESTRUCT Modelist[] =
{
	{"主机", Mode_Master},
	{"从机", Mode_Slave}
};
uint8_t G_Modelist_Size = (sizeof(Modelist) / sizeof(MODESTRUCT));

OBJCTSTRUCT Objlist[] = 
{
	{"Ethernet"},
	{"WIFI/4G"},
	{"RS485"}
};
uint8_t G_Objlist_Size = (sizeof(Objlist) / sizeof(OBJCTSTRUCT));

void ControlInit(void)
{
	/*缺省控件类型*/
	System_Parameter.PSWNext.First_Input_Flag = false;
	BaudInit();		 //串口3波特率初始化
	PowerInit();	 //开关初始化
	CommunicaInit(); //通信初始化
}

void CommunicaInit(void)
{ 	/*默认为本地连接方式*/
	/*初始连接状态*/
//	LTEenable(CommunciaType);
    Wifi_Enable(System_Parameter.CommunicationType);
}

void PowerInit(void)
{	/*PLC初始运行状态*/
	RUNKEY = System_Parameter.PlcState; //默认为STOP
}

void BaudInit(void)
{	/*默认波特率为9600*/
	/*波特率预选索引,操作的是波特率选项界面*/
	SET_BRT1(1, Baudlist[System_Parameter.BaudIndex[0]].BaudValue);
	SET_BRT1(2, Baudlist[System_Parameter.BaudIndex[1]].BaudValue);
	SET_BRT1(3, Baudlist[System_Parameter.BaudIndex[2]].BaudValue);
	SET_BRT1(4, Baudlist[System_Parameter.BaudIndex[3]].BaudValue);
}

/**
 * @brief	密码输入
 * @details	
 * @param	operation：操作类型
 * @param	Password：密码对象
 * @retval	当前索引下密码值
 */
uint8_t PassWordInput(uint8_t operation, SYSTEM_PARAMETER *Password) //密码输入
{
	/*解决初始时密码错乱*/
	if (Password->PSWNext.PassWordbuff[Password->PSWNext.Index] == 0xFF)
	{
		Password->PSWNext.PassWordbuff[Password->PSWNext.Index] = 0;
	}
	if (operation == ADD)
	{
		Password->PSWNext.PassWordbuff[Password->PSWNext.Index]++;
		Password->PSWNext.PassWordbuff[Password->PSWNext.Index] %= 10;
	}
	else
	{
		if (Password->PSWNext.PassWordbuff[Password->PSWNext.Index] == 0)
		{
			Password->PSWNext.PassWordbuff[Password->PSWNext.Index] = 10;
		}
		Password->PSWNext.PassWordbuff[Password->PSWNext.Index]--;
		Password->PSWNext.PassWordbuff[Password->PSWNext.Index] %= 10;
	}
	return Password->PSWNext.PassWordbuff[Password->PSWNext.Index]; //显示
}


/**
 * @brief	输入密码核对
 * @details	
 * @param	PasswordA：密码A
 * @param	PasswordB：密码B
 * @retval	true/false
 */
uint8_t PassWordjudge(SYSTEM_PARAMETER PasswordA, SYSTEM_PARAMETER PasswordB) //密码判断
{
	/*密码正确*/
	if (!strncmp(PasswordA.PSWNext.PassWordbuff, PasswordB.PSWNext.PassWordbuff, PASSWORDBITS))
		return true;
	else
		return false;
}

void PassWordDelete(SYSTEM_PARAMETER *Password)
{
	memset(Password->PSWNext.PassWordbuff, 0xFF, sizeof(Password->PSWNext.PassWordbuff));
	Password->PSWNext.Index = 0;
}

void InputOffect(SYSTEM_PARAMETER *Password)
{
	Password->PSWNext.Index++;
	if(Password->PSWNext.Index == PASSWORDBITS)
	{	/*密码输入为有效位数*/
		System_Parameter.PSWNext.Bit_Efficient_Flag = true;
	}
	
	Password->PSWNext.Index %= PASSWORDBITS;
}

//void PassWordChange(void)		 //密码修改
//{
//
//}

/*屏保显示页面*/
void ScreensaverUiShow(void)
{
	clear_screen();
	/*显示南方电网Logo*/
	GUI_Lattice(0, 0, 192, 64, START_LOGO);
}

void PassWordInputUIShow(void) //输入密码界面进入显示
{
	clear_screen();
	GUI_Lattice(0, 8, 81, 50, Logo); //Logo显示
	GUI_String(100, 15, "请输入密码", CH_12_12);
}

void PassWordChangeUIShow(void) //修改密码界面进入显示
{
	// PassWordDelete(&PassWordChange1); //清0数据
	// PassWordDelete(&PassWordChange2);
	uint8_t i;
    uint8_t temp[2];

	clear_screen();
	/*如果是输入第二次密码*/
	if (System_Parameter.PSWNext.First_Input_Flag)
	{
		/*保留原来的密码*/
		for (i = 0; i < PASSWORDBITS; i++) //显示4位密码
        {
            GUI_String(i * 20 + 100, 18, myitoa(PassWordChange1.PSWNext.PassWordbuff[i], temp, 10), EN_5_8);
        }
    	GUI_Lattice(175, 16, 16, 12, dot);
	}

	GUI_String(15, 15, "请输入新密码", CH_12_12);
	GUI_String(15, 35, "请确认新密码", CH_12_12);
}

void PlcPowerUIshow(void)
{
	clear_screen();

	GUI_String(15, 24, "STOP", EN_5_8);
	GUI_String(150, 24, "RUN", EN_5_8);

	if (System_Parameter.PlcState == RUN)
	{
		GUI_Lattice(45, 0, 100, 56, PlcRun);
	}
	else
	{
		GUI_Lattice(45, 0, 100, 56, PlcStop);
	}
}

void CommunicaUIshow(void)
{
	clear_screen();
	GUI_Lattice(10, System_Parameter.CommunicationType * 30 + 11, 16, 12, finger);

	GUI_String(30, 10, "关闭无线模块", CH_12_12);
	GUI_String(30, 40, "打开无线模块", CH_12_12);
}

// void BaudSettingUIshow(void)
// {
// 	// clear_screen();
// 	// GUI_String(10, 10, "本地串口", CH_12_12);
// 	// GUI_String(105, 13, Baudlist[System_Parameter.BaudIndex].pstring, EN_5_8);
// 	// GUI_Lattice(149, 13, 5, 8, IconRight);
// 	// GUI_Lattice(97, 13, 5, 8, Iconleft);

// 	// GUI_String(10, 40, "远程串口", CH_12_12);
// 	// GUI_String(80, 43, "115200(readonly)", EN_5_8);
// }

void BaudSettingUI1show(void)
{
	clear_screen();
	GUI_String(10, 29, "以太网", CH_12_12);
	GUI_String(105, 31, Baudlist[System_Parameter.BaudIndex[0]].pstring, EN_5_8);
	GUI_Lattice(149, 31, 5, 8, IconRight);
	GUI_Lattice(97, 31, 5, 8, Iconleft);
}

void BaudSettingUI2show(void)
{
	clear_screen();
	GUI_String(10, 29, "无线网", CH_12_12);
	GUI_String(105, 31, Baudlist[System_Parameter.BaudIndex[1]].pstring, EN_5_8);
	GUI_Lattice(149, 31, 5, 8, IconRight);
	GUI_Lattice(97, 31, 5, 8, Iconleft);
}

void BaudSettingUI3show(void)
{
	clear_screen();
	GUI_String(10, 29, "扩展网", CH_12_12);
	GUI_String(105, 31, Baudlist[System_Parameter.BaudIndex[2]].pstring, EN_5_8);
	GUI_Lattice(149, 31, 5, 8, IconRight);
	GUI_Lattice(97, 31, 5, 8, Iconleft);
}

void BaudSettingUI4show(void)
{
	clear_screen();
	GUI_String(10, 29, "内部网", CH_12_12);
	GUI_String(105, 31, Baudlist[System_Parameter.BaudIndex[3]].pstring, EN_5_8);
	GUI_Lattice(149, 31, 5, 8, IconRight);
	GUI_Lattice(97, 31, 5, 8, Iconleft);
}

void ReloadSettingUIshow(void)
{
	clear_screen();
	GUI_String(48, 20, "是否恢复出厂设置", CH_12_12);
	GUI_String(10, 48, "是", CH_12_12);
	GUI_String(172, 48, "否", CH_12_12);
}

void HotspotSettingUIshow(void)
{
	clear_screen();
	GUI_String(10,10,"热点", CH_12_12);
	GUI_String(115,10,Aplist[System_Parameter.Apstate].pstring,CH_12_12);
	GUI_Lattice(149,13,5,8,IconRight);
	GUI_Lattice(97,13,5,8,Iconleft);
			
	GUI_String(10,43,"AP ID",EN_5_8);
	GUI_String(97,43,AP_ID,EN_5_8);	
}

void WorkModeUIshow(void)
{
	clear_screen();
	GUI_String(10,10,"模式", CH_12_12);
	GUI_String(115,10,Modelist[System_Parameter.WorkMode].pstring,CH_12_12);
	GUI_Lattice(149,13,5,8,IconRight);
	GUI_Lattice(97,13,5,8,Iconleft);
			
	GUI_String(10,43,"object",EN_5_8);
	GUI_String(97,43,Objlist[System_Parameter.CurrentSlave].pstring,EN_5_8);	
}

void Mode_Slave(void)
{
	System_Parameter.WorkMode = SLAVE;
}

void Mode_Master(void)
{
	System_Parameter.WorkMode = MASTER;
	/*PLC工作在主站时，默认从站为RS485*/
	System_Parameter.CurrentSlave = RS485_ID;
}

/**
 * @brief	系统数据存储到EEPROM
 * @details	存储数据前为了防止中断打断数据的存储，因该关闭全局中断
 * @param	None
 * @retval	None
 */
void ControlSave(void)
{
	/*计算出当前有效数据的校验码并存储*/
	System_Parameter.CRC16 = getCrc16(&System_Parameter.PSWNext.PassWordbuff[0], (sizeof(System_Parameter) - (sizeof(PASSWORDSTRUCT) - 4U) - 2U), 0xffff);
	
	CLOSE_GLOBAL_OUTAGE();
	/*每次写之前必须进行擦除操作：擦除每次按照512B进行(0x00-0x0200)*/
	IapErase(START_SAVEADDRESS); 
	IapWrite_Buff(START_SAVEADDRESS, &System_Parameter.PSWNext.PassWordbuff[0], (sizeof(System_Parameter) - (sizeof(PASSWORDSTRUCT) - 4U)));
	OPEN_GLOBAL_OUTAGE();
}