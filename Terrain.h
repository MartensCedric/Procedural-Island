//
// Created by cedric on 09/03/18.
//

#ifndef PROCEDURAL_ISLAND_TERRAIN_H
#define PROCEDURAL_ISLAND_TERRAIN_H


class Terrain {
    const int SEA_LEVEL = 0, width, height;
    float** heightMap;
public:
    Terrain(int width, int height);
    int getSeaLevel() const { return SEA_LEVEL; }

private:
    float** createHeightMap() const;
};


#endif //PROCEDURAL_ISLAND_TERRAIN_H
