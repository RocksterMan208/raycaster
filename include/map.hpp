#pragma once

#include <iostream>
#include "raylib.h"
#include "raymath.h"
#include <vector>

class Map
{
    private:

    public:
    std::vector<std::vector<int>> tiles =
    {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 1, 0, 0, 1, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };

    Vector2 sizeV;
    float size;

    Map(float tileSize)
    {
        sizeV = (Vector2){tileSize, tileSize};
        size = tileSize;
    }

    void drawMap()
    {
        for (int y = 0; y < tiles.size(); y++)
        {
            for (int x = 0; x < tiles[y].size(); x++)
            {
                if (tiles[y][x] == 1)
                    DrawRectangleV({x * size, y * size}, sizeV, BLUE);
            }
        }
    }

    bool isWall(int x, int y)
    {
        if (x < 0 || y < 0 || y >= tiles.size() || x >= tiles[y].size())
        return 1;

    return tiles[y][x] == 1;
    }
};