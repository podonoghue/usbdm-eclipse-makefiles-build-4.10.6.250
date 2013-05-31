/*
 * wxPlugin.h
 *
 *  Created on: 28/04/2011
 *      Author: PODonoghue
 */
#ifndef WXPLUGIN_H_
#define WXPLUGIN_H_

//==================================================
#if defined __cplusplus
#define EXTERN_C  extern "C"
#else
#define EXTERN_C
#endif

//=========================================================
// Linking against wxPlugin or building DLL

#if defined(_WIN32) && !defined (WINAPI)
   #define WINAPI __attribute__((__stdcall__))
#endif

#if defined(_WIN32)
   // Functions exported from a library
   #define DLL_EXPORT WINAPI __declspec(dllexport)

   // Functions imported from a library
   #define DLL_IMPORT WINAPI __declspec(dllimport)

   // Functions local to a library
   #define DLL_LOCAL
#else
   // Functions exported from a library
   #define DLL_EXPORT __attribute__ ((visibility ("default")))

   // Functions imported from a library
   #define DLL_IMPORT __attribute__ ((visibility ("default")))

   // Functions local to a library
   #define DLL_LOCAL  __attribute__ ((visibility ("hidden")))
#endif

#ifdef WXPLUGIN_DLL_EXPORTS
   //! These definitions are used when USBDM_API is being exported (creating DLL)
   #define WXPLUGIN_API      EXTERN_C DLL_EXPORT
   #define WXPLUGIN_LOCAL             DLL_LOCAL
#else
   //! These definitions are used when USBDM_API is being imported (linking against DLL)
   #define WXPLUGIN_API      EXTERN_C DLL_IMPORT
#endif

//==================================================
#include <wx/defs.h>

#if defined __cplusplus
   extern "C" {
#endif

// Opaque type
typedef void WindowHandle;

WXPLUGIN_API
WindowHandle *getWindowHandle(const char *windowName);
WXPLUGIN_API
int setDefaultWindowParent(WindowHandle *windowHandle);
WXPLUGIN_API
int displayDialogue(const char *message, const char *caption, long style);
WXPLUGIN_API
int getDataDir(char *buff, int size);
WXPLUGIN_API
int getUserDataDir(char *buff, int size);
#ifdef _WIN32
WXPLUGIN_API
int getInstallationDir(char *buff, int size);
#endif
WXPLUGIN_API
char getPathSeparator(void);

#if defined __cplusplus
    }
#endif

#endif /* WXPLUGIN_H_ */
