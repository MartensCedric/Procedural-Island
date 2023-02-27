#include <SFML/Window.hpp>
#include "AssetManager.h"
#include "Terrain.h"
#include "FastNoise.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <cmath>
#include <iostream>
#include <time.h>

float generate(int x, int y);
float circle(int x, int y);

const float WIDTH = 600.0f;
const float HEIGHT = 600.0f;
const int MAX_SMOOTH = 300;
FastNoise fnoise(0xdedbeef);

int main() {

    srand(time(0));
    int seed = rand();
    std::cout << "Seed: " << seed << std::endl;
    fnoise.SetSeed(seed);

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Procedural Island", sf::Style::Titlebar);
    window.setFramerateLimit(60);

    sf::Shader shdTerrain;
    if(!shdTerrain.loadFromFile("shaders/default.vs", "shaders/island.fs"))
    {
        std::cerr << "Failed to load shaders" << std::endl;
        return 0;
    }

    Island::Terrain terrain((int)WIDTH, (int) HEIGHT);
    float newSeaLevel = terrain.getSeaLevel();

            terrain.setValues(&generate);
    int timesSmoothed = 0;

    sf::Image imgTerrain;
    imgTerrain.create((int)WIDTH, (int)HEIGHT);
    for(int x = 0; x < WIDTH; x++)
    {
        for(int y = 0; y < HEIGHT; y++)
        {
            float value = terrain.getAt(x, y);
            const sf::Color color(value * 255.0f, value * 255.0f, value * 255.0f);
            imgTerrain.setPixel(x, y, color);
        }
    }
    sf::Texture textureTerrain;
    if(!textureTerrain.loadFromImage(imgTerrain))
    {
        std::cerr << "Failed to load terrain texture" << std::endl;
    }

    sf::Sprite sprTerrain(textureTerrain);

    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
        }

        if(timesSmoothed < MAX_SMOOTH)
        {
            terrain.smooth();
            timesSmoothed += 1;

            for(int x = 0; x < WIDTH; x++)
            {
                for(int y = 0; y < HEIGHT; y++)
                {
                    float value = terrain.getAt(x, y);
                    const sf::Color color(value * 255.0f, value * 255.0f, value * 255.0f);
                    imgTerrain.setPixel(x, y, color);
                }
            }

            textureTerrain.loadFromImage(imgTerrain);
            sprTerrain.setTexture(textureTerrain);
        }else{
            newSeaLevel += 0.00f / 60.0f;
        }

        window.clear(sf::Color::White);
        shdTerrain.setUniform("sea_level", newSeaLevel);
        shdTerrain.setUniform("beach_level", terrain.getBeachLevel());
        shdTerrain.setUniform("grass_level", terrain.getGrassLevel());
        shdTerrain.setUniform("mountain_level", terrain.getMountainLevel());
        window.draw(sprTerrain, &shdTerrain);
        window.display();
    }

    return 0;
}

float generate(int x, int y)
{
    float n = fnoise.GetValue(x * 25.0f, y * 25.0f);
    n += 1.0f;
    n /= 2.0f;

    float v = n + circle(x, y) * 0.75f;

    if(v > 1.0f)
        v = 1.0f;
    else if (v < 0.0f)
        v = 0.0f;
    return v;
}

float circle(int x, int y)
{
    float normX = (float)x / WIDTH;
    float normY = (float)y / HEIGHT;

    float mX = 0.5f;
    float mY = 0.5f;

    float v = (mX - normX) * (mX - normX) + (mY - normY) * (mY - normY);

    v = (float)sqrt(v);
    v *= 2.0f;

    if(v > 1.0f)
        v = 1.0f;
    else if(v < 0.0f)
        v = 0.0f;

    return 1.0f - v;
}
