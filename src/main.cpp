#include <iostream>

#include "raylib.h"
#include "player.hpp"
#include "map.hpp"

int threeD = 1;
int mouseLock = 1;

int main()
{
    constexpr int screenWidth = 1920;
    constexpr int screenHeight = 1080;
    constexpr int speed = 100;
    constexpr int fov = 45;
    constexpr int numRays = 320;

    constexpr float playerSens = 0.5f;


    Player player;
    player.pos = {200, 200};
    player.size = 10;

    Map mainMap(100.0f, DARKBLUE);

    std::vector<RAY> rays = createRays(numRays, fov, &player, &mainMap);

    InitWindow(screenWidth, screenHeight, "Ray-caster");
    SetTargetFPS(60);
    DisableCursor();

    while (!WindowShouldClose())
    {
    if (IsKeyPressed(KEY_TAB)) threeD = !threeD;
    if (IsKeyPressed(KEY_M)) mouseLock = !mouseLock;
        
        float dt = GetFrameTime();
        
        player.camera(playerSens);
        player.update(dt, speed);

        BeginDrawing();
            ClearBackground(RAYWHITE);

            if (!threeD)
            {
                mainMap.drawMap();
                processRays2D(rays, PURPLE);
                player.render();
            }
            else processRays3D(rays, DARKBLUE, numRays);


            DrawFPS(10,10);

        EndDrawing();
    }
}