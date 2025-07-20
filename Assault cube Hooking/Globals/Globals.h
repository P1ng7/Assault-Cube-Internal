#pragma once
#include <Windows.h>
#include <iostream>

namespace Globals {
    extern HMODULE hGameModule;
    extern uintptr_t gameModuleAddress;


    void Init();
}