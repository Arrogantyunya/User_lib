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
#include "uart_analysis.h"

#if UART1_ENABLE_IRQRX
#if UART1_ENABLE_DMARX
extern DMA_HandleTypeDef hdma_usart1_rx;
#endif
uint8_t UART1_Rec_Data[UART1_REC_LEN_MAX] = {0x00};	//接收缓冲区数组
uint8_t UART1_Rec_Len = 0;	//接收长度
uint8_t UART1_Rec_Flag = false;//接收完成标志位
#endif

#if UART2_ENABLE_IRQRX
#if UART2_ENABLE_DMARX
extern DMA_HandleTypeDef hdma_usart2_rx;
#endif
uint8_t UART2_Rec_Data[UART2_REC_LEN_MAX] = {0x00};	//接收缓冲区数组
uint8_t UART2_Rec_Len = 0;	//接收长度
uint8_t UART2_Rec_Flag = false;//接收完成标志位
#endif

#if UART3_ENABLE_IRQRX
#if UART3_ENABLE_DMARX
extern DMA_HandleTypeDef hdma_usart3_rx;
#endif
uint8_t UART3_Rec_Data[UART3_REC_LEN_MAX] = {0x00};	//接收缓冲区数组
uint8_t UART3_Rec_Len = 0;	//接收长度
uint8_t UART3_Rec_Flag = false;//接收完成标志位
#endif


#if UART1_ENABLE_IRQRX
/**
 * @Brief:串口中断处理函数
 * @Param:
 * @Return:
 * @Note:
 * @Author:
 */
void MY_UART1_IRQHandler(void)
{
#if (UART1_ENABLE_DMARX == false)
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
#else
  uint32_t temp;
  if(__HAL_UART_GET_FLAG(&huart1, UART_FLAG_IDLE) != RESET)
	{
		/*注意：这里只能用__HAL_UART_CLEAR_IDLEFLAG来清除空闲中断标志位*/
		__HAL_UART_CLEAR_IDLEFLAG(&huart1);
		
		temp = huart1.Instance->SR;  //清除状态寄存器SR,读取SR寄存器可以实现清除SR寄存器的功能
		temp = huart1.Instance->DR; //读取数据寄存器中的数据
		
		HAL_UART_DMAStop(&huart1); //
		
    // temp = hdma_usart1_rx.Instance->NDTR;// 获取DMA中未传输的数据个数，NDTR寄存器分析见下面
		temp = __HAL_DMA_GET_COUNTER(&hdma_usart1_rx);// 获取DMA中未传输的数据个数
		UART1_Rec_Len = UART1_REC_LEN_MAX - temp;
		UART1_Rec_Flag = true;
	}
#endif
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
    #if UART1_ENABLE_DMARX
    HAL_UART_Receive_DMA(&huart1,UART1_Rec_Data,UART1_REC_LEN_MAX);
    #endif
	}
}
#endif


#if UART2_ENABLE_IRQRX
/**
 * @Brief:串口中断处理函数
 * @Param:
 * @Return:
 * @Note:
 * @Author:
 */
void MY_UART2_IRQHandler(void)
{
#if (UART2_ENABLE_DMARX == false)
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
#else
  uint32_t temp;
  if(__HAL_UART_GET_FLAG(&huart2, UART_FLAG_IDLE) != RESET)
	{
		/*注意：这里只能用__HAL_UART_CLEAR_IDLEFLAG来清除空闲中断标志位*/
		__HAL_UART_CLEAR_IDLEFLAG(&huart2);
		
		temp = huart2.Instance->SR;  //清除状态寄存器SR,读取SR寄存器可以实现清除SR寄存器的功能
		temp = huart2.Instance->DR; //读取数据寄存器中的数据
		
		HAL_UART_DMAStop(&huart2); //
		
    // temp = hdma_usart1_rx.Instance->NDTR;// 获取DMA中未传输的数据个数，NDTR寄存器分析见下面
		temp = __HAL_DMA_GET_COUNTER(&hdma_usart1_rx);// 获取DMA中未传输的数据个数
		UART2_Rec_Len = UART2_REC_LEN_MAX - temp;
		UART2_Rec_Flag = true;
	}
#endif
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
    #if UART2_ENABLE_DMARX
    HAL_UART_Receive_DMA(&huart2,UART2_Rec_Data,UART2_REC_LEN_MAX);
    #endif
	}
}
#endif


#if UART3_ENABLE_IRQRX
/**
 * @Brief:串口中断处理函数
 * @Param:
 * @Return:
 * @Note:
 * @Author:
 */
void MY_UART3_IRQHandler(void)
{
#if (UART3_ENABLE_DMARX == false)
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
#else
  uint32_t temp;
  if(__HAL_UART_GET_FLAG(&huart3, UART_FLAG_IDLE) != RESET)
	{
		/*注意：这里只能用__HAL_UART_CLEAR_IDLEFLAG来清除空闲中断标志位*/
		__HAL_UART_CLEAR_IDLEFLAG(&huart3);
		
		temp = huart3.Instance->SR;  //清除状态寄存器SR,读取SR寄存器可以实现清除SR寄存器的功能
		temp = huart3.Instance->DR; //读取数据寄存器中的数据
		
		HAL_UART_DMAStop(&huart3); //
		
    // temp = hdma_usart1_rx.Instance->NDTR;// 获取DMA中未传输的数据个数，NDTR寄存器分析见下面
		temp = __HAL_DMA_GET_COUNTER(&hdma_usart1_rx);// 获取DMA中未传输的数据个数
		UART3_Rec_Len = UART3_REC_LEN_MAX - temp;
		UART3_Rec_Flag = true;
	}
#endif
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
    #if UART3_ENABLE_DMARX
    HAL_UART_Receive_DMA(&huart3,UART3_Rec_Data,UART3_REC_LEN_MAX);
    #endif
	}
}
#endif


