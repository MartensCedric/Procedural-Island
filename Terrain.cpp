//
// Created by cedric on 09/03/18.
//

#include "Terrain.h"

namespace Island{
Terrain::Terrain(int width, int height) : width(width), height(height) {
    heightMap = new float*[width];
    for(int i = 0; i < height; i++)
    {
        heightMap[i] = new float[height];
    }
}

Terrain::~Terrain() {
    destroyMap(heightMap);
}

void Terrain::setValues(float (*func)(int, int)) {
    for(int i = 0; i < width; i++)
    {
        for(int j = 0; j < height; j++)
        {
            heightMap[i][j] = func(i, j);
        }
    }
}

    float Terrain::getAt(int x, int y) const {
        return heightMap[x][y];
    }

    void Terrain::smooth() {
        float** newTerrain = new float*[width];

        for(int i = 0; i < width; i++)
        {
            newTerrain[i] = new float[height];
            for(int j = 0; j < height; j++)
            {
                newTerrain[i][j] = getNeighborAverage(i, j);
            }
        }

        destroyMap(heightMap);
        heightMap = newTerrain;
    }

    void Terrain::destroyMap(float **map) {
        for(int i = 0; i < width; i++)
        {
            delete[] map[i];
        }

        delete[] map;
    }

    int Terrain::getNeighborCount(int x, int y) const {
        if(x == 0 && y == 0)
            return 3;
        else if(x == 0 && y == height - 1)
            return 3;
        else if(x == width - 1 && y == height - 1)
            return 3;
        else if(x == width - 1 && y == 0)
            return 3;
        else if(isBorder(x, y))
            return 5;

        return 8;
    }

    bool Terrain::isBorder(int x, int y) const {
        return x == 0 || y == 0 || x == width - 1 || y == height - 1;
    }

    float Terrain::getNeighborAverage(int x, int y) const {
        int neighbors = getNeighborCount(x, y);
        float total = 0.0f;

        for(int i = x - 1; i <= x + 1; i++)
        {
            for(int j = y - 1; j <= y + 1; j++)
            {
                if(i >= 0 && i < width && j >= 0 && j < height && !(i == x && j == y))
                {
                    total += heightMap[i][j];
                }
            }
        }

        return total / (float)neighbors;
    }
}