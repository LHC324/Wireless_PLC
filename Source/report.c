#include "report.h"
#include "usart.h"

void Uart_DataForward(SEL_CHANNEL Src, SEL_CHANNEL Dest);
void Plc_To_Rs485(void);
void Wifi_To_Plc(void);

/*定义当前串口交换序列*/
const ComData_Handle ComData_Array[] =
	{
		{CHANNEL_PLC, CHANNEL_RS485, Plc_To_Rs485},
		{CHANNEL_WIFI, CHANNEL_PLC, Wifi_To_Plc},
		//	{CHANNEL_LAN,  CHANNEL_PLC,   Lan_To_Plc}
};

#define COMDATA_SIZE (sizeof(ComData_Array) / sizeof(ComData_Handle))

/*创建4条链队*/
Uart_List Uart_LinkList[MAX_LQUEUE];

/**
 * @brief	初始化静态链队
 * @details	
 * @param	*List:当前链队指针
 * @retval	None
 */
// void Init_ListQueue(Uart_List *List)
// {
// 	uint8_t i = 0;
// 	uint8_t count = 0;

// 	for(i = 0; i < MAX_NODE; i++)
// 	{	/*初始化队列数据域*/
// 		List->LNode[i].Frame_Flag = false;
// 		/*初始化链表节点读写指针*/
// 		List->Wptr = List->Rptr = 0;
// 		/*初始化连接关系*/
// 		List->LNode[i].Next = ++count;
// 	}
// }

/**
 * @brief	串口1对1数据转发
 * @details	
 * @param	None
 * @retval	None
 */
void Uart_DataForward(SEL_CHANNEL Src, SEL_CHANNEL Dest)
{
	uint8_t i = 0;

	for (i = 0; i < COMDATA_SIZE; i++)
	{
		if ((Src == ComData_Array[i].Source_Channel) && (Dest == ComData_Array[i].Target_Channel))
		{
			ComData_Array[i].pHandle();
		}
	}
}

/**
 * @brief	串口事件处理
 * @details	
 * @param	None
 * @retval	None
 */
void Uart_Handle(void)
{
	/*关闭串口4接收中断*/
	// S4CON &= ~S2REN;
	/*数据交换序列1:PLC与RS485进行数据交换*/
	Uart_DataForward(CHANNEL_PLC, CHANNEL_RS485);
	/*打开串口4接收中断*/
	// S4CON |= S2REN;
	/*数据交换序列2:WIFI与PLC进行数据交换*/
	Uart_DataForward(CHANNEL_WIFI, CHANNEL_PLC);
}

/**
 * @brief	PLC数据交付到RS485
 * @details	
 * @param	None
 * @retval	None
 */
void Plc_To_Rs485(void)
{
	// printf("Wptr=%bd,Rptr=%bd,Next=%bd\r\n",COM_UART4.Wptr, COM_UART4.Rptr, COM_UART4.LNode[COM_UART4.Wptr].Next);
	// printf("Wptr=%bd,Rptr=%bd,flag=%bd\r\n", COM_UART4.Wptr, COM_UART4.Rptr, COM_UART4.LNode[COM_UART4.Wptr].Frame_Flag);
	// printf("buffer=0x%x\r\n",COM_UART4.LNode[COM_UART4.Rptr].Rx_Buffer[0]);

	/*STC串口4收到PLC发出的数据*/
	if ((COM_UART4.LNode[COM_UART4.Rptr].Frame_Flag)) //&& (COM_UART4.LNode[COM_UART4.Rptr].Rx_Length)
	{												  
		/*如果串口4接收到的数据帧不是EBM所需的，过滤掉*/
		if (COM_UART4.LNode[COM_UART4.Rptr].Rx_Buffer[0] != MODBUS_SLAVEADDR)
		{	/*标记该接收帧以进行处理*/
			COM_UART4.LNode[COM_UART4.Rptr].Frame_Flag = false;
			/*允许485发送*/
			USART3_EN = 1;
			/*数据转发给RS485时，数据长度+1，可以保证MAX3485芯片能够最后一位数据刚好不停止在串口的停止位上*/
			Uartx_SendStr(&Uart3, COM_UART4.LNode[COM_UART4.Rptr].Rx_Buffer, COM_UART4.LNode[COM_UART4.Rptr].Rx_Length + 1U);
			/*接收到数据长度置为0*/
			COM_UART4.LNode[COM_UART4.Rptr].Rx_Length = 0;
			/*发送中断结束后，清空对应接收缓冲区*/
			memset(&COM_UART4.LNode[COM_UART4.Rptr].Rx_Buffer[0], 0, MAX_SIZE);
			/*发送完一帧数据后拉低*/
			USART3_EN = 0;
			/*读指针指到下一个节点*/
			SET_RPTR(4);
		}

		/*目标设备发出应答*/
		if ((COM_UART3.LNode[COM_UART3.Rptr].Frame_Flag)) //&& (COM_UART3.LNode[COM_UART3.Rptr].Rx_Length)
		{
			/*标记该接收帧已经进行处理*/
			COM_UART3.LNode[COM_UART3.Rptr].Frame_Flag = false;
			/*数据返回给请求对象*/
			Uartx_SendStr(&Uart4, COM_UART3.LNode[COM_UART3.Rptr].Rx_Buffer, COM_UART3.LNode[COM_UART3.Rptr].Rx_Length);
			/*接收到数据长度置为0*/
			COM_UART3.LNode[COM_UART3.Rptr].Rx_Length = 0;
			/*发送中断结束后，清空对应接收缓冲区*/
			memset(&COM_UART3.LNode[COM_UART3.Rptr].Rx_Buffer[0], 0, MAX_SIZE);
			/*读指针指到下一个节点*/
			SET_RPTR(3);
		}
	}
}

