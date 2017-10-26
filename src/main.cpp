#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <list>
#include <map>

#include <Box2D/Box2D.h>

#include "json.hpp"

#include "world.h"
#include "entityManager.h"
#include "textureManager.h"

#define PIXEL_METER_RATIO 64.f
#define WORLD_TIME_STEP 1.f / 60.0f
#define WORLD_VELOCITY_IT 8
#define WORLD_POSITION_IT 3

using json = nlohmann::json;

int main()
{
	// Reading Json File
	std::ifstream ifs("data/elements.json");
	json data;
	if (ifs.is_open())
		data = json::parse(ifs);
	else
	{
		std::cerr << "Unable to read the json file.\n";
		system("pause");
		return EXIT_FAILURE;
	}
	
	// Load textures 
	std::map<std::string, sf::Texture*> textureList;
	loadAllTextures(textureList);

	// Creating the world
	b2Vec2 gravity(0, 9.8); //normal earth gravity, 9.8 m/s/s straight down!
	World* myWorld = new World(gravity, PIXEL_METER_RATIO, WORLD_TIME_STEP, WORLD_VELOCITY_IT, WORLD_POSITION_IT);
	myWorld->createWorldTiles(data["level"], textureList);

	// Creating main window
	sf::RenderWindow window(sf::VideoMode(data["windows"]["width"], data["windows"]["height"]), "SFML works!");
	window.setFramerateLimit(60.f);
	
	// Creating playable character
	Entity character = myWorld->addEntity(b2Vec2(1, 2), textureList["slime"], b2_dynamicBody);
	
	while (window.isOpen())
	{
		sf::Event event;
		b2Vec2 vel = character.getBody()->GetLinearVelocity();
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		vel.x = 0.f;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			vel.x -= 3.f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			vel.x += 3.f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			if (vel.y == 0)
				vel.y -= 8;
		}

		character.getBody()->SetLinearVelocity(vel);
		myWorld->step();
		// Display manager
		window.clear();
		myWorld->draw(window);
		window.display();
	}

	return 0;
}