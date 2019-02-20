ENTRY(_Start);
SECTIONS
{
 . = 0x10000; /*initial address*/
 .startup . : { startup.o(.text) }
 .text : { *(.text) }
 .data : { *(.data) }
 __bss_start = .;
 .bss : { *(.bss COMMON) }
 _end = .;
}
