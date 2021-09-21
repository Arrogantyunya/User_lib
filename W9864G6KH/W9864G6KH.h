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
#ifndef _W9864G6KH_H_
#define _W9864G6KH_H_

#include "fmc.h"

/* ����SDRAM����ʼ��ַ */
#define SDRAM_BANK_START_ADDR		0xC0000000
#define SDRAM_BANK_END_ADDR 		(0xC0000000 + (4 * 1024 *1024 * 16 / 8)) 
	 
	 
/* ����ģʽֵ����ĺ� */
//ͻ������	 
#define SDRAM_MODEREG_BURST_LENGTH_1					0x000
#define SDRAM_MODEREG_BURST_LENGTH_2			  	0x001
#define SDRAM_MODEREG_BURST_LENGTH_4					0x010	
#define SDRAM_MODEREG_BURST_LENGTH_8					0x011
#define SDRAM_MODEREG_BURST_LENGTH_FULLPAGE		0x111

//ͻ������
#define SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL		0x0
#define SDRAM_MODEREG_BURST_TYPE_INTERLEAVVE	0x1
	 
//CAS Latency
#define SDRAM_MODEREG_CAS_LATENCY_2						0x010
#define SDRAM_MODEREG_CAS_LATENCY_3						0x011

//����ģʽ
#define SDRAM_MODEREG_OPERATING_MODE_STANDARD 0x00

//����д����
#define SDRAM_MODEREG_WRITEMODE_BURSTWRITE		0x0
#define SDRAM_MODEREG_WRITEMODE_SIGNALWRITE   0x1


void W9864G6KH_Init_Sequence(void);//W9864G6KH�ϵ��ʼ��ʱ��


#endif
