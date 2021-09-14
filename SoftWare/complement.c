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

#include "complement.h"


/**
 * @Brief:��ӡ������
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
 * @Brief:ԭ��ת����
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
		// Serial_println("����������λΪ1��Ҳ���Ǹ�����");
		//����������λΪ1��Ҳ���Ǹ�����
		//�������ķ����ǳ���ԭ�����λ����λȫ��ȡ��
		for (uint8_t i = 0; i < (Length-1); i++)
    {
      if(OriginalCode & (1 << i))//��λ��1
      {
      }
      else//��λ��0
      {
        InverseCode |= (1 << i);
      }
    }
    InverseCode |= (OriginalCode & (1 << (Length-1)));
	}
  else
  {
    //����������λΪ0��Ҳ����������
		//�������ķ�����ԭ��
		// Serial_println("����������λΪ0��Ҳ����������");
    InverseCode = OriginalCode;
  }

  return InverseCode;
}


/**
 * @Brief:ԭ��ת����
 * @Param:
 * @Return:
 * @Note:
 * @Author:
 */
uint32_t OriginalCode_to_Complement(uint32_t OriginalCode,uint8_t Length)
{
  uint32_t InverseCode = 0;//����
	uint32_t Complement = 0;//����
	
  InverseCode = OriginalCode_to_InverseCode(OriginalCode,Length);

  if(InverseCode & (1 << (Length-1)))
  {
    //����������λΪ1��Ҳ���Ǹ�����
		//�������ķ����ǳ���ԭ�����λ����λȫ��ȡ��,�����Ƿ���+1
    Complement = InverseCode + 1;
  }
  else
  {
    //����������λΪ0��Ҳ����������
		//�������ķ�����ԭ��,����Ҳ��ԭ��
    Complement = InverseCode;
  }

	return Complement;
}


/**
 * @Brief:����ת����
 * @Param:
 * @Return:
 * @Note:
 * @Author:
 */
uint32_t Complement_to_InverseCode(uint32_t Complement,uint8_t Length)
{
  uint32_t InverseCode = 0;//����

  if (Complement & (1 << (Length-1)))
  {
    //�������ķ�����ڲ��� -1
    InverseCode = Complement - 1;
  }
  else
  {
    //�������ķ���͵��ڲ���
    InverseCode = Complement;
  }
    
  
  return InverseCode;
}


/**
 * @Brief:����תԭ��
 * @Param:
 * @Return:
 * @Note:
 * @Author:
 */
uint32_t Complement_to_OriginalCode(uint32_t Complement,uint8_t Length)
{
  uint32_t InverseCode = 0;//����
  uint32_t OriginalCode = 0;//ԭ��

  InverseCode = Complement_to_InverseCode(Complement,Length);

  if (InverseCode & (1 << (Length-1)))
  {
    //��������ԭ����ڷ��������λ֮��ȡ��
    for (uint8_t i = 0; i < (Length-1); i++)
    {
      if(InverseCode & (1 << i))//��λ��1
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
    //��������ԭ����ڷ���
    OriginalCode = InverseCode;
  }
  
  return OriginalCode;
}
