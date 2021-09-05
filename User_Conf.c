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
#include "User_Conf.h"

#if ARDUINO_CHIP
//int serial_putc(char c, struct __file*)
//{
//	Serial.write(c);
//	return c;
//}
//
//void printf_begin(void)
//{
//	fdevopen(&serial_putc, 0);
//}
#endif // ARDUINO_CHIP

#if STM32_CHIP
#ifdef __GNUC__
/* With GCC, small printf (option LD Linker->Libraries->Small printf
set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

PUTCHAR_PROTOTYPE
{
	/* Place your implementation of fputc here */
	/* e.g. write a character to the USART2 and Loop until the end of transmission */
	HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 0xFFFF);
	return ch;
}
#endif // STM32_CHIP

