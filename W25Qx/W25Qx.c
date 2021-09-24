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
#include "W25Qx.h"

/* W25Qx的指令 */
uint8_t READ_ID[4] = {0x90, 0x00, 0x00, 0x00}; //读ID
uint8_t READ_STATUS[1] = {0x05};							 //检查线路是否繁忙
uint8_t WRITE_ENABLE[1] = {0x06};							 //写使能
uint8_t SECTOR_EARSE[1] = {0x20};							 //扇区擦除命令
uint8_t BLOCK_EARSE[1] = {0xD8};							 //块擦除命令
uint8_t PAGE_WRITE[1] = {0x02};								 //页编程命令
uint8_t READ_DATA[1] = {0x03};								 //读数据命令

#ifndef USE_FATFS
//工作区缓存大小（以字节为单位的闪存介质的最小擦除单元大小）
uint8_t Buffer[W25Qx_SectorBuff] = {0};

//数据参数结构体
typedef struct
{
  uint32_t BaseAddr;//数据的起始地址
  uint32_t EndAddr;//数据的结束地址
  uint32_t Length;//数据的长度
  uint32_t BaseAddr_Of_Sector;//数据起始地址所对齐的扇区基地址
  uint32_t EndAddr_Of_Sector; //数据结束地址所对齐的扇区基地址
  uint16_t Span_Sector;//数据跨过了多少个扇区
  uint32_t IndexAddr;//指示当前到了到了哪一地址
}DATA_PARAM;
#endif



/**
 * @Brief:读芯片ID
 * @Param:
 * @Return:
 * @Note:
 * @Author:
 */
uint16_t W25Qx_ReadID(void)
{
	uint8_t temp_id[2] = {0};// 接收缓存
	uint16_t ID = 0;//ID
	HAL_GPIO_WritePin(W25Qx_CS_Port, W25Qx_CS_Pin, GPIO_PIN_RESET);    // 使能CS
	HAL_SPI_Transmit(&hspi2, READ_ID, sizeof(READ_ID), 100);
	HAL_SPI_Receive(&hspi2, temp_id, 2, 100);
	HAL_GPIO_WritePin(W25Qx_CS_Port, W25Qx_CS_Pin, GPIO_PIN_SET);    // 失能CS

	ID = (((uint16_t)temp_id[0]) << 8) | temp_id[1];
//	Serial_println("ID = %x",ID);
	return ID;
}

/**
 * @Brief:打印相关参数
 * @Param:
 * @Return:
 * @Note:
 * @Author:
 */
void W25Qx_PrintInfo(void)
{
  Serial_println("\r\n----------------------------");
	Serial_println("W25Qx的型号为 : %s", W25Qx_NAME);
	Serial_println("W25QxFlash的大小 : %d字节",W25Qx_CapacityBuff);
  Serial_println("W25Qx块的大小 : %d字节",W25Qx_BlockBuff);
  Serial_println("W25Qx扇区的大小 : %d字节",W25Qx_SectorBuff);
  Serial_println("W25Qx页的大小 : %d字节",W25Qx_PageBuff);
  Serial_println("W25Qx块数量 : %d",W25Qx_BlockCnt);
  Serial_println("W25Qx扇区数量 : %d",W25Qx_SectorCnt);
  Serial_println("W25Qx页数量 : %d",W25Qx_PageCnt);
  Serial_println("----------------------------\r\n");
}

/**
 * @Brief:读SR状态寄存器
 * @Param:
 * @Return:
 * @Note:
 * @Author:
 */
uint8_t W25Qx_ReadSR(void)
{
  uint8_t status = 1;
  HAL_GPIO_WritePin(W25Qx_CS_Port, W25Qx_CS_Pin, GPIO_PIN_RESET);    // 使能CS
  HAL_SPI_Transmit(&hspi2, READ_STATUS, sizeof(READ_STATUS), 100);
  HAL_SPI_Receive(&hspi2, &status, 1, 100);
  HAL_GPIO_WritePin(W25Qx_CS_Port, W25Qx_CS_Pin, GPIO_PIN_SET);    // 失能CS
  return status;
}

/**
 * @Brief:繁忙时等待
 * @Param:
 * @Return:
 * @Note:
 * @Author:
 */
