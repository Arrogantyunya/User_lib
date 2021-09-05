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
#include "uart_irq_analysis.h"

#if UART1_ENABLE_FLAG
uint8_t UART1_Rec_Data[UART1_REC_LEN_MAX] = {0x00};	//接收缓冲区数组
uint8_t UART1_Rec_Len = 0;	//接收长度
uint8_t UART1_Rec_Flag = false;//接收完成标志位
#endif

#if UART2_ENABLE_FLAG
uint8_t UART2_Rec_Data[UART2_REC_LEN_MAX] = {0x00};	//接收缓冲区数组
uint8_t UART2_Rec_Len = 0;	//接收长度
uint8_t UART2_Rec_Flag = false;//接收完成标志位
#endif

#if UART3_ENABLE_FLAG
uint8_t UART3_Rec_Data[UART3_REC_LEN_MAX] = {0x00};	//接收缓冲区数组
uint8_t UART3_Rec_Len = 0;	//接收长度
uint8_t UART3_Rec_Flag = false;//接收完成标志位
#endif


#if UART1_ENABLE_FLAG
/**
 * @Brief:串口中断处理函数
 * @Param:
 * @Return:
 * @Note:
 * @Author:
 */
void MY_UART1_IRQHandler(void)
{

	if(__HAL_UART_GET_FLAG(&huart1, UART_FLAG_RXNE) != RESET)
	{
		__HAL_UART_CLEAR_FLAG(&huart1,UART_FLAG_RXNE);
		UART1_Rec_Data[UART1_Rec_Len++] = huart1.Instance->DR;
	}
	//溢出-如果发生溢出需要先读SR,再读DR寄存器 则可清除不断入中断的问题
	else if(__HAL_UART_GET_FLAG(&huart1,UART_FLAG_ORE) == SET)
	{
		__HAL_UART_CLEAR_FLAG(&huart1,UART_FLAG_ORE);          //读SR
	}
	else if(__HAL_UART_GET_FLAG(&huart1, UART_FLAG_IDLE) != RESET)
	{
		/*注意：这里只能用__HAL_UART_CLEAR_IDLEFLAG来清除空闲中断标志位*/
		__HAL_UART_CLEAR_IDLEFLAG(&huart1);
//		__HAL_UART_CLEAR_FLAG(&huart1,UART_FLAG_IDLE);
		UART1_Rec_Flag = true;
	}
}


/**
 * @Brief:串口数据分析函数
 * @Param:
 * @Return:
 * @Note:
 * @Author:
 */
void UART1_Data_Analysis(void)
{
	if(UART1_Rec_Flag)
	{
		UART1_Rec_Flag = false;
		printf("接收完成，接收的长度为%d\r\n",UART1_Rec_Len);
		printf("接收的数据为：{%s}\r\n",UART1_Rec_Data);
		memset(UART1_Rec_Data,'\0',sizeof(UART1_Rec_Data));
		UART1_Rec_Len = 0;
	}
}
#endif


#if UART2_ENABLE_FLAG
/**
 * @Brief:串口中断处理函数
 * @Param:
 * @Return:
 * @Note:
 * @Author:
 */
void MY_UART2_IRQHandler(void)
{

	if(__HAL_UART_GET_FLAG(&huart2, UART_FLAG_RXNE) != RESET)
	{
		__HAL_UART_CLEAR_FLAG(&huart2,UART_FLAG_RXNE);
		UART2_Rec_Data[UART2_Rec_Len++] = huart2.Instance->DR;
	}
	//溢出-如果发生溢出需要先读SR,再读DR寄存器 则可清除不断入中断的问题
	else if(__HAL_UART_GET_FLAG(&huart2,UART_FLAG_ORE) == SET)
	{
		__HAL_UART_CLEAR_FLAG(&huart2,UART_FLAG_ORE);          //读SR
	}
	else if(__HAL_UART_GET_FLAG(&huart2, UART_FLAG_IDLE) != RESET)
	{
		/*注意：这里只能用__HAL_UART_CLEAR_IDLEFLAG来清除空闲中断标志位*/
		__HAL_UART_CLEAR_IDLEFLAG(&huart2);
//		__HAL_UART_CLEAR_FLAG(&huart2,UART_FLAG_IDLE);
		UART2_Rec_Flag = true;
	}
}


/**
 * @Brief:串口数据分析函数
 * @Param:
 * @Return:
 * @Note:
 * @Author:
 */
void UART2_Data_Analysis(void)
{
	if(UART2_Rec_Flag)
	{
		UART2_Rec_Flag = false;
		printf("接收完成，接收的长度为%d\r\n",UART2_Rec_Len);
		printf("接收的数据为：{%s}\r\n",UART2_Rec_Data);
		memset(UART2_Rec_Data,'\0',sizeof(UART2_Rec_Data));
		UART2_Rec_Len = 0;
	}
}
#endif


#if UART3_ENABLE_FLAG
/**
 * @Brief:串口中断处理函数
 * @Param:
 * @Return:
 * @Note:
 * @Author:
 */
void MY_UART3_IRQHandler(void)
{

	if(__HAL_UART_GET_FLAG(&huart3, UART_FLAG_RXNE) != RESET)
	{
		__HAL_UART_CLEAR_FLAG(&huart3,UART_FLAG_RXNE);
		UART3_Rec_Data[UART3_Rec_Len++] = huart3.Instance->DR;
	}
	//溢出-如果发生溢出需要先读SR,再读DR寄存器 则可清除不断入中断的问题
	else if(__HAL_UART_GET_FLAG(&huart3,UART_FLAG_ORE) == SET)
	{
		__HAL_UART_CLEAR_FLAG(&huart3,UART_FLAG_ORE);          //读SR
	}
	else if(__HAL_UART_GET_FLAG(&huart3, UART_FLAG_IDLE) != RESET)
	{
		/*注意：这里只能用__HAL_UART_CLEAR_IDLEFLAG来清除空闲中断标志位*/
		__HAL_UART_CLEAR_IDLEFLAG(&huart3);
//		__HAL_UART_CLEAR_FLAG(&huart3,UART_FLAG_IDLE);
		UART3_Rec_Flag = true;
	}
}


/**
 * @Brief:串口数据分析函数
 * @Param:
 * @Return:
 * @Note:
 * @Author:
 */
void UART3_Data_Analysis(void)
{
	if(UART3_Rec_Flag)
	{
		UART3_Rec_Flag = false;
		printf("接收完成，接收的长度为%d\r\n",UART3_Rec_Len);
		printf("接收的数据为：{%s}\r\n",UART3_Rec_Data);
		memset(UART3_Rec_Data,'\0',sizeof(UART3_Rec_Data));
		UART3_Rec_Len = 0;
	}
}
#endif


