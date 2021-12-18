#include "report.h"
#include "usart.h"

void Public_DataHandle(SEL_CHANNEL src, SEL_CHANNEL dest);
void Uart_DataForward(SEL_CHANNEL Src, SEL_CHANNEL Dest);
void Plc_To_Rs485(void);
void Wifi_To_Plc(void);
void Rs485_to_Plc(void);

/*定义当前串口交换序列*/
// const ComData_Handle ComData_Array[] =
// 	{
// 		{CHANNEL_PLC, CHANNEL_RS485, Plc_To_Rs485},
// 		{CHANNEL_WIFI, CHANNEL_PLC, Wifi_To_Plc},
// 		//	{CHANNEL_LAN,  CHANNEL_PLC,   Lan_To_Plc}
// };

const ComData_Handle ComData_Array[] =
	{
		// {CHANNEL_PLC, CHANNEL_RS485, Public_DataHandle},
		{CHANNEL_WIFI, CHANNEL_PLC, Public_DataHandle},
		{CHANNEL_LAN, CHANNEL_PLC, Public_DataHandle},
		{CHANNEL_RS485, CHANNEL_PLC, Public_DataHandle}};

#define COMDATA_SIZE (sizeof(ComData_Array) / sizeof(ComData_Handle))

/*创建4条链队*/
Uart_List Uart_LinkList[MAX_LQUEUE];

/**
 * @brief	初始化静态链队
 * @details
 * @param	*List:当前链队指针
 * @retval	None
 */
void Init_ListQueue(Uart_List *List)
{
	uint8_t i = 0;

	for (i = 0; i < MAX_NODE; i++)
	{
		/*初始化队列数据域*/
		List->LNode[i].Source_Channel = CHANNEL_IDLE;
		List->LNode[i].Target_Channel = CHANNEL_IDLE;
		List->LNode[i].Frame_Flag = false;
		List->LNode[i].Timer_Flag = false;
		List->LNode[i].Rx_Length = 0;
		List->LNode[i].OverTime = MAX_SILENCE;
		/*清空对应数据缓冲区*/
		memset(&List->LNode[i].Rx_Buffer[0], 0, MAX_SIZE);
	}
	/*初始化链表节点读写指针*/
	List->Wptr = List->Rptr = 0;
}

/**
 * @brief	串口1对1数据转发
 * @details
 * @param	None
 * @retval	None
 */
// void Uart_DataForward(SEL_CHANNEL Src, SEL_CHANNEL Dest)
// {
// 	uint8_t i = 0;

// 	for (i = 0; i < COMDATA_SIZE; i++)
// 	{
// 		if ((Src == ComData_Array[i].Source_Channel) && (Dest == ComData_Array[i].Target_Channel))
// 		{
// 			ComData_Array[i].pHandle();
// 		}
// 	}
// }

/**
 * @brief	串口事件处理
 * @details
 * @param	None
 * @retval	None
 */
void Uart_Handle(void)
{
	static uint8_t i = 0;

	// /*关闭串口4接收中断*/
	// // S4CON &= ~S4REN;

	// for (i = 0; i < COMDATA_SIZE; i++)
	// {
	// 	ComData_Array[i].pHandle(ComData_Array[i].Source_Channel, ComData_Array[i].Target_Channel);
	// }
	// ComData_Array[0].pHandle(ComData_Array[0].Source_Channel, ComData_Array[0].Target_Channel);
	// ComData_Array[1].pHandle(ComData_Array[1].Source_Channel, ComData_Array[1].Target_Channel);
	// ComData_Array[2].pHandle(ComData_Array[2].Source_Channel, ComData_Array[2].Target_Channel);
	// USART3_EN = 1;
	// Uartx_SendStr(&Uart3, "\x01\x02\x03", 3);
	// USART3_EN = 0;
	/*当前无请求通道*/
	current_request_channel = CHANNEL_IDLE;
	// Rs485_to_Plc();
	Public_DataHandle(CHANNEL_RS485, CHANNEL_PLC);
	// Public_DataHandle(CHANNEL_WIFI, CHANNEL_PLC);
	// Public_DataHandle(CHANNEL_LAN, CHANNEL_PLC);
}

/*禁止编译器优化该模块*/
// #pragma OPTIMIZE(0)
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
		p = &COM_UART4;
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

/**
 * @brief	请求发送方源数据处理
 * @details
 * @param	psrc 数据源请求通道
 * @param   peuart 目标串口
 * @retval	None
 */
static void Source_DataHandle(Uart_List *psrc, Uart_HandleTypeDef *peuart)
{
	if ((psrc == NULL) || (peuart == NULL))
	{
		return;
	}
	/*检测发起请求接收缓冲区*/
	if ((psrc->LNode[psrc->Rptr].Frame_Flag))
	{
		/*检查当前节点源地址和目标地址是否与正在执行上目标相同*/
		// if ((psrc->LNode[psrc->Rptr].Source_Channel != src) || (psrc->LNode[psrc->Rptr].Target_Channel != dest))
		// {
		// 	return;
		// }
		/*标记该接收帧以进行处理*/
		psrc->LNode[psrc->Rptr].Frame_Flag = false;
		if (psrc->LNode[psrc->Rptr].Target_Channel == CHANNEL_RS485)
		{
			/*允许485发送*/
			USART3_EN = 1;
			/*数据转发给RS485时，数据长度+1，可以保证MAX3485芯片能够最后一位数据刚好不停止在串口的停止位上*/
			psrc->LNode[psrc->Rptr].Rx_Length += 1U;
		}
		/*启动对应端硬件数据转发*/
		Uartx_SendStr(peuart, psrc->LNode[psrc->Rptr].Rx_Buffer, psrc->LNode[psrc->Rptr].Rx_Length);
		/*接收到数据长度置为0*/
		psrc->LNode[psrc->Rptr].Rx_Length = 0;
		/*发送中断结束后，清空对应接收缓冲区*/
		memset(&psrc->LNode[psrc->Rptr].Rx_Buffer[0], 0, MAX_SIZE);
		if (psrc->LNode[psrc->Rptr].Target_Channel == CHANNEL_RS485)
		{
			/*发送完一帧数据后拉低*/
			USART3_EN = 0;
		}
		/*读指针指到下一个节点*/
		psrc->Rptr = ((psrc->Rptr + 1U) % MAX_NODE);
	}
}

