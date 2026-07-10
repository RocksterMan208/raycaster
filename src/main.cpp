#include <iostream>

#include "raylib.h"
#include "player.hpp"
#include "map.hpp"
#include "ray.hpp"

int threeD = 1;
int mouseLock = 1;

int main()
{
    constexpr int screenWidth = 1920;
    constexpr int screenHeight = 1080;
    constexpr int speed = 100;
    constexpr int fov = 45;
    constexpr int numRays = 640;

    constexpr float playerSens = 0.5f;


    Player player;
    player.pos = {200, 200};
    player.size = 10;

    Map mainMap(100.0f, DARKBLUE, "./resources/map.csv");

    std::vector<RAY> rays = createRays(numRays, fov, &player, &mainMap);

    InitWindow(screenWidth, screenHeight, "Ray-caster");
    SetTargetFPS(60);
    DisableCursor();

    Camera2D cam = {0};
    cam.target = player.pos;
    cam.offset = {screenWidth/2, screenHeight/2};
    cam.zoom = 1.0f;
    cam.rotation = 0.0f;

    while (!WindowShouldClose())
    {
    if (IsKeyPressed(KEY_TAB)) threeD = !threeD;
    if (IsKeyPressed(KEY_M)) mouseLock = !mouseLock;
        
        float dt = GetFrameTime();
        
        player.camera(playerSens);
        player.update(dt, speed, &mainMap);

        BeginDrawing();
            ClearBackground(RAYWHITE);

            if (!threeD)
            {
                BeginMode2D(cam);
                
                    mainMap.drawMap();
                    processRays2D(rays, PURPLE);
                    player.render();
                    cam.target = player.pos;

                EndMode2D();
            }
            else 
            {
                DrawRectangleV({0,screenHeight/2}, {screenWidth, screenHeight/2}, GRAY);
                processRays3D(rays, DARKBLUE, numRays);
            }

            //DrawFPS(10,10);

        EndDrawing();
    }
}