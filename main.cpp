#include <SFML/Window.hpp>
#include "AssetManager.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(600, 600), "Procedural Island", sf::Style::Titlebar);
    window.setFramerateLimit(60);

    AssetManager assetManager;

    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);
        window.display();
    }

    return 0;
}
