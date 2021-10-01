/*
 * FreeRTOS V202012.00
 * Copyright (C) 2020 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://www.FreeRTOS.org
 * http://aws.amazon.com/freertos
 *
 * 1 tab == 4 spaces!
 */


#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

/*-----------------------------------------------------------
 * Application specific definitions.
 *
 * These definitions should be adjusted for your particular hardware and
 * application requirements.
 *
 * THESE PARAMETERS ARE DESCRIBED WITHIN THE 'CONFIGURATION' SECTION OF THE
 * FreeRTOS API DOCUMENTATION AVAILABLE ON THE FreeRTOS.org WEB SITE.
 *
 * See http://www.freertos.org/a00110.html
 *----------------------------------------------------------*/

/* Ensure stdint is only used by the compiler, and not the assembler. */
#if defined(__ICCARM__) || defined(__CC_ARM) || defined(__GNUC__)
	#include <stdint.h>
	extern uint32_t SystemCoreClock;
	void xPortSysTickHandler(void);
#endif

#define configUSE_PREEMPTION			1		//1:ʹ����ռʽ������ 0:ʹ�ܺ���ʽ������
#define configSUPPORT_STATIC_ALLOCATION          0
#define configSUPPORT_DYNAMIC_ALLOCATION         1	//1:ʹ�ô� FreeRTOS ���Զ������ RAM ���� RTOS ����
#define configUSE_IDLE_HOOK				0		//1��ʹ�ܿ�������Ĺ��Ӻ���
#define configUSE_TICK_HOOK				0		//1��ʹ�ܵδ�ʱ���ж�����ִ�еĹ��Ӻ���
#define configCPU_CLOCK_HZ				( SystemCoreClock )	//ϵͳ��Ƶʱ��
#define configTICK_RATE_HZ				( ( TickType_t ) 1000 )	//ϵͳʱ�ӽ�����,1MS
#define configMAX_PRIORITIES			( 16 )	//�ɹ��û�ʹ�õ�����������ȼ��� 0 ~ n-1��
#define configMINIMAL_STACK_SIZE		( ( unsigned short ) 128 )	//���������ջ��С
/*���� Cortex-M3 �� M4 �ں˾���˫��ջָ�룬MSP ����ջָ��� PSP ���̶�ջָ�룬���߽� PSP
�����ջָ��Ҳ�ǿ��Եġ��� FreeRTOS ����ϵͳ�У�����ջָ�� MSP �Ǹ�ϵͳջ�ռ�ʹ�õģ���
�̶�ջָ�� PSP �Ǹ�����ջʹ�õġ� Ҳ����˵���� FreeRTOS �����У�����ջ�ռ��ʹ�ö���ͨ��
PSP ָ�����ָ��ġ� һ���������жϺ����Լ����ܷ������ж�Ƕ�׶����õ� MSP ָ�롣���֪ʶ
��Ҫ��ס������ǰ���Բ�֪������Ϊʲô������һ��Ҫ��ס�����������ջ�ռ��Ǹ�ϵͳ����ʹ�õ�
��ʹ��PSP��IDE�ﶨ���ջ�ռ��Ǹ��жϷ�����ʹ�õģ�ʹ��MSP��*/
#define configTOTAL_HEAP_SIZE			( ( size_t ) ( 40 * 1024 ) )	//�Ѵ�С
#define configMAX_TASK_NAME_LEN			( 20 )	//������������ַ�����'\0'��������
#define configUSE_TRACE_FACILITY			1	//1:ʹ����Ӷ���Ľṹ���Ա�ͺ�������Э�����ӻ���׷��
#define configUSE_16_BIT_TICKS				0	//����ϵͳ���ļ���TickType_t���ݳ���Ϊ16λ��32λ����������Ϊ0����ʹ�á�
#define configIDLE_SHOULD_YIELD				1
#define configUSE_MUTEXES							1	//1:ʹ�ܻ����ź�
#define configUSE_RECURSIVE_MUTEXES		1	//1:ʹ�õݹ黥���ź���
#define INCLUDE_xQueueGetMutexHolder	1	//1:ʹ��xSemaphoreGetMutexHolder����
#define configCHECK_FOR_STACK_OVERFLOW	0
#define configQUEUE_REGISTRY_SIZE			8
#define configUSE_TASK_NOTIFICATIONS 	1	//ʹ������֪ͨ
#define configTASK_NOTIFICATION_ARRAY_ENTRIES		2//����ÿ�����������֪ͨ�����е�������
#define configUSE_QUEUE_SETS    			1	//1:ʹ�ܶ��м�
#define configUSE_MALLOC_FAILED_HOOK	0
#define configUSE_APPLICATION_TASK_TAG	0
#define configUSE_COUNTING_SEMAPHORES	1	//Ϊ1ʱʹ�ü����ź���
#define configUSE_PORT_OPTIMISED_TASK_SELECTION    1	////Ҫʹ��ר���Ż����������ȼ��㷨����������������ȼ���Ҫ���ó���32��(p282)
#define configGENERATE_RUN_TIME_STATS	0	//1:ʹ����������״̬����ͳ��
#define configUSE_STATS_FORMATTING_FUNCTIONS 1	//configUSE_TRACE_FACILITY �͸ú궼Ϊ1��ʹ��vTaskList��vTaskGetRunTimeStats����

