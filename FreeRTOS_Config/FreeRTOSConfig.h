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

#define configUSE_PREEMPTION			1		//1:使能抢占式调度器 0:使能合作式调度器
#define configSUPPORT_STATIC_ALLOCATION          0
#define configSUPPORT_DYNAMIC_ALLOCATION         1	//1:使用从 FreeRTOS 堆自动分配的 RAM 创建 RTOS 对象
#define configUSE_IDLE_HOOK				0		//1：使能空闲任务的钩子函数
#define configUSE_TICK_HOOK				0		//1：使能滴答定时器中断里面执行的钩子函数
#define configCPU_CLOCK_HZ				( SystemCoreClock )	//系统主频时钟
#define configTICK_RATE_HZ				( ( TickType_t ) 1000 )	//系统时钟节拍数,1MS
#define configMAX_PRIORITIES			( 16 )	//可供用户使用的最大任务优先级数 0 ~ n-1。
#define configMINIMAL_STACK_SIZE		( ( unsigned short ) 128 )	//空闲任务的栈大小
/*由于 Cortex-M3 和 M4 内核具有双堆栈指针，MSP 主堆栈指针和 PSP 进程堆栈指针，或者叫 PSP
任务堆栈指针也是可以的。在 FreeRTOS 操作系统中，主堆栈指针 MSP 是给系统栈空间使用的，进
程堆栈指针 PSP 是给任务栈使用的。 也就是说，在 FreeRTOS 任务中，所有栈空间的使用都是通过
PSP 指针进行指向的。 一旦进入了中断函数以及可能发生的中断嵌套都是用的 MSP 指针。这个知识
点要记住它，当前可以不知道这是为什么，但是一定要记住。下面申请的栈空间是给系统任务使用的
，使用PSP。IDE里定义的栈空间是给中断服务函数使用的，使用MSP。*/
#define configTOTAL_HEAP_SIZE			( ( size_t ) ( 40 * 1024 ) )	//堆大小
#define configMAX_TASK_NAME_LEN			( 20 )	//定义任务最大字符数，'\0'计算在内
#define configUSE_TRACE_FACILITY			1	//1:使能添加额外的结构体成员和函数，来协助可视化和追踪
#define configUSE_16_BIT_TICKS				0	//设置系统节拍计数TickType_t数据长度为16位。32位处理器设置为0，不使用。
#define configIDLE_SHOULD_YIELD				1
#define configUSE_MUTEXES							1	//1:使能互斥信号
#define configUSE_RECURSIVE_MUTEXES		1	//1:使用递归互斥信号量
#define INCLUDE_xQueueGetMutexHolder	1	//1:使能xSemaphoreGetMutexHolder函数
#define configCHECK_FOR_STACK_OVERFLOW	0
#define configQUEUE_REGISTRY_SIZE			8
#define configUSE_TASK_NOTIFICATIONS 	1	//使能任务通知
#define configTASK_NOTIFICATION_ARRAY_ENTRIES		2//设置每个任务的任务通知数组中的索引数
#define configUSE_QUEUE_SETS    			1	//1:使能队列集
#define configUSE_MALLOC_FAILED_HOOK	0
#define configUSE_APPLICATION_TASK_TAG	0
#define configUSE_COUNTING_SEMAPHORES	1	//为1时使用计数信号量
#define configUSE_PORT_OPTIMISED_TASK_SELECTION    1	////要使用专用优化的任务优先级算法，建议最大任务优先级不要设置超过32。(p282)
#define configGENERATE_RUN_TIME_STATS	0	//1:使能任务运行状态参数统计
#define configUSE_STATS_FORMATTING_FUNCTIONS 1	//configUSE_TRACE_FACILITY 和该宏都为1，使能vTaskList和vTaskGetRunTimeStats函数

/* Co-routine definitions. */
#define configUSE_CO_ROUTINES 		0
#define configMAX_CO_ROUTINE_PRIORITIES ( 2 )

/* Software timer definitions. */
#define configUSE_TIMERS				1	//使用软件定时器组
#define configTIMER_TASK_PRIORITY		( configMAX_PRIORITIES - 1 )//配置定时器任务的优先级
#define configTIMER_QUEUE_LENGTH		10	//配置定时器任务用到的消息队列大小，即能够储存的消息个数。
#define configTIMER_TASK_STACK_DEPTH	( configMINIMAL_STACK_SIZE * 2 )//配置定时器任务的任务栈大小

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

