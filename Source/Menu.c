#include "Menu.h"

/*��ǰUI����״̬*/
SHOW_STATE UI_STATE = MAIN_STATE;

OPTION Optionlist[] =
{
    {"��ͣ����", CONTROL_PLCPOWER, PlcPowerUIshow},
    {"ͨ�ŷ�ʽ", CONTROL_COMMUNICA, CommunicaUIshow},
    {"�����޸�", CONTROL_PASSWORD_CHANGE, PassWordChangeUIShow},
    {"����������", CONTROL_BAUDSETTING, Baud_Setting},
    {"�ָ���������", CONTROL_RELOAD, ReloadSettingUIshow},
};

#define OptionlistSize (sizeof(Optionlist) / sizeof(OPTION))

/*�����˵�*/
OPTION Optionlist1[] =
{
    {"��̫��", CONTROL_BAUD1, BaudSettingUI1show},
    {"������", CONTROL_BAUD2, BaudSettingUI2show}, 
    {"��չ��", CONTROL_BAUD3, BaudSettingUI3show}, 
    {"�ڲ���", CONTROL_BAUD4, BaudSettingUI4show}
};

#define OptionlistSize1 (sizeof(Optionlist1) / sizeof(OPTION))

/*��ǰ�༶�˵�����*/
Menu_Show M_Show[] = 
{
    {0, 0, 0, {1, 2, 3}, Optionlist}, 
    {0, 0, 0, {1, 2, 3}, Optionlist1}

};

#define MENU_NUM (sizeof(M_Show) / sizeof(Menu_Show))

/*����ӳ���*/
const KEY_MAP keyStateEvent[] =
    {
        /*Main״̬*/
        {KEY_UP, MAIN_STATE, KeyMain_Up},
        {KEY_DOWN, MAIN_STATE, KeyMain_Down},
        {KEY_ENTER, MAIN_STATE, KeyMain_Enter},
        {KEY_CANCEL, MAIN_STATE, KeyMain_Cancel},
        {KEY_MENU, MAIN_STATE, KeyMain_Menu},
        /*Menu״̬*/
        {KEY_UP, MENU_STATE, KeyMenu_Up},
        {KEY_DOWN, MENU_STATE, KeyMenu_Down},
        {KEY_ENTER, MENU_STATE, KeyMenu_Enter},
        {KEY_CANCEL, MENU_STATE, KeyMenu_Cancel},
        {KEY_MENU, MENU_STATE, KeyMenu_Menu},
        /*CONTROL״̬*/
        {KEY_UP, CONTROL_STATE, KeyControl_Up},
        {KEY_DOWN, CONTROL_STATE, KeyControl_Down},
        {KEY_ENTER, CONTROL_STATE, KeyControl_Enter},
        {KEY_CANCEL, CONTROL_STATE, KeyControl_Cancel},
        {KEY_MENU, CONTROL_STATE, KeyControl_Menu},
        /*BAUD״̬*/
        {KEY_UP, BAUD_STATE, KeyBaud_Up},
        {KEY_DOWN, BAUD_STATE, KeyBaud_Down},
        {KEY_ENTER, BAUD_STATE, KeyBaud_Enter},
        {KEY_CANCEL, BAUD_STATE, KeyBaud_Cancel},
        {KEY_MENU, BAUD_STATE, KeyBaud_Menu}
};

#define keyStateEventSize (sizeof(keyStateEvent) / sizeof(KEY_MAP))

void KeyEvent(void) //�����¼�
{
    uint8_t i;
    KEY_e KeyState = Key_Chick(); //��ȡ����״̬

    LcdDly(KeyState); // �ް����������غ���

    if (KeyState == NO_KEY) //�ް���ֱ�ӷ���
    {
        return;
    }

    for (i = 0; i < keyStateEventSize; i++)
    {
        if (KeyState == keyStateEvent[i].Keycodel) //����ֵ
        {
            if (UI_STATE == keyStateEvent[i].Stage) //����״̬
            {
                keyStateEvent[i].fun(); //ִ�а���״̬��Ӧ����
                break;
            }
        }
    }
}

void LcdShowInit(void) //������ʾ��ʼ��
{
    LcdShow(&ScreensaverUiShow);
}

void LcdShow(pshow InterfaceShow) //������ʾ�ӿ�(�ص�����˼��)
{
    InterfaceShow();
}

