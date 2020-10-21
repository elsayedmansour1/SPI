#include"../../LIB/STD_TYPES.h"
#include"../../LIB/BIT_MATH.h"
#include"SPI_Reg.h"
#include"SPI_Config.h"
#include"../DIO/DIO_INT.h"
#include"../DIO/DIO_config.h"
#include"../Global Interrupt/GIE_config.h"


/****** Global Pointer To Function *********/
static void (*GPFunc)(void)=NULL;
void SPI_SetCallBack(void(*LocPFunc)(void))
{
GPFunc=LocPFunc;
}
ISR(__vector_12)
{
	if(GPFunc!=NULL)
	{
		GPFunc();
	}

}

void SPI_MASTERINIT(void)
{
	
	DIO_VidSetPinDirection(DIO_PORTB,PIN6,INPUT); //MISO
	DIO_VidSetPinDirection(DIO_PORTB,PIN5,OUTPUT); //MOSI
	DIO_VidSetPinDirection(DIO_PORTB,PIN4,OUTPUT); //SS

	/****SPI ENABLE****/
	SET_BIT(SPCR,SPE);	
	/***LSB DATA WORD TRANSIMIT***/
	SET_BIT(SPCR,DORD);
	/***SPI SELECTED AS MASTER***/
	SET_BIT(SPCR,MSTR);
	/***Clock Polarity(lading falling)***/
	SET_BIT(SPCR,CPOL);
	/***CPOL Functionality(setup/sample)***/
	SET_BIT(SPCR,CPHA);
	/***** Frequency/16*******/
	SET_BIT(SPCR,SPR0);
	CLR_BIT(SPCR,SPR1);
}
void SPI_SLAVEINIT(void)
{
	DIO_VidSetPinDirection(DIO_PORTB,PIN6,OUTPUT); //MISO
	DIO_VidSetPinDirection(DIO_PORTB,PIN5,INPUT); //MOSI
	DIO_VidSetPinDirection(DIO_PORTB,PIN4,INPUT); //SS
	/****SPI ENABLE****/
	SET_BIT(SPCR,SPE);	
	/***LSB DATA WORD TRANSIMIT***/
	SET_BIT(SPCR,DORD);
	/***SPI SELECTED AS SALVE***/
	CLR_BIT(SPCR,MSTR);
	/***Clock Polarity(lading falling)***/
	SET_BIT(SPCR,CPOL);
	/***CPOL Functionality(setup/sample)***/
	SET_BIT(SPCR,CPHA);
	/***** Frequency/16*******/
	SET_BIT(SPCR,SPR0);
	CLR_BIT(SPCR,SPR1);
}
u8 SPI_Transceiver(u8 Data)
{
	SPDR=Data;
	while(GET_BIT(SPSR,SPIF)==0);
	return SPDR;
}
void SPI_Enterrupt_Enable(void)
{
	/***SPI Interrupt Enable***/
	SET_BIT(SPCR,SPIE);
}
