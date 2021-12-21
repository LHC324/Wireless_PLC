#include "Control.h"

extern uint16_t getCrc16(const uint8_t *ptr, uint8_t length, uint16_t IniDat);
extern void Uart1SendStr(unsigned char *p, unsigned char length);
//*************************�������****************************

SYSTEM_PARAMETER PassWordI; //��������
//Ĭ�����뽫��У�����������´浽System_Parameter.PSWNext.PassWordbuff

SYSTEM_PARAMETER PassWordChange1; //�޸�����1
SYSTEM_PARAMETER PassWordChange2; //�޸�����2

// PASSWORDSTRUCT PassWordChange1 = {0, false, false, {0}}; //�޸�����1
// PASSWORDSTRUCT PassWordChange2 = {0, false, false, {0}}; //�޸�����2
//*************************************************************

/*****************�����ʱ���*********************************/
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

/*�ȵ�����*/
APSTRUCT Aplist[] =
{
	{"��", Wifi_Open_Ap},
	{"�ر�", Wifi_Close_Ap}
};
uint8_t G_Aplist_Size = (sizeof(Aplist) / sizeof(APSTRUCT));

/*����ģʽ����*/
MODESTRUCT Modelist[] =
{
	{"����", Mode_Master},
	{"�ӻ�", Mode_Slave}
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
	/*ȱʡ�ؼ�����*/
	System_Parameter.PSWNext.First_Input_Flag = false;
	BaudInit();		 //����3�����ʳ�ʼ��
	PowerInit();	 //���س�ʼ��
	CommunicaInit(); //ͨ�ų�ʼ��
}

void CommunicaInit(void)
{ 	/*Ĭ��Ϊ�������ӷ�ʽ*/
	/*��ʼ����״̬*/
//	LTEenable(CommunciaType);
    Wifi_Enable(System_Parameter.CommunicationType);
}

void PowerInit(void)
{	/*PLC��ʼ����״̬*/
	RUNKEY = System_Parameter.PlcState; //Ĭ��ΪSTOP
}

void BaudInit(void)
{	/*Ĭ�ϲ�����Ϊ9600*/
	/*������Ԥѡ����,�������ǲ�����ѡ�����*/
	SET_BRT1(1, Baudlist[System_Parameter.BaudIndex[0]].BaudValue);
	SET_BRT1(2, Baudlist[System_Parameter.BaudIndex[1]].BaudValue);
	SET_BRT1(3, Baudlist[System_Parameter.BaudIndex[2]].BaudValue);
	SET_BRT1(4, Baudlist[System_Parameter.BaudIndex[3]].BaudValue);
}

/**
 * @brief	��������
 * @details	
 * @param	operation����������
 * @param	Password���������
 * @retval	��ǰ����������ֵ
 */
uint8_t PassWordInput(uint8_t operation, SYSTEM_PARAMETER *Password) //��������
{
	/*�����ʼʱ�������*/
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
	return Password->PSWNext.PassWordbuff[Password->PSWNext.Index]; //��ʾ
}


/**
 * @brief	��������˶�
 * @details	
 * @param	PasswordA������A
 * @param	PasswordB������B
 * @retval	true/false
 */
uint8_t PassWordjudge(SYSTEM_PARAMETER PasswordA, SYSTEM_PARAMETER PasswordB) //�����ж�
{
	/*������ȷ*/
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
	{	/*��������Ϊ��Чλ��*/
		System_Parameter.PSWNext.Bit_Efficient_Flag = true;
	}
	
	Password->PSWNext.Index %= PASSWORDBITS;
}

//void PassWordChange(void)		 //�����޸�
//{
//
//}

/*������ʾҳ��*/
void ScreensaverUiShow(void)
{
	clear_screen();
	/*��ʾ�Ϸ�����Logo*/
	GUI_Lattice(0, 0, 192, 64, START_LOGO);
}

void PassWordInputUIShow(void) //����������������ʾ
{
	clear_screen();
	GUI_Lattice(0, 8, 81, 50, Logo); //Logo��ʾ
	GUI_String(100, 15, "����������", CH_12_12);
}

void PassWordChangeUIShow(void) //�޸�������������ʾ
{
	// PassWordDelete(&PassWordChange1); //��0����
	// PassWordDelete(&PassWordChange2);
	uint8_t i;
    uint8_t temp[2];

	clear_screen();
	/*���������ڶ�������*/
	if (System_Parameter.PSWNext.First_Input_Flag)
	{
		/*����ԭ��������*/
		for (i = 0; i < PASSWORDBITS; i++) //��ʾ4λ����
        {
            GUI_String(i * 20 + 100, 18, myitoa(PassWordChange1.PSWNext.PassWordbuff[i], temp, 10), EN_5_8);
        }
    	GUI_Lattice(175, 16, 16, 12, dot);
	}

	GUI_String(15, 15, "������������", CH_12_12);
	GUI_String(15, 35, "��ȷ��������", CH_12_12);
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

	GUI_String(30, 10, "�ر�����ģ��", CH_12_12);
	GUI_String(30, 40, "������ģ��", CH_12_12);
}

