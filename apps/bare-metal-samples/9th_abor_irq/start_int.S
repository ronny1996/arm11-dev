/*
    ARM have 7 mode
    general reg : r0-r15, state reg: cpsr spsr
    pc - r15, sp - r13, lr - r14

    system and user,
        : r0-15, cpsr, no spsr                                  copy cpsr to spsr_xx before enter other mode
    FIQ,            
        : r0-r7,  r8_fiq-r14_fiq,  r15, cpsr, spsr_fiq
    Supervisor(SVC),    power on
        : r0-r12, r13_svc-r14_svc, r15, cpsr, spsr_svc
    Abort,
        : r0-r12, r13_abt-r14_abt, r15, cpsr, spsr_abt
    IRQ, 
        : r0-r12, r13_irq-r14_irq, r15, cpsr, spsr_irq                
    Undefined,
        : r0-r12, r13_und-r14_und, r15, cpsr, spsr_und
    Secure monitor
        : r0-r12, r13_mon-r14_mon, r15, cpsr, spsr_mon


    cpsr include condition code, global irq/fiq en, mode bits, arm/thumb bit

interrupt program:
    1. set interrupt source
    2. write interrupt service function
        a. recognize what int   -- by using VICxADDRESS, VICxVECTADDRyy
        b. processing
        c. clear int before return
    3. turn on global int switch
*/

.global _start
_start:
    b reset                                 @ power on,             enter svc, ldr pc,0    
    ldr pc, =Undefined_instruction          @ ... always used as debug 
    ldr pc, _vector_swi                     @ swi - software int,   enter svc, ldr pc,0x8   ... always used as sys_recall
.word 0
    @ldr pc, _prefetch_abort
.word 0
    @ldr pc, _data_abort
.word 0
    @ldr pc, _not_used
    ldr pc, _irq                            @ occur interrupt,      enter irq mode, spsr_irq=cpsr, lr=pc+4, ldr pc,0x18
.word 0    
    @ldr pc, _fiq

_vector_swi:
    .word vector_swi
_irq:
    .word vector_irq:
vector_irq:
    ldr sp, =0x54000000
    sub lr, lr, #4
    stmdb sp!, {r0-r12,lr}

    bl do_irq

    ldmia sp!, {r0-r12,pc}^  
vector_swi:
    /* save field */
    ldr sp, =0x56000000
    stmdb sp!, {r0-r12,lr}
    /* process */
    mrs r0, cpsr
    ldr r1, =swi_str
    bl print_cpsr
    /* resume field */
    ldmia sp!, {r0-r12,pc}^                @ ^ denote that cpu resume spsr to cpsr


Undefined_instruction:
    ldr sp, =0x55000000
    stmdb sp!, {r0-r12,lr}
    mrs r0, cpsr
    ldr r1, =und_str 
    bl print_cpsr
    ldmia sp!, {r0,r12,pc}^
 

reset:
