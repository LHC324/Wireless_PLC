/********************************************************************
 **--------------文件信息---------------------------------------------
 **文   件   名：wifi.h
 **创 建  日 期：2021年4月9日
 **最后修改日期：
 **版 权 信  息: 云南兆富科技有限公司
 **程   序   员：LHC
 **版   本   号：V3.0
 **描        述：WIFI驱动程序（USR-C215）
 **修 改 日  志:
 *********************************************************************/
#ifndef _WIFI_H_
#define	_WIFI_H_

#ifdef	__cplusplus
extern "C" {
#endif

#include "config.h"

/*定义WIFI模块相关引脚*/
#define WIFI_RESET		P14
#define WIFI_RELOAD		P15

typedef unsigned char (*event)(void);
typedef struct
{
	char* pSend;
	char* pRecv;
	uint16_t WaitTimes;
	event pFunc;
}AT_Command;

void AT_SetWap(char* ssid,char* key);
void AT_SetWsta(char* ssid,char* key);


/**
 * @brief	初始化WIFI模块
 * @details	
 * @param	None
 * @retval	None
 */
extern void Wifi_Init(void);

/**
 * @brief	WIFI模块启停
 * @details	
 * @param	status:状态
 * @retval	None
 */
extern void Wifi_Enable(uint8_t status);

#ifdef	__cplusplus
}
#endif

#endif	/* _WIFI_H_ */