/**
 * @brief	������״̬--enter
 * @details	���������°���enter��ť
 * @param	None
 * @retval	None
 */
void KeyMain_Enter(void)
{
#if USE_PRINTF_DEBUG
    uint8_t temp = strncmp(System_Parameter.PSWNext.PassWordbuff, "\xFF\xFF\xFF\xFF", PASSWORDBITS);
#endif
    if (ControlType == CONTROL_PASSWORD)
    {
        /*û�����ù��������������ȷ*/
        if (PassWordjudge(PassWordI, System_Parameter) || (!strncmp(System_Parameter.PSWNext.PassWordbuff, "\xFF\xFF\xFF\xFF", PASSWORDBITS)))
        {
            LcdShow(RefreshMenuDisp); //ˢ�½���
            UI_STATE = MENU_STATE;
            // PublicTimer16.MenuDly16.Timer16Count = T_60S; //�޲������ض�ʱ������
        }
        else //����������
        {
            PassWordDelete(&PassWordI);
            clear_screen();
            GUI_String(49, 31, "wrong password !", EN_5_8);
            Delay_ms(1000);
            LcdShow(PassWordInputUIShow); //��������
        }
    }

#if USE_PRINTF_DEBUG
    Uartx_SendStr(&Uart1, System_Parameter.PSWNext.PassWordbuff, 4);
    Uartx_SendStr(&Uart1, &temp, 1);
    printf("KeyMain_Enter\r\n");
#endif
}

void KeyMain_Up(void) //������״̬--Up
{
    if (ControlType == CONTROL_PASSWORD) //����ؼ�
    {
        uint8_t Value = PassWordInput(ADD, &PassWordI);
        uint8_t temp[2]; //�ַ�
        GUI_String(PassWordI.PSWNext.Index * 20 + 97, 38, myitoa(Value, temp, 10), EN_5_8);
    }

#if USE_PRINTF_DEBUG
    printf("KeyMain_Up\r\n");
#endif
}
/*�������浽������������л�*/
void KeyMain_Menu(void) //������״̬--Menu
{
    switch (ControlType)
    {
    case CONTROL_SCREENSAVE:
    {
        /*�л����������*/
        ControlType = CONTROL_PASSWORD;
        LcdShow(&PassWordInputUIShow);
        /*�޲������ض�ʱ������*/
        PublicTimer16.MenuDly16.Timer16Count = T_60S;
    }
    break;
    case CONTROL_PASSWORD:
    { /*�ı䵱ǰ��������λ��*/
        InputOffect(&PassWordI);
    }
    break;
    default:
        break;
    }

#if USE_PRINTF_DEBUG
    printf("KeyMain_Menu\r\n");
#endif
}

void KeyMain_Cancel(void) //������״̬--Cancel
{
    /*�����水��ȡ�������˵���������*/
    if (ControlType == CONTROL_PASSWORD)
    {
        LcdShow(&ScreensaverUiShow);
        PassWordDelete(&PassWordI);
    }

#if USE_PRINTF_DEBUG
    printf("%s\r\n", System_Parameter.PSWNext.PassWordbuff); //��ֹ��������֮�����ȥPLC
#endif
}

void KeyMain_Down(void) //������״̬--Down
{
    if (ControlType == CONTROL_PASSWORD)
    {
        uint8_t Value = PassWordInput(SUB, &PassWordI);
        uint8_t temp[2]; //�ַ�
        GUI_String(PassWordI.PSWNext.Index * 20 + 97, 38, myitoa(Value, temp, 10), EN_5_8);
    }

#if USE_PRINTF_DEBUG
    printf("KeyMain_Down\r\n");
#endif
}

void KeyMenu_Enter(void) //�˵�״̬--Enter
{
    if (M_Show[MAIN_MENU].OptionNow->ControlShow == NULL)
    {
        return;
    }

    UI_STATE = CONTROL_STATE;
    ControlType = M_Show[MAIN_MENU].OptionNow->ControlType; //��ֵ�ؼ�
    LcdShow(M_Show[MAIN_MENU].OptionNow->ControlShow);      //��ʾ���ƽ���
#if USE_PRINTF_DEBUG
    printf("KeyMenu_Enter\r\n");
#endif
}