/**
 * @brief	目标响应方数据处理
 * @details
 * @param	pdest 数据源请求通道
 * @param   psuart 目标串口
 * @retval	None
 */
static void Target_DataHandle(Uart_List *pdest, Uart_HandleTypeDef *psuart)
{
	if ((pdest == NULL) || (psuart == NULL))
	{
		return;
	}
	/*目标设备发出应答*/
	if ((pdest->LNode[pdest->Rptr].Frame_Flag))
	{
		/*检查目标端是否与当前节点数据目标相同*/
		// if ((pdest->LNode[pdest->Rptr].Source_Channel != dest) || (pdest->LNode[pdest->Rptr].Target_Channel != src))
		// {
		// 	return;
		// }
		/*标记该接收帧已经进行处理*/
		pdest->LNode[pdest->Rptr].Frame_Flag = false;
		if (pdest->LNode[pdest->Rptr].Target_Channel == CHANNEL_RS485)
		{
			/*允许485发送*/
			USART3_EN = 1;
			/*数据转发给RS485时，数据长度+1，可以保证MAX3485芯片能够最后一位数据刚好不停止在串口的停止位上*/
			pdest->LNode[pdest->Rptr].Rx_Length += 1U;
		}
		/*数据返回给请求对象*/
		Uartx_SendStr(psuart, pdest->LNode[pdest->Rptr].Rx_Buffer, pdest->LNode[pdest->Rptr].Rx_Length);
		/*接收到数据长度置为0*/
		pdest->LNode[pdest->Rptr].Rx_Length = 0;
		/*发送中断结束后，清空对应接收缓冲区*/
		memset(&pdest->LNode[pdest->Rptr].Rx_Buffer[0], 0, MAX_SIZE);
		if (pdest->LNode[pdest->Rptr].Target_Channel == CHANNEL_RS485)
		{
			/*发送完一帧数据后拉低*/
			USART3_EN = 0;
		}
		/*读指针指到下一个节点*/
		pdest->Rptr = ((pdest->Rptr + 1U) % MAX_NODE);
	}
}

/**
 * @brief	数据帧公共转发
 * @details
 * @param	src 数据源请求通道
 * @param   dest 数据交付通道
 * @retval	None
 */
void Public_DataHandle(SEL_CHANNEL src, SEL_CHANNEL dest)
{
	Source_DataHandle(Get_Target_Channel(src), Get_Target_Uart(dest));
	Target_DataHandle(Get_Target_Channel(dest), Get_Target_Uart(src));
}

void Rs485_to_Plc(void)
{
	/*STC串口4收到PLC发出的数据*/
	if ((COM_UART3.LNode[COM_UART3.Rptr].Frame_Flag)) //&& (COM_UART4.LNode[COM_UART4.Rptr].Rx_Length)
	{
		/*如果串口4接收到的数据帧不是EBM所需的，过滤掉*/
		// if (COM_UART3.LNode[COM_UART3.Rptr].Rx_Buffer[0] != MODBUS_SLAVEADDR)
		{ /*标记该接收帧以进行处理*/
			COM_UART3.LNode[COM_UART3.Rptr].Frame_Flag = false;
			/*允许485发送*/
			// USART3_EN = 1;
			/*数据转发给RS485时，数据长度+1，可以保证MAX3485芯片能够最后一位数据刚好不停止在串口的停止位上*/
			Uartx_SendStr(&Uart4, COM_UART3.LNode[COM_UART3.Rptr].Rx_Buffer, COM_UART3.LNode[COM_UART3.Rptr].Rx_Length + 1U);
			/*接收到数据长度置为0*/
			COM_UART3.LNode[COM_UART3.Rptr].Rx_Length = 0;
			/*发送中断结束后，清空对应接收缓冲区*/
			memset(&COM_UART3.LNode[COM_UART3.Rptr].Rx_Buffer[0], 0, MAX_SIZE);
			/*发送完一帧数据后拉低*/
			// USART3_EN = 0;
			/*读指针指到下一个节点*/
			SET_RPTR(3);
		}

		/*目标设备发出应答*/
		if ((COM_UART4.LNode[COM_UART4.Rptr].Frame_Flag)) //&& (COM_UART3.LNode[COM_UART3.Rptr].Rx_Length)
		{
			/*标记该接收帧已经进行处理*/
			COM_UART4.LNode[COM_UART4.Rptr].Frame_Flag = false;
			/*允许485发送*/
			USART3_EN = 1;
			/*数据返回给请求对象*/
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
