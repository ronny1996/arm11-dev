#ifndef __NAND_H__
#define __NAND_H__

typedef unsigned char u8_size_t;
typedef unsigned short u16_size_t;
typedef unsigned int u32_size_t;

#define __reg__(x) (*((volatile unsigned int *)(x)))

#define NAND_CTR_BASE (0x70200000)
#define NFCONF __reg__(NAND_CTR_BASE + 0x00)
#define NFCONT __reg__(NAND_CTR_BASE + 0x04)
#define NFCMMD __reg__(NAND_CTR_BASE + 0x08)
#define NFADDR __reg__(NAND_CTR_BASE + 0x0C)
#define NFDATA __reg__(NAND_CTR_BASE + 0x10)
#define NFMECCD0 __reg__(NAND_CTR_BASE + 0x14)
#define NFMECCD1 __reg__(NAND_CTR_BASE + 0x18)
#define NFSECCD __reg__(NAND_CTR_BASE + 0x1C)
#define NFSBLK __reg__(NAND_CTR_BASE + 0x20)
#define NFEBLK __reg__(NAND_CTR_BASE + 0x24)
#define NFSTAT __reg__(NAND_CTR_BASE + 0x28)
#define NFECCERR0 __reg__(NAND_CTR_BASE + 0x2C)
#define NFECCERR1 __reg__(NAND_CTR_BASE + 0x30)
#define NFMECC0 __reg__(NAND_CTR_BASE + 0x34)
#define NFMECC1 __reg__(NAND_CTR_BASE + 0x38)
#define NFSECC __reg__(NAND_CTR_BASE + 0x3C)
#define NFMLCBITPT __reg__(NAND_CTR_BASE + 0x40)
#define NF8ECCERR0 __reg__(NAND_CTR_BASE + 0x44)
#define NF8ECCERR1 __reg__(NAND_CTR_BASE + 0x48)
#define NF8ECCERR2 __reg__(NAND_CTR_BASE + 0x4C)
#define NFM8ECC0 __reg__(NAND_CTR_BASE + 0x50)
#define NFM8ECC1 __reg__(NAND_CTR_BASE + 0x54)
#define NFM8ECC2 __reg__(NAND_CTR_BASE + 0x58)
#define NFM8ECC3 __reg__(NAND_CTR_BASE + 0x5C)
#define NFMLC8BITPT0 __reg__(NAND_CTR_BASE + 0x60)
#define NFMLC8BITPT1 __reg__(NAND_CTR_BASE + 0x64)

int nand_init(void);
u8_size_t nand_read_data(u32_size_t addr, u32_size_t len, u32_size_t to);
u8_size_t nand_erase_block(u32_size_t addr);
u8_size_t nand_prog_page(u32_size_t addr, u32_size_t len, u32_size_t from);
u8_size_t nand_read_id(u8_size_t id[]);
#endif
