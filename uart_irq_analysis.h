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
#ifndef _UART_IRQ_ANALYSIS_h_
#define _UART_IRQ_ANALYSIS_h_

#include "User_Conf.h"

/* ��Ӧ�Ĵ���ʹ�ܱ�־λ */
#define UART1_ENABLE_FLAG		true
#define UART2_ENABLE_FLAG		false
#define UART3_ENABLE_FLAG		false


#define UART1_REC_LEN_MAX		64		//���ջ�������С��
#define UART2_REC_LEN_MAX		64		//���ջ�������С��
#define UART3_REC_LEN_MAX		64		//���ջ�������С��

#if UART1_ENABLE_FLAG
void MY_UART1_IRQHandler(void);//�����жϴ�����
void UART1_Data_Analysis(void);//�������ݷ�������
#endif

#if UART2_ENABLE_FLAG
void MY_UART2_IRQHandler(void);//�����жϴ�����
void UART2_Data_Analysis(void);//�������ݷ�������
#endif

#if UART3_ENABLE_FLAG
void MY_UART3_IRQHandler(void);//�����жϴ�����
void UART3_Data_Analysis(void);//�������ݷ�������
#endif


#endif


