/* ARMLtd_GCC-rom-mk-sramu.ld
 * 
 * Kinetis version with SRAM_U allocation and bitband
 *
 * Linker script based on example scripts provided with ARM Ltd GCC
 *
 * It references the following symbols, which must be defined in code:
 * 
 *      Reset_Handler : Entry of reset handler
 * 
 * 
 * It defines the following symbols, which code can use without definition:
 *      __exidx_start
 *      __exidx_end
 *      __etext
 *      __data_start__
 *      __preinit_array_start
 *      __preinit_array_end
 *      __init_array_start
 *      __init_array_end
 *      __fini_array_start
 *      __fini_array_end
 *      __data_end__
 *      __bss_start__
 *      __bss_end__
 *      __end__
 *      end
 *      __HeapBottom
 *      __HeapLimit
 *      __StackLimit
 *      __StackTop
 *      __stack
 */
 
OUTPUT_FORMAT ("elf32-littlearm", "elf32-bigarm", "elf32-littlearm")
SEARCH_DIR(.)

/* Include external memory map defining ram and Flash memory etc */
INCLUDE "MemoryMap-$(targetDeviceName).ld"

ENTRY(Reset_Handler)

PROVIDE(__HardReset = Reset_Handler);

/* Needed for -nostartfiles linker option call main directly */
PROVIDE(_start = main);

SECTIONS
{
   .text :
   {
      __flash_start = .;

      /* Vector table */
      KEEP(*(.interrupt_vectors))
      /* Make sure we pulled in at least a reset vector.  */
      ASSERT (. != __flash_start, "No interrupt vector");

      /* Emit a Bootloader configuration if present */
      . = __flash_start + 0x3C0;
      KEEP(*(.bootloader_configuration))

      /* Emit a Security field */
      . = __flash_start + 0x400;
      KEEP(*(.security_information))
      ASSERT (. == __flash_start + 0x410, "No security information");

      *(.text*)

      KEEP(*(.init))
      KEEP(*(.fini))

      /* .ctors */
      *crtbegin.o(.ctors)
      *crtbegin?.o(.ctors)
      *(EXCLUDE_FILE(*crtend?.o *crtend.o) .ctors)
      *(SORT(.ctors.*))
      *(.ctors)

      /* .dtors */
      *crtbegin.o(.dtors)
      *crtbegin?.o(.dtors)
      *(EXCLUDE_FILE(*crtend?.o *crtend.o) .dtors)
      *(SORT(.dtors.*))
      *(.dtors)

      . = ALIGN(4);
      /* preinit data */
      PROVIDE_HIDDEN (__preinit_array_start = .);
      KEEP(*(.preinit_array))
      PROVIDE_HIDDEN (__preinit_array_end = .);

      . = ALIGN(4);
      /* init data */
      PROVIDE_HIDDEN (__init_array_start = .);
      KEEP(*(SORT(.init_array.*)))
      KEEP(*(.init_array))
      PROVIDE_HIDDEN (__init_array_end = .);

      . = ALIGN(4);
      /* finit data */
      PROVIDE_HIDDEN (__fini_array_start = .);
      KEEP(*(SORT(.fini_array.*)))
      KEEP(*(.fini_array))
      PROVIDE_HIDDEN (__fini_array_end = .);

      KEEP(*(.jcr*))

      *(.rodata*)

      KEEP(*(.eh_frame*))
    } > rom

   .ARM.extab : 
   {
      *(.ARM.extab* .gnu.linkonce.armextab.*)
   } > rom

   __exidx_start = .;
   .ARM.exidx :
   {
      *(.ARM.exidx* .gnu.linkonce.armexidx.*)
   } > rom
   __exidx_end = .;

   __etext = .;

   .data : AT (__etext)
   {
      __data_start__ = .;
      *(vtable)
      *(.data*)

      . = ALIGN(4);
      /* All data end */
      __data_end__ = .;
   } > ram

   .bss :
   {
      . = ALIGN(4);
      __bss_start__ = .;
      *(.bss*)
      *(COMMON)
      . = ALIGN(4);
      __bss_end__ = .;
   } > ram
    
   /* Minimum HEAP - from top of BSS */
   .heap :
   {
      . = ALIGN(4);
      PROVIDE ( end = . );
      PROVIDE ( __end__ = . );
      PROVIDE ( _end = . );
      __HeapBottom = .;
      __heap_addr = .;
      . = . + __heap_size;
   } > ram

   /* STACK space - between HEAP and end of RAM (or bitband_bytes) */
   PROVIDE ( __sram_u_size = 0 );
   .stack :
   {
      /* Make sure location doesn't move backwards as causes cryptic messages */
      . = MAX( ., ABSOLUTE(ORIGIN(ram) + LENGTH(ram) - __stack_size - __sram_u_size - 3));
      . = ALIGN(4);
      __HeapLimit = .;
      __StackLimit = .;
      . = . + __stack_size;
      __StackTop = .;
   } > ram

   /* 
    * SRAM_U region
    *
    * This area is partitioned from the top of SRAM
    *
    * Each bit in this region maps to a word in the .bitband region (if present)
    * This region is also accessible to BME (if present and supports RAM access) 
    */
   .sram_u (NOLOAD) :
   {
      *(.sram_u)
   } > ram

   /*
    * Bitband region
    *
    * Each word in this region maps to a bit in the .bitband_byte region 
    */
   .bitband (NOLOAD) :
   {
      /* Allocate variables from top of region */
      . = ORIGIN(bitband) + ((ORIGIN(ram) + LENGTH(ram) - __sram_u_size) & 0xFFFFFF) * 32;
      *(.bitband)
   } > bitband
    
  PROVIDE(__stack = __StackTop);
  PROVIDE(__cs3_stack = __StackTop);
  
  /*
   RAM Memory map                                            Example
  +----------------------+ __data_start__                    0x1FFFFF00
  | DATA                 |
  |                      |
  +----------------------+ __data_end__ = __bss_start__      0x1FFFFF68
  | BSS                  |
  |                      |
  +----------------------+ __bss_end__ = __HeapBottom        0x1FFFFF84
  | Heap                 |
  | (__heap_size)        |  (minimum heap)                   (size=0x120)
  +----------------------+                                   0x200000A4
  |//////////////////////|
  +----------------------+ __HeapLimit = __StackLimit        0x200001fc
  | Stack                |
  | (__stack_size)       |                                   (size=0x100)
  +----------------------+ __StackTop                        0x200002ff
  | Bitband/BME (sram_u) |
  | (__sram_u_size)      |                                   (size=1)
  +----------------------+                                   0x20000300
  
  */
}