/* Co-routine definitions. */
#define configUSE_CO_ROUTINES 		0
#define configMAX_CO_ROUTINE_PRIORITIES ( 2 )

/* Software timer definitions. */
#define configUSE_TIMERS				1	//ʹ�������ʱ����
#define configTIMER_TASK_PRIORITY		( configMAX_PRIORITIES - 1 )//���ö�ʱ����������ȼ�
#define configTIMER_QUEUE_LENGTH		10	//���ö�ʱ�������õ�����Ϣ���д�С�����ܹ��������Ϣ������
#define configTIMER_TASK_STACK_DEPTH	( configMINIMAL_STACK_SIZE * 2 )//���ö�ʱ�����������ջ��С

/* Set the following definitions to 1 to include the API function, or zero
to exclude the API function. */
#define INCLUDE_vTaskPrioritySet						1
#define INCLUDE_uxTaskPriorityGet						1
#define INCLUDE_vTaskDelete									1
#define INCLUDE_vTaskCleanUpResources				1
#define INCLUDE_vTaskSuspend								1
#define INCLUDE_vTaskDelayUntil							1
#define INCLUDE_vTaskDelay									1
#define INCLUDE_xTaskGetSchedulerState      1
#define INCLUDE_xTimerPendFunctionCall			0
#define INCLUDE_eTaskGetState								1

/* Cortex-M specific definitions. */
#ifdef __NVIC_PRIO_BITS
	/* __BVIC_PRIO_BITS will be specified when CMSIS is being used. */
	#define configPRIO_BITS       		__NVIC_PRIO_BITS
#else
	#define configPRIO_BITS       		4        /* 15 priority levels */
#endif

/* The lowest interrupt priority that can be used in a call to a "set priority"
function. */
#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY			15

/* The highest interrupt priority that can be used by any interrupt service
routine that makes calls to interrupt safe FreeRTOS API functions.  DO NOT CALL
INTERRUPT SAFE FREERTOS API FUNCTIONS FROM ANY INTERRUPT THAT HAS A HIGHER
PRIORITY THAN THIS! (higher priorities are lower numeric values. */
#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY	1

/* Interrupt priorities used by the kernel port layer itself.  These are generic
to all Cortex-M ports, and do not rely on any particular library functions. */
#define configKERNEL_INTERRUPT_PRIORITY 		( configLIBRARY_LOWEST_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )
/* !!!! configMAX_SYSCALL_INTERRUPT_PRIORITY must not be set to zero !!!!
See http://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html. */
#define configMAX_SYSCALL_INTERRUPT_PRIORITY 	( configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )
	
/* Normal assert() semantics without relying on the provision of an assert.h
header file. */
#define configASSERT( x ) if( ( x ) == 0 ) { taskDISABLE_INTERRUPTS(); for( ;; ); }	
	
/* Definitions that map the FreeRTOS port interrupt handlers to their CMSIS
standard names. */
#define vPortSVCHandler SVC_Handler
#define xPortPendSVHandler PendSV_Handler
//#define xPortSysTickHandler SysTick_Handler

#endif /* FREERTOS_CONFIG_H */

