#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>

#include <Box2D/Box2D.h>

#include "json.hpp"

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

	b2Vec2 gravity(0, 9.8); //normal earth gravity, 9.8 m/s/s straight down!

	b2World* myWorld = new b2World(gravity);

	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
	window.setFramerateLimit(60.f);
	sf::RectangleShape square (sf::Vector2f(50,50));
	square.setFillColor(sf::Color(2, 56, 37));
	
	b2BodyDef myBodyDef;
	myBodyDef.type = b2_dynamicBody; //this will be a dynamic body
	myBodyDef.position.Set(0, 0); //set the starting position
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

		window.draw(square);
		
		window.display();
	}
	delete myWorld;

	system("pause");
	return 0;
}