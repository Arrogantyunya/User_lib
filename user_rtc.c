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
#include "user_rtc.h"

User_RTC_DataTime_ST RTC_DataTime;

/**
 * @Brief:得到RTC掉电状态
 * @Param:
 * @Return:
 * @Note:
 * @Author:
 */
bool RTC_GetLostStatus(void)
{
	__HAL_RCC_BKP_CLK_ENABLE();       //开启后备区域时钟
	__HAL_RCC_PWR_CLK_ENABLE();		  //开启电源时钟
	
	if(HAL_RTCEx_BKUPRead(&hrtc,RTC_BKP_DR1)!= 0x5051)
	{
		return true;//掉电过
	}
	
	return false;
}


/**
 * @Brief:得到RTC的日期和时间
 * @Param:
 * @Return:
 * @Note:
 * @Author:
 */
bool RTC_GetDateTime(User_RTC_DataTime_ST *sDateTime)
{
	RTC_DateTypeDef RTC_Data;
	RTC_TimeTypeDef RTC_Time;
	
	/* Get the RTC current Time ,must get time first*/
	HAL_RTC_GetTime(&hrtc, &RTC_Time, RTC_FORMAT_BIN);
	/* Get the RTC current Date */
	HAL_RTC_GetDate(&hrtc, &RTC_Data, RTC_FORMAT_BIN);
	
	/* Display date Format : yy/mm/dd[week]  hh:mm:ss */
	printf("%02d/%02d/%02d[%d]  ",2000 + RTC_Data.Year, RTC_Data.Month, RTC_Data.Date, RTC_Data.WeekDay); 
	printf("%02d:%02d:%02d\r\n",RTC_Time.Hours, RTC_Time.Minutes, RTC_Time.Seconds);
	
	return true;
}


/**
 * @Brief:设置RTC的日期和时间
 * @Param:
 * @Return:
 * @Note:
 * @Author:
 */
bool RTC_SetDateTime(uint16_t Year,uint8_t Month,uint8_t Date,uint8_t Hours,uint8_t Minutes,uint8_t Seconds)
{
	RTC_DateTypeDef RTC_Data;
	RTC_TimeTypeDef RTC_Time;
	
	RTC_Data.Year = Year - 2000;
	RTC_Data.Month = Month;
	RTC_Data.Date = Date;
	RTC_Time.Hours = Hours;
	RTC_Time.Minutes = Minutes;
	RTC_Time.Seconds = Seconds;
	
	HAL_RTC_SetTime(&hrtc, &RTC_Time, RTC_FORMAT_BIN);
	HAL_RTC_SetDate(&hrtc, &RTC_Data, RTC_FORMAT_BIN);
	
	HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR1, 0x5051);//向指定的后备区域寄存器写入数据
	return true;
}

/**
 * @Brief:开启RTC秒中断
 * @Param:
 * @Return:
 * @Note:
 * @Author:
 */
void RTC_SetSecond_IT(void)
{
	 HAL_RTCEx_SetSecond_IT(&hrtc);
}


/**
 * @Brief:关闭RTC秒中断
 * @Param:
 * @Return:
 * @Note:
 * @Author:
 */
void RTC_DeactivateSecond(void)
{
	HAL_RTCEx_DeactivateSecond(&hrtc);
}




/**
  * @brief  Alarm A callback.
  * @param  hrtc   pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @retval None
  */
void HAL_RTC_AlarmAEventCallback(RTC_HandleTypeDef *hrtc)
{
	RTC_GetDateTime(&RTC_DataTime);
  Serial_println("RTC闹钟触发！！！");
}

/**
  * @brief  Second event callback.
  * @param  hrtc: pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @retval None
  */
void HAL_RTCEx_RTCEventCallback(RTC_HandleTypeDef *hrtc)
{
  Serial_println("..");
}

/**
  * @brief  Second event error callback.
  * @param  hrtc: pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @retval None
  */
void HAL_RTCEx_RTCEventErrorCallback(RTC_HandleTypeDef *hrtc)
{
  
}

