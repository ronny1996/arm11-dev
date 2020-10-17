CROSS_COMPILE:=/home/ronny/software/cross_tool_chain/arm-linux-gcc/bin/arm-linux-
LD:=${CROSS_COMPILE}ld
CC:=${CROSS_COMPILE}gcc
AR:=${CROSS_COMPILE}ar
OBJCOPY:=${CROSS_COMPILE}objcopy
OBJDUMP:=${CROSS_COMPILE}objdump
CPPFLAGS:=-nostdinc -nostdlib -fno-builtin 

led.bin : start.o led.o
	${LD} -Ttext 0 -o led.elf start.o led.o
	${OBJCOPY} -O binary led.elf led.bin
	${OBJDUMP} -D led.elf > led.dis
start.o : start.S 
	${CC} -o start.o start.S -c
led.o : led.c
	${CC} -o led.o led.c -c

clean:
	rm *.o led.elf led.bin led.dis 