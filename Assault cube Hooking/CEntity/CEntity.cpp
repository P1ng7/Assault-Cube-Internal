#include "CEntity.h"


CEntity::CEntity() {};
CEntity::CEntity(uintptr_t* base) : base(base) {}

int CEntity::getHealth() {
	return *(int*)(*this->base + offsets::iHealth);
}

Vec3 CEntity::getHeadPosition() {
	return *(Vec3*)(*this->base + offsets::HeadPositionX);
}

Vec3 CEntity::getFeetPosition() {
	return *(Vec3*)(*this->base + offsets::FeetPositionX);
}

Vec2 CEntity::getViewAngles() {
	return *(Vec2*)(*this->base + offsets::CameraX);
}