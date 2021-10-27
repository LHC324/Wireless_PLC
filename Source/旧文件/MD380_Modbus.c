#include "MD380_Modbus.h"
#include "string.h"
#include "usart.h"

MODS_T g_tModS;

Md_struct g_Mdbuff[2] = {		//2个变频器
	{MD380_SLAVEADDR1, {{RUNNING_SPEED_ADDR, MODS_SPEED1_ADDR,0x00}, {OUTPUT_VOLTAGE_ADDR,MODS_VOLTAGE_ADDR,0x00}, \
		                {OUTPUT_CURRENT_ADDR,MODS_CURRENT_ADDR,0x00}, {FAULT_ADDR,MODS_ERROR_ADDR,0x00}}
	},    //第一个变频器
	{MD380_SLAVEADDR2, {{RUNNING_SPEED_ADDR,MODS_SPEED2_ADDR,0x00}, {OUTPUT_VOLTAGE_ADDR,MODS_VOLTAGE2_ADDR,0x00}, \
					    {OUTPUT_CURRENT_ADDR,MODS_CURRENT2_ADDR,0x00}, {FAULT_ADDR,MODS_ERROR2_ADDR,0x00}}
	},    //第二个变频器
};


uint16_t Mods_RigAddrNow;   //有一些Mosbus主站指令回复没有寄存器地址
uint8_t Mods_UsartNow;    //当前串口


#define InverterQuantity (sizeof(g_Inverter)/sizeof(Md_struct))
   

/*
*********************************************************************************************************
*	
*	
*	
*	
*********************************************************************************************************
*/
void MODS_SlaveInit(void)
{
//	uint8_t i = 0;
//	uint8_t j = 0;
	
    Mods_UsartNow = USART3;    //缺省为串口3
	
//	for(i = 0;i < InverterQuantity;i++){
//		g_Mdbuff[i].slaveaddr = g_Inverter[i].slaveaddr;
//		
//		for(j = 0;j < sizeof(Md_parm) >> 1;j++){
//			g_Mdbuff[i].modsparm[j].Mdrigaddr = g_Inverter[i].modsparm[j].Mdrigaddr;
//			g_Mdbuff[i].modsparm[j].addr = g_Inverter[i].modsparm[j].addr;
//			g_Mdbuff[i].modsparm[j].value = g_Inverter[i].modsparm[j].value;
//		}	
//	}
}


/*
*********************************************************************************************************
*	函数名:   getCrc16
*	功能说明: CRC16检测
*	形    参: 无
*	返回值：无
*********************************************************************************************************
*/
uint16_t getCrc16(const uint8_t *ptr, uint8_t length, uint16_t IniDat)
{
    uint8_t iix;
    uint16_t iiy;
    uint16_t crc16 = IniDat;

    for(iix = 0; iix < length; iix++)
    {
        crc16 ^= *ptr++;

        for(iiy = 0; iiy < 8; iiy++)
        {
            if(crc16 & 0x0001)
            {
                crc16 = (crc16 >> 1) ^ 0xa001;
            }
            else
            {
                crc16 = crc16 >> 1;
            }
        }
    }

    return(crc16);
}
/*
*********************************************************************************************************
*	函数名:   checkCrc16
*	功能说明: CRC16??
*	形    参: 无
*	返回值： 无
*********************************************************************************************************
*/
//uint8_t checkCrc16(const uint8_t *ptr, uint8_t length)
//{
//    uint16_t crc1;
//    uint16_t crc2;

//    crc1 = getCrc16(ptr, length - 2, 0xFFFF);

//    crc2 = *(ptr + length - 1) << 8;        // CRC MSB
//    crc2 += *(ptr + length - 2);            // CRC LSB

//    // ??????????0xCCCC?0xcccc??????CRC
//    if((crc1 == crc2) || (crc2 == 0xCCCC) || (crc2 == 0xcccc))
//        return 1;

//    return 0;
//}


/*
*********************************************************************************************************
*	
*	
*	
*	
*********************************************************************************************************
*/
void MODS_ReciveNew(uint8_t * rxBuf, uint16_t Len)
{
    uint16_t i;

    for(i = 0; i < Len; i++)
    {
        g_tModS.RxBuf[i] = rxBuf[i];
    }

    g_tModS.RxCount = Len;
}



