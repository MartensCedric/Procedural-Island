//
// Created by cedric on 09/03/18.
//

#ifndef PROCEDURAL_ISLAND_TERRAIN_H
#define PROCEDURAL_ISLAND_TERRAIN_H

namespace Island {

class Terrain {
    const int width, height;
    float seaLevel = 0.35f;
    float** heightMap;
public:
    Terrain(int width, int height);
    float getSeaLevel() const { return seaLevel; }
    void smooth();
    void setValues(float (*func)(int, int));
    float getAt(int x, int y) const;
    ~Terrain();

private:
    void destroyMap(float** map);
    int getNeighborCount(int x, int y) const;
    float getNeighborAverage(int x, int y) const;
    bool isBorder(int x, int y) const;
};

}

#endif //PROCEDURAL_ISLAND_TERRAIN_H
