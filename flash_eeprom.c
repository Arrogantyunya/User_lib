/****************************************Copyright (c)****************************************************
 

**--------------File Info---------------------------------------------------------------------------------

** File name:flash_eeprom.c
** Last modified Date:

** Last Version:

** Descriptions:����HAL���FLASHģ��EEPROM�Ŀ�(֧��оƬSTM32F1)
**--------------------------------------------------------------------------------------------------------

** Created by:		���һ� 
** Created date:	2021/xx/xx

** Version:				V1.0
** Descriptions:
**--------------------------------------------------------------------------------------------------------*/
#include "flash_eeprom.h"

FLASH_EP_INFO FLASH_EP; 

/**
 * @Brief:Flash_EEPROM��ʼ��
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
 * @Brief:Flash_EEPROM��Ϣ��ӡ
 * @Param:
 * @Return:
 * @Note:
 * @Author:
 */
void Flash_EP_Info(void)
{
  Serial_println("\r\n---------------------------");
  Serial_println("Flash���ܴ�СΪ%d�ֽ�",FLASH_SIZE);
  Serial_println("Flash�ĵ�ַ����Ϊ:[0x%08x - 0x%08x)",FLASH_BASE_ADDR,FLASH_END_ADDR);
  Serial_println("Flash��ҳ��СΪ%d�ֽ�",FLASH_PAGE_SIZE);
  Serial_println("Flash��ҳ����Ϊ%d",FLASH_PAGE_COUNT);
  Serial_println("Flash����С��̴�СΪ%d�ֽ�",FLASH_Program_SIZE);

  Serial_println("Flash_EP����ʹ�õ�ҳ��Ϊ%d",FLASH_EP.PAGE_USE);
  Serial_println("Flash_EP���ܴ�СΪ%d",FLASH_EP.SIZE);
  Serial_println("Flash_EP�ĵĵ�ַ����Ϊ:[0x%08x - 0x%08x)",FLASH_EP.BASE_ADDR,FLASH_EP.END_ADDR);
  Serial_println("---------------------------\r\n");
}

/**
 * @Brief:Flash_EEPROM��
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
	/* ������һ����ֹд���ݳ���FlashоƬ��ʵ�ʴ�С����δ֪�Ĵ���Ķ��� */
  DataParam.EndAddr = DataParam.EndAddr > FLASH_END_ADDR ? FLASH_END_ADDR : DataParam.EndAddr;
  DataParam.Length = DataParam.EndAddr - DataParam.BaseAddr; //��֮ǰ�����ݳ�����С����������������һ��

  for (uint16_t i = 0; i < DataParam.Length; i++)
  {
		_data[i] = *(__IO uint8_t *)(DataParam.BaseAddr + i);
//    _data[i] = *(__IO uint16_t *)(Addr + (2 * i)); //*(__IO uint16_t *)�Ƕ�ȡ�õ�ַ�Ĳ���ֵ,��ֵΪ16λ����,һ�ζ�ȡ�����ֽڣ�*(__IO uint32_t *)��һ�ζ�4���ֽ�
  }
}

/**
 * @Brief:Flash_EEPROMд
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
  /* ������һ����ֹд���ݳ���FlashоƬ��ʵ�ʴ�С����δ֪�Ĵ���Ķ��� */
  DataParam.EndAddr = DataParam.EndAddr > FLASH_END_ADDR ? FLASH_END_ADDR : DataParam.EndAddr;
  DataParam.Length = DataParam.EndAddr - DataParam.BaseAddr; //��֮ǰ�����ݳ�����С����������������һ��
  DataParam.BaseAddr_Of_Page = (DataParam.BaseAddr / FLASH_PAGE_SIZE) * FLASH_PAGE_SIZE;
  DataParam.EndAddr_Of_Page = (DataParam.EndAddr / FLASH_PAGE_SIZE) * FLASH_PAGE_SIZE;
  DataParam.Span_Page = ((DataParam.EndAddr_Of_Page - DataParam.BaseAddr_Of_Page) / FLASH_PAGE_SIZE) + 1;
