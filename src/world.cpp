#include "world.h"

float World::scale = 0.f;

World::World(b2Vec2 gravity, float scale, float32 timeStep, int32 velocityIterations, int32 positionIterations) :
	timeStep(timeStep), velocityIterations(velocityIterations), positionIterations(positionIterations)
{
	world = new b2World(gravity);
	entitiesManager = new EntityManager();
	setScale(scale);
}

World::~World() 
{
	delete entitiesManager;
	delete world;
}

void World::step() 
{
	world->Step(timeStep, velocityIterations, positionIterations);
}

void World::draw(sf::RenderWindow& window) 
{
	entitiesManager->draw(window);
}

Entity World::addEntity(b2Vec2 position, sf::Texture* texture, b2BodyType bodyType)
{
	return entitiesManager->addEntity(position, texture, bodyType, *world);
}


void World::createWorldTiles(json mapData, std::map<std::string, sf::Texture*>& textureList) 
{
	for (int height = 0; height < mapData.size(); height++)
	{
		for (int width = 0; width < mapData[height].size(); width++)
		{
			if (mapData[height][width] == GROUND)
			{
				b2Vec2 position = b2Vec2(width, height);
				this->addEntity(position, textureList["grass"], b2_staticBody);
			}
		}
	}
}

b2Vec2 World::pixel2meter(sf::Vector2f vect) 
{
	return b2Vec2(vect.x / scale, vect.y / scale);
}

sf::Vector2f World::meter2pixel(b2Vec2 vect) 
{
	return sf::Vector2f(vect.x * scale, vect.y * scale);
}

void World::setScale(const float newScale) 
{
	scale = newScale;
}
