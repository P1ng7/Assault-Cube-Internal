#pragma once
#pragma comment(lib, "OpenGL32.lib")

#include <Windows.h>
#include "../Vector/Vec.h"
#include <gl/GL.h>

namespace Render {
	struct Color_RGBA {
		float r, g, b, a;
	};
	extern Color_RGBA red;
	extern Color_RGBA blue;
	extern Color_RGBA green;

	void SetupOrtho();
	void RestoreGL();

	void DrawLine(float x, float y, float x2, float y2, const Color_RGBA& color);
	void DrawRect(float x, float y, float x2, float y2, const Color_RGBA& color);
	void DrawCircle(float cx, float cy, float r, int num_segments, const Color_RGBA& color);

	bool WorldToScreen(const Vec3& pos, Vec3& screen, float matrix[16], const int height, const int width);
}