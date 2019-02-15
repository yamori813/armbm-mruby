ENTRY(_Reset)
SECTIONS
{
 . = 0x100000; /*initial address*/
 .startup . : { startup.o(.text) }
 .text : { *(.text) }
 .data : { *(.data) }
 .bss : { *(.bss COMMON) }
 end = .;
 . = ALIGN(8);
 . = . + 0x200000; /* 1M of stack memory */
 stack_top = .;
}
