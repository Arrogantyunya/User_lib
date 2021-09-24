/****************************************Copyright (c)****************************************************
 

**--------------File Info---------------------------------------------------------------------------------

** File name:
** Last modified Date:

** Last Version:

** Descriptions:
**--------------------------------------------------------------------------------------------------------

** Created by:		���һ� 
** Created date:	2021/xx/xx

** Version:				V2.0
** Descriptions: Ϊ�˼���FATFS�ļ�ϵͳ����API�����˲����޸�
**--------------------------------------------------------------------------------------------------------*/
#ifndef _W25QX_H_
#define _W25QX_H_

/*
W25Q64��һ��SPI�ӿڵ�Nor FlashоƬ������8M Byte��
Block�飨64K Byte������Sector������4K Byte������Pageҳ�棨256 Byte��
��������/�����
ҳ���
�����
*/

#include "spi.h"
#include "main.h"
#include <stdint.h>
#include <stdbool.h>

#include "User_Conf.h"

#define USE_FATFS           true  //ʹ��FATFS�ļ�ϵͳ
#ifdef USE_FATFS
#include "integer.h"
#endif

/* SPI��Ƭѡ�� */
#define W25Qx_CS_Pin 				W25Q64_CS_Pin
#define W25Qx_CS_Port 			W25Q64_CS_GPIO_Port

/* W25QXоƬ�ĺ궨�� */
#define W25Q64							true	//������ʹ�õ�SPI-FlashоƬ

#ifdef W25Q64
#define W25Qx_NAME 					"W25Q64"	//FlashоƬ����
#define W25Qx_ID						0xEF16	//FlashоƬID
#define W25Qx_CapacityBuff 	(8*1024*1024)	//FlashоƬ�ܴ�С(�ֽ�)
#define W25Qx_BlockBuff    	(16*4*1024)	//��Ĵ�С(�ֽ�)
#define W25Qx_BlockCnt     	(W25Qx_CapacityBuff/W25Qx_BlockBuff)	//�������
#define W25Qx_SectorBuff   	(4*1024)	//������С(�ֽ�)
#define W25Qx_SectorCnt    	(W25Qx_CapacityBuff/W25Qx_SectorBuff)	//��������
#define W25Qx_PageBuff     	256	//ҳ��С(�ֽ�)
#define W25Qx_PageCnt      	(W25Qx_CapacityBuff/W25Qx_PageBuff)	//ҳ����
#endif

extern uint8_t READ_ID[4];	              //��ID
extern uint8_t READ_STATUS[1];						//��״̬�Ĵ����������·�Ƿ�æ
extern uint8_t WRITE_ENABLE[1];						//дʹ��
extern uint8_t SECTOR_EARSE[1];						//��������
extern uint8_t PAGE_WRITE[1];							//д��������
extern uint8_t READ_DATA[1];							//����������


/* ͨ���ڲ�API */
uint16_t W25Qx_ReadID(void);//��оƬID
void W25Qx_PrintInfo(void);//��ӡ��ز���
uint8_t W25Qx_ReadSR(void);//��SR״̬�Ĵ���
void W25Qx_WaitBusy(void);//��æʱ�ȴ�
void W25Qx_WriteEnable(void);//дʹ��
void W25Qx_EarseSector(uint32_t Addr);//��������
void W25Qx_EarseBlock(uint32_t Addr);//������
void W25Qx_PageRead(uint32_t Addr, uint8_t *Data); //ҳд
void W25Qx_PageWrite_NoCheck(uint32_t Addr,uint8_t* Data);//ҳд(��У��)
// void W25Qx_PageWrite(uint32_t Addr,uint8_t* Data);//ҳд
void W25QX_SectorRead(uint32_t Addr,uint8_t* Data);//������
void W25Qx_SectorWrite_NoCheck(uint32_t Addr,uint8_t* Data);//����д(��У��)
// void W25Qx_SectorWrite(uint32_t Addr,uint8_t* Data);//����д


#ifdef USE_FATFS
/* �ò������ڽ���FATFS���ļ�ϵͳAPI */
bool FF_W25Qx_Status(void); //FatFs��ȡ��ȡ�豸״̬
bool FF_W25Qx_Init(void);		//FatFs��ʼ��W25QxоƬ
bool FF_W25Qx_SectorRead(BYTE *buff, DWORD sector, UINT count); //FatFs������W25QxоƬ
bool FF_W25Qx_SectoWrite(BYTE *buff, DWORD sector, UINT count); //FatFs�������W25QxоƬ
#else
/* �ò������û��洢���ݵĲ��� */
void W25Qx_ReadData(uint32_t Addr, uint8_t *Data, uint32_t Length); 	//������
void W25Qx_WriteData(uint32_t Addr, uint8_t *Data, uint32_t Length);	//д����
void W25Qx_EarseChip(void);	//����W25QxFlashоƬ
#endif

		extern uint8_t Buffer[4096];

#endif