/*
*********************************************************************************************************
*	
*	
*	
*	
*********************************************************************************************************
*/
void MODS_SendWithCRC(uint8_t *_pBuf, uint8_t _ucLen)
{
    uint16_t crc;
    uint8_t buf[MOD_TX_BUF_SIZE];

    memcpy(buf, _pBuf, _ucLen);
    crc = getCrc16(_pBuf, _ucLen, 0xffff);
    buf[_ucLen++] = crc;
    buf[_ucLen++] = crc >> 8;

    switch(Mods_UsartNow)
    {
//			 case USART1: Uart1SendStr(buf,_ucLen); break;
//        case USART2:
//            Uart2SendStr(buf, _ucLen);
//            break;

        case USART3: //发送命令请求变频器数据
//            Uart3SendStr(buf, _ucLen);
		    Uartx_SendStr(&Uart3,&buf,_ucLen+1); //485端口数据需要额外加一位
            break;

        case USART4: //把从变频器回应的数据处理后存入PLC
//            Uart4SendStr(buf, _ucLen);  
			 Uartx_SendStr(&Uart4,&buf,_ucLen); 
//		    memcpy(&buffer1, &buf, _ucLen); //测试
            break;

        default:
            break;
    }
}

//void MODS_Host_01(uint16_t slaveaddr, uint16_t startaddr, uint16_t length) //离散输出
//{
//    g_tModS.TxCount = 0;
//    g_tModS.TxBuf[g_tModS.TxCount++] = slaveaddr;
//    g_tModS.TxBuf[g_tModS.TxCount++] = 0x01;
//    g_tModS.TxBuf[g_tModS.TxCount++] = startaddr >> 8;
//    g_tModS.TxBuf[g_tModS.TxCount++] = startaddr;
//    g_tModS.TxBuf[g_tModS.TxCount++] = length >> 8;
//    g_tModS.TxBuf[g_tModS.TxCount++] = length;

//    MODS_SendWithCRC(g_tModS.TxBuf, g_tModS.TxCount);

//}


//void MODS_Host_02(uint16_t slaveaddr, uint16_t startaddr, uint16_t length)		//离散输入
//{
//    g_tModS.TxCount = 0;
//    g_tModS.TxBuf[g_tModS.TxCount++] = slaveaddr;
//    g_tModS.TxBuf[g_tModS.TxCount++] = 0x02;
//    g_tModS.TxBuf[g_tModS.TxCount++] = startaddr >> 8;
//    g_tModS.TxBuf[g_tModS.TxCount++] = startaddr;
//    g_tModS.TxBuf[g_tModS.TxCount++] = length >> 8;
//    g_tModS.TxBuf[g_tModS.TxCount++] = length;

//    MODS_SendWithCRC(g_tModS.TxBuf, g_tModS.TxCount);

//}

void MODS_Host_03(uint16_t slaveaddr, uint16_t startaddr, uint16_t length) //保持寄存器
{
    g_tModS.TxCount = 0;
    g_tModS.TxBuf[g_tModS.TxCount++] = slaveaddr;
    g_tModS.TxBuf[g_tModS.TxCount++] = 0x03;
    g_tModS.TxBuf[g_tModS.TxCount++] = startaddr >> 8;
    g_tModS.TxBuf[g_tModS.TxCount++] = startaddr;
    g_tModS.TxBuf[g_tModS.TxCount++] = length >> 8;
    g_tModS.TxBuf[g_tModS.TxCount++] = length;

    MODS_SendWithCRC(g_tModS.TxBuf, g_tModS.TxCount);
}


//void MODS_Host_04(uint16_t slaveaddr, uint16_t startaddr, uint16_t length)		//模拟输入
//{
//    g_tModS.TxCount = 0;
//    g_tModS.TxBuf[g_tModS.TxCount++] = slaveaddr;
//    g_tModS.TxBuf[g_tModS.TxCount++] = 0x04;
//    g_tModS.TxBuf[g_tModS.TxCount++] = startaddr >> 8;
//    g_tModS.TxBuf[g_tModS.TxCount++] = startaddr;
//    g_tModS.TxBuf[g_tModS.TxCount++] = length >> 8;
//    g_tModS.TxBuf[g_tModS.TxCount++] = length;

//    MODS_SendWithCRC(g_tModS.TxBuf, g_tModS.TxCount);
//}


//void MODS_Host_05(uint16_t slaveaddr, uint16_t startaddr, uint8_t power)			//写单个线圈
//{
//    g_tModS.TxCount = 0;
//    g_tModS.TxBuf[g_tModS.TxCount++] = slaveaddr;
//    g_tModS.TxBuf[g_tModS.TxCount++] = 0x05;
//    g_tModS.TxBuf[g_tModS.TxCount++] = startaddr >> 8;
//    g_tModS.TxBuf[g_tModS.TxCount++] = startaddr;

