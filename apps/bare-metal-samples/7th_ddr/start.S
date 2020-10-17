.global _start
_start:
    /*peripheral port setup */
    ldr r0, =0x70000000                   
    orr r0, r0, #0x13
    mcr p15,0,r0,c15,c2,4 @ 256M(0x7000_0000 --- 0x7FFF_FFFF)

    /*disable watch dog */
    ldr r0, =0x7e004000
    mov r1, #0
    str r1, [r0]

    bl clock_init
    ldr sp, =8*1024
    bl sdram_init
    
    /* code relocation */
    adr r0,_start @ current address
    ldr r1,=_start @ link address
    ldr r2,=__bss_start @ bss
    cmp r0,r1
    beq clean_bss
relocation:
    ldr r3,[r0],#4
    str r3,[r1],#4
    cmp r1,r2 @ reach at bss_start (or code_ending)?
    bne relocation

/* clean bss */
/* global variable which is not init or initialize with 0 be stored in .bss */
clean_bss: 
    ldr r0,=__bss_start
    ldr r1,=__bss_end
    mov r3,#0
    cmp r0,r1
    beq clean_bss_ret
clean_loop:
    str r3,[r0],#4
    cmp r0,r1
    bne clean_loop
clean_bss_ret:
    ldr pc,=main