#pragma once
#include <iostream>
#include "../Vector/Vec.h"
#include "../Globals/Globals.h"
#include "../Offsets/offsets.h"
#include "../CEntity/CEntity.h"

namespace AimBot {


	void Aim();
	uintptr_t* getBestTarget();
	Vec2 calcAngles(Vec3 src, Vec3 to);
}