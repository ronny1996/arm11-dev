#include "uart.h" 
#define GPM_CON (*((volatile unsigned int *)(0x7f008820)))
#define GPM_DAT  (*((volatile unsigned int *)(0x7f008824)))


void delay(void)
{
    volatile unsigned int i = 0x7FFFF;
    while(i--);
}
void led_init(void)
{
    GPM_CON = 0X1111;
    GPM_DAT  = 0X0;
}

//ATPCS 规则:  mix asm and c
int main(void)
{ 
    led_init();
    uart_init(); 
    GPM_DAT = 0x1F;
	while (1)
	{ 
		GPM_DAT = ~GPM_DAT;
		delay();
	}
    return 0;   
}