;#<![CDATA[
;#
;######################################################################################
;#  This file defines the following flash functions
;#  
;#  massEraseTarget - Entirely erases the target.
;#                    The target should be left in an unsecured state.
;#
;#  isUnsecure - indicates if the target is secured in some fashion (read/write protected)
;#               Returns TCL_OK if NOT secured
;#
;#  initFlash - initialises the target for flash programing (if needed)
;#
;#  initTarget - initialises the target for general use
;#
;#  In addition the script may do any once-only initialisation such as setting global symbols
;#  when initially loaded into the TCL environment.
;#

;#####################################################################################
;#  History
;#
;#  V4.10.6.250 - Updated to include unsecure device
;#  V4.10.4     - Changed return code handling
;# 

;######################################################################################
;#
;#
proc loadSymbols {} {
   # LittleEndian format for writing numbers to memory
   setbytesex  littleEndian
   defaultMemorySpace X

   set ::HFM_FCLKD             x:0xF400
   set ::HFM_CR                x:0xF401
   set ::HFM_SECH              x:0xF403
   set ::HFM_SECL              x:0xF404
   set ::HFM_PROT              x:0xF410
   set ::HFM_USTAT             x:0xF413
   set ::HFM_CMD               x:0xF414
   set ::HFM_DATA              x:0xF418
   set ::HFM_OPT1              x:0xF41B
   set ::HFM_TSTSIG            x:0xF41D

   set ::HFM_SECH_SECSTAT_MASK     0x4000
   set ::HFM_SECH_SECSTAT_UNSECURE 0x0000
   
   set ::HFM_USTAT_CBEIF       0x80
   set ::HFM_USTAT_CCIF        0x40
   set ::HFM_USTAT_PVIOL       0x20
   set ::HFM_USTAT_ACCERR      0x10
   set ::HFM_USTAT_BLANK       0x04

   set ::HFM_CMD_ERASE_VER     0x05
   set ::HFM_CMD_CALC_SIG      0x06
   set ::HFM_CMD_WORD_PROG     0x20
   set ::HFM_CMD_SECTOR_ERASE  0x40
   set ::HFM_CMD_MASS_ERASE    0x41
   set ::HFM_CMD_CALC_IFR_SIG  0x66

   set ::DSC_PRDIV8            0x40
     
   set ::BUS_FREQUENCY         4000
   set ::JTAG_UNLOCK_CMD       0x08
   
   set ::SIM_MSHID             x:0xF146
   set ::SIM_LSHID             x:0xF147
   
   set ::PROGRAMMING_RC_OK                         0
   set ::BDM_RC_ILLEGAL_COMMAND                    4
   set ::PROGRAMMING_RC_ERROR_SECURED              114
   set ::PROGRAMMING_RC_ERROR_FAILED_FLASH_COMMAND 115
   set ::PROGRAMMING_RC_ERROR_NO_VALID_FCDIV_VALUE 116
   
   return
}

;######################################################################################
;#
;#
proc initTarget { args } {
   puts "initTarget {}"
   return
}

;######################################################################################
;#
;#  busFrequency - Target bus frequency in kHz
;#
proc initFlash { busFrequency } {
   puts "initFlash {}"
   
   set ::BUS_FREQUENCY $busFrequency

   ;# Set up Flash
   set cfmclkd [calculateFlashDivider $busFrequency]
   ww $::HFM_FCLKD $cfmclkd   ;# Flash divider
   ww $::HFM_PROT  0x0000     ;# unprotect Flash
   
   return
}

