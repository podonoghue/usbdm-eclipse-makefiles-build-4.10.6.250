/*
 * wxPlugin.h
 *
 *  Created on: 28/04/2011
 *      Author: PODonoghue
 */
#ifndef WXPLUGIN_H_
#define WXPLUGIN_H_

#if defined(useWxWidgets) && !defined(WXPLUGIN_DLL_EXPORTS)

#include <wx/wx.h>

//=========================================================
// Linking against wxWidgets libraries
   #define displayDialogue(message, caption, style)          \
         wxMessageBox(                                       \
            wxString((message), wxConvUTF8), /* message */   \
            wxString((caption), wxConvUTF8), /* caption */   \
            (style),                         /* style   */   \
            NULL                             /* parent  */   \
            );

#else // !useWxWidgets

//=========================================================
// Linking against wxPlugin or building DLL

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

#ifdef WXPLUGIN_DLL_EXPORTS
   //! These definition are used when WXPLUGIN_API is being exported (creating DLL)
   #define WXPLUGIN_API extern "C" DLL_EXPORT
   #define WXPLUGIN_LOCAL          DLL_LOCAL
#else
   //! This definition is used when WXPLUGIN_API is being imported (linking against DLL)
   #define WXPLUGIN_API extern "C" DLL_IMPORT
#endif

#if defined __cplusplus
   extern "C" {
#endif

// Use wxPlugin
#define wxYES                   0x00000002
#define wxOK                    0x00000004
#define wxNO                    0x00000008
#define wxYES_NO                (wxYES | wxNO)
#define wxCANCEL                0x00000010

#define wxOK_DEFAULT            0x00000000
#define wxYES_DEFAULT           0x00000000
#define wxNO_DEFAULT            0x00000080

#define wxICON_EXCLAMATION      0x00000100
#define wxICON_HAND             0x00000200
#define wxICON_WARNING          wxICON_EXCLAMATION
#define wxICON_ERROR            wxICON_HAND
#define wxICON_QUESTION         0x00000400
#define wxICON_INFORMATION      0x00000800
#define wxICON_STOP             wxICON_HAND
#define wxICON_ASTERISK         wxICON_INFORMATION

#define wxSTAY_ON_TOP           0x8000
#define wxCENTER                0x0001

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


#endif // useWxWidgets

#endif /* WXPLUGIN_H_ */
