#pragma once

#include "raymath.h"
#include <vector>
#include "map.hpp"
#include <cmath>

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

    void update(float dt, int speed, Map* map)
    {
        Vector2 direction = {0,0};
        Vector2 forward = {cos(yaw*DEG2RAD), sin(yaw*DEG2RAD)};
        Vector2 right = {-sin(yaw*DEG2RAD), cos(yaw*DEG2RAD)};

        if (IsKeyDown(KEY_W))
        {
            direction += forward * speed * 1/60;
        }
        if (IsKeyDown(KEY_S))
        {
            direction -= forward * speed * 1/60;
        }
        if (IsKeyDown(KEY_A))
        {
            direction -= right * speed * 1/60;
        }
        if (IsKeyDown(KEY_D))
        {
            direction += right * speed * 1/60;
        }

        if (IsKeyDown(KEY_UP)) pos.y -= speed * dt;
        if (IsKeyDown(KEY_DOWN)) pos.y += speed * dt;
        if (IsKeyDown(KEY_RIGHT)) pos.x += speed * dt;
        if (IsKeyDown(KEY_LEFT)) pos.x -= speed * dt;

        if (direction.x && direction.y) direction = Vector2Normalize(direction);

        Vector2 newPos = pos;

        newPos.x += direction.x * speed * dt;

        if (!map->isWall(newPos.x / map->size, pos.y / map->size)) pos.x = newPos.x;

        newPos = pos;
        newPos.y += direction.y * speed * dt;

        if (!map->isWall(pos.x / map->size, newPos.y / map->size)) pos.y = newPos.y;
    }

    
    void render()
    {
        DrawCircle(pos.x, pos.y, size, color);
    }
};