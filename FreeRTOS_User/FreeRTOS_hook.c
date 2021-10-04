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
#include "FreeRTOS_hook.h"

/**
 * @Brief:空闲钩子函数
 * @Param:
 * @Return:
 * @Note:	只要空闲任务正在运行，就会重复调用空闲挂钩
					空闲挂钩函数不能调用任何可能导致其阻塞的 API 函数
 * @Author:
 */
void vApplicationIdleHook(void)
{
//	Info_Println("!!!!");
}


/**
 * @Brief:滴答钩子函数
 * @Param:
 * @Return:
 * @Note:	当滴答中断发生时，就会调用滴答钩子函数
					从 ISR 内执行，因此必须非常短，不使用太多堆栈
					并且只能调用“FromISR”或“FROM_ISR”结尾的 API 函数
 * @Author:
 */
void vApplicationTickHook(void)
{
//	Info_Println("Tick");
}


/**
 * @Brief:Malloc失败钩子函数
 * @Param:
 * @Return:
 * @Note:当Malloc失败时，就会调用Malloc失败钩子函数
 * @Author:
 */
void vApplicationMallocFailedHook(void)
{
	taskDISABLE_INTERRUPTS();
	Error_Println("Malloc Fail");
	for(;;);
}


/**
 * @Brief:堆栈溢出钩子函数
 * @Param:
 * @Return:
 * @Note:当堆栈溢出时，就会调用堆栈溢出钩子函数
 * @Author:
 */
void vApplicationStackOverflowHook(TaskHandle_t pxTask, char *pcTaskName)
{
	char TaskName[configMAX_TASK_NAME_LEN];
	strncpy(TaskName, pcTaskGetName(pxTask), sizeof(TaskName));
	Error_Println("名称为%s的任务堆栈溢出!",TaskName);
	for(;;);
}


/**
 * @Brief:守护进程任务启动钩子函数
 * @Param:
 * @Return:
 * @Note:当守护进程任务启动时，就会调用守护进程任务启动钩子函数
 * @Author:
 */
void vApplicationDaemonTaskStartupHook(void)
{
	Info_Println("Daemon Task Startup");
}






static StackType_t IdleTaskStack[configMINIMAL_STACK_SIZE];//空闲任务任务堆栈
static StaticTask_t IdleTaskTCB;//空闲任务控制块 
/**
 * @Brief:获取空闲任务地堆栈和控制块内存
 * @Param:ppxIdleTaskTCBBuffer:任务控制块内存
					ppxIdleTaskStackBuffer:任务堆栈内存
					pulIdleTaskStackSize:任务堆栈大小
 * @Return:
 * @Note:
 * @Author:
 */
void vApplicationGetIdleTaskMemory(	
	StaticTask_t **ppxIdleTaskTCBBuffer,
	StackType_t **ppxIdleTaskStackBuffer,
	uint32_t *pulIdleTaskStackSize)
{
	*ppxIdleTaskTCBBuffer = &IdleTaskTCB;
	*ppxIdleTaskStackBuffer = IdleTaskStack;
	*pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
}


static StackType_t TimerTaskStack[configTIMER_TASK_STACK_DEPTH];//定时器服务任务堆栈
static StaticTask_t TimerTaskTCB;//定时器服务任务控制块
/**
 * @Brief:获取定时器服务任的堆栈和控制块内存
 * @Param:ppxTimerTaskTCBBuffer:任务控制块内存 
					ppxTimerTaskStackBuffer:任务堆栈内存
					pulTimerTaskStackSize:任务堆栈大小 任务堆栈大小
 * @Return:
 * @Note:
 * @Author:
 */
void vApplicationGetTimerTaskMemory(
	StaticTask_t **ppxTimerTaskTCBBuffer,
	StackType_t **ppxTimerTaskStackBuffer,
	uint32_t *pulTimerTaskStackSize)
{
	*ppxTimerTaskTCBBuffer = &TimerTaskTCB;
	*ppxTimerTaskStackBuffer = TimerTaskStack;
	*pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
}

