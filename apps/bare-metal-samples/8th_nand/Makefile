CROSS_COMPILE:=/home/ronny/software/cross_tool_chain/arm-linux-gcc/bin/arm-linux-
LD:=${CROSS_COMPILE}ld
CC:=${CROSS_COMPILE}gcc
AR:=${CROSS_COMPILE}ar
OBJCOPY:=${CROSS_COMPILE}objcopy
OBJDUMP:=${CROSS_COMPILE}objdump

INCLUDEDIR := $(shell pwd)/lib/inc
CFLAGS :=  -Wall -Os -fno-builtin 
CPPFLAGS := -nostdinc -I$(INCLUDEDIR)

export 	CC AR LD OBJCOPY OBJDUMP INCLUDEDIR CFLAGS CPPFLAGS 

objs := start.o main.o uart.o clock.o sdram.o nand.o lib/libc.a
target := uart

.PHONY : all
$(target).bin : $(objs)
	${LD} -Tuart.lds -o $(target).elf $^
	${OBJCOPY} -O binary -S $(target).elf $@
	${OBJDUMP} -D $(target).elf > $(target).dis
	@echo '[generate .bin]'  
	
.PHONY : lib/libc.a
lib/libc.a:
	@cd lib; make; cd ..

%.o:%.c
	${CC} $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

%.o:%.S
	${CC} $(CPPFLAGS) $(CFLAGS) -c -o $@ $< 

Image: $(target).bin 
	@dd if=$(target).bin of=Image bs=2048 count=1 skip=0 seek=0 conv=sync #0-2k
	@dd if=$(target).bin of=Image bs=2048 count=1 skip=1 seek=2 conv=sync #4k-6k
	@dd if=$(target).bin of=Image bs=2048 count=1 skip=2 seek=4 conv=sync #8k-10k
	@dd if=$(target).bin of=Image bs=2048 count=1 skip=3 seek=6 conv=sync #12k-14k
	@dd if=/dev/zero of=Image bs=2048 count=1 seek=7 conv=sync  #12k-16k  
	@echo '[generate Image]'

.PHONY : clean				# in case of that exits a file name clean
clean: 
	make  clean -C lib
	rm -f $(target).bin $(target).elf $(target).dis *.o Image