/**
 * @brief	WIFI数据交付到PLC
 * @details	
 * @param	None
 * @retval	None
 */
void Wifi_To_Plc(void)
{
	/*STC串口2收到WIIF发出的数据*/
	if (COM_UART2.LNode[COM_UART2.Rptr].Frame_Flag )//&& (COM_UART2.LNode[COM_UART2.Rptr].Rx_Length)
	{ /*标记该接收帧以进行处理*/
		COM_UART2.LNode[COM_UART2.Rptr].Frame_Flag = false;
		/*串口2收到的数据从串口4转发给PLC*/
		Uartx_SendStr(&Uart4, COM_UART2.LNode[COM_UART2.Rptr].Rx_Buffer, COM_UART2.LNode[COM_UART2.Rptr].Rx_Length);
		/*接收到数据长度置为0*/
		COM_UART2.LNode[COM_UART2.Rptr].Rx_Length = 0;
		/*发送中断结束后，清空对应接收缓冲区*/
		memset(&COM_UART2.LNode[COM_UART2.Rptr].Rx_Buffer[0], 0, MAX_SIZE);
		/*读指针指到下一个节点*/
		SET_RPTR(2);
		
		/*数据转发完毕后，等待目标设备响应*/
		if (COM_UART4.LNode[COM_UART4.Rptr].Frame_Flag)
		{
			/*如果串口4接收到的数据帧不是云平台所需的，过滤掉*/
			if (COM_UART4.LNode[COM_UART4.Rptr].Rx_Buffer[0] == MODBUS_SLAVEADDR)
			{
				/*标记该接收帧已经进行处理*/
				COM_UART4.LNode[COM_UART4.Rptr].Frame_Flag = false;
				/*数据返回给请求对象*/
				Uartx_SendStr(&Uart2, COM_UART4.LNode[COM_UART4.Rptr].Rx_Buffer, COM_UART4.LNode[COM_UART4.Rptr].Rx_Length);
				/*接收到数据长度置为0*/
				COM_UART4.LNode[COM_UART4.Rptr].Rx_Length = 0;
				/*发送中断结束后，清空对应接收缓冲区*/
				memset(&COM_UART4.LNode[COM_UART4.Rptr].Rx_Buffer[0], 0, MAX_SIZE);
				/*读指针指到下一个节点*/
				SET_RPTR(4);
			}
		}
	}	
}

/*禁止编译器优化该模块*/
// #pragma OPTIMIZE(0)

/**
 * @brief	获取16bitCRC码
 * @details	
 * @param	*ptr:参与校验数据指针,length:数据长度,init_dat:参与运算目标数据
 * @retval	None
 */
uint16_t getCrc16(uint8_t *ptr, uint8_t length, uint16_t init_dat)
{
	uint8_t i = 0;
	uint16_t j = 0;
	uint16_t crc16 = init_dat;

	for (i = 0; i < length; i++)
	{
		crc16 ^= *ptr++;

		for (j = 0; j < 8; j++)
		{
			if (crc16 & 0x0001)
			{
				crc16 = (crc16 >> 1) ^ 0xa001;
			}
			else
			{
				crc16 = crc16 >> 1;
			}
		}
	}
	return (crc16);
}
