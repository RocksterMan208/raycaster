#pragma once

#include "raymath.h"
#include <vector>

struct RAY
{
    private:
    float angle = 0;
    float FOV;
    int length;
    float offset;

    public:
    Vector2 rayPos = {0,0};

    RAY(int fov, int rayLength, float rayOffset)
    {
        FOV = fov * DEG2RAD;
        length = rayLength;
        offset = rayOffset*DEG2RAD;
    }

    void update()
    {
    }

    void render(Color rayColor)
    {
        DrawLine(GetScreenWidth()/2, GetScreenHeight()/2, GetScreenWidth()/2+length*cos(offset), GetScreenHeight()/2+length*sin(offset), rayColor);
    }
};

struct Player
{
    private:

    Vector2 mouseChange {0,0};
    float playerSensitivity = 1;
    
    public:
    Vector2 pos = {0,0};
    float yaw = 0;
    
    int size = 20;
    Color color = RED;

    float camera(float playerSensitivity)
    {
        mouseChange = GetMouseDelta();
        yaw += mouseChange.x;

        return yaw * DEG2RAD * playerSensitivity;
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

std::vector<RAY> createRays(int numRays, int rayLength, int fov)
{
    std::vector<RAY> rayStruct;
    
    for (int i = 0; i < numRays; i++)
    {
        rayStruct.emplace_back(RAY(fov, rayLength, fov/numRays*i));
        std::cout << (fov*DEG2RAD)/numRays*i << std::endl;
    }

    return rayStruct;
}

inline void renderRays(std::vector<RAY> rays, Color rayColor)
{
    for (auto r : rays)
    {
        r.render(rayColor);
    }
}