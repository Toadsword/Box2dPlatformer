#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include "world.h"

enum moveState 
{
	MS_STOP,
	MS_LEFT,
	MS_RIGHT
};

class Entity
{
protected:
	sf::Texture* texture;
	sf::Sprite sprite;
	b2Body* body;
	b2BodyType bodyType;

public:
	moveState moveState;


	Entity(b2Vec2, sf::Texture*, b2BodyType, b2World&);
	~Entity();
	void draw(sf::RenderWindow&);

	b2Body* getBody();
	b2BodyType getBodyType();
	sf::Sprite* getSprite();
};

#endif //! ENTITY_H