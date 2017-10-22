#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include "world.h"
enum MoveState {
	
	LEFT,
	RIGHT
};

class Entity
{
protected:
	sf::Texture* texture;
	sf::Sprite sprite;
	b2Body* body;
	b2BodyType bodyType;
	MoveState movestate;
	
public:
	Entity(b2Vec2, sf::Texture*, b2BodyType, b2World&);
	~Entity();
	void draw(sf::RenderWindow&);
	void move(double deltaX, double deltaY);

	b2Body* getBody();
	b2BodyType getBodyType();
	sf::Sprite* getSprite();

	
	void Keyboard(sf::Keyboard::Key code);
	
	
};

#endif //! ENTITY_H