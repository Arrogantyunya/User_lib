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
#include "W25Qx.h"

/* W25Qx��ָ�� */
uint8_t READ_ID[4] = {0x90, 0x00, 0x00, 0x00}; //��ID
uint8_t READ_STATUS[1] = {0x05};							 //�����·�Ƿ�æ
uint8_t WRITE_ENABLE[1] = {0x06};							 //дʹ��
uint8_t SECTOR_EARSE[1] = {0x20};							 //������������
uint8_t BLOCK_EARSE[1] = {0xD8};							 //���������
uint8_t PAGE_WRITE[1] = {0x02};								 //ҳ�������
uint8_t READ_DATA[1] = {0x03};								 //����������

#ifndef USE_FATFS
//�����������С�����ֽ�Ϊ��λ��������ʵ���С������Ԫ��С��
uint8_t Buffer[W25Qx_SectorBuff] = {0};

//���ݲ����ṹ��
typedef struct
{
  uint32_t BaseAddr;//���ݵ���ʼ��ַ
  uint32_t EndAddr;//���ݵĽ�����ַ
  uint32_t Length;//���ݵĳ���
  uint32_t BaseAddr_Of_Sector;//������ʼ��ַ���������������ַ
  uint32_t EndAddr_Of_Sector; //���ݽ�����ַ���������������ַ
  uint16_t Span_Sector;//���ݿ���˶��ٸ�����
  uint32_t IndexAddr;//ָʾ��ǰ���˵�����һ��ַ
}DATA_PARAM;
#endif



/**
 * @Brief:��оƬID
 * @Param:
 * @Return:
 * @Note:
 * @Author:
 */
uint16_t W25Qx_ReadID(void)
{
	uint8_t temp_id[2] = {0};// ���ջ���
	uint16_t ID = 0;//ID
	HAL_GPIO_WritePin(W25Qx_CS_Port, W25Qx_CS_Pin, GPIO_PIN_RESET);    // ʹ��CS
	HAL_SPI_Transmit(&hspi2, READ_ID, sizeof(READ_ID), 100);
	HAL_SPI_Receive(&hspi2, temp_id, 2, 100);
	HAL_GPIO_WritePin(W25Qx_CS_Port, W25Qx_CS_Pin, GPIO_PIN_SET);    // ʧ��CS

	ID = (((uint16_t)temp_id[0]) << 8) | temp_id[1];
//	Serial_println("ID = %x",ID);
	return ID;
}

/**
 * @Brief:��ӡ��ز���
 * @Param:
 * @Return:
 * @Note:
 * @Author:
 */
void W25Qx_PrintInfo(void)
{
  Serial_println("\r\n----------------------------");
	Serial_println("W25Qx���ͺ�Ϊ : %s", W25Qx_NAME);
	Serial_println("W25QxFlash�Ĵ�С : %d�ֽ�",W25Qx_CapacityBuff);
  Serial_println("W25Qx��Ĵ�С : %d�ֽ�",W25Qx_BlockBuff);
  Serial_println("W25Qx�����Ĵ�С : %d�ֽ�",W25Qx_SectorBuff);
  Serial_println("W25Qxҳ�Ĵ�С : %d�ֽ�",W25Qx_PageBuff);
  Serial_println("W25Qx������ : %d",W25Qx_BlockCnt);
  Serial_println("W25Qx�������� : %d",W25Qx_SectorCnt);
  Serial_println("W25Qxҳ���� : %d",W25Qx_PageCnt);
  Serial_println("----------------------------\r\n");
}

/**
 * @Brief:��SR״̬�Ĵ���
 * @Param:
 * @Return:
 * @Note:
 * @Author:
 */
uint8_t W25Qx_ReadSR(void)
{
  uint8_t status = 1;
  HAL_GPIO_WritePin(W25Qx_CS_Port, W25Qx_CS_Pin, GPIO_PIN_RESET);    // ʹ��CS
  HAL_SPI_Transmit(&hspi2, READ_STATUS, sizeof(READ_STATUS), 100);
  HAL_SPI_Receive(&hspi2, &status, 1, 100);
  HAL_GPIO_WritePin(W25Qx_CS_Port, W25Qx_CS_Pin, GPIO_PIN_SET);    // ʧ��CS
  return status;
}

/**
 * @Brief:��æʱ�ȴ�
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
    if(timeCount > 0xFFFFFFFF) //�ȴ���ʱ
      return;

    status = W25Qx_ReadSR();
  }while((status & 0x01) == 0x01);
}

/**
 * @Brief:дʹ��
 * @Param:
 * @Return:
 * @Note:
 * @Author:
 */
