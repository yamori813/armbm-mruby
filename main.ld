ENTRY(_Start);
SECTIONS
{
 . = 0x10000; /*initial address*/
 .startup . : { startup.o(.text) }
 .text : { *(.text) }
 .data : { *(.data) }
 __bss_start = .;
 .bss : { *(.bss COMMON) }
 end = .;
 . = ALIGN(8);
 . = . + 0x200000; /* 1M of stack memory */
 stack_top = .;
}
