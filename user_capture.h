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
#ifndef _RECEIVER_H_
#define _RECEIVER_H_

#include "main.h"
#include "stm32f1xx_hal.h"

#include <String.h>
#include <stdbool.h>


#define		TIM2_PRESCALER_COUNT	72			//��Ƶ��
/* IC capture edge define*/
#define		IC_RISE_EDGE_FIRST		0
#define		IC_RISE_EDGE_SECOND		1
#define		IC_RISE_EDGE_THIRD		2
/* IC capture Parameters define*/
#define		TIM_ICOF_MAX					5//����������������ֵ
#define   CH_IC_MAX							2//���ͨ����(Ŀǰֻ����CH1��CH2)


typedef struct CH_Parameter_st 
{
	/*  */
	uint8_t 	update_cnt;			//�������
	uint8_t  	edge_seq;				//���ؼ���־λ
	uint32_t 	cap_val[2];			//�������ֵ
	uint32_t 	cap_high;				//����ߵ�ƽʱ��
	uint32_t 	cap_low;				//����͵�ƽʱ��
	uint32_t 	cap_cycle;			//��������ʱ��
	uint8_t		cap_duty;				//����ռ�ձ�
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

void TIMCompareChannelHandle(TIM_HandleTypeDef *htim);//��ʱ���Ƚ϶�ͨ�����д���

extern CH_Parameter ch_param_info[CH_IC_MAX];
extern OC_CH_Parameter oc_ch_param_info[CH_IC_MAX];
#endif


