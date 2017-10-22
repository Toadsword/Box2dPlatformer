#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

sf::Texture* loadTexture(std::string);
void loadAllTextures(std::map<std::string, sf::Texture*>&);

#endif