void W25Qx_WriteEnable(void)
{
  HAL_GPIO_WritePin(W25Qx_CS_Port, W25Qx_CS_Pin, GPIO_PIN_RESET);    // ʹ��CS
  HAL_SPI_Transmit(&hspi2, WRITE_ENABLE, sizeof(WRITE_ENABLE), 100);
  HAL_GPIO_WritePin(W25Qx_CS_Port, W25Qx_CS_Pin, GPIO_PIN_SET);    // ʧ��CS
}

/**
 * @Brief:��������
 * @Param:
 * @Return:
 * @Note:
 * @Author:
 */
void W25Qx_EarseSector(uint32_t Addr)
{
  // ������������ʱ������ַ���������룬Ҳ���ǽ���ַ���뵽�������Ļ���ַ
  // ÿ������4096�ֽ�
  uint8_t addr_array[3] = {0};
  uint32_t n = Addr/W25Qx_SectorBuff;
  Addr = n*W25Qx_SectorBuff;
  addr_array[0] = (uint8_t)((Addr>>16)) & 0xff;
  addr_array[1] = (uint8_t)((Addr>>8)) & 0xff;
  addr_array[2] = (uint8_t)((Addr) & 0xff);

  W25Qx_WaitBusy();
  W25Qx_WriteEnable();

  HAL_GPIO_WritePin(W25Qx_CS_Port, W25Qx_CS_Pin, GPIO_PIN_RESET);    // ʹ��CS
  HAL_SPI_Transmit(&hspi2, SECTOR_EARSE, sizeof(SECTOR_EARSE), 100);
  HAL_SPI_Transmit(&hspi2, addr_array, sizeof(addr_array), 100);
  HAL_GPIO_WritePin(W25Qx_CS_Port, W25Qx_CS_Pin, GPIO_PIN_SET);    // ʧ��CS
}

/**
 * @Brief:������
 * @Param:
 * @Return:
 * @Note:
 * @Author:
 */
void W25Qx_EarseBlock(uint32_t Addr)
{
  // ���տ����ʱ������ַ������룬Ҳ���ǽ���ַ���뵽�ÿ�Ļ���ַ
  // ÿ����65536�ֽ�
  uint8_t addr_array[3] = {0};
  uint32_t n = Addr/W25Qx_BlockBuff;
  Addr = n*W25Qx_BlockBuff;
  addr_array[0] = (uint8_t)((Addr>>16)) & 0xff;
  addr_array[1] = (uint8_t)((Addr>>8)) & 0xff;
  addr_array[2] = (uint8_t)((Addr) & 0xff);

  W25Qx_WaitBusy();
  W25Qx_WriteEnable();

  HAL_GPIO_WritePin(W25Qx_CS_Port, W25Qx_CS_Pin, GPIO_PIN_RESET);    // ʹ��CS
  HAL_SPI_Transmit(&hspi2, BLOCK_EARSE, sizeof(BLOCK_EARSE), 100);
  HAL_SPI_Transmit(&hspi2, addr_array, sizeof(addr_array), 100);
  HAL_GPIO_WritePin(W25Qx_CS_Port, W25Qx_CS_Pin, GPIO_PIN_SET);    // ʧ��CS
}

/**
 * @Brief:ҳ��
 * @Param:
 * @Return:
 * @Note:
 * @Author:
 */
void W25Qx_PageRead(uint32_t Addr, uint8_t *Data)
{
	// ����ҳ��ʱ������ַ��ҳ���룬Ҳ���ǽ���ַ���뵽��ҳ�Ļ���ַ
	// ÿҳ256�ֽ�
	uint8_t addr_array[3] = {0};
	uint32_t n = Addr / W25Qx_PageBuff;
	Addr = n * W25Qx_PageBuff;
	addr_array[0] = (uint8_t)((Addr >> 16)) & 0xff;
	addr_array[1] = (uint8_t)((Addr >> 8)) & 0xff;
	addr_array[2] = (uint8_t)((Addr)&0xff);

	W25Qx_WaitBusy();
	HAL_GPIO_WritePin(W25Qx_CS_Port, W25Qx_CS_Pin, GPIO_PIN_RESET); // ʹ��CS
	HAL_SPI_Transmit(&hspi2, READ_DATA, sizeof(READ_DATA), 100);
	HAL_SPI_Transmit(&hspi2, addr_array, sizeof(addr_array), 100);
	HAL_SPI_Receive(&hspi2, Data, W25Qx_PageBuff, 100);
	HAL_GPIO_WritePin(W25Qx_CS_Port, W25Qx_CS_Pin, GPIO_PIN_SET); // ʧ��CS
}

/**
 * @Brief:ҳд����У�飩
 * @Param:
 * @Return:
 * @Note:
 * @Author:
 */
