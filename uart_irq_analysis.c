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
#include "uart_irq_analysis.h"

#if UART1_ENABLE_FLAG
uint8_t UART1_Rec_Data[UART1_REC_LEN_MAX] = {0x00};	//���ջ���������
uint8_t UART1_Rec_Len = 0;	//���ճ���
uint8_t UART1_Rec_Flag = false;//������ɱ�־λ
#endif

#if UART2_ENABLE_FLAG
uint8_t UART2_Rec_Data[UART2_REC_LEN_MAX] = {0x00};	//���ջ���������
uint8_t UART2_Rec_Len = 0;	//���ճ���
uint8_t UART2_Rec_Flag = false;//������ɱ�־λ
#endif

#if UART3_ENABLE_FLAG
uint8_t UART3_Rec_Data[UART3_REC_LEN_MAX] = {0x00};	//���ջ���������
uint8_t UART3_Rec_Len = 0;	//���ճ���
uint8_t UART3_Rec_Flag = false;//������ɱ�־λ
#endif


#if UART1_ENABLE_FLAG
/**
 * @Brief:�����жϴ�����
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
	}
}
#endif


#if UART2_ENABLE_FLAG
/**
 * @Brief:�����жϴ�����
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
	}
}
#endif


#if UART3_ENABLE_FLAG
/**
 * @Brief:�����жϴ�����
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
	}
}
#endif


