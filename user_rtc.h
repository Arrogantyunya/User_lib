/****************************************Copyright (c)****************************************************
 

**--------------File Info---------------------------------------------------------------------------------

** File name:
** Last modified Date:

** Last Version:

** Descriptions:
**--------------------------------------------------------------------------------------------------------

** Created by:		¡ıº“ª‘ 
** Created date:	2021/xx/xx

** Version:				V1.0
** Descriptions:
**--------------------------------------------------------------------------------------------------------*/
#ifndef _USER_RTC_H_
#define _USER_RTC_H_

#include "rtc.h"

#include "User_Conf.h"
#include "stdbool.h"


typedef struct USER_RTC_DTAETIME_ST
{
	uint8_t WeekDay;
	uint16_t Year;
	uint8_t Month;
	uint8_t Date;
	uint8_t Hours;
	uint8_t Minutes;
	uint8_t Seconds;
}User_RTC_DataTime_ST;

bool RTC_GetLostStatus(void);
bool RTC_GetDateTime(User_RTC_DataTime_ST *sDateTime);
bool RTC_SetDateTime(uint16_t Year,uint8_t Month,uint8_t Date,uint8_t Hours,uint8_t Minutes,uint8_t Seconds);
void RTC_SetSecond_IT(void);
void RTC_DeactivateSecond(void);


extern User_RTC_DataTime_ST RTC_DataTime;



#endif
