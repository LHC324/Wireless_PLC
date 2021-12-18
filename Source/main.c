//#include "config.h"
#include "Menu.h"
#include "timer.h"
#include "usart.h"
//#include "systemTimer.h"
#include "eeprom.h"
#include "GPIO.h"
#include "LCD.h"
#include "Key.h"
#include "Control.h"
#include "pFunc.h"
#include "report.h"
#include "mdrtuslave.h"
#include "wifi.h"

/*系统参数*/
SYSTEM_PARAMETER System_Parameter = {0, false, false, "\xFF\xFF\xFF\xFF", "\x08\x08\x02\x08", 0x01, 0x01, 0x00, 0x00,0x487e};

static void systemInit(void);
static void UsartHandle(void);
static void Iap_Flash_Iinit(void);

void main(void)
{
    systemInit(); //系统初始化

    while(1)
    {	/*按键*/
		KeyEvent(); 
		/*多串口数据处理*/
		Uart_Handle();
		/*ModBus接收数据处理*/
//        mdRTU_Handler();
    }
}

void systemInit(void)
{
	Init_All(); //初始化外设
	
	/***********************************************************************/
    //以太网串口结构体初始化
    Init_ListQueue(&COM_UART1);
	memset(&COM_UART1,  0, sizeof(COM_UART1));
	
	// 4G串口结构体初始化
    Init_ListQueue(&COM_UART2);
	memset(&COM_UART2, 0, sizeof(COM_UART2));
	
	// RS485串口结构体初始化
    Init_ListQueue(&COM_UART3);
	memset(&COM_UART3, 0, sizeof(COM_UART3));
	
	// PLC串口结构体初始化
    Init_ListQueue(&COM_UART4);
	memset(&COM_UART4, 0, sizeof(COM_UART4));

	/***********************************************************************/
	/*液晶屏初始化*/
    initial_lcd();  
    /*系统参数存储区初始化*/
    Iap_Flash_Iinit();
    /*以下为系统滴答定时器的初始化（10ms （不建议更改））*/	
    Timer0_Init();
    PublicTimer16.MenuDly16.Timer16Flag = false;
    // /*控件变量初始化,放在串口3初始化之前*/
    // ControlInit();	
    /*STC程序下载/printf/以太网*/
    Uart1_Init(); 
    /*4G模块*/
    Uart2_Init(); 
    /*RS485*/
    Uart3_Init(); 
    /*PLC*/
    Uart4_Init(); 
    /*串口3的485使能引脚，初始化为接收状态*/
    USART3_EN = 0; 
    /*控件变量初始化,放在串口3初始化之前*/
    ControlInit();
    /*打开全局中断*/
    OPEN_GLOBAL_OUTAGE(); 
	/*初始化Modbus协议栈*/
//	ModbusInit();
    /*显示界面初始化*/ 
    LcdShowInit();
    if(System_Parameter.WifiInitFlag == false)
    {
        /*初始化WIIF模块*/
        Wifi_Init(); 
        System_Parameter.WifiInitFlag = true; 
        /*存储到IAPFLASH*/
        ControlSave();
    }
    /*看门狗初始化 */ 
//	WDT_init();
}

