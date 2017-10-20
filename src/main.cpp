#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <list>
#include <map>

#include <Box2D/Box2D.h>

#include "json.hpp"

#include "objectManager.h"

#define PIXEL_METER_RATIO 64
#define FOLDER_IMG "data/img/"

using json = nlohmann::json;


// - meter2pixel
// Description : Converti les pixels de SFML en mètres de Box2d
// Args :
//		meters : Vecteur  en mètre à convertir
// Return : Vecteur converti en pixel
sf::Vector2f meter2pixel(b2Vec2 meters)
{
	return sf::Vector2f(meters.x * PIXEL_METER_RATIO, meters.y * PIXEL_METER_RATIO);
}

// - pixel2meter
// Description : Converti les mètres de Box2d en pixels de SFML
// Args :
//		pixels : Vecteur en pixels à convertir
// Return : Vecteur converti en mètres
b2Vec2 pixel2meter(sf::Vector2f pixels)
{
	return b2Vec2(pixels.x / PIXEL_METER_RATIO, pixels.y / PIXEL_METER_RATIO);
}

sf::Texture loadTexture(std::string textureName)
{
	sf::Texture texture;
	if (!texture.loadFromFile(FOLDER_IMG + textureName))
	{
		std::cerr << "Unable to load image (" << textureName << ")";
	}
	return texture;
}

void loadAllTextures(std::map<std::string, sf::Texture>& textureList)
{
	textureList["grass"] = loadTexture("data/img/grass.png");
}

void createWorldTiles(b2World* world, json mapData, std::list<objectManager*>& objectList, std::map<std::string, sf::Texture>& textureList)
{
	for (int height = 0; height < mapData.size(); height++)
	{
		for (int width = 0; width < mapData[height].size(); width++)
		{
			if (mapData[height][width] == 1)
			{
				sf::Vector2f position = meter2pixel(b2Vec2(width, height));
				sf::RectangleShape square(position);
				square.setFillColor(sf::Color(0, 255, 0));

				b2BodyDef myBodyDef;
				myBodyDef.type = b2_staticBody; //this will be a dynamic body
				myBodyDef.position.Set(width, height); //set the starting position
				b2Body* staticBody = world->CreateBody(&myBodyDef);
				b2PolygonShape shape;
				shape.SetAsBox(0.7, 0.7);
				b2FixtureDef boxFixtureDef;
				boxFixtureDef.shape = &shape;
				boxFixtureDef.density = 10;
				staticBody->CreateFixture(&boxFixtureDef);
				
				objectManager* object = new objectManager(position, &textureList["grass"], staticBody);
				objectList.push_front(object);
				std::cout << height << " " << width << "\n";
			}
		}
	}
}

void displayMap(sf::RenderWindow& window, std::list<objectManager*>& map)
{
	for (auto it = map.begin(); it != map.end(); it++)
		(*it)->draw(window);	
}

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

	std::list<objectManager*> worldMap;
	std::map<std::string, sf::Texture> textureList;
	b2Vec2 gravity(0, 9.8); //normal earth gravity, 9.8 m/s/s straight down!

	b2World* myWorld = new b2World(gravity);

	createWorldTiles(myWorld, data["level"], worldMap, textureList);

	sf::RenderWindow window(sf::VideoMode(data["windows"]["width"], data["windows"]["height"]), "SFML works!");
	window.setFramerateLimit(60.f);
	sf::RectangleShape square (sf::Vector2f(50,50));
	square.setTexture(&textureList["grass"]);
	//square.setFillColor(sf::Color(2, 56, 37));
	
	b2BodyDef myBodyDef;
	myBodyDef.type = b2_dynamicBody; //this will be a dynamic body
	myBodyDef.position.Set(10, 0); //set the starting position
	b2Body* dynamicBody = myWorld->CreateBody(&myBodyDef);
	b2PolygonShape shape;
	shape.SetAsBox(0.7, 0.7);
	b2FixtureDef boxFixtureDef;
	boxFixtureDef.shape = &shape;
	boxFixtureDef.density = 10;
	dynamicBody->CreateFixture(&boxFixtureDef);

	float32 timeStep = 1 / 60.0;      //the length of time passed to simulate (seconds)
	int32 velocityIterations = 8;   //how strongly to correct velocity
	int32 positionIterations = 80;   //how strongly to correct position


	float speed = 5.0f;
	while (window.isOpen())
	{
		myWorld->Step(timeStep, velocityIterations, positionIterations);
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Space)
				{
					std::cout << "User pressed SPACE\n";
				}
			}
		}
		

		square.setPosition(dynamicBody->GetPosition().x, dynamicBody->GetPosition().y);

		window.clear();

		displayMap(window, worldMap);
		window.draw(square);
		
		window.display();
	}
	delete myWorld;

	return 0;
}