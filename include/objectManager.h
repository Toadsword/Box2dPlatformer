#ifndef OBJECT_MANAGER
#define OBJECT_MANAGER

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>

class objectManager
{
private:
	sf::Vector2f position;
	sf::Texture* texture;
	sf::Sprite sprite;
	b2Body* body;

public:
	objectManager(sf::Vector2f, sf::Texture*, b2Body*);
	~objectManager();
	void draw(sf::RenderWindow&);
	void move(double deltaX, double deltaY);
	void keyboard(unsigned char key);

	b2Body* getBody();
	sf::Sprite* getSprite();

};

#endif