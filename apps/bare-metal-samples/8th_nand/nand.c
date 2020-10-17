#include "nand.h"

#define MEM_SYS_CFG (*((volatile unsigned int *)(0x7E00F120)))
#define PAGE_SZIE (4096) //byte
#define BLOCK_SIZE (512 * 1024) //byte

//private macro
#define ns2clk(ns) (ns / (1000000000 / HCLK) + 1)
#define clrbits(addr, bits, len) (addr & (~(((1 << len) - 1) << bits)))
#define setbits(addr, bits, len, val) (addr = (clrbits(addr, bits, len) | (val << bits)))

#if 0
#define __io_inline_type__
#else
#define __io_inline_type__ inline
#endif

//IO declare
void nand_select(void);
void nand_deselect(void);
void nand_cmd(u8_size_t cmd);
void nand_addr(u8_size_t addr);
void nand_prog_data(u8_size_t dat);
u8_size_t nand_get_data(void);
u8_size_t nand_is_ready(void);
void nand_wait_ready_block(void);
//public func
void nand_reset(void)
{
    nand_select();
    nand_cmd(0xFF);
    nand_wait_ready_block();
    nand_deselect();
}

int nand_init(void)
{
    //cs
    MEM_SYS_CFG &= ~(1 << 1);
#define TACLS 0
#define TWRPH0 2
#define TWRPH1 0 //set to maximn
    setbits(NFCONF, 30, 1, 0); // clk more than 66Mhz
    //setbits(NFCONF, 25, 1, 0);   // 512byte per ecc(4/8bit)
    //setbits(NFCONF, 23, 2, 0x1); // 8bit ecc
    setbits(NFCONF, 12, 3, TACLS);
    setbits(NFCONF, 8, 3, TWRPH0);
    setbits(NFCONF, 4, 3, TWRPH1);
    setbits(NFCONT, 0, 1, 1); // nand ctr en
    setbits(NFCONT, 16, 1, 0); // dis soft lock
    return 0;
}
u8_size_t nand_read_data(u32_size_t addr, u32_size_t len, u32_size_t to)
{
    u8_size_t *dst = (u8_size_t *)to;
    // TODO: check args
    nand_select(); //mww 0x70200004 0xc5
    while (len)
    {
        nand_cmd(0x00); //mww 0x70200008 0x00
        nand_addr((addr >> 0) & 0xff); /* a0~a7   */ //mww 0x7020000c 0x00
        nand_addr((addr >> 8) & 0x1f); /* a8~a12  */
        nand_addr((addr >> 13) & 0xff); /* a13~a20 . page, a20-plane*/
        nand_addr((addr >> 21) & 0xff); /* a19~a26 . block*/
        nand_addr((addr >> 29) & 0x07); /* a27~a31 . block*/
        nand_cmd(0x30);
        nand_wait_ready_block(); //0x70200028
        for (; len--; dst++)
        {
            *dst = nand_get_data(); //0x70200010
        }
    }
    nand_deselect();
    return 0;
}

u8_size_t nand_erase_block(u32_size_t addr) //block address A21~A31 (12bit = 4*1024) * 512k = 2048M
{
    u32_size_t page = addr / PAGE_SZIE;
    nand_select();
    nand_cmd(0x60);
    nand_addr(page & 0xff); //row
    nand_addr((page >> 8) & 0xff);
    nand_addr((page >> 16) & 0x07);
    nand_cmd(0xd0);
    nand_wait_ready_block();
    nand_deselect();
    return 0;
}

u8_size_t nand_prog_page(u32_size_t addr, u32_size_t len, u32_size_t from)
{
    u8_size_t *src = (u8_size_t *)from;
    nand_select();
    nand_cmd(0x80);
    nand_addr((addr >> 0) & 0xff); /* a0~a7   */ //0x7020000c
    nand_addr((addr >> 8) & 0x1f); /* a8~a12  */
    nand_addr((addr >> 13) & 0xff); /* a13~a20 . page, a20-plane*/
    nand_addr((addr >> 21) & 0xff); /* a19~a26 . block*/
    nand_addr((addr >> 29) & 0x07); /* a27~a31 . block*/
    for (; len--; src++)
    {
        nand_prog_data(*src);
    }
    nand_cmd(0x10);
    nand_wait_ready_block();
    nand_deselect();

    return 0;
}

u8_size_t nand_read_id(u8_size_t id[])
{
    nand_select();
    nand_cmd(0x90);
    nand_addr(0x00);
    id[0] = nand_get_data(); //0xec
    id[1] = nand_get_data(); //0xd5
    id[2] = nand_get_data(); //0x94
    id[3] = nand_get_data(); //0x29
    id[4] = nand_get_data(); //0x34
    id[5] = nand_get_data(); //0x41
    nand_deselect();
    return 0;
}

//IO & CTR
__io_inline_type__ void nand_select(void)
{
    setbits(NFCONT, 1, 1, 0);
}
__io_inline_type__ void nand_deselect(void)
{
    setbits(NFCONT, 1, 1, 1);
}
__io_inline_type__ void nand_cmd(u8_size_t cmd)
{
    NFCMMD = cmd;
}
__io_inline_type__ void nand_addr(u8_size_t addr)
{
    NFADDR = addr;
}
__io_inline_type__ void nand_prog_data(u8_size_t dat)
{
    NFDATA = dat;
}
__io_inline_type__ u8_size_t nand_get_data(void)
{
    return NFDATA;
}
__io_inline_type__ void nand_wait_ready_block(void)
{
    while (!(NFSTAT & 0x1))
    {
        /* code */
    }
}

#if 0
__io_inline_type__ u8_size_t nand_wait_ready_no_block(u32_size_t timeout)
{
    while (!(NFSTAT & 0x1))
    {
        if (!timeout--)return 1;
    }
    return 0;
}

#endif
