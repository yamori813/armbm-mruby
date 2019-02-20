# refered
# https://github.com/dwelch67/raspberrypi/
# https://www.stefannaumann.de/informatik/mmu-on-raspberry-pi.html

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
	.word _end

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

 mov sp,#0x700000

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
	
.globl PUT32
PUT32:
	str r1,[r0]
	bx lr

.globl GET32
GET32:
	ldr r0,[r0]
	bx lr

.globl dummy
dummy:
	bx lr

.globl start_l1cache
start_l1cache:
	mov r0, #0
	mcr p15, 0, r0, c7, c7, 0 ;@ invalidate caches
	mcr p15, 0, r0, c8, c7, 0 ;@ invalidate tlb
	mrc p15, 0, r0, c1, c0, 0
	orr r0,r0,#0x1000 ;@ instruction
	orr r0,r0,#0x0004 ;@ data
	mcr p15, 0, r0, c1, c0, 0
	bx lr

.globl stop_l1cache
stop_l1cache:
	mrc p15, 0, r0, c1, c0, 0
	bic r0,r0,#0x1000 ;@ instruction
	bic r0,r0,#0x0004 ;@ data
	mcr p15, 0, r0, c1, c0, 0
	bx lr

.globl start_mmu
start_mmu:
	mov r2,#0
	mcr p15,0,r2,c7,c7,0 ;@ invalidate caches
	mcr p15,0,r2,c8,c7,0 ;@ invalidate tlb
	mcr p15,0,r2,c7,c10,4 ;@ DSB ??

	mvn r2,#0
	bic r2,#0xC
	mcr p15,0,r2,c3,c0,0 ;@ domain

	mcr p15,0,r0,c2,c0,0 ;@ tlb base
	mcr p15,0,r0,c2,c0,1 ;@ tlb base

	mrc p15,0,r2,c1,c0,0
	orr r2,r2,r1
	mcr p15,0,r2,c1,c0,0

	bx lr

.globl stop_mmu
stop_mmu:
	mrc p15,0,r2,c1,c0,0
	bic r2,#0x1000
	bic r2,#0x0004
	bic r2,#0x0001
	mcr p15,0,r2,c1,c0,0
	bx lr

.globl invalidate_tlbs
invalidate_tlbs:
	mov r2,#0
	mcr p15,0,r2,c8,c7,0  ;@ invalidate tlb
	mcr p15,0,r2,c7,c10,4 ;@ DSB ??
	bx lr

.globl enableInterrupt
enableInterrupt:
	mrs	r0, cpsr
	bic	r1, r0, #0xC0
	msr	cpsr_c, r1
	mov	pc, lr

.globl disableInterrupt
disableInterrupt:
	mrs	r0, cpsr
	orr	r1, r0, #0xC0
	msr	cpsr_c, r1
	mov	pc, lr