//  Serial_println("DataParam.BaseAddr = 0x%08x",DataParam.BaseAddr);
//  Serial_println("DataParam.EndAddr = 0x%08x",DataParam.EndAddr);
//  Serial_println("DataParam.BaseAddr_Of_Page = 0x%08x", DataParam.BaseAddr_Of_Page);
//  Serial_println("DataParam.EndAddr_Of_Page = 0x%08x", DataParam.EndAddr_Of_Page);
//  Serial_println("DataParam.Span_Page = %d", DataParam.Span_Page);
//  Serial_println("............");

  DataParam.IndexAddr = DataParam.BaseAddr_Of_Page; //��������ַָ��������ʼ��ַ�������ҳ����ַ
  uint32_t count = 0;
  //������Ҫ�ڶ��ٸ�ҳ�����ظ�����
  for (uint16_t i = 0; i < DataParam.Span_Page; i++)
  {
    memset(FLASH_EP.DB.U8Array, 0x00, sizeof(FLASH_EP.DB.U8Array)); //ʹ��FLASH_EP.DBǰ������������Ӱ��
    /* �Ƚ���Ӧ���������ݶ�����FLASH_EP.DB */
    Flash_EP_Read(DataParam.IndexAddr - FLASH_EP.BASE_ADDR, FLASH_EP.DB.U8Array, FLASH_PAGE_SIZE);
    /* ������Ӧ������ */
    FLASH_EraseInitTypeDef My_Flash; //���� FLASH_EraseInitTypeDef �ṹ��Ϊ My_Flash
    HAL_FLASH_Unlock();              //����Flash
    __disable_irq();                            //����ǰ�ر��ж�
    My_Flash.TypeErase = FLASH_TYPEERASE_PAGES; //����Flashִ��ҳ��ֻ����������
    My_Flash.PageAddress = DataParam.IndexAddr; //����Ҫ�����ĵ�ַ
    My_Flash.NbPages = 1;     //˵��Ҫ������ҳ�����˲���������Min_Data = 1��Max_Data =(���ҳ��-��ʼҳ��ֵ)֮���ֵ
    uint32_t PageError = 0;                   //����PageError,������ִ�����������ᱻ����Ϊ�����FLASH��ַ
    HAL_FLASHEx_Erase(&My_Flash, &PageError); //���ò�����������
    __enable_irq();                           //��������ж�
    /* ��Ҫ�޸ĵ�����д��FLASH_EP.DB */
    for (uint32_t i = DataParam.IndexAddr; i < DataParam.IndexAddr + FLASH_PAGE_SIZE; i++)
    {
      if ((i >= DataParam.BaseAddr) && (i < DataParam.EndAddr))
      {
        FLASH_EP.DB.U8Array[i - DataParam.IndexAddr] = _data[count++];
      }
    }
    /* ��FLASH_EP.DB.U8Array������д���Ӧ������ */
    for (uint16_t i = 0; i < Flash_EP_BUFFER_SIZE; i++)
    {
			#if (FLASH_Program_SIZE == 1)
//				HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, (DataParam.IndexAddr + (FLASH_Program_SIZE * i)), FLASH_EP.DB.Buffer[i]); //��Flash���б��
			#elif (FLASH_Program_SIZE == 2)
				HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, (DataParam.IndexAddr + (FLASH_Program_SIZE * i)), FLASH_EP.DB.Buffer[i]); //��Flash���б��
			#elif (FLASH_Program_SIZE == 4)
				HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, (DataParam.IndexAddr + (FLASH_Program_SIZE * i)), FLASH_EP.DB.Buffer[i]); //��Flash���б��
			#elif (FLASH_Program_SIZE == 8)
				HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, (DataParam.IndexAddr + (FLASH_Program_SIZE * i)), FLASH_EP.DB.Buffer[i]); //��Flash���б��
			#endif
    }
    DataParam.IndexAddr += FLASH_PAGE_SIZE;
    HAL_FLASH_Lock(); //��סFlash
  }

  // uint16_t i = 0;
	// FLASH_EraseInitTypeDef My_Flash;  //���� FLASH_EraseInitTypeDef �ṹ��Ϊ My_Flash
	// HAL_FLASH_Unlock();               //����Flash
	
	// __disable_irq();                             //����ǰ�ر��ж�
	// My_Flash.TypeErase = FLASH_TYPEERASE_PAGES;  //����Flashִ��ҳ��ֻ����������
	// My_Flash.PageAddress = Addr;  //����Ҫ�����ĵ�ַ
	// My_Flash.NbPages = 1;                        //˵��Ҫ������ҳ�����˲���������Min_Data = 1��Max_Data =(���ҳ��-��ʼҳ��ֵ)֮���ֵ
			
	// uint32_t PageError = 0;                    //����PageError,������ִ�����������ᱻ����Ϊ�����FLASH��ַ
	// HAL_FLASHEx_Erase(&My_Flash, &PageError);  //���ò�����������
	// __enable_irq();                            //��������ж�
	
	// for(i = 0;i < len;i++)
	// {
	// 	HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, (Addr+(2*i)), _data[i]); //��Flash������д��FLASH_TYPEPROGRAM_HALFWORD ����������Flash��ַ��16λ�ģ����⻹��32λ��64λ�Ĳ��������з���HAL��Ķ��弴��
	// }

	// HAL_FLASH_Lock(); //��סFlash
}

/**
 * @Brief:Flash_EEPROM����
 * @Param:
 * @Return:
 * @Note:
 * @Author:
 */
void Flash_EP_Earse(void)
{
  FLASH_EraseInitTypeDef My_Flash;  //���� FLASH_EraseInitTypeDef �ṹ��Ϊ My_Flash
	HAL_FLASH_Unlock();               //����Flash
	
	__disable_irq();                             //����ǰ�ر��ж�
	My_Flash.TypeErase = FLASH_TYPEERASE_PAGES;  //����Flashִ��ҳ��ֻ����������
	My_Flash.PageAddress = FLASH_EP.BASE_ADDR;  //����Ҫ�����ĵ�ַ
	My_Flash.NbPages = FLASH_EP.PAGE_USE;       //˵��Ҫ������ҳ�����˲���������Min_Data = 1��Max_Data =(���ҳ��-��ʼҳ��ֵ)֮���ֵ
			
	uint32_t PageError = 0;                    //����PageError,������ִ�����������ᱻ����Ϊ�����FLASH��ַ
	HAL_FLASHEx_Erase(&My_Flash, &PageError);  //���ò�����������
	__enable_irq();                            //��������ж�
}

