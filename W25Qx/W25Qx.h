/****************************************Copyright (c)****************************************************
 

**--------------File Info---------------------------------------------------------------------------------

** File name:
** Last modified Date:

** Last Version:

** Descriptions:
**--------------------------------------------------------------------------------------------------------

** Created by:		刘家辉 
** Created date:	2021/xx/xx

** Version:				V2.0
** Descriptions: 为了兼容FATFS文件系统，对API进行了部分修改
**--------------------------------------------------------------------------------------------------------*/
#ifndef _W25QX_H_
#define _W25QX_H_

/*
W25Q64是一块SPI接口的Nor Flash芯片的容量8M Byte，
Block块（64K Byte）——Sector扇区（4K Byte）——Page页面（256 Byte）
扇区擦除/块擦除
页编程
随机读
*/

#include "spi.h"
#include "main.h"
#include <stdint.h>
#include <stdbool.h>

#include "User_Conf.h"

#define USE_FATFS           true  //使用FATFS文件系统
#ifdef USE_FATFS
#include "integer.h"
#endif

/* SPI的片选线 */
#define W25Qx_CS_Pin 				W25Q64_CS_Pin
#define W25Qx_CS_Port 			W25Q64_CS_GPIO_Port

/* W25QX芯片的宏定义 */
#define W25Q64							true	//定义所使用的SPI-Flash芯片

#ifdef W25Q64
#define W25Qx_NAME 					"W25Q64"	//Flash芯片名称
#define W25Qx_ID						0xEF16	//Flash芯片ID
#define W25Qx_CapacityBuff 	(8*1024*1024)	//Flash芯片总大小(字节)
#define W25Qx_BlockBuff    	(16*4*1024)	//块的大小(字节)
#define W25Qx_BlockCnt     	(W25Qx_CapacityBuff/W25Qx_BlockBuff)	//块的数量
#define W25Qx_SectorBuff   	(4*1024)	//扇区大小(字节)
#define W25Qx_SectorCnt    	(W25Qx_CapacityBuff/W25Qx_SectorBuff)	//扇区数量
#define W25Qx_PageBuff     	256	//页大小(字节)
#define W25Qx_PageCnt      	(W25Qx_CapacityBuff/W25Qx_PageBuff)	//页数量
#endif

extern uint8_t READ_ID[4];	              //读ID
extern uint8_t READ_STATUS[1];						//读状态寄存器，检查线路是否繁忙
extern uint8_t WRITE_ENABLE[1];						//写使能
extern uint8_t SECTOR_EARSE[1];						//擦除命令
extern uint8_t PAGE_WRITE[1];							//写数据命令
extern uint8_t READ_DATA[1];							//读数据命令


/* 通用内部API */
uint16_t W25Qx_ReadID(void);//读芯片ID
void W25Qx_PrintInfo(void);//打印相关参数
uint8_t W25Qx_ReadSR(void);//读SR状态寄存器
void W25Qx_WaitBusy(void);//繁忙时等待
void W25Qx_WriteEnable(void);//写使能
void W25Qx_EarseSector(uint32_t Addr);//擦除扇区
void W25Qx_EarseBlock(uint32_t Addr);//擦除块
void W25Qx_PageRead(uint32_t Addr, uint8_t *Data); //页写
void W25Qx_PageWrite_NoCheck(uint32_t Addr,uint8_t* Data);//页写(不校验)
// void W25Qx_PageWrite(uint32_t Addr,uint8_t* Data);//页写
void W25QX_SectorRead(uint32_t Addr,uint8_t* Data);//扇区读
void W25Qx_SectorWrite_NoCheck(uint32_t Addr,uint8_t* Data);//扇区写(不校验)
// void W25Qx_SectorWrite(uint32_t Addr,uint8_t* Data);//扇区写


#ifdef USE_FATFS
/* 该部分用于接入FATFS的文件系统API */
bool FF_W25Qx_Status(void); //FatFs获取获取设备状态
bool FF_W25Qx_Init(void);		//FatFs初始化W25Qx芯片
bool FF_W25Qx_SectorRead(BYTE *buff, DWORD sector, UINT count); //FatFs扇区读W25Qx芯片
bool FF_W25Qx_SectoWrite(BYTE *buff, DWORD sector, UINT count); //FatFs扇区编程W25Qx芯片
#else
/* 该部分是用户存储数据的参数 */
void W25Qx_ReadData(uint32_t Addr, uint8_t *Data, uint32_t Length); 	//读数据
void W25Qx_WriteData(uint32_t Addr, uint8_t *Data, uint32_t Length);	//写数据
void W25Qx_EarseChip(void);	//擦除W25QxFlash芯片
#endif

		extern uint8_t Buffer[4096];

#endif

