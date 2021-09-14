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
#include "soft_i2c.h"



/**
 * @Brief:设置SDA线路为输出模式，此时为主机写
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
 * @Brief:设置SDA线路为输入模式，此时为主机读
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
 * @Brief:I2C延时
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
 * @Brief:I2C起始信号
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
	
	//SDA输出0
	I2C_SDA_0;
	I2C_Delay();
	
	//SCL输出0
	I2C_SCL_0;
	I2C_Delay();
}


/**
 * @Brief:I2C停止信号
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
 * @Brief:主机应答
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
	
	//一定要记得释放总线
	I2C_SDA_1; 
}


/**
 * @Brief:主机非应答
 * @Param:
 * @Return:
 * @Note:
 * @Author:
 */
void I2C_NACK() //Master NAck
{
  I2C_SDA_1;  //可以省略
	
	I2C_SCL_1;
	I2C_Delay();
	
	I2C_SCL_0;
	I2C_Delay();
}


/**
 * @Brief:主机等待应答，0：有应答；1：无应答
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
		
	ret = I2C_SDA_READ(); //读SDA，如果读到的是0，表示从机ACK，如果为1，表示从机NACK
	
	I2C_SCL_0;
	I2C_Delay();
	
	return ret;
}


/**
 * @Brief:i2c发送指令
 * @Param:
 * @Return:
 * @Note:
 * @Author:
 */
void I2C_Send_Byte(uint8_t byte)
{
  int i = 0;
	
	//从最高位开始发送
	for(i=0; i<8; i++)
	{
		if(byte & 0x80) 
		  I2C_SDA_1;   //SDA输出1
		else 
      I2C_SDA_0;  //SDA输出0
		
		I2C_SCL_1;
		I2C_Delay();
		
		I2C_SCL_0;
		I2C_Delay();
		
		byte = byte << 1;
	}
	
	I2C_SDA_1;
}

/**
 * @Brief:i2c读取指令
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
		
		//读到的是高位，因为从机是从高位开始发送的
		value = value | (I2C_SDA_READ() << (7-i));
		
		I2C_SCL_0;
		I2C_Delay();
	}

	return value;
}

