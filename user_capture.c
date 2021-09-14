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
#include "user_capture.h"


CH_Parameter ch_param_info[CH_IC_MAX] = {0};
OC_CH_Parameter oc_ch_param_info[CH_IC_MAX] = {0};


/**
 * @Brief:定时器输入捕获回调
 * @Param:
 * @Return:
 * @Note:
 * @Author:
 */
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	if(TIM2 == htim->Instance)
	{
		TIMCaptureChannelHandle(htim);//定时器捕获多通道进行处理
	}	
}

/**
 * @Brief:定时器输出比较回调
 * @Param:
 * @Return:
 * @Note:
 * @Author:
 */
void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(TIM3 == htim->Instance)
	{
		TIMCompareChannelHandle(htim);//定时器比较多通道进行处理
	}
}

/**
 * @Brief:定时器溢出回调
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
			if (ch_param_info[i].update_cnt < TIM_ICOF_MAX)//如果这个通道达到最大溢出值
			{
				ch_param_info[i].update_cnt++;
			}
			else
			{
				//发生了太多次的超时溢出没有被清除，所以认为采集出了问题，直接清空结构体的所有数据
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
 * @Brief:定时器捕获多通道进行处理
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
	 *在使用定时器之前都一定要注意定时器的时钟频率，预分频器值，以及计数器周期。
	 *在这个定时器输入捕获这个Demo中，我们首先捕获上升沿信号，记录计数值1，然后切换到捕获下降沿信号，再次记录计数值2，根据差值即可计算出高电平的持续时间。低电平的持续时间计算也是差不多的。
	 *在这个过程中，可能发生计数器溢出，我们也将溢出次数进行记录，根据公式即可计算：计算值 = (计数周期 * 溢出次数) + 步骤二捕获到低电平的计数值 - 步骤一捕获到高电平的计数值
	 *然后TIM2的时钟频率是72MHZ，我们的分频值就设置为71，那么就是1us一次的计数值增加，具体公式可以看参考手册与数据手册
	*/
	
	if(ch_param_info[channel_num].edge_seq == IC_RISE_EDGE_FIRST)
	{
		//读取到上升沿后记录当前的计数值为cap_val[0]
		ch_param_info[channel_num].cap_val[0] = HAL_TIM_ReadCapturedValue(htim, channel);//捕获当前值
		
		/*
		低电平脉冲持续时间也就是计算值 = (计数周期 * 溢出次数) + 步骤一捕获到高电平的计数值 - 步骤二捕获到低电平的计数值 
		计算值应该 = (0xFFFF * update_cnt) + cap_val[1] - cap_val[0]
		*/
		ch_param_info[channel_num].cap_low = (0xFFFF*ch_param_info[channel_num].update_cnt) + ch_param_info[channel_num].cap_val[0] - ch_param_info[channel_num].cap_val[1];
		ch_param_info[channel_num].edge_seq = IC_RISE_EDGE_SECOND;//重置步骤
		
		ch_param_info[channel_num].update_cnt = 0;//然后溢出次数归零
		__HAL_TIM_SET_CAPTUREPOLARITY(htim,channel,TIM_ICPOLARITY_FALLING);  //设置为下降沿捕获
	}
	else
	{
		//读取到下降沿后记录当前的计数值为cap_val[1]
		ch_param_info[channel_num].cap_val[1] = HAL_TIM_ReadCapturedValue(htim, channel);//捕获当前值
		
		/*
		高电平脉冲持续时间也就是计算值 = (计数周期 * 溢出次数) + 步骤二捕获到低电平的计数值 - 步骤一捕获到高电平的计数值 
		计算值应该 = (0xFFFF * update_cnt) + cap_val[0] - cap_val_last[1]
		*/
		ch_param_info[channel_num].cap_high = (0xFFFF*ch_param_info[channel_num].update_cnt) + ch_param_info[channel_num].cap_val[1] - ch_param_info[channel_num].cap_val[0];
		ch_param_info[channel_num].edge_seq = IC_RISE_EDGE_FIRST;//重置步骤

		ch_param_info[channel_num].update_cnt = 0;//然后溢出次数归零
		__HAL_TIM_SET_CAPTUREPOLARITY(htim,channel,TIM_ICPOLARITY_RISING);  //设置为上升沿捕获
	}
}


/**
 * @Brief:定时器比较多通道进行处理
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
 * @Brief:读取当前定时器句柄对应的通道
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



