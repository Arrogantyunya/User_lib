/****************************************Copyright (c)****************************************************
 

**--------------File Info---------------------------------------------------------------------------------

** File name:flash_eeprom.h
** Last modified Date:

** Last Version:

** Descriptions:����HAL���FLASHģ��EEPROM�Ŀ�(֧��оƬSTM32F1)
**--------------------------------------------------------------------------------------------------------

** Created by:		���һ� 
** Created date:	2021/xx/xx

** Version:				V1.0
** Descriptions:
**--------------------------------------------------------------------------------------------------------*/
#ifndef _FLASH_EEPROM_H_
#define _FLASH_EEPROM_H_

#include "stm32f1xx_hal.h"

#include "User_Conf.h"

/* 
	STM32F103C8Tx�����е�������Ʒ��Flash�Ĵ�СΪ64K
	��������Ʒ���洢�����Ϊ16K��64λ��ÿ���洢�黮��Ϊ256��1K�ֽڵ�ҳ��
	ÿҳ�Ĵ�СΪ1K�ֽڣ�����������ҳΪ��λ��д����������16λΪ��ȣ������ҳд��
	FLASH����ʼ��ַΪ0x0800_0000����0ҳ��,
	64K��flash����ֹ��ַΪ0x0800_FFFF����63ҳ��,128K��flash����ֹ��ַΪ0x0801_FFFF����127ҳ��
	����STM32F103C8Txʵ�ʿ���ʹ�õ�128K��flash
*/

// ����FLASH�Ļ�����Ϣ
#define FLASH_SIZE          0x10000 //FLASH�Ĵ�С(�ֽ�)
#define FLASH_BASE_ADDR			0x08000000	//FLASH����ʼ��ַ
#define FLASH_END_ADDR			(FLASH_BASE_ADDR+FLASH_SIZE)	//FLASH�Ľ�����ַ
#ifndef FLASH_PAGE_SIZE	//���ҳ��С���ܱ�HAL���Ѿ��������
#define FLASH_PAGE_SIZE     1024		//FLASH��ҳ(Ҳ������С������Ԫ)��С���ֽڣ�
#endif
#define FLASH_PAGE_COUNT    (FLASH_SIZE/FLASH_PAGE_SIZE)//FLASH��ҳ(Ҳ������С������Ԫ)����(Ҳ������С������Ԫ)
#define FLASH_Program_SIZE  2		//FLASH����С��̴�С���ֽڣ�

// ������Ϊģ��EEPROM��Flash����Ϣ
#define Flash_EP_BUFFER_SIZE (FLASH_PAGE_SIZE / FLASH_Program_SIZE)
typedef union 
{
#if (FLASH_Program_SIZE == 1)
  uint8_t Buffer[Flash_EP_BUFFER_SIZE];
#elif (FLASH_Program_SIZE == 2)
  uint16_t Buffer[Flash_EP_BUFFER_SIZE];
#elif (FLASH_Program_SIZE == 4)
  uint32_t Buffer[Flash_EP_BUFFER_SIZE];
#elif (FLASH_Program_SIZE == 8)
  uint64_t Buffer[Flash_EP_BUFFER_SIZE];
#endif
  uint8_t U8Array[FLASH_PAGE_SIZE];
}DATA_BUFFER;

typedef struct 
{
  uint16_t PAGE_USE;   //Flash_EP����ʹ�õ�ҳ��
  uint32_t SIZE;       //Flash_EP���ܴ�С
  uint32_t BASE_ADDR;  //Flash_EP�Ŀ�ʼ��ַ
  uint32_t END_ADDR;   //Flash_EP�Ľ�����ַ
  DATA_BUFFER DB;  //Flash_EP��Buffer
}FLASH_EP_INFO;

//���ݲ����ṹ��
typedef struct
{
  uint32_t BaseAddr;//���ݵ���ʼ��ַ
  uint32_t EndAddr;//���ݵĽ�����ַ
  uint32_t Length;//���ݵĳ���
  uint32_t BaseAddr_Of_Page;//������ʼ��ַ�������ҳ����ַ
  uint32_t EndAddr_Of_Page; //���ݽ�����ַ�������ҳ����ַ
  uint16_t Span_Page;//���ݿ���˶��ٸ�����
  uint32_t IndexAddr;//ָʾ��ǰ���˵�����һ��ַ
}DATA_PARAM;



/* ��ؽӿں��� */
void Flash_EP_Init(uint16_t Flash_EP_PAGE_USE);//Flash_EEPROM��ʼ��
void Flash_EP_Info(void);//Flash_EEPROM��Ϣ��ӡ
void Flash_EP_Read(uint32_t Addr, uint8_t *_data, uint32_t Length); //Flash_EEPROM��
void Flash_EP_Write(uint32_t Addr, uint8_t *_data, uint32_t Length); //Flash_EEPROMд
void Flash_EP_Earse(void);//Flash_EEPROM����


#endif