// void BaudSettingUIshow(void)
// {
// 	// clear_screen();
// 	// GUI_String(10, 10, "���ش���", CH_12_12);
// 	// GUI_String(105, 13, Baudlist[System_Parameter.BaudIndex].pstring, EN_5_8);
// 	// GUI_Lattice(149, 13, 5, 8, IconRight);
// 	// GUI_Lattice(97, 13, 5, 8, Iconleft);

// 	// GUI_String(10, 40, "Զ�̴���", CH_12_12);
// 	// GUI_String(80, 43, "115200(readonly)", EN_5_8);
// }

void BaudSettingUI1show(void)
{
	clear_screen();
	GUI_String(10, 29, "��̫��", CH_12_12);
	GUI_String(105, 31, Baudlist[System_Parameter.BaudIndex[0]].pstring, EN_5_8);
	GUI_Lattice(149, 31, 5, 8, IconRight);
	GUI_Lattice(97, 31, 5, 8, Iconleft);
}

void BaudSettingUI2show(void)
{
	clear_screen();
	GUI_String(10, 29, "������", CH_12_12);
	GUI_String(105, 31, Baudlist[System_Parameter.BaudIndex[1]].pstring, EN_5_8);
	GUI_Lattice(149, 31, 5, 8, IconRight);
	GUI_Lattice(97, 31, 5, 8, Iconleft);
}

void BaudSettingUI3show(void)
{
	clear_screen();
	GUI_String(10, 29, "��չ��", CH_12_12);
	GUI_String(105, 31, Baudlist[System_Parameter.BaudIndex[2]].pstring, EN_5_8);
	GUI_Lattice(149, 31, 5, 8, IconRight);
	GUI_Lattice(97, 31, 5, 8, Iconleft);
}

void BaudSettingUI4show(void)
{
	clear_screen();
	GUI_String(10, 29, "�ڲ���", CH_12_12);
	GUI_String(105, 31, Baudlist[System_Parameter.BaudIndex[3]].pstring, EN_5_8);
	GUI_Lattice(149, 31, 5, 8, IconRight);
	GUI_Lattice(97, 31, 5, 8, Iconleft);
}

void ReloadSettingUIshow(void)
{
	clear_screen();
	GUI_String(48, 20, "�Ƿ�ָ���������", CH_12_12);
	GUI_String(10, 48, "��", CH_12_12);
	GUI_String(172, 48, "��", CH_12_12);
}

void HotspotSettingUIshow(void)
{
	clear_screen();
	GUI_String(10,10,"�ȵ�", CH_12_12);
	GUI_String(115,10,Aplist[System_Parameter.Apstate].pstring,CH_12_12);
	GUI_Lattice(149,13,5,8,IconRight);
	GUI_Lattice(97,13,5,8,Iconleft);
			
	GUI_String(10,43,"AP ID",EN_5_8);
	GUI_String(97,43,AP_ID,EN_5_8);	
}

void WorkModeUIshow(void)
{
	clear_screen();
	GUI_String(10,10,"ģʽ", CH_12_12);
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
	/*PLC��������վʱ��Ĭ�ϴ�վΪRS485*/
	System_Parameter.CurrentSlave = RS485_ID;
}

/**
 * @brief	ϵͳ���ݴ洢��EEPROM
 * @details	�洢����ǰΪ�˷�ֹ�жϴ�����ݵĴ洢����ùر�ȫ���ж�
 * @param	None
 * @retval	None
 */
void ControlSave(void)
{
	/*�������ǰ��Ч���ݵ�У���벢�洢*/
	System_Parameter.CRC16 = getCrc16(&System_Parameter.PSWNext.PassWordbuff[0], (sizeof(System_Parameter) - (sizeof(PASSWORDSTRUCT) - 4U) - 2U), 0xffff);
	
	CLOSE_GLOBAL_OUTAGE();
	/*ÿ��д֮ǰ������в�������������ÿ�ΰ���512B����(0x00-0x0200)*/
	IapErase(START_SAVEADDRESS); 
	IapWrite_Buff(START_SAVEADDRESS, &System_Parameter.PSWNext.PassWordbuff[0], (sizeof(System_Parameter) - (sizeof(PASSWORDSTRUCT) - 4U)));
	OPEN_GLOBAL_OUTAGE();
}