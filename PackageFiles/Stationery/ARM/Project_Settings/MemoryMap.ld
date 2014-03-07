
/* ---- <<< Use Configuration Wizard in Context Menu >>> ---- */

/* <o> Stack Size <0x0-$(linkerRamSize)> */
__stack_size = $(linkerStackSize);   /* required amount of stack */

/* <o> Minimum Heap Size <0x0-$(linkerRamSize)> */
/* <i> Actual heap may be larger as it fills all unused RAM */
__heap_size  = $(linkerHeapSize);   /* required amount of heap  */

/* <h>RAM region   <o0>  start <o1> length </h> */
/* <h>Flash region <o2>  start <o3> length </h> */
$(linkerInformation)

