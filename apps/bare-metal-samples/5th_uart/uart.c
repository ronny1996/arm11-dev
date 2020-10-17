#include "uart.h"
/*
DIV_VAL = UBRDIVn + (num of 1's in UDIVSLOTn)/16

DIV_VAL = (PCLK / (bps x 16 ) ) −1      
or
DIV_VAL = (EXT_UCLK0 / (bps x 16 ) ) −1
or
DIV_VAL = (EXT_UCLK1 / (bps x 16 ) ) −1
*/
#define GPACON (*((volatile int*)(0x7F008000)))
void uart_init(void)
{
    GPACON &= ~0xff;
	GPACON |= 0x22;

    ULCON0 = 0x03;       
    UCON0 = 0x05;
    UFCON0 = 0x01;      //fifo 
    UMCON0 = 0x00;     //no flow 
    UBRDIV0 = 35;          //PCLK = 66.5MHZ
    UDIVSLOT0 = 1;
}

char putchar(char ch)
{
    //while(!(UTRSTAT0&0x2));
    while(UFSTAT0&(1<<14));
    UTXH0 =  ch;
    return ch;
}
char getchar (void)
{
    //while(!(UTRSTAT0&0x1));
    while(!(UFSTAT0&0x7F));
    return URXH0;
}