/*�˵�״̬--Up*/
void KeyMenu_Up(void) 
{
    /*��ͷ������С*/
    if ((M_Show[MAIN_MENU].Finger_Index--) == 0) 
        M_Show[MAIN_MENU].Finger_Index = 0;

    M_Show[MAIN_MENU].Option_Index = LoopIndex(UPWORD, M_Show[MAIN_MENU].Option_Index, OptionlistSize);

    if (M_Show[MAIN_MENU].Option_Index == (OptionlistSize - 1)) //�����߼�
    {
        M_Show[MAIN_MENU].Finger_Index = 2;
    }
    /*�˵������߼�*/
    if (M_Show[MAIN_MENU].Finger_Index == 0)
    {
        M_Show[MAIN_MENU].OptionIndex_buf[0] = M_Show[MAIN_MENU].Option_Index;
        M_Show[MAIN_MENU].OptionIndex_buf[1] = M_Show[MAIN_MENU].Option_Index + 1;
        M_Show[MAIN_MENU].OptionIndex_buf[2] = M_Show[MAIN_MENU].Option_Index + 2;
    }
    else if (M_Show[MAIN_MENU].Finger_Index == 1)
    {
        M_Show[MAIN_MENU].OptionIndex_buf[0] = M_Show[MAIN_MENU].Option_Index - 1;
        M_Show[MAIN_MENU].OptionIndex_buf[1] = M_Show[MAIN_MENU].Option_Index;
        M_Show[MAIN_MENU].OptionIndex_buf[2] = M_Show[MAIN_MENU].Option_Index + 1;
    }
    else
    {
        M_Show[MAIN_MENU].OptionIndex_buf[0] = M_Show[MAIN_MENU].Option_Index - 2;
        M_Show[MAIN_MENU].OptionIndex_buf[1] = M_Show[MAIN_MENU].Option_Index - 1;
        M_Show[MAIN_MENU].OptionIndex_buf[2] = M_Show[MAIN_MENU].Option_Index;
    }

    LcdShow(RefreshMenuDisp);             //ˢ����ʾ
    M_Show[MAIN_MENU].OptionNow = &Optionlist[M_Show[MAIN_MENU].Option_Index]; //��ֵ��ǰѡ��
#if USE_PRINTF_DEBUG
    printf("KeyMenu_Up\r\n");
#endif
}

/*�˵�״̬--Menu*/
void KeyMenu_Menu(void) 
{
#if USE_PRINTF_DEBUG
    printf("KeyMenu_Menu\r\n");
#endif
}

void KeyMenu_Cancel(void) //�˵�״̬--Cancel
{
    /*�˵����水��ȡ������ֱ������*/
    UI_STATE = MAIN_STATE;
    ControlType = CONTROL_SCREENSAVE;
    LcdShow(&ScreensaverUiShow);
    PassWordDelete(&PassWordI);

#if USE_PRINTF_DEBUG
    printf("KeyMenu_Cancel\r\n");
#endif
}

void KeyMenu_Down(void) //�˵�״̬--Down
{
    if ((M_Show[MAIN_MENU].Finger_Index++) == 2) //��ͷ��������
        M_Show[MAIN_MENU].Finger_Index = 2;

    M_Show[MAIN_MENU].Option_Index = LoopIndex(DOWMWORD, M_Show[MAIN_MENU].Option_Index, OptionlistSize); //ѡ������

    if (M_Show[MAIN_MENU].Option_Index == 0) //�����߼�
    {
        M_Show[MAIN_MENU].Finger_Index = 0;
    }

    if (M_Show[MAIN_MENU].Finger_Index == 0)
    {
        M_Show[MAIN_MENU].OptionIndex_buf[0] = M_Show[MAIN_MENU].Option_Index;
        M_Show[MAIN_MENU].OptionIndex_buf[1] = M_Show[MAIN_MENU].Option_Index + 1;
        M_Show[MAIN_MENU].OptionIndex_buf[2] = M_Show[MAIN_MENU].Option_Index + 2;
    }
    else if (M_Show[MAIN_MENU].Finger_Index == 1)
    {
        M_Show[MAIN_MENU].OptionIndex_buf[0] = M_Show[MAIN_MENU].Option_Index - 1;
        M_Show[MAIN_MENU].OptionIndex_buf[1] = M_Show[MAIN_MENU].Option_Index;
        M_Show[MAIN_MENU].OptionIndex_buf[2] = M_Show[MAIN_MENU].Option_Index + 1;
    }
    else
    {
        M_Show[MAIN_MENU].OptionIndex_buf[0] = M_Show[MAIN_MENU].Option_Index - 2;
        M_Show[MAIN_MENU].OptionIndex_buf[1] = M_Show[MAIN_MENU].Option_Index - 1;
        M_Show[MAIN_MENU].OptionIndex_buf[2] = M_Show[MAIN_MENU].Option_Index;
    }

    LcdShow(RefreshMenuDisp);             //ˢ����ʾ
    M_Show[MAIN_MENU].OptionNow = &Optionlist[M_Show[MAIN_MENU].Option_Index]; //��ֵ��ǰѡ��

#if USE_PRINTF_DEBUG
    printf("KeyMenu_Down\r\n");
#endif
}

