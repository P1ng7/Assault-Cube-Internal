#include "Globals.h"

HMODULE Globals::hGameModule;
uintptr_t Globals::gameModuleAddress;

void Globals::Init() {
	Globals::hGameModule = GetModuleHandle(L"ac_client.exe");
	Globals::gameModuleAddress = (uintptr_t)hGameModule;
}