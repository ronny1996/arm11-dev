CROSS_COMPILE:=/home/ronny/software/cross_tool_chain/arm-linux-gcc/bin/arm-linux-
LD:=${CROSS_COMPILE}ld
CC:=${CROSS_COMPILE}gcc
AR:=${CROSS_COMPILE}ar
OBJCOPY:=${CROSS_COMPILE}objcopy
OBJDUMP:=${CROSS_COMPILE}objdump
CPPFLAGS:=-nostdinc -nostdlib -fno-builtin 
#WARNING:=-Wall

uart.bin : start.o main.o clock.o uart.o
	${LD} -Ttext 0 -o uart.elf $^
	${OBJCOPY} -O binary uart.elf $@
	${OBJDUMP}  -D uart.elf > uart.dis
	
%.o : %.S 
	${CC} ${WARNING} -o $@ $< -c 
%.o : %.c 
	${CC} ${CPPFLAGS} ${WARNING} -o $@ $< -c

clean:
	rm *.o uart.elf uart.bin uart.dis 