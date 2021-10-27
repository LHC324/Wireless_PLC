#ifndef __MD380_MODBUS_H
#define __MD380_MODBUS_H

#include "config.h"

#define  PLC_SLAVEADDRESS			0x02
#define  MOD_RX_BUF_SIZE            200
#define  MOD_TX_BUF_SIZE     		200

#define  DIGITAL_INPUT_SIZE       	50     //数字输入内存大小
#define  DIGITAL_OUTPUT_SIZE		50		 //数字输出内存大小
#define  ANALOG_INPUT_SIZE			200		 //模拟输入内存大小
#define  KEEP_SIZE					500		 //保持寄存器内存大小

/*错误码状态*/
#define RSP_OK				    	0x00	  // 成功
#define RSP_ERR_CMD			  		0x01	  // 不支持的功能码
#define RSP_ERR_REG_ADDR			0x02	  // 寄存器地址错误
#define RSP_ERR_VALUE		  		0x03	  // 数据域错误
#define RSP_ERR_WRITE		  		0x04	  // 写入失败


#define USART1						1                       //串口1
#define USART2						2						//串口2
#define USART3        				3						//串口3
#define USART4						4						//串口4

/*****************************通讯地址************************************/

#define ZH_ADDR						0x1001    //运行频率
#define BUSBAR_VOLTAGE_ADDR			0x1002    //母线电压
#define PID_SETTING_ADDR			0x1010    //PID设置
#define PID_FEEDBACK_ADDR			0x1011    //PID反馈
#define PLC_STEP_ADDR				0x1012    //PLC步骤
#define OUTPUT_VOLTAGE_ADDR			0x1003    //输出电压
#define OUTPUT_CURRENT_ADDR			0x1004	  //输出电流
#define OUTPUT_POWER_ADDR			0x1005    //输出功率
#define OUTPUT_TORQUE_ADDR			0x1006    //输出转矩
#define RUNNING_SPEED_ADDR			0x1007    //运行速度
#define DI_INPUT_FLAG_ADDR			0x1008    //DI输入标志
#define DO_OUTPUT_FLAG_ADDR			0x1009    //DO输出标志
#define AI1_VOLTAGE_ADDR			0x100A    //AI1电压
#define AI2_VOLTAGE_ADDR			0x100B    //AI2电压
#define AI3_VOLTAGE_ADDR			0x100C	  //AI3电压
#define COUNT_INPUT_ADDR			0x100D	  //计数值输入
#define LENGTH_INPUT_ADDR			0x100E    //长度值输入
#define PAYLOAD_SPEED_ADDR			0x100F    //负载速度
#define PULSE_FREQUENCY_ADDR		0x1013    //脉冲频率
#define FEEDBACK_SPEED_ADDR			0x1014    //反馈速度
#define SURPLUS_RUNNINGTIME_ADDR	0x1015    //剩余运行时间
#define AL1_REVISE_VOLTAGE_ADDR		0x1016    //AL1校正前电压
#define AL2_REVISE_VOLTAGE_ADDR   	0x1017    //AI2校正前电压
#define AL3_REVISE_VOLTAGE_ADDR   	0x1018	  //AL3校正前电压
#define WIRE_SPEED_ADDR				0x1019	  //线速度
#define NOW_POWER_ON_TIME_ADDR		0x101A    //当前上电时间
#define NOW_RUNNING_TIME_ADDR		0x101B    //当前运行时间
#define COMMUNICATION_SETTING_ADDR  0x101D    //通讯设定值
#define ACTUAL_FEEDBACK_SPEED_ADDR	0x101E    //实际反馈速度
#define MAIN_FREQUENCY_X_ADDR		0x101F	  //主频率X显示
#define ASSIST_FREQUENCY_Y_ADDR		0x1020	  //辅频率Y显示
#define FAULT_ADDR					0x8000	  //故障码

/************************************************************************/


//****************************MD380定义**********************************//

