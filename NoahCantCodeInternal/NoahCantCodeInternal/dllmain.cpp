#include "pch.h"
#include "lazy.h"
#include <iostream>
#include <Windows.h>
#include <string>
#include "glob.h"
#include <thread>
#include "memory.h"


#define BYTEn(x, n)   (*((_BYTE*)&(x)+n))
#define BYTE1(x)   BYTEn(x,  1)         
#define BYTEn(x, n)   (*((_BYTE*)&(x)+n))
#define BYTE1(x)   BYTEn(x,  1)         
#include "xor.hpp"
#include "menu.hpp"

void CreateConsole()
{

    if (!AllocConsole()) {
        //Add some error handling here.
        //You can call GetLastError() to get more info about the error.
        return;
    }

    //std::cout, std::clog, std::cerr, std::cin
    FILE* fDummy;
    freopen_s(&fDummy, "CONOUT$", "w", stdout);
    freopen_s(&fDummy, "CONOUT$", "w", stderr);
    freopen_s(&fDummy, "CONIN$", "r", stdin);
    std::cout.clear();
    std::clog.clear();
    std::cerr.clear();
    std::cin.clear();

    //std::wcout, std::wclog, std::wcerr, std::wcin
    HANDLE hConOut = CreateFile(("CONOUT$"), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    HANDLE hConIn = CreateFile(("CONIN$"), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    SetStdHandle(STD_OUTPUT_HANDLE, hConOut);
    SetStdHandle(STD_ERROR_HANDLE, hConOut);
    SetStdHandle(STD_INPUT_HANDLE, hConIn);
    std::wcout.clear();
    std::wclog.clear();
    std::wcerr.clear();
    std::wcin.clear();
    

}

void hook(__int64 addr, __int64 func, __int64* orig)
{
    static uintptr_t hook_addr;
    if (!hook_addr)
        hook_addr = sig_scan(("GameOverlayRenderer64.dll"), ("48 ? ? ? ? 57 48 83 EC 30 33 C0"));
    auto hook = ((__int64(__fastcall*)(__int64 addr, __int64 func, __int64* orig, __int64 smthng))(hook_addr));
    hook((__int64)addr, (__int64)func, orig, (__int64)1);
}

void init() {
    if (!SAFE_CALL(GetModuleHandleA)(("GameOverlayRenderer64.dll")))
    {
        printf("NoWork");
        abort();
    }

    uintptr_t Steam_DXGI_PresentScene = sig_scan(("GameOverlayRenderer64.dll"), ("48 89 6C 24 18 48 89 74 24 20 41 56 48 83 EC 20 41 8B E8"));

    if (Steam_DXGI_PresentScene)
        hook(Steam_DXGI_PresentScene, (__int64)hkPresentScene, (__int64*)&OPresent);
}

bool __stdcall DllMain(HMODULE dll_module, DWORD conclusion, LPVOID reserved)
{
    UNREFERENCED_PARAMETER(dll_module);
    UNREFERENCED_PARAMETER(reserved);
    if (conclusion == 1)
    {
        //CreateConsole();
        Game = (uintptr_t)SAFE_CALL(GetModuleHandleA)("r5apex.exe");
       //std::cout << Game;
      // Being();
       // Being();
       init();

    }

    return TRUE;
}
