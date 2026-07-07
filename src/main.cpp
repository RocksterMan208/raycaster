#include <iostream>

#include "raylib.h"
#include "player.hpp"
#include "map.hpp"

bool threeD = 1;

int main()
{
    constexpr int screenWidth = 1920;
    constexpr int screenHeight = 1080;
    constexpr int speed = 100;
    constexpr int fov = 45;
    constexpr int numRays = 320;


    Player player;
    player.pos = {200, 200};
    player.size = 10;

    Map mainMap(100.0f);

    std::vector<RAY> rays = createRays(numRays, fov, &player, &mainMap);

    InitWindow(screenWidth, screenHeight, "Ray-caster");
    SetTargetFPS(60);
    DisableCursor();

    while (!WindowShouldClose())
    {
    if (IsKeyPressed(KEY_TAB)) threeD = !threeD;
        
        float dt = GetFrameTime();
        
        player.update(dt, speed);
        player.camera(0.5f);

        BeginDrawing();
            ClearBackground(RAYWHITE);

            if (!threeD)
            {
                mainMap.drawMap();
                processRays2D(rays, PURPLE);
                player.render();
            }

            if (threeD)
            {
                processRays3D(rays, BLUE, numRays);
            }

            DrawFPS(10,10);

        EndDrawing();
    }
}