void KeyControl_Enter(void) //�ؼ�״̬--Enter
{
    switch (ControlType)
    {
    case CONTROL_PASSWORD_CHANGE:
    {
        if (PassWordFirstChangeFlag == 0) //����ǵ�һ�������޸�����
        {
            uint8_t i;
            uint8_t temp[2];

            for (i = 0; i < PASSWORDBITS; i++) //��ʾ4λ����
            {
                GUI_String(i * 20 + 100, 18, myitoa(PassWordChange1.PSWNext.PassWordbuff[i], temp, 10), EN_5_8);
            }

            GUI_Lattice(175, 16, 16, 12, dot);
            PassWordFirstChangeFlag = 1; //�ñ�־λ
        }
        else
        {

            if (PassWordjudge(PassWordChange1, PassWordChange2)) //�����ж�����������ͬ����ʱ�޸ĳɹ�
            {
                memcpy(&System_Parameter.PSWNext.PassWordbuff, &PassWordChange2.PSWNext.PassWordbuff, sizeof(PassWordChange2.PSWNext.PassWordbuff));
                ControlSave();
                PassWordDelete(&PassWordChange1); //�޸�����1��0
                PassWordDelete(&PassWordChange2); //�޸�����2��0
                UI_STATE = MENU_STATE;            //���ز˵�����

                clear_screen();
                GUI_String(70, 22, "�޸ĳɹ�", CH_12_12); //��ʾ�޸Ľ��
                Delay_ms(500);
                LcdShow(RefreshMenuDisp); //ˢ����ʾ
            }
            else //�����������벻һ��ʱ
            {

                clear_screen();
                GUI_String(70, 22, "�޸�ʧ��", CH_12_12); //��ʾ�޸Ľ��
                Delay_ms(500);
                LcdShow(PassWordChangeUIShow); //�޸�����
            }

            PassWordFirstChangeFlag = 0; //��0��־λ
        }

        break;
    }

    case CONTROL_PLCPOWER:
    {
        System_Parameter.PlcState ^= 1;
        RUNKEY = System_Parameter.PlcState;
        ControlSave();           //���̿�����
        LcdShow(PlcPowerUIshow); // PLC���ý���
        break;
    }

    case CONTROL_COMMUNICA:
    {
        if (System_Parameter.CommunicationType == LOCAL)
        {
            Wifi_Enable(false);
        }
        else
        {
            Wifi_Enable(true);
            clear_screen();
            GUI_String(30, 22, "Please wait a moment", EN_5_8);
            // /*��ʼ��WIIFģ��*/
            // Wifi_Init();
        }
        ControlSave(); //����ͨ�ŷ�ʽ

        clear_screen();
        GUI_String(70, 22, "�޸ĳɹ�", CH_12_12); //��ʾ�޸Ľ��
        Delay_ms(500);
        LcdShow(CommunicaUIshow); //ͨѶ���ý���
        break;
    }

    case CONTROL_BAUDSETTING:
    {
        if (M_Show[SEC0_MENU].OptionNow->ControlShow == NULL)
        {
            return;
        }
	    /*�л������������ý���*/
	    UI_STATE = BAUD_STATE;
        /*��ֵ�ؼ�*/
        ControlType = M_Show[SEC0_MENU].OptionNow->ControlType; 
        /*��ʾ���ƽ���*/
        LcdShow(M_Show[SEC0_MENU].OptionNow->ControlShow);      
	    /*�޲������ض�ʱ������*/
	    // PublicTimer16.MenuDly16.Timer16Count = T_60S; 
    } break;
    /*�ָ���������*/
    case CONTROL_RELOAD:
    {
        // novalueflag = true;
        CLOSE_GLOBAL_OUTAGE();
        IapErase(START_SAVEADDRESS); //����������
                                     /*��Ĭ�ϲ�����������ǰ���ݽṹ*/
        memcpy(&System_Parameter.PSWNext.PassWordbuff[0], DEFAULT_SYSTEM_PARAMETER, (sizeof(System_Parameter) - 1U));
        /*�����ݽ��д洢*/
        IapWrite_Buff(START_SAVEADDRESS, &System_Parameter.PSWNext.PassWordbuff[0], (sizeof(System_Parameter) - 1U)); //ʹ�������ʧЧ
        OPEN_GLOBAL_OUTAGE();

        BaudInit();
        // PassWordinit();
        PowerInit();
        CommunicaInit();
        UI_STATE = MENU_STATE; //���ز˵�����

        clear_screen();
        GUI_String(70, 22, "�޸ĳɹ�", CH_12_12); //��ʾ�޸Ľ��
        Delay_ms(500);
        LcdShow(RefreshMenuDisp); //ˢ����ʾ
        break;
    }

    default:
        break;
    }

#if USE_PRINTF_DEBUG
    printf("KeyControl_Enter\r\n");
#endif
}

