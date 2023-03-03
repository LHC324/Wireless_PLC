#include "report.h"
#include "usart.h"

void Public_DataHandle(SEL_CHANNEL src, SEL_CHANNEL dest);
void Uart_DataForward(SEL_CHANNEL Src, SEL_CHANNEL Dest);

/*定义当前串口交换序列*/
const ComData_Handle code ComData_Array[] =
	{
		// {CHANNEL_PLC, CHANNEL_RS485, Public_DataHandle},
		{CHANNEL_WIFI, CHANNEL_PLC, Public_DataHandle},
		{CHANNEL_LAN, CHANNEL_PLC, Public_DataHandle},
		{CHANNEL_RS485, CHANNEL_PLC, Public_DataHandle},
		/*作为主机时情况*/
		{CHANNEL_PLC, CHANNEL_WIFI, Public_DataHandle},
		{CHANNEL_PLC, CHANNEL_LAN, Public_DataHandle},
		{CHANNEL_PLC, CHANNEL_RS485, Public_DataHandle}
	};

#define COMDATA_SIZE (sizeof(ComData_Array) / sizeof(ComData_Handle))

/*创建4条链队*/
Uart_List xdata Uart_LinkList[MAX_LQUEUE] = {0};
#if USING_PORT0_SINGLE
Uart_List_X xdata Uart_Port0 = {0};
#endif

#if 0
/**
 * @brief	初始化静态链队
 * @details
 * @param	*List:当前链队指针
 * @retval	None
 */
void Init_ListQueue(Uart_List *List)
{
	uint8_t j = 0;

	for (j = 0; j < MAX_NODE; j++)
	{
		/*初始化队列数据域*/
		List->LNode[j].Source_Channel = CHANNEL_IDLE;
		List->LNode[j].Target_Channel = CHANNEL_IDLE;
		List->LNode[j].Frame_Flag = false;
		List->LNode[j].Timer_Flag = false;
		List->LNode[j].Rx_Length = 0;
		List->LNode[j].OverTime = MAX_SILENCE;
		memset(&List->LNode[j].Rx_Buffer[0], 0, MAX_SIZE);
	}
	// List->Buffer_Size = buf_size;
	/*初始化链表节点读写指针*/
	List->Wptr = List->Rptr = 0;
}
#endif

/**
 * @brief	串口事件处理
 * @details
 * @param	None
 * @retval	None
 */
void Uart_Handle(void)
{
	uint8_t i = 0;
	
	if (System_Parameter.WorkMode == SLAVE)
	{
		if (System_Parameter.Ppistate) //ppi模式：握手速度必须要快
		{
			Public_DataHandle(CHANNEL_RS485, CHANNEL_PLC);
			return;
		}
		else
			for (i = 0; i < COMDATA_SIZE - 3U; i++)
			{	
				ComData_Array[i].pHandle(ComData_Array[i].Source_Channel, 			
				ComData_Array[i].Target_Channel);
			}
	}
	else
	{
		switch (System_Parameter.CurrentSlave)
		{
			case ETHERNET_ID: 
			{
				ComData_Array[3].pHandle(ComData_Array[3].Source_Channel, ComData_Array[3].Target_Channel);
			}break;
			case WIFI_ID:
			{
				ComData_Array[4].pHandle(ComData_Array[4].Source_Channel, ComData_Array[4].Target_Channel);
			}break;
			case RS485_ID:
			{
				ComData_Array[5].pHandle(ComData_Array[5].Source_Channel, ComData_Array[5].Target_Channel);
			}break;
			default : break;
		}
	}
}

/*禁止编译器优化该模块*/
// #pragma OPTIMIZE(2)
/**
 * @brief	获得目标通道链表地址
 * @details
 * @param	channel 通道号
 * @retval	p 指向链表的指针
 */
