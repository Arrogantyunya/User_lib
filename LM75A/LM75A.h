/****************************************Copyright (c)****************************************************
 

**--------------File Info---------------------------------------------------------------------------------

** File name:
** Last modified Date:

** Last Version:

** Descriptions:
**--------------------------------------------------------------------------------------------------------

** Created by:		Áõ¼Ò»Ô 
** Created date:	2021/xx/xx

** Version:				V1.0
** Descriptions:
**--------------------------------------------------------------------------------------------------------*/
#ifndef _LM75A_H_
#define _LM75A_H_

#include <stdint.h>

#include "soft_i2c.h"

#include "User_Conf.h"
#include "complement.h"


/*LM75AµÄIICµØÖ·*/
/*0b1001111X = 0x9E*/
#define LM75A_IIC_ADDRESS				0x9E
#define LM75A_IIC_ADDRESS_R			0x9E
#define LM75A_IIC_ADDRESS_W			0x9F

/*LM75AµÄ¼Ä´æÆ÷µØÖ·*/
#define LM75A_TEMP_ADDRESS			0x00	//ÎÂ¶È¼Ä´æÆ÷
#define LM75A_CONF_ADDRESS			0x01	//ÅäÖÃ¼Ä´æÆ÷
#define LM75A_TOS_ADDRESS				0x03	//¹ýÈÈ¹Ø¶ÏãÐÖµ¼Ä´æÆ÷
#define LM75A_THYST_ADDRESS			0x02	//ÖÍºó¼Ä´æÆ÷



float Read_LM75A_Temp(void);
uint8_t LM75_readoneByte(uint8_t addr);
void LM75_writeoneByte(uint8_t addr, uint8_t dt);
uint16_t LM75_readtwoByte(uint8_t addr);
void LM75_writetwoByte(uint8_t addr, uint16_t dt);

#endif
