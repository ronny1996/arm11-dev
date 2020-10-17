CROSS_COMPILE:=/home/ronny/software/cross_tool_chain/arm-linux-gcc/bin/arm-linux-
LD:=${CROSS_COMPILE}ld
CC:=${CROSS_COMPILE}gcc
AR:=${CROSS_COMPILE}ar
OBJCOPY:=${CROSS_COMPILE}objcopy
OBJDUMP:=${CROSS_COMPILE}objdump
CPPFLAGS:=-nostdinc -nostdlib -fno-builtin 

led.bin : start.o led.o clock.o
	${LD} -Ttext 0 -o led.elf $^
	${OBJCOPY} -O binary led.elf $@
	${OBJDUMP}  -D led.elf > led.dis
	
%.o : %.S 
	${CC} -o $@ $< -c 
%.o : %.c 
	${CC}  -o $@ $< -c

clean:
	rm *.o led.elf led.bin led.dis 