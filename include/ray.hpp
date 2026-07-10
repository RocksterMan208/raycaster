#pragma once

#include "raymath.h"
#include <vector>
#include "map.hpp"
#include "player.hpp"
#include <cmath>

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
    }

    void cast()
    {
        direction = {cos(angle+offset), sin(angle+offset)};

        Vector2 mapCheck =
        {
            (int)(player->pos.x / map->size),
            (int)(player->pos.y / map->size)
        };
        
        Vector2 step =
        {
            direction.x < 0 ? -1 : 1,
            direction.y < 0 ? -1 : 1
        };

        Vector2 distancePerGridSquare =
        {
            direction.x == 0 ? INFINITY : sqrt(1 + (direction.y / direction.x) * (direction.y / direction.x)),
            direction.y == 0 ? INFINITY : sqrt(1 + (direction.x / direction.y) * (direction.x / direction.y))
        };

        Vector2 playerMapPos =
        {
            player->pos.x / map->size,
            player->pos.y / map->size
        };

        Vector2 fraction =
        {
            playerMapPos.x - mapCheck.x,
            playerMapPos.y - mapCheck.y
        };

        Vector2 distanceToNextGridLine;

        if(direction.x < 0)
            distanceToNextGridLine.x = fraction.x * distancePerGridSquare.x;
        else
            distanceToNextGridLine.x = (1 - fraction.x) * distancePerGridSquare.x;


        if(direction.y < 0)
            distanceToNextGridLine.y = fraction.y * distancePerGridSquare.y;
        else
            distanceToNextGridLine.y = (1 - fraction.y) * distancePerGridSquare.y;

        for(int i = 0; i < 50; i++)
        {
            if(distanceToNextGridLine.x < distanceToNextGridLine.y)
            {
                mapCheck.x += step.x;
                hitDistance = distanceToNextGridLine.x;
                distanceToNextGridLine.x += distancePerGridSquare.x;
            }
            else
            {
                mapCheck.y += step.y;
                hitDistance = distanceToNextGridLine.y;
                distanceToNextGridLine.y += distancePerGridSquare.y;
            }

            if(map->isWall((int)mapCheck.x, (int)mapCheck.y))
                break;
        }

        hitDistance *= map->size;

        rayPos =
        {
            player->pos.x + direction.x * hitDistance,
            player->pos.y + direction.y * hitDistance
        };
    }

    void render2D(Color rayColor)
    {
        DrawLine(player->pos.x, player->pos.y, rayPos.x, rayPos.y, rayColor);
    }

    void render3D(Color rayColor, int numRays)
    {
        float correctedDistance = hitDistance * cos(offset);

        float wallHeight = 100000 / correctedDistance;

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

inline void processRays2D(std::vector<RAY>& rays, Color rayColor)
{
    for (auto& r : rays)
    {
        r.update();
        r.cast();
        r.render2D(rayColor);
    }
}

inline void processRays3D(std::vector<RAY>& rays, Color mapColor, int numRays)
{
    for (auto& r : rays)
    {
        r.update();
        r.cast();
        r.render3D(mapColor, numRays);
    }
}