void KeyControl_Menu(void) //�ؼ�״̬--Menu
{
    switch (ControlType)
    {
    case CONTROL_PASSWORD_CHANGE:
    {
        if (PassWordFirstChangeFlag == 0)
        {

            InputOffect(&PassWordChange1);
        }
        else
        {

            InputOffect(&PassWordChange2);
        }

        break;
    }

    default:
        break;
    }

#if USE_PRINTF_DEBUG
    printf("KeyControl_Menu\r\n");
#endif
}

void KeyControl_Cancel(void) //�ؼ�״̬--Cancel
{
    switch (ControlType)
    {
    case CONTROL_PASSWORD_CHANGE:
    {
        break;
    }

    case CONTROL_COMMUNICA:
    {
        // CommunciaIndex = CommunciaType; //���û��ȷ��,ֱ�ӷ��أ���ָ���ǰ״̬����
        break;
    }

    case CONTROL_BAUDSETTING:
    {
        // BaudWillIndex = BaudIndex; //���û��ȷ��,ֱ�ӷ��أ���ָ���ǰ״̬����
        break;
    }

    case CONTROL_RELOAD:
    {
        break;
    }

    default:
        break;
    }

    UI_STATE = MENU_STATE;    //���ز˵�����
    LcdShow(RefreshMenuDisp); //��ʾ����

#if USE_PRINTF_DEBUG
    printf("KeyControl_Cancel\r\n");
#endif
}

