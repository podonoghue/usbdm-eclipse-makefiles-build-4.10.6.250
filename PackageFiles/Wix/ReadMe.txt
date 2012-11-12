USBDM V4.10
=========================
V4.10.2 (November 2012) -
   - Added device driver installation (V1.0.0)
   - Fixed BDM doing reset when setting target even if already powered.
     This was interfering with doing a 'gentle' connection to a running target.
   - Fixed DSC bug that prevented ONCE register writes to executing target
   - Kinetis target connection modified to allow gentle connections  
V4.10.2 (October 2012) -
This is intended as a interim release to support Codewarrior 10.3 Beta.
It has not been extensively tested.
Use only if you wish to experiment with CW10.3!
   - Updated installer for Codewarrior 10.3 Beta
   - Kinetis & CFV1 targets now correctly support RAM only targets (again)
   - Changed to shared DLLs build for wxWidgets
   - Support added for Kinetis KLxx devices
   - Updated libusbx version (& changed to static linkage)
   Bug Fixes
     - Fixes for an output glitch on USBDM_JMxx_CLD & CLC. (firmware)
     - Kinetis-SWD reports memory read/write errors on failing access
       (not following access) (firmware) 
   
V4.10.0 (September 2012) -
   - Improved ARM-JTAG interface speed.
   - Added support for ARM-SWD interfaces (requires different hardware). 
     ARM-SWD is much faster than ARM-JTAG. For reference, programming a
     file to flash using Codewarrior 10.2:
                      Readback     Without
                      verify       readback
      - OSJTAG        1m 20s         53s      
      - USBDM-JTAG       47s         23s
      - USBDM-SWD        21s         17s
   - ARM interfaces (JTAG & SWD) are now provided by USBDM interface DLL. This
     means that the ARM API is now uniform with the RS08, HCS08, HCS12 and 
     CFV1 interfaces. A compatibility DLL is provided for legacy use.
   - Simple ARM-SWD interface hardware designs are provided.
   - Bug fixes
      - Alignment error in programming code for some S12 targets
      - Corrected load addresses for ELF files for HCS08/HCS12
      - Added/corrected support for MCF51AG128
