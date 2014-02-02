
/* ---- <<< Use Configuration Wizard in Context Menu >>> ---- */

/* <o> Stack Size <0x0-$(linkerRamSize)> */
__stack_size = $(linkerStackSize);   /* required amount of stack */

/* <o> Heap Size <0x0-$(linkerRamSize)> */
__heap_size  = $(linkerHeapSize);   /* required amount of heap  */

$(linkerInformation)

