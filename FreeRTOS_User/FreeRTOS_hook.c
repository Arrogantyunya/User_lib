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
#include "FreeRTOS_hook.h"

/**
 * @Brief:���й��Ӻ���
 * @Param:
 * @Return:
 * @Note:	ֻҪ���������������У��ͻ��ظ����ÿ��йҹ�
					���йҹ��������ܵ����κο��ܵ����������� API ����
 * @Author:
 */
void vApplicationIdleHook(void)
{
//	Info_Println("!!!!");
}


/**
 * @Brief:�δ��Ӻ���
 * @Param:
 * @Return:
 * @Note:	���δ��жϷ���ʱ���ͻ���õδ��Ӻ���
					�� ISR ��ִ�У���˱���ǳ��̣���ʹ��̫���ջ
					����ֻ�ܵ��á�FromISR����FROM_ISR����β�� API ����
 * @Author:
 */
void vApplicationTickHook(void)
{
//	Info_Println("Tick");
}


/**
 * @Brief:Mallocʧ�ܹ��Ӻ���
 * @Param:
 * @Return:
 * @Note:��Mallocʧ��ʱ���ͻ����Mallocʧ�ܹ��Ӻ���
 * @Author:
 */
void vApplicationMallocFailedHook(void)
{
	taskDISABLE_INTERRUPTS();
	Error_Println("Malloc Fail");
	for(;;);
}


/**
 * @Brief:��ջ������Ӻ���
 * @Param:
 * @Return:
 * @Note:����ջ���ʱ���ͻ���ö�ջ������Ӻ���
 * @Author:
 */
void vApplicationStackOverflowHook(TaskHandle_t pxTask, char *pcTaskName)
{
	char TaskName[configMAX_TASK_NAME_LEN];
	strncpy(TaskName, pcTaskGetName(pxTask), sizeof(TaskName));
	Error_Println("����Ϊ%s�������ջ���!",TaskName);
	for(;;);
}


/**
 * @Brief:�ػ����������������Ӻ���
 * @Param:
 * @Return:
 * @Note:���ػ�������������ʱ���ͻ�����ػ����������������Ӻ���
 * @Author:
 */
void vApplicationDaemonTaskStartupHook(void)
{
	Info_Println("Daemon Task Startup");
}






static StackType_t IdleTaskStack[configMINIMAL_STACK_SIZE];//�������������ջ
static StaticTask_t IdleTaskTCB;//����������ƿ� 
/**
 * @Brief:��ȡ��������ض�ջ�Ϳ��ƿ��ڴ�
 * @Param:ppxIdleTaskTCBBuffer:������ƿ��ڴ�
					ppxIdleTaskStackBuffer:�����ջ�ڴ�
					pulIdleTaskStackSize:�����ջ��С
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


static StackType_t TimerTaskStack[configTIMER_TASK_STACK_DEPTH];//��ʱ�����������ջ
static StaticTask_t TimerTaskTCB;//��ʱ������������ƿ�
/**
 * @Brief:��ȡ��ʱ�������εĶ�ջ�Ϳ��ƿ��ڴ�
 * @Param:ppxTimerTaskTCBBuffer:������ƿ��ڴ� 
					ppxTimerTaskStackBuffer:�����ջ�ڴ�
					pulTimerTaskStackSize:�����ջ��С �����ջ��С
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

