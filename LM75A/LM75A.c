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
#include "LM75A.h"

float Read_LM75A_Temp(void)
{
	float Temp = 0.00;
	uint8_t val[2] = {0};
#if USE_SOFTI2C
	I2C_Start();
	I2C_Send_Byte(LM75A_IIC_ADDRESS);
	if(I2C_Wait_Ack() != 0) goto fail;

	I2C_Send_Byte(LM75A_TEMP_ADDRESS);
	if(I2C_Wait_Ack() != 0) goto fail;
	
	
	I2C_Start();
	I2C_Send_Byte(LM75A_IIC_ADDRESS+1);
	if(I2C_Wait_Ack() != 0) goto fail;
	
	val[0] = I2C_Read_Byte();
	val[1] = I2C_Read_Byte();
	if(I2C_Wait_Ack() != 0) goto fail;
	
fail:
	I2C_Stop();
#else
	HAL_StatusTypeDef Status;
	Status = HAL_I2C_Master_Transmit(&hi2c1,LM75A_IIC_ADDRESS,LM75A_TEMP_ADDRESS,1,0xff);
//	if(Status == HAL_OK)
//	{
//		Serial_println("���ͳɹ�");
//	}
//	else
//	{
//		Serial_println("����ʧ��");
//	}
	
	Status = HAL_I2C_Master_Receive(&hi2c1,LM75A_IIC_ADDRESS,val,2,0xff);
//	if(Status == HAL_OK)
//	{
//		Serial_println("���ճɹ�");
////		Serial_println("val[0] = 0x%02x",val[0]);
////		Serial_println("val[1] = 0x%02x",val[1]);
//	}
//	else
//	{
//		Serial_println("����ʧ��");
//	}
#endif

//	����11λ��Temp����������Tempֵ�ķ����� 
//1. ��D10��0���¶�ֵ���棩����Temp���ݵĶ����Ʋ��룩��0.125�棻 
//2. ��D10��1���¶�ֵ���棩����Temp���ݵĶ����Ʋ��룩��0.125�档
	
	uint16_t val_16 = ((uint16_t)val[0] << 8) | val[1];
	val_16 >>= 5;//��5λû��
	
	uint32_t val_32 = Complement_to_OriginalCode(val_16,11);
	val_32 &= 0x3ff;//D10�ķ���λ���ܼӽ�ȥ
	if((val_16 & 0x0400))
	{
		Temp = -(float)val_32*0.125;
	}
	else
	{
		Temp = (float)val_32*0.125;
	}
	
	return Temp;
}

#if USE_SOFTI2C
//read one Byte
uint8_t LM75_readoneByte(uint8_t addr)
{
	uint8_t temp = 0;
  I2C_Start();
	//send write hardware addr
	I2C_Send_Byte(LM75A_IIC_ADDRESS);
	I2C_Wait_Ack();
	//send registor addr
	I2C_Send_Byte(addr%256);
	I2C_Wait_Ack();
	
	I2C_Start();
	//send read hardware addr
	I2C_Send_Byte(LM75A_IIC_ADDRESS+1);
	I2C_Wait_Ack();
	temp = I2C_Read_Byte();
	I2C_Stop();
	return temp;
}


void LM75_writeoneByte(uint8_t addr, uint8_t dt)
{
  I2C_Start();
	//send write hardware addr
	I2C_Send_Byte(LM75A_IIC_ADDRESS);
	I2C_Wait_Ack();
	//send registor addr
	I2C_Send_Byte(addr%256);
	I2C_Wait_Ack();
 
	I2C_Send_Byte(dt);
	I2C_Wait_Ack();
	I2C_Stop();
	HAL_Delay(10);
}
 
//read two Byte
uint16_t LM75_readtwoByte(uint8_t addr)
{
	uint16_t temp = 0;
  I2C_Start();
	//send write hardware addr
	I2C_Send_Byte(LM75A_IIC_ADDRESS);
	I2C_Wait_Ack();
	//send registor addr
	I2C_Send_Byte(addr%256);
	I2C_Wait_Ack();
	
	I2C_Start();
	//send read hardware addr
	I2C_Send_Byte(LM75A_IIC_ADDRESS+1);
	I2C_Wait_Ack();
	temp = I2C_Read_Byte();
	temp <<= 8;
	temp = temp | I2C_Read_Byte();
	
	I2C_Stop();
	return temp;
}
 
void LM75_writetwoByte(uint8_t addr, uint16_t dt)
{
  I2C_Start();
	//send write hardware addr
	I2C_Send_Byte(LM75A_IIC_ADDRESS);
	I2C_Wait_Ack();
	//send registor addr
	I2C_Send_Byte(addr%256);
	I2C_Wait_Ack();
 
	I2C_Send_Byte(dt>>8);
	I2C_Wait_Ack();
	I2C_Send_Byte(dt&0xff);
	I2C_Wait_Ack();
	I2C_Stop();
	HAL_Delay(10);

}
#endif


