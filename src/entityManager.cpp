#include "entityManager.h"

EntityManager::EntityManager()
{
}

EntityManager::~EntityManager()
{
}

void EntityManager::addEntity(b2Vec2 position, sf::Texture* texture, b2BodyType bodyType, b2World & world)
{
	entityList.push_front(Entity(position, texture, bodyType, world));
}

void EntityManager::draw(sf::RenderWindow & window)
{
	for (auto entity : entityList) {
		entity.draw(window);
	}
}
