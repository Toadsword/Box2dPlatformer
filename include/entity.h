#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include "world.h"

class Entity
{
private:
	sf::Texture* texture;
	sf::Sprite sprite;
	b2Body* body;
	b2BodyType bodyType;

public:
	Entity(b2Vec2, sf::Texture*, b2BodyType, b2World&);
	~Entity();
	void draw(sf::RenderWindow&);
	void move(double deltaX, double deltaY);

	b2Body* getBody();
	b2BodyType getBodyType();
	sf::Sprite* getSprite();

	void setLinearVelocity(b2Vec2);
	void applyForce(b2Vec2);
	void applyLinearImpulse(b2Vec2);
	b2Vec2 getLinearVelocity();
};
#endif //! ENTITY_H