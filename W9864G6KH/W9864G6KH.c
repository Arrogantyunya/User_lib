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
#include "W9864G6KH.h"

/**
 * @Brief:W9864G6KH上电初始化时序
 * @Param:
 * @Return:
 * @Note:
 * @Author:
 */
void W9864G6KH_Init_Sequence(void)
{
	FMC_SDRAM_CommandTypeDef FMC_SDRAMCommandStructure;

  /* Step 3:配置命令：开启提供给SDRAM的时钟 */
  FMC_SDRAMCommandStructure.CommandMode = FMC_SDRAM_CMD_CLK_ENABLE;
  FMC_SDRAMCommandStructure.CommandTarget = FMC_SDRAM_CMD_TARGET_BANK1;
  FMC_SDRAMCommandStructure.AutoRefreshNumber = 1;
  FMC_SDRAMCommandStructure.ModeRegisterDefinition = 0;

  HAL_SDRAM_SendCommand(&hsdram1, &FMC_SDRAMCommandStructure, 0x1000);

	
  /* Step 4:延时等待CLK稳定 */
  HAL_Delay(1);

	
  /* Step 5:配置命令：对所有的bank预充电*/
  FMC_SDRAMCommandStructure.CommandMode = FMC_SDRAM_CMD_PALL;
  FMC_SDRAMCommandStructure.CommandTarget = FMC_SDRAM_CMD_TARGET_BANK1;
  FMC_SDRAMCommandStructure.AutoRefreshNumber = 1;
  FMC_SDRAMCommandStructure.ModeRegisterDefinition = 0;

  HAL_SDRAM_SendCommand(&hsdram1, &FMC_SDRAMCommandStructure, 0x1000);


  /* Step 6:配置命令：自动刷新（自动刷新需要至少发送2次）*/
  FMC_SDRAMCommandStructure.CommandMode = FMC_SDRAM_CMD_AUTOREFRESH_MODE;
  FMC_SDRAMCommandStructure.CommandTarget = FMC_SDRAM_CMD_TARGET_BANK1;
  FMC_SDRAMCommandStructure.AutoRefreshNumber = 2;
  FMC_SDRAMCommandStructure.ModeRegisterDefinition = 0;

  HAL_SDRAM_SendCommand(&hsdram1, &FMC_SDRAMCommandStructure, 0x1000);


  /* Step 7:设置sdram寄存器配置*/
  uint32_t mode_value;  //暂存设置的模式值;0x21;00000000 0010 0001;
  mode_value =\
  SDRAM_MODEREG_BURST_LENGTH_2 |\
  SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL |\
  SDRAM_MODEREG_CAS_LATENCY_2 |\
  SDRAM_MODEREG_OPERATING_MODE_STANDARD |\
  SDRAM_MODEREG_WRITEMODE_BURSTWRITE;
  /* 配置命令：设置SDRAM寄存器 */
  FMC_SDRAMCommandStructure.CommandMode = FMC_SDRAM_CMD_LOAD_MODE;
  FMC_SDRAMCommandStructure.CommandTarget = FMC_SDRAM_CMD_TARGET_BANK1;
  FMC_SDRAMCommandStructure.AutoRefreshNumber = 1;
  FMC_SDRAMCommandStructure.ModeRegisterDefinition = mode_value;

  HAL_SDRAM_SendCommand(&hsdram1, &FMC_SDRAMCommandStructure, 0x1000);


  /* Step 8:设置刷新计数器 */
  /* 刷新速率 = (COUNT + 1) x SDRAM 频率时钟 */
  /* COUNT =（ SDRAM 刷新周期/行数) - 20 */
  /* 64ms/4096=15.62us (15.62 us x FSDCLK) - 20 =1386 */
  HAL_SDRAM_ProgramRefreshRate(&hsdram1, 1386);
}
