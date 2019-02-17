# https://github.com/dwelch67/raspberrypi/tree/master/blinker05


.global _Start
_Start:
ldr pc,reset_handler
ldr pc,undefined_handler
ldr pc,swi_handler
ldr pc,prefetch_handler
ldr pc,data_handler
ldr pc,unused_handler
ldr pc,irq_handler
ldr pc,fiq_handler
reset_handler:      .word reset
undefined_handler:  .word hang
swi_handler:        .word hang
prefetch_handler:   .word hang
data_handler:       .word hang
unused_handler:     .word hang
irq_handler:        .word irq
fiq_handler:        .word hang

.globl _bss_start
_bss_start:
	.word __bss_start

.globl _bss_end
_bss_end:
	.word end

.globl IRQ_STACK_START
IRQ_STACK_START:
        .word   0x0badc0de

reset:
mov r0,#0x10000
mov r1,#0x0000
ldmia r0!,{r2-r9}
stmia r1!,{r2-r9}
ldmia r0!,{r2-r9}
stmia r1!,{r2-r9}

 LDR sp, =stack_top

 ldr     r0, _bss_start
 ldr     r1, _bss_end
 mov     r2, #0x00000000
clbss_l:str     r2, [r0]
 add     r0, r0, #4
 cmp     r0, r1
 ble     clbss_l

 BL main
 B .

.globl enable_irq
enable_irq:
	mrs r0,cpsr
	bic r0,r0,#0x80
	msr cpsr_c,r0
	bx lr

hang: b hang

irq:
        ldr     sp, IRQ_STACK_START
        sub     sp, sp, #72
        stmia   sp, {r0 - r12}
        add     r8, sp, #60
        stmdb   r8, {sp, lr}^
        str     lr, [r8, #0] 
        mrs     r6, spsr
        str     r6, [r8, #4]
        str     r0, [r8, #8]
        mov     r0, sp

	bl irqch

        ldmia   sp, {r0 - lr}^
        mov     r0, r0
        ldr     lr, [sp, #60]
        add     sp, sp, #72
        subs    pc, lr, #4
	
