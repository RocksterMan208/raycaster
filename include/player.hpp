#pragma once

#include "raymath.h"
#include <vector>
#include "map.hpp"

// Creating the player struct which will be the basis of the ray-caster

struct Player
{
    private:

    Vector2 mouseChange {0,0};
    
    public:
    Vector2 pos = {0,0};
    float yaw = 0;
    float playerSensitivity = .05f;
    
    int size = 20;
    Color color = RED;

    float camera(float playerSensitivity)
    {
        mouseChange = GetMouseDelta();
        yaw += mouseChange.x * playerSensitivity;

        return yaw * DEG2RAD;
    }

    void update(float dt, int speed)
    {
        Vector2 direction = {0,0};
        Vector2 forward = {cos(yaw*DEG2RAD), sin(yaw*DEG2RAD)};
        Vector2 right = {-sin(yaw*DEG2RAD), cos(yaw*DEG2RAD)};

        if (IsKeyDown(KEY_W))
        {
            direction += forward * speed * dt;
        }
        if (IsKeyDown(KEY_S))
        {
            direction -= forward * speed * dt;
        }
        if (IsKeyDown(KEY_A))
        {
            direction -= right * speed * dt;
        }
        if (IsKeyDown(KEY_D))
        {
            direction += right * speed * dt;
        }

        pos += direction * speed * dt;
    }
    
    void render()
    {
        DrawCircle(pos.x, pos.y, size, color);
    }
};

// Creating a struct which handles the generating and processing of rays using the player as reference.

struct RAY
{
    private:
    float angle = 0;
    float FOV;
    float offset;
    Player* player;
    Map* map;
    Vector2 direction = {0,0};

    public:
    Vector2 rayPos = {0,0};
    int stepSize = 1;
    float hitDistance = 0;
    float screenX = 0;

    RAY(int fov, float rayOffset, Player* p, Map* m, int x)
    {
        FOV = fov * DEG2RAD;
        offset = rayOffset*DEG2RAD;
        player = p;
        map = m;
        screenX = x;
    }

    void update()
    {
        rayPos = player->pos;
        angle = player->yaw*DEG2RAD;
        direction = {cos(angle+offset), sin(angle+offset)};
    }

    void cast()
    {
        rayPos = player->pos;
        
        while (!map->isWall(rayPos.x / map->size, rayPos.y / map->size))
        {
            rayPos.x += direction.x * stepSize;
            rayPos.y += direction.y * stepSize;
        }

        hitDistance = Vector2Distance(player->pos, rayPos);
    }

    void render2D(Color rayColor)
    {
        DrawLine(player->pos.x, player->pos.y, rayPos.x, rayPos.y, rayColor);
    }

    void render3D(Color rayColor, int numRays)
    {
        float correctedDistance = hitDistance * cos(offset);

        float wallHeight = 20000 / correctedDistance;

        float wallTop = (GetScreenHeight() / 2) - (wallHeight / 2);
        float wallBottom = (GetScreenHeight() / 2) + (wallHeight / 2);

        DrawLineEx(
            {screenX, wallTop},
            {screenX, wallBottom},
            GetScreenWidth() / numRays,
            rayColor
        );
    }
};

std::vector<RAY> createRays(int numRays, int fov, Player* player, Map* map)
{
    std::vector<RAY> rayStruct;
    
    for (int i = 0; i < numRays; i++)
    {
        float angle = ((float)fov / (numRays - 1) * i) - (fov / 2);
        rayStruct.emplace_back(RAY(fov, angle, player, map, i * (1920/numRays)));
    }

    return rayStruct;
}

inline void processRays2D(std::vector<RAY> rays, Color rayColor)
{
    for (auto& r : rays)
    {
        r.update();
        r.cast();
        r.render2D(rayColor);
    }
}

inline void processRays3D(std::vector<RAY> rays, Color rayColor, int numRays)
{
    for (auto& r : rays)
    {
        r.update();
        r.cast();
        r.render3D(rayColor, numRays);
    }
}