#pragma once
#include <iostream>
namespace offsets {
	constexpr uintptr_t iHealth = 0xEC;
	constexpr uintptr_t iTeam = 0x30C;
	constexpr uintptr_t LocalPlayer = 0x18AC00; // 
	constexpr uintptr_t HeadPositionX = 0x4; // 0x2C
	constexpr uintptr_t FeetPositionX = 0x28;
	constexpr uintptr_t PlayerCount = 0x18AC0C; // 0x18AC04
	constexpr uintptr_t EntityList = 0x18AC04;
	constexpr uintptr_t CameraX = 0x34;
	constexpr uintptr_t CameraY = 0x38;
	constexpr uintptr_t viewMatrix = 0x17DFD0;

}