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
#include "soft_i2c.h"



/**
 * @Brief:����SDA��·Ϊ���ģʽ����ʱΪ����д
 * @Param:
 * @Return:
 * @Note:
 * @Author:
 */
void I2C_SDA_OUT()
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /*Configure GPIO pin Output Level */
  //HAL_GPIO_WritePin(GPIOB, I2C_SDA_Pin, GPIO_PIN_SET);
  /*Configure GPIO pins : PBPin PBPin */
  GPIO_InitStruct.Pin = SDA_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(SDA_PORT, &GPIO_InitStruct);
}


/**
 * @Brief:����SDA��·Ϊ����ģʽ����ʱΪ������
 * @Param:
 * @Return:
 * @Note:
 * @Author:
 */
void I2C_SDA_IN()
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /*Configure GPIO pin Output Level */
  //HAL_GPIO_WritePin(GPIOB, I2C_SDA_Pin, GPIO_PIN_SET);
  /*Configure GPIO pins : PBPin PBPin */
  GPIO_InitStruct.Pin = SDA_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(SDA_PORT, &GPIO_InitStruct);
}


/**
 * @Brief:I2C��ʱ
 * @Param:
 * @Return:
 * @Note:
 * @Author:
 */
void I2C_Delay(void)
{
	delay_us(5);
}


/**
 * @Brief:I2C��ʼ�ź�
 * @Param:
 * @Return:
 * @Note:
 * @Author:
 */
void I2C_Start()
{
	I2C_SDA_1;
	I2C_SCL_1;
	I2C_Delay();
	
	//SDA���0
	I2C_SDA_0;
	I2C_Delay();
	
	//SCL���0
	I2C_SCL_0;
	I2C_Delay();
}


/**
 * @Brief:I2Cֹͣ�ź�
 * @Param:
 * @Return:
 * @Note:
 * @Author:
 */
void I2C_Stop()
{
  I2C_SCL_1;
	I2C_SDA_0;
	I2C_Delay();
	
	I2C_SDA_1;
	I2C_Delay();
}


/**
 * @Brief:����Ӧ��
 * @Param:
 * @Return:
 * @Note:
 * @Author:
 */
void I2C_ACK() //Master ack
{
  I2C_SDA_0;
	
	I2C_SCL_1;
	I2C_Delay();
	
	I2C_SCL_0;
	I2C_Delay();
	
	//һ��Ҫ�ǵ��ͷ�����
	I2C_SDA_1; 
}


/**
 * @Brief:������Ӧ��
 * @Param:
 * @Return:
 * @Note:
 * @Author:
 */
void I2C_NACK() //Master NAck
{
  I2C_SDA_1;  //����ʡ��
	
	I2C_SCL_1;
	I2C_Delay();
	
	I2C_SCL_0;
	I2C_Delay();
}


/**
 * @Brief:�����ȴ�Ӧ��0����Ӧ��1����Ӧ��
 * @Param:
 * @Return:	0:ack 
						1:nack
 * @Note:
 * @Author:
 */
uint8_t I2C_Wait_Ack(void)//wait slaver ack  0 means ack OK; 1 means ack Fail;
{
  uint8_t ret = 0;
	
	I2C_SDA_1; 
	
	I2C_SCL_1;
	I2C_Delay();
		
	ret = I2C_SDA_READ(); //��SDA�������������0����ʾ�ӻ�ACK�����Ϊ1����ʾ�ӻ�NACK
	
	I2C_SCL_0;
	I2C_Delay();
	
	return ret;
}


/**
 * @Brief:i2c����ָ��
 * @Param:
 * @Return:
 * @Note:
 * @Author:
 */
void I2C_Send_Byte(uint8_t byte)
{
  int i = 0;
	
	//�����λ��ʼ����
	for(i=0; i<8; i++)
	{
		if(byte & 0x80) 
		  I2C_SDA_1;   //SDA���1
		else 
      I2C_SDA_0;  //SDA���0
		
		I2C_SCL_1;
		I2C_Delay();
		
		I2C_SCL_0;
		I2C_Delay();
		
		byte = byte << 1;
	}
	
	I2C_SDA_1;
}

/**
 * @Brief:i2c��ȡָ��
 * @Param:
 * @Return:
 * @Note:
 * @Author:
 */
uint8_t I2C_Read_Byte(void)
{
  int i = 0;
	uint8_t value = 0;
	
	for(i=0; i<8; i++)
	{
		I2C_SCL_1;
		I2C_Delay();
		
		//�������Ǹ�λ����Ϊ�ӻ��ǴӸ�λ��ʼ���͵�
		value = value | (I2C_SDA_READ() << (7-i));
		
		I2C_SCL_0;
		I2C_Delay();
	}

	return value;
}