;######################################################################################
;#
;#  busFrequency - Target bus busFrequency in kHz
;#
proc calculateFlashDivider { busFrequency } {
;# NOTES:
;# According to data sheets the Flash uses the Oscillator clock for timing but 
;# it is also influenced by the bus period.
;#
;# This code assumes that busFrequency = sysclock = oscclk/2
;#
   ;#  puts "calculateFlashDivider {}"
   if { [expr $busFrequency < 1000] } {
      puts "Clock too low for flash programming"
      error $::PROGRAMMING_RC_ERROR_NO_VALID_FCDIV_VALUE
   }
   set oscFrequency [expr 2*$busFrequency]
   if { [expr $oscFrequency > 12800] } {
      set cfmclkd $::DSC_PRDIV8 
      set inFrequency [expr $oscFrequency/8]
   } else {
      set cfmclkd 0
      set inFrequency $oscFrequency 
   }
   set minPeriod [expr (1/200.0 + 1/(4.0*$busFrequency))]
   set cfmclkd [expr $cfmclkd + round(floor(($inFrequency*$minPeriod)))] 
   set flashClk [expr $inFrequency / (($cfmclkd&0x3F)+1)]
   puts [ format "inFrequency = %d kHz cfmclkd = 0x%02X, flashClk = %d kHz" $inFrequency $cfmclkd $flashClk ]
   if { [expr ($flashClk<150)] } {
      puts "Not possible to find suitable flash clock divider"
      error $::PROGRAMMING_RC_ERROR_NO_VALID_FCDIV_VALUE
   }      
   return $cfmclkd
}

;######################################################################################
;#  Target is erased & unsecured
proc massEraseTarget { } {

   puts "massEraseTarget{}"
   
   catch { reset s h }
   catch { connect }

   ;# Calculate clock divider using reset assumed value (4MHz)
   set cfmclkd [calculateFlashDivider $::BUS_FREQUENCY]
   
   ;#puts "jtag-idcode"
   ;#jtag-idcode

   puts "jtag-reset"
   jtag-reset

   puts "Lockout Recovery CMD to instruction register"
   puts "jtag-shift-ir"
         jtag-shift-ir
   puts "jtag-shift D 8 $::JTAG_UNLOCK_CMD"
         jtag-shift D 8 $::JTAG_UNLOCK_CMD
   
   puts "Clk Divider to data register"
   puts "jtag-shift R 16 0 $cfmclkd"
         jtag-shift R 16 0 $cfmclkd
   
   puts "Erase Delay"

   after 2000

   puts "Erase Complete"
   
   catch { reset sh }
   
   return [ isUnsecure ] 
}

;######################################################################################
;#
proc isUnsecure { } {
   puts "isUnsecure{} - Checking if unsecured"

   ;# Check HFM_SECH
   ;# This is unreliable as a secured device reads as zero anyway!
   ;# set securityValueH [rw $::HFM_SECH]
   ;# puts [format "isUnsecure{} - HFM_SECH = 0x%08X" $securityValueH ]
   ;# if [ expr ( ( $securityValueH & $::HFM_SECH_SECSTAT_MASK ) != $::HFM_SECH_SECSTAT_UNSECURE ) ] {
   ;#    puts "isUnsecure{} - Target is secured!"
   ;#    return $::PROGRAMMING_RC_ERROR_SECURED
   ;# }
   
   ;# Check if the idcode can be read
   set jtag_idcode [ jtag-idcode ]
   puts [ format "isUnsecure{} - jtag_idcode =0x%08X" $jtag_idcode ]
   catch { connect }
   
   set idcodeH [rw $::SIM_MSHID]
   set idcodeL [rw $::SIM_LSHID]
   set idcode  [ expr ($idcodeH<<16) + $idcodeL ]
   puts [format "isUnsecure{} - idcode =0x%08X" $idcode ]
   if [ expr ( $jtag_idcode != $idcode ) ] {
      puts "isUnsecure{} - Target is secured!"
      return $::PROGRAMMING_RC_ERROR_SECURED
   }
   puts "isUnsecure{} - Target is unsecured"
   return $::PROGRAMMING_RC_OK
}

proc try {} {
   openbdm
   settarget DSC
   catch { reset s h }
   catch { connect }
   catch { isUnsecure }   
   catch { massEraseTarget }
   closebdm
}

;######################################################################################
;# Actions on initial load
;#
loadSymbols

;#]]>
