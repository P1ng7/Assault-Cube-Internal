#include "aimbot.h"


Vec2 SmoothAim(Vec2 current, Vec2 target, float smoothFactor) {
	Vec2 delta = target - current;

	// Corrige envolvimiento de ángulos (180° ↔ -180°)
	if (delta.x > 180.0f) delta.x -= 360.0f;
	if (delta.x < -180.0f) delta.x += 360.0f;
	if (delta.y > 180.0f) delta.y -= 360.0f;
	if (delta.y < -180.0f) delta.y += 360.0f;

	return current + delta / smoothFactor;
}


Vec2 AimBot::calcAngles(Vec3 src, Vec3 to) {
	Vec2 angles;
	angles.x = -std::atan2f((to.x - src.x), (to.y - src.y)) / 3.14159265358979323846f * 180.f + 180.0f;
	angles.y = std::asinf((to.z - src.z) / src.Distance(to)) * (180.f / 3.14159265358979323846f);

	return angles;
}

uintptr_t* AimBot::getBestTarget() {
	float bestFOV = FLT_MAX;
	uintptr_t* target = 0;


	uintptr_t* localPlayerAdrr = (uintptr_t*)(Globals::gameModuleAddress + offsets::LocalPlayer);
	auto localPlayer = std::make_unique<CEntity>(localPlayerAdrr);

	int* players_in_party = (int*)(Globals::gameModuleAddress + offsets::PlayerCount);
	
	uintptr_t* entityListEntry = (uintptr_t*)(Globals::gameModuleAddress + offsets::EntityList);

	for (int i = 1; i < *players_in_party; i++) {
		uintptr_t* entityAddr = (uintptr_t*)(*entityListEntry + (i * 0x4));

		auto entity = std::make_unique<CEntity>(entityAddr);

		int health = entity->getHealth();
		if (health < 0 || health > 100) continue;

		Vec2 viewAngles = localPlayer->getViewAngles();
		Vec2 targetAngles = calcAngles(localPlayer->getHeadPosition(), entity->getHeadPosition());

		float deltaYaw = fabsf(viewAngles.y - targetAngles.y);
		float deltaPitch = fabsf(viewAngles.x - targetAngles.x);

		float fov = sqrt(deltaYaw * deltaYaw + deltaPitch * deltaPitch);

		if (fov < bestFOV) {
			bestFOV = fov;
			target = entityAddr;
		}

	}



	return target;
}

void AimBot::Aim() {
	if (GetAsyncKeyState(VK_XBUTTON1)) {
		uintptr_t* target = getBestTarget();
		uintptr_t* localPlayerAdrr = (uintptr_t*)(Globals::gameModuleAddress + offsets::LocalPlayer);
		auto targetEntity = std::make_unique<CEntity>(target);
		auto localPlayer = std::make_unique<CEntity>(localPlayerAdrr);
		Vec2 anglesToAim = calcAngles(localPlayer->getHeadPosition(), targetEntity->getHeadPosition());
		Vec2* viewAngles = (Vec2*)(*localPlayerAdrr + offsets::CameraX);
		*viewAngles = SmoothAim(*viewAngles, anglesToAim, 25.0f);;
	}
	
}