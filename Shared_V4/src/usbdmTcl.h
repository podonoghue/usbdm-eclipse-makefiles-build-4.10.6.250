/*
 * usbdmTcl.h
 *
 *  Created on: 06/04/2011
 *      Author: podonoghue
 */

#ifndef USBDMTCL_H_
#define USBDMTCL_H_

//==================================================
#if defined __cplusplus
#define EXTERN_C  extern "C"
#else
#define EXTERN_C
#endif

#if defined(_WIN32) && !defined (WINAPI)
   #define WINAPI __attribute__((__stdcall__))
#endif

#if defined(_WIN32) && !defined(DLL_LOCAL)
   // Functions exported from a library
   #define DLL_EXPORT WINAPI __declspec(dllexport)

   // Functions imported from a library
   #define DLL_IMPORT WINAPI __declspec(dllimport)

   // Functions local to a library
   #define DLL_LOCAL
#endif

#if !defined(DLL_LOCAL)
   // Functions exported from a library
   #define DLL_EXPORT __attribute__ ((visibility ("default")))
   // Functions imported from a library
   #define DLL_IMPORT __attribute__ ((visibility ("default")))

   // Functions local to a library
   #define DLL_LOCAL  __attribute__ ((visibility ("hidden")))
#endif

#ifdef USBDM_TCL_DLL_EXPORTS
   //! These definitions are used when USBDM_TCL_API is being exported (creating DLL)
   #define TCL_API     EXTERN_C DLL_EXPORT
   #define TCL_LOCAL              DLL_LOCAL
#else
   //! These definitions are used when USBDM_TCL_API is being imported (linking against DLL)
   #define TCL_API     EXTERN_C DLL_IMPORT
   #define TCL_LOCAL              DLL_LOCAL
#endif

//==================================================

#if defined __cplusplus
    extern "C" {
#endif

// Opaque type
typedef void UsbdmTclInterp;

TCL_API UsbdmTclInterp *createTclInterpreter(TargetType_t target, FILE *fp);
TCL_API void freeTclInterpreter(UsbdmTclInterp *interp);
TCL_API USBDM_ErrorCode evalTclScript(UsbdmTclInterp *interp, const char *script);
TCL_API const char *getTclResult(UsbdmTclInterp *interp);

#if defined __cplusplus
    }
#endif

#endif /* USBDMTCL_H_ */