//    if(power)
//    {
//        g_tModS.TxBuf[g_tModS.TxCount++] = 0xff;
//    }
//    else
//    {
//        g_tModS.TxBuf[g_tModS.TxCount++] = 0x00;
//    }

//    g_tModS.TxBuf[g_tModS.TxCount++] = 0x00;

//    MODS_SendWithCRC(g_tModS.TxBuf, g_tModS.TxCount);
//}


//void MODS_Host_06(uint16_t slaveaddr, uint16_t startaddr, uint16_t wdata)	 //写单个寄存器
//{
//    g_tModS.TxCount = 0;
//    g_tModS.TxBuf[g_tModS.TxCount++] = slaveaddr;
//    g_tModS.TxBuf[g_tModS.TxCount++] = 0x06;
//    g_tModS.TxBuf[g_tModS.TxCount++] = startaddr >> 8;
//    g_tModS.TxBuf[g_tModS.TxCount++] = startaddr;
//    g_tModS.TxBuf[g_tModS.TxCount++] = wdata >> 8;
//    g_tModS.TxBuf[g_tModS.TxCount++] = wdata;

//    MODS_SendWithCRC(g_tModS.TxBuf, g_tModS.TxCount);
//}


//void MODS_Host_0F(uint16_t slaveaddr, uint16_t startaddr, uint16_t length, uint16_t bytes, uint8_t* wdata) //写多个线圈
//{
//    uint8_t i;
//    g_tModS.TxCount = 0;
//    g_tModS.TxBuf[g_tModS.TxCount++] = slaveaddr;
//    g_tModS.TxBuf[g_tModS.TxCount++] = 0x0F;
//    g_tModS.TxBuf[g_tModS.TxCount++] = startaddr >> 8;
//    g_tModS.TxBuf[g_tModS.TxCount++] = startaddr;
//    g_tModS.TxBuf[g_tModS.TxCount++] = length >> 8;
//    g_tModS.TxBuf[g_tModS.TxCount++] = length;
//    g_tModS.TxBuf[g_tModS.TxCount++] = bytes;

//    for(i = 0 ; i < bytes; i++)
//    {
//        g_tModS.TxBuf[g_tModS.TxCount++] = wdata[i];
//    }

//    MODS_SendWithCRC(g_tModS.TxBuf, g_tModS.TxCount);
//}

/*
*********************************************************************************************************
*	函 数 名: MODH_Send10
*	功能说明: 发送10H指令，连续写多个保持寄存器. 最多一次支持23个寄存器。
*	形    参: _addr : 从站地址
*			  _reg : 寄存器编号
*			  _num : 寄存器个数n (每个寄存器2个字节) 值域
*			  _buf : n个寄存器的数据。长度 = 2 * n
*	返 回 值: 无
*********************************************************************************************************
*/
void MODS_Host_10(uint16_t slaveaddr, uint16_t startaddr, uint16_t length, uint8_t *wdata)		//写多个寄存器
{
    uint8_t i;
    g_tModS.TxCount = 0;
    g_tModS.TxBuf[g_tModS.TxCount++] = slaveaddr;
    g_tModS.TxBuf[g_tModS.TxCount++] = 0x10;
    g_tModS.TxBuf[g_tModS.TxCount++] = startaddr >> 8;
    g_tModS.TxBuf[g_tModS.TxCount++] = startaddr;
    g_tModS.TxBuf[g_tModS.TxCount++] = length >> 8;
    g_tModS.TxBuf[g_tModS.TxCount++] = length;
    g_tModS.TxBuf[g_tModS.TxCount++] = length * 2;

    for(i = 0 ; i < length * 2; i++)
    {
        g_tModS.TxBuf[g_tModS.TxCount++] = wdata[i];
    }

    MODS_SendWithCRC(g_tModS.TxBuf, g_tModS.TxCount);
}


/*
*********************************************************************************************************
*	函数名:: MODS_Host_Poll
*	功能说明: Modbus主站接收
*	形   参: 无
*	返回值: 无
*********************************************************************************************************
*/
void MODS_Host_Poll(void)
{
    uint16_t addr;
	
    if (g_tModS.RxCount < 4) /* 收到的数据长度小于4则为错误帧 */
    {
        goto err_ret;
    }

    addr = g_tModS.RxBuf[0]; /*从站地址不对则为错误 */

    if(addr != g_Mdbuff[0].slaveaddr && addr != g_Mdbuff[1].slaveaddr)
    {
        goto err_ret;
    }

    MODS_Host_AnalyzeApp();

err_ret:
    g_tModS.RxCount = 0;
}

