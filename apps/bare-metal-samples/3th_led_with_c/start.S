.global _start
_start:
    /*peripheral port setup */
    ldr r0, =0x70000000 @ fake insruction
    orr r0, r0, #0x13
    mcr p15,0,r0,c15,c2,4 @ 256M(0x7000_0000 --- 0x7FFF_FFFF)

    /*disable watch dog */
    ldr r0, =0x7e004000
    mov r1, #0
    str r1, [r0]
    /*setup sp (c need), there are two methods, nand-boot and sd-boot.*/
    @ only for nand boot
    @ ldr sp, =8*1024 
    @ for all, change .lds 
    ldr sp, =0x0c002000 
    bl main
halt:
    b halt