#pragma once

#include <iostream>
#include "raylib.h"
#include "raymath.h"
#include <vector>
#include <fstream>
#include <sstream>

class Map
{
    private:
    Color col;

    public:
    std::vector<std::vector<int>> tiles;

    Vector2 sizeV;
    float size;

    Map(float tileSize, Color mapColor, const std::string& path)
    {
        sizeV = (Vector2){tileSize, tileSize};
        size = tileSize;
        col = mapColor;
        
        loadMap(path);
    }

    void drawMap()
    {
        for (int y = 0; y < tiles.size(); y++)
        {
            for (int x = 0; x < tiles[y].size(); x++)
            {
                if (tiles[y][x] == 1)
                    DrawRectangleV({x * size, y * size}, sizeV, col);
            }
        }
    }

    bool isWall(int x, int y)
    {
        if (x < 0 || y < 0 || y >= tiles.size() || x >= tiles[y].size())
        return 1;

    return tiles[y][x] == 1;
    }

    void loadMap(const std::string& path)
{
    std::ifstream file(path);
    std::string line;

    while(std::getline(file, line))
    {
        std::vector<int> row;
        std::stringstream ss(line);
        std::string value;

        while(std::getline(ss, value, ','))
        {
            row.push_back(std::stoi(value));
        }

        tiles.push_back(row);
    }
}
};