/*
*********************************************************************************************************
*	函数名:: MODS_Host_AnalyzeApp
*	功能说明: Modbus主站接收处理
*	形   参: 无
*	返回值: 无
*********************************************************************************************************
*/
void MODS_Host_AnalyzeApp(void)
{
    switch (g_tModS.RxBuf[1])	   /* 命令码 */
    {
        case 0x01:
        {
            MODS_Host_01H();
            break;
        }

        case 0x02:
        {
            MODS_Host_02H();
            break;
        }

        case 0x03:
        {
            MODS_Host_03H();
            break;
        }

        case 0x04:
        {
            MODS_Host_04H();
            break;
        }

        case 0x05:
        {
            MODS_Host_05H();
            break;
        }

        case 0x06:
        {
            MODS_Host_06H();
            break;
        }

        case 0x0F:
        {
            MODS_Host_0FH();
            break;
        }

        case 0x10:
        {
            MODS_Host_10H();
            break;
        }

        default:
            break;
    }
}

void MODS_Host_01H(void)
{

}

void MODS_Host_02H(void)
{

}

void MODS_Host_03H(void)
{
    uint16_t rcvdata;
    uint8_t slaveaddr;
    uint8_t datanum;
    uint8_t i;

    slaveaddr = g_tModS.RxBuf[0];
    datanum = g_tModS.RxBuf[2];
    rcvdata = ((uint16_t)g_tModS.RxBuf[4] << 8) | g_tModS.RxBuf[5];

    if(slaveaddr == g_Mdbuff[0].slaveaddr)
    {
        for(i = 0; i < VALUE_NUMS; i++)
        {
            if(Mods_RigAddrNow == g_Mdbuff[0].modsparm[i].Mdrigaddr)
            {
                g_Mdbuff[0].modsparm[i].value = rcvdata;
            }
        }
    }

    if(slaveaddr == g_Mdbuff[1].slaveaddr)
    {
        for(i = 0; i < VALUE_NUMS; i++)
        {
            if(Mods_RigAddrNow == g_Mdbuff[1].modsparm[i].Mdrigaddr)
            {
                g_Mdbuff[1].modsparm[i].value = rcvdata;
            }
        }
    }
}

void MODS_Host_04H(void)
{

}

void MODS_Host_05H(void)
{

}

void MODS_Host_06H(void)
{

}

void MODS_Host_0FH(void)
{

}

void MODS_Host_10H(void)
{

}

void MODS_Host_SetRigAddr(uint16_t regaddr)
{
    Mods_RigAddrNow = regaddr;
}

void MODS_Host_Set_Usart(uint8_t uartval)
{
    Mods_UsartNow = uartval;
}


void Inverter_SaveData_To_PLC(void)
{
    static uint8_t k = 0;
    static uint8_t j = 0;
	static uint8_t count = 0;
	static uint8_t buffer[20] = {0};

    MODS_Host_Set_Usart(USART4);
	
	if(g_Mdbuff[j].modsparm[k].addr == MODS_SPEED2_ADDR){
		
		memset(&buffer[8], 0, 2 * sizeof(uint16_t)); //对第10、11两个寄存器填零
		count += sizeof(uint16_t) * 2;
	}
		buffer[count++] = g_Mdbuff[j].modsparm[k].value >> 8;
		buffer[count++] = g_Mdbuff[j].modsparm[k].value;
	
//    MODS_Host_06(PLC_SLAVEADDRESS, g_Mdbuff[j].modsparm[k].addr, g_Mdbuff[j].modsparm[k].value);
////	MODS_Host_06(PLC_SLAVEADDRESS,g_Mdbuff[0].modsparm[k].addr,g_Mdbuff[0].modsparm[k].value);
	
////	Uartx_SendStr(&Uart1,&buffer1,0x02); //测试用
	
//    k++;

    if(k++ >= VALUE_NUMS -1)
    {
        k = 0;

        if(j++ >= RECTIFIER_NUMS -1)
        {
            j = 0;
        }
    }
	

//	Uartx_SendStr(&Uart1,&buffer,20); //测试用
	
	if((k == 0)	&& (j == 0)){ //变频器数据采集完毕
		count = 0;
		MODS_Host_10(PLC_SLAVEADDRESS, MODS_SPEED1_ADDR, 0x0A, &buffer);		//写多个寄存器
	}
}