void W25Qx_PageWrite_NoCheck(uint32_t Addr,uint8_t* Data)
{
  // ����ҳдʱ������ַ��ҳ���룬Ҳ���ǽ���ַ���뵽��ҳ�Ļ���ַ
  // ÿҳ256�ֽ�
  uint8_t addr_array[3] = {0};
  uint32_t n = Addr/W25Qx_PageBuff;
  Addr = n*W25Qx_PageBuff;
  addr_array[0] = (uint8_t)((Addr>>16)) & 0xff;
  addr_array[1] = (uint8_t)((Addr>>8)) & 0xff;
  addr_array[2] = (uint8_t)((Addr) & 0xff);
  
  W25Qx_WaitBusy();
  W25Qx_WriteEnable();
	
  HAL_GPIO_WritePin(W25Qx_CS_Port, W25Qx_CS_Pin, GPIO_PIN_RESET);    // ʹ��CS
  HAL_SPI_Transmit(&hspi2, PAGE_WRITE, sizeof(PAGE_WRITE), 100);
  HAL_SPI_Transmit(&hspi2, addr_array, sizeof(addr_array), 100);
	HAL_SPI_Transmit(&hspi2, Data, W25Qx_PageBuff, 100);						 //����Ҫд������
	HAL_GPIO_WritePin(W25Qx_CS_Port, W25Qx_CS_Pin, GPIO_PIN_SET);    // ʧ��CS
}

// /**
//  * @Brief:ҳд
//  * @Param:
//  * @Return:
//  * @Note:
//  * @Author:
//  */
// void W25Qx_PageWrite(uint32_t Addr, uint8_t *Data)
// {
// 	// ����ҳдʱ������ַ��ҳ���룬Ҳ���ǽ���ַ���뵽��ҳ�Ļ���ַ
// 	// ÿҳ256�ֽ�
// 	uint8_t addr_array[3] = {0};
// 	uint32_t n = Addr / W25Qx_PageBuff;
// 	Addr = n * W25Qx_PageBuff;
// 	addr_array[0] = (uint8_t)((Addr >> 16)) & 0xff;
// 	addr_array[1] = (uint8_t)((Addr >> 8)) & 0xff;
// 	addr_array[2] = (uint8_t)((Addr)&0xff);

// 	/* �ȶ���PageWrite�е����� */

// 	W25Qx_WaitBusy();
// 	W25Qx_WriteEnable();

// 	HAL_GPIO_WritePin(W25Qx_CS_Port, W25Qx_CS_Pin, GPIO_PIN_RESET); // ʹ��CS
// 	HAL_SPI_Transmit(&hspi2, PAGE_WRITE, sizeof(PAGE_WRITE), 100);
// 	HAL_SPI_Transmit(&hspi2, addr_array, sizeof(addr_array), 100);
// 	HAL_SPI_Transmit(&hspi2, Data, W25Qx_PageBuff, 100);					//����Ҫд������
// 	HAL_GPIO_WritePin(W25Qx_CS_Port, W25Qx_CS_Pin, GPIO_PIN_SET); // ʧ��CS
// }

/**
 * @Brief:������
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
	HAL_GPIO_WritePin(W25Qx_CS_Port, W25Qx_CS_Pin, GPIO_PIN_RESET); // ʹ��CS
	HAL_SPI_Transmit(&hspi2, READ_DATA, sizeof(READ_DATA), 100);
	HAL_SPI_Transmit(&hspi2, addr_array, sizeof(addr_array), 100);
	HAL_SPI_Receive(&hspi2, Data, W25Qx_SectorBuff, 100);
	HAL_GPIO_WritePin(W25Qx_CS_Port, W25Qx_CS_Pin, GPIO_PIN_SET); // ʧ��CS
}

/**
 * @Brief:����д
 * @Param:
 * @Return:
 * @Note:
 * @Author:
 */
void W25Qx_SectorWrite_NoCheck(uint32_t Addr,uint8_t* Data)
{
  uint32_t Page_Addr = Addr;//ҳ��ַ
  uint32_t Data_Index = 0;
  for (uint32_t i = 0; i < (W25Qx_SectorBuff/W25Qx_PageBuff); i++)//ÿ������16ҳ
  {
    W25Qx_PageWrite_NoCheck(Page_Addr,&Data[Data_Index]);
    Page_Addr+=W25Qx_PageBuff;
    Data_Index+=W25Qx_PageBuff;
  }
}





// ----------------------------------------------------------------------------

#ifdef USE_FATFS /* �ò������ڽ���FATFS���ļ�ϵͳAPI */

/**
 * @Brief:Fatfs��ȡ��ȡ�豸״̬
 * @Param:
 * @Return:
 * @Note:
 * @Author:
 */
bool FF_W25Qx_Status(void)
{
	/* SPI Falsh�豸û���豸״̬����ô��ֱ�ӷ���true */
	return true;
}

