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
#include "user_capture.h"


CH_Parameter ch_param_info[CH_IC_MAX] = {0};
OC_CH_Parameter oc_ch_param_info[CH_IC_MAX] = {0};


/**
 * @Brief:��ʱ�����벶��ص�
 * @Param:
 * @Return:
 * @Note:
 * @Author:
 */
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	if(TIM2 == htim->Instance)
	{
		TIMCaptureChannelHandle(htim);//��ʱ�������ͨ�����д���
	}	
}

/**
 * @Brief:��ʱ������Ƚϻص�
 * @Param:
 * @Return:
 * @Note:
 * @Author:
 */
void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(TIM3 == htim->Instance)
	{
		TIMCompareChannelHandle(htim);//��ʱ���Ƚ϶�ͨ�����д���
	}
}

/**
 * @Brief:��ʱ������ص�
 * @Param:
 * @Return:
 * @Note:
 * @Author:
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM2) 
	{
		for (uint8_t i = 0; i < CH_IC_MAX; i++)
		{
			if (ch_param_info[i].update_cnt < TIM_ICOF_MAX)//������ͨ���ﵽ������ֵ
			{
				ch_param_info[i].update_cnt++;
			}
			else
			{
				//������̫��εĳ�ʱ���û�б������������Ϊ�ɼ��������⣬ֱ����սṹ�����������
				memset(&ch_param_info[i],0,sizeof(CH_Parameter));
				
//				ch_param_info[i].update_cnt = 0;
//				ch_param_info[i].cap_val[0] = 0;
//				ch_param_info[i].cap_val[1] = 0;
//				ch_param_info[i].cap_high = 0;
//				ch_param_info[i].cap_low = 0;
			}
		}
	}
}


/**
 * @Brief:��ʱ�������ͨ�����д���
 * @Param:
 * @Return:
 * @Note:
 * @Author:
 */
void TIMCaptureChannelHandle(TIM_HandleTypeDef *htim)
{
	uint8_t channel_num, channel;
	tim_read_channel_num(htim, &channel_num, &channel);//
	if(channel_num == 0xFF)
		return;
	/*
	 *��ʹ�ö�ʱ��֮ǰ��һ��Ҫע�ⶨʱ����ʱ��Ƶ�ʣ�Ԥ��Ƶ��ֵ���Լ����������ڡ�
	 *�������ʱ�����벶�����Demo�У��������Ȳ����������źţ���¼����ֵ1��Ȼ���л��������½����źţ��ٴμ�¼����ֵ2�����ݲ�ֵ���ɼ�����ߵ�ƽ�ĳ���ʱ�䡣�͵�ƽ�ĳ���ʱ�����Ҳ�ǲ��ġ�
	 *����������У����ܷ������������������Ҳ������������м�¼�����ݹ�ʽ���ɼ��㣺����ֵ = (�������� * �������) + ��������񵽵͵�ƽ�ļ���ֵ - ����һ���񵽸ߵ�ƽ�ļ���ֵ
	 *Ȼ��TIM2��ʱ��Ƶ����72MHZ�����ǵķ�Ƶֵ������Ϊ71����ô����1usһ�εļ���ֵ���ӣ����幫ʽ���Կ��ο��ֲ��������ֲ�
	*/
	
	if(ch_param_info[channel_num].edge_seq == IC_RISE_EDGE_FIRST)
	{
		//��ȡ�������غ��¼��ǰ�ļ���ֵΪcap_val[0]
		ch_param_info[channel_num].cap_val[0] = HAL_TIM_ReadCapturedValue(htim, channel);//����ǰֵ
		
		/*
		�͵�ƽ�������ʱ��Ҳ���Ǽ���ֵ = (�������� * �������) + ����һ���񵽸ߵ�ƽ�ļ���ֵ - ��������񵽵͵�ƽ�ļ���ֵ 
		����ֵӦ�� = (0xFFFF * update_cnt) + cap_val[1] - cap_val[0]
		*/
		ch_param_info[channel_num].cap_low = (0xFFFF*ch_param_info[channel_num].update_cnt) + ch_param_info[channel_num].cap_val[0] - ch_param_info[channel_num].cap_val[1];
		ch_param_info[channel_num].edge_seq = IC_RISE_EDGE_SECOND;//���ò���
		
		ch_param_info[channel_num].update_cnt = 0;//Ȼ�������������
		__HAL_TIM_SET_CAPTUREPOLARITY(htim,channel,TIM_ICPOLARITY_FALLING);  //����Ϊ�½��ز���
	}
	else
	{
		//��ȡ���½��غ��¼��ǰ�ļ���ֵΪcap_val[1]
		ch_param_info[channel_num].cap_val[1] = HAL_TIM_ReadCapturedValue(htim, channel);//����ǰֵ
		
		/*
		�ߵ�ƽ�������ʱ��Ҳ���Ǽ���ֵ = (�������� * �������) + ��������񵽵͵�ƽ�ļ���ֵ - ����һ���񵽸ߵ�ƽ�ļ���ֵ 
		����ֵӦ�� = (0xFFFF * update_cnt) + cap_val[0] - cap_val_last[1]
		*/
		ch_param_info[channel_num].cap_high = (0xFFFF*ch_param_info[channel_num].update_cnt) + ch_param_info[channel_num].cap_val[1] - ch_param_info[channel_num].cap_val[0];
		ch_param_info[channel_num].edge_seq = IC_RISE_EDGE_FIRST;//���ò���

		ch_param_info[channel_num].update_cnt = 0;//Ȼ�������������
		__HAL_TIM_SET_CAPTUREPOLARITY(htim,channel,TIM_ICPOLARITY_RISING);  //����Ϊ�����ز���
	}
}


