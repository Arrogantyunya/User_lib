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
#include "uart_analysis.h"

#if UART1_ENABLE_IRQRX
#if UART1_ENABLE_DMARX
extern DMA_HandleTypeDef hdma_usart1_rx;
#endif
uint8_t UART1_Rec_Data[UART1_REC_LEN_MAX] = {0x00};	//���ջ���������
uint8_t UART1_Rec_Len = 0;	//���ճ���
uint8_t UART1_Rec_Flag = false;//������ɱ�־λ
#endif

#if UART2_ENABLE_IRQRX
#if UART2_ENABLE_DMARX
extern DMA_HandleTypeDef hdma_usart2_rx;
#endif
uint8_t UART2_Rec_Data[UART2_REC_LEN_MAX] = {0x00};	//���ջ���������
uint8_t UART2_Rec_Len = 0;	//���ճ���
uint8_t UART2_Rec_Flag = false;//������ɱ�־λ
#endif

#if UART3_ENABLE_IRQRX
#if UART3_ENABLE_DMARX
extern DMA_HandleTypeDef hdma_usart3_rx;
#endif
uint8_t UART3_Rec_Data[UART3_REC_LEN_MAX] = {0x00};	//���ջ���������
uint8_t UART3_Rec_Len = 0;	//���ճ���
uint8_t UART3_Rec_Flag = false;//������ɱ�־λ
#endif


#if UART1_ENABLE_IRQRX
/**
 * @Brief:�����жϴ�����
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
	//���-������������Ҫ�ȶ�SR,�ٶ�DR�Ĵ��� �������������жϵ�����
	else if(__HAL_UART_GET_FLAG(&huart1,UART_FLAG_ORE) == SET)
	{
		__HAL_UART_CLEAR_FLAG(&huart1,UART_FLAG_ORE);          //��SR
	}
	else if(__HAL_UART_GET_FLAG(&huart1, UART_FLAG_IDLE) != RESET)
	{
		/*ע�⣺����ֻ����__HAL_UART_CLEAR_IDLEFLAG����������жϱ�־λ*/
		__HAL_UART_CLEAR_IDLEFLAG(&huart1);
//		__HAL_UART_CLEAR_FLAG(&huart1,UART_FLAG_IDLE);
		UART1_Rec_Flag = true;
	}
#else
  uint32_t temp;
  if(__HAL_UART_GET_FLAG(&huart1, UART_FLAG_IDLE) != RESET)
	{
		/*ע�⣺����ֻ����__HAL_UART_CLEAR_IDLEFLAG����������жϱ�־λ*/
		__HAL_UART_CLEAR_IDLEFLAG(&huart1);
		
		temp = huart1.Instance->SR;  //���״̬�Ĵ���SR,��ȡSR�Ĵ�������ʵ�����SR�Ĵ����Ĺ���
		temp = huart1.Instance->DR; //��ȡ���ݼĴ����е�����
		
		HAL_UART_DMAStop(&huart1); //
		
    // temp = hdma_usart1_rx.Instance->NDTR;// ��ȡDMA��δ��������ݸ�����NDTR�Ĵ�������������
		temp = __HAL_DMA_GET_COUNTER(&hdma_usart1_rx);// ��ȡDMA��δ��������ݸ���
		UART1_Rec_Len = UART1_REC_LEN_MAX - temp;
		UART1_Rec_Flag = true;
	}
#endif
}


/**
 * @Brief:�������ݷ�������
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
		printf("������ɣ����յĳ���Ϊ%d\r\n",UART1_Rec_Len);
		printf("���յ�����Ϊ��{%s}\r\n",UART1_Rec_Data);
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
 * @Brief:�����жϴ�����
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
	//���-������������Ҫ�ȶ�SR,�ٶ�DR�Ĵ��� �������������жϵ�����
	else if(__HAL_UART_GET_FLAG(&huart2,UART_FLAG_ORE) == SET)
	{
		__HAL_UART_CLEAR_FLAG(&huart2,UART_FLAG_ORE);          //��SR
	}
	else if(__HAL_UART_GET_FLAG(&huart2, UART_FLAG_IDLE) != RESET)
	{
		/*ע�⣺����ֻ����__HAL_UART_CLEAR_IDLEFLAG����������жϱ�־λ*/
		__HAL_UART_CLEAR_IDLEFLAG(&huart2);
