#pragma once
#include <iostream>
#include "../Offsets/offsets.h"
#include "../Vector/Vec.h"

class CEntity {
public:
	CEntity();
	CEntity(uintptr_t* base);
	int getHealth();
	Vec3 getHeadPosition();
	Vec3 getFeetPosition();
	Vec2 getViewAngles();
private:
	uintptr_t* base;
};