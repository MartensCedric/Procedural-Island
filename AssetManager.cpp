//
// Created by cedric on 21/02/18.
//

#include <iostream>
#include "AssetManager.h"
bool AssetManager::loadTexture(const char *path) {

    sf::Texture* texture = new sf::Texture();

    if(!texture->loadFromFile(path))
        return false;

    map[std::string(path)] = texture;
}

const sf::Texture* AssetManager::getTexture(const char *path) const
{
    if(map.find(path) != map.end())
    {
        return map.at(std::string(path));
    }

    std::cerr << "Could not find texture at path : " << path << std::endl;
    throw std::exception();
}

AssetManager::~AssetManager() {
    for(TextureMap::iterator it = map.begin(); it != map.end(); it++)
        delete it->second;
}
