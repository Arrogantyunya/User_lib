/****************************************Copyright (c)****************************************************
 

**--------------File Info---------------------------------------------------------------------------------

** File name:flash_eeprom.c
** Last modified Date:

** Last Version:

** Descriptions:基于HAL库的FLASH模拟EEPROM的库(支持芯片STM32F1)
**--------------------------------------------------------------------------------------------------------

** Created by:		刘家辉 
** Created date:	2021/xx/xx

** Version:				V1.0
** Descriptions:
**--------------------------------------------------------------------------------------------------------*/
#include "flash_eeprom.h"

FLASH_EP_INFO FLASH_EP; 

/**
 * @Brief:Flash_EEPROM初始化
 * @Param:
 * @Return:
 * @Note:
 * @Author:
 */
void Flash_EP_Init(uint16_t Flash_EP_PAGE_USE)
{
  FLASH_EP.PAGE_USE = Flash_EP_PAGE_USE;
  FLASH_EP.SIZE = FLASH_EP.PAGE_USE * FLASH_PAGE_SIZE;
  FLASH_EP.END_ADDR = FLASH_END_ADDR;
  FLASH_EP.BASE_ADDR = FLASH_EP.END_ADDR - FLASH_EP.SIZE;
}

/**
 * @Brief:Flash_EEPROM信息打印
 * @Param:
 * @Return:
 * @Note:
 * @Author:
 */
void Flash_EP_Info(void)
{
  Serial_println("\r\n---------------------------");
  Serial_println("Flash的总大小为%d字节",FLASH_SIZE);
  Serial_println("Flash的地址区间为:[0x%08x - 0x%08x)",FLASH_BASE_ADDR,FLASH_END_ADDR);
  Serial_println("Flash的页大小为%d字节",FLASH_PAGE_SIZE);
  Serial_println("Flash的页数量为%d",FLASH_PAGE_COUNT);
  Serial_println("Flash的最小编程大小为%d字节",FLASH_Program_SIZE);

  Serial_println("Flash_EP的所使用的页数为%d",FLASH_EP.PAGE_USE);
  Serial_println("Flash_EP的总大小为%d",FLASH_EP.SIZE);
  Serial_println("Flash_EP的的地址区间为:[0x%08x - 0x%08x)",FLASH_EP.BASE_ADDR,FLASH_EP.END_ADDR);
  Serial_println("---------------------------\r\n");
}

/**
 * @Brief:Flash_EEPROM读
 * @Param:
 * @Return:
 * @Note:
 * @Author:
 */
void Flash_EP_Read(uint32_t Addr, uint8_t *_data, uint32_t Length)
{
	DATA_PARAM DataParam;
	DataParam.BaseAddr = FLASH_EP.BASE_ADDR + Addr;
  DataParam.EndAddr = DataParam.BaseAddr + Length;
	/* 这里是一个防止写数据超出Flash芯片的实际大小引起未知的错误的断言 */
  DataParam.EndAddr = DataParam.EndAddr > FLASH_END_ADDR ? FLASH_END_ADDR : DataParam.EndAddr;
  DataParam.Length = DataParam.EndAddr - DataParam.BaseAddr; //怕之前的数据超出大小，所以这里重新算一遍

  for (uint16_t i = 0; i < DataParam.Length; i++)
  {
		_data[i] = *(__IO uint8_t *)(DataParam.BaseAddr + i);
//    _data[i] = *(__IO uint16_t *)(Addr + (2 * i)); //*(__IO uint16_t *)是读取该地址的参数值,其值为16位数据,一次读取两个字节，*(__IO uint32_t *)就一次读4个字节
  }
}

/**
 * @Brief:Flash_EEPROM写
 * @Param:
 * @Return:
 * @Note:
 * @Author:
 */
