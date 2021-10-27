#include "Menu.h"

/*当前UI界面状态*/
SHOW_STATE UI_STATE = MAIN_STATE;

OPTION Optionlist[] =
{
    {"启停开关", CONTROL_PLCPOWER, PlcPowerUIshow},
    {"通信方式", CONTROL_COMMUNICA, CommunicaUIshow},
    {"密码修改", CONTROL_PASSWORD_CHANGE, PassWordChangeUIShow},
    {"波特率设置", CONTROL_BAUDSETTING, Baud_Setting},
    {"恢复出厂设置", CONTROL_RELOAD, ReloadSettingUIshow},
};

#define OptionlistSize (sizeof(Optionlist) / sizeof(OPTION))

/*二级菜单*/
OPTION Optionlist1[] =
{
    {"以太网", CONTROL_BAUD1, BaudSettingUI1show},
    {"无线网", CONTROL_BAUD2, BaudSettingUI2show}, 
    {"扩展网", CONTROL_BAUD3, BaudSettingUI3show}, 
    {"内部网", CONTROL_BAUD4, BaudSettingUI4show}
};

#define OptionlistSize1 (sizeof(Optionlist1) / sizeof(OPTION))

/*当前多级菜单数量*/
Menu_Show M_Show[] = 
{
    {0, 0, 0, {1, 2, 3}, Optionlist}, 
    {0, 0, 0, {1, 2, 3}, Optionlist1}

};

#define MENU_NUM (sizeof(M_Show) / sizeof(Menu_Show))

/*函数映射表*/
const KEY_MAP keyStateEvent[] =
    {
        /*Main状态*/
        {KEY_UP, MAIN_STATE, KeyMain_Up},
        {KEY_DOWN, MAIN_STATE, KeyMain_Down},
        {KEY_ENTER, MAIN_STATE, KeyMain_Enter},
        {KEY_CANCEL, MAIN_STATE, KeyMain_Cancel},
        {KEY_MENU, MAIN_STATE, KeyMain_Menu},
        /*Menu状态*/
        {KEY_UP, MENU_STATE, KeyMenu_Up},
        {KEY_DOWN, MENU_STATE, KeyMenu_Down},
        {KEY_ENTER, MENU_STATE, KeyMenu_Enter},
        {KEY_CANCEL, MENU_STATE, KeyMenu_Cancel},
        {KEY_MENU, MENU_STATE, KeyMenu_Menu},
        /*CONTROL状态*/
        {KEY_UP, CONTROL_STATE, KeyControl_Up},
        {KEY_DOWN, CONTROL_STATE, KeyControl_Down},
        {KEY_ENTER, CONTROL_STATE, KeyControl_Enter},
        {KEY_CANCEL, CONTROL_STATE, KeyControl_Cancel},
        {KEY_MENU, CONTROL_STATE, KeyControl_Menu},
        /*BAUD状态*/
        {KEY_UP, BAUD_STATE, KeyBaud_Up},
        {KEY_DOWN, BAUD_STATE, KeyBaud_Down},
        {KEY_ENTER, BAUD_STATE, KeyBaud_Enter},
        {KEY_CANCEL, BAUD_STATE, KeyBaud_Cancel},
        {KEY_MENU, BAUD_STATE, KeyBaud_Menu}
};

#define keyStateEventSize (sizeof(keyStateEvent) / sizeof(KEY_MAP))

void KeyEvent(void) //按键事件
{
    uint8_t i;
    KEY_e KeyState = Key_Chick(); //获取按键状态

    LcdDly(KeyState); // 无按键操作返回函数

    if (KeyState == NO_KEY) //无按键直接返回
    {
        return;
    }

    for (i = 0; i < keyStateEventSize; i++)
    {
        if (KeyState == keyStateEvent[i].Keycodel) //按键值
        {
            if (UI_STATE == keyStateEvent[i].Stage) //按键状态
            {
                keyStateEvent[i].fun(); //执行按键状态对应函数
                break;
            }
        }
    }
}

