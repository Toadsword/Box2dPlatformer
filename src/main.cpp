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

#define PIXEL_METER_RATIO 1.f/64.f
#define WORLD_TIME_STEP 1.f / 60.0f
#define WORLD_VELOCITY_IT 8
#define WORLD_POSITION_IT 3

using json = nlohmann::json;

int main()
{
	// Reading the json file
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
	
	
	std::map<std::string, sf::Texture*> textureList;
	loadAllTextures(textureList);

	b2Vec2 gravity(0, 9.8); //normal earth gravity, 9.8 m/s/s straight down!

	World* myWorld = new World(gravity, PIXEL_METER_RATIO, WORLD_TIME_STEP, WORLD_VELOCITY_IT, WORLD_POSITION_IT);

	myWorld->createWorldTiles(data["level"], textureList);

	sf::RenderWindow window(sf::VideoMode(data["windows"]["width"], data["windows"]["height"]), "SFML works!");
	window.setFramerateLimit(60.f);
	unsigned char key = 'a';
	Entity  character =  myWorld->addEntity(b2Vec2(1, 2), textureList["slime"], b2_dynamicBody);
	float speed = 5.0f;
	while (window.isOpen())
	{
		myWorld->step();
		sf::Event event;
		
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				character.Keyboard();
			}
		}

		
		window.clear();
		
		myWorld->draw(window);
		
		window.display();
	}

	return 0;
}