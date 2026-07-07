#pragma once

#include "raymath.h"
#include <vector>

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
        if (IsKeyDown(KEY_W)) pos.y -= speed * dt;
        if (IsKeyDown(KEY_S)) pos.y += speed * dt;
        if (IsKeyDown(KEY_A)) pos.x -= speed * dt;
        if (IsKeyDown(KEY_D)) pos.x += speed * dt;
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
    int length;
    float offset;
    Player* player;

    public:
    Vector2 rayPos = {0,0};

    RAY(int fov, int rayLength, float rayOffset, Player* p)
    {
        FOV = fov * DEG2RAD;
        length = rayLength;
        offset = rayOffset*DEG2RAD;
        player = p;
    }

    void update()
    {
        rayPos = player->pos;
        angle = player->yaw*DEG2RAD;
    }

    void render(Color rayColor)
    {
        DrawLine(rayPos.x, rayPos.y, rayPos.x+length*cos(angle+offset), rayPos.y+length*sin(angle+offset), rayColor);
    }
};

std::vector<RAY> createRays(int numRays, int rayLength, int fov, Player* player)
{
    std::vector<RAY> rayStruct;
    
    for (int i = 0; i < numRays; i++)
    {
        float angle = ((float)fov / numRays * i) - (fov / 2);
        rayStruct.emplace_back(RAY(fov, rayLength, angle, player));
    }

    return rayStruct;
}

inline void processRays(std::vector<RAY> rays, Color rayColor)
{
    for (auto& r : rays)
    {
        r.update();
        r.render(rayColor);
    }
}