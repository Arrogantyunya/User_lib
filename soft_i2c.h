/****************************************Copyright (c)****************************************************
 

**--------------File Info---------------------------------------------------------------------------------

** File name:
** Last modified Date:

** Last Version:

** Descriptions:
**--------------------------------------------------------------------------------------------------------

** Created by:		¡ıº“ª‘ 
** Created date:	2021/xx/xx

** Version:				V1.0
** Descriptions:
**--------------------------------------------------------------------------------------------------------*/
#ifndef _SOFT_I2C_H_
#define _SOFT_I2C_H_

#include "main.h"

#include "User_Delay.h"

#define SCL_PORT				SCL_SOFT_GPIO_Port
#define SCL_PIN					SCL_SOFT_Pin
#define	SDA_PORT				SDA_SOFT_GPIO_Port
#define SDA_PIN					SDA_SOFT_Pin

#define I2C_SCL_1 			HAL_GPIO_WritePin(SCL_PORT, SCL_PIN, GPIO_PIN_SET)
#define I2C_SCL_0 			HAL_GPIO_WritePin(SCL_PORT, SCL_PIN, GPIO_PIN_RESET)
#define I2C_SDA_1 			HAL_GPIO_WritePin(SDA_PORT, SDA_PIN, GPIO_PIN_SET)
#define I2C_SDA_0 			HAL_GPIO_WritePin(SDA_PORT, SDA_PIN, GPIO_PIN_RESET)
#define I2C_SDA_READ()  HAL_GPIO_ReadPin(SDA_PORT, SDA_PIN)

void I2C_SDA_OUT(void);
void I2C_SDA_IN(void);
void I2C_Delay(void);


void I2C_Start(void);
void I2C_Stop(void);
void I2C_ACK(void);
void I2C_NACK(void);
uint8_t I2C_Wait_Ack(void);
void I2C_Send_Byte(uint8_t byte);
uint8_t I2C_Read_Byte(void);

#endif