void W25Qx_WaitBusy(void)
{
  uint8_t status = 1;
  uint32_t timeCount = 0;
  do
  {
    timeCount++;
    if(timeCount > 0xFFFFFFFF) //等待超时
      return;

    status = W25Qx_ReadSR();
  }while((status & 0x01) == 0x01);
}

/**
 * @Brief:写使能
 * @Param:
 * @Return:
 * @Note:
 * @Author:
 */
void W25Qx_WriteEnable(void)
{
  HAL_GPIO_WritePin(W25Qx_CS_Port, W25Qx_CS_Pin, GPIO_PIN_RESET);    // 使能CS
  HAL_SPI_Transmit(&hspi2, WRITE_ENABLE, sizeof(WRITE_ENABLE), 100);
  HAL_GPIO_WritePin(W25Qx_CS_Port, W25Qx_CS_Pin, GPIO_PIN_SET);    // 失能CS
}

/**
 * @Brief:擦除扇区
 * @Param:
 * @Return:
 * @Note:
 * @Author:
 */
void W25Qx_EarseSector(uint32_t Addr)
{
  // 按照扇区擦除时，将地址按扇区对齐，也就是将地址对齐到该扇区的基地址
  // 每个扇区4096字节
  uint8_t addr_array[3] = {0};
  uint32_t n = Addr/W25Qx_SectorBuff;
  Addr = n*W25Qx_SectorBuff;
  addr_array[0] = (uint8_t)((Addr>>16)) & 0xff;
  addr_array[1] = (uint8_t)((Addr>>8)) & 0xff;
  addr_array[2] = (uint8_t)((Addr) & 0xff);

  W25Qx_WaitBusy();
  W25Qx_WriteEnable();

  HAL_GPIO_WritePin(W25Qx_CS_Port, W25Qx_CS_Pin, GPIO_PIN_RESET);    // 使能CS
  HAL_SPI_Transmit(&hspi2, SECTOR_EARSE, sizeof(SECTOR_EARSE), 100);
  HAL_SPI_Transmit(&hspi2, addr_array, sizeof(addr_array), 100);
  HAL_GPIO_WritePin(W25Qx_CS_Port, W25Qx_CS_Pin, GPIO_PIN_SET);    // 失能CS
}

/**
 * @Brief:擦除块
 * @Param:
 * @Return:
 * @Note:
 * @Author:
 */
void W25Qx_EarseBlock(uint32_t Addr)
{
  // 按照块擦除时，将地址按块对齐，也就是将地址对齐到该块的基地址
  // 每个块65536字节
  uint8_t addr_array[3] = {0};
  uint32_t n = Addr/W25Qx_BlockBuff;
  Addr = n*W25Qx_BlockBuff;
  addr_array[0] = (uint8_t)((Addr>>16)) & 0xff;
  addr_array[1] = (uint8_t)((Addr>>8)) & 0xff;
  addr_array[2] = (uint8_t)((Addr) & 0xff);

  W25Qx_WaitBusy();
  W25Qx_WriteEnable();

  HAL_GPIO_WritePin(W25Qx_CS_Port, W25Qx_CS_Pin, GPIO_PIN_RESET);    // 使能CS
  HAL_SPI_Transmit(&hspi2, BLOCK_EARSE, sizeof(BLOCK_EARSE), 100);
  HAL_SPI_Transmit(&hspi2, addr_array, sizeof(addr_array), 100);
  HAL_GPIO_WritePin(W25Qx_CS_Port, W25Qx_CS_Pin, GPIO_PIN_SET);    // 失能CS
}

/**
 * @Brief:页读
 * @Param:
 * @Return:
 * @Note:
 * @Author:
 */