#define  MODS_SPEED1_ADDR           0x06                //变频器1转速
#define  MODS_SPEED2_ADDR		    0x0C				//变频器2转速
#define  MODS_VOLTAGE_ADDR			0x07				//变频器1电压
#define  MODS_VOLTAGE2_ADDR			0x0D				//变频器2电压
#define  MODS_CURRENT_ADDR			0x08				//变频器1电流
#define  MODS_CURRENT2_ADDR			0x0E				//变频器2电流
#define  MODS_ERROR_ADDR			0x09				//变频器1故障码
#define  MODS_ERROR2_ADDR		    0x0F				//变频器2故障码

#define  MD380_SLAVEADDR1		    0x01                //变频器从站地址1
#define  MD380_SLAVEADDR2			0x02				//变频器从站地址2

#define  VALUE_NUMS					4                   //变量个数
#define  RECTIFIER_NUMS				2					//变频器个数

typedef struct
{
    uint16_t Mdrigaddr;  //变频器寄存器地址
    uint16_t addr;       //Plc寄存器地址
    uint16_t value;		 //变量值
} Md_parm;

typedef struct
{
    uint16_t slaveaddr;  //从站地址
    Md_parm  modsparm[VALUE_NUMS];
} Md_struct;

//************************************************************************//

typedef struct
{
    uint8_t  RxBuf[MOD_RX_BUF_SIZE];
    uint16_t RxCount;
    uint8_t  RxStatus;
    uint8_t  RxNewFlag;
    uint8_t  TxBuf[MOD_TX_BUF_SIZE];
    uint16_t TxCount;
} MODS_T;

extern MODS_T g_tModS;


uint16_t getCrc16(const uint8_t *ptr, uint8_t length, uint16_t IniDat);    //检查CRC16值
//uint8_t checkCrc16(const uint8_t *ptr, uint8_t length);      			   //检查CRC16值


//Mosbus作为从机接收

void MODS_SendWithCRC(uint8_t *_pBuf, uint8_t _ucLen);
//void MODS_AnalyzeApp(void);    																			 //Mosbus数据解析
void MODS_ReciveNew(uint8_t * rxBuf, uint16_t Len);
//void MODS_InportMap(Areatype area, uint8_t* pmap, uint16_t Len);
void MODS_SlaveInit(void);
//void MODS_Poll(void);

//void MODS_01H(void);
//void MODS_02H(void);
//void MODS_03H(void);
//void MODS_04H(void);
//void MODS_05H(void);
//void MODS_06H(void);
//void MODS_0FH(void);
//void MODS_10H(void);


//Modbus作为主机发送
void MODS_Host_01(uint16_t slaveaddr, uint16_t startaddr, uint16_t length);     //离散输出
void MODS_Host_02(uint16_t slaveaddr, uint16_t startaddr, uint16_t length);		//离散输入
void MODS_Host_03(uint16_t slaveaddr, uint16_t startaddr, uint16_t length);     //保持寄存器
void MODS_Host_04(uint16_t slaveaddr, uint16_t startaddr, uint16_t length);		//模拟输入
void MODS_Host_05(uint16_t slaveaddr, uint16_t startaddr, uint8_t power);	    //写单个线圈
void MODS_Host_06(uint16_t slaveaddr, uint16_t startaddr, uint16_t wdata);	    //写单个寄存器
void MODS_Host_0F(uint16_t slaveaddr, uint16_t startaddr, uint16_t length, uint16_t bytes, uint8_t* wdata);     //写多个线圈
void MODS_Host_10(uint16_t slaveaddr, uint16_t startaddr, uint16_t length, uint8_t* wdata);		//写多个寄存器

void MODS_Host_01H(void);
void MODS_Host_02H(void);
void MODS_Host_03H(void);
void MODS_Host_04H(void);
void MODS_Host_05H(void);
void MODS_Host_06H(void);
void MODS_Host_0FH(void);
void MODS_Host_10H(void);

void MODS_Host_Poll(void);
void MODS_Host_AnalyzeApp(void);
void MODS_Host_SetRigAddr(uint16_t rigaddr);
void MODS_Host_Set_Usart(uint8_t uartval);

void Inverter_SaveData_To_PLC(void);

#endif