/*�ؼ�״̬--Up*/
void KeyControl_Up(void) 
{
    switch (ControlType)
    {
    case CONTROL_PASSWORD_CHANGE:
    {
        if (PassWordFirstChangeFlag == 0)
        {
            uint8_t Value = PassWordInput(ADD, &PassWordChange1);
            uint8_t temp[2]; //�ַ�
            GUI_String(PassWordChange1.PSWNext.Index * 20 + 100, 18, myitoa(Value, temp, 10), EN_5_8);
        }
        else
        {
            uint8_t Value = PassWordInput(ADD, &PassWordChange2);
            uint8_t temp[2]; //�ַ�
            GUI_String(PassWordChange2.PSWNext.Index * 20 + 100, 38, myitoa(Value, temp, 10), EN_5_8);
        }  
    }break;

    case CONTROL_COMMUNICA:
    {
        System_Parameter.CommunicationType ^= 1;
        LcdShow(CommunicaUIshow); //ͨѶ���ý���
    }break;

    case CONTROL_BAUDSETTING:
    {
        /*��ͷ������С*/
        if ((M_Show[SEC0_MENU].Finger_Index--) == 0) 
            M_Show[SEC0_MENU].Finger_Index = 0;

        M_Show[SEC0_MENU].Option_Index = LoopIndex(UPWORD, M_Show[SEC0_MENU].Option_Index, OptionlistSize1);

        if (M_Show[SEC0_MENU].Option_Index == (OptionlistSize1 - 1)) //�����߼�
        {
            M_Show[SEC0_MENU].Finger_Index = 2;
        }
        /*�˵������߼�*/
        if (M_Show[SEC0_MENU].Finger_Index == 0)
        {
            M_Show[SEC0_MENU].OptionIndex_buf[0] = M_Show[SEC0_MENU].Option_Index;
            M_Show[SEC0_MENU].OptionIndex_buf[1] = M_Show[SEC0_MENU].Option_Index + 1;
            M_Show[SEC0_MENU].OptionIndex_buf[2] = M_Show[SEC0_MENU].Option_Index + 2;
        }
        else if (M_Show[SEC0_MENU].Finger_Index == 1)
        {
            M_Show[SEC0_MENU].OptionIndex_buf[0] = M_Show[SEC0_MENU].Option_Index - 1;
            M_Show[SEC0_MENU].OptionIndex_buf[1] = M_Show[SEC0_MENU].Option_Index;
            M_Show[SEC0_MENU].OptionIndex_buf[2] = M_Show[SEC0_MENU].Option_Index + 1;
        }
        else
        {
            M_Show[SEC0_MENU].OptionIndex_buf[0] = M_Show[SEC0_MENU].Option_Index - 2;
            M_Show[SEC0_MENU].OptionIndex_buf[1] = M_Show[SEC0_MENU].Option_Index - 1;
            M_Show[SEC0_MENU].OptionIndex_buf[2] = M_Show[SEC0_MENU].Option_Index;
        }

        LcdShow(RefreshBaudDisp);             //ˢ����ʾ
        M_Show[SEC0_MENU].OptionNow = &Optionlist1[M_Show[SEC0_MENU].Option_Index]; //��ֵ��ǰѡ��
    }break;

    default:
        break;
    }

#if USE_PRINTF_DEBUG
    printf("KeyControl_Up\r\n");
#endif
}

void KeyControl_Down(void) //�ؼ�״̬--Down
{
    switch (ControlType)
    {
    case CONTROL_PASSWORD_CHANGE:
    {
        if (PassWordFirstChangeFlag == 0)
        {
            uint8_t Value = PassWordInput(SUB, &PassWordChange1);
            uint8_t temp[2]; //�ַ�
            GUI_String(PassWordChange1.PSWNext.Index * 20 + 100, 18, myitoa(Value, temp, 10), EN_5_8);
        }
        else
        {

            uint8_t Value = PassWordInput(SUB, &PassWordChange2);
            uint8_t temp[2]; //�ַ�
            GUI_String(PassWordChange2.PSWNext.Index * 20 + 100, 38, myitoa(Value, temp, 10), EN_5_8);
        }

    }break;

    case CONTROL_COMMUNICA:
    {
        System_Parameter.CommunicationType ^= 1;
        LcdShow(CommunicaUIshow); //ͨѶ���ý���
        
    }break;

    case CONTROL_BAUDSETTING:
    {   
        if ((M_Show[SEC0_MENU].Finger_Index++) >= 2) //��ͷ��������
        M_Show[SEC0_MENU].Finger_Index = 2;

        M_Show[SEC0_MENU].Option_Index = LoopIndex(DOWMWORD, M_Show[SEC0_MENU].Option_Index, OptionlistSize1); //ѡ������

        if (M_Show[SEC0_MENU].Option_Index == 0) //�����߼�
        {
            M_Show[SEC0_MENU].Finger_Index = 0;
        }

        if (M_Show[SEC0_MENU].Finger_Index == 0)
        {
            M_Show[SEC0_MENU].OptionIndex_buf[0] = M_Show[SEC0_MENU].Option_Index;
            M_Show[SEC0_MENU].OptionIndex_buf[1] = M_Show[SEC0_MENU].Option_Index + 1;
            M_Show[SEC0_MENU].OptionIndex_buf[2] = M_Show[SEC0_MENU].Option_Index + 2;
        }
        else if (M_Show[SEC0_MENU].Finger_Index == 1)
        {
            M_Show[SEC0_MENU].OptionIndex_buf[0] = M_Show[SEC0_MENU].Option_Index - 1;
            M_Show[SEC0_MENU].OptionIndex_buf[1] = M_Show[SEC0_MENU].Option_Index;
            M_Show[SEC0_MENU].OptionIndex_buf[2] = M_Show[SEC0_MENU].Option_Index + 1;
        }
        else
        {
            M_Show[SEC0_MENU].OptionIndex_buf[0] = M_Show[SEC0_MENU].Option_Index - 2;
            M_Show[SEC0_MENU].OptionIndex_buf[1] = M_Show[SEC0_MENU].Option_Index - 1;
            M_Show[SEC0_MENU].OptionIndex_buf[2] = M_Show[SEC0_MENU].Option_Index;
        }
        /*ˢ�µ�ǰѡ�*/
        LcdShow(RefreshBaudDisp);             
        M_Show[SEC0_MENU].OptionNow = &Optionlist1[M_Show[SEC0_MENU].Option_Index]; //��ֵ��ǰѡ��
    }break;

    default:
        break;
    }

#if USE_PRINTF_DEBUG
    printf("KeyControl_Down\r\n");
#endif
}