/**
 * @Brief:FatFs��ʼ��W25QxоƬ
 * @Param:
 * @Return:
 * @Note:
 * @Author:
 */
bool FF_W25Qx_Init(void)
{
	/* �����ж϶�ȡ��оƬID�Ƿ���ͬ���� */
	uint16_t ReadID = W25Qx_ReadID();

	if (ReadID == W25Qx_ID)
		return true;
	else
		return false;
}

/**
 * @Brief:FatFs������W25QxоƬ
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
	/* ������ܻ���Ҫ���� */
	for (uint32_t i = 0; i < count; i++)
	{
		W25QX_SectorRead(addr, &buff[index]);
		addr += W25Qx_SectorBuff;
		index += W25Qx_SectorBuff;
	}

	return true;
}

/**
 * @Brief:FatFs�������W25QxоƬ
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

	/* ������ܻ���Ҫ���� */
	for (uint32_t i = 0; i < count; i++)
	{
		W25Qx_EarseSector(addr);
		W25Qx_SectorWrite_NoCheck(addr, &buff[index]);
		addr += W25Qx_SectorBuff;
		index += W25Qx_SectorBuff;
	}

	return true;
}

#else /* �ò������û��洢���ݵĲ��� */

/**
 * @Brief:������
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
  HAL_GPIO_WritePin(W25Qx_CS_Port, W25Qx_CS_Pin, GPIO_PIN_RESET);    // ʹ��CS
  HAL_SPI_Transmit(&hspi2, READ_DATA, sizeof(READ_DATA), 100);
  HAL_SPI_Transmit(&hspi2, addr_array, sizeof(addr_array), 100);
  HAL_SPI_Receive(&hspi2, Data, Length, 100);
  HAL_GPIO_WritePin(W25Qx_CS_Port, W25Qx_CS_Pin, GPIO_PIN_SET);    // ʧ��CS
}

extern void Print_Array(uint8_t* data, uint32_t Length);
/**
 * @Brief:д����
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
  /* ������һ����ֹд�ĳ���FlashоƬ��ʵ�ʴ�С����δ֪�Ĵ���Ķ��� */
  DataParam.EndAddr = DataParam.EndAddr > W25Qx_CapacityBuff ? W25Qx_CapacityBuff : DataParam.EndAddr;
  DataParam.Length = DataParam.EndAddr - DataParam.BaseAddr;//��֮ǰ�����ݳ�����С����������������һ��
	DataParam.BaseAddr_Of_Sector = (DataParam.BaseAddr/W25Qx_SectorBuff)*W25Qx_SectorBuff;
  DataParam.EndAddr_Of_Sector = (DataParam.EndAddr/W25Qx_SectorBuff)*W25Qx_SectorBuff;
  DataParam.Span_Sector = ((DataParam.EndAddr_Of_Sector - DataParam.BaseAddr_Of_Sector)/W25Qx_SectorBuff) + 1;
  
//  Serial_println("DataParam.BaseAddr = %d",DataParam.BaseAddr);
//  Serial_println("DataParam.EndAddr = %d",DataParam.EndAddr);
//  Serial_println("DataParam.BaseAddr_Of_Sector = %d",DataParam.BaseAddr_Of_Sector);
//  Serial_println("DataParam.EndAddr_Of_Sector = %d",DataParam.EndAddr_Of_Sector);
//  Serial_println("DataParam.Span_Sector = %d",DataParam.Span_Sector);
//  Serial_println("............");

  DataParam.IndexAddr = DataParam.BaseAddr_Of_Sector;//��������ַָ��������ʼ��ַ���������������ַ
  uint32_t count = 0;
  //������Ҫ�ڶ��ٸ����������ظ�����
  for (uint16_t i = 0; i < DataParam.Span_Sector; i++)
  {
    memset(Buffer,0x00,sizeof(Buffer));//ʹ��Bufferǰ������������Ӱ��
    // �Ƚ���Ӧ���������ݶ�����Buffer
    W25Qx_ReadData(DataParam.IndexAddr,Buffer,W25Qx_SectorBuff);
    // ������Ӧ������
    W25Qx_EarseSector(DataParam.IndexAddr);
    // ��Ҫ�޸ĵ�����д��Buffer
    for (uint32_t i = DataParam.IndexAddr; i < DataParam.IndexAddr + W25Qx_SectorBuff; i++)
    {
      if ((i >= DataParam.BaseAddr) && (i < DataParam.EndAddr))
      {
        Buffer[i-DataParam.IndexAddr] = Data[count++];
      }
    }
    // ��Buffer������д���Ӧ������
    W25Qx_SectorWrite_NoCheck(DataParam.IndexAddr,Buffer);
    DataParam.IndexAddr += W25Qx_SectorBuff;
  }
}

/**
 * @Brief:����W25QxFlashоƬ
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
