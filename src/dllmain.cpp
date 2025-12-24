// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "LilyLib/LilyLib.hpp"
#include "LibraPatch.h"
static HANDLE threadHandle = NULL;

DWORD WINAPI MainThread(HMODULE hModule)
{
    LilyLib::Util::WaitForProcess();
    LibraPatch::installHooks();
    return S_OK;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved)
{

    
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        threadHandle = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)MainThread, hModule, NULL, NULL);
        break;
    case DLL_PROCESS_DETACH:
        CloseHandle(threadHandle);
        LibraPatch::removeHooks();
        break;
    }
    return TRUE;
}

