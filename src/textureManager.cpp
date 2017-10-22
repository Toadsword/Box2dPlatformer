#include <SFML/Graphics.hpp>
#include <iostream>
#include "textureManager.h"

#define FOLDER_IMG "data/img/"

// - loadTexture
// Description : Load a texture in the heap
// Args :
//		imageName : Image name
// Return : Texture's pointer
sf::Texture* loadTexture(std::string imageName)
{
	sf::Texture* texture = new sf::Texture();
	if (!texture->loadFromFile(FOLDER_IMG + imageName))
	{
		std::cerr << "Unable to load image (" << imageName << ")";
	}
	return texture;
}

// - loadAllTextures
// Description : Load all textures that will be used
// Args :
//		textureList : List of textures
void loadAllTextures(std::map<std::string, sf::Texture*>& textureList)
{
	textureList["grass"] = loadTexture("grass.png");
	textureList["slime"] = loadTexture("slime.png");
}