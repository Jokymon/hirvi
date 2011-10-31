/*OUTPUT_FORMAT("binary")*/
ENTRY(start)
SECTIONS
{
  .text  0xFF800000 : {
    *(.text)
  }
  .data  : {
    *(.data)
  }
  .bss  :
  { 					
    *(.bss)
  }
}