//		__HAL_UART_CLEAR_FLAG(&huart2,UART_FLAG_IDLE);
		UART2_Rec_Flag = true;
	}
#else
  uint32_t temp;
  if(__HAL_UART_GET_FLAG(&huart2, UART_FLAG_IDLE) != RESET)
	{
		/*ע�⣺����ֻ����__HAL_UART_CLEAR_IDLEFLAG����������жϱ�־λ*/
		__HAL_UART_CLEAR_IDLEFLAG(&huart2);
		
		temp = huart2.Instance->SR;  //���״̬�Ĵ���SR,��ȡSR�Ĵ�������ʵ�����SR�Ĵ����Ĺ���
		temp = huart2.Instance->DR; //��ȡ���ݼĴ����е�����
		
		HAL_UART_DMAStop(&huart2); //
		
    // temp = hdma_usart1_rx.Instance->NDTR;// ��ȡDMA��δ��������ݸ�����NDTR�Ĵ�������������
		temp = __HAL_DMA_GET_COUNTER(&hdma_usart1_rx);// ��ȡDMA��δ��������ݸ���
		UART2_Rec_Len = UART2_REC_LEN_MAX - temp;
		UART2_Rec_Flag = true;
	}
#endif
}


/**
 * @Brief:�������ݷ�������
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
		printf("������ɣ����յĳ���Ϊ%d\r\n",UART2_Rec_Len);
		printf("���յ�����Ϊ��{%s}\r\n",UART2_Rec_Data);
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
 * @Brief:�����жϴ�����
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
	//���-������������Ҫ�ȶ�SR,�ٶ�DR�Ĵ��� �������������жϵ�����
	else if(__HAL_UART_GET_FLAG(&huart3,UART_FLAG_ORE) == SET)
	{
		__HAL_UART_CLEAR_FLAG(&huart3,UART_FLAG_ORE);          //��SR
	}
	else if(__HAL_UART_GET_FLAG(&huart3, UART_FLAG_IDLE) != RESET)
	{
		/*ע�⣺����ֻ����__HAL_UART_CLEAR_IDLEFLAG����������жϱ�־λ*/
		__HAL_UART_CLEAR_IDLEFLAG(&huart3);
//		__HAL_UART_CLEAR_FLAG(&huart3,UART_FLAG_IDLE);
		UART3_Rec_Flag = true;
	}
#else
  uint32_t temp;
  if(__HAL_UART_GET_FLAG(&huart3, UART_FLAG_IDLE) != RESET)
	{
		/*ע�⣺����ֻ����__HAL_UART_CLEAR_IDLEFLAG����������жϱ�־λ*/
		__HAL_UART_CLEAR_IDLEFLAG(&huart3);
		
		temp = huart3.Instance->SR;  //���״̬�Ĵ���SR,��ȡSR�Ĵ�������ʵ�����SR�Ĵ����Ĺ���
		temp = huart3.Instance->DR; //��ȡ���ݼĴ����е�����
		
		HAL_UART_DMAStop(&huart3); //
		
    // temp = hdma_usart1_rx.Instance->NDTR;// ��ȡDMA��δ��������ݸ�����NDTR�Ĵ�������������
		temp = __HAL_DMA_GET_COUNTER(&hdma_usart1_rx);// ��ȡDMA��δ��������ݸ���
		UART3_Rec_Len = UART3_REC_LEN_MAX - temp;
		UART3_Rec_Flag = true;
	}
#endif
}


/**
 * @Brief:�������ݷ�������
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
		printf("������ɣ����յĳ���Ϊ%d\r\n",UART3_Rec_Len);
		printf("���յ�����Ϊ��{%s}\r\n",UART3_Rec_Data);
		memset(UART3_Rec_Data,'\0',sizeof(UART3_Rec_Data));
		UART3_Rec_Len = 0;
    #if UART3_ENABLE_DMARX
    HAL_UART_Receive_DMA(&huart3,UART3_Rec_Data,UART3_REC_LEN_MAX);
    #endif
	}
}
#endif


