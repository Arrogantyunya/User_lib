/****************************************Copyright (c)****************************************************
 

**--------------File Info---------------------------------------------------------------------------------

** File name:
** Last modified Date:

** Last Version:

** Descriptions:
**--------------------------------------------------------------------------------------------------------

** Created by:		Áõ¼Ò»Ô 
** Created date:	2021/xx/xx

** Version:				V1.0
** Descriptions:
**--------------------------------------------------------------------------------------------------------*/
#include "User_Delay.h"




/**
 * @Brief:
 * @Param:
 * @Return:
 * @Note:
 * @Author:
 */
void delay_us(__IO uint32_t us)
{
#if USE_SYSTICK
	int last, curr, val;
	int temp;

	while (us != 0)
	{
		temp = us > 900 ? 900 : us;
		last = SysTick->VAL;
		curr = last - CPU_FREQUENCY_MHZ * temp;
		if (curr >= 0)
		{
			do
			{
				val = SysTick->VAL;
			}
			while ((val < last) && (val >= curr));
		}
		else
		{
			curr += CPU_FREQUENCY_MHZ * 1000;
			do
			{
				val = SysTick->VAL;
			}
			while ((val <= last) || (val > curr));
		}
		us -= temp;
	}
#elif USE_NOP
	uint32_t delay = ((HAL_RCC_GetHCLKFreq()/4000000)*us) - 10;
	while (delay--);
#elif USE_BASIC_TIMER
	__HAL_TIM_SET_COUNTER(DLY_TIM_Handle, 0);
	__HAL_TIM_ENABLE(DLY_TIM_Handle);
	while (__HAL_TIM_GET_COUNTER(DLY_TIM_Handle) < nus)
	{
	}
	__HAL_TIM_DISABLE(DLY_TIM_Handle);
#endif
}


/**
 * @Brief:
 * @Param:
 * @Return:
 * @Note:
 * @Author:
 */
void delay_ms(__IO uint32_t ms)
{
	while(ms--)
	{
		delay_us(1000);
	}
}