/**
 * @Brief:��ʱ���Ƚ϶�ͨ�����д���
 * @Param:
 * @Return:
 * @Note:
 * @Author:
 */
void TIMCompareChannelHandle(TIM_HandleTypeDef *htim)
{
	uint8_t channel_num, channel;
	tim_read_channel_num(htim, &channel_num, &channel);//
	if(channel_num == 0xFF)
		return;
	
	if(oc_ch_param_info[channel_num].val == oc_ch_param_info[channel_num].compare_val[0])
	{
//		oc_ch_param_info[channel_num].flag = false;
		oc_ch_param_info[channel_num].val = oc_ch_param_info[channel_num].compare_val[1];
		__HAL_TIM_SET_COMPARE(htim, channel, oc_ch_param_info[channel_num].val);
	}
	else
	{
//		oc_ch_param_info[channel_num].flag = true;
		oc_ch_param_info[channel_num].val = oc_ch_param_info[channel_num].compare_val[0];
		__HAL_TIM_SET_COMPARE(htim, channel, oc_ch_param_info[channel_num].val);
	}
}


/**
 * @Brief:��ȡ��ǰ��ʱ�������Ӧ��ͨ��
 * @Param:
 * @Return:
 * @Note:
 * @Author:
 */void tim_read_channel_num(TIM_HandleTypeDef *htim, uint8_t* channel_num, uint8_t* channel)
{
	switch (htim->Channel)
	{
		case HAL_TIM_ACTIVE_CHANNEL_1:
			*channel_num = 0;
			*channel = TIM_CHANNEL_1;
			break;
		
		case HAL_TIM_ACTIVE_CHANNEL_2:
			*channel_num = 1;
			*channel = TIM_CHANNEL_2;
			break;
		
//		case HAL_TIM_ACTIVE_CHANNEL_3:
//			*channel_num = 2;
//			*channel = TIM_CHANNEL_3;
//			break;
//		
//		case HAL_TIM_ACTIVE_CHANNEL_4:
//			*channel_num = 3;
//			*channel = TIM_CHANNEL_4;
//			break;
		
		default:
			*channel_num = 0xFF;
			*channel = 0xFF;
			break;
	}
}