/************************************外设初始化************************************/
void  Init_All(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

//    #ifdef EXTERNAL_CRYSTAL //只要有宏名，就成立
	#if EXTERNAL_CRYSTAL
    P_SW2 = 0x80;
    XOSCCR = 0xC0;
    /*启动外部晶振20MHz*/
    while (!(XOSCCR & 1));             
    /*时钟不分频*/
    CLKDIV = 0x01;  
    /*选择外部晶振 */                    
    CKSEL = 0x01;                    
    P_SW2 = 0x00;
    #endif
//  P_SW1 = 0xC0; //串口1切换到P4.3、4.4(P0.2、0.3)
//	P_SW2 |= 0x01; //串口2切换到P4.0、4.2(P1.0、1.1)（新板子引脚问题）

    //手册提示，串口1、2、3、4的发送引脚必须设置为强挽输出
	/*P0.x引脚输出方式*/
    /*设置P0.0、P0.2为准双向口*/
	GPIO_InitStruct.Mode = GPIO_PullUp;
    GPIO_InitStruct.Pin  = GPIO_Pin_0 | GPIO_Pin_2;
    GPIO_Inilize(GPIO_P0, &GPIO_InitStruct);
    /*设置P0.1为强挽输出 、设置P0.3为强挽输出*/
	GPIO_InitStruct.Mode = GPIO_OUT_PP;
    GPIO_InitStruct.Pin  = GPIO_Pin_1 | GPIO_Pin_3;
    GPIO_Inilize(GPIO_P0, &GPIO_InitStruct);

	/*P1.x引脚输出方式*/
    /*设置P1.0为准双向口*/
	GPIO_InitStruct.Mode = GPIO_PullUp;
    GPIO_InitStruct.Pin  = GPIO_Pin_0;
    GPIO_Inilize(GPIO_P1, &GPIO_InitStruct);
    /*设置P1.1、P1.4、 P1.5为强挽输出*/
	GPIO_InitStruct.Mode = GPIO_OUT_PP;
    GPIO_InitStruct.Pin  = GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5;
    GPIO_Inilize(GPIO_P1, &GPIO_InitStruct);

    /*P2.x引脚输出方式*/
    /*按键相关P2.2、P2.3、P2.4、P2.5、P2.6为高阻态*/
    GPIO_InitStruct.Mode = GPIO_HighZ;
    GPIO_InitStruct.Pin  = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6;
    GPIO_Inilize(GPIO_P2, &GPIO_InitStruct);

	/*P3.x引脚输出方式*/
    /*设置P3.0为准双向口*/
	GPIO_InitStruct.Mode = GPIO_PullUp;
    GPIO_InitStruct.Pin  = GPIO_Pin_0;
    GPIO_Inilize(GPIO_P3, &GPIO_InitStruct);

    /*设置P3.1为强挽输出*/
	GPIO_InitStruct.Mode = GPIO_OUT_PP;
    GPIO_InitStruct.Pin  = GPIO_Pin_1;
    GPIO_Inilize(GPIO_P3, &GPIO_InitStruct);
    
}
/************************************外设初始化************************************/


/************************************检查IAP区FLASH内容************************************/
bit CheckIap_Flash(void)
{
    uint16_t CRC = 0;

	/*读取存储区数据*/
	IapRead_Buff(START_SAVEADDRESS, &System_Parameter.PSWNext.PassWordbuff[0], (sizeof(System_Parameter) - (sizeof(PASSWORDSTRUCT) - 4U))); 
	/*计算CRC校验码*/
	CRC = getCrc16(&System_Parameter.PSWNext.PassWordbuff[0], (sizeof(System_Parameter) - (sizeof(PASSWORDSTRUCT) - 4U) - 2U), 0xffff);   
	/*比较当前校验码和存储区校验码是否匹配*/
	if(CRC == System_Parameter.CRC16)
	{
		return true;
	}
	return false;
}


void Iap_Flash_Iinit(void)
{   /*检查eeprom参数是否正确*/
    if(CheckIap_Flash())  
    {
        GUI_String(14, 31, "parameters are correct !", EN_5_8);
        Delay_ms(1000);
    }
    else
    {
        GUI_String(19, 31, "parameters error !", EN_5_8);
        Delay_ms(500);
        GUI_String(19, 31, "restore parameters...", EN_5_8);
		
		/*每次写之前必须进行擦除操作：擦除每次按照512B进行(0x00-0x0200)*/
        IapErase(START_SAVEADDRESS); 
		/*把默认参数拷贝到当前数据结构*/
		memcpy(&System_Parameter.PSWNext.PassWordbuff[0], DEFAULT_SYSTEM_PARAMETER, (sizeof(System_Parameter) - (sizeof(PASSWORDSTRUCT) - 4U))); 
		/*把数据进行存储*/
        IapWrite_Buff(START_SAVEADDRESS, &System_Parameter.PSWNext.PassWordbuff[0], (sizeof(System_Parameter) - (sizeof(PASSWORDSTRUCT) - 4U))); //去掉一个字节的index

        Delay_ms(1000);
        clear_screen();
        GUI_String(49, 31, "successfully !", EN_5_8);
        Delay_ms(500);
    }
}
/************************************检查IAP区FLASH内容************************************/