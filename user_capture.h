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
#ifndef _RECEIVER_H_
#define _RECEIVER_H_

#include "main.h"
#include "stm32f1xx_hal.h"

#include <String.h>
#include <stdbool.h>


#define		TIM2_PRESCALER_COUNT	72			//分频数
/* IC capture edge define*/
#define		IC_RISE_EDGE_FIRST		0
#define		IC_RISE_EDGE_SECOND		1
#define		IC_RISE_EDGE_THIRD		2
/* IC capture Parameters define*/
#define		TIM_ICOF_MAX					5//允许溢出次数的最大值
#define   CH_IC_MAX							2//最大通道数(目前只用了CH1和CH2)


typedef struct CH_Parameter_st 
{
	/*  */
	uint8_t 	update_cnt;			//溢出次数
	uint8_t  	edge_seq;				//边沿检测标志位
	uint32_t 	cap_val[2];			//捕获计数值
	uint32_t 	cap_high;				//捕获高电平时间
	uint32_t 	cap_low;				//捕获低电平时间
	uint32_t 	cap_cycle;			//捕获周期时间
	uint8_t		cap_duty;				//捕获占空比
}CH_Parameter;

typedef struct OUTPUT_COMPARE_CH_Parameter_st
{
	/*  */
	uint8_t		frequency;
	uint8_t		duty_cycle;
	uint16_t	val;
	uint16_t	compare_val[2];
	uint8_t		flag;
}OC_CH_Parameter;


void TIMCaptureChannelHandle(TIM_HandleTypeDef *htim);
void tim_read_channel_num(TIM_HandleTypeDef *htim, uint8_t* channel_num, uint8_t* channel);

void TIMCompareChannelHandle(TIM_HandleTypeDef *htim);//定时器比较多通道进行处理

extern CH_Parameter ch_param_info[CH_IC_MAX];
extern OC_CH_Parameter oc_ch_param_info[CH_IC_MAX];
#endif