static Uart_List *Get_Target_Channel(channel)
{
	Uart_List *p = NULL;
	switch (channel)
	{
	case CHANNEL_LAN:
		p = &COM_UART1;
		break;
	case CHANNEL_WIFI:
		p = &COM_UART2;
		break;
	case CHANNEL_RS485:
		p = &COM_UART3;
		break;
	case CHANNEL_PLC:
#if !USING_PORT0_SINGLE
		p = &COM_UART4;
#endif
		break;
	default:
		break;
	}
	return p;
}

/**
 * @brief	获得目标通道对应串口
 * @details
 * @param	channel 通道号
 * @retval	p 指向链表的指针
 */
static Uart_HandleTypeDef *Get_Target_Uart(channel)
{
	Uart_HandleTypeDef *p = NULL;
	switch (channel)
	{
	case CHANNEL_LAN:
		p = &Uart1;
		break;
	case CHANNEL_WIFI:
		p = &Uart2;
		break;
	case CHANNEL_RS485:
		p = &Uart3;
		break;
	case CHANNEL_PLC:
		p = &Uart4;
		break;
	default:
		break;
	}
	return p;
}

#if USING_PORT0_SINGLE
/**
 * @brief	数据帧公共转发
 * @details
 * @param	src 数据源请求通道
 * @param   puart 目标串口句柄
 * @retval	None
 */
static void Port0_Send(SEL_CHANNEL src, 
					   Uart_HandleTypeDef * const puart) 
{
	if (COM_UART4.Target_Channel != src)
	{
		return;
	}

	/*目标设备发出应答*/
	if (COM_UART4.Frame_Flag)
	{
		/*标记该接收帧已经进行处理*/
		COM_UART4.Frame_Flag = false;
#if (USE_PRINTF_DEBUG)
		printf("2->>source %bd, target %bd, src %bd, len %d.\r\n",
		COM_UART4.Source_Channel, COM_UART4.Target_Channel, src, COM_UART4.Rx_Length);
#endif		
		if (src == CHANNEL_RS485)
		{
			/*允许485发送*/
			USART3_EN = 1;
			/*数据转发给RS485时，数据长度+1，可以保证MAX3485芯片能够最后一位数据刚好不停止在串口的停止位上*/
			COM_UART4.Rx_Length++;
		}
		/*数据返回给请求对象*/
		Uartx_SendStr(puart, (uint8_t *)&COM_UART4.Rx_Buffer[0], COM_UART4.Rx_Length);
		/*接收到数据长度置为0*/
		COM_UART4.Rx_Length = 0;
		/*发送中断结束后，清空对应接收缓冲区*/
		// memset(&COM_UART4.Rx_Buffer[0], 0, MAX_SIZE);
		if (src == CHANNEL_RS485)
		{
			/*发送完一帧数据后拉低*/
			USART3_EN = 0;
		}
	}
}
#endif


/**
 * @brief	数据帧公共转发
 * @details
 * @param	src 数据源请求通道
 * @param   dest 数据交付通道
 * @retval	None
 */
