//
// Created by cedric on 21/02/18.
//

#ifndef SFML_TEXTURELOADER_H
#define SFML_TEXTURELOADER_H

#include <SFML/Graphics/Texture.hpp>
#include <map>

typedef std::map<std::string, const sf::Texture*> TextureMap;

class AssetManager
{
    TextureMap map;
public:
    bool loadTexture(const char* path);
    const sf::Texture* getTexture(const char* path) const;
    ~AssetManager();
};


#endif //SFML_TEXTURELOADER_H
