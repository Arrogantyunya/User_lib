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
#ifndef _USER_DELAY_H_
#define _USER_DELAY_H_

#include "stm32f1xx_hal.h"
#include <stdint.h>
#include <stdbool.h>

/* 
使用SYSTICK进行延时操作
优点：全系列通用，只需要将宏定义CPU_FREQUENCY_MHZ根据时钟主频修改即可。
缺点：系统滴答定时器是HAL库初始化的，且必须由HAL库初始化。
*/
#define USE_SYSTICK					true

/* 
使用NOP进行延时操作
优点：实现简单，如果是F1系列，HAL_RCC_GetHCLKFreq()获取的值是72000000，
			此方式经过测试还是比较准的，如果不考虑通用性，F1系列建议使用此种方式。
缺点：系统滴答定时器是HAL库初始化的，且必须由HAL库初始化。
*/
//实际使用的时候发现不对。。
#define USE_NOP							false

/* 
使用NOP进行延时操作
优点： STM32全系列通用
缺点： 占用一个定时器
*/
#define USE_BASIC_TIMER			false

#if USE_SYSTICK
#define CPU_FREQUENCY_MHZ    72		// STM32时钟主频
#elif USE_NOP

#elif USE_BASIC_TIMER

#endif

void delay_us(uint32_t us);
void delay_ms(uint32_t ms);


#endif



