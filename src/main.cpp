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

enum TILES_TYPES 
{
	AIR,
	GROUND
};

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

// - loadTexture
// Description : Charge une texture donnée en paramètre dans la mémoire
// Args :
//		imageName : Nom de l'image
// Return : Le pointeur de la texture
sf::Texture* loadTexture(std::string imageName)
{
	sf::Texture* texture = new sf::Texture();
	if (!texture->loadFromFile(FOLDER_IMG + imageName))
	{
		std::cerr << "Unable to load image (" << imageName << ")";
	}
	return texture;
}

// - loadAllTextures
// Description : Charge toutes les textures voulus et le stock dans une liste de textures
// Args :
//		imageName : textureList Liste de textures à agrémenter
void loadAllTextures(std::map<std::string, sf::Texture*>& textureList)
{
	textureList["grass"] = loadTexture("grass.png");
}

// - createWorldTiles
// Description : Crée la carte du jeu, et stock les tuiles dans une liste
// Args :
//		world : Monde Box2D dans lequel on va créer les tuiles
//		mapData : Données json sur comment doit être créé la carte
//		objectList : Liste où sera stocké les tuiles de la carte
//		textureList : Liste des textures, qui viendra utilisé pour les tuiles
void createWorldTiles(b2World* world, json mapData, std::list<objectManager*>& objectList, std::map<std::string, sf::Texture*>& textureList)
{
	for (int height = 0; height < mapData.size(); height++)
	{
		for (int width = 0; width < mapData[height].size(); width++)
		{
			if (mapData[height][width] == GROUND)
			{
				sf::Vector2f position = meter2pixel(b2Vec2(width, height));
				sf::RectangleShape square(position);
				square.setFillColor(sf::Color(0, 255, 0));

				b2BodyDef myBodyDef;
				myBodyDef.type = b2_staticBody; //this will be a dynamic body
				myBodyDef.position.Set(width, height); //set the starting position
				b2Body* staticBody = world->CreateBody(&myBodyDef);
				/*
				b2PolygonShape shape;
				shape.SetAsBox(0.7, 0.7);
				b2FixtureDef boxFixtureDef;
				boxFixtureDef.shape = &shape;
				boxFixtureDef.density = 1;
				staticBody->CreateFixture(&boxFixtureDef);
				*/
				objectManager* object = new objectManager(position, textureList["grass"], staticBody);
				objectList.push_front(object);
				std::cout << height << " " << width << "\n";
			}
		}
	}
}

// - displayMap
// Description : Affiche la carte à l'écran
// Args :
//		window : Ecran du jeu
//		map : Carte du jeu
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

	std::map<std::string, sf::Texture*> textureList;
	loadAllTextures(textureList);

	b2Vec2 gravity(0, 9.8); //normal earth gravity, 9.8 m/s/s straight down!

	b2World* myWorld = new b2World(gravity);

	std::list<objectManager*> worldMap;
	createWorldTiles(myWorld, data["level"], worldMap, textureList);

	sf::RenderWindow window(sf::VideoMode(data["windows"]["width"], data["windows"]["height"]), "SFML works!");
	window.setFramerateLimit(60.f);
	sf::RectangleShape square (sf::Vector2f(50,50));
	square.setFillColor(sf::Color(2, 56, 37));
	
	b2BodyDef myBodyDef;
	myBodyDef.type = b2_dynamicBody; //this will be a dynamic body
	myBodyDef.position.Set(10, 0); //set the starting position
	b2Body* dynamicBody = myWorld->CreateBody(&myBodyDef);
	b2PolygonShape shape;
	shape.SetAsBox(0.7, 0.7);
	b2FixtureDef boxFixtureDef;
	boxFixtureDef.shape = &shape;
	boxFixtureDef.density = 1;
	dynamicBody->CreateFixture(&boxFixtureDef);

	float32 timeStep = 1 / 60.0;      //the length of time passed to simulate (seconds)
	int32 velocityIterations = 8;   //how strongly to correct velocity
	int32 positionIterations = 3;   //how strongly to correct position

	for (auto it = worldMap.begin(); it != worldMap.end(); it++)
	{
		std::cout << (*it)->getSprite()->getPosition().x << " " << (*it)->getSprite()->getPosition().y << "\n";
	}

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