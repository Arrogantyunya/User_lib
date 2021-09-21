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
#include "W9864G6KH.h"

/**
 * @Brief:W9864G6KH�ϵ��ʼ��ʱ��
 * @Param:
 * @Return:
 * @Note:
 * @Author:
 */
void W9864G6KH_Init_Sequence(void)
{
	FMC_SDRAM_CommandTypeDef FMC_SDRAMCommandStructure;

  /* Step 3:������������ṩ��SDRAM��ʱ�� */
  FMC_SDRAMCommandStructure.CommandMode = FMC_SDRAM_CMD_CLK_ENABLE;
  FMC_SDRAMCommandStructure.CommandTarget = FMC_SDRAM_CMD_TARGET_BANK1;
  FMC_SDRAMCommandStructure.AutoRefreshNumber = 1;
  FMC_SDRAMCommandStructure.ModeRegisterDefinition = 0;

  HAL_SDRAM_SendCommand(&hsdram1, &FMC_SDRAMCommandStructure, 0x1000);

	
  /* Step 4:��ʱ�ȴ�CLK�ȶ� */
  HAL_Delay(1);

	
  /* Step 5:������������е�bankԤ���*/
  FMC_SDRAMCommandStructure.CommandMode = FMC_SDRAM_CMD_PALL;
  FMC_SDRAMCommandStructure.CommandTarget = FMC_SDRAM_CMD_TARGET_BANK1;
  FMC_SDRAMCommandStructure.AutoRefreshNumber = 1;
  FMC_SDRAMCommandStructure.ModeRegisterDefinition = 0;

  HAL_SDRAM_SendCommand(&hsdram1, &FMC_SDRAMCommandStructure, 0x1000);


  /* Step 6:��������Զ�ˢ�£��Զ�ˢ����Ҫ���ٷ���2�Σ�*/
  FMC_SDRAMCommandStructure.CommandMode = FMC_SDRAM_CMD_AUTOREFRESH_MODE;
  FMC_SDRAMCommandStructure.CommandTarget = FMC_SDRAM_CMD_TARGET_BANK1;
  FMC_SDRAMCommandStructure.AutoRefreshNumber = 2;
  FMC_SDRAMCommandStructure.ModeRegisterDefinition = 0;

  HAL_SDRAM_SendCommand(&hsdram1, &FMC_SDRAMCommandStructure, 0x1000);


  /* Step 7:����sdram�Ĵ�������*/
  uint32_t mode_value;  //�ݴ����õ�ģʽֵ;0x21;00000000 0010 0001;
  mode_value =\
  SDRAM_MODEREG_BURST_LENGTH_2 |\
  SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL |\
  SDRAM_MODEREG_CAS_LATENCY_2 |\
  SDRAM_MODEREG_OPERATING_MODE_STANDARD |\
  SDRAM_MODEREG_WRITEMODE_BURSTWRITE;
  /* �����������SDRAM�Ĵ��� */
  FMC_SDRAMCommandStructure.CommandMode = FMC_SDRAM_CMD_LOAD_MODE;
  FMC_SDRAMCommandStructure.CommandTarget = FMC_SDRAM_CMD_TARGET_BANK1;
  FMC_SDRAMCommandStructure.AutoRefreshNumber = 1;
  FMC_SDRAMCommandStructure.ModeRegisterDefinition = mode_value;

  HAL_SDRAM_SendCommand(&hsdram1, &FMC_SDRAMCommandStructure, 0x1000);


  /* Step 8:����ˢ�¼����� */
  /* ˢ������ = (COUNT + 1) x SDRAM Ƶ��ʱ�� */
  /* COUNT =�� SDRAM ˢ������/����) - 20 */
  /* 64ms/4096=15.62us (15.62 us x FSDCLK) - 20 =1386 */
  HAL_SDRAM_ProgramRefreshRate(&hsdram1, 1386);
}
