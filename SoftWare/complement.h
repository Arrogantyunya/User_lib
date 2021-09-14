/****************************************Copyright (c)****************************************************
 

**--------------File Info---------------------------------------------------------------------------------

** File name:
** Last modified Date:

** Last Version:

** Descriptions:提供原码转反码；原码转补码；补码转反码；补码转原码的函数
**--------------------------------------------------------------------------------------------------------

** Created by:		刘家辉 
** Created date:	2021/xx/xx

** Version:				V1.0
** Descriptions:
**--------------------------------------------------------------------------------------------------------*/

#ifndef _COMPLEMENT_H_
#define _COMPLEMENT_H_

#include "User_Conf.h"

void Print_Binary(uint32_t Binary,uint8_t Length);//打印二进制

uint32_t OriginalCode_to_InverseCode(uint32_t OriginalCode,uint8_t Length);//原码转反码
uint32_t OriginalCode_to_Complement(uint32_t OriginalCode,uint8_t Length);//原码转补码

uint32_t Complement_to_InverseCode(uint32_t Complement,uint8_t Length);//补码转反码
uint32_t Complement_to_OriginalCode(uint32_t Complement,uint8_t Length);//补码转原码


#endif

