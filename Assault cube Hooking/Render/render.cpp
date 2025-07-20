#include "render.h"

Render::Color_RGBA Render::red{ 1.0f, 0.0f, 0.0f, 1.0f };
Render::Color_RGBA Render::green{ 0.0f, 1.0f, 0.0f, 1.0f };
Render::Color_RGBA Render::blue{ 0.0f, 0.0f, 1.0f, 1.0f };


void Render::SetupOrtho()
{
	
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glPushMatrix();

	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	glViewport(0, 0, viewport[2], viewport[3]);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, viewport[2], viewport[3], 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glDisable(GL_DEPTH_TEST);
}

void Render::RestoreGL()
{
	glPopMatrix();
	glPopAttrib();
}


void Render::DrawLine(float x, float y, float x2, float y2, const Color_RGBA& color)
{
	glColor4f(color.r, color.g, color.b, color.a);

	glBegin(GL_LINES);
	glVertex2f(x, y);
	glVertex2f(x2, y2);
	glEnd();
}

void Render::DrawRect(float x, float y, float x2, float y2, const Color_RGBA& color)
{
	glColor4f(color.r, color.g, color.b, color.a);

	glBegin(GL_LINE_LOOP);
	glVertex2f(x, y);
	glVertex2f(x2, y);
	glVertex2f(x2, y2);
	glVertex2f(x, y2);
	glEnd();
}

void Render::DrawCircle(float cx, float cy, float r, int num_segments, const Color_RGBA& color)
{
	glColor4f(color.r, color.g, color.b, color.a);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < num_segments; ++i)
	{
		float theta = 2.0f * 3.1415926f * float(i) / float(num_segments); // Ángulo actual

		float x = r * cosf(theta); // Coordenada x
		float y = r * sinf(theta); // Coordenada y

		glVertex2f(x + cx, y + cy); // Añadir punto al círculo
	}
	glEnd();
}



bool Render::WorldToScreen(const Vec3& pos, Vec3& screen, float matrix[16], const int height, const int width) {
	Vec4 clipCoords;

	clipCoords.x = pos.x * matrix[0] + pos.y * matrix[4] + pos.z * matrix[8] + matrix[12];
	clipCoords.y = pos.x * matrix[1] + pos.y * matrix[5] + pos.z * matrix[9] + matrix[13];
	clipCoords.z = pos.x * matrix[2] + pos.y * matrix[6] + pos.z * matrix[10] + matrix[14];
	clipCoords.w = pos.x * matrix[3] + pos.y * matrix[7] + pos.z * matrix[11] + matrix[15];

	
	if (clipCoords.w < 0.1f)
	{
		return false;
	}

	Vec3 NDC;
	NDC.x = clipCoords.x / clipCoords.w;
	NDC.y = clipCoords.y / clipCoords.w;
	NDC.z = clipCoords.z / clipCoords.w;

	
	screen.x = (width / 2 * NDC.x) + (NDC.x + width / 2);
	screen.y = -(height / 2 * NDC.y) + (NDC.y + height / 2);

	return true;
}