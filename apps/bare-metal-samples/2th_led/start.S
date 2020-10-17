.global _start
_start:
    /*peripheral port setup */
    ldr r0, =0x70000000                   @ fake insruction
    orr r0, r0, #0x13
    mcr p15,0,r0,c15,c2,4               @ 256M(0x7000_0000 --- 0x7FFF_FFFF)

    /*disable watch dog */
    ldr r0, =0x7e004000
    mov r1, #0
    str r1, [r0]
   
    /*config GPM3 */
    ldr r1, =0x7f008820                     @ GPMCON
    ldr r0, =0x1111 
    str r0, [r1]

    ldr r1, =0x7f008824                    @ GPMDAT
    mov r0, #0

loop:
    str r0,[r1]
    add r0, r0, #1
    cmp r0, #16
    bl delay
    b loop
delay:
    mov r2, #0x10000
delay_loop:
    sub r2, r2, #1
    cmp r2, #0
    bne delay_loop
    mov pc, lr
halt:
    b halt