/****************************************Copyright (c)****************************************************
 

**--------------File Info---------------------------------------------------------------------------------

** File name:
** Last modified Date:

** Last Version:

** Descriptions:
**--------------------------------------------------------------------------------------------------------

** Created by:		刘家辉 
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
#define W25Q64_CapacityBuff (8*1024*1024)     //Flash的大小(字节)
#define W25Q64_BlockBuff    (16*4*1024)       //块的大小(字节)
#define W25Q64_BlockCnt     (W25Q64_CapacityBuff/W25Q64_BlockBuff)  //块的数量
#define W25Q64_SectorBuff   (4*1024)          //扇区大小(字节)
#define W25Q64_SectorCnt    (W25Q64_CapacityBuff/W25Q64_SectorBuff) //扇区数量
#define W25Q64_PageBuff     256           //页大小(字节)
#define W25Q64_PageCnt      (W25Q64_CapacityBuff/W25Q64_PageBuff)   //页数量

extern uint8_t READ_ID[4];	              //读ID
extern uint8_t READ_STATUS[1];						//读状态寄存器，检查线路是否繁忙
extern uint8_t WRITE_ENABLE[1];						//写使能
extern uint8_t SECTOR_EARSE[1];						//擦除命令
extern uint8_t PAGE_WRITE[1];							//写数据命令
extern uint8_t READ_DATA[1];							//读数据命令

uint16_t W25Qx_ReadID(void);//读芯片ID
void W25Qx_PrintInfo(void);//打印相关参数
uint8_t W25Qx_ReadSR(void);//读SR状态寄存器
void W25Qx_WaitBusy(void);//繁忙时等待
void W25Qx_WriteEnable(void);//写使能
void W25Qx_EarseSector(uint32_t Addr);//擦除扇区
void W25Qx_EarseBlock(uint32_t Addr);//擦除块
void W25Qx_PageWrite(uint32_t Addr,uint8_t* Data,uint16_t Length);//页写
void W25Qx_SectorWrite(uint32_t Addr,uint8_t* Data,uint32_t Length);//扇区写

void W25Qx_ReadData(uint32_t Addr,uint8_t* Data,uint32_t Length);//读数据
void W25Qx_WriteData(uint32_t Addr,uint8_t* Data,uint32_t Length);//写数据
void W25Qx_EarseChip(void);//擦除W25QxFlash芯片



extern uint8_t Buffer[4096];

#endif

