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
#ifndef _UART_IRQ_ANALYSIS_h_
#define _UART_IRQ_ANALYSIS_h_

#include "User_Conf.h"

/* 对应的串口使能标志位 */
#define UART1_ENABLE_FLAG		true
#define UART2_ENABLE_FLAG		false
#define UART3_ENABLE_FLAG		false


#define UART1_REC_LEN_MAX		64		//接收缓冲区大小宏
#define UART2_REC_LEN_MAX		64		//接收缓冲区大小宏
#define UART3_REC_LEN_MAX		64		//接收缓冲区大小宏

#if UART1_ENABLE_FLAG
void MY_UART1_IRQHandler(void);//串口中断处理函数
void UART1_Data_Analysis(void);//串口数据分析函数
#endif

#if UART2_ENABLE_FLAG
void MY_UART2_IRQHandler(void);//串口中断处理函数
void UART2_Data_Analysis(void);//串口数据分析函数
#endif

#if UART3_ENABLE_FLAG
void MY_UART3_IRQHandler(void);//串口中断处理函数
void UART3_Data_Analysis(void);//串口数据分析函数
#endif


#endif


