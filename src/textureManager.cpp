#include <SFML/Graphics.hpp>
#include <iostream>
#include "textureManager.h"

#define FOLDER_IMG "data/img/"

// - loadTexture
// Description : Charge une texture donnée en paramètre dans la mémoire
// Args :
//		imageName : Nom de l'image
// Return : Le pointeur de la texture
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
// Description : Charge toutes les textures voulus et le stock dans une liste de textures
// Args :
//		imageName : textureList Liste de textures à agrémenter
void loadAllTextures(std::map<std::string, sf::Texture*>& textureList)
{
	textureList["grass"] = loadTexture("grass.png");
	textureList["slime"] = loadTexture("slime.png");
}