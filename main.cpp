#include <SFML/Window.hpp>
#include "AssetManager.h"
#include "Terrain.h"
#include "FastNoise.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <iostream>
#include <cmath>

float generate(int x, int y);
float circle(int x, int y);

const float WIDTH = 600.0f;
const float HEIGHT = 600.0f;

FastNoise fnoise(0xdedbeef);

int main() {
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Procedural Island", sf::Style::Titlebar);
    window.setFramerateLimit(60);

    Island::Terrain terrain((int)WIDTH, (int) HEIGHT);

    terrain.setValues(&generate);
    for(int i = 0; i < 50; i++)
        terrain.smooth();

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

        window.clear(sf::Color::White);
        window.draw(sprTerrain);
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