void W25Qx_PageRead(uint32_t Addr, uint8_t *Data)
{
	// 按照页读时，将地址按页对齐，也就是将地址对齐到该页的基地址
	// 每页256字节
	uint8_t addr_array[3] = {0};
	uint32_t n = Addr / W25Qx_PageBuff;
	Addr = n * W25Qx_PageBuff;
	addr_array[0] = (uint8_t)((Addr >> 16)) & 0xff;
	addr_array[1] = (uint8_t)((Addr >> 8)) & 0xff;
	addr_array[2] = (uint8_t)((Addr)&0xff);

	W25Qx_WaitBusy();
	HAL_GPIO_WritePin(W25Qx_CS_Port, W25Qx_CS_Pin, GPIO_PIN_RESET); // 使能CS
	HAL_SPI_Transmit(&hspi2, READ_DATA, sizeof(READ_DATA), 100);
	HAL_SPI_Transmit(&hspi2, addr_array, sizeof(addr_array), 100);
	HAL_SPI_Receive(&hspi2, Data, W25Qx_PageBuff, 100);
	HAL_GPIO_WritePin(W25Qx_CS_Port, W25Qx_CS_Pin, GPIO_PIN_SET); // 失能CS
}

/**
 * @Brief:页写（不校验）
 * @Param:
 * @Return:
 * @Note:
 * @Author:
 */
void W25Qx_PageWrite_NoCheck(uint32_t Addr,uint8_t* Data)
{
  // 按照页写时，将地址按页对齐，也就是将地址对齐到该页的基地址
  // 每页256字节
  uint8_t addr_array[3] = {0};
  uint32_t n = Addr/W25Qx_PageBuff;
  Addr = n*W25Qx_PageBuff;
  addr_array[0] = (uint8_t)((Addr>>16)) & 0xff;
  addr_array[1] = (uint8_t)((Addr>>8)) & 0xff;
  addr_array[2] = (uint8_t)((Addr) & 0xff);
  
  W25Qx_WaitBusy();
  W25Qx_WriteEnable();
	
  HAL_GPIO_WritePin(W25Qx_CS_Port, W25Qx_CS_Pin, GPIO_PIN_RESET);    // 使能CS
  HAL_SPI_Transmit(&hspi2, PAGE_WRITE, sizeof(PAGE_WRITE), 100);
  HAL_SPI_Transmit(&hspi2, addr_array, sizeof(addr_array), 100);
	HAL_SPI_Transmit(&hspi2, Data, W25Qx_PageBuff, 100);						 //发送要写的数据
	HAL_GPIO_WritePin(W25Qx_CS_Port, W25Qx_CS_Pin, GPIO_PIN_SET);    // 失能CS
}

// /**
//  * @Brief:页写
//  * @Param:
//  * @Return:
//  * @Note:
//  * @Author:
//  */
// void W25Qx_PageWrite(uint32_t Addr, uint8_t *Data)
// {
// 	// 按照页写时，将地址按页对齐，也就是将地址对齐到该页的基地址
// 	// 每页256字节
// 	uint8_t addr_array[3] = {0};
// 	uint32_t n = Addr / W25Qx_PageBuff;
// 	Addr = n * W25Qx_PageBuff;
// 	addr_array[0] = (uint8_t)((Addr >> 16)) & 0xff;
// 	addr_array[1] = (uint8_t)((Addr >> 8)) & 0xff;
// 	addr_array[2] = (uint8_t)((Addr)&0xff);

// 	/* 先读出PageWrite中的数据 */

// 	W25Qx_WaitBusy();
// 	W25Qx_WriteEnable();

// 	HAL_GPIO_WritePin(W25Qx_CS_Port, W25Qx_CS_Pin, GPIO_PIN_RESET); // 使能CS
// 	HAL_SPI_Transmit(&hspi2, PAGE_WRITE, sizeof(PAGE_WRITE), 100);
// 	HAL_SPI_Transmit(&hspi2, addr_array, sizeof(addr_array), 100);
// 	HAL_SPI_Transmit(&hspi2, Data, W25Qx_PageBuff, 100);					//发送要写的数据
// 	HAL_GPIO_WritePin(W25Qx_CS_Port, W25Qx_CS_Pin, GPIO_PIN_SET); // 失能CS
// }

/**
 * @Brief:扇区读
 * @Param:
 * @Return:
 * @Note:
 * @Author:
 */
