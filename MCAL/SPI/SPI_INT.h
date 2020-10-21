#ifndef _SPI_INTERFACE_H_
#define _SPI_INTERFACE_H_


void SPI_SetCallBack(void(*LocPFunc)(void));


void SPI_MASTERINIT(void);
void SPI_SLAVEINIT(void);
u8 SPI_Transceiver(u8 Data);
void SPI_Enterrupt_Enable(void);














#endif
