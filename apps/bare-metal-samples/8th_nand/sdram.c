#include "sdram.h"

#define MEM_SYS_CFG (*((volatile unsigned int *)(0x7E00F120)))

#define HCLK 133000000

//private macro
#define ns2clk(ns) (ns / (1000000000 / HCLK) + 1)
#define clrbits(addr, bits, len) (addr & (~(((1 << len) - 1) << bits)))
#define setbits(addr, bits, len, val) (addr = (clrbits(addr, bits, len) | (val << bits)))

void sdram_init(void)
{
    // DRAM controller initialization
    P1MEMCCMD = 0x4; //configure dram controller
    //write timing parameter
    P1REFRESH = ns2clk(7800);
    P1CASLAT = 0x3 << 1;
    P1T_DQSS = 0x1;
    P1T_MRD = 0x2;
    P1T_RAS = ns2clk(45);
    P1T_RC = ns2clk(68);
    P1T_RCD = ns2clk(23) | ((ns2clk(23) - 3) << 3);
    P1T_RFC = ns2clk(80) | ((ns2clk(80) - 3) << 5);
    P1T_RP = ns2clk(23) | ((ns2clk(23) - 3) << 3);
    P1T_RRD = ns2clk(15);
    P1T_WR = ns2clk(15);
    P1T_WTR = 7; //not find
    P1T_XP = 1;
    P1T_XSR = ns2clk(120);
    P1T_ESR = ns2clk(120); //not find
                           //memory configure
    setbits(P1MEMCFG, 0, 3, 0x2);
    setbits(P1MEMCFG, 3, 3, 0x3);
    setbits(P1MEMCFG, 6, 1, 0x0);
    setbits(P1MEMCFG, 15, 3, 0x2);

    setbits(P1MEMCFG2, 0, 4, 0x5);
    setbits(P1MEMCFG2, 6, 2, 0x1);
    setbits(P1MEMCFG2, 8, 3, 0x3);
    setbits(P1MEMCFG2, 11, 2, 0x1);
    //P1MEMCFG    = (0x2<<0) | (0x3<<3) | (0x0<<6) | (0x2<<15);   //col 10, row 14, ap 10, burst 4 (support 2 4 8 16)
    //P1MEMCFG2   = (0x5<<0) | (0x1<<6) | (0x3<<8) | (0x1<<11);   //32bit
    P1_chip_0_cfg = 0x1 << 16; //bank-row-column

    //memory initialization sequence

    P1DIRECTCMD = (0x3 << 18); // makes DRAM Controller issue 'NOP' memory command.
    P1DIRECTCMD = (0x0 << 18); // makes DRAM Controller issue 'PrechargeAll' memory command.
    P1DIRECTCMD = (0x1 << 18); // makes DRAM Controller issue 'Autorefresh' memory command.
    P1DIRECTCMD = (0x1 << 18);
    P1DIRECTCMD = (0x2 << 18) | (0x2 << 16); // makes DRAM Controller issue 'EMRS' memory command.
    P1DIRECTCMD = (0x2 << 18) | (0x32 << 0); // makes DRAM Controller issue 'MRS' memory command.

    MEM_SYS_CFG = 0x0;
    P1MEMCCMD = 0x0; //go

    while (!((P1MEMSTAT & 0x3) == 0x1)); // ready?
}