void W25QX_SectorRead(uint32_t Addr, uint8_t *Data)
{
	uint8_t addr_array[3] = {0};
	uint32_t n = Addr / W25Qx_SectorBuff;
	Addr = n * W25Qx_SectorBuff;
	addr_array[0] = (uint8_t)((Addr >> 16)) & 0xff;
	addr_array[1] = (uint8_t)((Addr >> 8)) & 0xff;
	addr_array[2] = (uint8_t)((Addr)&0xff);

	W25Qx_WaitBusy();
	HAL_GPIO_WritePin(W25Qx_CS_Port, W25Qx_CS_Pin, GPIO_PIN_RESET); // 使能CS
	HAL_SPI_Transmit(&hspi2, READ_DATA, sizeof(READ_DATA), 100);
	HAL_SPI_Transmit(&hspi2, addr_array, sizeof(addr_array), 100);
	HAL_SPI_Receive(&hspi2, Data, W25Qx_SectorBuff, 100);
	HAL_GPIO_WritePin(W25Qx_CS_Port, W25Qx_CS_Pin, GPIO_PIN_SET); // 失能CS
}

/**
 * @Brief:扇区写
 * @Param:
 * @Return:
 * @Note:
 * @Author:
 */
void W25Qx_SectorWrite_NoCheck(uint32_t Addr,uint8_t* Data)
{
  uint32_t Page_Addr = Addr;//页地址
  uint32_t Data_Index = 0;
  for (uint32_t i = 0; i < (W25Qx_SectorBuff/W25Qx_PageBuff); i++)//每个扇区16页
  {
    W25Qx_PageWrite_NoCheck(Page_Addr,&Data[Data_Index]);
    Page_Addr+=W25Qx_PageBuff;
    Data_Index+=W25Qx_PageBuff;
  }
}





// ----------------------------------------------------------------------------

#ifdef USE_FATFS /* 该部分用于接入FATFS的文件系统API */

/**
 * @Brief:Fatfs获取获取设备状态
 * @Param:
 * @Return:
 * @Note:
 * @Author:
 */
bool FF_W25Qx_Status(void)
{
	/* SPI Falsh设备没有设备状态，那么就直接返回true */
	return true;
}

/**
 * @Brief:FatFs初始化W25Qx芯片
 * @Param:
 * @Return:
 * @Note:
 * @Author:
 */
bool FF_W25Qx_Init(void)
{
	/* 这里判断读取的芯片ID是否相同即可 */
	uint16_t ReadID = W25Qx_ReadID();

	if (ReadID == W25Qx_ID)
		return true;
	else
		return false;
}

/**
 * @Brief:FatFs扇区读W25Qx芯片
 * @Param:
 * @Return:
 * @Note:
 * @Author:
 */
bool FF_W25Qx_SectorRead(BYTE *buff, DWORD sector, UINT count)
{
	uint32_t index = 0;
	uint32_t addr = sector * W25Qx_SectorBuff;
//	Info_Println("sector:%ld;count:%d;addr:%d",sector,count,addr);
	/* 这里可能还需要断言 */
	for (uint32_t i = 0; i < count; i++)
	{
		W25QX_SectorRead(addr, &buff[index]);
		addr += W25Qx_SectorBuff;
		index += W25Qx_SectorBuff;
	}

	return true;
}

/**
 * @Brief:FatFs扇区编程W25Qx芯片
 * @Param:
 * @Return:
 * @Note:
 * @Author:
 */
bool FF_W25Qx_SectoWrite(BYTE *buff, DWORD sector, UINT count)
{
	uint32_t index = 0;
	uint32_t addr = sector * W25Qx_SectorBuff;
//	Info_Println("sector:%ld;count:%d;addr:%d",sector,count,addr);

	/* 这里可能还需要断言 */
	for (uint32_t i = 0; i < count; i++)
	{
		W25Qx_EarseSector(addr);
		W25Qx_SectorWrite_NoCheck(addr, &buff[index]);
		addr += W25Qx_SectorBuff;
		index += W25Qx_SectorBuff;
	}

	return true;
}

#else /* 该部分是用户存储数据的参数 */

/**
 * @Brief:读数据
 * @Param:
 * @Return:
 * @Note:
 * @Author:
 */
