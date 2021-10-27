#ifndef __EEPROM_H_
#define __EEPROM_H_

#include"config.h"
#include"systemtimer.h"

#define WT_30M          0x80
#define WT_24M          0x81
#define WT_20M          0x82
#define WT_12M          0x83
#define WT_6M           0x84
#define WT_3M           0x85
#define WT_2M           0x86
#define WT_1M           0x87

/**
 * @brief	����STC8��Ƭ��EEPROM�ĵȴ�ʱ��
 * @details	
 * @param	None
 * @retval	None
 */
static void IapConfigWaitTime();

/**
 * @brief	�ر�iap����
 * @details	
 * @param	None
 * @retval	None
 */
extern void IapIdle();

/**
 * @brief	��iap��e2prom�ж���һ���ֽ�����
 * @details	
 * @param	addr: ָ����ַ
 * @retval	None
 */
extern char IapRead(char addr);

/**
 * @brief	��iap��e2prom��ָ����ַд��һ���ֽ�����
 * @details	
 * @param	addr: ָ����ַ, dat: ����
 * @retval	None
 */
extern void IapProgram(unsigned short addr, unsigned char dat);

/**
 * @brief	����ָ����ַ������
 * @details	����ÿ�ΰ���512B���У����ṩ�׵�ַ����
 * @param	addr:��ʼ��ַ
 * @retval	None
 */
extern void IapErase(unsigned short addr);

/**
 * @brief	��ָ����ַд�����ֽ�����
 * @details	д����һ���밴��һ������һ����������д����Ȼ�ڲ������ݵ�ʱ���������ݶ�ʧ��һ�������Ĵ�С�� 512�ֽ�
 * @param	addr:��ʼ��ַ, *Str: ָ���ֽ�����ָ��, Len:����
 * @retval	None
 */
extern void IapWrite_Buff(uint16_t Addr,const uint8_t *Str,uint8_t Len);

/**
 * @brief	��ָ����ַ��ȡ����ֽ�����
 * @details	
 * @param	addr:��ʼ��ַ, *Str: ָ��Ŀ�껺����ָ��, Len:����
 * @retval	None
 */
extern void IapRead_Buff(uint16_t Addr,uint8_t *Str,uint8_t Len);


#endif