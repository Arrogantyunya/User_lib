/****************************************Copyright (c)****************************************************


**--------------File Info---------------------------------------------------------------------------------

** File name:
** Last modified Date:

** Last Version:

** Descriptions:
**--------------------------------------------------------------------------------------------------------

** Created by:		刘家辉
** Created date:	2020/xx/xx

** Version:				V1.0
** Descriptions:
**--------------------------------------------------------------------------------------------------------*/

#ifndef _USER_CONF_H_
#define _USER_CONF_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>



/*串口Debug相关配置*/
#define STM32_CHIP						true		//使用stm32芯片
//#define ARDUINO_CHIP					true		//使用Arduino芯片
#define MY_DEBUG							true		//Debug开关
#define USE_HyperTerminal			false 	//使用HyperTerminal串口工具,可以设置字符颜色
#define DETAILED_OUTPUT				false		//详细输出(false关闭详细输出，不会将__FILE__，__LINE__进行输出)

#if (STM32_CHIP || ARDUINO_CHIP)

#if ARDUINO_CHIP
#define Debug_Serial					Serial
#include <Arduino.h>
//int serial_putc(char c, struct __file*);
//void printf_begin(void);
#if MY_DEBUG
#if USE_HyperTerminal
#if DETAILED_OUTPUT
#define Error_Println(...)						Debug_Serial.println(String(F("\033[31m[Error]\033[0m")) + "-["+__func__+"]" + "-["+__FILE__+":"+__LINE__+"]" + "-["+__VA_ARGS__+"]");
#define Warn_Println(...)							Debug_Serial.println(String(F("\033[35m[Warn]\033[0m")) + "-["+__func__+"]" + "-["+__FILE__+":"+__LINE__+"]" + "-["+__VA_ARGS__+"]");
#define Info_Println(...)							Debug_Serial.println(String(F("\033[36m[Info]\033[0m")) + "-["+__func__+"]" + "-["+__FILE__+":"+__LINE__+"]" + "-["+__VA_ARGS__+"]");
#define Debug_Println(...)						Debug_Serial.println(String(F("\033[34m[Debug]\033[0m")) + "-["+__func__+"]" + "-["+__FILE__+":"+__LINE__+"]" + "-["+__VA_ARGS__+"]");
#else
#define Error_Println(...)						Debug_Serial.println(String(F("\033[31m[Error]\033[0m")) + "-["+__func__+"]" + "-["+__VA_ARGS__+"]");
#define Warn_Println(...)							Debug_Serial.println(String(F("\033[35m[Warn]\033[0m")) + "-["+__func__+"]" + "-["+__VA_ARGS__+"]");
#define Info_Println(...)							Debug_Serial.println(String(F("\033[36m[Info]\033[0m")) + "-["+__func__+"]" + "-["+__VA_ARGS__+"]");
#define Debug_Println(...)						Debug_Serial.println(String(F("\033[34m[Debug]\033[0m")) + "-["+__func__+"]" + "-["+__VA_ARGS__+"]");
#endif // DETAILED_OUTPUT
#else
#if DETAILED_OUTPUT
#define Error_Println(...)						Debug_Serial.println(String(F("[Error]")) + "-["+__func__+"]" + "-["+__FILE__+":"+__LINE__+"]" + "-["+__VA_ARGS__+"]");
#define Warn_Println(...)							Debug_Serial.println(String(F("[Warn]")) + "-["+__func__+"]" + "-["+__FILE__+":"+__LINE__+"]" + "-["+__VA_ARGS__+"]");
#define Info_Println(...)							Debug_Serial.println(String(F("[Info]")) + "-["+__func__+"]" + "-["+__FILE__+":"+__LINE__+"]" + "-["+__VA_ARGS__+"]");
#define Debug_Println(...)						Debug_Serial.println(String(F("[Debug]")) + "-["+__func__+"]" + "-["+__FILE__+":"+__LINE__+"]" + "-["+__VA_ARGS__+"]");
#else
#define Error_Println(...)						Debug_Serial.println(String(F("[Error]")) + "-["+__func__+"]" + "-["+__VA_ARGS__+"]");
#define Warn_Println(...)							Debug_Serial.println(String(F("[Warn]")) + "-["+__func__+"]" + "-["+__VA_ARGS__+"]");
#define Info_Println(...)							Debug_Serial.println(String(F("[Info]")) + "-["+__func__+"]" + "-["+__VA_ARGS__+"]");
#define Debug_Println(...)						Debug_Serial.println(String(F("[Debug]")) + "-["+__func__+"]" + "-["+__VA_ARGS__+"]");
#endif // DETAILED_OUTPUT
#endif // USE_HyperTerminal
#else
#define Error_Println(...)
#define Warn_Println(...)
#define Info_Println(...)
#define Debug_Println(...)
#endif // MY_DEBUG
#endif // ARDUINO_CHIP

