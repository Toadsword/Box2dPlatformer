#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include "world.h"
enum MOVESTATE {
	
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
	MOVESTATE movestate;
	int numcontact;
	
public:
	Entity(b2Vec2, sf::Texture*, b2BodyType, b2World&);
	~Entity();
	void draw(sf::RenderWindow&);
	void move(double deltaX, double deltaY);

	b2Body* getBody();
	b2BodyType getBodyType();
	sf::Sprite* getSprite();

	void beginContact(b2Contact* contact);
	void endContact(b2Contact* contact);
	void Keyboard(unsigned char key);
	void step();
	void setLinearVelocity(b2Vec2);
	void applyForce(b2Vec2);
	void applyLinearImpulse(b2Vec2);
	b2Vec2 getLinearVelocity();
};
//class MyContactListener 
//{
//	
//public:
//	¨void begincontact()
//};
#endif //! ENTITY_H