/****************************************Copyright (c)****************************************************
 

**--------------File Info---------------------------------------------------------------------------------

** File name:
** Last modified Date:

** Last Version:

** Descriptions:
**--------------------------------------------------------------------------------------------------------

** Created by:		���һ� 
** Created date:	2021/xx/xx

** Version:				V1.0
** Descriptions:
**--------------------------------------------------------------------------------------------------------*/
#ifndef _W25Q64_H_
#define _W25Q64_H_

#include "spi.h"
#include "main.h"
#include <stdint.h>

#include "User_Conf.h"

#define W25Qx_CS_Pin 				W25Q64_CS_Pin
#define W25Qx_CS_Port 			W25Q64_CS_GPIO_Port

#define W25Q64_ID						0xEF16
#define W25Q64_CapacityBuff (8*1024*1024)     //Flash�Ĵ�С(�ֽ�)
#define W25Q64_BlockBuff    (16*4*1024)       //��Ĵ�С(�ֽ�)
#define W25Q64_BlockCnt     (W25Q64_CapacityBuff/W25Q64_BlockBuff)  //�������
#define W25Q64_SectorBuff   (4*1024)          //������С(�ֽ�)
#define W25Q64_SectorCnt    (W25Q64_CapacityBuff/W25Q64_SectorBuff) //��������
#define W25Q64_PageBuff     256           //ҳ��С(�ֽ�)
#define W25Q64_PageCnt      (W25Q64_CapacityBuff/W25Q64_PageBuff)   //ҳ����

extern uint8_t READ_ID[4];	              //��ID
extern uint8_t READ_STATUS[1];						//��״̬�Ĵ����������·�Ƿ�æ
extern uint8_t WRITE_ENABLE[1];						//дʹ��
extern uint8_t SECTOR_EARSE[1];						//��������
extern uint8_t PAGE_WRITE[1];							//д��������
extern uint8_t READ_DATA[1];							//����������

uint16_t W25Qx_ReadID(void);//��оƬID
void W25Qx_PrintInfo(void);//��ӡ��ز���
uint8_t W25Qx_ReadSR(void);//��SR״̬�Ĵ���
void W25Qx_WaitBusy(void);//��æʱ�ȴ�
void W25Qx_WriteEnable(void);//дʹ��
void W25Qx_EarseSector(uint32_t Addr);//��������
void W25Qx_EarseBlock(uint32_t Addr);//������
void W25Qx_PageWrite(uint32_t Addr,uint8_t* Data,uint16_t Length);//ҳд
void W25Qx_SectorWrite(uint32_t Addr,uint8_t* Data,uint32_t Length);//����д

void W25Qx_ReadData(uint32_t Addr,uint8_t* Data,uint32_t Length);//������
void W25Qx_WriteData(uint32_t Addr,uint8_t* Data,uint32_t Length);//д����
void W25Qx_EarseChip(void);//����W25QxFlashоƬ



extern uint8_t Buffer[4096];

#endif

