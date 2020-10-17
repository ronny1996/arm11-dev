#ifndef __UART_H_
#define __UART_H_

/*
    register mapping
*/
#define ULCON0 (*((volatile unsigned int *)(0x7F005000)))
#define UCON0 (*((volatile unsigned int *)(0x7F005004)))
#define UFCON0 (*((volatile unsigned int *)(0x7F005008)))
#define UMCON0 (*((volatile unsigned int *)(0x7F00500C)))
#define UTRSTAT0 (*((volatile unsigned int *)(0x7F005010)))
#define UERSTAT0 (*((volatile unsigned int *)(0x7F005014)))
#define UFSTAT0 (*((volatile unsigned int *)(0x7F005018)))
#define UMSTAT0 (*((volatile unsigned int *)(0x7F00501C)))
#define UTXH0 (*((volatile unsigned int *)(0x7F005020)))
#define URXH0 (*((volatile unsigned int *)(0x7F005024)))
#define UBRDIV0 (*((volatile unsigned int *)(0x7F005028)))
#define UDIVSLOT0 (*((volatile unsigned int *)(0x7F00502C)))
#define UINTP0 (*((volatile unsigned int *)(0x7F005030)))
#define UINTSP0 (*((volatile unsigned int *)(0x7F005034)))
#define UINTM0 (*((volatile unsigned int *)(0x7F005038)))
#define ULCON1 (*((volatile unsigned int *)(0x7F005400)))
#define UCON1 (*((volatile unsigned int *)(0x7F005404)))
#define UFCON1 (*((volatile unsigned int *)(0x7F005408)))
#define UMCON1 (*((volatile unsigned int *)(0x7F00540C)))
#define UTRSTAT1 (*((volatile unsigned int *)(0x7F005410)))
#define UERSTAT1 (*((volatile unsigned int *)(0x7F005414)))
#define UFSTAT1 (*((volatile unsigned int *)(0x7F005418)))
#define UMSTAT1 (*((volatile unsigned int *)(0x7F00541C)))
#define UTXH1 (*((volatile unsigned int *)(0x7F005420)))
#define URXH1 (*((volatile unsigned int *)(0x7F005424)))
#define UBRDIV1 (*((volatile unsigned int *)(0x7F005428)))
#define UDIVSLOT1 (*((volatile unsigned int *)(0x7F00542C)))
#define UINTP1 (*((volatile unsigned int *)(0x7F005430)))
#define UINTSP1 (*((volatile unsigned int *)(0x7F005434)))
#define UINTM1 (*((volatile unsigned int *)(0x7F005438)))
#define ULCON2 (*((volatile unsigned int *)(0x7F005800)))
#define UCON2 (*((volatile unsigned int *)(0x7F005804)))
#define UFCON2 (*((volatile unsigned int *)(0x7F005808)))
#define UTRSTAT2 (*((volatile unsigned int *)(0x7F005810)))
#define UERSTAT2 (*((volatile unsigned int *)(0x7F005814)))
#define UFSTAT2 (*((volatile unsigned int *)(0x7F005818)))
#define UTXH2 (*((volatile unsigned int *)(0x7F005820)))
#define URXH2 (*((volatile unsigned int *)(0x7F005824)))
#define UBRDIV2 (*((volatile unsigned int *)(0x7F005828)))
#define UDIVSLOT2 (*((volatile unsigned int *)(0x7F00582C)))
#define INTP2 (*((volatile unsigned int *)(0x7F005830)))
#define UINTSP2 (*((volatile unsigned int *)(0x7F005834)))
#define UINTM2 (*((volatile unsigned int *)(0x7F005838)))
#define ULCON3 (*((volatile unsigned int *)(0x7F005C00)))
#define UCON3 (*((volatile unsigned int *)(0x7F005C04)))
#define UFCON3 (*((volatile unsigned int *)(0x7F005C08)))
#define UTRSTAT3 (*((volatile unsigned int *)(0x7F005C10)))
#define UERSTAT3 (*((volatile unsigned int *)(0x7F005C14)))
#define UFSTAT3 (*((volatile unsigned int *)(0x7F005C18)))
#define UTXH3 (*((volatile unsigned int *)(0x7F005C20)))
#define URXH3 (*((volatile unsigned int *)(0x7F005C24)))
#define UBRDIV3 (*((volatile unsigned int *)(0x7F005C28)))
#define UDIVSLOT3 (*((volatile unsigned int *)(0x7F005C2C)))
#define INTP3 (*((volatile unsigned int *)(0x7F005C30)))
#define UINTSP3 (*((volatile unsigned int *)(0x7F005C34)))
#define UINTM3 (*((volatile unsigned int *)(0x7F005C38)))

/*
    function declaration
*/
void uart_init(void);
char putchar(char ch);
char getchar (void);

#endif