/*�����ʿؼ�״̬--up*/
void KeyBaud_Up(void)
{
    switch (ControlType)
    {
        case CONTROL_BAUD1:
        {
            System_Parameter.BaudIndex[0] = LoopIndex(DOWMWORD, System_Parameter.BaudIndex[0], G_BaudList_Size);
            GUI_String(105, 31, Baudlist[System_Parameter.BaudIndex[0]].pstring, EN_5_8);
        }break;
        case CONTROL_BAUD2:
        {
            System_Parameter.BaudIndex[1] = LoopIndex(DOWMWORD, System_Parameter.BaudIndex[1], G_BaudList_Size);
            GUI_String(105, 31, Baudlist[System_Parameter.BaudIndex[1]].pstring, EN_5_8);
        }break;
        case CONTROL_BAUD3:
        {
            System_Parameter.BaudIndex[2] = LoopIndex(DOWMWORD, System_Parameter.BaudIndex[2], G_BaudList_Size);
            GUI_String(105, 31, Baudlist[System_Parameter.BaudIndex[2]].pstring, EN_5_8);
        }break;
        case CONTROL_BAUD4:
        {
            System_Parameter.BaudIndex[3] = LoopIndex(DOWMWORD, System_Parameter.BaudIndex[3], G_BaudList_Size);
            GUI_String(105, 31, Baudlist[System_Parameter.BaudIndex[3]].pstring, EN_5_8);
        }break;
        default : break;
    }
#if USE_PRINTF_DEBUG
    printf("KeyBaud_Up\r\n");
#endif
}

/*�����ʿؼ�״̬--Down*/
void KeyBaud_Down(void)
{
    switch (ControlType)
    {
        case CONTROL_BAUD1:
        {
            System_Parameter.BaudIndex[0] = LoopIndex(UPWORD, System_Parameter.BaudIndex[0], G_BaudList_Size);
            GUI_String(105, 31, Baudlist[System_Parameter.BaudIndex[0]].pstring, EN_5_8);
        }break;
        case CONTROL_BAUD2:
        {
            System_Parameter.BaudIndex[1] = LoopIndex(UPWORD, System_Parameter.BaudIndex[1], G_BaudList_Size);
            GUI_String(105, 31, Baudlist[System_Parameter.BaudIndex[1]].pstring, EN_5_8);
        }break;
        case CONTROL_BAUD3:
        {
            System_Parameter.BaudIndex[2] = LoopIndex(UPWORD, System_Parameter.BaudIndex[2], G_BaudList_Size);
            GUI_String(105, 31, Baudlist[System_Parameter.BaudIndex[2]].pstring, EN_5_8);
        }break;
        case CONTROL_BAUD4:
        {
            System_Parameter.BaudIndex[3] = LoopIndex(UPWORD, System_Parameter.BaudIndex[3], G_BaudList_Size);
            GUI_String(105, 31, Baudlist[System_Parameter.BaudIndex[3]].pstring, EN_5_8);
        }break;
        default : break;
    }
#if USE_PRINTF_DEBUG
    printf("KeyBaud_Down\r\n");
#endif
}

