#ifndef WORLD_H
#define WORLD_H

#include <Box2D\Box2D.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>

#include "json.hpp"

#include "entityManager.h"
#include "entity.h"

using json = nlohmann::json;

class EntityManager;
class Entity;

enum TilesTypes
{
	AIR,
	GROUND
};

class World 
{
private:
	b2World* world;
	EntityManager* entitiesManager;

	static float scale;
	float32 timeStep;
	int32 velocityIterations;
	int32 positionIterations;
public:
	World(b2Vec2, float, float32, int32, int32);
	~World();

	void step();
	void draw(sf::RenderWindow&);
	Entity addEntity(b2Vec2, sf::Texture*, b2BodyType = b2_staticBody);
	void createWorldTiles(json mapData, std::map<std::string, sf::Texture*>& textureList);

	static b2Vec2 pixel2meter(sf::Vector2f);
	static sf::Vector2f meter2pixel(b2Vec2);
	void setScale(const float);
};

#endif // !WORLD_H