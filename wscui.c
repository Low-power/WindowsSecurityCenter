#include <windows.h>
#include <cpl.h>

#define _NODEBUG

static void *Module = NULL;

// Main entry point for the Control Panel DLL.
int DllMain(void *hModule, unsigned long int ul_reason_for_call, void *lpReserved)
{
  switch (ul_reason_for_call){
    case DLL_PROCESS_ATTACH:{
      Module = (void *)hModule;
    }
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
       break;
  }
  return 1;
}

// The entry point to the Control Panel application.
long int CPlApplet(HWND hwndCPL, unsigned int message, LPARAM lParam1, LPARAM lParam2)
{
#ifndef _NODEBUG
  char DebugMessage[256];
  sprintf(DebugMessage, "func: CPlApplet(%d, %d, %d, %d)", hwndCPL, message, lParam1, lParam2);
  size_t dlen = strlen(DebugMessage) + 1;
  wchar_t DebugMessageW[dlen];
  mbstowcs(DebugMessageW, DebugMessage, dlen);
  MessageBoxW(0, DebugMessageW, L"PC GO Program Debug", 0);
#endif
  switch (message){
    case CPL_INIT:
      // Perform global initializations, especially memory
      // allocations, here.
      // Return 1 for success or 0 for failure.
      // Control Panel does not load if failure is returned.
      return 1;

    case CPL_GETCOUNT:
      // The number of actions supported by this Control
      // Panel application.
      return 1;

    case CPL_NEWINQUIRE:
      // This message is sent once for each dialog box, as
      // determined by the value returned from CPL_GETCOUNT.
      // lParam1 is the 0-based index of the dialog box.
      // lParam2 is a pointer to the NEWCPLINFO structure.
    {
      //assert(0 == lParam1);
      //assert(lParam2);

      NEWCPLINFOW *NewCplInfo = (NEWCPLINFOW *) lParam2;
      if (NewCplInfo) {
         NewCplInfo->dwSize = sizeof(NEWCPLINFOW);
         NewCplInfo->dwFlags = 0;
         NewCplInfo->dwHelpContext = 0;
         NewCplInfo->lData = 501;
         NewCplInfo->hIcon = LoadIconW(Module, (wchar_t *)501);
         mbstowcs(NewCplInfo->szName, "Windows Security Center", 24);
         mbstowcs(NewCplInfo->szInfo, "Monitors system security settings and configurations.", 54);
         //mbstowcs(NewCplInfo->szHelpFile, "", 1);
         // The large icon for this application. Do not free this
         // HICON; it is freed by the Control Panel infrastructure.
         //NewCplInfo->hIcon = LoadIcon(Module, MAKEINTRESOURCE(IDI_HELLOWORLD));
         //LoadString(Module, IDS_APP_TITLE, NewCplInfo->szName, lengthof(NewCplInfo->szName));
         //LoadString(Module, IDS_HELLO, NewCplInfo->szInfo, lengthof(NewCplInfo->szInfo));
         //LoadString(Module, IDC_HelloWorld, NewCplInfo->szInfo, lengthof(NewCplInfo->szInfo));
         //_tcscpy(lpNewCplInfo->szHelpFile, _T(""));

         return 0;
      }
      return 1;  // Nonzero value means CPlApplet failed.
    }

    case CPL_DBLCLK:
    {
      // The user has double-clicked the icon for the
      // dialog box in lParam1 (zero-based).
/*
      PROCESS_INFORMATION pi = {0};
      if (CreateProcessW(L"//Windows//HelloWorld.exe"), NULL, NULL, NULL, FALSE, 0, NULL, NULL, NULL, &pi)) {
           CloseHandle(pi.hThread);
           CloseHandle(pi.hProcess);
           return 0;
      }*/
      return 1;     // CPlApplet failed.
    }

    //case CPL_STOP:
             // Called once for each dialog box. Used for cleanup.
    case CPL_EXIT:
             // Called only once for the application. Used for cleanup.
    default:
             return 0;
  }

  return 1;        // CPlApplet failed.
}                    // CPlApplet


//decompiled from Windows XP
/*
int CPlApplet(int ecx0, int edx0, int a1, unsigned __int16 a2, int a3, int a4)
{
  int v6; // edx@1
  int ebp0; // ebp@0
  signed int v8; // ebx@5
  signed int v9; // eax@8
  int v10; // edx@8
  signed int v11; // eax@10
  LONG v12; // eax@15
  DWORD v13; // eax@16
  int v15; // [sp+Ch] [bp-208h]@1
  WCHAR Buffer; // [sp+10h] [bp-204h]@16
  char v17; // [sp+12h] [bp-202h]@16
  __int16 v18; // [sp+20Eh] [bp-6h]@16
  int v19; // [sp+210h] [bp-4h]@1

  v19 = dword_4BA686B8;
  sub_4BA53278((int)&v15, edx0);
  if ( a2 == 1 )
  {
    v8 = 0;
    v12 = (LONG)LoadLibraryExW(L"xpsp2res.dll", 0, 0);
    if ( !v12 )
    {
      Buffer = 0;
      memset(&v17, 0, 0x1FCu);
      v18 = 0;
      v13 = GetLastError();
      FormatMessageW(0x1000u, 0, v13, 0, &Buffer, 0x100u, 0);
      goto LABEL_19;
    }
    sub_4BA5CE8B(v12);
    goto LABEL_18;
  }
  if ( a2 == 2 )
    goto LABEL_18;
  if ( a2 == 3 )
  {
    *(_DWORD *)a4 = 200;
    *(_DWORD *)(a4 + 4) = 0;
    *(_DWORD *)(a4 + 8) = 0;
    goto LABEL_18;
  }
  if ( a2 == 5 )
  {
    sub_4BA5616D(ebp0, a1, dword_4BA6874C != 0);
    goto LABEL_18;
  }
  v8 = 0;
  if ( a2 != 8 )
  {
    if ( a2 == 10 )
      dword_4BA6874C = a4;
    goto LABEL_19;
  }
  *(_DWORD *)a4 = 468;
  *(_DWORD *)(a4 + 16) = 0;
  sub_4BA536D5((int)&v15, v6, 0x17DAu);
  v9 = sub_4BA55F00(a4 + 20, 32, v15, *(_DWORD *)(v15 - 12));
  if ( !v9 || v9 == -2147024774 )
  {
    sub_4BA536D5((int)&v15, v10, 0x17D8u);
    v11 = sub_4BA55F00(a4 + 84, 64, v15, *(_DWORD *)(v15 - 12));
    if ( !v11 || v11 == -2147024774 )
    {
LABEL_18:
      v8 = 1;
      goto LABEL_19;
    }
  }
LABEL_19:
  sub_4BA53290((int)&v15);
  return v8;
}
*/

/*
int main(){
	return 0;
}

int DllMain(){
	return 1;
}

int DllEntryPoint(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved)
{
	return 1;
}*/
