
#include <Windows.h>
#include <iostream>
#include "MinHook/MinHook.h"
#include "CEntity/CEntity.h"
#include "Globals/Globals.h"
#include "Offsets/offsets.h"
#include "Render/render.h"
#include "Wallhack/wallhack.h"
#include "Aimbot/aimbot.h"

typedef BOOL(__stdcall* twglSwapBuffers)(HDC hDC);
twglSwapBuffers wglSwapBuffersGateway;

BOOL __stdcall hkwglSwapBuffers(HDC hDC)
{
    Render::SetupOrtho();
    Wallhack::Draw();
    AimBot::Aim();
    Render::RestoreGL();
    
    return wglSwapBuffersGateway(hDC);
}

FILE* OpenDebugConsole() {
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);
    freopen_s(&f, "CONOUT$", "r", stdin);
    freopen_s(&f, "CONOUT$", "w", stderr);
    printf("Cheat Inyected2");

    return f;
}


DWORD WINAPI MainThread(HMODULE hModule) {
    FILE* f = OpenDebugConsole();
    //INIT GLOBALS
    Globals::Init();

    HMODULE hOpenGL = GetModuleHandleA("opengl32.dll");
    if (!hOpenGL)
    {
        MessageBoxA(NULL, "No se pudo obtener opengl32.dll", "Error", MB_OK);
        return 1;
    }

    void* target = GetProcAddress(hOpenGL, "wglSwapBuffers");
    if (!target)
    {
        MessageBoxA(NULL, "No se pudo obtener wglSwapBuffers", "Error", MB_OK);
        return 1;
    }

    if (MH_Initialize() != MH_OK)
    {
        MessageBoxA(NULL, "No se pudo inicializar MinHook", "Error", MB_OK);
        return 1;
    }

    
    MH_STATUS status = MH_CreateHook(target, &hkwglSwapBuffers, reinterpret_cast<void**>(&wglSwapBuffersGateway));
    if (status != MH_OK)
    {
        MessageBoxA(NULL, MH_StatusToString(status), "Error al crear hook", MB_OK);
        return 1;
    }

    // Habilitar hook
    if (MH_EnableHook(target) != MH_OK)
    {
        MessageBoxA(NULL, "No se pudo habilitar el hook", "Error", MB_OK);
        return 1;
    }
    

    while (!GetAsyncKeyState(VK_INSERT)) {

    }

    MH_DisableHook(target);
    MH_Uninitialize();
    

    
    fclose(f);
    FreeConsole();
    FreeLibraryAndExitThread(hModule, 0);
    return 0;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CloseHandle(CreateThread(nullptr, 0, (PTHREAD_START_ROUTINE)MainThread, hModule, 0, nullptr));
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

