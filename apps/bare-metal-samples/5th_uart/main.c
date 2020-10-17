#include "uart.h"

#define GPM_CON (*((volatile unsigned int *)(0x7f008820)))
#define GPM_DAT  (*((volatile unsigned int *)(0x7f008824)))


void delay(void)
{
    volatile int i = 0x10000;
    while(i--);
}
void led_init(void)
{
    GPM_CON = 0X1000;
    GPM_DAT  = 0X0;
}
//ATPCS 规则:  mix asm and c
void main(void)
{
    char ch;
    uart_init();
    while (1)
    {
        ch  = getchar();
        if(ch>='a'){
            putchar(ch - ('a' - 'A'));
        }else
        {
            putchar(ch + ('a' - 'A'));
        }
        
    }
}