void Flash_EP_Write(uint32_t Addr, uint8_t *_data, uint32_t Length)
{
  DATA_PARAM DataParam;
  DataParam.BaseAddr = FLASH_EP.BASE_ADDR + Addr;
  DataParam.EndAddr = DataParam.BaseAddr + Length;
  /* 这里是一个防止写数据超出Flash芯片的实际大小引起未知的错误的断言 */
  DataParam.EndAddr = DataParam.EndAddr > FLASH_END_ADDR ? FLASH_END_ADDR : DataParam.EndAddr;
  DataParam.Length = DataParam.EndAddr - DataParam.BaseAddr; //怕之前的数据超出大小，所以这里重新算一遍
  DataParam.BaseAddr_Of_Page = (DataParam.BaseAddr / FLASH_PAGE_SIZE) * FLASH_PAGE_SIZE;
  DataParam.EndAddr_Of_Page = (DataParam.EndAddr / FLASH_PAGE_SIZE) * FLASH_PAGE_SIZE;
  DataParam.Span_Page = ((DataParam.EndAddr_Of_Page - DataParam.BaseAddr_Of_Page) / FLASH_PAGE_SIZE) + 1;
//  Serial_println("DataParam.BaseAddr = 0x%08x",DataParam.BaseAddr);
//  Serial_println("DataParam.EndAddr = 0x%08x",DataParam.EndAddr);
//  Serial_println("DataParam.BaseAddr_Of_Page = 0x%08x", DataParam.BaseAddr_Of_Page);
//  Serial_println("DataParam.EndAddr_Of_Page = 0x%08x", DataParam.EndAddr_Of_Page);
//  Serial_println("DataParam.Span_Page = %d", DataParam.Span_Page);
//  Serial_println("............");

  DataParam.IndexAddr = DataParam.BaseAddr_Of_Page; //将索引地址指向数据起始地址所对齐的页基地址
  uint32_t count = 0;
  //代表需要在多少个页进行重复操作
  for (uint16_t i = 0; i < DataParam.Span_Page; i++)
  {
    memset(FLASH_EP.DB.U8Array, 0x00, sizeof(FLASH_EP.DB.U8Array)); //使用FLASH_EP.DB前先清空数组避免影响
    /* 先将对应扇区的数据读出到FLASH_EP.DB */
    Flash_EP_Read(DataParam.IndexAddr - FLASH_EP.BASE_ADDR, FLASH_EP.DB.U8Array, FLASH_PAGE_SIZE);
    /* 擦除对应的扇区 */
    FLASH_EraseInitTypeDef My_Flash; //声明 FLASH_EraseInitTypeDef 结构体为 My_Flash
    HAL_FLASH_Unlock();              //解锁Flash
    __disable_irq();                            //擦除前关闭中断
    My_Flash.TypeErase = FLASH_TYPEERASE_PAGES; //标明Flash执行页面只做擦除操作
    My_Flash.PageAddress = DataParam.IndexAddr; //声明要擦除的地址
    My_Flash.NbPages = 1;     //说明要擦除的页数，此参数必须是Min_Data = 1和Max_Data =(最大页数-初始页的值)之间的值
    uint32_t PageError = 0;                   //设置PageError,如果出现错误这个变量会被设置为出错的FLASH地址
    HAL_FLASHEx_Erase(&My_Flash, &PageError); //调用擦除函数擦除
    __enable_irq();                           //擦除后打开中断
    /* 将要修改的数据写入FLASH_EP.DB */
    for (uint32_t i = DataParam.IndexAddr; i < DataParam.IndexAddr + FLASH_PAGE_SIZE; i++)
    {
      if ((i >= DataParam.BaseAddr) && (i < DataParam.EndAddr))
      {
        FLASH_EP.DB.U8Array[i - DataParam.IndexAddr] = _data[count++];
      }
    }
    /* 将FLASH_EP.DB.U8Array的数据写入对应的扇区 */
    for (uint16_t i = 0; i < Flash_EP_BUFFER_SIZE; i++)
    {
			#if (FLASH_Program_SIZE == 1)
//				HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, (DataParam.IndexAddr + (FLASH_Program_SIZE * i)), FLASH_EP.DB.Buffer[i]); //对Flash进行编程
			#elif (FLASH_Program_SIZE == 2)
				HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, (DataParam.IndexAddr + (FLASH_Program_SIZE * i)), FLASH_EP.DB.Buffer[i]); //对Flash进行编程
			#elif (FLASH_Program_SIZE == 4)
				HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, (DataParam.IndexAddr + (FLASH_Program_SIZE * i)), FLASH_EP.DB.Buffer[i]); //对Flash进行编程
			#elif (FLASH_Program_SIZE == 8)
				HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, (DataParam.IndexAddr + (FLASH_Program_SIZE * i)), FLASH_EP.DB.Buffer[i]); //对Flash进行编程
			#endif
    }
    DataParam.IndexAddr += FLASH_PAGE_SIZE;
    HAL_FLASH_Lock(); //锁住Flash
  }

  // uint16_t i = 0;
	// FLASH_EraseInitTypeDef My_Flash;  //声明 FLASH_EraseInitTypeDef 结构体为 My_Flash
	// HAL_FLASH_Unlock();               //解锁Flash
	
	// __disable_irq();                             //擦除前关闭中断
	// My_Flash.TypeErase = FLASH_TYPEERASE_PAGES;  //标明Flash执行页面只做擦除操作
	// My_Flash.PageAddress = Addr;  //声明要擦除的地址
	// My_Flash.NbPages = 1;                        //说明要擦除的页数，此参数必须是Min_Data = 1和Max_Data =(最大页数-初始页的值)之间的值
			
	// uint32_t PageError = 0;                    //设置PageError,如果出现错误这个变量会被设置为出错的FLASH地址
	// HAL_FLASHEx_Erase(&My_Flash, &PageError);  //调用擦除函数擦除
	// __enable_irq();                            //擦除后打开中断
	
	// for(i = 0;i < len;i++)
	// {
	// 	HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, (Addr+(2*i)), _data[i]); //对Flash进行烧写，FLASH_TYPEPROGRAM_HALFWORD 声明操作的Flash地址的16位的，此外还有32位跟64位的操作，自行翻查HAL库的定义即可
	// }

	// HAL_FLASH_Lock(); //锁住Flash
}

/**
 * @Brief:Flash_EEPROM擦除
 * @Param:
 * @Return:
 * @Note:
 * @Author:
 */
void Flash_EP_Earse(void)
{
  FLASH_EraseInitTypeDef My_Flash;  //声明 FLASH_EraseInitTypeDef 结构体为 My_Flash
	HAL_FLASH_Unlock();               //解锁Flash
	
	__disable_irq();                             //擦除前关闭中断
	My_Flash.TypeErase = FLASH_TYPEERASE_PAGES;  //标明Flash执行页面只做擦除操作
	My_Flash.PageAddress = FLASH_EP.BASE_ADDR;  //声明要擦除的地址
	My_Flash.NbPages = FLASH_EP.PAGE_USE;       //说明要擦除的页数，此参数必须是Min_Data = 1和Max_Data =(最大页数-初始页的值)之间的值
			
	uint32_t PageError = 0;                    //设置PageError,如果出现错误这个变量会被设置为出错的FLASH地址
	HAL_FLASHEx_Erase(&My_Flash, &PageError);  //调用擦除函数擦除
	__enable_irq();                            //擦除后打开中断
}

