/****************************************Copyright (c)****************************************************
 

**--------------File Info---------------------------------------------------------------------------------

** File name:flash_eeprom.h
** Last modified Date:

** Last Version:

** Descriptions:基于HAL库的FLASH模拟EEPROM的库(支持芯片STM32F1)
**--------------------------------------------------------------------------------------------------------

** Created by:		刘家辉 
** Created date:	2021/xx/xx

** Version:				V1.0
** Descriptions:
**--------------------------------------------------------------------------------------------------------*/
#ifndef _FLASH_EEPROM_H_
#define _FLASH_EEPROM_H_

#include "stm32f1xx_hal.h"

#include "User_Conf.h"

/* 
	STM32F103C8Tx属于中等容量产品，Flash的大小为64K
	中容量产品主存储块最大为16K×64位，每个存储块划分为256个1K字节的页，
	每页的大小为1K字节，擦除操作以页为单位，写操作必须以16位为宽度，允许跨页写入
	FLASH的起始地址为0x0800_0000（第0页）,
	64K的flash的终止地址为0x0800_FFFF（第63页）,128K的flash的终止地址为0x0801_FFFF（第127页）
	但是STM32F103C8Tx实际可以使用到128K的flash
*/

// 定义FLASH的基本信息
#define FLASH_SIZE          0x10000 //FLASH的大小(字节)
#define FLASH_BASE_ADDR			0x08000000	//FLASH的起始地址
#define FLASH_END_ADDR			(FLASH_BASE_ADDR+FLASH_SIZE)	//FLASH的结束地址
#ifndef FLASH_PAGE_SIZE	//这个页大小可能被HAL库已经定义好了
#define FLASH_PAGE_SIZE     1024		//FLASH的页(也就是最小擦除单元)大小（字节）
#endif
#define FLASH_PAGE_COUNT    (FLASH_SIZE/FLASH_PAGE_SIZE)//FLASH的页(也就是最小擦除单元)数量(也就是最小擦除单元)
#define FLASH_Program_SIZE  2		//FLASH的最小编程大小（字节）

// 定义作为模拟EEPROM的Flash的信息
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
  uint16_t PAGE_USE;   //Flash_EP的所使用的页数
  uint32_t SIZE;       //Flash_EP的总大小
  uint32_t BASE_ADDR;  //Flash_EP的开始地址
  uint32_t END_ADDR;   //Flash_EP的结束地址
  DATA_BUFFER DB;  //Flash_EP的Buffer
}FLASH_EP_INFO;

//数据参数结构体
typedef struct
{
  uint32_t BaseAddr;//数据的起始地址
  uint32_t EndAddr;//数据的结束地址
  uint32_t Length;//数据的长度
  uint32_t BaseAddr_Of_Page;//数据起始地址所对齐的页基地址
  uint32_t EndAddr_Of_Page; //数据结束地址所对齐的页基地址
  uint16_t Span_Page;//数据跨过了多少个扇区
  uint32_t IndexAddr;//指示当前到了到了哪一地址
}DATA_PARAM;



/* 相关接口函数 */
void Flash_EP_Init(uint16_t Flash_EP_PAGE_USE);//Flash_EEPROM初始化
void Flash_EP_Info(void);//Flash_EEPROM信息打印
void Flash_EP_Read(uint32_t Addr, uint8_t *_data, uint32_t Length); //Flash_EEPROM读
void Flash_EP_Write(uint32_t Addr, uint8_t *_data, uint32_t Length); //Flash_EEPROM写
void Flash_EP_Earse(void);//Flash_EEPROM擦除


#endif