/*�����ʿؼ�״̬--Enter*/
void KeyBaud_Enter(void)
{
    switch (ControlType)
    {
        case CONTROL_BAUD1:
        {
            SET_BRT1(1, Baudlist[System_Parameter.BaudIndex[0]].BaudValue);
            ControlSave();

            clear_screen();
            GUI_String(70, 22, "�޸ĳɹ�", CH_12_12); //��ʾ�޸Ľ��
            Delay_ms(500);
            LcdShow(BaudSettingUI1show); //���������ý���
        }break;
        case CONTROL_BAUD2:
        {
            SET_BRT1(2, Baudlist[System_Parameter.BaudIndex[1]].BaudValue);
            ControlSave();

            clear_screen();
            GUI_String(70, 22, "�޸ĳɹ�", CH_12_12); //��ʾ�޸Ľ��
            Delay_ms(500);
            LcdShow(BaudSettingUI2show); //���������ý���
        }break;
        case CONTROL_BAUD3:
        {
            SET_BRT1(3, Baudlist[System_Parameter.BaudIndex[2]].BaudValue);
            ControlSave();

            clear_screen();
            GUI_String(70, 22, "�޸ĳɹ�", CH_12_12); //��ʾ�޸Ľ��
            Delay_ms(500);
            LcdShow(BaudSettingUI3show); //���������ý���
        }break;
        case CONTROL_BAUD4:
        {
            SET_BRT1(4, Baudlist[System_Parameter.BaudIndex[3]].BaudValue);
            ControlSave();

            clear_screen();
            GUI_String(70, 22, "�޸ĳɹ�", CH_12_12); //��ʾ�޸Ľ��
            Delay_ms(500);
            LcdShow(BaudSettingUI4show); //���������ý���
        }break;
        default : break;
    }
#if USE_PRINTF_DEBUG
    printf("KeyBaud_Enter\r\n");
#endif
}

/*�����ʿؼ�״̬--Cancel*/
void KeyBaud_Cancel(void)
{   /*�����ϼ��˵�����*/
    UI_STATE = CONTROL_STATE; 
    /*��ֵ�ؼ�*/
    ControlType = CONTROL_BAUDSETTING; 
    LcdShow(RefreshBaudDisp);

#if USE_PRINTF_DEBUG
    printf("KeyBaud_Cancel\r\n");
#endif
}

/*�����ʿؼ�״̬--Menue*/
void KeyBaud_Menu(void)
{
#if USE_PRINTF_DEBUG
    printf("KeyBaud_Menu\r\n");
#endif
}

/*һ���˵�����ˢ����ʾ*/
void RefreshMenuDisp(void) 
{
    uint8_t i = 0;
    clear_screen(); //����

    for (; i < 3; i++)
    {
        GUI_String(70, 20 * i + 5, Optionlist[M_Show[MAIN_MENU].OptionIndex_buf[i]].pString, CH_12_12);
    }

    GUI_Lattice(50, 6 + M_Show[MAIN_MENU].Finger_Index * 20, 16, 12, finger);
}

/*�˵������¶����˵�ˢ����ʾ*/
void RefreshBaudDisp(void)
{
    uint8_t i = 0;
    clear_screen(); //����

    for (; i < 3U; i++)
    {
        GUI_String(70, 20 * i + 5, Optionlist1[M_Show[SEC0_MENU].OptionIndex_buf[i]].pString, CH_12_12);
    }

    GUI_Lattice(50, 6 + M_Show[SEC0_MENU].Finger_Index * 20, 16, 12, finger);
}

/**
 * @brief	���������ö����˵�
 * @details	
 * @param	None
 * @retval	None
 */
void Baud_Setting(void)
{
	/*ˢ�½���*/
	LcdShow(RefreshBaudDisp); 
	// /*�л������������ý���*/
	// UI_STATE = BAUD_STATE;
	// /*�޲������ض�ʱ������*/
	// PublicTimer16.MenuDly16.Timer16Count = T_60S; 
}


void LcdDly(KEY_e key)
{ /*����Ѿ��������������*/
    if (UI_STATE == MAIN_STATE)
    { /*���ҵ�ǰ�ؼ�Ϊ�����������ö�ʱ��*/
        if (ControlType == CONTROL_SCREENSAVE)
            return;
    }

    if (key == NO_KEY)
    {
        if (PublicTimer16.MenuDly16.Timer16Flag)
        {
            PublicTimer16.MenuDly16.Timer16Flag = false;
            UI_STATE = MAIN_STATE;
            ControlType = CONTROL_SCREENSAVE;
            /*�����������*/
            LcdShow(&ScreensaverUiShow);
            PassWordDelete(&PassWordI);
        }
    }
    else
    {
        PublicTimer16.MenuDly16.Timer16Count = T_60S;
    }
}
