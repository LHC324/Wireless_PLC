#ifndef __MD380_MODBUS_H
#define __MD380_MODBUS_H

#include "config.h"

#define  PLC_SLAVEADDRESS			0x02
#define  MOD_RX_BUF_SIZE            200
#define  MOD_TX_BUF_SIZE     		200

#define  DIGITAL_INPUT_SIZE       	50     //���������ڴ��С
#define  DIGITAL_OUTPUT_SIZE		50		 //��������ڴ��С
#define  ANALOG_INPUT_SIZE			200		 //ģ�������ڴ��С
#define  KEEP_SIZE					500		 //���ּĴ����ڴ��С

/*������״̬*/
#define RSP_OK				    	0x00	  // �ɹ�
#define RSP_ERR_CMD			  		0x01	  // ��֧�ֵĹ�����
#define RSP_ERR_REG_ADDR			0x02	  // �Ĵ�����ַ����
#define RSP_ERR_VALUE		  		0x03	  // ���������
#define RSP_ERR_WRITE		  		0x04	  // д��ʧ��


#define USART1						1                       //����1
#define USART2						2						//����2
#define USART3        				3						//����3
#define USART4						4						//����4

/*****************************ͨѶ��ַ************************************/

#define ZH_ADDR						0x1001    //����Ƶ��
#define BUSBAR_VOLTAGE_ADDR			0x1002    //ĸ�ߵ�ѹ
#define PID_SETTING_ADDR			0x1010    //PID����
#define PID_FEEDBACK_ADDR			0x1011    //PID����
#define PLC_STEP_ADDR				0x1012    //PLC����
#define OUTPUT_VOLTAGE_ADDR			0x1003    //�����ѹ
#define OUTPUT_CURRENT_ADDR			0x1004	  //�������
#define OUTPUT_POWER_ADDR			0x1005    //�������
#define OUTPUT_TORQUE_ADDR			0x1006    //���ת��
#define RUNNING_SPEED_ADDR			0x1007    //�����ٶ�
#define DI_INPUT_FLAG_ADDR			0x1008    //DI�����־
#define DO_OUTPUT_FLAG_ADDR			0x1009    //DO�����־
#define AI1_VOLTAGE_ADDR			0x100A    //AI1��ѹ
#define AI2_VOLTAGE_ADDR			0x100B    //AI2��ѹ
#define AI3_VOLTAGE_ADDR			0x100C	  //AI3��ѹ
#define COUNT_INPUT_ADDR			0x100D	  //����ֵ����
#define LENGTH_INPUT_ADDR			0x100E    //����ֵ����
#define PAYLOAD_SPEED_ADDR			0x100F    //�����ٶ�
#define PULSE_FREQUENCY_ADDR		0x1013    //����Ƶ��
#define FEEDBACK_SPEED_ADDR			0x1014    //�����ٶ�
#define SURPLUS_RUNNINGTIME_ADDR	0x1015    //ʣ������ʱ��
#define AL1_REVISE_VOLTAGE_ADDR		0x1016    //AL1У��ǰ��ѹ
#define AL2_REVISE_VOLTAGE_ADDR   	0x1017    //AI2У��ǰ��ѹ
#define AL3_REVISE_VOLTAGE_ADDR   	0x1018	  //AL3У��ǰ��ѹ
#define WIRE_SPEED_ADDR				0x1019	  //���ٶ�
#define NOW_POWER_ON_TIME_ADDR		0x101A    //��ǰ�ϵ�ʱ��
#define NOW_RUNNING_TIME_ADDR		0x101B    //��ǰ����ʱ��
#define COMMUNICATION_SETTING_ADDR  0x101D    //ͨѶ�趨ֵ
#define ACTUAL_FEEDBACK_SPEED_ADDR	0x101E    //ʵ�ʷ����ٶ�
#define MAIN_FREQUENCY_X_ADDR		0x101F	  //��Ƶ��X��ʾ
#define ASSIST_FREQUENCY_Y_ADDR		0x1020	  //��Ƶ��Y��ʾ
#define FAULT_ADDR					0x8000	  //������

/************************************************************************/


//****************************MD380����**********************************//

#define  MODS_SPEED1_ADDR           0x06                //��Ƶ��1ת��
#define  MODS_SPEED2_ADDR		    0x0C				//��Ƶ��2ת��
#define  MODS_VOLTAGE_ADDR			0x07				//��Ƶ��1��ѹ
#define  MODS_VOLTAGE2_ADDR			0x0D				//��Ƶ��2��ѹ
#define  MODS_CURRENT_ADDR			0x08				//��Ƶ��1����
#define  MODS_CURRENT2_ADDR			0x0E				//��Ƶ��2����
#define  MODS_ERROR_ADDR			0x09				//��Ƶ��1������
#define  MODS_ERROR2_ADDR		    0x0F				//��Ƶ��2������

#define  MD380_SLAVEADDR1		    0x01                //��Ƶ����վ��ַ1
#define  MD380_SLAVEADDR2			0x02				//��Ƶ����վ��ַ2

#define  VALUE_NUMS					4                   //��������
#define  RECTIFIER_NUMS				2					//��Ƶ������

typedef struct
{
    uint16_t Mdrigaddr;  //��Ƶ���Ĵ�����ַ
    uint16_t addr;       //Plc�Ĵ�����ַ
    uint16_t value;		 //����ֵ
} Md_parm;

typedef struct
{
    uint16_t slaveaddr;  //��վ��ַ
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


uint16_t getCrc16(const uint8_t *ptr, uint8_t length, uint16_t IniDat);    //���CRC16ֵ
//uint8_t checkCrc16(const uint8_t *ptr, uint8_t length);      			   //���CRC16ֵ


//Mosbus��Ϊ�ӻ�����

void MODS_SendWithCRC(uint8_t *_pBuf, uint8_t _ucLen);
//void MODS_AnalyzeApp(void);    																			 //Mosbus���ݽ���
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


//Modbus��Ϊ��������
void MODS_Host_01(uint16_t slaveaddr, uint16_t startaddr, uint16_t length);     //��ɢ���
void MODS_Host_02(uint16_t slaveaddr, uint16_t startaddr, uint16_t length);		//��ɢ����
void MODS_Host_03(uint16_t slaveaddr, uint16_t startaddr, uint16_t length);     //���ּĴ���
void MODS_Host_04(uint16_t slaveaddr, uint16_t startaddr, uint16_t length);		//ģ������
void MODS_Host_05(uint16_t slaveaddr, uint16_t startaddr, uint8_t power);	    //д������Ȧ
void MODS_Host_06(uint16_t slaveaddr, uint16_t startaddr, uint16_t wdata);	    //д�����Ĵ���
void MODS_Host_0F(uint16_t slaveaddr, uint16_t startaddr, uint16_t length, uint16_t bytes, uint8_t* wdata);     //д�����Ȧ
void MODS_Host_10(uint16_t slaveaddr, uint16_t startaddr, uint16_t length, uint8_t* wdata);		//д����Ĵ���

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