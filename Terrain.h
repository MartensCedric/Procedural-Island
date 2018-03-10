//
// Created by cedric on 09/03/18.
//

#ifndef PROCEDURAL_ISLAND_TERRAIN_H
#define PROCEDURAL_ISLAND_TERRAIN_H

namespace Island {

class Terrain {
    const int width, height;
    float seaLevel = 0.6f, beachLevel = 0.7f, grassLevel = 0.85f, mountainLevel = 0.95f;
    float** heightMap;
public:
    Terrain(int width, int height);
    float getSeaLevel() const { return seaLevel; }
    float getBeachLevel() const { return beachLevel; }
    float getGrassLevel() const { return grassLevel; }
    float getMountainLevel() const { return mountainLevel; }
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
