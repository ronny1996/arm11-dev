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

objs := start.o main.o uart.o clock.o sdram.o 

uart.bin: $(objs)
	${LD} -Tuart.lds -o uart.elf $^
	${OBJCOPY} -O binary -S uart.elf $@
	${OBJDUMP} -D uart.elf > uart.dis
	@echo 'generate .bin'  
	
%.o:%.c
	${CC} $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

%.o:%.S
	${CC} $(CPPFLAGS) $(CFLAGS) -c -o $@ $< 

clean: 
	rm -f uart.bin uart.elf uart.dis *.o
	