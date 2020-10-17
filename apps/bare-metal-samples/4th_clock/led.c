

#define GPM_CON (*((volatile unsigned int *)(0x7f008820)))
#define GPM_DAT  (*((volatile unsigned int *)(0x7f008824)))


void delay()
{
    volatile int i = 0x10000;
    while(i--);
}

//ATPCS 规则:  mix asm and c
void main(void)
{
    int i = 0;
    GPM_CON = 0X1000;
    GPM_DAT  = 0X0;
    while (1)
    {
        GPM_DAT = i;
        i++;
        if(i==16)i=0;
        delay();
    }
}