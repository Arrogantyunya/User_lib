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

#include "complement.h"


/**
 * @Brief:打印二进制
 * @Param:
 * @Return:
 * @Note:
 * @Author:
 */
void Print_Binary(uint32_t Binary,uint8_t Length)
{
  for (uint8_t i = Length; i > 0; i--)
  {
    if ((Binary >> (i-1)) & 1)
    {
      Serial_print("1");
    }
    else
    {
      Serial_print("0");
    }
  }
  Serial_println("");
}



/**
 * @Brief:原码转反码
 * @Param:
 * @Return:
 * @Note:
 * @Author:
 */
uint32_t OriginalCode_to_InverseCode(uint32_t OriginalCode,uint8_t Length)
{
	uint32_t InverseCode = 0;
	
	if(OriginalCode & (1 << (Length-1)))
	{
		// Serial_println("这里代表符号位为1，也就是负整数");
		//这里代表符号位为1，也就是负整数
		//负整数的反码是除了原码符号位其他位全部取反
		for (uint8_t i = 0; i < (Length-1); i++)
    {
      if(OriginalCode & (1 << i))//该位是1
      {
      }
      else//该位是0
      {
        InverseCode |= (1 << i);
      }
    }
    InverseCode |= (OriginalCode & (1 << (Length-1)));
	}
  else
  {
    //这里代表符号位为0，也就是正整数
		//正整数的反码是原码
		// Serial_println("这里代表符号位为0，也就是正整数");
    InverseCode = OriginalCode;
  }

  return InverseCode;
}


/**
 * @Brief:原码转补码
 * @Param:
 * @Return:
 * @Note:
 * @Author:
 */
uint32_t OriginalCode_to_Complement(uint32_t OriginalCode,uint8_t Length)
{
  uint32_t InverseCode = 0;//反码
	uint32_t Complement = 0;//补码
	
  InverseCode = OriginalCode_to_InverseCode(OriginalCode,Length);

  if(InverseCode & (1 << (Length-1)))
  {
    //这里代表符号位为1，也就是负整数
		//负整数的反码是除了原码符号位其他位全部取反,补码是反码+1
    Complement = InverseCode + 1;
  }
  else
  {
    //这里代表符号位为0，也就是正整数
		//正整数的反码是原码,补码也是原码
    Complement = InverseCode;
  }

	return Complement;
}


/**
 * @Brief:补码转反码
 * @Param:
 * @Return:
 * @Note:
 * @Author:
 */
uint32_t Complement_to_InverseCode(uint32_t Complement,uint8_t Length)
{
  uint32_t InverseCode = 0;//反码

  if (Complement & (1 << (Length-1)))
  {
    //负整数的反码等于补码 -1
    InverseCode = Complement - 1;
  }
  else
  {
    //正整数的反码就等于补码
    InverseCode = Complement;
  }
    
  
  return InverseCode;
}


/**
 * @Brief:补码转原码
 * @Param:
 * @Return:
 * @Note:
 * @Author:
 */
uint32_t Complement_to_OriginalCode(uint32_t Complement,uint8_t Length)
{
  uint32_t InverseCode = 0;//反码
  uint32_t OriginalCode = 0;//原码

  InverseCode = Complement_to_InverseCode(Complement,Length);

  if (InverseCode & (1 << (Length-1)))
  {
    //负整数的原码等于反码除符号位之外取反
    for (uint8_t i = 0; i < (Length-1); i++)
    {
      if(InverseCode & (1 << i))//该位是1
      {
      }
      else
      {
        OriginalCode |=  (1 << i);
      }
      OriginalCode |= (InverseCode & (1 << (Length-1)));
    }
  }
  else
  {
    //正整数的原码等于反码
    OriginalCode = InverseCode;
  }
  
  return OriginalCode;
}
