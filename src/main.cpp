#include <iostream>

#include "raylib.h"
#include "player.hpp"

int main()
{
    constexpr int screenWidth = 1920;
    constexpr int screenHeight = 1080;
    constexpr int speed = 200;

    std::vector<RAY> rays = createRays(30,300,45);

    Player player;
    player.pos = {screenWidth/2, screenHeight/2};

    InitWindow(screenWidth, screenHeight, "Ray-caster");
    SetTargetFPS(60);
    DisableCursor();

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();
        
        player.update(dt, speed);

        BeginDrawing();
            ClearBackground(RAYWHITE);
            player.render();

            renderRays(rays, PURPLE);

        EndDrawing();
    }
}