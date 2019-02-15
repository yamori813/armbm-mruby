.globl _bss_start
_bss_start:
	.word __bss_start

.globl _bss_end
_bss_end:
	.word end

.global _Reset
_Reset:
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