#if STM32_CHIP
#include "usart.h"
#if MY_DEBUG
#if USE_HyperTerminal
#define Serial1_print(...)						printf(__VA_ARGS__)
#define Serial1_println(...)					printf(__VA_ARGS__);printf("\r\n")
#define Feiji_Println(title,fmt,...)	printf("{" #title ":" fmt "}\r\n",__VA_ARGS__);
#if DETAILED_OUTPUT
#define Error_Println(X,...)					printf("\033[31m" "[Error]" "\033[0m" "-[%s]" "-[%s:%d]" "-["X"]\r\n",__func__,__FILE__,__LINE__,##__VA_ARGS__);//红
#define Warn_Println(X,...)						printf("\033[35m" "[Warn]" "\033[0m" "-[%s]" "-[%s:%d]" "-["X"]\r\n",__func__,__FILE__,__LINE__,##__VA_ARGS__);//紫红
#define Info_Println(X,...)						printf("\033[36m" "[Info]" "\033[0m" "-[%s]" "-[%s:%d]" "-["X"]\r\n",__func__,__FILE__,__LINE__,##__VA_ARGS__);//青蓝
#define Debug_Println(X,...)					printf("\033[34m" "[Debug]" "\033[0m" "-[%s]" "-[%s:%d]" "-["X"]\r\n",__func__,__FILE__,__LINE__,##__VA_ARGS__);//蓝
#else
#define Error_Println(X,...)					printf("\033[31m" "[Error]" "\033[0m" "-[%s]" "-["X"]\r\n",__func__,##__VA_ARGS__);//红
#define Warn_Println(X,...)						printf("\033[35m" "[Warn]" "\033[0m" "-[%s]" "-["X"]\r\n",__func__,##__VA_ARGS__);//紫红
#define Info_Println(X,...)						printf("\033[36m" "[Info]" "\033[0m" "-[%s]" "-["X"]\r\n",__func__,##__VA_ARGS__);//青蓝
#define Debug_Println(X,...)					printf("\033[34m" "[Debug]" "\033[0m" "-[%s]" "-["X"]\r\n",__func__,##__VA_ARGS__);//蓝
#endif // DETAILED_OUTPUT
#else
#define Serial_print(...)							printf(__VA_ARGS__);
#define Serial_println(...)						printf(__VA_ARGS__);printf("\r\n");
#define Feiji_Println(title,fmt,...)	printf("{" #title ":" fmt "}\r\n",__VA_ARGS__);
#if DETAILED_OUTPUT
#define Error_Println(X,...)					printf("[Error]" "-[%s]" "-[%s:%d]" "-["X"]\r\n",__func__,__FILE__,__LINE__,##__VA_ARGS__);
#define Warn_Println(X,...)						printf("[Warn]" "-[%s]" "-[%s:%d]" "-["X"]\r\n",__func__,__FILE__,__LINE__,##__VA_ARGS__);
#define Info_Println(X,...)						printf("[Info]" "-[%s]" "-[%s:%d]" "-["X"]\r\n",__func__,__FILE__,__LINE__,##__VA_ARGS__);
#define Debug_Println(X,...)					printf("[Debug]" "-[%s]" "-[%s:%d]" "-["X"]\r\n",__func__,__FILE__,__LINE__,##__VA_ARGS__);
#else
#define Error_Println(X,...)					printf("[Error]" "-[%s]" "-["X"]\r\n",__func__,##__VA_ARGS__);
#define Warn_Println(X,...)						printf("[Warn]" "-[%s]" "-["X"]\r\n",__func__,##__VA_ARGS__);
#define Info_Println(X,...)						printf("[Info]" "-[%s]" "-["X"]\r\n",__func__,##__VA_ARGS__);
#define Debug_Println(X,...)					printf("[Debug]" "-[%s]" "-["X"]\r\n",__func__,##__VA_ARGS__);
#endif // DETAILED_OUTPUT
#endif // USE_HyperTerminal
#else
#define Serial_print(...)
#define Serial_println(...)
#define Error_Println(X,...)
#define Warn_Println(X,...)
#define Info_Println(X,...)
#define Debug_Println(X,...)
#endif // MY_DEBUG
#endif // STM32_CHIP


#endif // (STM32_CHIP || ARDUINO_CHIP)





//printf("\033[30m""初始化完成...\r\n""\033[0m");//黑色显示
//printf("\033[31m""初始化完成...\r\n""\033[0m");//红色显示
//printf("\033[32m""初始化完成...\r\n""\033[0m");//绿色显示
//printf("\033[33m""初始化完成...\r\n""\033[0m");//黄色显示
//printf("\033[34m""初始化完成...\r\n""\033[0m");//蓝色显示
//printf("\033[35m""初始化完成...\r\n""\033[0m");//紫红色显示
//printf("\033[36m""初始化完成...\r\n""\033[0m");//青蓝色显示
//printf("\033[37m""初始化完成...\r\n""\033[0m");//白色显示




#endif // !_USER_CONF_H_
