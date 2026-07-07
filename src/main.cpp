#include <iostream>

#include "raylib.h"
#include "player.hpp"

int main()
{
    constexpr int screenWidth = 1920;
    constexpr int screenHeight = 1080;
    constexpr int speed = 200;
    constexpr int fov = 90;

    Player player;
    player.pos = {screenWidth/2, screenHeight/2};

    std::vector<RAY> rays = createRays(30,300,fov, &player);

    InitWindow(screenWidth, screenHeight, "Ray-caster");
    SetTargetFPS(60);
    DisableCursor();

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();
        
        player.update(dt, speed);
        player.camera(0.5f);

        BeginDrawing();
            ClearBackground(RAYWHITE);
        
            renderRays(rays, PURPLE);
            player.render();

            DrawFPS(10,10);

        EndDrawing();
    }
}