void LcdShowInit(void) //界面显示初始化
{
    LcdShow(&ScreensaverUiShow);
}

void LcdShow(pshow InterfaceShow) //界面显示接口(回调函数思想)
{
    InterfaceShow();
}

/**
 * @brief	主界面状态--enter
 * @details	在主界面下按下enter按钮
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
        /*没有设置过密码或者密码正确*/
        if (PassWordjudge(PassWordI, System_Parameter) || (!strncmp(System_Parameter.PSWNext.PassWordbuff, "\xFF\xFF\xFF\xFF", PASSWORDBITS)))
        {
            LcdShow(RefreshMenuDisp); //刷新界面
            UI_STATE = MENU_STATE;
            // PublicTimer16.MenuDly16.Timer16Count = T_60S; //无操作返回定时器开启
        }
        else //如果密码错误
        {
            PassWordDelete(&PassWordI);
            clear_screen();
            GUI_String(49, 31, "wrong password !", EN_5_8);
            Delay_ms(1000);
            LcdShow(PassWordInputUIShow); //重新输入
        }
    }

#if USE_PRINTF_DEBUG
    Uartx_SendStr(&Uart1, System_Parameter.PSWNext.PassWordbuff, 4);
    Uartx_SendStr(&Uart1, &temp, 1);
    printf("KeyMain_Enter\r\n");
#endif
}

