/****************************************Copyright (c)****************************************************


**--------------File Info---------------------------------------------------------------------------------

** File name:uart_analysis.h
** Last modified Date:

** Last Version:

** Descriptions:����һ������UART��IRQRX/DMARX���տ⣬ͨ��ʹ�ܶ�Ӧ�ĺ꣬����ʹ���Ѿ�����õĺ����ͱ������Լ����ô��ڻ�������С
**--------------------------------------------------------------------------------------------------------

** Created by:		���һ�
** Created date:	2021/xx/xx

** Version:				V1.0
** Descriptions:
**--------------------------------------------------------------------------------------------------------*/
#ifndef _UART_ANALYSIS_h_
#define _UART_ANALYSIS_h_

#include "User_Conf.h"

/* ��Ӧ�Ĵ���ʹ�ܱ�־λ */
#define UART1_ENABLE_IRQRX		true
#define UART2_ENABLE_IRQRX		false
#define UART3_ENABLE_IRQRX		false


#define UART1_REC_LEN_MAX		64		//���ջ�������С��
#define UART2_REC_LEN_MAX		64		//���ջ�������С��
#define UART3_REC_LEN_MAX		64		//���ջ�������С��

#if UART1_ENABLE_IRQRX
#define UART1_ENABLE_DMARX		false	//UART1 DMA����ʹ��
extern uint8_t UART1_Rec_Data[UART1_REC_LEN_MAX];	//���ջ���������
extern uint8_t UART1_Rec_Len;	//���ճ���
extern uint8_t UART1_Rec_Flag;//������ɱ�־λ
void MY_UART1_IRQHandler(void);//�����жϴ�����
void UART1_Data_Analysis(void);//�������ݷ�������
#endif

#if UART2_ENABLE_IRQRX
#define UART2_ENABLE_DMARX		true	//UART2 DMA����ʹ��
extern uint8_t UART2_Rec_Data[UART2_REC_LEN_MAX];	//���ջ���������
extern uint8_t UART2_Rec_Len;	//���ճ���
extern uint8_t UART2_Rec_Flag;//������ɱ�־λ
void MY_UART2_IRQHandler(void);//�����жϴ�����
void UART2_Data_Analysis(void);//�������ݷ�������
#endif

#if UART3_ENABLE_IRQRX
#define UART3_ENABLE_DMARX		true	//UART3 DMA����ʹ��
extern uint8_t UART3_Rec_Data[UART3_REC_LEN_MAX];	//���ջ���������
extern uint8_t UART3_Rec_Len;	//���ճ���
extern uint8_t UART3_Rec_Flag;//������ɱ�־λ
void MY_UART3_IRQHandler(void);//�����жϴ�����
void UART3_Data_Analysis(void);//�������ݷ�������
#endif


#endif


