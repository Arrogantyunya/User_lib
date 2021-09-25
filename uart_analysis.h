/****************************************Copyright (c)****************************************************


**--------------File Info---------------------------------------------------------------------------------

** File name:uart_analysis.h
** Last modified Date:

** Last Version:

** Descriptions:这是一个串口UART的IRQRX/DMARX接收库，通过使能对应的宏，可以使用已经分配好的函数和变量，以及设置串口缓冲区大小
**--------------------------------------------------------------------------------------------------------

** Created by:		刘家辉
** Created date:	2021/xx/xx

** Version:				V1.0
** Descriptions:
**--------------------------------------------------------------------------------------------------------*/
#ifndef _UART_ANALYSIS_h_
#define _UART_ANALYSIS_h_

#include "User_Conf.h"

/* 对应的串口使能标志位 */
#define UART1_ENABLE_IRQRX		true
#define UART2_ENABLE_IRQRX		false
#define UART3_ENABLE_IRQRX		false


#define UART1_REC_LEN_MAX		512		//接收缓冲区大小宏
#define UART2_REC_LEN_MAX		64		//接收缓冲区大小宏
#define UART3_REC_LEN_MAX		64		//接收缓冲区大小宏

#if UART1_ENABLE_IRQRX
#define UART1_ENABLE_DMARX		true	//UART1 DMA接收使能
extern uint8_t UART1_Rec_Data[UART1_REC_LEN_MAX];	//接收缓冲区数组
extern uint32_t UART1_Rec_Len;	//接收长度
extern uint8_t UART1_Rec_Flag;//接收完成标志位
void MY_UART1_IRQHandler(void);//串口中断处理函数
void UART1_Data_Analysis(void);//串口数据分析函数
#endif

#if UART2_ENABLE_IRQRX
#define UART2_ENABLE_DMARX		true	//UART2 DMA接收使能
extern uint8_t UART2_Rec_Data[UART2_REC_LEN_MAX];	//接收缓冲区数组
extern uint32_t UART2_Rec_Len;	//接收长度
extern uint8_t UART2_Rec_Flag;//接收完成标志位
void MY_UART2_IRQHandler(void);//串口中断处理函数
void UART2_Data_Analysis(void);//串口数据分析函数
#endif

#if UART3_ENABLE_IRQRX
#define UART3_ENABLE_DMARX		true	//UART3 DMA接收使能
extern uint8_t UART3_Rec_Data[UART3_REC_LEN_MAX];	//接收缓冲区数组
extern uint32_t UART3_Rec_Len;	//接收长度
extern uint8_t UART3_Rec_Flag;//接收完成标志位
void MY_UART3_IRQHandler(void);//串口中断处理函数
void UART3_Data_Analysis(void);//串口数据分析函数
#endif


#endif


