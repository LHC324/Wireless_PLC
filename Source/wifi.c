/********************************************************************
 **--------------文件信息---------------------------------------------
 **文   件   名：wifi.h
 **创 建  日 期：2019年3月1日
 **最后修改日期：
 **版 权 信  息: 云南兆富科技有限公司
 **程   序   员：张东海
 **版   本   号：V1.0
 **描        述：WIFI驱动程序（RAK425）
 **修 改 日  志:
 *********************************************************************/

#include "wifi.h"
#include "systemTimer.h"
#include "usart.h"

/*当前设备热点名称*/
#define AP_NAME	 "AT+WAP=PLC0_AP,NONE\r\n"
// /*当前设备云平台设备号*/
#define CLOUD_ID "AT+REGCLOUD=00019639000000000040,SkdGAzyl\r\n"

/*USR-C210模块AT指令列表*/
const AT_Command code Wifi_Cmd[] =
{
	/*WIFI模块推出透传模式进入AT指令模式*/
	{"+++", "a", 1000U,  NULL},
	/*WIFI模块响应后，主动发送”a“*/
	{"a",   "+Ok", 200U, NULL},
	/*关闭回显*/ 
	//{"AT+E=OFF\r\n", "+OK", 500},           
	/*显示SSID*/ 
	//{"AT+HSSID = OFF\r\n", "+OK", 500}, 
	/*WIFI工作模式：AP + STA*/ 
	{"AT+WMODE=APSTA\r\n", "+OK", 200U, NULL},        
	/*设置路由器名称*/ 
	{AP_NAME, "+OK", 200U, NULL},
	/*设置心跳数据:www.ynpax.com*/ 
	{"AT+HEARTDT=7777772E796E7061782E636F6D\r\n", "+OK", 200U, NULL},   
	/*SSID和密码不能程序输入，需要在现场根据用户方的WIFI设置通过WEB方式修改*/
	/*设置WIFI登录SSID，密码*/ 
	{"AT+WSTA=union,*!ynzfkj20091215!*\r\n", "+OK", 200U, NULL}, 
	/*透传云设置*/       
	{"AT+REGENA=CLOUD,FIRST\r\n", "+OK", 200U, NULL},
	/*设置STOCKA参数*/
	{"AT+SOCKA=TCPC,cloud.usr.cn,15000\r\n", "+OK", 200U, NULL},
	/*设置搜索服务器和端口*/
	{"AT+SEARCH=15000,cloud.usr.cn\r\n", "+OK", 200U, NULL},
	/*透传云ID，透传云密码*/  
	{CLOUD_ID, "+OK", 200U, NULL},
	/*设置DHCP*/ 
	{"AT+WANN=DHCP\r\n", "+OK", 200U, NULL},
	/*软件重启USR-C210*/
	{"AT+Z\r\n", "+OK", 200U, NULL},  
	/*设置透传模式*/     
	// {"AT+ENTM\r\n", "+OK", 50U, NULL}    
};

#define WIFI_CMDSIZE sizeof(Wifi_Cmd) / sizeof(AT_Command)

/**
 * @brief	WIFI模块从透传模式退出到命令模式
 * @details	
 * @param	None
 * @retval	None
 */
// void wifi_cmd_mode(void)
// {
// 	char str[] = "+++";
// 	wifi_sendcmd((uint8_t*)str,strlen(str));
// }

// void wifi_ReciveNew(uint8_t* rxBuf,uint16_t Len)
// {
// 	uint16_t i;
// 	for(i = 0;i<Len;i++)
// 	{
// 		g_Wifi.RxBuf[i] = rxBuf[i];
// 	}
// 	g_Wifi.RxCount = Len;
// }

// void wifi_Poll(void)
// {
// 	wifi_AnalyzeApp();
// 	g_Wifi.RxCount = 0;
// }

// void wifi_AnalyzeApp(void)
// {
// 	if(g_Wifi.RxBuf[0] == 0x61 && g_Wifi.RxCount == 1)
// 	{
// 		cmdmodeflag = 1;
// 		wifisend_a();
// //		WifiCmdLight(0);     /*这一段可以不用，有点耦合*/
// 	}
// 	if(cmdmodeflag)  /*如果是在命令模式下*/
// 	{

// 	}
// }

// void wifisend_a(void)
// {
// 	char str = 'a';
// 	wifi_sendcmd((uint8_t*)&str, 1U);
// }

// void wifi_sendcmd(uint8_t * dat,uint8_t length)
// {
// 	Uartx_SendStr(&Uart2, dat, length);
// }

// void AT_SetWap(char* ssid,char* key)
// {
// 	char str[50] = "AT+WAP=";
// 	char*pstr = str;
// 	// assert_param((ssid!=NULL)&&(key!=NULL)); //检查参数是否正确

// 	if(strlen(key) < 8)
// 	{
// 		AT_error("length too short");
// 		return;
// 	}

// 	while(*pstr)
// 	{
// 		pstr++;
// 	}
// 	while(*ssid)
// 	{
// 		*pstr++ = *ssid++;
// 	}
// 	*pstr++ = ',';
// 	while(*key)
// 	{
// 		*pstr++ = *key++;
// 	}
// 	*pstr++ = '\r';
// 	*pstr++ = '\n';
// 	wifi_sendcmd((uint8_t*)str,strlen(str));
// }

// void SetUpWifi(char*ssid,char* key)
// {
// 	char str[100] = "AT+WSTA=";
// 	char*pstr = str;
// 	// assert_param((ssid!=NULL)&&(key!=NULL)); //检查参数是否正确

// 	if(strlen(ssid)> 32U)
// 	{
// 		AT_error("length too long");
// 	}

// 	while(*pstr)
// 	{
// 		pstr++;
// 	}
// 	while(*ssid)
// 	{
// 		*pstr++ = *ssid++;
// 	}
// 	*pstr++ = ',';
// 	while(*key)
// 	{
// 		*pstr++ = *key++;
// 	}
// 	*pstr++ = '\r';
// 	*pstr++ = '\n';
// 	wifi_sendcmd((uint8_t*)str,strlen(str));
// }

// void AT_Reload(void)
// {
// 	char str[20] = "AT+Z\r\n";
// 	wifi_sendcmd((uint8_t*)str,strlen(str));
// }

// void AT_error(char* error)
// {
// 	Uartx_SendStr(&Uart2, error, strlen(error));
// }


/**
 * @brief	WIFI模块启停
 * @details	
 * @param	status:状态
 * @retval	None
 */
void Wifi_Enable(uint8_t status)
{
	switch(status)
	{
		case true:
		{
			WIFI_RESET  = 1;
		}break;
		case false:
		{
			WIFI_RESET  = 0;
		}break;
		default : break;
	}
}

/**
 * @brief	初始化WIFI模块
 * @details	WIFI模块复位需要一定延时；在退出透传模式时延时必须>500ms,每条指令间间隔必须>100ms
 * @param	None
 * @retval	None
 */
void Wifi_Init(void)
{
	uint8_t i = 0;

	/*WIFI硬件引脚不复位*/
	WIFI_RESET  = 1;
	WIFI_RELOAD = 1;
	/*等待模块复位*/
	Delay_ms(500);

	for(i = 0; i < WIFI_CMDSIZE; i++)
	{
		Uartx_SendStr(&Uart2, (uint8_t *)Wifi_Cmd[i].pSend, strlen(Wifi_Cmd[i].pSend));
		/*执行对应的等待时间*/
		Delay_ms(Wifi_Cmd[i].WaitTimes);
	}
}

