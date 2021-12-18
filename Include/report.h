#ifndef _REPORT_H_
#define _REPORT_H_

#include "config.h"	

/*Modbus协议站从机地址*/
#define MODBUS_SLAVEADDR    0x02

//extern void dataExchange(void);
//void copyPlcToExt(void);

/**
 * @brief	串口事件处理
 * @details	
 * @param	None
 * @retval	None
 */
extern void Uart_Handle(void);
/**
 * @brief	初始化静态链队
 * @details
 * @param	*List:当前链队指针
 * @retval	None
 */
 extern void Init_ListQueue(Uart_List *List);

/**
 * @brief	获取16bitCRC码
 * @details	
 * @param	*ptr:参与校验数据指针,length:数据长度,init_dat:参与运算目标数据
 * @retval	None
 */
extern uint16_t getCrc16(uint8_t *ptr, uint8_t length, uint16_t init_dat);

#endif