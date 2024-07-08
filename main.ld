ENTRY(_Start);
SECTIONS
{
 . = LOADADDR; /*initial address*/
 .startup . : { startup.o(.text) }
 .text : { *(.text) }
 .data : { *(.data) }
 __bss_start = .;
 .bss : { *(.bss COMMON) }
 _end = .;
}