void KeyMain_Up(void) //主界面状态--Up
{
    if (ControlType == CONTROL_PASSWORD) //密码控件
    {
        uint8_t Value = PassWordInput(ADD, &PassWordI);
        uint8_t temp[2]; //字符
        GUI_String(PassWordI.PSWNext.Index * 20 + 97, 38, myitoa(Value, temp, 10), EN_5_8);
    }

#if USE_PRINTF_DEBUG
    printf("KeyMain_Up\r\n");
#endif
}
/*屏保界面到密码输入界面切换*/
void KeyMain_Menu(void) //主界面状态--Menu
{
    switch (ControlType)
    {
    case CONTROL_SCREENSAVE:
    {
        /*切换到密码界面*/
        ControlType = CONTROL_PASSWORD;
        LcdShow(&PassWordInputUIShow);
        /*无操作返回定时器开启*/
        PublicTimer16.MenuDly16.Timer16Count = T_60S;
    }
    break;
    case CONTROL_PASSWORD:
    { /*改变当前密码输入位置*/
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

void KeyMain_Cancel(void) //主界面状态--Cancel
{
    /*主界面按下取消键，退到屏保界面*/
    if (ControlType == CONTROL_PASSWORD)
    {
        LcdShow(&ScreensaverUiShow);
        PassWordDelete(&PassWordI);
    }

#if USE_PRINTF_DEBUG
    printf("%s\r\n", System_Parameter.PSWNext.PassWordbuff); //防止忘记密码之后进不去PLC
#endif
}

void KeyMain_Down(void) //主界面状态--Down
{
    if (ControlType == CONTROL_PASSWORD)
    {
        uint8_t Value = PassWordInput(SUB, &PassWordI);
        uint8_t temp[2]; //字符
        GUI_String(PassWordI.PSWNext.Index * 20 + 97, 38, myitoa(Value, temp, 10), EN_5_8);
    }

#if USE_PRINTF_DEBUG
    printf("KeyMain_Down\r\n");
#endif
}

void KeyMenu_Enter(void) //菜单状态--Enter
{
    if (M_Show[MAIN_MENU].OptionNow->ControlShow == NULL)
    {
        return;
    }

    UI_STATE = CONTROL_STATE;
    ControlType = M_Show[MAIN_MENU].OptionNow->ControlType; //赋值控件
    LcdShow(M_Show[MAIN_MENU].OptionNow->ControlShow);      //显示控制界面
#if USE_PRINTF_DEBUG
    printf("KeyMenu_Enter\r\n");
#endif
}

/*菜单状态--Up*/
void KeyMenu_Up(void) 
{
    /*箭头索引减小*/
    if ((M_Show[MAIN_MENU].Finger_Index--) == 0) 
        M_Show[MAIN_MENU].Finger_Index = 0;

    M_Show[MAIN_MENU].Option_Index = LoopIndex(UPWORD, M_Show[MAIN_MENU].Option_Index, OptionlistSize);

    if (M_Show[MAIN_MENU].Option_Index == (OptionlistSize - 1)) //索引逻辑
    {
        M_Show[MAIN_MENU].Finger_Index = 2;
    }
    /*菜单滑动逻辑*/
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

    LcdShow(RefreshMenuDisp);             //刷新显示
    M_Show[MAIN_MENU].OptionNow = &Optionlist[M_Show[MAIN_MENU].Option_Index]; //赋值当前选项
#if USE_PRINTF_DEBUG
    printf("KeyMenu_Up\r\n");
#endif
}

/*菜单状态--Menu*/
void KeyMenu_Menu(void) 
{
#if USE_PRINTF_DEBUG
    printf("KeyMenu_Menu\r\n");
#endif
}

void KeyMenu_Cancel(void) //菜单状态--Cancel
{
    /*菜单界面按下取消键，直接锁屏*/
    UI_STATE = MAIN_STATE;
    ControlType = CONTROL_SCREENSAVE;
    LcdShow(&ScreensaverUiShow);
    PassWordDelete(&PassWordI);

#if USE_PRINTF_DEBUG
    printf("KeyMenu_Cancel\r\n");
#endif
}

void KeyMenu_Down(void) //菜单状态--Down
{
    if ((M_Show[MAIN_MENU].Finger_Index++) == 2) //箭头索引增加
        M_Show[MAIN_MENU].Finger_Index = 2;

    M_Show[MAIN_MENU].Option_Index = LoopIndex(DOWMWORD, M_Show[MAIN_MENU].Option_Index, OptionlistSize); //选项索引

    if (M_Show[MAIN_MENU].Option_Index == 0) //索引逻辑
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

    LcdShow(RefreshMenuDisp);             //刷新显示
    M_Show[MAIN_MENU].OptionNow = &Optionlist[M_Show[MAIN_MENU].Option_Index]; //赋值当前选项

#if USE_PRINTF_DEBUG
    printf("KeyMenu_Down\r\n");
#endif
}

void KeyControl_Enter(void) //控件状态--Enter
{
    switch (ControlType)
    {
    case CONTROL_PASSWORD_CHANGE:
    {
        if (PassWordFirstChangeFlag == 0) //如果是第一次输入修改密码
        {
            uint8_t i;
            uint8_t temp[2];

            for (i = 0; i < PASSWORDBITS; i++) //显示4位密码
            {
                GUI_String(i * 20 + 100, 18, myitoa(PassWordChange1.PSWNext.PassWordbuff[i], temp, 10), EN_5_8);
            }

            GUI_Lattice(175, 16, 16, 12, dot);
            PassWordFirstChangeFlag = 1; //置标志位
        }
        else
        {

            if (PassWordjudge(PassWordChange1, PassWordChange2)) //密码判断两次输入相同密码时修改成功
            {
                memcpy(&System_Parameter.PSWNext.PassWordbuff, &PassWordChange2.PSWNext.PassWordbuff, sizeof(PassWordChange2.PSWNext.PassWordbuff));
                ControlSave();
                PassWordDelete(&PassWordChange1); //修改密码1清0
                PassWordDelete(&PassWordChange2); //修改密码2清0
                UI_STATE = MENU_STATE;            //返回菜单界面

                clear_screen();
                GUI_String(70, 22, "修改成功", CH_12_12); //显示修改结果
                Delay_ms(500);
                LcdShow(RefreshMenuDisp); //刷新显示
            }
            else //两次密码输入不一致时
            {

                clear_screen();
                GUI_String(70, 22, "修改失败", CH_12_12); //显示修改结果
                Delay_ms(500);
                LcdShow(PassWordChangeUIShow); //修改密码
            }

            PassWordFirstChangeFlag = 0; //置0标志位
        }

        break;
    }

    case CONTROL_PLCPOWER:
    {
        System_Parameter.PlcState ^= 1;
        RUNKEY = System_Parameter.PlcState;
        ControlSave();           //存盘开关量
        LcdShow(PlcPowerUIshow); // PLC设置界面
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
            // /*初始化WIIF模块*/
            // Wifi_Init();
        }
        ControlSave(); //存盘通信方式

        clear_screen();
        GUI_String(70, 22, "修改成功", CH_12_12); //显示修改结果
        Delay_ms(500);
        LcdShow(CommunicaUIshow); //通讯设置界面
        break;
    }

    case CONTROL_BAUDSETTING:
    {
        if (M_Show[SEC0_MENU].OptionNow->ControlShow == NULL)
        {
            return;
        }
	    /*切换到波特率设置界面*/
	    UI_STATE = BAUD_STATE;
        /*赋值控件*/
        ControlType = M_Show[SEC0_MENU].OptionNow->ControlType; 
        /*显示控制界面*/
        LcdShow(M_Show[SEC0_MENU].OptionNow->ControlShow);      
	    /*无操作返回定时器开启*/
	    // PublicTimer16.MenuDly16.Timer16Count = T_60S; 
    } break;
    /*恢复出厂设置*/
    case CONTROL_RELOAD:
    {
        // novalueflag = true;
        CLOSE_GLOBAL_OUTAGE();
        IapErase(START_SAVEADDRESS); //擦除密码区
                                     /*把默认参数拷贝到当前数据结构*/
        memcpy(&System_Parameter.PSWNext.PassWordbuff[0], DEFAULT_SYSTEM_PARAMETER, (sizeof(System_Parameter) - 1U));
        /*把数据进行存储*/
        IapWrite_Buff(START_SAVEADDRESS, &System_Parameter.PSWNext.PassWordbuff[0], (sizeof(System_Parameter) - 1U)); //使密码界面失效
        OPEN_GLOBAL_OUTAGE();

        BaudInit();
        // PassWordinit();
        PowerInit();
        CommunicaInit();
        UI_STATE = MENU_STATE; //返回菜单界面

        clear_screen();
        GUI_String(70, 22, "修改成功", CH_12_12); //显示修改结果
        Delay_ms(500);
        LcdShow(RefreshMenuDisp); //刷新显示
        break;
    }

    default:
        break;
    }

#if USE_PRINTF_DEBUG
    printf("KeyControl_Enter\r\n");
#endif
}

void KeyControl_Menu(void) //控件状态--Menu
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

void KeyControl_Cancel(void) //控件状态--Cancel
{
    switch (ControlType)
    {
    case CONTROL_PASSWORD_CHANGE:
    {
        break;
    }

    case CONTROL_COMMUNICA:
    {
        // CommunciaIndex = CommunciaType; //如果没有确定,直接返回，则恢复当前状态索引
        break;
    }

    case CONTROL_BAUDSETTING:
    {
        // BaudWillIndex = BaudIndex; //如果没有确定,直接返回，则恢复当前状态索引
        break;
    }

    case CONTROL_RELOAD:
    {
        break;
    }

    default:
        break;
    }

    UI_STATE = MENU_STATE;    //返回菜单界面
    LcdShow(RefreshMenuDisp); //显示设置

#if USE_PRINTF_DEBUG
    printf("KeyControl_Cancel\r\n");
#endif
}

/*控件状态--Up*/
void KeyControl_Up(void) 
{
    switch (ControlType)
    {
    case CONTROL_PASSWORD_CHANGE:
    {
        if (PassWordFirstChangeFlag == 0)
        {
            uint8_t Value = PassWordInput(ADD, &PassWordChange1);
            uint8_t temp[2]; //字符
            GUI_String(PassWordChange1.PSWNext.Index * 20 + 100, 18, myitoa(Value, temp, 10), EN_5_8);
        }
        else
        {
            uint8_t Value = PassWordInput(ADD, &PassWordChange2);
            uint8_t temp[2]; //字符
            GUI_String(PassWordChange2.PSWNext.Index * 20 + 100, 38, myitoa(Value, temp, 10), EN_5_8);
        }  
    }break;

    case CONTROL_COMMUNICA:
    {
        System_Parameter.CommunicationType ^= 1;
        LcdShow(CommunicaUIshow); //通讯设置界面
    }break;

    case CONTROL_BAUDSETTING:
    {
        /*箭头索引减小*/
        if ((M_Show[SEC0_MENU].Finger_Index--) == 0) 
            M_Show[SEC0_MENU].Finger_Index = 0;

        M_Show[SEC0_MENU].Option_Index = LoopIndex(UPWORD, M_Show[SEC0_MENU].Option_Index, OptionlistSize1);

        if (M_Show[SEC0_MENU].Option_Index == (OptionlistSize1 - 1)) //索引逻辑
        {
            M_Show[SEC0_MENU].Finger_Index = 2;
        }
        /*菜单滑动逻辑*/
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

        LcdShow(RefreshBaudDisp);             //刷新显示
        M_Show[SEC0_MENU].OptionNow = &Optionlist1[M_Show[SEC0_MENU].Option_Index]; //赋值当前选项
    }break;

    default:
        break;
    }

#if USE_PRINTF_DEBUG
    printf("KeyControl_Up\r\n");
#endif
}

void KeyControl_Down(void) //控件状态--Down
{
    switch (ControlType)
    {
    case CONTROL_PASSWORD_CHANGE:
    {
        if (PassWordFirstChangeFlag == 0)
        {
            uint8_t Value = PassWordInput(SUB, &PassWordChange1);
            uint8_t temp[2]; //字符
            GUI_String(PassWordChange1.PSWNext.Index * 20 + 100, 18, myitoa(Value, temp, 10), EN_5_8);
        }
        else
        {

            uint8_t Value = PassWordInput(SUB, &PassWordChange2);
            uint8_t temp[2]; //字符
            GUI_String(PassWordChange2.PSWNext.Index * 20 + 100, 38, myitoa(Value, temp, 10), EN_5_8);
        }

    }break;

    case CONTROL_COMMUNICA:
    {
        System_Parameter.CommunicationType ^= 1;
        LcdShow(CommunicaUIshow); //通讯设置界面
        
    }break;

    case CONTROL_BAUDSETTING:
    {   
        if ((M_Show[SEC0_MENU].Finger_Index++) >= 2) //箭头索引增加
        M_Show[SEC0_MENU].Finger_Index = 2;

        M_Show[SEC0_MENU].Option_Index = LoopIndex(DOWMWORD, M_Show[SEC0_MENU].Option_Index, OptionlistSize1); //选项索引

        if (M_Show[SEC0_MENU].Option_Index == 0) //索引逻辑
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
        /*刷新当前选项卡*/
        LcdShow(RefreshBaudDisp);             
        M_Show[SEC0_MENU].OptionNow = &Optionlist1[M_Show[SEC0_MENU].Option_Index]; //赋值当前选项
    }break;

    default:
        break;
    }

#if USE_PRINTF_DEBUG
    printf("KeyControl_Down\r\n");
#endif
}

/*波特率控件状态--up*/
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

/*波特率控件状态--Down*/
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

/*波特率控件状态--Enter*/
void KeyBaud_Enter(void)
{
    switch (ControlType)
    {
        case CONTROL_BAUD1:
        {
            SET_BRT1(1, Baudlist[System_Parameter.BaudIndex[0]].BaudValue);
            ControlSave();

            clear_screen();
            GUI_String(70, 22, "修改成功", CH_12_12); //显示修改结果
            Delay_ms(500);
            LcdShow(BaudSettingUI1show); //波特率设置界面
        }break;
        case CONTROL_BAUD2:
        {
            SET_BRT1(2, Baudlist[System_Parameter.BaudIndex[1]].BaudValue);
            ControlSave();

            clear_screen();
            GUI_String(70, 22, "修改成功", CH_12_12); //显示修改结果
            Delay_ms(500);
            LcdShow(BaudSettingUI2show); //波特率设置界面
        }break;
        case CONTROL_BAUD3:
        {
            SET_BRT1(3, Baudlist[System_Parameter.BaudIndex[2]].BaudValue);
            ControlSave();

            clear_screen();
            GUI_String(70, 22, "修改成功", CH_12_12); //显示修改结果
            Delay_ms(500);
            LcdShow(BaudSettingUI3show); //波特率设置界面
        }break;
        case CONTROL_BAUD4:
        {
            SET_BRT1(4, Baudlist[System_Parameter.BaudIndex[3]].BaudValue);
            ControlSave();

            clear_screen();
            GUI_String(70, 22, "修改成功", CH_12_12); //显示修改结果
            Delay_ms(500);
            LcdShow(BaudSettingUI4show); //波特率设置界面
        }break;
        default : break;
    }
#if USE_PRINTF_DEBUG
    printf("KeyBaud_Enter\r\n");
#endif
}

/*波特率控件状态--Cancel*/
void KeyBaud_Cancel(void)
{   /*返回上级菜单界面*/
    UI_STATE = CONTROL_STATE; 
    /*赋值控件*/
    ControlType = CONTROL_BAUDSETTING; 
    LcdShow(RefreshBaudDisp);

#if USE_PRINTF_DEBUG
    printf("KeyBaud_Cancel\r\n");
#endif
}

/*波特率控件状态--Menue*/
void KeyBaud_Menu(void)
{
#if USE_PRINTF_DEBUG
    printf("KeyBaud_Menu\r\n");
#endif
}

/*一级菜单界面刷新显示*/
void RefreshMenuDisp(void) 
{
    uint8_t i = 0;
    clear_screen(); //清屏

    for (; i < 3; i++)
    {
        GUI_String(70, 20 * i + 5, Optionlist[M_Show[MAIN_MENU].OptionIndex_buf[i]].pString, CH_12_12);
    }

    GUI_Lattice(50, 6 + M_Show[MAIN_MENU].Finger_Index * 20, 16, 12, finger);
}

/*菜单界面下二级菜单刷新显示*/
void RefreshBaudDisp(void)
{
    uint8_t i = 0;
    clear_screen(); //清屏

    for (; i < 3U; i++)
    {
        GUI_String(70, 20 * i + 5, Optionlist1[M_Show[SEC0_MENU].OptionIndex_buf[i]].pString, CH_12_12);
    }

    GUI_Lattice(50, 6 + M_Show[SEC0_MENU].Finger_Index * 20, 16, 12, finger);
}

/**
 * @brief	波特率设置二级菜单
 * @details	
 * @param	None
 * @retval	None
 */
void Baud_Setting(void)
{
	/*刷新界面*/
	LcdShow(RefreshBaudDisp); 
	// /*切换到波特率设置界面*/
	// UI_STATE = BAUD_STATE;
	// /*无操作返回定时器开启*/
	// PublicTimer16.MenuDly16.Timer16Count = T_60S; 
}


void LcdDly(KEY_e key)
{ /*如果已经在密码输入界面*/
    if (UI_STATE == MAIN_STATE)
    { /*并且当前控件为屏保，不启用定时器*/
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
            /*屏保界面界面*/
            LcdShow(&ScreensaverUiShow);
            PassWordDelete(&PassWordI);
        }
    }
    else
    {
        PublicTimer16.MenuDly16.Timer16Count = T_60S;
    }
}
