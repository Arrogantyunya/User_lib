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
#ifndef _USER_DELAY_H_
#define _USER_DELAY_H_

#include "stm32f1xx_hal.h"
#include <stdint.h>
#include <stdbool.h>

/* 
ʹ��SYSTICK������ʱ����
�ŵ㣺ȫϵ��ͨ�ã�ֻ��Ҫ���궨��CPU_FREQUENCY_MHZ����ʱ����Ƶ�޸ļ��ɡ�
ȱ�㣺ϵͳ�δ�ʱ����HAL���ʼ���ģ��ұ�����HAL���ʼ����
*/
#define USE_SYSTICK					true

/* 
ʹ��NOP������ʱ����
�ŵ㣺ʵ�ּ򵥣������F1ϵ�У�HAL_RCC_GetHCLKFreq()��ȡ��ֵ��72000000��
			�˷�ʽ�������Ի��ǱȽ�׼�ģ����������ͨ���ԣ�F1ϵ�н���ʹ�ô��ַ�ʽ��
ȱ�㣺ϵͳ�δ�ʱ����HAL���ʼ���ģ��ұ�����HAL���ʼ����
*/
//ʵ��ʹ�õ�ʱ���ֲ��ԡ���
#define USE_NOP							false

/* 
ʹ��NOP������ʱ����
�ŵ㣺 STM32ȫϵ��ͨ��
ȱ�㣺 ռ��һ����ʱ��
*/
#define USE_BASIC_TIMER			false

#if USE_SYSTICK
#define CPU_FREQUENCY_MHZ    72		// STM32ʱ����Ƶ
#elif USE_NOP

#elif USE_BASIC_TIMER

#endif

void delay_us(uint32_t us);
void delay_ms(uint32_t ms);


#endif