void Public_DataHandle(SEL_CHANNEL src, SEL_CHANNEL dest) 
{
	Uart_List * const psrc = Get_Target_Channel(src);
	Uart_List * const pdest = Get_Target_Channel(dest);
	Uart_HandleTypeDef * const psuart = Get_Target_Uart(src);
	Uart_HandleTypeDef * const peuart = Get_Target_Uart(dest);
#if !USING_PORT0_SINGLE
	uint8_t i = 0;
	if ((psrc == NULL) || (pdest == NULL) || (psuart == NULL) || (peuart == NULL))
	{
		return;
	}
#else
if ((psrc == NULL) || (psuart == NULL) || (peuart == NULL))
	{
		return;
	}
#endif

#if (USE_PRINTF_DEBUG)
	// printf ("psrc %d, pdest %d, %d, %d, %d, %d\r\n",
	// (uint16_t)psrc, (uint16_t)pdest, (uint16_t)&COM_UART1, (uint16_t)&COM_UART2,
	// (uint16_t)&COM_UART3, (uint16_t)&COM_UART4);
#endif
	/*主机时plc目标通道无法确定*/
	if (System_Parameter.WorkMode == MASTER)
	{
		psrc->LNode[psrc->Rptr].Target_Channel = dest;
	}
	/*检查当前节点源地址和目标地址是否与正在执行上目标相同*/
	if ((psrc->LNode[psrc->Rptr].Source_Channel == src) && 
		(psrc->LNode[psrc->Rptr].Target_Channel == dest))
	{
		/*检测发起请求接收缓冲区*/
		if (psrc->LNode[psrc->Rptr].Frame_Flag)
		{
#if (USE_PRINTF_DEBUG)
			printf("1->>source %bd, target %bd, ptr %bd, len %d\r\n",
			psrc->LNode[psrc->Rptr].Source_Channel, psrc->LNode[psrc->Rptr].Target_Channel, 
			psrc->Rptr, psrc->LNode[psrc->Rptr].Rx_Length);
#endif
			/*标记该接收帧以进行处理*/
			psrc->LNode[psrc->Rptr].Frame_Flag = false;
			if (dest == CHANNEL_RS485)
			{
				/*允许485发送*/
				USART3_EN = 1;
				/*数据转发给RS485时，数据长度+1，可以保证MAX3485芯片能够最后一位数据刚好不停止在串口的停止位上*/
				psrc->LNode[psrc->Rptr].Rx_Length++;
			}
			/*启动对应端硬件数据转发*/
			Uartx_SendStr(peuart, psrc->LNode[psrc->Rptr].Rx_Buffer, psrc->LNode[psrc->Rptr].Rx_Length);
			/*接收到数据长度置为0*/
			psrc->LNode[psrc->Rptr].Rx_Length = 0;
			/*发送中断结束后，清空对应接收缓冲区*/
			// memset(&psrc->LNode[psrc->Rptr].Rx_Buffer[0], 0, MAX_SIZE);
			if (dest == CHANNEL_RS485)
			{
				/*发送完一帧数据后拉低*/
				USART3_EN = 0;
			}
			/*读指针指到下一个节点*/
			psrc->Rptr = ((++psrc->Rptr) & (MAX_NODE - 1));
		}
	}
#if USING_PORT0_SINGLE
	Port0_Send(src, psuart);
#else
	for (i = 0; i < MAX_NODE; i++)
	{
		if ((pdest->LNode[i].Source_Channel != dest) || (pdest->LNode[i].Target_Channel != src))
		{
			continue;
		}
		/*目标设备发出应答*/
		if (pdest->LNode[i].Frame_Flag)
		{
#if (USE_PRINTF_DEBUG)
			printf("2->>source %bd, target %bd, ptr %bd, len %d\r\n\r\n",
			pdest->LNode[i].Source_Channel, pdest->LNode[i].Target_Channel, 
			pdest->Rptr, pdest->LNode[pdest->Rptr].Rx_Length);
#endif		
			/*标记该接收帧已经进行处理*/
			pdest->LNode[i].Frame_Flag = false;
			if (src == CHANNEL_RS485)
			{
				/*允许485发送*/
				USART3_EN = 1;
				/*数据转发给RS485时，数据长度+1，可以保证MAX3485芯片能够最后一位数据刚好不停止在串口的停止位上*/
				pdest->LNode[i].Rx_Length += 1U;
			}
			/*数据返回给请求对象*/
			Uartx_SendStr(psuart, pdest->LNode[i].Rx_Buffer, pdest->LNode[i].Rx_Length);
			/*接收到数据长度置为0*/
			pdest->LNode[i].Rx_Length = 0;
			/*发送中断结束后，清空对应接收缓冲区*/
			// memset(&pdest->LNode[i].Rx_Buffer[0], 0, MAX_SIZE);
			if (src == CHANNEL_RS485)
			{
				/*发送完一帧数据后拉低*/
				USART3_EN = 0;
			}
		}
	}
#endif
}


/*禁止编译器优化该模块*/
#pragma OPTIMIZE(9)

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
