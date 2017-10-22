#ifndef WORLD_H
#define WORLD_H

#include <Box2D\Box2D.h>
#include <iostream>
#include <fstream>

#include "json.hpp"

#include "entityManager.h"

using json = nlohmann::json;

enum TILES_TYPES
{
	AIR,
	GROUND
};

class World {
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
	void addEntity(b2Vec2, sf::Texture*, b2BodyType = b2_staticBody);
	bool createWorldTiles(json mapData, std::map<std::string, sf::Texture*>& textureList);

	b2Vec2 pixel2meter(sf::Vector2f);
	sf::Vector2f meter2pixel(b2Vec2);
	void setScale(const float);
};

#endif // !WORLD_H