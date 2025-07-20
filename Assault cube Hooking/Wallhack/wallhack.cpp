#include "wallhack.h"

void Wallhack::Draw() {
    // Validar player count
    int* currentPlayers = (int*)(Globals::gameModuleAddress + offsets::PlayerCount);
    if (!currentPlayers || *currentPlayers <= 0 || *currentPlayers > 32) return;

    // Validar matrix
    float* matrix = (float*)(Globals::gameModuleAddress + offsets::viewMatrix);
    if (!matrix) return;

    // Validar entity list
    uintptr_t* entityList = (uintptr_t*)(Globals::gameModuleAddress + offsets::EntityList);
    if (!entityList) return;

    // Viewport
    int viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);

    for (int i = 1; i < *currentPlayers; i++) {
        uintptr_t* entityAddr = (uintptr_t*)(*entityList + (i * 0x4));
        if (!entityAddr) continue;

        auto entity = std::make_unique<CEntity>(entityAddr);

        int health = entity->getHealth();
        
        if (health > 100 || health <= 0) continue;


        Render::Color_RGBA color = Render::red;

        Vec3 screenHead{ 0 }, screenFoot{ 0 };

       
        
        

        if (Render::WorldToScreen(entity->getHeadPosition(), screenHead, matrix, viewport[3], viewport[2]) && Render::WorldToScreen(entity->getFeetPosition(), screenFoot, matrix, viewport[3], viewport[2])) {
            
            
            float boxHeight = screenHead.y - screenFoot.y;
            float boxWidth = boxHeight / 2.f;

            float porcentajeBarraVida = (boxHeight / 100) * health;
            std::cout << "box height: " << boxHeight << std::endl;

            Render::DrawLine(viewport[2] / 2, viewport[3], screenFoot.x, screenFoot.y, color);
            Render::DrawCircle(screenHead.x, screenHead.y, 10, 100, color);
            Render::DrawLine(screenFoot.x + (boxWidth / 1.5), screenFoot.y, screenFoot.x + (boxWidth / 1.5), screenFoot.y + porcentajeBarraVida, Render::green);
            Render::DrawRect(screenHead.x - (boxWidth / 2.f), screenHead.y, screenFoot.x + (boxWidth / 2), screenFoot.y, color);
            
            
        }
        //Render::DrawCircle(viewport[2] / 2, viewport[3] / 2, 25, 100, color);
    }
}
