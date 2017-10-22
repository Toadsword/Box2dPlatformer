#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <list>

#include "entity.h"

class Entity;

class EntityManager
{
private:
	std::list<Entity> entityList;
public:
	EntityManager();
	~EntityManager();
	void draw(sf::RenderWindow&);
	void addEntity(b2Vec2, sf::Texture*, b2BodyType, b2World&);
};

#endif //!ENTITY_MANAGER_H