void W25Qx_ReadData(uint32_t Addr,uint8_t* Data,uint32_t Length)
{
  uint8_t addr_array[3] = {0};
  addr_array[0] = (uint8_t)((Addr>>16)) & 0xff;
  addr_array[1] = (uint8_t)((Addr>>8)) & 0xff;
  addr_array[2] = (uint8_t)((Addr) & 0xff);
	
	W25Qx_WaitBusy();
  HAL_GPIO_WritePin(W25Qx_CS_Port, W25Qx_CS_Pin, GPIO_PIN_RESET);    // 使能CS
  HAL_SPI_Transmit(&hspi2, READ_DATA, sizeof(READ_DATA), 100);
  HAL_SPI_Transmit(&hspi2, addr_array, sizeof(addr_array), 100);
  HAL_SPI_Receive(&hspi2, Data, Length, 100);
  HAL_GPIO_WritePin(W25Qx_CS_Port, W25Qx_CS_Pin, GPIO_PIN_SET);    // 失能CS
}

extern void Print_Array(uint8_t* data, uint32_t Length);
/**
 * @Brief:写数据
 * @Param:
 * @Return:
 * @Note:
 * @Author:
 */
void W25Qx_WriteData(uint32_t Addr,uint8_t* Data,uint32_t Length)
{
  DATA_PARAM DataParam;
	DataParam.BaseAddr = Addr;
	DataParam.EndAddr = Addr + Length;
  /* 这里是一个防止写的超出Flash芯片的实际大小引起未知的错误的断言 */
  DataParam.EndAddr = DataParam.EndAddr > W25Qx_CapacityBuff ? W25Qx_CapacityBuff : DataParam.EndAddr;
  DataParam.Length = DataParam.EndAddr - DataParam.BaseAddr;//怕之前的数据超出大小，所以这里重新算一遍
	DataParam.BaseAddr_Of_Sector = (DataParam.BaseAddr/W25Qx_SectorBuff)*W25Qx_SectorBuff;
  DataParam.EndAddr_Of_Sector = (DataParam.EndAddr/W25Qx_SectorBuff)*W25Qx_SectorBuff;
  DataParam.Span_Sector = ((DataParam.EndAddr_Of_Sector - DataParam.BaseAddr_Of_Sector)/W25Qx_SectorBuff) + 1;
  
//  Serial_println("DataParam.BaseAddr = %d",DataParam.BaseAddr);
//  Serial_println("DataParam.EndAddr = %d",DataParam.EndAddr);
//  Serial_println("DataParam.BaseAddr_Of_Sector = %d",DataParam.BaseAddr_Of_Sector);
//  Serial_println("DataParam.EndAddr_Of_Sector = %d",DataParam.EndAddr_Of_Sector);
//  Serial_println("DataParam.Span_Sector = %d",DataParam.Span_Sector);
//  Serial_println("............");

  DataParam.IndexAddr = DataParam.BaseAddr_Of_Sector;//将索引地址指向数据起始地址所对齐的扇区基地址
  uint32_t count = 0;
  //代表需要在多少个扇区进行重复操作
  for (uint16_t i = 0; i < DataParam.Span_Sector; i++)
  {
    memset(Buffer,0x00,sizeof(Buffer));//使用Buffer前先清空数组避免影响
    // 先将对应扇区的数据读出到Buffer
    W25Qx_ReadData(DataParam.IndexAddr,Buffer,W25Qx_SectorBuff);
    // 擦除对应的扇区
    W25Qx_EarseSector(DataParam.IndexAddr);
    // 将要修改的数据写入Buffer
    for (uint32_t i = DataParam.IndexAddr; i < DataParam.IndexAddr + W25Qx_SectorBuff; i++)
    {
      if ((i >= DataParam.BaseAddr) && (i < DataParam.EndAddr))
      {
        Buffer[i-DataParam.IndexAddr] = Data[count++];
      }
    }
    // 将Buffer的数据写入对应的扇区
    W25Qx_SectorWrite_NoCheck(DataParam.IndexAddr,Buffer);
    DataParam.IndexAddr += W25Qx_SectorBuff;
  }
}

/**
 * @Brief:擦除W25QxFlash芯片
 * @Param:
 * @Return:
 * @Note:
 * @Author:
 */
void W25Qx_EarseChip(void)
{
  for (uint8_t i = 0; i < W25Qx_BlockCnt; i++)
  {
    W25Qx_EarseBlock(i*W25Qx_BlockBuff);
  }
}
#endif
