/*
 * main.c
 *
 *  Created on: Oct 13, 2020
 *      Author: elsay
 */
#include "../LIB/BIT_MATH.h"
#include "../LIB/STD_TYPES.h"
#include "../MCAL/DIO/DIO_INT.h"
#include "../MCAL/DIO/DIO_config.h"
#include "../MCAL/SPI/SPI_INT.h"
#include "../MCAL/Global Interrupt/GIE_INT.h"
int main(void)
{
	u8 num=0;
	DIO_VidSetPinDirection(DIO_PORTB, PIN0, OUTPUT);//LED_on
	DIO_VidSetPinDirection(DIO_PORTB, PIN1, OUTPUT);//LED_off
	while(1)
	{
		num=SPI_Transceiver(6);
		if(num==6)
		{
			DIO_VidSetPinValue(DIO_PORTB, PIN0, HIGH);
		}
		else
		{
			DIO_VidSetPinValue(DIO_PORTB, PIN1, HIGH);
		}
	}
	return 0;
}
